#ifndef __P0_H
#define __P0_H


#include <stddef.h>
#include <stdint.h>
// #include <stdlib.h>
#include <stdio.h>
#include  <string.h>
#include "libc.h"
#define   BUF_SIZE   100

extern void (*entry_P0)(); 
extern uint32_t tos_P0;
#endif
