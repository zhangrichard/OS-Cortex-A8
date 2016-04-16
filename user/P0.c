#include "P0.h"
#include <stdlib.h>
#include <stdio.h>
#include  <string.h>
int is_prime( uint32_t x ) {
  if ( !( x & 1 ) || ( x < 2 ) ) {
    return ( x == 2 );
  }

  for( uint32_t d = 3; ( d * d ) <= x ; d += 2 ) {
    if( !( x % d ) ) {
      return 0;
    }
  }

  return 1;
}

// combine task 3
// void P0() {
//   char* x = "hello world, I'm P0\n";

//   while( 1 ) {
//     write( 0, x, 20 ); //yield();
//   }
// }
// future computation
int tokenize(buffer_t buffer, int length, args_t args) {
  int i, count = 0, start = -1;
// https://github.com/alexcoco/alexsh/blob/master/shell.c
  /* examine every character in buffer */
  for (i = 0; i < length; i++) {
    switch(buffer[i]) {
      case ' ':
      case '\t': /* argument separators */
        if (start  != -1) {
          args[count] = &buffer[start]; /* set up pointer */
          count++;
        }

        buffer[i] = '\0'; /* add null character to make a C string */
        start = -1;
        break;
      case '\n': /* should be the final character examined */
        if (start != -1) {
          args[count] = &buffer[start];
          count++;
        }

        buffer[i] = '\0';
        args[count] = NULL; /* no more arguments to this command */
        break;
      default: /* some other character */
        if (start == -1) {
          start = i;
        }
    }
  }
  if (length > 0 && count == 0) {
    args[0] = &buffer[start];
  }

  return count;
  
}
void P0() {
  // char   buf[BUF_SIZE];
  int x = 0;
  // fork();
      // int n =0;
    // while(1){
    //   cache[n] = PL011_getc( UART0 );
    //   if (cache[n]=='\r'){
    //     break;
    //   }
    //   n++;
    // }
    // char *x = cache;
    // for( int i = 0; i < n; i++ ) {
    //   PL011_putc( UART0, *x++ );
    // }
  args_t args;
  buffer_t cache;
  char * start = "enter \n";
  char * output = "output is : \n";
  char * p0 = "p0 thread\n";
  // exit1();
  // while(1){
  //   write(1,"exitingP0\n",10);
  //   for( int i = 0; i < 0x20000000; i++ ) {
  //     asm volatile( "nop" );
  //   }

  // //   for (int i = 0;i<10;i++){
  // //  write(1,p0,10);
  // // }
  
  
  // }
  

  

  // while( 1 ) {
  //   // test whether each x for 2^8 < x < 2^24 is prime or not

  //   // for( uint32_t x = ( 1 << 8 ); x < ( 1 << 24 ); x++ ) {
  //   //   int r = is_prime( x ); //printf( "is_prime( %d ) = %d\n", x, r );
  //   //   sprintf(buf, "is_prime( %d ) = %d\n", x, r );
  //   //   write(1, buf, strlen(buf));
  //   // }
  
  while(1){
  
     int length;  
  write(1,start,7);
  length= read(0,cache,100);
  char * string = &cache[0];
  // write(0,string,10);
  int count =   tokenize(cache,length,args);
  
  if (strcmp(args[0],"fork") == 0){ 
    write(0,"forking\n",8);
    int pid = atoi(args[1]);
    fork(pid);
    // fork();
  }

  if (strcmp(string,"exit\r\n") == 0){
    write(0,"exiting\n",8);
    // exit();
    int pid = atoi(args[1]);
    exit1(pid);
  }
  // write(0,output,13);
  // write(0,cache,length);
  write(0,"\n",1);
  for( int i = 0; i < 0x20000000; i++ ) {
        asm volatile( "nop" );
      } 
  }

 
  // exit1();
  // write(1,p0,10);
    
  // }

  return;
}
void (*entry_P0)() = &P0;