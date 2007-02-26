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

class QColor;

namespace Poisson 
{

class CPixel 
{
public:
    CPixel();
    CPixel(const QColor & c, const SelectEnum & s = kNotSelected);

    QColor GetQColor() const;

    float & Color(const ColorEnum & i) { return(m_c[i]); }
    const float & Color(const ColorEnum & i) const { return(m_c[i]); }

    unsigned & Selection() { return(m_s); }
    const unsigned & Selection() const { return(m_s); }

private:
    float m_c[NUM_COLORS]; /// The color channels
    unsigned int m_s; /// The selection channel
};

}; // namespace
