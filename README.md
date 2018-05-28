# mmap_allocator
Basic allocator for mmap memory

At this moment, you can create mmap shared memory (create_shared_memory) and use the allocator (mmap_alloc) to malloc any kind of things by just passing the mmap start pointer and the size.

All variable can be free by using free_mmap_alloc.

Example are provided in example.c

make example: build example binary
make: build .a lib

By Lucas Alloin https://github.com/LucasALLOIN
Thanks to Alexandre Fourcat https://github.com/Afourcat for the Makefile
