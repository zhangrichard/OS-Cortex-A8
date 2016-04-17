SECTIONS {
  /* assign address (per  QEMU)  */
  .       =     0x70010000; 
  /* place text segment(s)       */
  .text : { kernel/interrupt.o(.text) *(.text .rodata) } 
  /* place data segment(s)       */        
  .data : {                           *(.data        ) } 
  /* place bss  segment(s)       */        
  .bss  : {                           *(.bss         ) }
  /* align  address (per AAPCS)  */
  .       = ALIGN(8); 
  /* allocate stack for irq mode */
  .       = . + 0x00001000;  
  tos_irq = .;
  /* allocate stack for svc mode */
  .       = . + 0x00001000;        
  tos_svc = .;
   
   heap_low = .;
   . += 0x10000;
   heap_top = .;

  /* allocate stack for user process   8 users   */

  /* allocate stack for P0       */
  .       = . + 0x10000;  
  tos_user  = .;

  PROVIDE (end = .);
}
