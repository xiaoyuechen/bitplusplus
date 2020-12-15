// Copyright (C) 2020  Xiaoyue Chen
//
// This file is part of Bit Helper.
// See <https://github.com/xiaoyuechen/bit-helper.git>.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <cstdint>
#include <type_traits>

namespace bhp {

template <typename U>
[[nodiscard]] bool TestBit(U x, int pos) {
  static_assert(std::is_integral<U>::value, "Integral required.");
  return (x & (U(1) << pos));
}

template <typename U>
[[nodiscard]] U SetBit(U x, int pos) {
  static_assert(std::is_integral<U>::value, "Integral required.");
  return (x | (U(1) << pos));
}

template <typename U>
[[nodiscard]] U ResetBit(U x, int pos) {
  static_assert(std::is_integral<U>::value, "Integral required.");
  return (x & ~(U(1) << pos));
}

}  // namespace bhp
