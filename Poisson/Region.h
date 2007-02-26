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

#define NO_PIXEL unsigned(-1) 

struct RegionPixel {
    bool isEdge; /// indicates if the pixel is an edge or not.
    unsigned x, y;    /// Coordinates of the pixel
    
    enum ADJECENCYENUM {
        kLeft = 0,
        kAbove = 1,
        kRight = 2,
        kBelow = 3
    };
    unsigned adjecentIdx[4]; /// Index values of the adjecent edge pixels in the dataset. 
    /// NOT_A_PIXEL means that there is no adjecent pixel
};

typedef std::vector<RegionPixel> RegionType;    

