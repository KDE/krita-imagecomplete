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

#include "Algorithm.h"
#include "ImageData.h"
#include "Pixel.h"
#include "Plane.h"

#include <gmm/gmm.h>
#include <qsize.h>

namespace Poisson {

class PAlgorithm
{
public:
    PAlgorithm(const QSize & size)
    : data(new CImageData(size.width(), size.height()))
    , adjMatrix(size.width()*size.height(), size.width()*size.height())
    { }

    ~PAlgorithm() { delete data; }

    CImageData * data;
    gmm::row_matrix< gmm::wsvector<float> > adjMatrix;
    // Later add the functor for calculating the b vector.
};


CAlgorithm::CAlgorithm(const QSize & size)
    : d(new PAlgorithm(size))
{ }
CAlgorithm::~CAlgorithm() 
{ 
    delete d;
}

CImageData * CAlgorithm::Data() { return(d->data); }

void CAlgorithm::PreProcess()
{
    const unsigned width = d->data->Width(), height = d->data->Height();
    // We need to build the smallest adjacency matrix possible from d->data so 
    // solving the linear system is fast as possible
    // 1) 

    // Build the adjecency matrix
    const CPlane<unsigned> & selected = d->data->Selected();

    gmm::clear(d->adjMatrix);

    for(unsigned y=0; y<height; y++)
    {
        for(unsigned x=0; x<width; x++)
        {
            const int idx = y*width + x;

            // Build the matrix at idx
            // The user needs to select the areas he wants filled in.
            if(selected(x, y) == kNotSelected)
            {
                d->adjMatrix(idx, idx) = 1.f;
            } else
            {
                float count = -4.f;
                if(y > 0) { d->adjMatrix(idx, idx-width) = 1.f; }
                else { count += 1.f; }
                if(y < height-1) { d->adjMatrix(idx, idx+width) = 1.f; }
                else { count += 1.f; }
                
                if(x > 0) { d->adjMatrix(idx, idx-1) = 1.f; }
                else { count+=1.f; }
                if(x < width-1) { d->adjMatrix(idx, idx+1) = 1.f; }
                else { count+=1.f; }
                
                d->adjMatrix(idx, idx) = count;
            }
        }
    }
}
void CAlgorithm::Process(ColorEnum channel)
{
    Q_ASSERT(channel < NUM_COLORS);

    const unsigned width = d->data->Width(), height = d->data->Height();

    const int N = width * height;

    // Make a known pixel vector b (size=N) with the known pixel values in each entry
    std::vector<float> bWrite(N);

    const CPlane<unsigned> & selected = d->data->Selected();
    CPlane<float> & color = d->data->Color(channel);

    //      std::cout << "Building matrix " << std::endl;
    
    for(unsigned y=0; y<height; y++)
    {
        for(unsigned x=0; x<width; x++)
        {
            const int idx = y*width + x;

            // Build the vector at idx
            if(selected(x, y) == kNotSelected)
            {
                bWrite[idx] = color(x, y);
            } else
            {
                bWrite[idx] = 0.f;
            }
        }
    }

    // Make a readable vectors b and x
    std::vector<float> B(N), X(N);
    gmm::copy(bWrite, B);
    gmm::copy(bWrite, X);

    //typedef gmm::row_matrix< gmm::rsvector<float> > MatrixType;
    typedef gmm::csr_matrix<float> MatrixType;

    // std::cout << "Solving matrix " << std::endl;
    // Maybe the csr matrix will be faster then row_matrix<rsvector<float>.
    // Doubt it matters since the cache is probably larger then number of elements anyway...
    MatrixType M(N, N);
    gmm::copy(d->adjMatrix, M);

    // computation of a preconditioner (ILUT)
    // gmm::diagonal_precond< MatrixType > P(M);
    // gmm::ildltt_precond< MatrixType > P(M, 10, 1e-4);
    gmm::ilut_precond< MatrixType > P(M, 10, 1e-4);
    // gmm::ilutp_precond< MatrixType > P(M, 10, 1e-4);

    // defines an iteration object, with a max residu of 1E-8
    gmm::iteration iter(1E-4); // 1e-8

    // Solve the matrix
    gmm::gmres(M, X, B, P, 50, iter);  // execute the GMRES algorithm
    // gmm::bicgstab(M, x, b, P, iter);
    // gmm::cg(M, x, b, P, iter);
    // gmm::qmr(M, x, b, P, iter); // Quasi-Minimal Residual method.

    // Convert from X to the channel
    // color.Data() = X;
    for(unsigned y=0; y<height; y++)
    {
        for(unsigned x=0; x<width; x++)
        {
            const int idx = y*width + x;
            color(x, y) = X[idx]; 
        }
    }
}

}; // namespace
