#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "thread.h"

#define MAX_THREADS 1024

int counter = 0;

static int acquire(struct lock *lock)
{
	while (lock->val == 0) {
		sleep(lock);
	}
	lock->val = 0;
}

static int release(struct lock *lock)
{
	wakeup(lock);
	lock->val = 1;
}

void foo(void *ptr)
{
	struct lock *l = (struct lock*)ptr;
	int val;
	
	val = counter;
	val++;
	counter = val;

	thread_exit();
}

void bar(void *ptr)
{
	struct lock *l = (struct lock*)ptr;
	int val;

	val = counter;
	val++;
	counter = val;

	thread_exit();
}

int main(int argc, char *argv[])
{
	struct lock l;
	l.val = 1;
	l.wait_list = NULL;

	create_thread(foo, &l);
	create_thread(bar, &l);
	wait_for_all();

	assert(counter == 2);
	printf("main thread exiting.\n");

	return 0;
}
