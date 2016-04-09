#include "P0.h"

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

void P0() {
  char   buf[BUF_SIZE];
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
  char cache[500];
  char * start = "enter \n";
  char * output = "output is : \n";
 
  while( 1 ) {
    // test whether each x for 2^8 < x < 2^24 is prime or not

    // for( uint32_t x = ( 1 << 8 ); x < ( 1 << 24 ); x++ ) {
    //   int r = is_prime( x ); //printf( "is_prime( %d ) = %d\n", x, r );
    //   sprintf(buf, "is_prime( %d ) = %d\n", x, r );
    //   write(1, buf, strlen(buf));
    // }
  
  
  int length;  
  write(1,start,7);
  length= read(0,cache,100);
  char * string = &cache[0];
  if (myStrCmp(string,"fork\r\n",length) == 0){
    write(0,"forking\n",8);
    fork();
  }
  if (myStrCmp(string,"fork\r\n",length) == 0){
    write(0,"exiting\n",8);
    exit();
  }
  write(0,output,13);
  write(0,cache,length);
  // write(1,"\n",1);

    
  }

  return;
}
void (*entry_P0)() = &P0;