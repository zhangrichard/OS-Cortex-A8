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
  char   buf[BUF_SIZE];
  char * p1 = "p1 thread\n";
  // for (int i = 0;i<10;i++){
  //    write(1,p1,10); 
  // }
  // write(1,"exitingP1\n",10);
  // exit1();

  while( 1 ) {
  //   // compute the gcd between pairs of x and y for 2^4 < x, y < 2^8
    for (int i =0;i<10;i++){
      write(0,"staringP1\n",10);
    }
    
    for( int i = 0; i < 0x20000000; i++ ) {
        asm volatile( "nop" );
      } 
    
    // for( uint32_t x = ( 1 << 4 ); x < ( 1 << 4); x++ ) {
    //   for( uint32_t y = ( 1 << 4 ); y < ( 1 << 4 ); y++ ) {
    //     uint32_t r = gcd( x, y );  
    //     //printf( "gcd( %d, %d ) = %d\n", x, y, r );
    //     sprintf(buf, "gcd( %d, %d ) = %d\n", x, y, r );
    //     write(1, buf, strlen(buf));
    //   }
    // }
    // exit1();
    // write(1,"staringP1\n",10);
    //   for (int i =0;i<10;i++){
    //     write(1,i,10);
    //   }

      // write(1,"staringP1\n",10);
      // for( int i = 0; i < 0x20000000; i++ ) {
      //   asm volatile( "nop" );
      // }
      // exit1();
    //   for (int i = 0;i<10;i++){
    //  write(1,p0,10);
    // }
    
    
    
  }

  return;
}
void(*entry_P1)() =&P1;