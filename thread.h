#ifndef __THREAD_H__
#define __THREAD_H__

typedef void (*func_t)(void*);

struct lock
{
	int val;
	void *wait_list;
};

void create_thread(func_t func, void *param);
void thread_yield();
void thread_exit();
void wait_for_all();

void sleep(struct lock *l);
void wakeup(struct lock *l);

#endif
