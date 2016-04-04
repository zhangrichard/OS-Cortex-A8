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
  

  while( 1 ) {
    // test whether each x for 2^8 < x < 2^24 is prime or not

    for( uint32_t x = ( 1 << 8 ); x < ( 1 << 24 ); x++ ) {
      int r = is_prime( x ); //printf( "is_prime( %d ) = %d\n", x, r );
      sprintf(buf, "is_prime( %d ) = %d\n", x, r );
      write(1, buf, strlen(buf));
    }
    
  }

  return;
}
void (*entry_P0)() = &P0;