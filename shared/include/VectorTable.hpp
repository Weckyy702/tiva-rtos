#include "ints.hpp"

#ifndef offsetof
#define offsetof(T, m) __builtin_offsetof(T, m)
#endif

typedef void (*VectorFunction)(void);

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
  VectorFunction irqs[139];
};

static_assert(sizeof(VectorTable) == 0x026C);

static_assert(offsetof(VectorTable, initial_sp) == 0);
static_assert(offsetof(VectorTable, sv_call) == 0x002C);
static_assert(offsetof(VectorTable, pend_sv) == 0x0038);
