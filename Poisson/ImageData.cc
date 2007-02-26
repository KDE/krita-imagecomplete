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

#include "ImageData.h"
#include "Plane.h"
#include "Pixel.h"

namespace Poisson {

class PImageData
{
public:
    PImageData(const unsigned & w, const unsigned & h)
    { 
        c[kRed].Resize(w, h);
        c[kGreen].Resize(w, h);
        c[kBlue].Resize(w, h);
        s.Resize(w, h);
    }

    CPlane<float> c[NUM_COLORS];
    CPlane<unsigned> s;
};

CImageData::CImageData(const unsigned & w, const unsigned & h)
    : p(new PImageData(w, h))
{ }

CImageData::~CImageData()
{
    delete p;
}

unsigned CImageData::Width() const { return(p->s.Width()); }
unsigned CImageData::Height() const { return(p->s.Height()); }

CPlane<float> & CImageData::Color(const ColorEnum & channel) { return(p->c[channel]); }
const CPlane<float> & CImageData::Color(const ColorEnum & channel) const { return(p->c[channel]); }
CPlane<unsigned> & CImageData::Selected() { return(p->s); }
const CPlane<unsigned> & CImageData::Selected() const { return(p->s); }

CPixel CImageData::Pixel(const unsigned & x, const unsigned & y) const
{
    CPixel d;
    d.Color(kRed) = p->c[kRed](x, y);
    d.Color(kGreen) = p->c[kGreen](x, y);
    d.Color(kBlue) = p->c[kBlue](x, y);
    d.Selection() = p->s(x, y);
    return(d);
}
void CImageData::SetPixel(const CPixel & d, const unsigned & x, const unsigned & y)
{
    p->c[kRed](x, y) = d.Color(kRed);
    p->c[kGreen](x, y) = d.Color(kGreen);
    p->c[kBlue](x, y) = d.Color(kBlue);
    p->s(x, y) = d.Selection();
}

}; // namespace

