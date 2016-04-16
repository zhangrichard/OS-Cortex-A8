#include "P0.h"
#include <stdlib.h>
#include <stdio.h>
#include  <string.h>
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
void shell() {
  // char   buf[BUF_SIZE];
  int x = 0;
  args_t args;
  buffer_t cache;
  char * start = "enter \n";
  char * output = "output is : \n";
  char * p0 = "p0 thread\n";


  
  while(1){
  printf("%s\n","starting command shell" );
     int length;  
  _write(1,start,7);
  length= _read(1,cache,100);
  char * string = &cache[0];
  // write(0,string,10);
  int count =   tokenize(cache,length,args);
  
  if (strcmp(args[0],"fork") == 0){ 
    _write(1,"forking\n",8);
    int pid = atoi(args[1]);
    fork(pid);
    // fork();
  }

  if (strcmp(string,"exit\r\n") == 0){
    _write(1,"exiting\n",8);
    // exit();
    int pid = atoi(args[1]);
    exit1(pid);
  }
  // write(0,output,13);
  // write(0,cache,length);
  _write(1,"\n",1);
  for( int i = 0; i < 0x20000000; i++ ) {
        asm volatile( "nop" );
      } 
  }

 
  // exit1();
  // write(1,p0,10);
    
  // }

  return;
}
void (*entry_shell)() = &shell;