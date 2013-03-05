//
//  GeometryFunctions.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/4/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "GeometryFunctions.h"
#include <cmath>
#include <algorithm>

int distanceXY(int x1, int y1, int x2, int y2){
    
    int maxX = std::max(x1, x2);
    int minX = std::min(x1, x2);
    
    int maxY = std::max(y1, y2);
    int minY = std::min(y1, y2);
    
    int xd = maxX-minX;
	int yd = maxY-minY;
    
	int distance = sqrt((xd*xd) + (yd*yd));
    
    return distance;
}


int distanceXYZ(int x1, int y1, int z1, int x2, int y2, int z2){
    
    int maxX = std::max(x1, x2);
    int minX = std::min(x1, x2);
    
    int maxY = std::max(y1, y2);
    int minY = std::min(y1, y2);
    
    int maxZ = std::max(z1, z2);
    int minZ = std::min(z1, z2);
    
    
    int xd = maxX-minX;
	int yd = maxY-minY;
	int zd = maxZ-minZ;
    
	int distance = sqrt((xd*xd) + (yd*yd) + (zd*zd));
    
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