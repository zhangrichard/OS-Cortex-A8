  #include "kernel.h"
#include <stdio.h>
#include <stdlib.h>
// #include "queue.h"
#include "string.h"
#include "../device/disk.h"
#include <sys/unistd.h>
// #include "../device/disk.c"

/* Since we *know* there will be 2 processes, stemming from the 2 user 
 * programs, we can 
 * 
 * - allocate a fixed-size process table (of PCBs), and use a pointer
 *   to keep track of which entry is currently executing, and
 * - employ a fixed-case of round-robin scheduling: no more processes
 *   can be created, and neither is able to complete.
 */

#define DEBUG 1

pcb_t pcb[ PCB_SIZE ], *current = NULL;
fdt_t fdt;
static int numberOfProcess =4;
heap_t *h = NULL;
// heap_t *m;
pid_t nextpid =4;
bool InterestFlag[2] =  {false,false};
int shareInt =100;
int turn;
int signalflag = 0;


void priorityBaseScheduler( ctx_t* ctx ) {
  // find largest priority   store index and coresond priority
  
  //pop heap to get the index
  int pid = pop(h);
  // printf("at position ready queue%d",(indexPop%h->len));

  pcb_t *pointer = current;
  memcpy(&pointer->ctx, ctx, sizeof(ctx_t));
  memcpy(ctx,&pcb[pid].ctx, sizeof(ctx_t));

  current = &pcb[pid];

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

}

