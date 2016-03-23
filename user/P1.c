#include "P1.h"

uint32_t gcd( uint32_t x, uint32_t y ) {
  if     ( x == y ) {
    return x;
  }
  else if( x >  y ) {
    return gcd( x - y, y );
  }
  else if( x <  y ) {
    return gcd( x, y - x );
  }
}
// combine task3
// void P1() {
//   char* x = "hello world, I'm P1\n";

//   while( 1 ) {
//     write( 0, x, 20 ); //yield();
//   }
// }

void P1() {
  while( 1 ) {
    // compute the gcd between pairs of x and y for 2^4 < x, y < 2^8

    for( uint32_t x = ( 1 << 4 ); x < ( 1 << 8 ); x++ ) {
      for( uint32_t y = ( 1 << 4 ); y < ( 1 << 8 ); y++ ) {
        uint32_t r = gcd( x, y );  //printf( "gcd( %d, %d ) = %d\n", x, y, r );
   
      }
    }
    
  }

  return;
}
void(*entry_P1)() =&P1;