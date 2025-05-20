
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
Pixel shader

Explicitly typed input registers? 

    Convert to format expected by pixel shader already at the end of previous shader stage (or interstage). This reduces conversion costs significantly as they
    would be done once instead of per pixel.

    Metadata for initializing explicit registers in a loop

How to handle branches since each pixel in the quad might have different condition?

    Comparisons produce Shader::Boolean 

    Special Shader::If(...) with lambdas? In this case lambdas corresponding to both true and false branches would be executed. The results are then merged.
    This gets complex quickly, since each branch could write to multiple variables, call functions and even write to output registers.



    Switch statements are also difficult to do. Since each pixel performs its own branching. The basic solution is to perform up to 4 different cases and then
    merge them according to the path each pixel took.

How to implement swizzles?

    The vertical layout (SOA) for four pixels makes swizzles kind of trivial since one vector has x-components, second has y, etc. so swizzle turns into array indexing.

    Helper functions in the style of xxz() that return either swizzled copy or lazy evaluation class with references to original. Lazy evaluation of course has the risk
    that the source values get changed before it is evaluated.

Texture samplers output texture's native format by default. This type can then be promoted if operations are performed on it.

Loop implementation is complicated, because each pixel in the quad can potentially have different number of iterations.

    Loop ends when all pixels have hit loop condition

    Alternative loop end conditions: all pixels have used "break;", "discard;" or "return;"

    Once loop ends for a pixel, subsequent operations must mask out that pixel

    "continue;" is straightforward only if all pixels use it. Otherwise the pixel that used continue needs to be masked out for the
    remaining instructions in the loop iteration




