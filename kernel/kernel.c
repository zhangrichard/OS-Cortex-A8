  #include "kernel.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include "queue.h"
#include "string.h"

/* Since we *know* there will be 2 processes, stemming from the 2 user 
 * programs, we can 
 * 
 * - allocate a fixed-size process table (of PCBs), and use a pointer
 *   to keep track of which entry is currently executing, and
 * - employ a fixed-case of round-robin scheduling: no more processes
 *   can be created, and neither is able to complete.
 */



pcb_t pcb[ PCB_SIZE ], *current = NULL;
static int numberOfProcess =3;
heap_t h[1];
heap_t *m;
pid_t nextpid =3;

// base on the priority to schedule process
void priorityBaseScheduler( ctx_t* ctx ) {
  // find largest priority   store index and coresond priority
  
  //pop heap to get the index
  int index = pop(h);
  memcpy(&current->ctx, ctx, sizeof(ctx_t));
  memcpy(ctx,&pcb[index].ctx, sizeof(ctx_t));
  current = &pcb[index];

}
void scheduler( ctx_t* ctx ) {
  if      ( current ==   &pcb[numberOfProcess-1]) {
      memcpy( &current->ctx, ctx, sizeof( ctx_t ) );
      memcpy( ctx, &pcb[ 0 ].ctx, sizeof( ctx_t ) );
      current =  &pcb[ 0 ];
    }

  else{
    memcpy( &current->ctx, ctx, sizeof( ctx_t ) );
    memcpy( ctx, &(current+1)->ctx, sizeof( ctx_t ) );
    current =  (current+1);
  }
  // else if ( current == &pcb[ 1 ] ) {
  //   memcpy( &pcb[ 1 ].ctx, ctx, sizeof( ctx_t ) );
  //   memcpy( ctx, &pcb[ 2].ctx, sizeof( ctx_t ) );
  //   current = &pcb[ 2 ];
  // }
  // else if ( current == &pcb[ 2 ] ) {
  //   memcpy( &pcb[ 2 ].ctx, ctx, sizeof( ctx_t ) );
  //   memcpy( ctx, &pcb[ 0 ].ctx, sizeof( ctx_t ) );
  //   current = &pcb[ 0 ];
  // }
}

void kernel_handler_rst( ctx_t* ctx              ) { 
  /* Initialise PCBs representing processes stemming from execution of
   * the two user programs.  Note in each case that
   *    
   * - the CPSR value of 0x50 means the processor is switched into USR 
   *   mode, with IRQ interrupts enabled, and
   * - the PC and SP values matche the entry point and top of stack. 
   */

  write(0,"initialising\n",13);
  UART0->IMSC           |= 0x00000010; // enable UART    (Rx) interrupt
  UART0->CR              = 0x00000301; // enable UART (Tx+Rx)
  TIMER0->Timer1Load     = 0x00100000; // select period = 2^20 ticks ~= 1 sec
  TIMER0->Timer1Ctrl     = 0x00000002; // select 32-bit   timer
  TIMER0->Timer1Ctrl    |= 0x00000040; // select periodic timer
  TIMER0->Timer1Ctrl    |= 0x00000020; // enable          timer interrupt
  TIMER0->Timer1Ctrl    |= 0x00000080; // enable          timer

  GICC0->PMR             = 0x000000F0; // unmask all            interrupts
  GICD0->ISENABLER[ 1 ] |= 0x00000010; // enable timer          interrupt
  GICC0->CTLR            = 0x00000001; // enable GIC interface
  GICD0->CTLR            = 0x00000001; // enable GIC distributor
  // PL011_puts( UART0 , "Scheduler: initialising\n", 24);

  // predefine scheduler priority
  memset( &pcb[ 0 ], 0, sizeof( pcb_t ) );
  pcb[ 0 ].pid      = 0;
  pcb[ 0 ].ctx.cpsr = 0x50;
  pcb[ 0 ].ctx.pc   = ( uint32_t )( entry_P0 );
  pcb[ 0 ].ctx.sp   = ( uint32_t )(  &tos_user );
  pcb[ 0 ].ctx.priority = 10;
  memset( &pcb[ 1 ], 0, sizeof( pcb_t ) );
  pcb[ 1 ].pid      = 1;
  pcb[ 1 ].ctx.cpsr = 0x50;
  pcb[ 1 ].ctx.pc   = ( uint32_t )( entry_P1 );
  pcb[ 1 ].ctx.sp   = ( uint32_t )(  &(tos_user)+1000 );
  pcb[ 1 ].ctx.priority = 5;
  memset( &pcb[ 2 ], 0, sizeof( pcb_t ) );
  pcb[ 2 ].pid      = 2;
  pcb[ 2 ].ctx.cpsr = 0x50;
  pcb[ 2 ].ctx.pc   = ( uint32_t )( entry_P2 );
  pcb[ 2 ].ctx.sp   = ( uint32_t )(  &(tos_user)+2000  );
  pcb[ 2 ].ctx.priority = 2;
  /* Once the PCBs are initialised, we (arbitrarily) select one to be
   * restored (i.e., executed) when the function then returns.
   */
  // PL011_puts( UART0 , "Scheduler: switching to process 0\n", 34);

  // h  = (heap_t*) calloc(1, sizeof (heap_t));
  // m = (heap_t *) malloc(sizeof(heap_t));
  // m->len =0;
  // free(m);
  h->len=0;

  for (int index = 0;index<numberOfProcess;index++){
    push(h,pcb[index].ctx.priority,index);
  }
  int index = pop(h);
  current = &pcb[ index ]; memcpy( ctx, &current->ctx, sizeof( ctx_t ) );
  irq_enable();

  return;
}
  
