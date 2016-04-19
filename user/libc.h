#ifndef __LIBC_H
#define __LIBC_H

#include <stddef.h>
#include <stdint.h>
#include <sys/stat.h>
#include<stdbool.h>

#include "file.h"

// void init_buffer_share(buffer_share *bs);
int withdrawl(int amount,int *acountMoney);
void yield();

int load();

int store(int data);
bool registerInterest();
void deRegisterInterest();


// write n bytes from x to the file descriptor fd
int _reads( int fd, void* x, size_t n );
int write( int fd, void* x, size_t n );
int fork();
int exit1();
int myStrCmp ( char *s1,  char *s2,int length);
void printm(char *str,...);


int _close(int file);
int _fstat(int file, struct stat *st);
int _isatty(int file);
int _lseek(int file, int ptr, int dir);
int _open(const char *name, int flags, int mode);
int _read(int file, char *ptr, int len);
caddr_t _sbrk(int incr);
int _write( int fd, void* x, size_t n );

#endif