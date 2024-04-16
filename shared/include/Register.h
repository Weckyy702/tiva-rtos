#pragma once

#include "ints.h"

template <typename T = u32> class Register {
public:
  constexpr explicit Register(T address)
      : address{reinterpret_cast<volatile T *>(address)} {}

  volatile T &operator*() { return *address; }

  T read() const { return *address; }

  void write(T t) { *address = t; }

private:
  volatile T *address;
};
