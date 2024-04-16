#include "Register.h"
#include "ints.h"
#include <stddef.h>

typedef void (*VectorFunction)(void);

extern "C" {
[[noreturn]] void reset_handler(void);
void nmi_handler(void);
void hard_fault_handler(void);
void mem_manage_handler(void);
void bus_fault_handler(void);
void usage_fault_handler(void);
void sv_call_handler(void);
void pend_sv_handler(void);
void sys_tick_handler(void);
}

struct [[gnu::packed]] VectorTable {
  u32 *initial_sp;
  VectorFunction reset;
  VectorFunction nmi;
  VectorFunction hard_fault;
  VectorFunction memory_management_fault;
  VectorFunction bus_fault;
  VectorFunction usage_fault;
  u32 __padding1[4] = {0};
  VectorFunction sv_call;
  u32 __padding2[2] = {0};
  VectorFunction pend_sv;
  VectorFunction systick;
  VectorFunction irqs[139] = {0};
};

static_assert(sizeof(VectorTable) == 0x026C);

static_assert(offsetof(VectorTable, initial_sp) == 0);
static_assert(offsetof(VectorTable, sv_call) == 0x002C);
static_assert(offsetof(VectorTable, pend_sv) == 0x0038);

extern u32 _stack;

extern "C" {
void blocking_handler(void) {
  for (;;)
    ;
}

void null_handler(void) {}

#define PIN1 0x02
#define PIN2 0x04
#define PIN3 0x08

#define LED_PINS (PIN1 | PIN2 | PIN3)

#define PORTF_GPIODEN *((volatile u32 *)0x4002'551C)
#define PORTF_GPIODIR *((volatile u32 *)0x4002'5400)
#define PORTF_GPIODATA *((volatile u32 *)(0x4002'5000 + LED_PINS))

[[gnu::weak]] [[noreturn]] void reset_handler(void) {
  Register rcgc{0x400F'E608_u32};

  u32 state = LED_PINS;

  *rcgc |= 0x20;
  PORTF_GPIODEN |= LED_PINS;
  PORTF_GPIODIR |= LED_PINS;

  for (;;) {
    for (u32 i = 5'000'000; i != 0; --i) {
    }

    PORTF_GPIODATA &= ~LED_PINS;
    PORTF_GPIODATA |= state;

    state ^= LED_PINS;
  }
}
}

[[gnu::section(".vectors")]] VectorTable vectors = {
    .initial_sp = &_stack,
    .reset = reset_handler,
    .nmi = nmi_handler,
    .hard_fault = hard_fault_handler,
    .memory_management_fault = mem_manage_handler,
    .bus_fault = bus_fault_handler,
    .usage_fault = usage_fault_handler,
    .sv_call = sv_call_handler,
    .pend_sv = pend_sv_handler,
    .systick = sys_tick_handler,
    .irqs = {
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler, blocking_handler,
        blocking_handler, blocking_handler, blocking_handler,
    }};

#pragma weak sv_call_handler = null_handler
#pragma weak pend_sv_handler = null_handler
#pragma weak sys_tick_handler = null_handler

#pragma weak nmi_handler = null_handler
#pragma weak hard_fault_handler = blocking_handler
#pragma weak bus_fault_handler = blocking_handler
#pragma weak usage_fault_handler = blocking_handler
#pragma weak mem_manage_handler = blocking_handler
