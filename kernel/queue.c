#include "queue.h"
#include <stdlib.h>
#include<stdio.h>
#include "string.h"
int indexPop = 0;
// void queue_init(heap_t *h){
    
// }
void push (heap_t *h, int priority, int index) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = realloc(h->nodes, h->size * sizeof (node_t));
    }
    int i = h->len + 1;
    int j = i / 2;
    while (i > 1 && h->nodes[j].priority < priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    h->nodes[i].priority = priority;
    h->nodes[i].index = index;
    h->len++;
}

int pop (heap_t *h) {
    if (!h->len) {
        return 0;
    }
    int pos = (indexPop % (h->len))+1;
    // printf("at position ready queue%d\n",(indexPop % (h->len))+1);
    int index = h->nodes[pos].index;
    indexPop++;
    
    return index;
} 

void exitQueue(heap_t *h,int index){
    int pos;
    for (int i =1;i<=h->len;i++){
         if (h->nodes[i].index == index){
            pos = i;
         }
    }
    for (int i = pos;i<h->len;i++){
        memcpy(&h->nodes[i],&h->nodes[i+1],sizeof(node_t));
    }
    memset(&h->nodes[h->len],0,sizeof(node_t));
    h->len--;
    indexPop = 0;
    // h->nodes[index+1];
}