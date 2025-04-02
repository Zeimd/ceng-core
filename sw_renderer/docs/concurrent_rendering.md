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

----------------------------------------------------------------------------------------------
Threading model

Dedicated threads

    In the dedicated thread model worker threads never change their task. X threads are allocated to pixel shading, Y to rasterizing, etc.

    CONS:

        - Limits the number of threads that can be assigned to a specific task compared to task based model, since the total number of threads
          can't be grown without limit

Task model

    All worker threads can execute any task. A task queue provides work from which a task is selected according to priority.

    CONS:

        - Increased overhead from selecting next task to execute

----------------------------------------------------------------------------------------------
Task queue

Priority is

    pixel shader 

        split into buckets. 

        TBC: separate queue per bucket or single serial queue

            single queue would need read mutex to prevent multiple threads popping at the same time

                PROBLEM: bucket exclusion needs to be handled in an another manner

                PROBLEM: task at queue front might be blocking, but tasks behind it in different buckets might be not.

                        TBC: need to implemented task polling that looks ahead into the queue?

            multiple queues increases overhead from looking for tasks to execute

    rasterizer

        works similar to pixel shader

    triangle setup

        allows truly out of order execution as long as output is ordered

    clipper

        allows truly out of order execution as long as output is ordered

    vertex shader

        allows truly out of order execution as long as output is ordered

Data structure

    Multiple queues scanned in order

        NOTE: Current design

    Alternatives

        Priority queue / Heap

            TBA

----------------------------------------------------------------------------------------------
Task starvation 

Because of the way a naive priority queue works, all threads will select tasks from the highest priority queue if possible.
This means that it's possible that all threads do pixel shader tasks and only do more rasterizer work after pixel shader queue
is empty. But rasterizer tasks feed the pixel shader queue, which might stall the pipeline unless at least one thread is intentionally
held back from pixel shading.

----------------------------------------------------------------------------------------------
Out of order execution

To ensure that API call order is followed, various methods can be used to prevent threads from working on tasks too soon:

    futures can be inserted to output queue before task execution starts. This ensures that output is in correct order despite individual tasks
    completing out of order. A future can only be popped from queue once it's associated task is complete.

        NOTE: std::future doesn't allow wait-free checking for ready, so need a custom class

        PROBLEM: might have to fold bucket queues into a single future to keep queue lengths manageable.

        PROBLEM: need a way to signal task completion so that other threads can execute from input queue.

                TBC: would atomic semaphores work? Compare number of issued and completed tasks, which must match before a guard element in the queue
                     can be popped.

    execution mutex on queue prevents other threads from starting a task from the queue while a thread is already executing from the queue.

        NOTE: releasing mutex also signals that work on the task is done.

        NOTE: most likely slow

----------------------------------------------------------------------------------------------
Scheduler thread

Instead of worker threads checking the priority queue for work, that task could be performed by a separate scheduler thread.

The most obvious advantage is that only the scheduler thread will push and pop from the priority queue, so mutexes aren't needed. Futures must be
used to push result storage to output queue before the task that writes the result starts executing. 

To handle screen space bucket exclusion, an array can be kept that has

    currently executing thread id

    ready semaphore (atomic)

In addition to finding a task, the scheduler must also find a free worker thread to execute it. Again there are multiple possible approaches.

    Thread status structure

        Simple array

            PRO: Simple to implement

            PRO: Can simply ask the worker thread object if it's done

            CON: might be fast enough for small number of threads, but for scalability a more complex structure might be needed. 

        Status bit vector

            PRO: a most significant bit finding operation can find a free thread relatively quickly

            CON: worker thread must signal end of task somehow. This risks false sharing for the compact bit vector. Also means the bit vector needs to
                 be atomic

    Thread input queues

        Bypasses the problem of knowing when threads are free by distributing work into thread specific input queues in a round-robin manner.

        CON: introduces some lag. It can't be guaranteed that threads are always executing the highest priority tasks. Also can't guarantee that
             high priority tasks will be added to the queue of the thread that will finish its current task fastest.

----------------------------------------------------------------------------------------------
Completion detection and counters

API call queue

    Used to determine when an API call has been completed.

        NOTE: This means draw calls, not state calls.

Triangle queue

    Used to determine when a triangle has been completely rendered.

Things to count

    number of pixels shaded per thread

    overdraw level?

    depth test pass / fail

    stencil test pass / fail


