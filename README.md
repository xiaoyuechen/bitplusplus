# Bit Helper - Bit Utilities for C++
The repository contains the Bit Helper C++ library code. Bit Helper is an open-source header-only C++ library designed to perform fast bit operations.

## How to use
Simply include the header you need.

Example:
```cpp
#include <cstddef>

#include "bit-helper/bit.h"

int main() {
    std::uint32_t x = 0x0200ffffu;
    // Count left zero in STL (C++ 20) <bit>
    // std::countl_zero(x)
    // but here you write
    int clz = bhp::Count<bhp::From::Left>(x); // 6
    // Want to count from the right?
    int crz = bhp::Count<bhp::From::Right>(x); // 0

    // Want to count on an array?
    static constexpr const std::uint32_t mask[] = 
        {0x0, 0x1u << 31, 0x0, 0x0, 0xf};
    int clz_arr = bhp::Count<bhp::From::Left>(&mask[0], &mask[4]); // 32
}

```

## License
The Bit Helper C++ library is licensed under the terms of the GPL-3.0 License.
