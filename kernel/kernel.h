#ifndef __KERNEL_H
#define __KERNEL_H

#include <stddef.h>
#include <stdint.h>
// #include <stdio.h>
#include   "GIC.h"
#include "PL011.h"
#include "SP804.h"

#include "interrupt.h"


// #include <string.h>
#include "P0.h"
#include "P1.h"
#include "P2.h"
#include "shell.h"

// #include <stdlib.h>
//https://www3.cs.stonybrook.edu/~skiena/392/programs/queue.h
 #include "queue.h"
 // #include "constant.h"

#define O_R 0
#define O_w 1
extern uint32_t tos_user;

typedef struct {
  uint32_t cpsr, pc, gpr[ 13 ], sp, lr;
} ctx_t;

typedef int pid_t;

typedef struct {
  pid_t pid;
  pid_t ppid;
  ctx_t ctx;
  int priority;
} pcb_t;

typedef struct{
 int description;
 char * fcb_address;
 int flags;
 int rwPointer;

}fdt_t;



// typedef struct {
// 	pcb_t pc
// }
// extern int withdrawl(int amount);

#define PCB_SIZE 100

#endif