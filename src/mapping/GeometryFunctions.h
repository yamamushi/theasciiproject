#pragma once
//
//  GeometryFunctions.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/4/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

int distanceXY(int posXOne, int posYOne, const int posXTwo, const int posYTwo);
int distanceXYZ(int posXOne, int posYOne, int posZOne, const int posXTwo, const int posYTwo, const int posZTwo);
float Q_rsqrt( float number);
bool IsPointOnLine(int x1, int y1, int x2, int y2, int x3, int y3);