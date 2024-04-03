sw_renderer
-----------------------------------------------------------

A software renderer that aims to implement ceng-core's 3d rendering API. It doesn't have compiled shaders
at the moment, which makes it unusable in a real scenario.

-----------------------------------------------------------
Pipeline structure

The pipeline implements the following stages:

Vertex shader
Homogeneous clipper
Triangle setup
Rasterizer
Pixel shader

These stages are implemented as tasks. A priority queue is used by worker threads to select most urgent task. Current priority
is:

1. Pixel shader
2. Rasterizer
3. Triangle setup
4. Clipper
5. Vertex shader

This is largely by the amount of memory each stage's input consumes.

For the rasterizer and pixel shader the screen is divided into buckets. There are always more buckets than worker threads to increase
probability that multiple threads can work on the same triangle. Current bucket allocation divides the screen into horizontal stripes.
Only one thread is allowed to work on a bucket at a time to prevent race conditions.

The pipeline itself is stateless. Relevant state information is carried by each render task. Irrelevant parts of the state are discarded
as the draw command flows through the pipeline.

-----------------------------------------------------------
Client API

Client sends commands through the command processor. Client commands can be divided into two categories:

1. State change
2. Draw

State change commands are gathered into a potential pipeline state until a draw command is received. At that point the potential
state is instantiated and attached to the draw command, which is then added to a queue.

----------------------------------------------------------
Draw batches

Draw commands are split into self-contained batches to allow efficient parallelization of the vertex shader stage. This does lead into some
duplicate work, but it has the advantage that each batch is independent of the others through the entire pipeline. A naive implementation might 
first determine all vertices it needs to shade and divide that work evenly between tasks, but that would create a bottleneck since each vertex shader
task might have to finish before any of them can move to the next pipeline stage. This approach could also require a significant amount of memory, as
32-bit indices are possible, and potentially all shaded vertices would have to be kept in RAM until the entire draw command has been completed.

----------------------------------------------------------
Command processor

The command processor is a separate thread that executes the queued draw commands. It currently also performs the following pipeline tasks
as they are more complicated to parallelize:

1. Vertex shader
2. Clipper
3. Triangle setup


