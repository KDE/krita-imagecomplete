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

#include "defs.h"

namespace Poisson {

template<typename T> class CPlane;

class PImageData;
class CPixel;

class CImageData
{
public:
    CImageData(const unsigned & width, const unsigned & height);
    virtual ~CImageData();

    unsigned Width() const;
    unsigned Height() const;

    CPlane<float> & Color(const ColorEnum & channel);
    const CPlane<float> & Color(const ColorEnum & channel) const;
    CPlane<unsigned> & Selected();
    const CPlane<unsigned> & Selected() const;

    CPixel Pixel(const unsigned & x, const unsigned & y) const;
    void SetPixel(const CPixel &, const unsigned & x, const unsigned & y);

private:
    PImageData * p;
};

};
