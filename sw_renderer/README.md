sw_renderer
-----------------------------------------------------------

A software renderer that aims to implement ceng-core's 3d rendering API. It doesn't have compiled shaders
at the moment, which makes it unusable in a real scenario.

-----------------------------------------------------------
Client API

Client sends commands through the command processor. Client commands can be divided into two categories:

1. State change
2. Draw

State change commands are gathered into a potential pipeline state until a draw command is received. At that point the potential
state is instantiated and attached to the draw command, which is then added to a queue.

----------------------------------------------------------
Draw batches

Draw commands are split into self-contained batches to allow efficient parallelization of the vertex shader stage. This does lead to some
duplicate work, but it has the advantage that each batch is independent of the others through the entire pipeline. A naive implementation might 
first determine all vertices it needs to shade and divide that work evenly between tasks, but that would create a bottleneck since each vertex shader
task might have to finish before any of them can move to the next pipeline stage. This approach could also require a significant amount of memory, as
32-bit indices are possible, and potentially all shaded vertices would have to be kept in RAM until the entire draw command has been completed.

The batching is done by going through input primitives. Vertices used by the primitive are added into the batch if they are unique. 
A batch specific index buffer is used to detect duplicates. New vertices are added into the batch buffer. Input primitives are converted to use batch indices. 
If an input primitive doesn't fit into the current batch, a new one is started. 

-----------------------------------------------------------
Pipeline structure

The pipeline implements the following stages:

* Out-of-order pipeline
    * Vertex shader
    * Homogeneous clipper
    * Triangle setup
* In-order pipeline
    * Rasterizer
    * Pixel shader

The tasks in the out-of-order portion can be completed in any order, but they need to be reordered before entering the in-order part
of the pipeline to ensure that things are drawn in the order the draw commands were received.

These stages are implemented as tasks. A priority queue is used by worker threads to select most urgent task. Current priority
is:

1. Pixel shader
2. Rasterizer
3. Triangle setup
4. Clipper
5. Vertex shader

This is largely by the amount of memory each stage's input consumes.

Command processor is a separate thread that executes the queued draw commands. It currently also performs the out-of-order pipeline tasks
in serial order, as they are more complex to parallelize.

For the rasterizer and pixel shader the screen is divided into buckets. There are always more buckets than worker threads to increase
probability that multiple threads can work on the same triangle. Current bucket allocation divides the screen into horizontal stripes.
Only one thread is allowed to work on a bucket at a time to prevent race conditions.

--------------------------------------------------------------
Pipeline state

The pipeline itself is stateless. Relevant state information is carried by each render task. Irrelevant parts of the state are discarded
as the draw command flows through the pipeline.

The following information is part of the state:

1. Clipper state
2. Rasterizer state
3. Depth-stencil test state
4. Active shaders
5. Texture bindings
6. Buffer bindings
7. Shader inputs (uniforms)
8. Shader outputs (render targets)

The contents of textures and buffers is not part of the state. The current design doesn't protect their contents while the rendering is
in progress.

--------------------------------------------------------------
Rasterizer

A half-space rasterizer is used as it allows the parallelization of the process by screen area. It also works well with vector instruction sets. 
In comparison, a traditional scanline rasterizer is a serial process since only one thread can step the edge equations at a time.

The half-space rasterizer uses the line equation

e(x,y) = (y-y0)(x1-x0) - (y1-y0)(x-x0),

which is positive on one side of the edge and negative on the other. If three equations corresponding to the edges of the triangle give the same sign, 
the pixel is inside the triangle. 

The rasterizer is hierarchical: it first checks 8x8 tiles and then proceeds to check partially filled triangles one pixel at a time.
The line equations can also be used to check if a square is entirely inside or outside of the triangle.
This test can be simplified further by realizing that only a single corner of the square must be checked to determine if the square and line intersect.
The corner used depends on the slope of the triangle and whether we check for trivial inside or outside.

Early depth-stencil test is currently performed at tile level if the tile has even one pixel within the triangle.

Fixed point is used to perform the necessary calculations quickly. 

--------------------------------------------------------------
Pixel shader

