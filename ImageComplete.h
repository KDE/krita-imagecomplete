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

#ifndef ImageComplete_H
#define ImageComplete_H

// TODO: remove that
#define LCMS_HEADER <lcms.h>
// TODO: remove it !

#include <kparts/plugin.h>
#include "kis_filter.h"
#include "kis_filter_config_widget.h"

#include <memory>

class KritaImageComplete : public KParts::Plugin
{
public:
    KritaImageComplete(QObject *parent, const char *name, const QStringList &);
    virtual ~KritaImageComplete();
};

class KisFilterImageComplete : public KisFilter
{
public:
    KisFilterImageComplete();
public:
    virtual void process(KisPaintDeviceSP src, KisPaintDeviceSP dst, 
			 KisFilterConfiguration*, const QRect&);
    virtual ColorSpaceIndependence colorSpaceIndependence() { return FULLY_INDEPENDENT; };
    static inline KisID id() { return KisID("ImageComplete", i18n("ImageComplete")); };
    virtual bool supportsPainting() { return true; }
    virtual bool supportsPreview() { return false; }
    virtual bool supportsIncrementalPainting() { return false; }
    virtual bool supportsAdjustmentLayers() { return false; }
};

#endif
