#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mmap_allocator.h"

void *get_next_alloc_space(void *map, unsigned int size)
{
	data_t *tmp;
	data_t new_node;

	if ((tmp = find_free_node(((mem_t *) map)->data, size)) == NULL)
		return (alloc_new_node(map, size));
	if (tmp->data_size >= size + sizeof(data_t)) {
		new_node.data_size = tmp->data_size - size - sizeof(data_t);
		new_node.data = NULL;
		new_node.next = tmp->next;
		tmp->data_size = size;
		tmp->next = (void *) tmp + size + sizeof(data_t);
		memcpy((void *) tmp + size + sizeof(data_t), &new_node,
		sizeof(data_t));
	}
	tmp->data = (void *) tmp + sizeof(data_t);
	return (tmp->data);
}

void *mmap_alloc(void *map, unsigned int size)
{
	mem_t *mem = (mem_t *) map;
	data_t *tmp = mem->data;

	if (tmp == NULL)
		return (alloc_mmap_start(mem, size));
	return (get_next_alloc_space(map, size));
}

unsigned int get_new_mmap_size(data_t *data)
{
	unsigned int size = data->data_size;

	data = data->next;
	while (data != NULL && data->data == NULL) {
		size += sizeof(data_t) + data->data_size;
		data = data->next;
	}
	return (size);
}

void *get_new_next_ptr(data_t *data)
{
	data = data->next;
	while (data != NULL) {
		if (data->data != NULL)
			return (data);
		data = data->next;
	}
	return (NULL);
}

void *create_shared_memory(unsigned int size)
{
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_ANONYMOUS | MAP_SHARED;
	void *shmem = mmap(NULL, size, protection, visibility, -1, 0);
	mem_t mem;

	mem.data = NULL;
	mem.mem_size = size;
	mem.actual_mem_used = sizeof(mem_t);
	memcpy(shmem, &mem, sizeof(mem_t));
	return (shmem);
}
