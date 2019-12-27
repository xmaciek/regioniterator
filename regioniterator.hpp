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

#pragma once

#include <cstdint>
#include <iterator>

//! @class RegionIterator
//! @brief Iterator over subrectangle within greater rectangle
template <typename T>
struct RegionIterator {
    using this_type = RegionIterator<T>;
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::intptr_t;
    using pointer = T*;
    using reference = T&;

    pointer m_ptr = nullptr;
    pointer m_end = nullptr;
    difference_type m_diff = 0;
    uint32_t m_width = 0;
    uint32_t m_pitch = 0;

    ~RegionIterator() noexcept = default;
    constexpr RegionIterator() noexcept = default;
    constexpr RegionIterator( this_type&& ) noexcept = default;
    constexpr RegionIterator( const this_type& ) noexcept = default;
    constexpr this_type& operator = ( this_type&& ) noexcept = default;
    constexpr this_type& operator = ( const this_type& ) noexcept = default;


    //! @brief Subrectangle definition
    //! @param[in] ptr beginning of rect data
    //! @param[in] p rect pitch, most of the time it's rect width
    //! @param[in] x subrect x position within rect
    //! @param[in] y subrect y position within rect
    //! @param[in] w subrect width
    //! @param[in] h subrect height
    constexpr RegionIterator( this_type::pointer ptr, uint32_t p, uint32_t x, uint32_t y, uint32_t w, uint32_t h ) noexcept
    : m_width( w )
    , m_pitch( p )
    {
        m_ptr = ptr + p * y + x;
        m_end = m_ptr + w * h;
    }

    constexpr this_type operator + ( this_type::difference_type delta ) const noexcept
    {
        this_type tmp = *this;
        tmp.m_diff += delta;
        return tmp;
    }

    constexpr this_type operator - ( this_type::difference_type delta ) const noexcept
    {
        this_type tmp = *this;
        tmp.m_diff += delta;
        return tmp;
    }

    constexpr this_type& operator ++ () noexcept
    {
        ++m_diff;
        return *this;
    }

    constexpr this_type operator ++ ( int ) noexcept
    {
        this_type tmp = *this;
        m_diff++;
        return tmp;
    }

    constexpr this_type& operator -- () noexcept
    {
        --m_diff;
        return *this;
    }

    constexpr this_type operator -- ( int ) noexcept
    {
        this_type tmp = *this;
        m_diff--;
        return tmp;
    }

    constexpr this_type& operator += ( this_type::difference_type delta ) noexcept
    {
        m_diff += delta;
        return *this;
    }

    constexpr this_type& operator -= ( this_type::difference_type delta ) noexcept
    {
        m_diff -= delta;
        return *this;
    }

    constexpr this_type::difference_type operator - ( const this_type& rhs ) const noexcept
    {
        return m_diff - rhs.m_diff;
    }

    constexpr this_type::reference operator * () const noexcept
    {
        return *position();
    }

    constexpr bool operator != ( const this_type& rhs ) const noexcept
    {
        return m_ptr != rhs.m_ptr
            || m_diff != rhs.m_diff
            || m_width != rhs.m_width
            || m_pitch != rhs.m_pitch
            || m_end != rhs.m_end
            ;
    }

    //! @brief Automatically deduces end point iterator, based on constructor arguments
    constexpr this_type end() const noexcept
    {
        this_type tmp = *this;
        tmp.m_diff = tmp.m_end - tmp.m_ptr;
        return tmp;
    }

    //! @brief returns pointer to data within subrect
    constexpr this_type::pointer position() const noexcept
    {
        this_type::pointer ptr = m_ptr + m_diff;
        this_type::difference_type rows = m_diff / m_width;
        ptr += rows * ( m_pitch - m_width );
        return ptr;
    }

    //! @brief tells whether current index is (still) within subrectangle area
    constexpr operator bool () const noexcept
    {
        return m_diff >= 0
            && m_diff < ( m_end - m_ptr )
        ;
    }

};
