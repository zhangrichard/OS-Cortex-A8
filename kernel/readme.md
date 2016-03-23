readme.md
|term| definition|
|----|------|
|UART0|0x10009000 
|ctx|sp  passing by irq function
|spsr |saved program status register    invokes the
processor mode switch
|pid_t| PID
|pcb_t|PCB


### things to do 
create empty multi-task kernel
combine lab3 interrupt  
***timer  interrupt kernel by period 


link file to have 3 process


1.create context switch 
2. kernel yield
3.allocation PCBs (fixed-size process table) pointer to keep track process running

4.stack space for process
5.scheduling algorism for schedule process

###  svc struct 
 5-instruction prologue
  5-instruction  epilogue


low to high
       inc F(svc)



#### svc file structure
id switch 



#### rst file structure