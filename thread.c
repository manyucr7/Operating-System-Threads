//apt-get install gcc-multilib

#include "thread.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


// thread metadata
struct thread {
	void *esp;
	struct thread *next;
	struct thread *prev;
};

// insert the input thread to the end of the ready list.
struct node {
    struct thread *t;
    struct node *next;
    struct node *prev;
};

struct thread *ready_list = NULL;     // ready list
struct thread *cur_thread = NULL;     // current thread

// defined in context.s
void context_switch(struct thread *prev, struct thread *next);

// insert the input thread to the end of the ready list.
static void push_back(struct thread *ti)
{
    struct node n = (struct node*)malloc(sizeof(struct node));
    n->t=ti;
    n->prev=NULL;
    n->next=NULL;
    struct thread *temp= ready_list;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=node;
    n->prev=temp;
}

// remove the first thread from the ready list and return to caller.
static struct thread *pop_front()
{
    if (ready_list == NULL) {
        return NULL;
    }
    struct thread *temp=ready_list;
    ready_list=ready_list->next;
    ready_list->prev=NULL;
    return temp;
}

// the next thread to schedule is the first thread in the ready list.
// obtain the next thread from the ready list and call context_switch.
static void schedule()
{
    struct thread *prev = cur_thread;
    struct thread *next = pop_front();
    cur_thread = next;
    context_switch(prev, next);
}

// push the cur_thread to the end of the ready list and call schedule
// if cur_thread is null, allocate struct thread for cur_thread
static void schedule1()
{
    push_back(cur_thread);
    schedule();
}

// allocate stack and struct thread for new thread
// save the callee-saved registers and parameters on the stack
// set the return address to the target thread
// save the stack pointer in struct thread
// push the current thread to the end of the ready list
void create_thread(func_t func, void *param)
{
    unsigned *esp=malloc(4096);
    esp+=1024;
    struct thread *t= malloc(sizeof(struct thread));
}


// call schedule1
void thread_yield()
{
    schedule1();
}

// call schedule
void thread_exit()
{
    schedule();
}

// call schedule1 until ready_list is null
void wait_for_all()
{
    while(ready_list!=NULL){
        schedule1();
    }
}

void sleep(struct lock *lock)
{
}

void wakeup(struct lock *lock)
{
}

