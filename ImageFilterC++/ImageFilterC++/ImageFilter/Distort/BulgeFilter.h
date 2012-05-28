/* 
 * HaoRan ImageFilter Classes v0.3
 * Copyright (C) 2012 Zhenjun Dai
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation.
 */

#if !defined(BulgeFilter_H)
#define BulgeFilter_H

#include "BilinearDistort.h"


namespace HaoRan_ImageFilter{

class BulgeFilter : public BilinearDistort{

private:
    double   m_amount ;
    double   m_offset_x ;
    double   m_offset_y ;

public:
    /**
        Constructor \n
        param -200 <= nAmount <= 100 \n
        param -1 <= offset_x (offset_y) <= 1
    */
    BulgeFilter (int nAmount, double offset_x=0, double offset_y=0)
    {
        m_amount = nAmount / 100.0 ;
        m_offset_x = FClamp(offset_x, -1.0, 1.0) ;
        m_offset_y = FClamp(offset_y, -1.0, 1.0) ;
    }

	virtual void calc_undistorted_coord (int x, int y, double& un_x, double& un_y)
    {
        double   hw = clone.getWidth() / 2.0 ;
        double   hh = clone.getHeight() / 2.0 ;
        double   maxrad = (hw < hh ? hw : hh) ;
        hw += m_offset_x * hw ;
        hh += m_offset_y * hh ;

        double   u = x - hw ;
        double   v = y - hh ;
        double   r = sqrt(u*u + v*v) ;
        double   rscale1 = 1.0 - (r / maxrad) ;

        if (rscale1 > 0)
        {
            double   rscale2 = 1.0 - m_amount * rscale1 * rscale1 ;
            un_x = FClamp (u * rscale2 + hw, 0.0, clone.getWidth()-1.0) ;
            un_y = FClamp (v * rscale2 + hh, 0.0, clone.getHeight()-1.0) ;
        }
        else
        {
            un_x = x ;
            un_y = y ;
        }
    }

};

}// namespace HaoRan
#endif