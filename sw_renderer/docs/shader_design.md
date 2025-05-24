
Considerations

GLSL 

    Shader program 

        Vertex shader outputs must have same name and type as fragment shader inputs

    Separate shader objects

        Interface variables matched either by type+name or layout location (which is similar to HLSL semantics in function)

HLSL

    Conjecture: 

        semantics have specific hardware locations. As long as semantic matches, vertex shader output gets correctly
        linked to pixel shader input. If output is narrower, input gets filled from (0,0,0,1) as needed

-------------------------------------------------------------------------------
Changes:

- Mapping of c++ variable or struct to uniform(s) in the buffer

- Automatic allocation and linking of locals to locals buffer. Alternatively get alignment of locals right so that a separate
  buffer isn't needed (uses stack)

    NOTE: using alignas(x) for the shader variable types should fix the problem of temporaries getting generated with wrong alignment for SIMD

- Shaders are defined externally so that different shaders can be used. This requires moving much of the shader implementation into the
  user land.

-------------------------------------------------
Pixel shader common

Explicitly typed input registers? 

    Convert to format expected by pixel shader already at the end of previous shader stage (or interstage). This reduces conversion costs significantly as they
    would be done once instead of per pixel.

    Metadata for initializing explicit registers in a loop

Texture sampling

    Texture samplers output texture's native format by default. This type can then be promoted if operations are performed on it.

Discard

    Discard is a special instruction that aborts shading of the current pixel. It can be called from anywhere. The only way to handle it is to mark the pixel
    as skipped in the quad's coverage mask. If all pixels discard, it's possible to exit shader function.

    Discard also prevents use of early depth test, since the result must be as if no buffer writes were done. The only way to handle this is to cache all shader
    writes until entire shader has executed. Only then cached values can be written to render targets.

-------------------------------------------------
Quad Pixel shader

This pixel shader processes entire quad in one call. This has many advantages: it reduces number of function calls, branches and loops by 75%, and allows
derivatives of variables to be calculated, including MIP-map levels.

This is abstracted by shader datatypes that look scalar but handle this duplication internally. There are two data layouts:

    - SOA: in this approach one 4 component vector holds x components, second hold 4 y values etc. It is optimal for most arithmetic purposes. 

    - AOS: in this approach there is a struct of 4 vectors of correct length (one per pixel). Basically the way C++ struct store data.

