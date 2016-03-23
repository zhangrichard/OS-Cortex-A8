#ifndef __P2_H
#define __P2_H

#include <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include <stddef.h>
#include <stdint.h>

#include "libc.h"
#define   BUF_SIZE   100

extern void (*entry_P2)(); 
extern uint32_t tos_P2;
#endif
