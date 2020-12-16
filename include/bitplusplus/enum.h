// Copyright (C) 2020  Xiaoyue Chen
//
// This file is part of Bitplusplus.
// See <https://github.com/xiaoyuechen/bitplusplus.git>.
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

#include <cstddef>
#include <type_traits>

namespace bpp {

template <typename Enum>
struct EnableBitWiseOperators {
  static constexpr bool enable = false;
};

template <typename Enum>
typename std::enable_if<EnableBitWiseOperators<Enum>::enable, Enum>::type
operator|(Enum lhs, Enum rhs) {
  using Underlying = typename std::underlying_type<Enum>::type;
  return static_cast<Enum>(static_cast<Underlying>(lhs) |
                           static_cast<Underlying>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitWiseOperators<Enum>::enable, Enum>::type
operator&(Enum lhs, Enum rhs) {
  using Underlying = typename std::underlying_type<Enum>::type;
  return static_cast<Enum>(static_cast<Underlying>(lhs) &
                           static_cast<Underlying>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitWiseOperators<Enum>::enable, Enum>::type
operator^(Enum lhs, Enum rhs) {
  using Underlying = typename std::underlying_type<Enum>::type;
  return static_cast<Enum>(static_cast<Underlying>(lhs) ^
                           static_cast<Underlying>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitWiseOperators<Enum>::enable, Enum>::type
operator~(Enum rhs) {
  using Underlying = typename std::underlying_type<Enum>::type;
  return static_cast<Enum>(~static_cast<Underlying>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitWiseOperators<Enum>::enable, Enum&>::type
operator|=(Enum& lhs, Enum rhs) {
  using Underlying = typename std::underlying_type<Enum>::type;
  lhs = static_cast<Enum>(static_cast<Underlying>(lhs) |
                          static_cast<Underlying>(rhs));

  return lhs;
}

template <typename Enum>
typename std::enable_if<EnableBitWiseOperators<Enum>::enable, Enum&>::type
operator&=(Enum& lhs, Enum rhs) {
  using Underlying = typename std::underlying_type<Enum>::type;
  lhs = static_cast<Enum>(static_cast<Underlying>(lhs) &
                          static_cast<Underlying>(rhs));
  return lhs;
}

template <typename Enum>
typename std::enable_if<EnableBitWiseOperators<Enum>::enable, Enum&>::type
operator^=(Enum& lhs, Enum rhs) {
  using Underlying = typename std::underlying_type<Enum>::type;
  lhs = static_cast<Enum>(static_cast<Underlying>(lhs) ^
                          static_cast<Underlying>(rhs));
  return lhs;
}

}  // namespace bpp
