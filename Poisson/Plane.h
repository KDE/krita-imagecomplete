/*
 * This file is part of the KDE project
 *
 * Copyright (c) 2007 Benjamin Schleimer <bensch128@yahoo.com>
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#pragma once

#include <assert.h>
#include <vector>

namespace Poisson {

template <typename T>
class CPlane
{
public:
    CPlane() : m_width(0), m_height(0), m_data(0) { }

    virtual ~CPlane() { }
    
    void Resize(const unsigned & width, const unsigned & height) 
    { 
        m_width = width; m_height = height;
        m_data.resize(width*height);
    }

    unsigned Width() const { return(m_width); }
    unsigned Height() const { return(m_height); }

    /**
     * Returns the value at (x,y)
     * @throws EOutOfRange if the arguments are invalid
     */
    T& operator()(const unsigned & x, const unsigned & y)
    {
        assert(x < m_width);
        assert(y < m_height);
        
        return(m_data[m_width*y + x]);
    }

    /**
     * Returns the value at (x,y)
     * @throws EOutOfRange if the arguments are invalid
     */
    const T& operator()(const unsigned & x, const unsigned & y) const
    {
        assert(x < m_width);
        assert(y < m_height);

        return(m_data[m_width*y + x]);
    }

    std::vector<T> & Data() { return(m_data); }

private:
    unsigned m_width, m_height;
    std::vector<T> m_data;
};

};
