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

#include "ImageComplete.h"

#include <stdlib.h>
#include <vector>

#include <klocale.h>
#include <kiconloader.h>
#include <kinstance.h>
#include <kmessagebox.h>
#include <kstandarddirs.h>
#include <ktempfile.h>
#include <kdebug.h>
#include <kgenericfactory.h>

#include <kis_iterators_pixel.h>
#include <kis_filter_registry.h>
#include <kis_global.h>
#include <kis_types.h>
#include <kis_multi_bool_filter_widget.h>

#include "Poisson/Algorithm.h"
#include "Poisson/ImageData.h"
#include "Poisson/Pixel.h"

typedef KGenericFactory<KritaImageComplete> KritaImageCompleteFactory;
K_EXPORT_COMPONENT_FACTORY( kritaImageComplete, KritaImageCompleteFactory( "krita" ) )

KritaImageComplete::KritaImageComplete(QObject *parent, const char *name, const QStringList &)
: KParts::Plugin(parent, name)
{
    setInstance(KritaImageCompleteFactory::instance());

    kdDebug(41006) << "ImageRestoration tools plugin. Class: "
    << className()
    << ", Parent: "
    << parent -> className()
    << "\n";

    if(parent->inherits("KisFilterRegistry"))
    {
        KisFilterRegistry * manager = dynamic_cast<KisFilterRegistry *>(parent);
        manager->add(new KisFilterImageComplete());
    }
}

KritaImageComplete::~KritaImageComplete()
{
}

KisFilterImageComplete::KisFilterImageComplete() 
    : KisFilter(id(), "enhance", i18n("&ImageComplete"))
{

}

/**
 * NOTE: We ignore the rect because it is the bounding rect of the selection and 
 * we want the bounds of the whole image.
 */
void KisFilterImageComplete::process(KisPaintDeviceSP src, KisPaintDeviceSP dst, 
                                     KisFilterConfiguration* /*config*/, const QRect& rect ) 
{
    Q_ASSERT(src != 0);
    Q_ASSERT(dst != 0);

    if(src->hasSelection() == false)
    {	
	// Have to clear the progress to allow the info box to work
	setProgressDone();
	// Popup a error dialog here.
	KMessageBox::information (0,
				  i18n("You must select a region to Complete."),
				  i18n("Region was not selected"));
    } else
    {
        // NOTE: We need to process the whole image, not just the selected area.
        // Double NOTE: we should be processing just the selected areas to increase speed 
        // instead of the whole image
        const QRect exactRect = src->exactBounds();

        try
        {
            // Build a multidim array of floats to represent all of the color and 
            // selection information of the rect of interest.
            // Get the region of interest and grow it by one on all sizes and bound it by exactRect
            QRect tpRect = rect;
            tpRect.addCoords(-1, -1, 1, 1);
            const QRect tRect = tpRect.intersect(exactRect);

            kdDebug(41006) << "KisFilterImageComplete::process: tight rect = " << tRect << "\n";

            KisColorSpace* cs = src->colorSpace();                

            // Build a poisson algorithm object
            Poisson::CAlgorithm algorithm(tRect.size());
            Poisson::CImageData * data = algorithm.Data();

            KisRectIteratorPixel it = src->createRectIterator(tRect.x(), tRect.y(), 
                                                              tRect.width(), tRect.height(), 
                                                              false);
            while(it.isDone() == false)
            {
                QColor c;
                // Just lose the precision for now...
                cs->toQColor(it.rawData(), &c);
                Poisson::CPixel pixel(c, (it.isSelected()? Poisson::kSelected: Poisson::kNotSelected));
                data->SetPixel(pixel, it.x()-tRect.x(), it.y()-tRect.y());
                ++it;
            }
            
            // This setups the poisson operation
            algorithm.PreProcess();
            
            setProgressTotalSteps(Poisson::NUM_COLORS);
            for(Poisson::ColorEnum c=Poisson::MIN_COLOR; c<=Poisson::MAX_COLOR; c=Poisson::ColorEnum(c+1))
            {
                algorithm.Process(c);
                incProgress();
            }
            
            // Copy the processed data back into the dst paintDevice
            data = algorithm.Data();
            it = dst->createRectIterator(tRect.x(), tRect.y(), 
                                         tRect.width(), tRect.height(), 
                                         true);
            while(it.isDone() == false)
            {
                const Poisson::CPixel pixel = data->Pixel(it.x()-tRect.x(), it.y()-tRect.y());
                QColor c = pixel.GetQColor();
                cs->fromQColor(c, it.rawData());
                ++it;
            }
        } catch(...)
        {
	    setProgressDone();
            // Show a dialog box
            // Popup a error dialog here.
            KMessageBox::error(0, 
                               i18n("There was an math exception thrown while running the filter. "
                                    "Please email kimageshop@kde.org. "
                                    "If you want, please try running the filter again. "
                                    "The image was not modified."), 
                               i18n("Math exception caught"));
        }
    }   
    
    // NOTE TO DEVELOPERS: Progress state should be following RAII.
    setProgressDone(); // Must be called even if you don't really support progression
}




