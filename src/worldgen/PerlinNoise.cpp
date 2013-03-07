//
//  PerlinNoise.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/6/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//
//  Various Perlin Noise Functions
//

#include "PerlinNoise.h"
#include "SimplexNoise.h"
#include "../mapping/Tile.h"
#include "../mapping/TileMap.h"
#include "../mapping/WorldMap.h"
#include "../mapping/GeometryFunctions.h"
#include "../mapping/HeightMap.h"
#include <cmath>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "../utils/IntToUTF8String.h"





inline double FindPerlinNoise(int x){
    
    x = (x<<13) ^ x;
    return (double)( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0);
    
}


inline double FindPerlinNoise(double x,double y){
    
    int n=(int)x+(int)y*57;
    n=(n<<13)^n;
    int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
    return 1.0-((double)nn/1073741824.0);
    
}



inline double InterpolatePerlin(double a,double b,double x){
    
    double ft=x * 3.1415927;
    double f=(1.0-cos(ft))* 0.5;
    return a*(1.0-f)+b*f;
    
}



double noise(double x,double y){
    
    double floorx=(double)((int)x);
    double floory=(double)((int)y);
    double s,t,u,v;
    
    s=FindPerlinNoise(floorx,floory);
    t=FindPerlinNoise(floorx+1,floory);
    u=FindPerlinNoise(floorx,floory+1); //Get the surrounding pixels to calculate the transition.
    v=FindPerlinNoise(floorx+1,floory+1);
    
    double int1=InterpolatePerlin(s,t,x-floorx); //Interpolate between the values.
    
    double int2=InterpolatePerlin(u,v,x-floorx); //Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
    
    return InterpolatePerlin(int1,int2,y-floory); //Here we use y-floory, to get the 2nd dimension.
    
}


void TileNoiseHeightmap(TileMap *tileMap, double zoom, double persistence, double range, int octaves){
    
    int w = tileMap->getWidth();
    int h = tileMap->getLength();
    
    if(octaves < 2)
        octaves=2;
    
    boost::shared_ptr<HeightMap> hMap(new HeightMap(w, h));
    //double normalize = sqrt(w*h);

    // We run through this series of functions twice to "normalize" our heightmap.
    
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            
            double getnoise = 0;
            for(int a=0;a<octaves-1;a++){ //This loops trough the octaves.
                
                double frequency = pow(2,a); //This increases the frequency with every loop of the octave.
                double amplitude = pow(persistence,a); //This decreases the amplitude with every loop of the octave.
                
                
                //getnoise += noise(((double)x)*frequency/zoom,((double)y)/zoom*frequency)*amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude
                
                getnoise += (noise( ((double)(x)*frequency)/zoom, ((double)(y)/zoom*frequency)*amplitude) * (w-x) * (h-y));
                getnoise += (noise( ((double)(x-w)*frequency)/zoom, ((double)(y)/zoom*frequency)*amplitude) * (x) * (h-y));
                getnoise += (noise( ((double)(x-w)*frequency)/zoom, ((double)(y-h)/zoom*frequency)*amplitude) * (x) * (y));
                getnoise += (noise( ((double)(x)*frequency)/zoom, ((double)(y-h)/zoom*frequency)*amplitude) * (w-x) * (y));
                getnoise = getnoise / (w*h);  
                
            }
            
            //int mod = (int)(getnoise*(range/2))+(range/2);
            hMap->AddHeightAt(x, y, getnoise);
            
        }
    }
    
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            /*
            double getnoise = 0;
            for(int a=0;a<octaves-1;a++){ //This loops trough the octaves.
                
                double frequency = pow(2,a); //This increases the frequency with every loop of the octave.
                double amplitude = pow(persistence,a); //This decreases the amplitude with every loop of the octave.

                getnoise += (noise( ((double)(x)*frequency)/normalize, ((double)(y)/normalize*frequency)*amplitude) * (w-x) * (h-y));
                getnoise += (noise( ((double)(x-w)*frequency)/normalize, ((double)(y)/normalize*frequency)*amplitude) * (x) * (h-y));
                getnoise += (noise( ((double)(x-w)*frequency)/normalize, ((double)(y-h)/normalize*frequency)*amplitude) * (x) * (y));
                getnoise += (noise( ((double)(x)*frequency)/normalize, ((double)(y-h)/normalize*frequency)*amplitude) * (w-x) * (y));
                getnoise = getnoise / (w*h);
                
            }
            if(distanceXY(x, y, w/2, h/2) < w/4){
                //int mod = (int)(getnoise*(range/2))+(range/2);
                hMap->AddHeightAt(x, y, getnoise);
            } */
            
            int finalHeight = (int)(hMap->GetHeightAt(x, y)*(range/2))+(range/2);
            
            if(finalHeight>(range))
                finalHeight = range;
            if(finalHeight<0)
                finalHeight = 0;
            
            finalHeight = finalHeight + 0x2581;
            //2581 - 2589
            //tileMap->getTilePtr(x, y)->setSymbol(std::to_string(heightMap));
            tileMap->getTilePtr(x, y)->setSymbol(IntToUTF8String(finalHeight));
        }
    }
    
}



