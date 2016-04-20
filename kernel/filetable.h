#ifndef __FILETABLE_H
#define __FILETABLE_H
#include "constant.h"
typedef struct{
 int fd;
 char * filename;
 int flags;
 int rwPointer;

}file_t;

typedef struct{
	int size;
	file_t file[100];
}fdt_t;

//flat directory
typedef struct 
{
	file_t file[10];
	int size;
	// char * directory;
}directory_t;
void initialDirectory(directory_t *d);
void createFile(directory_t *d,char *filename);
int openFile (directory_t *d, fdt_t *fdt,char *filename,int mode);


void initialTable(fdt_t *fdt);
void closeFile (fdt_t *fdt,int fd );
void addFile (fdt_t *fdt,file_t * filename,int mode);
int lookUpIndex(directory_t *d,char * filename);
#endif