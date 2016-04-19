#ifndef __FILE_H
#define __FILE_H

#include <stddef.h>
#include <stdint.h>


int file_close( void* x );
int file_create( int fd, void* x, size_t n ) ;
int file_open( int fd, void* x, size_t n );
int file_unlink( int fd, void* x, size_t n );
int file_read( int fd, void* x, size_t n );
int file_writes( int fd, void* x, size_t n );
#endif