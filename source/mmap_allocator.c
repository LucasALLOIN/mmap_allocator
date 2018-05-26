#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mmap_allocator.h"

void *mmap_alloc(void *map, unsigned int size)
{
	mem_t *mem = (mem_t *) map;
	data_t *tmp = mem->data;
	data_t new_node;

	//printf("New alloc of size %d\nActual size %d\nSpace free %d\n", size, mem->actual_mem_used, mem->mem_size - mem->actual_mem_used);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = map + mem->actual_mem_used;
	new_node.data = map + mem->actual_mem_used + sizeof(data_t);
	new_node.next = NULL;
	memcpy(map + mem->actual_mem_used, &new_node, sizeof(data_t));
	mem->actual_mem_used += size + sizeof(data_t);
	return (new_node.data);
}

void *create_shared_memory(unsigned int size)
{
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_ANONYMOUS | MAP_SHARED;
	void *shmem = mmap(NULL, size, protection, visibility, -1, 0);
	mem_t mem;
	data_t fnode;

	mem.data = shmem + sizeof(mem_t);
	mem.mem_size = size;
	mem.actual_mem_used = sizeof(mem_t) + sizeof(data_t);
	fnode.data = NULL;
	fnode.next = NULL;
	memcpy(shmem, &mem, sizeof(mem_t));
	memcpy(shmem + sizeof(mem_t), &fnode, sizeof(data_t));
	return (shmem);
}

void dump_mmap_mem(void *map)
{
	write(1, map, ((mem_t *) map)->actual_mem_used);
}