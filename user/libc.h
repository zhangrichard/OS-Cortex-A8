#ifndef __LIBC_H
#define __LIBC_H

#include <stddef.h>
#include <stdint.h>

// cooperatively yield control of processor, i.e., invoke the scheduler
void yield();

// write n bytes from x to the file descriptor fd
int read( int fd, void* x, size_t n );
int write( int fd, void* x, size_t n );
int fork();
int exit();
int myStrCmp ( char *s1,  char *s2,int length);
#endif
