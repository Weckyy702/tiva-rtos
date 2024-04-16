#pragma once

#include <stdint.h>

#define DEFINE_INT(T, Base, Size)                                              \
  using T = Base;                                                              \
  constexpr T operator"" _##T(unsigned long long x) {                          \
    return static_cast<T>(x);                                                  \
  }                                                                            \
  static_assert(sizeof(T) == Size);

DEFINE_INT(u8, uint8_t, 1)
DEFINE_INT(u16, uint16_t, 2)
DEFINE_INT(u32, uint32_t, 4)

DEFINE_INT(i8, int8_t, 1)
DEFINE_INT(i16, int16_t, 2)
DEFINE_INT(i32, int32_t, 4)
