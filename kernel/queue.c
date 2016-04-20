#include "queue.h"
#include <stdlib.h>
#include<stdio.h>
#include "string.h"

// void queue_init(heap_t *h){
    
// }

void queue_init( heap_t *h){
    h->size = 100;
    h->nodes = (node_t*)malloc(h->size*sizeof(node_t));
    h->len = 0;
    h->indexPop = 0;

}
void push (heap_t *h, int priority, int pid) {
    h->indexPop = 0;
    int len = h->len;
    for (int i = 0;i<len;i++ ){
        if(priority>= h->nodes[i].priority )
        {
            for (int j = len-1;j>=i;j--){
                h->nodes[j+1] = h->nodes[j];
            }
            h->nodes[i].priority = priority;
            h->nodes[i].pid = pid;
            // printf("position push%d\n",i );
            // printf("position 0%d\n",h->nodes[0].priority);
            // printf("position cur priority%d\n",priority);

            h->len++;
            return;
        }

    }
    h->nodes[len].priority = priority;
    h->nodes[len].pid = pid;
    h->len++;

}


 
int pop (heap_t *h) {
    if (!h->len) {
        return 0;
    }

    int pos = (h->indexPop % (h->len));
    int pid = h->nodes[pos].pid;
    h->indexPop++;
    return pid;
} 

void exitQueueByPid(heap_t *h,int pid){
    // node_t * p = h->nodes[index+1];
    h->indexPop = 0;
    int pos;
    for (int i =0;i< h->len;i++){
         if (h->nodes[i].pid == pid){
            pos = i;
         }
    }
    for (int i = pos;i<h->len;i++){
        h->nodes[i] = h->nodes[i+1];
    }
    h->len--;
}
 