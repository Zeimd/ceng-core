Render targets
------------------------

--------------------------
Datatype

The following standard datatypes come in version with 1-4 components

- signed normalized byte (converts to float in range [-1.0, 1.0] )

- unsigned normalized byte (converts to float in range [0.0, 1.0] )

- signed normalized short

- unsigned normalized short

- int8 (converts to float in range [-128,127])

- uint8 (converts to float in range [0,255])

- int16

- uint16

- int32

- uint32

- float16

- float32

Total standard types: 12x4 = 48

Grayscale types have only one channel and set R,G,B to same value:

    gray_unorm8
    gray_unorm16
    gray_unorm24
    gray_unorm32

    gray_fp16

Total grayscale types = 5

Alpha only types

    alpha8

Total alpha only types = 1

Complex types

    unorm_r5_g6_b5
    unorm_b5_g6_r5

    unorm_a1_r5_g5_b5
    unorm_a1_b5_g5_r5

    unorm_a2_r10_g10_b10
    unorm_a2_b10_g10_r10

    unorm_r3_g3_b2
    unorm_b2_g3_r3

    unorm_x8_r8_g8_b8
    unorm_x8_b8_g8_r8

    unorm_x1_r5_g5_b5

    unorm_a4_r4_g4_b4
    unorm_a4_b4_g4_r4
    unorm_x4_r4_g4_b4
    unorm_x4_b4_g4_r4

    unorm_a8_r3_g3_b2
    unorm_a8_b2_g3_r3

Total complex types: 17

Total datatypes = 71

Layouts
--------------------------

The first layout choice is between AOS and SOA. This is mainly driven by what is optimal for pixel shader and if
the render target texture needs to be client accessible or not.

The second choice is how pixels are located in the buffer. Options include:

scanlines (normal way to store images)

linear quads (color values of a 2x2 texel quad are stored in memory like a color[2] [2] array)

tiled (texture is stored as a 2d array of tiles, where color values for [n][n] texels are stored continuously in memory like a 2d array)

    tiled4 (used for unorm_a8_g8_b8_r8 textures to fill a cache line)

tiled, linear quads (each quad in a row in the tile is stored linearly)

    tiled8_lquads (current choice for depth-stencil buffer to match rasterizer tile size)

minimum number of variants: 4x2 = 8 

Multisampling
--------------------------

TBA

Blend modes
--------------------------

Blend state options

global

    alpha to coverage (2)

per render target

    blend enabled (2)

color group

    source color mode (17)

    destination color mode (17)

    blend op (5)

alpha group

    source alpha mode (17)

    destination alpha mode (17)

    alpha blend op (5)

Unique states

all states which have blend disabled are the same, so that leaves us with 4_176_050 combinations.

Total combinations
--------------------

Combining all of the above, 2_371_996_400 unique render target writer variants are needed. 




