#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "thread.h"

#define MAX_THREADS 1024

int num_threads = 3;
long long counter = 1;
long long sum = 0;
int test2 = 0;

void foo(void *ptr)
{
	int *tid = (int*)ptr;
	int i;
	int thread_id = tid[0];
	for (i = thread_id; i <= num_threads; i++) {
		sum += counter * (thread_id + 1) * (i + 1);
		counter++;
		if (num_threads <= 16) {
			printf("thread: %d running iteration:%d\n", tid[0], i);
		}
		thread_yield();
	}
	thread_exit();
}

void bar1(void *ptr);

void bar2(void *ptr)
{
	create_thread(bar1, (void*)1);
	printf("bar2: %p\n", ptr);
	thread_exit();
}

void bar1(void *ptr)
{
	if (ptr == NULL) {
		create_thread(bar2, NULL);
	}
	printf("bar1: %p\n", ptr);
	thread_exit();
}

int main(int argc, char *argv[])
{
	int tid[MAX_THREADS];
	int i;

	if (argc >= 2) {
		num_threads = atoi(argv[1]);
		assert(num_threads > 0 && num_threads <= MAX_THREADS);
	}
	if (argc >= 3) {
		test2 = 1;
	}

	printf("starting main thread: num_threads: %d\n", num_threads);

	if (!test2) {
		for (i = 0; i < num_threads; i++) {
			tid[i] = i;
			create_thread(foo, &tid[i]);
		}
	}
	else {
		create_thread(bar1, NULL);
	}

	wait_for_all();

	printf("main thread exiting: counter:%lld\n", sum);

	return 0;
}
