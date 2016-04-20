#include "file.h"
// #include<stdio.h>
// #include<stdarg.h>

int file_create(void* x) {
  int r;
  asm volatile( "mov r0, %1 \n"
              "svc #8     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            :  "r" (x)
            : "r0" );
  return r;
}
int file_open( void* x, size_t n ) {
  int r;
  asm volatile( "mov r0, %1 \n"
              "mov r1, %2 \n"
              "svc #9     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            : "r" (x), "r" (n) 
            : "r0", "r1" );
  return r;
}

int file_read( int fd, void* x, size_t n ) {
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

int file_writes( int fd, void* x, size_t n ) {
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

// int file_unlink( int fd, void* x, size_t n ) {
//   int r;
//   asm volatile( "mov r0, %1 \n"
//               "mov r1, %2 \n"
//               "mov r2, %3 \n"
//               "svc #12     \n"
//               "mov %0, r0 \n" 
//             : "=r" (r) 
//             : "r" (fd), "r" (x), "r" (n) 
//             : "r0", "r1", "r2" );
//   return r;
// }
void file_close(int fd ) {
  int r;
  asm volatile( "mov r0, %1 \n"
              "svc #13     \n"
              "mov %0, r0 \n" 
            : "=r" (r) 
            : "r" (fd)
            : "r0" );
  // return r;
}