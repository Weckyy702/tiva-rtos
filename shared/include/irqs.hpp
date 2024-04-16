#pragma once

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
