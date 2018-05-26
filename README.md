# mmap_allocator
Basic allocator for mmap memory

At this moment, you can create mmap shared memory (create_shared_memory) and use the allocator (mmap_alloc) to malloc any kind of things by just passing the mmap start pointer and the size.

Example are provided in example.c

Does not contain free or dynamic remap for now.

make to build example binary
make lib to build .a lib