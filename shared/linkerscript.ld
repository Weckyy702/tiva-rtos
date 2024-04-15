EXTERN(vector_table)
ENTRY(reset_handler)

MEMORY {
    rom (rx) : ORIGIN = 0,          LENGTH = 256K
    ram (rw) : ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS {
  .text :{
    *(.vectors)
    *(.text*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
  } >rom
}

PROVIDE(_stack = ORIGIN(ram) + LENGTH(ram));
