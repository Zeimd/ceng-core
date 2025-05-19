
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

- Shaders are defined externally so that different shaders can be used. This requires moving much of the shader implementation into the
  user land.

-------------------------------------------------
Pixel shader

- Explicitly typed input registers? 

        * Convert to format expected by pixel shader already at the end of previous shader stage. This reduces conversion costs significantly as they
          would be done once instead of per pixel.

        * Metadata for initializing explicit registers in a loop

- How to handle branches since each pixel in the quad might have different condition?

        * Comparisons produce Shader::Boolean 

        * Special Shader::if(...) with lambda?

- Implement Shader::Float3

- Vector helper functions dot, cross, norm

- How to implement swizzles?

        * Separate helper functions in the style of Swizzle.xyzw(input)?

        * Special members for input and local variables that perform the swizzle?

                NOTE: Costly since the members need correct this pointer to use in their conversion functions, and there are a lot of different
                      swizzles




