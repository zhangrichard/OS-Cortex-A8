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
// http://stackoverflow.com/questions/12136329/how-does-strcmp-work
int myStrCmp ( char *s1,  char *s2,int length) {
    char *p1 = s1;
    char *p2 = s2;

    for (int i =0;i<length;i++){
        if(*(p1+i) != *(p2+i))
        return -1;
    }
    return 0;
    // while (*p1 != '\0') {
    //     if (*p2 == '\0') return  1;
    //     if (*p2 > *p1)   return -1;
    //     if (*p1 > *p2)   return  1;

    //     p1++;
    //     p2++;
    // }

    // if (*p2 != '\0') return -1;

    // return 0;
}