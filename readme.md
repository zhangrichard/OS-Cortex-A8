# OS-Cortex-A8

Adapted from the COMS20001 unit at the University of Bristol.


## Features

### Current

* Communication over UART
* Basic interrupt handling
* Pre-emptive multi-tasking
* Dynamic creation and destruction of process with `fork()` and `exit()`
* An interactive shell.
* A scheduler pre-defined priority processes
* Basic shell utilities: `cd`, `ls`, `mkdir`, `pwd`, `touch`, `write`
* Asynchronous message-passing IPC


## Supported platforms

* RealView Platform Cortex-A8 (tested in QEMU)

## Build and Run

* `make build`
* `make launch-qemu`
* `make launch-gdb`




## Available system calls

* `void exit(int pid)` - terminate the current process
* `void fork(int pid)` - duplicate the giving pid process
* `int32_t _read(int32_t fd, char* buf, size_t nbytes)` - read some bytes from a file
* `size_t _write(int32_t fd, char* buf, size_t nbytes)` - write some bytes to a file
* ` _open(char* pathname, int32_t flags)` - open a file and get its file descriptor
* `int32_t _close(filedesc_t fd)` - close a file by its file descriptor
* `int32_t _chdir(char* path)` - change the current working directory
* `int32_t _mkdir(char* path)` - create a new directory