void WorldMapHeightMap(WorldMap *worldMap, double zoom, double persistence, double range, int octaves){
    
    int w = worldMap->returnWorldWidth();
    int h = worldMap->returnWorldLength();
    
    if(octaves < 2)
        octaves=2;
    
    boost::shared_ptr<HeightMap> hMap(new HeightMap(w, h));
    //double normalize = sqrt(w*h);
    
    // We run through this series of functions twice to "normalize" our heightmap.
    
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            
            double getnoise = 0;
            for(int a=0;a<octaves-1;a++){ //This loops trough the octaves.
                
                double frequency = pow(2,a); //This increases the frequency with every loop of the octave.
                double amplitude = pow(persistence,a); //This decreases the amplitude with every loop of the octave.
                
                
                //getnoise += noise(((double)x)*frequency/zoom,((double)y)/zoom*frequency)*amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude
                
                getnoise += (noise( ((double)(x)*frequency)/zoom, ((double)(y)/zoom*frequency)*amplitude) * (w-x) * (h-y));
                getnoise += (noise( ((double)(x-w)*frequency)/zoom, ((double)(y)/zoom*frequency)*amplitude) * (x) * (h-y));
                getnoise += (noise( ((double)(x-w)*frequency)/zoom, ((double)(y-h)/zoom*frequency)*amplitude) * (x) * (y));
                getnoise += (noise( ((double)(x)*frequency)/zoom, ((double)(y-h)/zoom*frequency)*amplitude) * (w-x) * (y));
                getnoise = getnoise / (w*h);
                
            }
            
            //int mod = (int)(getnoise*(range/2))+(range/2);
            hMap->AddHeightAt(x, y, getnoise);
            
        }
    }
    
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            /*
             double getnoise = 0;
             for(int a=0;a<octaves-1;a++){ //This loops trough the octaves.
             
             double frequency = pow(2,a); //This increases the frequency with every loop of the octave.
             double amplitude = pow(persistence,a); //This decreases the amplitude with every loop of the octave.
             
             getnoise += (noise( ((double)(x)*frequency)/normalize, ((double)(y)/normalize*frequency)*amplitude) * (w-x) * (h-y));
             getnoise += (noise( ((double)(x-w)*frequency)/normalize, ((double)(y)/normalize*frequency)*amplitude) * (x) * (h-y));
             getnoise += (noise( ((double)(x-w)*frequency)/normalize, ((double)(y-h)/normalize*frequency)*amplitude) * (x) * (y));
             getnoise += (noise( ((double)(x)*frequency)/normalize, ((double)(y-h)/normalize*frequency)*amplitude) * (w-x) * (y));
             getnoise = getnoise / (w*h);
             
             }
             if(distanceXY(x, y, w/2, h/2) < w/4){
             //int mod = (int)(getnoise*(range/2))+(range/2);
             hMap->AddHeightAt(x, y, getnoise);
             } */
            
            int finalHeight = (int)(hMap->GetHeightAt(x, y)*(range/2))+(range/2);
            
            if(finalHeight>(range))
                finalHeight = range;
            if(finalHeight<0)
                finalHeight = 0;
            
            finalHeight = finalHeight + 0x2581;
            //2581 - 2589
            //tileMap->getTilePtr(x, y)->setSymbol(std::to_string(heightMap));
            worldMap->AltGetTileAt(x, y, 0)->setSymbol(IntToUTF8String(finalHeight));
        }
    }
    worldMap->getTileAt(13, 17, 0)->setSymbol("F");
}

