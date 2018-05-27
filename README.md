# mmap_allocator
Basic allocator for mmap memory

At this moment, you can create mmap shared memory (create_shared_memory) and use the allocator (mmap_alloc) to malloc any kind of things by just passing the mmap start pointer and the size.

All variable can be free by using free_mmap_alloc.

Example are provided in example.c

make to build example binary
make lib to build .a lib