Pixel shaders are currently written in C++ code that internally expands to use the types used by each input, output and local variable. This isn't
exposed to the client at the moment, and shaders can only be implemented within the library.

Pixel shader works on 2x2 pixel quads. This makes it possible to calculate derivatives, and hence MIP-map levels. 

Pixel shader uses struct of arrays (SoA) instead of the more common array of structs (AoS):

// Traditional approach

struct Vec4
{
    float x;
    float y;
    float z;
    float w;
}

Vec4 pos[4];

// Struct of arrays approach

struct QuadVec4
{
    float x[4];
    float y[4];
    float z[4];
    float w[4];
};

QuadVec4 pos;

When using vector instruction sets (SSE in particular), SoA is better for some things that often appear in
shader code:

1. Swizzles: converted into moves / use only selected channels. AoS would require shuffle or masking.
2. Per component operations: simply skip unused channels. AoS would require shuffle or masking.
3. Dot product (because it requires a horizontal sum in array of structs mode)
4. Cross product (because it requires swizzles)

SoA allows uniform way of handling vectors of any number of components. When 3 components are used, it doesn't waste a SIMD register slot or require special
load/store solution.

The main downside of the SoA approach is that data must be converted between AoS and SoA at various points of the process. For example texture data
comes in AoS. The other is that it produces larger working sets.

Pixel shader inputs must be interpolated in screen space. This is done with

invZ = z0 + (x-x0)*step_dz_dx + (y-y0)*step_dz_dy

z = 1 / invZ

pOverZ = p0 + (x-x0)*step_dpOz_dx + (y-y0)*step_dpOz_dy

p = pOverZ * z

These values must be obtained for the 2x2 quad. One way is to use duplication and stored step vectors

[0, dpOz_dx, dpOz_dy, dpOz_dx + dpOz_dy]

to produce the quad's input value before multiplying each SIMD slot by corresponding z. The data used for this can be halved by using two cleverly
selected step values:

a,b = [dpOz_dx, -dpOz_dx + dpOz_dy]

which gives the quad's points as:

pTopLeft = p0;
pTopRight = pTopLeft + a;
pBottomLeft = pTopRight + b;
pBottomRight = pBottomLeft + a;

and as a bonus, the value for the top-left corner of the next quad on the right is given by

pTopLeft = pBottomRight - b;

so this process can continue through the entire scanline. The steps above generate a Z-order curve.

The division by depth is easily performed with a SIMD operation, and in practice SSE's approximate 1/x instruction is accurate enough for 
rendering purposes unless the camera is super close to the surface. 

--------------------------------------------------------------
Textures

Shader input textures are converted into a 4x4 pixel tile layout. For 4 bits per pixel, this corresponds to a single 64 byte cache line. This increases
the probability that texels that will be needed next are already in cache, regardless of the direction the texture is scanned.

Mip-map level calculation, texel fetch and bilinear interpolation are performed using SSE instrinsics. These can be found in source file

    cr-shader-view-tex2d.cpp

Address is calculated with

    address = base + bytes_per_pixel * (v * rowBytes + u);

or more simply

    address = base + v * yStep + u * xStep;

Much of the address calculation relies on the way PMADDWD instruction works:

using 16-bit integers, we have

steps = [ yStep, xStep, yStep, xStep, yStep, xStep, yStep, xStep],

uv = [v3, u3, v2, u2, v1, u1, v0, u0],

where slots are 16 bit.

pmaddwd out, steps, uv

out = [v3 * yStep, u3 * xStep, v2 * yStep, u2 * xStep, v1 * yStep, u1 * xStep, v0 * yStep, u0 * xStep],

where slots are 32 bit.

In 32-bit mode, it is then simple to add the base address of the texture to each slot.

-----------------------------------------------------------------
Render targets

Shader output textures, also known as render targets, use rows of 2x2 quads as their layout. This allows pixel shader to output with the smallest
extra cost possible. This layout is converted back to scanlines just before presenting the framebuffer.

The renderer doesn't currently handle the possibility of a texture being swapped between input and output role. In those cases the 2x2 rows layout would
most likely be used to avoid the costly conversion process.




