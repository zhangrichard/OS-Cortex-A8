
#ifndef __QUEUE_H
#define __QUEUE_H
#include <stdio.h>
#include <stdlib.h>
 

typedef struct {
    int priority;
    int index;
} node_t;
 
typedef struct {
    node_t nodes[10];
    int len;

} heap_t;
static int indexPop = 1;

void push (heap_t *h, int priority, int index) ;
int pop (heap_t *h) ;
#endif