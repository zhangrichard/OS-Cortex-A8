#ifndef __LIBC_H
#define __LIBC_H

#include <stddef.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdbool.h>




int file_create( int fd, void* x, size_t n ) ;

// void init_buffer_share(buffer_share *bs);
int withdrawl(int amount,int *acountMoney);
// bool flag[2];
// int turn;
// typedef struct {
// 	int accountNumber;
// 	int money;
// 	// https://en.wikipedia.org/wiki/Peterson%27s_algorithm
// }buffer_share;
// cooperatively yield control of processor, i.e., invoke the scheduler
void yield();

// write n bytes from x to the file descriptor fd
int load();
int store(int data);
bool registerInterest();
void deRegisterInterest();
int file_writes( int fd, void* x, size_t n );
int _reads( int fd, void* x, size_t n );

int _read(int file, char *ptr, int len);
int _write( int fd, void* x, size_t n );
int fork();
int exit1();
int myStrCmp ( char *s1,  char *s2,int length);
void std_print(char *str);


int _close(int file);
int _fstat(int file, struct stat *st);
int _isatty(int file);
int _lseek(int file, int ptr, int dir);
int _open(const char *name, int flags, int mode);

caddr_t _sbrk(int incr);

#endif