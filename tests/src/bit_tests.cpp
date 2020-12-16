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

#include <cstddef>
#include <tuple>

#include "bitplusplus/bit.h"
#include "gtest/gtest.h"

namespace bhp {

struct BitTestStruct {
  std::uint64_t x;
  int pos;
  bool set;
  int clz, crz;
};

struct BitTest : public testing::TestWithParam<BitTestStruct> {};

TEST_P(BitTest, TestBit) {
  auto [x, pos, set, clz, crz] = GetParam();
  bool s = TestBit(x, pos);
  EXPECT_FALSE(set ^ TestBit(x, pos));
}

TEST_P(BitTest, SetReset) {
  auto [x, pos, set, clz, crz] = GetParam();
  EXPECT_TRUE(TestBit(SetBit(x, pos), pos));
  EXPECT_FALSE(TestBit(ResetBit(x, pos), pos));
}

TEST_P(BitTest, CzlCzrTest) {
  auto [x, pos, set, clz, crz] = GetParam();
  if (clz >= 0) {
    EXPECT_EQ(CountZero<From::Left>(x), clz);
  }
  if (crz >= 0) {
    EXPECT_EQ(CountZero<From::Right>(x), crz);
  }
}

static constexpr const BitTestStruct kBitTestTestData[] = {
    {0x0, 0, false, -1, -1},        {0x1, 0, true, 63, 0},
    {0x000f, 3, true, 15 * 4, 0},   {0x000f, 2, true, 15 * 4, 0},
    {0x000f0, 1, false, 14 * 4, 4}, {0x1ull << 63, 63, true, 0, 63}};

INSTANTIATE_TEST_SUITE_P(, BitTest, testing::ValuesIn(kBitTestTestData));

}  // namespace bhp
