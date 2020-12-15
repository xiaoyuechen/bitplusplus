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

#include <cstddef>
#include <tuple>

#include "bit-helper/bit.h"
#include "gtest/gtest.h"

namespace bhp {

struct BitTest
    : public testing::TestWithParam<std::tuple<std::uint64_t, int, bool>> {};

TEST_P(BitTest, TestBit) {
  auto [x, pos, set] = GetParam();
  bool s = TestBit(x, pos);
  EXPECT_FALSE(set ^ TestBit(x, pos));
}

TEST_P(BitTest, SetReset) {
  auto [x, pos, set] = GetParam();
  EXPECT_TRUE(TestBit(SetBit(x, pos), pos));
  EXPECT_FALSE(TestBit(ResetBit(x, pos), pos));
}

static constexpr const std::tuple<std::uint64_t, int, bool> kBitTestTestData[] =
    {{0x0, 0, false},   {0x1, 0, true},      {0x000f, 3, true},
     {0x000f, 2, true}, {0x000f0, 1, false}, {0x1ull << 63, 63, true}};

INSTANTIATE_TEST_SUITE_P(, BitTest, testing::ValuesIn(kBitTestTestData));

}  // namespace bhp
