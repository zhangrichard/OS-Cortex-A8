#ifndef __shell_H
#define __shell_H


#include <stddef.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "libc.h"
#define   BUF_SIZE   100
typedef char  buffer_t  [500];
typedef char* args_t    [10];

// bool flag[2];
// int turn;

// typedef struct {
// 	int accountNumber;
// 	int money;
// 	// https://en.wikipedia.org/wiki/Peterson%27s_algorithm
// }buffer_share;
// int withdrawl(int amount);

extern void (*entry_shell)(); 
// extern uint32_t tos_P0;
#endif