void kernel_handler_svc( ctx_t* ctx, uint32_t id ) { 
  /* Based on the identified encoded as an immediate operand in the
   * instruction, 
   *
   * - read  the arguments from preserved usr mode registers,
   * - perform whatever is appropriate for this system call,
   * - write any return value back to preserved usr mode registers.
   */

  switch( id ) {
    case 0x00 : { // read(fd,x,n)
      // scheduler( ctx );
      // break;
      uint8_t cache[500];
      int   fd = ( int   )( ctx->gpr[ 0 ] ); 
      char*  x = ( char* )( ctx->gpr[ 1 ] );
      int    n = ( int   )( ctx->gpr[ 2 ] );

      int i =0; 
      while(1){
        cache[i] = PL011_getc( UART0 );
        PL011_putc( UART0,cache[i]);
        if (cache[i]=='\r'||i>n){
          PL011_putc( UART0,'\n');
          i++;
          cache[i] = '\n';
          break;
        }
        i++;
      }      
      for (int j = 0;j<=i;j++){
        x[j] = cache[j];
      }
      // add \0 is the end;
      x[i+1] = '\0';
      ctx->gpr[0] = i+2;
      break;
    } 
    case 0x01 : { // write( fd, x, n )
      int   fd = ( int   )( ctx->gpr[ 0 ] );  
      char*  x = ( char* )( ctx->gpr[ 1 ] );  
      int    n = ( int   )( ctx->gpr[ 2 ] ); 

      for( int i = 0; i < n; i++ ) {
        PL011_putc( UART0, *(x+i) );
        if ( *(x+i) == '\n'){
          break;
        }
      }
      ctx->gpr[ 0 ] = n;
      break;
    }
    case 0x02:{ //fork(pidNum)  can only fork process one two three
      //intinital new process in process block
      int   pidNum = ( int   )( ctx->gpr[ 0 ] ); 
      // create new process blockt
      int currentProcess = numberOfProcess;
      memset( &pcb[ currentProcess ], 0, sizeof( pcb_t ) );
      // parent =kid pid
      pcb[pidNum-1].pid =   
      pcb[ currentProcess ].pid      = nextpid++;       
      
      // copy parent to child
      memcpy( &pcb[ currentProcess ].ctx, &pcb[pidNum].ctx, sizeof( ctx_t ) );
      pcb[ currentProcess ].ctx.sp   = ( uint32_t )(  &(tos_user)+1000*currentProcess  );
      
      ctx->gpr[0]= pcb[ numberOfProcess ].pid;
      numberOfProcess++;
      break;
    }
    case 0x03:{ //exit(pidNum)
      // empty the pcb content
      // free(current);
      int   pidNum = ( int   )( ctx->gpr[ 0 ] ); 
      memset( current, 0, sizeof( pcb_t ) );
      // current == &pcb[ 1 ];
      memset( &current->ctx,0, sizeof(ctx_t));
      pcb_t *pointer = &pcb[ pidNum ];
      // pcb_t temp;
      // fill the gap in pcb block
      while(pointer !=&pcb[numberOfProcess-1]){
        memcpy(pointer,(pointer+1),sizeof(pcb_t));
        pointer++;
      }
      
      scheduler(ctx);
      numberOfProcess--;
      // *current->pid = 0;
      // *current->ctx.cpsr = 0;
      // *current->ctx.cpsr = 0;
      // *current->ctx.cpsr = 0;
      // pcb[ 2 ].ctx.pc   = 0;
      // pcb[ 2 ].ctx.sp   = 0;
      // if      ( current == &pcb[ 0 ] )
      // pcb[ 2 ].pid      = 0;
      // pcb[ 2 ].ctx.cpsr = 0;
      // pcb[ 2 ].ctx.pc   = 0;
      // pcb[ 2 ].ctx.sp   = 0;
      // priorityBaseScheduler(ctx);
      break;
    }
    default   : { // unknown
      break;
    }
  }

  return;
}
void kernel_handler_irq(ctx_t *ctx) {
  // Step 2: read  the interrupt identifier so we know the source.

  uint32_t id = GICC0->IAR;

  // Step 4: handle the interrupt, then clear (or reset) the source.


  if( id == GIC_SOURCE_TIMER0 ) {
  scheduler(ctx);  
  TIMER0->Timer1IntClr = 0x01;
  }

  // Step 5: write the interrupt identifier to signal we're done.

  GICC0->EOIR = id;
}
