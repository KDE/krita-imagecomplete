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

#include "Pixel.h"

#include <qcolor.h>

namespace Poisson {

CPixel::CPixel() 
{
    m_c[kRed] = 0.f;
    m_c[kGreen] = 0.f;
    m_c[kBlue] = 0.f;
    m_s = kNotSelected;

}

CPixel::CPixel(const QColor & c, const SelectEnum & s)
{
    m_c[kRed] = float(c.red())/255;
    m_c[kGreen] = float(c.green())/255;
    m_c[kBlue] = float(c.blue())/255;
    m_s = s;
};

QColor CPixel::GetQColor() const
{
    return( QColor( int(m_c[kRed]*255), int(m_c[kGreen]*255), int(m_c[kBlue]*255) ) );
}

}; // namespace
