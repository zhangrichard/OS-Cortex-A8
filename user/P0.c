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

void P0() {
  // char   buf[BUF_SIZE]
 
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
  // args_t args;
  // buffer_t cache;
  // char * start = "enter \n";
  // char * output = "output is : \n";
  // char * p0 = "p0 thread\n";
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

  
  while(1){
     // flag[0] = true;
     // turn = 0;
     // while (flag[1]==true && turn == 0)
     // {
     //     // busy wait
     // }
     // // critical section
     // int result = withdrawl(20);
     // printf("withdrawl 20 is %d\n", result);
     
     // // end of critical section
     // flag[0] = false; 


      while(registerInterest())
      {
        // busy wait
      }
      // enter critical section
      int acountMoney = load();
         printf("p0 read data %d\n", acountMoney);
         //conflict
         if (withdrawl(20,&acountMoney))
          {
            printf("take 20 from account \n");
          }

         
         store(acountMoney);
         printf("p0 after taking %d\n", acountMoney);

      deRegisterInterest();
    // for( uint32_t x = ( 1 << 8 ); x < ( 1 << 24 ); x++ ) {
    //   int r = is_prime( x ); //
    //   printf( "is_prime( %d ) = %d\n", x, r );
    //   // sprintf(buf, "is_prime( %d ) = %d\n", x, r );
    //   // write(1, buf, strlen(buf));
      for( int i = 0; i < 0x05000000; i++ ) {
        asm volatile( "nop" );
      } 
    // }
  
  }

 
  // exit1();
  // write(1,p0,10);
    
  // }

  return;
}
void (*entry_P0)() = &P0;