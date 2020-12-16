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

#include "bitplusplus/bit_vector.h"

#include <cstddef>
#include <tuple>

#include "gtest/gtest.h"

namespace bpp {

TEST(BitVectorTest, ResizeDown) {
  auto vec = BitVector(120, false);
  vec.set<From::Left>(63);
  vec.resize(64);
  EXPECT_EQ(vec.size(), 64);
  EXPECT_TRUE(vec.test<From::Left>(63));
  EXPECT_FALSE(vec.test<From::Left>(62));
  EXPECT_EQ(*vec.CountZero<From::Left>(), 63);
  EXPECT_EQ(*vec.CountZero<From::Right>(), 0);
}

TEST(BitVectorTest, ResizeDown2) {
  auto vec = BitVector(120, false);
  vec.set<From::Left>(62);
  vec.resize(64);
  EXPECT_EQ(vec.size(), 64);
  EXPECT_TRUE(vec.test<From::Left>(62));
  EXPECT_FALSE(vec.test<From::Left>(61));
  EXPECT_EQ(*vec.CountZero<From::Left>(), 62);
  EXPECT_EQ(*vec.CountZero<From::Right>(), 1);
}

TEST(BitVectorTest, ResizeUp) {
  auto vec = BitVector(120, false);
  vec.set<From::Left>(119);
  EXPECT_TRUE(vec.test<From::Left>(119));
  vec.resize(150);
  EXPECT_EQ(vec.size(), 150);
  EXPECT_FALSE(vec.test<From::Left>(118));
  EXPECT_TRUE(vec.test<From::Left>(119));
  EXPECT_FALSE(vec.test<From::Left>(120));
  EXPECT_FALSE(vec.test<From::Left>(149));
  EXPECT_EQ(*vec.CountZero<From::Left>(), 119);
  EXPECT_EQ(*vec.CountZero<From::Right>(), 149 - 119);
}

TEST(BitVectorTest, Reference) {
  static constexpr std::size_t kCount = 99999;
  auto vec = BitVector(kCount, false);
  for (std::size_t i = 0; i != kCount - 1; ++i) {
    vec[i] = true;
    EXPECT_TRUE(vec.test<From::Left>(i));
    EXPECT_TRUE(vec.test<From::Right>(kCount - i - 1));
    EXPECT_FALSE(vec.test<From::Left>(i + 1));
  }
  for (std::size_t i = 0; i != kCount - 1; ++i) {
    EXPECT_TRUE(vec.test<From::Left>(i));
  }
  EXPECT_FALSE(vec.test<From::Left>(kCount - 1));
  EXPECT_EQ(vec.CountZero<From::Left>(), 0);
  EXPECT_EQ(vec.CountZero<From::Right>(), 1);
}

}  // namespace bhp
