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

#include <cstddef>
#include <cstdint>
#include <optional>
#include <type_traits>

namespace bhp {

// You would get a linker error if you try to use the 64-bit specializations on
// a 32-bit machine

enum class From { Left, Right };

template <From from, typename U>
constexpr U OneHot(int offset) noexcept;

template <From from, typename U>
[[nodiscard]] constexpr bool TestBit(U x, int pos) noexcept;

template <From from, typename U>
[[nodiscard]] constexpr U SetBit(U x, int pos) noexcept;

template <From from, typename U>
[[nodiscard]] constexpr U ResetBit(U x, int pos) noexcept;

template <From from, typename U>
int CountZero(U x) noexcept;
template <>
int CountZero<From::Left>(std::uint32_t x) noexcept;
template <>
int CountZero<From::Right>(std::uint32_t x) noexcept;
template <>
int CountZero<From::Left>(std::uint64_t x) noexcept;
template <>
int CountZero<From::Right>(std::uint64_t x) noexcept;

template <From from, typename U>
std::optional<std::size_t> CountZero(const U* begin, const U* end) noexcept;
template <>
std::optional<std::size_t> CountZero<From::Left>(
    const std::uint32_t* begin, const std::uint32_t* end) noexcept;
template <>
std::optional<std::size_t> CountZero<From::Right>(
    const std::uint32_t* begin, const std::uint32_t* end) noexcept;
template <>
std::optional<std::size_t> CountZero<From::Left>(
    const std::uint64_t* begin, const std::uint64_t* end) noexcept;
template <>
std::optional<std::size_t> CountZero<From::Right>(
    const std::uint64_t* begin, const std::uint64_t* end) noexcept;

//////////////////// implementation details below ////////////////////

template <typename U, From from>
constexpr U OneHot(int offset) noexcept {
  if constexpr (from == From::Left) return U(1) << (sizeof(U) * 8 - 1 - offset);
  return U(1) << offset;
}

template <From from, typename U>
[[nodiscard]] constexpr bool TestBit(U x, int pos) noexcept {
  static_assert(std::is_integral<U>::value, "Integral required.");
  return x & OneHot<U, from>(pos);
}

template <From from, typename U>
[[nodiscard]] constexpr U SetBit(U x, int pos) noexcept {
  static_assert(std::is_integral<U>::value, "Integral required.");
  return x | OneHot<U, from>(pos);
}

template <From from, typename U>
[[nodiscard]] constexpr U ResetBit(U x, int pos) noexcept {
  static_assert(std::is_integral<U>::value, "Integral required.");
  return x & ~OneHot<U, from>(pos);
}

template <>
inline int CountZero<From::Left>(std::uint32_t x) noexcept {
#ifdef _MSC_VER
  unsigned long index;  // NOLINT
  _BitScanReverse(&index, x);
  return 31 ^ static_cast<int>(index);
#else
  return __builtin_clz(x);
#endif
}

template <>
inline int CountZero<From::Right>(std::uint32_t x) noexcept {
#ifdef _MSC_VER
  unsigned long index;  // NOLINT
  _BitScanForward(&index, x);
  return static_cast<int>(index);
#else
  return __builtin_ctz(x);
#endif
}

#if _WIN64 || __x86_64__ || __ppc64__

template <>
inline int CountZero<From::Left>(std::uint64_t x) noexcept {
#ifdef _MSC_VER
  unsigned long index;  // NOLINT
  _BitScanReverse64(&index, x);
  return 63 ^ static_cast<int>(index);
#else
  return __builtin_clzll(x);
#endif
}

template <>
inline int CountZero<From::Right>(std::uint64_t x) noexcept {
#ifdef _MSC_VER
  unsigned long index;  // NOLINT
  _BitScanForward64(&index, x);
  return static_cast<int>(index);
#else
  return __builtin_ctzll(x);
#endif
}

#endif

namespace internal {

template <typename U>
std::optional<std::size_t> CountLeftZeroArrayImpl(const U* begin,
                                                  const U* end) noexcept {
  for (auto iter = begin; iter != end; ++iter) {
    if (*iter != 0) {
      return 8 * sizeof(U) * (iter - begin) + CountZero<From::Left>(*iter);
    }
  }
  return std::nullopt;
}

template <typename U>
std::optional<std::size_t> CountRightZeroArrayImpl(const U* begin,
                                                   const U* end) noexcept {
  --end;
  --begin;
  for (auto iter = end; iter != begin; --iter) {
    if (*iter != 0) {
      return 8 * sizeof(U) * (end - iter) + CountZero<From::Right>(*iter);
    }
  }
  return std::nullopt;
}

}  // namespace internal

template <>
inline std::optional<std::size_t> CountZero<From::Left>(
    const std::uint32_t* begin, const std::uint32_t* end) noexcept {
  return internal::CountLeftZeroArrayImpl<std::uint32_t>(begin, end);
}

template <>
inline std::optional<std::size_t> CountZero<From::Right>(
    const std::uint32_t* begin, const std::uint32_t* end) noexcept {
  return internal::CountRightZeroArrayImpl<std::uint32_t>(begin, end);
}

#if _WIN64 || __x86_64__ || __ppc64__

template <>
inline std::optional<std::size_t> CountZero<From::Left>(
    const std::uint64_t* begin, const std::uint64_t* end) noexcept {
  return internal::CountLeftZeroArrayImpl<std::uint64_t>(begin, end);
}

template <>
inline std::optional<std::size_t> CountZero<From::Right>(
    const std::uint64_t* begin, const std::uint64_t* end) noexcept {
  return internal::CountRightZeroArrayImpl<std::uint64_t>(begin, end);
}

#endif

}  // namespace bhp
