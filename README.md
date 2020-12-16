# Bitplusplus - A Better Bit Library for C++
The repository contains the Bitplusplus C++ library code. Bitplusplus is an open-source header-only C++ library designed to perform fast bit operations.

## How to use
Simply include the header you need.

Example:
```cpp
#include <cstddef>
#include <cstdint>

#include "bitplusplus/bit.h"

int main() {
    std::uint32_t x = 0x0200ffffu;
    // Count left zero in STL (C++ 20) <bit>
    // std::countl_zero(x)
    // but here you write
    int clz = bpp::Count<bpp::From::Left>(x); // 6
    // Want to count from the right?
    int crz = bpp::Count<bpp::From::Right>(x); // 0

    // Want to count on an array?
    static constexpr const std::uint32_t mask[] = 
        {0x0, 0x1u << 31, 0x0, 0x0, 0xf};
    int clz_arr = bpp::Count<bpp::From::Left>(&mask[0], &mask[4]); // 32

    // Want a dynamic bit vector?
    auto vec = bpp::BitVector{666, false};
    // More explicit bit (re)set/test
    vec.Set<bpp::From::Left>(664);
    vec.Set<bpp::From::Right>(1); // equivalent to the line above
    // Also has essential ffs functions that are missing STL
    std::optional<std::size_t> count = vec.CoutZero<From::Left>(); // 664
}

```

## License
The Bitplusplus C++ library is licensed under the terms of the GPL-3.0 License.
