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

The simplest layout simply divides render target into horizontal stripes. Interleaving can be used to spread work more evenly between threads and to
reduce effect of triangle's screen space location to division of work.


---------------------------------------------------
Number of buckets

Increasing the number of buckets increases opportunities for parallelism, but it comes with overhead for finding work for threads. If buckets are used, there
should be at least as many bucket queues as there are threads. 

One possible solution would be to lock threads to a specific task queue (indexed by threadId) instead of polling all queues to find work. This would eliminate
the queue's execution mutex since its guaranteed that no other thread will ever execute from it. Main downside is that some tasks might be blocked until the right thread becomes
free.

Alternatively a n-way assocation with threads and queues could be used to reduce number of queues a thread scans for work. Since more than one thread can access every queue,
there is reduced risk for priority tasks getting blocked. Downside is that a mutex is still needed for execution.

---------------------------------------------------
Triangle-level parallelism

In principle it should be possible to render multiple triangles at the same time as long as they don't overlap in render target memory layout.
But most of the time a triangle is connected to the previous triangle(s), and the extra effort needed to find queued triangle that is not adjacent might
not be worth it.

The bucket system also allows work on overlapping triangles in parallel. However, before starting a task for a given bucket, it must be ensured that the
task for the previous triangle has finished. Using a mutex to prevent other threads from taking a task from the bucket's queue is the easiest way to handle
this, but it comes with context switch overhead.


