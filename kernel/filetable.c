#include "filetable.h"
#include<stdio.h>
#include "string.h"
void freeBlock (file_t *file){
    file->fd = 0;
    file->filename = NULL;
    file->flags = 0;
    file->rwPointer = 0;
}
void initialTable(fdt_t *fdt){
  fdt->size = 1;
  fdt->file[0].fd = 0;
  fdt->file[0].filename = "stdin";
  fdt->file[0].flags = O_R;
  fdt->file[0].rwPointer =0;
}

void addFile (fdt_t *fdt,char * filename,int mode){
	 int currentFile = fdt->size;
	  fdt->file[currentFile].filename = filename;
      fdt->file[currentFile].fd = fdt->size;
      fdt->file[currentFile].rwPointer = 0;
      fdt->file[currentFile].rwPointer = mode;
      fdt->size++;
}
int lookUpIndex(fdt_t *fdt,char * filename){
	int index;
	for (int i =0;i<fdt->size;i++){
		if(strcmp(fdt->file[i].filename,filename)){
			index = i;
		}
	}
	return index;
}