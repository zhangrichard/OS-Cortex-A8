
#ifndef __QUEUE_H
#define __QUEUE_H
// #include <stdio.h>
// #include <stdlib.h>
 #include "constant.h"
typedef struct {
    int priority;
    int pid;
} node_t;
 
typedef struct {
    node_t *nodes;
    int len;
    int size;
    int indexPop;
} heap_t;


// push and search by pid
void push (heap_t *h, int priority, int pid) ;
int pop (heap_t *h) ;
void exitQueueByPid(heap_t *h,int pid);
void queue_init( heap_t *h);
#endif