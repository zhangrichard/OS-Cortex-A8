#include "libc.h"
#include<stdio.h>
#include<stdarg.h>
// void yield() {
//   // asm volatile( "svc #0     \n"  );
// }

// void init_buffer_share(buffer_share *bs){
//   bs->accountNumber=1;
//   bs->money=100;
//   flag[1] =false;
//   flag[0] =false;
// }


int withdrawl(int amount,int *acountMoney){
  if(amount<= *acountMoney){
    
    *acountMoney -=amount;
    return 1;
  }else 
  {
    printf("money value%d\n",*acountMoney );
    return 0;
  }
}

int load(){
  int r;
    asm volatile("svc #4     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            :
            :"r0"
               );

  return r;
}
int store(int data){
  int r;
  asm volatile( "mov r0, %1 \n"
              "svc #5     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            :"r" (data)
            :"r0"
               );
  return r;
}
bool registerInterest(){
  bool r;
  asm volatile( 
              "svc #6     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            :
            :"r0"
               );
  return r;
}
void deRegisterInterest(){
  asm volatile( "svc #7    \n"
               );
}


int file_writes( int fd, void* x, size_t n ) {
  int r;
  asm volatile( "mov r0, %1 \n"
              "mov r1, %2 \n"
              "mov r2, %3 \n"
              "svc #8     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            : "r" (fd), "r" (x), "r" (n) 
            : "r0", "r1", "r2" );
  return r;
}

int file_create( int fd, void* x, size_t n ) {
  int r;
  asm volatile( "mov r0, %1 \n"
              "mov r1, %2 \n"
              "mov r2, %3 \n"
              "svc #9     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            : "r" (fd), "r" (x), "r" (n) 
            : "r0", "r1", "r2" );
  return r;
}

int file_close( int fd, void* x, size_t n ) {
  int r;
  asm volatile( "mov r0, %1 \n"
              "mov r1, %2 \n"
              "mov r2, %3 \n"
              "svc #10     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            : "r" (fd), "r" (x), "r" (n) 
            : "r0", "r1", "r2" );
  return r;
}

int file_open( int fd, void* x, size_t n ) {
  int r;
  asm volatile( "mov r0, %1 \n"
              "mov r1, %2 \n"
              "mov r2, %3 \n"
              "svc #11     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            : "r" (fd), "r" (x), "r" (n) 
            : "r0", "r1", "r2" );
  return r;
}

int file_unlink( int fd, void* x, size_t n ) {
  int r;
  asm volatile( "mov r0, %1 \n"
              "mov r1, %2 \n"
              "mov r2, %3 \n"
              "svc #12     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            : "r" (fd), "r" (x), "r" (n) 
            : "r0", "r1", "r2" );
  return r;
}
int file_read( int fd, void* x, size_t n ) {
  int r;
  asm volatile( "mov r0, %1 \n"
              "mov r1, %2 \n"
              "mov r2, %3 \n"
              "svc #13     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            : "r" (fd), "r" (x), "r" (n) 
            : "r0", "r1", "r2" );
  return r;
}

enum {
 UART_FR_RXFE = 0x10,
 UART_FR_TXFF = 0x20,
 UART0_ADDR = 0x10009000,
};

#define UART_DR(baseaddr) (*(unsigned int *)(baseaddr))
#define UART_FR(baseaddr) (*(((unsigned int *)(baseaddr))+6))
int _reads( int fd, void* x, size_t n ) {
  int r;
  asm volatile( "mov r0, %1 \n"
              "mov r1, %2 \n"
              "mov r2, %3 \n"
              "svc #0     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            : "r" (fd), "r" (x), "r" (n) 
            : "r0", "r1", "r2" );
  return r;
}
int _write( int fd, void* x, size_t n ) {
  int r;

  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "mov r2, %3 \n"
                "svc #1     \n"
                "mov %0, r0 \n" 
              : "=r" (r) 
              : "r" (fd), "r" (x), "r" (n) 
              : "r0", "r1", "r2" );

  return r;
}

int fork(int pid){
  int r;
  asm volatile( "mov r0, %1 \n"
                "svc #2 \n"
                "mov %0,r0 \n"
                :"=r"(r)
                :"r" (pid) 
                : "r0" );
                
  return r;
}
int exit1(int pid){
  int r;
  asm volatile( "mov r0, %1 \n"
                "svc #3 \n"
                "mov %0,r0 \n"
                :"=r"(r)
                :"r" (pid) 
                : "r0" );
               
  return r;
}
// int exit1(){
//   asm volatile("svc #3 \n");
// }
int _read(int file, char *ptr, int len) {
 int todo;
 if(len == 0)
  return 0;
 while(UART_FR(UART0_ADDR) & UART_FR_RXFE);
 *ptr++ = UART_DR(UART0_ADDR);
 for(todo = 1; todo < len; todo++) {
  if(UART_FR(UART0_ADDR) & UART_FR_RXFE) {
   break;
 }
 *ptr++ = UART_DR(UART0_ADDR);
 }
 return todo;
}
int _close(int file) { return -1; }

int _fstat(int file, struct stat *st) {
 st->st_mode = S_IFCHR;
 return 0;
}

int _isatty(int file) { return 1; }

int _lseek(int file, int ptr, int dir) { return 0; }

int _open(const char *name, int flags, int mode) { return -1; }

char *heap_end = 0;
caddr_t _sbrk(int incr) {
 extern char heap_low; /* Defined by the linker */
 extern char heap_top; /* Defined by the linker */
 char *prev_heap_end;

 if (heap_end == 0) {
  heap_end = &heap_low;
 }
 prev_heap_end = heap_end;

 if (heap_end + incr > &heap_top) {
  /* Heap and stack collision */
  return (caddr_t)0;
 }

 heap_end += incr;
 return (caddr_t) prev_heap_end;
 }
