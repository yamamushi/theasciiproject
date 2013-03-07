#pragma once
//
//  HeightMap.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/7/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//
//  Our HeightMap container class. A work in progress.
//

#include <vector>



class HeightMap {
    
private:
    
    int width;
    int length;
    
    std::vector< std::vector<double> > heightMap;
    
public:
    
    HeightMap(int width, int length) : width(width), length(length){heightMap.resize(width);for(int i=0; i<width; i++){heightMap[i].resize(length);}};
    
    void AddHeightAt(int x, int y, float value){heightMap[x][y] += value;};
    float GetHeightAt(int x, int y){return heightMap[x][y];};
    void SubHeightAt(int x, int y, float value){heightMap[x][y] -= value;};
    
};