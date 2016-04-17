
#ifndef __QUEUE_H
#define __QUEUE_H
// #include <stdio.h>
// #include <stdlib.h>
 #include "constant.h"
typedef struct {
    int priority;
    int index;
} node_t;
 
typedef struct {
    node_t *nodes;
    int len;
    int size;
} heap_t;



void push (heap_t *h, int priority, int index) ;
int pop (heap_t *h) ;
void exitQueue(heap_t *h,int index);
#endif