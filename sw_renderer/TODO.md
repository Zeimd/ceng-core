sw_renderer

TODO
-------------------------------------------------------------------
Rasterizer

- [ ] Fix assumptions about the number of screen buckets.

        software-renderer.cpp : Found that

                        maxBuckets = 2 * maxThreads;

                        rasterTileSize = 8

        buffer-factory.cpp : UpdateBucketAreas()

            number of buckets depends on rasterTileSize.

        pipeline.cpp : Found that number of buckets created is 

                        pixelShaderBuckets = maxThreads * maxBuckets;
                        rasterizerBuckets = maxBuckets;

        rasterizer-setup.cpp

            number of rasterizer buckets comes from render target's bucket info set in buffer-factory.cpp.

        rasterizer-work.cpp

            Found hard-coded assumption that number of output buckets is 3 instead of the 4 possible for rasterizer tile size of 8.

------------------------------------------------------------------
Depth-stencil test

- [ ] BUG: depth test is not skipped in code if disabled in state vector

------------------------------------------------------------------
Pipeline

- [X] BUG: crashes if issuing more than 25 rectangle draw calls per frame

            REASON: Render state instantiation of fragment format wasn't thread safe

- [ ] Use render target specific bucket amounts to prevent scanning unused buckets if maximum allocation is higher

-------------------------------------------------------------------
Pixel shader

- [ ] Implement Shader::Float3. It is needed for most vector math.

- [ ] Change Shader::Float\<N\> to use unions for clarity:

    union SoaField
    {
        float values[4];
        \__m128 vec;
    }

    struct Float4Data
    {
        SoaField x;
        SoaField y;
        SoaField z;
        SoaField w;
    }

    class Float4
    {
        Float4Data* values;
    };

- [ ] Implement Shader::int\<N\>, Shader::uint\<N\>, Shader::bool\<N\>

- [ ] Conversions between shader types

- [ ] Vector helper functions such as dot, cross, norm, invNorm

- [ ] Trigonometric functions

- [ ] Exponential and logarithm

- [ ] Implement Shader::mat\<N\>

------------------------------------------------------------------
Pixel shader special optimization datatypes

Pixels shader abstraction in C++ cannot automatically stich together a shader that performs the
minimum amount of operations. For that reason additional types are needed so that when programmer knows
what is enough, they are available for optimization.

- [ ] byte, ubyte, nbyte, unbyte

        NOTE: Used to represent common texture reads in compact form

- [ ] short, ushort, nshort, unshort

        NOTE: Used for wider texture types and intermediate results of byte arithmetic to prevent overflow

- [ ] Signed fixed point types 7.8 and 15.16

        NOTE: Used for intermediate result of arithmetic involving normalized bytes and fixed point formats

        NOTE: Possibly also as intermediate storage for floating point textures

- [ ] Unsigned fixed point 8.8 and 16.16

        NOTE: Used for intermediate result of arithmetic involving normalized bytes and fixed point formats

        NOTE: Possibly also as intermediate storage for floating point textures

- [ ] Multiplication of nbyte and unbyte:

            1. There is no 8x8->16 multiply instruction, so place inputs in low bytes of 16 bit integers

            2. multiply 16 bit integers, keep lowest 16 bits

            3. store lower byte as result

- [ ] Multiplication of nshort and unshort:

            Multiply 16 bit integers, keep highest 16 bits as result


- [ ] Implement division of 8 and 16 bit integer types (incl. fixed point) by converting to float, 
      which can represent entire 16 bit integer exactly in the mantissa. This allows division to be vectorized.

- [ ] Implement division of 32 bit integer types by converting to double, which can represent entire 32 bit integer
      exactly in the mantissa. This allows division to be vectorized.

------------------------------------------------------------------
External shaders

Many issues caused by fact that shader instance is now created on client side but needs to communicate with pipeline on the DLL side.

- [ ] How to handle common data when instancing? 

- [ ] How to handle texture unit access?

- [ ] How to provide batch data for processing quads?
