#pragma once

#include "ints.hpp"

namespace rtos::io::memory_mapped {

template <typename T = u32> class Register {
public:
  constexpr explicit Register(u32 address)
      : address{reinterpret_cast<volatile T *>(address)} {}

  volatile T &operator*() { return *address; }

  T read() const { return *address; }

  void write(T t) { *address = t; }

private:
  volatile T *address;
};

} // namespace rtos::io::memory_mapped
