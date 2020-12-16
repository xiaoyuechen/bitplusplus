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
#include <vector>

#include "bit-helper/bit.h"

namespace bhp {

class BitVector {
 public:
  using size_type = std::size_t;
  class reference;
  using const_reference = bool;

  static constexpr const size_type kWordBits = sizeof(size_type) * 8;

  explicit BitVector(size_type count = 0, bool value = false)
      : mask_(BitToWordCount(count), value ? ~0 : 0), size_{count} {}

  size_type size() const noexcept { return size_; }

  size_type capacity() const noexcept { return mask_.size() * kWordBits; }

  template <From from>
  std::optional<size_type> CountZero() const noexcept {
    if constexpr (from == From::Right) {
      if (mask_.back() != 0) {
        auto count = ::bhp::CountZero<From::Right>(mask_.back()) -
                     static_cast<int>(kWordBits * mask_.size() - size_);
        if (count >= 0) {
          return count;
        }
      }
    }
    auto count =
        ::bhp::CountZero<from>(mask_.data(), mask_.data() + mask_.size());
    if (count.has_value() && count < size_) {
      if constexpr (from == From::Right) {
        *count -= kWordBits * mask_.size() - size_;
      }
      return count;
    }
    return std::nullopt;
  }

  template <From from>
  bool test(size_type pos) const noexcept {
    auto [word, bit] = GetCursor<from>(pos);
    return TestBit<From::Left>(mask_[word], bit);
  }

  template <From from>
  void set(size_type pos) noexcept {
    auto [word, bit] = GetCursor<from>(pos);
    mask_[word] = SetBit<From::Left>(mask_[word], bit);
  }

  template <From from>
  void reset(size_type pos) noexcept {
    auto [word, bit] = GetCursor<from>(pos);
    mask_[word] = ResetBit<From::Left>(mask_[word], bit);
  }

  const_reference operator[](size_type pos) const noexcept {
    return test<From::Left>(pos);
  }

  reference operator[](size_type pos) noexcept { return reference{*this, pos}; }

  void resize(size_type count, bool value = false) {
    if (size_ < count) {
      mask_.resize(BitToWordCount(count), value ? -1 : 0);
      FixGrowthBorder(size_, value);
      size_ = count;
    } else if (size_ > count) {
      size_ = count;
      mask_.resize(BitToWordCount(count));
    }
  }

  void push_back(bool value) { resize(size_ + 1, value); }

  void clear() noexcept {
    mask_.clear();
    size_ = 0;
  }

  class reference {
   public:
    operator bool() const noexcept { return vec_.test<From::Left>(pos_); }

    reference& operator=(bool x) noexcept {
      if (x)
        vec_.set<From::Left>(pos_);
      else
        vec_.reset<From::Left>(pos_);
      return *this;
    }

   private:
    reference(BitVector& vec, BitVector::size_type pos) noexcept
        : vec_{vec}, pos_{pos} {}

    BitVector& vec_;
    BitVector::size_type pos_;

    friend class BitVector;
  };

 private:
  struct Cursor {
    size_type word_cursor, bit_cursor;
  };

  constexpr size_type BitToWordCount(size_type count) const noexcept {
    return (count + kWordBits - 1) / kWordBits;
  }

  template <From from>
  constexpr Cursor GetCursor(size_type pos) const noexcept {
    if constexpr (from == From::Right) pos = size_ - 1 - pos;
    size_type word_cursor = pos / kWordBits;
    size_type bit_cursor = pos - kWordBits * word_cursor;
    return Cursor{word_cursor, bit_cursor};
  }

  void FixGrowthBorder(size_type old_size, bool value) noexcept {
    auto end_mask = ~size_type(0);
    end_mask >>= (old_size % kWordBits);
    if (value)
      mask_[old_size / kWordBits] |= end_mask;
    else
      mask_[old_size / kWordBits] &= ~end_mask;
  }

  std::vector<size_type> mask_;
  size_type size_;
};

}  // namespace bhp
