ram limiter design
----------------------------------------------------------

Since the software renderer shares RAM with rest of the software, it must be possible to limit the amount it can use. This does complicate
things somewhat since it now becomes necessary to count allocations, deallocations, and estimate if outputs of operations fit into the
available RAM.

