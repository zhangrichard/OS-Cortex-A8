#include "libc.h"
// void yield() {
//   // asm volatile( "svc #0     \n"  );
// }
int read( int fd, void* x, size_t n ) {
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
int write( int fd, void* x, size_t n ) {
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

int fork(){
  int r;
  asm volatile("svc #2 \n"
                :"=r"(r)
                );
  return r;
}
int exit(){
  asm volatile("svc #3 \n");
}
// http://stackoverflow.com/questions/12136329/how-does-strcmp-work
int myStrCmp (const char *s1, const char *s2) {
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    while (*p1 != '\0') {
        if (*p2 == '\0') return  1;
        if (*p2 > *p1)   return -1;
        if (*p1 > *p2)   return  1;

        p1++;
        p2++;
    }

    if (*p2 != '\0') return -1;

    return 0;
}