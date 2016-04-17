#include "P1.h"
#include <stdlib.h>
#include <stdio.h>
#include  <string.h>
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


void P1() {
  char   buf[BUF_SIZE];
  char * p1 = "p1 thread\n";

  while( 1 ) {
 
    for( uint32_t x = ( 1 << 4 ); x < ( 1 << 4); x++ ) {
      for( uint32_t y = ( 1 << 4 ); y < ( 1 << 4 ); y++ ) {
        uint32_t r = gcd( x, y );  
        // printm( "gcd( %d, %d ) = %d\n", x, y, r );
        printf( "gcd( %d, %d ) = %d\n", x, y, r );
        
      }
      for( int i = 0; i < 0x20000000; i++ ) {
        asm volatile( "nop" );
      } 
    }
    
  
    
  }

  return;
}
void(*entry_P1)() =&P1;