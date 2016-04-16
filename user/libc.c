#include "libc.h"
#include<stdio.h>
#include<stdarg.h>
// void yield() {
//   // asm volatile( "svc #0     \n"  );
// }
int _read( int fd, void* x, size_t n ) {
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
