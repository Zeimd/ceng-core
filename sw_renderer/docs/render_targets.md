Render targets
------------------------

--------------------------
Datatype

unorm = converts to float in range (0,1)
uint = unsigned integer
int = signed integer

fp32 = 32-bit floating point
fp16 = 16-bit floating point

gray = single channel, extracts to RGB with same value on each channel

alpha = alpha only format

a = alpha
r = red
g = green
b = blue

Formats have 1-4 channels with different amounts of bits to represent the data

    unorm_r8 
    uint_r8
    int_r8

    unorm_r16
    uint_r16
    int_r16

    fp32_r
    fp16_r

    fp16_gray

    gray_8
    gray_16
    gray_24
    gray_32

    alpha_8

    unorm_r8_g8 
    uint_r8_g8
    int_r8_g8

    unorm_g8_r8
    uint_g8_r8
    int_g8_r8

    unorm_r16_g16
    uint_r16_g16
    int_r16_g16

    unorm_g16_r16
    uint_g16_r16
    int_g16_r16

    fp32_gr
    fp32_rg

    fp16_gr
    fp16_rg

    unorm_r8_g8_b8
    uint_r8_g8_b8
    int_r8_g8_b8

    unorm_b8_g8_r8
    uint_b8_g8_r8
    int_b8_g8_r8

    unorm_b32_g32_r32

    fp32_bgr
    fp32_rgb

    unorm_a8_r8_g8_b8
    uint_a8_r8_g8_b8
    int_a8_r8_g8_b8

    unorm_a8_b8_g8_r8
    uint_a8_b8_g8_r8
    int_a8_b8_g8_r8

    unorm_a16_b16_g16_r16
    uint_a16_b16_g16_r16
    int_a16_b16_g16_r16

    unorm_a16_r16_g16_b16

    unorm_a32_b32_g32_r32

    fp32_abgr
    fp32_argb

    fp16_abgr
    fp16_argb 

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

Total = 71 formats

In practice some of these will be too inefficient to support in a software renderer.



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

all states which have blend disabled are the same, which leaves us with 2*17*17*5*17*17*5 = 4_176_050 combinations.
But if both 



Total combinations
--------------------

Combining all of the above, 2_371_996_400 unique render target writer variants are needed. But since color and alpha are processed separately,
there are in practice two different functions with 2 * 17 * 17 * 5 * 71 * 8 = 1_641_520 variants each.


Blend implementation details
-------------------
For current design that doesn't use runtime shader compiler, using a sequence of callbacks is the only sane way to handle the massive amount of
blending variants. For compiled shaders, segments of handcrafted machine code can be spliced together to get any variant.

Smallest possible format is used for blending. For example, unorm_a8_b8_g8_r8 would use 16-bit integers, since that is the smallest
type for which SSE allows multiplication. Value written by pixel shader is first converted to this format. Similarly, current value from
render target is loaded and converted to this format.

If data is held in SOA, it is trivial to apply different operations to color and alpha. In case of AOS, it is necessary to separate alpha
and color with shifts or masking. Otherwise it is not possible to merge all blend operation variants to be performed at the same time.

NOTE: for unsigned integers, inversion can also be computed in another manner: 255-x = x XOR 255


