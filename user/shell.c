#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include  <string.h>

#include "../device/PL011.h"
// combine task 3

// static buffer_share bs;

// int turn;



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
  args_t args;
  buffer_t cache;
  char * start = "enter";
  char * output = "output is : \n";
  char * p0 = "p0 thread\n";

//initialise
  // init_buffer_share(&bs);
  // int x = 0;
  
  // turn = 0;

  
  while(1){
  printf("%s\n","starting command shell" );
     int length;  
  printf("%s\n",start );
  length= _reads(1,cache,100);
  char * string = &cache[0];
  // write(0,string,10);
  int count =   tokenize(cache,length,args);
  char str [10];
  // sscanf("input is%s",str);
  printf("%s\n",str );
  if (strcmp(args[0],"fork") == 0){ 
    printf("%s\n","forking" );
    int pid = atoi(args[1]);
    fork(pid);
    // fork();
  }
  if(strcmp (args[0],"folder")==0){// 01 01230000 F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF
    printf("%s\n","write to folder" );
    int address = atoi(args[1]);
    // char *a = itox()
    // if(strlen(args[2]))
    printf("%s\n",args[2]);
    int result = file_writes( address, args[2],  strlen(args[2]) );
  }
  if (strcmp(args[0],"exit") == 0){
    printf("%s\n","exiting ");
    // exit();
    int pid = atoi(args[1]);
    exit1(pid);
  }
  if (strcmp(args[0],"create")== 0){
    file_create(atoi(args[1]),args[2],16);
  }
  if (strcmp(args[0],"close")== 0){
    file_close(args[1]);
  }
  // if (strcmp(args[1]),"read")== 0){
  //   char * read;
  //   file_read(fd,read,4);
  //   printf("file read %s\n",read);
  // }
  // write(0,output,13);
  // write(0,cache,length);
  
  for( int i = 0; i < 0x05000000; i++ ) {
        asm volatile( "nop" );
      } 
  }

 
  // exit1();
  // write(1,p0,10);
    
  // }

  return;
}
void (*entry_shell)() = &shell;