void initialising_kernel( ctx_t* ctx){
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
  pcb[ 0 ].priority = 1;
  memset( &pcb[ 1 ], 0, sizeof( pcb_t ) );
  pcb[ 1 ].pid      = 1;
  pcb[ 1 ].ctx.cpsr = 0x50;
  pcb[ 1 ].ctx.pc   = ( uint32_t )( entry_P1 );
  pcb[ 1 ].ctx.sp   = ( uint32_t )(  &(tos_user)+1000 );
  pcb[ 1 ].priority = 5;
  
  memset( &pcb[ 2 ], 0, sizeof( pcb_t ) );
  pcb[ 2 ].pid      = 2;
  pcb[ 2 ].ctx.cpsr = 0x50;
  pcb[ 2 ].ctx.pc   = ( uint32_t )( entry_P2 );
  pcb[ 2 ].ctx.sp   = ( uint32_t )(  &(tos_user)+2000  );
  pcb[ 2 ].priority = 2;
  
  memset( &pcb[ 3 ], 0, sizeof( pcb_t ) );
  pcb[ 3 ].pid      = 3;
  pcb[ 3 ].ctx.cpsr = 0x50;
  pcb[ 3 ].ctx.pc   = ( uint32_t )( entry_shell);
  pcb[ 3 ].ctx.sp   = ( uint32_t )(  &(tos_user)+3000 );
  pcb[ 3 ].priority = 0;
  /* Once the PCBs are initialised, we (arbitrarily) select one to be
   * restored (i.e., executed) when the function then returns.
   */
  // PL011_puts( UART0 , "Scheduler: switching to process 0\n", 34);
  h= calloc(1, sizeof (heap_t));

  // initialize ready queue
  queue_init(h);
  for (int index = 0;index<numberOfProcess;index++){
    push(h,pcb[index].priority,index);
  }

// initalize file system
  initialTable(&fdt);

  current = &pcb[3]; memcpy( ctx, &current->ctx, sizeof( ctx_t ) );

  irq_enable();
}
void kernel_handler_rst( ctx_t* ctx              ) { 
  /* Initialise PCBs representing processes stemming from execution of
   * the two user programs.  Note in each case that
   *    
   * - the CPSR value of 0x50 means the processor is switched into USR 
   *   mode, with IRQ interrupts enabled, and
   * - the PC and SP values matche the entry point and top of stack. 
   */
   printf("%s\n","initialising" );
   initialising_kernel( ctx);

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
      // create new process block and to end of block queue
      int currentProcess = numberOfProcess;
      //unique pid  
      pcb[ currentProcess ].pid      = nextpid++;       
      pcb[ currentProcess ].ppid      = pidNum;
      pcb[ currentProcess ].priority      = pcb[pidNum].priority;
      // copy parent to child
      if(DEBUG){
        printf("kernel pidNum number%d\n", pidNum);

        for (int i =0;i<numberOfProcess;i++){
          printf("kernel pidNum number%d\n", i);
          printf("kernel pidNum priority%d\n", pcb[i].priority);

        }
      }
      memcpy( &pcb[ currentProcess ].ctx, &pcb[pidNum].ctx, sizeof( ctx_t ) );

      pcb[ currentProcess ].ctx.sp   = ( uint32_t )(  &(tos_user)+1000*currentProcess  );
      // push queue
      push(h,pcb[currentProcess].priority,currentProcess);
      
      //return child pid
      ctx->gpr[0]= pcb[ currentProcess ].pid;
      numberOfProcess++;
      break;
    }
    case 0x03:{ //exit(pidNum)
   
      int   pidNum = ( int   )( ctx->gpr[ 0 ] );    
  
      exitQueueByPid(h,pidNum);
   
      ctx->gpr[0]= pidNum;
      break;
    }

    case 0x04:{ //load()

      ctx->gpr[0]= shareInt;
      break;
    }
    case 0x05:{ //store(data)
   
      int   data = ( int   )( ctx->gpr[ 0 ] );   
      shareInt = data;
  
      break;
    }
    case 0x06:{ //registerinterest()
        // bool result ;
        // result = (InterestFlag == false) ? false : true ;
        
        int process =current->pid; 
        if (turn != process) {  
          ctx->gpr[0] = false;
          break;
        } 
        // printf("%d\n", process);   
        InterestFlag[process] = true;
        turn =(process+1)%2;
        // printf("bool %d\n",InterestFlag[(process+1)%2] == true);
        ctx->gpr[0]= InterestFlag[(process+1)%2]&& turn == (process+1)%2;
      break;
    }
    case 0x07:{ //deRegisterinterest
      
      InterestFlag[current->pid] = false;      
      // ctx->gpr[0]= pidNum;
      break;
    }

    case 0x08:{ //int file_create( int fd, void* x, size_t n ) 8196

      int   fd = ( int   )( ctx->gpr[ 0 ] );  
      char*  x = ( char* )( ctx->gpr[ 1 ] );  
      int    mode = ( int   )( ctx->gpr[ 2 ] ); 
       if (strlen(x)<16){
        for (int i = strlen(x);i<16;i++)
        x[i] = 0 ;
      } 
      int n= 16;
      printf("data %s\n", x);
      printf("address %d\n",fd );
      printf("size %d\n", n);
     
      // disk_get_block_num();
      PL011_puth( UART0, 0x01 );        // write command
      PL011_putc( UART0, ' '  );        // write separator
       addr_puth( UART0, fd    );        // write address
      PL011_putc( UART0, ' '  );        // write separator
       data_puth( UART0, x, n );        // write data
      PL011_putc( UART0, '\n' );
      disk_wr(fd,x,n);
      
      addFile(&fdt,x,mode);
      // InterestFlag[current->pid] = false;      
      ctx->gpr[0]= 0;
      break;
    }
   
    case 0x9:{//open file

      char *x = ( char *  )( ctx->gpr[ 0 ] );
      int   rwBit = ( int   )( ctx->gpr[1 ] );
      int fd=0; //default
      for (int i = 0;i<fdt.size;i++){
        if(strcmp(x,fdt.file[i].filename)){
          fd = fdt.file[i].fd;
          fdt.file[i].flags = rwBit;
        }
      }
      ctx->gpr[0]= fd;
    }
    case 0x10:{ // read file
      int   fd = ( int   )( ctx->gpr[ 0 ] );  
      char*  x = ( char* )( ctx->gpr[ 1 ] );  
      int    n = ( int   )( ctx->gpr[ 2 ] );
      printf("into syscall %s\n", x);
      ctx->gpr[0]= 0;
      break;
    }

     case 0x11:{ //file_open file
      int   fd = ( int   )( ctx->gpr[ 0 ] );  
      char*  x = ( char* )( ctx->gpr[ 1 ] );  
      int    mode = ( int   )( ctx->gpr[ 2 ] ); 
      // disk_get_block_num();
      PL011_puth( UART0, 0x01 );        // write command
      PL011_putc( UART0, ' '  );        // write separator
       addr_puth( UART0, fd    );        // write address
      PL011_putc( UART0, ' '  );        // write separator
       data_puth( UART0, x, 16 );        // write data
      PL011_putc( UART0, '\n' );
      disk_wr(fd,x,16);
     // increase siz
      printf("return fd %d\n", fd);
      ctx->gpr[0]= fd;
      break;
    }

    case 0x13:{ // close(fd)
      char*  filename = ( char* )( ctx->gpr[ 0 ] ); 
      int index = lookUpIndex(&fdt,filename);
      freeBlock(&fdt.file[index]);
      printf("into syscall %s\n", filename);
      ctx->gpr[0]= 0;
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
    priorityBaseScheduler(ctx);  
    TIMER0->Timer1IntClr = 0x01;
  }
  // Step 5: write the interrupt identifier to signal we're done.
  GICC0->EOIR = id;

}
