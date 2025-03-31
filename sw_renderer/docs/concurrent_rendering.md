Concurrent rendering design
---------------------------------------------------
Requirements

- The result must be as if all triangles were drawn sequentially in the order given by client

- 

---------------------------------------------------
Screen-space parallelism

Rasterizing and shading different parts of a single triangle can be easily parallelized by dividing the render target into buckets
whose memory doesn't overlap (eliminates false sharing).

Rasterizing and pixel shading are divided into tasks which only contain the work in a single bucket.

Each bucket gets its own task queue.

---------------------------------------------------
Bucket layout

---------------------------------------------------
Number of buckets

---------------------------------------------------
Triangle-level parallelism

In principle it should be possible to render multiple triangles at the same time as long as they don't overlap in render target memory layout.

The bucket system also allows work on overlapping triangles in parallel. However, before starting a task for a given bucket, it must be ensured that the
task for the previous triangle has finished. Using a mutex to prevent other threads from taking a task from the bucket's queue is the easiest way to handle
this, but it comes with context switch overhead.


