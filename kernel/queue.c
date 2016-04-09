#include "queue.h"
 void push (heap_t *h, int priority, int index) {
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
    int index = h->nodes[indexPop].index;
    indexPop++;
    return index;
}