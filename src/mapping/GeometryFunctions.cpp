//
//  GeometryFunctions.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/4/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "GeometryFunctions.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>

// It turns out, we can't use "normal" functions for determining distance.
// We have to use Bresenham functions to acurately determine distance
// In our tile-based data structures.

int distanceXY(int posXOne, int posYOne, const int posXTwo, const int posYTwo){

    int distance = 0;
    int x1 = std::min(posXOne, posXTwo);
    int x2 = std::max(posXOne, posXTwo);
    int y1 = std::min(posYOne, posYTwo);
    int y2 = std::max(posYOne, posYTwo);
    
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;
    
    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
    
    distance++;
    
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
        
        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing
            
            error += delta_y;
            x1 += ix;
            
            distance++;
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
        
        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing
            
            error += delta_x;
            y1 += iy;
            
            distance++;
        }
    }
    
    return distance;
}


// Same as above
// Our 3d distance algorithms are modified versions of Bresenham's algorithm

int distanceXYZ(int x1, int y1, int z1, const int x2, const int y2, const int z2){
    
    int distance = 0;
    int i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
    int point[3];
    
    point[0] = x1;
    point[1] = y1;
    point[2] = z1;
    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;
    x_inc = (dx < 0) ? -1 : 1;
    l = abs(dx);
    y_inc = (dy < 0) ? -1 : 1;
    m = abs(dy);
    z_inc = (dz < 0) ? -1 : 1;
    n = abs(dz);
    dx2 = l << 1;
    dy2 = m << 1;
    dz2 = n << 1;
    
    if ((l >= m) && (l >= n)) {
        err_1 = dy2 - l;
        err_2 = dz2 - l;
        for (i = 0; i < l; i++) {
            distance++;
            if (err_1 > 0) {
                point[1] += y_inc;
                err_1 -= dx2;
            }
            if (err_2 > 0) {
                point[2] += z_inc;
                err_2 -= dx2;
            }
            err_1 += dy2;
            err_2 += dz2;
            point[0] += x_inc;
        }
    } else if ((m >= l) && (m >= n)) {
        err_1 = dx2 - m;
        err_2 = dz2 - m;
        for (i = 0; i < m; i++) {
            distance++;
            if (err_1 > 0) {
                point[0] += x_inc;
                err_1 -= dy2;
            }
            if (err_2 > 0) {
                point[2] += z_inc;
                err_2 -= dy2;
            }
            err_1 += dx2;
            err_2 += dz2;
            point[1] += y_inc;
        }
    } else {
        err_1 = dy2 - n;
        err_2 = dx2 - n;
        for (i = 0; i < n; i++) {
            distance++;
            if (err_1 > 0) {
                point[1] += y_inc;
                err_1 -= dz2;
            }
            if (err_2 > 0) {
                point[0] += x_inc;
                err_2 -= dz2;
            }
            err_1 += dy2;
            err_2 += dx2;
            point[2] += z_inc;
        }
    }
    distance++;
    
    return distance;

}



// Carmacks Fast Inverse Square Root Function
// Original Comments and Source preserved for Historical Signfigance.

float Q_rsqrt( float number )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
    
    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
    //      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
    
    return y;
}



bool IsPointOnLine(int x1, int y1, int x2, int y2, int x3, int y3)
{
    int slope, intercept;
    int minX, minY, maxX, maxY; // We don't need float precision here.
    int left, top, right, bottom; // Bounding Box For Line Segment
    int dx, dy;
    
    maxX = std::max(x1, x2);
    minX = std::min(x1, x2);
    
    maxY = std::max(y1, y2);
    minY = std::min(y1, y2);
    
    dx = maxX - minX;
    dy = maxY - minY;
    
    slope = dy / dx;
    intercept = y1 - slope * x1;
    
    left = x1;
    right = x2;
    
    top = minY;
    bottom = maxY;
    
    
    if( ((slope * x3 + intercept) > y3-1) && ((slope * x3 + intercept) < y3+1))
    {
        if( (x3 >= left-1) && (x3 <= right+1) && (y3 >= top-1) && (y3 <= bottom+1) )
        {
            return true;
        }
        else
            return false;
    }
    else
        return false;
    
}