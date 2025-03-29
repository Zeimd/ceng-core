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




