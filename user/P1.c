#include "P1.h"
#include <stdio.h>
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
  while( 1 ) {
    // compute the gcd between pairs of x and y for 2^4 < x, y < 2^8
        flag[1] = true;
        turn = 0;
         while (flag[0] && turn == 0)
         {
             // busy wait
         }
         // critical section
         int result = withdrawl(10);
         
        printf("withdrawl 10 is %d\n", result);
         
         // end of critical section
         flag[1] = false;
    for( uint32_t x = ( 1 << 4 ); x < ( 1 << 8 ); x++ ) {
      for( uint32_t y = ( 1 << 4 ); y < ( 1 << 8 ); y++ ) {
        uint32_t r = gcd( x, y );  // 
        printf( "gcd( %d, %d ) = %d\n", x, y, r );
        for( int i = 0; i < 0x05000000; i++ ) {
          asm volatile( "nop" );
        }
      }
      // wait little bit longer
      
    }
    
  }

  return;
}
void (*entry_P1)() = &P1;