

#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    int priority;
    char *data;
} node_t;
 
typedef struct {
    node_t *nodes;
    int len;
    int size;
} heap_t;
 