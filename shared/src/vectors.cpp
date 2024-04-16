#include "VectorTable.hpp"
#include "irqs.hpp"

extern u32 _stack;

extern "C" {

void blocking_handler(void) {
  for (;;)
    ;
}

void null_handler(void) {}

[[gnu::weak]] [[noreturn]] void reset_handler(void) {
  for (;;)
    ;
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

// Weakly alias the handler to a sensible default
// so applications can overwrite them later
#pragma weak sv_call_handler = null_handler
#pragma weak pend_sv_handler = null_handler
#pragma weak sys_tick_handler = null_handler

#pragma weak nmi_handler = null_handler
#pragma weak hard_fault_handler = blocking_handler
#pragma weak bus_fault_handler = blocking_handler
#pragma weak usage_fault_handler = blocking_handler
#pragma weak mem_manage_handler = blocking_handler
