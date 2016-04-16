#ifndef __P0_H
#define __P0_H


#include <stddef.h>
#include <stdint.h>

#include "libc.h"
#define   BUF_SIZE   100
typedef char  buffer_t  [500];
typedef char* args_t    [10];
extern void (*entry_P0)(); 
extern uint32_t tos_P0;
#endif
