#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mmap_allocator.h"

typedef struct test_s {
	char *env;
	struct test_s *next;
} test_t;

typedef struct tcontainer_s {
	struct test_s *head;
} tcontainer_t;

void add_to_env_list(void *shmem, tcontainer_t *cont, char *line)
{
	test_t *new_node = mmap_alloc(shmem, sizeof(test_t));
	test_t *last = cont->head;

	memset(new_node, 0, sizeof(test_t));
	new_node->env = mmap_alloc(shmem, strlen(line) + 1);
	memset(new_node->env, 0, strlen(line));
	strcpy(new_node->env, line);
	new_node->next = NULL;
	if (cont->head == NULL) {
		cont->head = new_node;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

void free_list(void *shmem, tcontainer_t *cont)
{
	test_t *current = cont->head;
	test_t *tmp;

	while (current != NULL) {
		tmp = current->next;
		mmap_free(shmem, current->env);
		//free_mmap_alloc(shmem, current);
		current = tmp;
	}
	mmap_free(shmem, cont);
	cont = NULL;
}

int main(int argc, char **argv, char **env)
{
	void *shmem = create_shared_memory(20000);
	tcontainer_t *cont = mmap_alloc(shmem, sizeof(tcontainer_t));
	test_t *tmp;
	int pid;

	(void) argc;
	(void) argv;
	(void) tmp;
	(void) pid;
	(void) env;
	(void) cont;
	cont->head = NULL;
	cont->head = NULL;
	pid = fork();
	if (pid == 0) {
		printf("Child is creating env...\n");
		for (int i = 0; env[i] != NULL; i++) {
			add_to_env_list(shmem, cont, env[i]);
		}
		sleep(3);
		printf("Child free env...\n");
		free_list(shmem, cont);
		sleep(5);
		printf("Child is reading env...\n");
		for (tmp = cont->head; tmp != NULL; tmp = tmp->next) {
			printf("%s\n", tmp->env);
		}
	} else {
		printf("Parent read of env: \n");
		for (tmp = cont->head; tmp != NULL; tmp = tmp->next)
			printf("%s\n", tmp->env);
		sleep(2);
		printf("Parent read of env after 2s: \n");
		//free_mmap_alloc(shmem, cont);
		for (tmp = cont->head; tmp != NULL; tmp = tmp->next) {
			printf("%s\n", tmp->env);
		}
		sleep(4);
		printf("Parent recreating env...: \n");
		cont = mmap_alloc(shmem, sizeof(tcontainer_t));
		memset(cont, 0, sizeof(tcontainer_t));
		for (int i = 0; env[i] != NULL; i++) {
			add_to_env_list(shmem, cont, env[i]);
		}
		sleep(6);
		dump_mmap_mem_info(shmem);
	}
}
