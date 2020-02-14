#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "thread.h"

#define MAX_THREADS 1024000

int num_threads = 3;
static int counter = 0;

void foo(void *ptr)
{
	counter++;
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

	printf("starting main thread: num_threads: %d\n", num_threads);

	for (i = 0; i < num_threads; i++) {
		tid[i] = i;
		create_thread(foo, &tid[i]);
		thread_yield();
	}

	wait_for_all();

	printf("main thread exiting : counter:%d\n", counter);

	return 0;
}