How to handle branches since each pixel in the quad might have different condition?

    Comparisons of shader datatypes, such as Shader::Float, produce Shader::Bool. It will be used to produce operation mask for each case.

    In AOS, branches require array indices to select affected pixels.

    In SOA, branches require operation masking to affect only selected pixels.

    In general it seems that there isn't a way to abstract away the fact that all operations inside branches, loops, etc. need to be masked.

    In case of AOS, the boolean value for the pixel becomes a yes/no for the entire branch:

        if (x > 1.0f)
        {
            y += 0.5;
        }
        else
        {
            y -= 0.5;
        }

    Expands to                

        Shader::Bool condition = x > 1.0f;

        for(pixel=0; pixel < 4; pixel++)
        {
            if (condition[pixel])
            {
                y[pixel] += 0.5f;
            }
            else
            {
                y[pixel] -= 0.5;
            }
        }

    A special template might be possible:

        template\<typename TRUE_CASE, typename FALSE_CASE\>
        Shader::SerialIf(Shader::Bool& condition, TRUE_CASE && trueLambda, FALSE_CASE && falseLambda )
        {
            for(pixel=0; pixel < 4; ++pixel)
            {
                if (condition[pixel])
                {
                    trueLambda(pixel);
                }
                else
                {
                    falseLambda(pixel);    
                }
                
            }            
        }

    Lambda would be used as

        Shader::Float x,y;

        Shader::SerialIf(x < 1.0f,
            [&](int i)
            {
                y[i] += 0.5f;
            },
            [&](int i)
            {
                y[i] -= 0.5f;
            }
        );

    As can be seen, it would require some manual work, but relatively minor compared to the SOA version. A GLSL compiler could propably convert simple
    if statement into branchless mix instructions.

    A template variant could be added which adds "all true" and "all false" paths for less branching.

    Nested control blocks are written like normal C++ code:

    Shader::SerialIf(x < 1.0f,
        [&](int i)
        {
            y[i] += 0.5f;

            if (x[i] < 0.0f)
            {
                y[i] += 0.5f;
            }
        },
        [&](int i)
        {
            y[i] -= 0.5f;
        }
    );

    An alternative would be to pass the condition to lambda instead of pixel index:

       template\<typename TRUE_CASE, typename FALSE_CASE\>
        Shader::ParallelIf(Shader::Bool& condition, TRUE_CASE && trueLambda, FALSE_CASE && falseLambda )
        {
            trueLambda(condition);
            falseLambda(!condition);                    
        }

    which would be used as:

        Shader::Float x,y;

        Shader::If(x < 1.0f,
            [&](Shader::Bool& condition)
            {
                y(condition) += 0.5f;
            },
            [&](Shader::Bool& condition)
            {
                y(condition) -= 0.5f;
            }
        );

    where

        MaskedWrite Shader::Float::operator () (Shader::Bool& condition)
        {
            return MaskedWrite(this, condition);
        }

        class MaskedWrite
        {
            Shader::Float& base;

            Shader::Bool& condition;

            MaskedWrite& operator += (float x)
            {
                for(int pixel=0; pixel < 4; ++pixel)
                {
                    auto& dest = base.arr[pixel]
                    dest = mix(dest + x, dest, condition);
                }
                
                return *this;
            }
        }

    This approach has the advantage that nested ifs are relatively similar:

        Shader::Float x,y;

        Shader::ParallelIf(x < 1.0f,
            [&](Shader::Bool& condition)
            {
                y(condition) += 0.5f;
            },
            [&](Shader::Bool& condition)
            {
                Shader::ParallelIf( (x < 0.0f) & condition,
                    [&](Shader::Bool& condition)
                    {
                        y(condition) += 0.5f;
                    },
                     [&](Shader::Bool& condition)
                    {
                        y(condition) -= 0.5f;
                    }
                );

            );

    In AOS, the choice between serial and parallel if solution depends on how expensive the branches are. In SOA, only the parallel style can be implemented since the data
    for 4 pixels is mixed in the channels.

    An approach similar to if-else can be taken with switch-case. There are two problems. First, case values aren't necessarily continuous. This means that effort
    must be spent to find the correct case to execute. The second problem is case fall-through. For starters, the fall-through is to the next label in the declaration, 
    not the next label numerically. 

    A dictionary or map would be the obvious choice because it allows sparse values, but search time might be too long for shader code.

    A jump table would be the optimal approach. Jump table consists of entries with a range and an array. If the test value is within the range, the array is indexed 
    directly. If not, we move to the next table. Finding the correct range could be done with a search tree, though. 

        TBC: would it be possible to construct this via templates since case labels are known at compile time?

    Constructing the jump table entries manually would be hazardous work though, as gaps would have to be added to the array where needed. For throwaway work like 
    these hard-coded shaders, a simple table scan would probably be best:

        Shader::Switch(variable, table)
        {
            defaultIndex = table.findDefault();

            for(int pixel=0; pixel < 4; pixel++)
            {
                index = table.find(variable[pixel]);

                bool isBreak = false;

                if (index == -1)
                {
                    index = defaultIndex;
                }

                do
                    table[index].execute(pixel, isBreak)
                    ++index;
                while (isBreak == false);
            }                
        }

    The case functions would then be

        void case_function(int pixel, bool& isBreak)
        {
            BREAK(); // macro for isBreak = true
        }

    Loop implementation is complicated, because each pixel in the quad can potentially have different number of iterations. We also need to handle
    break, discard and return, which can end loop execution early.

        template<typename INIT_TYPE, typename CONDITION_TYPE, typename STEP_TYPE, typename BODY_TYPE
        Shader::For(INIT_TYPE&& initLambda, CONDITION_TYPE&& conditionLambda, STEP_TYPE&& stepLambda, BODY_TYPE&& bodyLambda)
        {
            for(int i=0; i < 4; i++)
            {
                initLambda(i);

                if (conditionLambda(i)) continue;

                do
                {
                    result = bodyLambda(i);

                    switch(result)
                    {
                    discard:
                    break:
                    return:
                    }

                    stepLambda(i);

                } while(conditionLambda(i) == false);
            }                
        }

    Like if-else statements, the lambdas work on only one pixel's values at a time. 


How to implement swizzles?

    NOTE: swizzles where component appears more than once should be read only

    The SOA layout turns swizzles into array indexing.

    In comparison, AOS requires shuffles, masks and blending in SIMD form to achieve the same. 

        1. If lhs and rhs are both swizzles, the swizzle operations are merged

        2. Source operand is swizzled into correct positions. Write mask is generated so that only the selected indices of dest are touched.

        3. For arithmetic operations, vector fields not indicated by mask are replaced by corresponding null operation

            addition, shift: zero

            mul, div: one

            logical or: false           (doesn't turn false in dest into true)

            logical and: true           (doesn't turn true in dest into false)

        4. For assignment, destination and source are blended so that only masked entries are taken from source.

    C++ side interface:

        Helper functions in the style of xxz() that return either swizzled copy or lazy evaluation class with references to original. Lazy evaluation of course has the risk
        that the source values get changed before it is evaluated.

        Implementing as member functions is a lot of work. It might be possible to use templates to write them 
        only once for all types, but if any SIMD specialization is needed, it could be difficult to add.

        Two member functions that take indices as params would be less work but more verbose, but enough for throwaway work of hardcoded shaders. One would be for
        duplicate swizzles, other for the rest. Either enums or structs would be needed to group them as function params.

------------------------------------------------------------------------
Scalar pixel shader

Due to the considerable issues with expressing a quad pixel shader via C++ code, a scalar pixel shader can be considered. Datawise everything works like normal C++ code.

We are still rasterizing quads though, but via 4 shader calls instead of one. 

Calculating MIP-map level is a problem though. The packed shader has access to texture coordinates for all 4 pixels when sampling the texture. It is possible to calculate
shader input values for each pixel before any shader code executes, but the texture coordinates might be modified or generated entirely within the shader.

The only way to solve this would be to synchronize the threads rendering the pixels of the quad so that they wait until all 4 have generated the texture coordinates used
for sampling.

If the pixels are rendered sequentially by a single thread, it's possible to instead split the shader execution into parts that end just before derivatives must be
calculated. In the C++ abstraction this would have to be done manually:

    for(int i=0; i < 4; i++)
    {
        shader_part1();
    }

    for(int i=0; i < 4; i++)
    {
        shader_part2();
    }

As a downside all local variables that need derivatives would have to be stored at class level to ensure visibility over multiple functions.

This approach doesn't work if the texture is sampled in a shader sub-function.






