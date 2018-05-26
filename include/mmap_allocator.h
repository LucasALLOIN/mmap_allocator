#ifndef MMAP_ALLOCATOR_H
#define MMAP_ALLOCATOR_H

#include <sys/mman.h>

typedef struct data_s {
        void *data;
        struct data_s *next;
} data_t;

typedef struct mem_s {
        struct data_s *data;
        unsigned int mem_size;
        unsigned int actual_mem_used;
} mem_t;

void *mmap_alloc(void *map, unsigned int size);
void *create_shared_memory(unsigned int size);
void dump_mmap_mem(void *map);

#endif
