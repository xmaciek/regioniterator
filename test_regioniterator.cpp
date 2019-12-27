// MIT License
//
// Copyright (c) 2019 Maciej Latocha ( latocha.maciek@gmail.com )
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "regioniterator.hpp"

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <numeric>

TEST( reg, iterate )
{
    std::vector<uint16_t> expected( 10 );
    std::iota( expected.begin(), expected.end(), 1 );
    std::fill( expected.begin() + 1, expected.begin() + 9, 0 );

    std::vector<uint16_t> bitmap( 10 );
    std::iota( bitmap.begin(), bitmap.end(), 1 );
    RegionIterator<uint16_t> it( bitmap.data(), 8, 1, 0, 8, 1 );
    std::fill( it, it.end(), 0 );

    EXPECT_EQ( bitmap, expected );
}

TEST( reg, region )
{
    std::vector<uint16_t> bitmap( 8 * 8, 0 );
    std::vector<uint16_t> expected( 8 * 8, 0 );
    std::fill( expected.begin() + 4, expected.begin() + 8, 1 );
    std::fill( expected.begin() + 12, expected.begin() + 16, 1 );

    RegionIterator<uint16_t> it( bitmap.data(), 8, 4, 0, 4, 2 );
    std::fill( it, it.end(), 1 );
    EXPECT_EQ( bitmap, expected );
}

TEST( reg, prepostinc )
{
    std::vector<uint16_t> bitmap( 64 );
    std::iota( bitmap.begin(), bitmap.end(), 0 );
    RegionIterator<uint16_t> it1( bitmap.data(), 8, 0, 0, 4, 4 );
    RegionIterator<uint16_t> it2( bitmap.data(), 8, 0, 0, 4, 4 );
    EXPECT_EQ( *(++it1), bitmap[ 1 ] );
    EXPECT_EQ( *it1, bitmap[ 1 ] );

    EXPECT_EQ( *(it2++), bitmap[ 0 ] );
    EXPECT_EQ( *it2, bitmap[ 1 ] );
}
