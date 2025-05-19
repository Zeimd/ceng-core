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





