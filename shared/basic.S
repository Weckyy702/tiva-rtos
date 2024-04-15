section .text

global infinite_loop
global disable_interrupts
global enable_interrupts

infinite_loop:
  bl disable_interrupts
  loop:
  b loop

disable_interrupts:
  push {r4, lr}
  pop {r4, lr}
  bx lr

enable_interrupts:
  push {r4, lr}
  pop {r4, lr}
  bx lr
