#include "filetable.h"
#include<stdio.h>
#include "string.h"

void initialDirectory(directory_t *d){
	d->size = 0;
}
void createFile(directory_t *d,char *filename){
	int size = d->size;
	d->file[size].filename = filename;
	d->file[size].fd = size;
	// seperate file by 300
	d->file[size].rwPointer = size*10;
	d->size++;
}


void initialTable(fdt_t *fdt){
  fdt->size = 1;
  fdt->file[0].fd = 0;
  fdt->file[0].filename = "stdin";
  fdt->file[0].flags = O_R;
  fdt->file[0].rwPointer =0;
}


int openFile (directory_t *d, fdt_t *fdt,char*filename,int mode){
	int fd = lookUpIndex(d,filename);
	if(fd = -1){
		return -1;
	}
	else{
		// put file to fdt
		addFile (fdt,&d->file[fd], mode);
	}
	return fd;
}

void closeFile (fdt_t *fdt,int fd){

    fdt->file[fd].fd = 0;
    fdt->file[fd].filename = NULL;
    fdt->file[fd].flags = 0;
    fdt->file[fd].rwPointer = 0;
    fdt->size--;
    printf("%s\n","close file!" );
}



void addFile (fdt_t *fdt,file_t *file,int mode){
	 int currentFile = fdt->size;
	  fdt->file[currentFile].filename = file->filename;
      fdt->file[currentFile].fd = file->fd;
      fdt->file[currentFile].rwPointer = file->rwPointer;
      fdt->file[currentFile].flags = mode;
      fdt->size++;
      printf("%s\n","open file!" );
}
int lookUpIndex(directory_t *d,char * filename){
	int fd = -1;
	for (int i =0;i<d->size;i++){
		if(strcmp(d->file[i].filename,filename)){
			fd = d->file[i].fd;
		}
	}
	if (fd==-1){
		printf("%s\n","cannot find file, please create file first" );
	}
	return fd;
}