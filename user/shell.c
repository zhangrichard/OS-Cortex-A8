#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include  <string.h>

#include "../device/PL011.h"
// combine task 3
// future computation
int fd;
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
      case '\r':
        if (start  != -1) {
            args[count] = &buffer[start]; /* set up pointer */
            count++;
          }
        buffer[i] = '\0'; /* add null character to make a C string */
        start = -1;
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
  buffer_t dir;
  char * start = "enter";
  char * output = "output is : \n";
  char * p0 = "p0 thread\n";

  while(1){
  printf("%s\n","/Downloads/question$" );
  int length;  
  length= _reads(1,cache,100);

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
  }// 1 represent write 0 read
  if (strcmp(args[0],"create")== 0){// create("file.txt",1)
    file_create((args[1]));
  }
  
  if (strcmp(args[0],"open")== 0){
    fd = file_open(args[1],0);
  }
   if (strcmp(args[0],"read")== 0){
    char  temp[100];
    file_read(fd,temp,16);
    // printf("read value is %s\n",temp );
  }
   if (strcmp(args[0],"write")== 0){
    file_writes(10,args[1],16);
  }
   if (strcmp(args[0],"close")== 0){
    file_close(fd);
  }
  if(strcmp (args[0],"pwd")==0){// 01 01230000 F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF
    // printf("shell\n" );
    pwd(dir);
    printf("%s\n",dir);
  }
  if(strcmp (args[0],"touch")==0){// 01 01230000 F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF
    // printf("shell\n" );
    touch(args[1]);
    // printf("%s\n",dir);
  }
   if(strcmp (args[0],"ls")==0){// 01 01230000 F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF
    // printf("shell\n" );
    ls();
    // printf("%s\n",dir);
  }
  if(strcmp (args[0],"mkdir")==0){// 01 01230000 F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF
    // printf("shell\n" );
    mkdirr(args[1]);
    // printf("%s\n",dir);
  }
    if(strcmp (args[0],"cd")==0){// 01 01230000 F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF
    // printf("shell\n" );
    cd(args[1]);
    // printf("%s\n",dir);
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