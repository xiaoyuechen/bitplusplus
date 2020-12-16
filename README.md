# Bitplusplus - A Better Bit Library for C++
The repository contains the Bitplusplus C++ library code. Bitplusplus is an open-source header-only C++ library designed to perform fast bit operations.

## How to use
Simply include the header you need.

Example:
```cpp
#include <cstddef>
#include <cstdint>

#include "bitplusplus/bit.h"
#include "bitplusplus/bit_vector.h"

int main() {
  std::uint32_t x = 0x0200ffffu;
  // Count left zero in STL (C++ 20) <bit>
  // std::countl_zero(x)
  // but here you write
  int clz = bpp::CountZero<bpp::From::Left>(x);  // 6
  // Want to count from the right?
  int crz = bpp::CountZero<bpp::From::Right>(x);  // 0

  // Want to count on an array?
  static constexpr const std::uint32_t mask[] = {0x0, 0x1u << 31, 0x0, 0xf};
  std::optional<std::size_t> clz_arr =
      bpp::CountZero<bpp::From::Left>(&mask[0], &mask[3]);  // 32

  // Want a dynamic bit vector?
  auto vec = bpp::BitVector{666, false};
  // More explicit bit (re)set/test
  vec.set<bpp::From::Left>(664);
  vec[664] = true;               // equivalent to the line above
  vec.set<bpp::From::Right>(1);  // equivalent to the line above
  // Also has essential ffs functions that are missing in STL
  std::optional<std::size_t> count = vec.CountZero<bpp::From::Left>();  // 664
}

```

## License
The Bitplusplus C++ library is licensed under the terms of the GPL-3.0 License.
