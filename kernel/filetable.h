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
void addFile (fdt_t *fdt,char * filename,int mode);
void initialTable(fdt_t *fdt);
void freeBlock (file_t *file);
int lookUpIndex(fdt_t *fdt,char * filename);
#endif