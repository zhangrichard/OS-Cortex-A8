#ifndef __FILE_H
#define __FILE_H

#include <stddef.h>
#include <stdint.h>


void file_close( int fd );
int file_create(void* x) ;
int file_open(  void* x, size_t n );
// int file_unlink( int fd, void* x, size_t n );
int file_read( int fd, void* x, size_t n );
int file_writes( int fd, void* x, size_t n );

void pwd( void* x );
void touch( void* x );
void mkdirr( void* x );
void ls();
void cd ( void* x );
#endif