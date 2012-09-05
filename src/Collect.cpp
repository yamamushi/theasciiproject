#include <string>
#include <vector>

#include "Entities.h"
#include "ClientMap.h"
#include "Serialization.h"

using std::vector;


std::string make_daytime_string()
{
    time_t now = time(0);
    return ctime(&now);
};


int renderForPlayer(Entity *target, vector<char *> *outbuf, ClientMap *savedMap)
{
    
    int x, y;
    int size = 0;
    int offset, posx, posy;
    
    
    Entity tgt = *target;
    
    
    
    posx = MAP_WIDTH/2;//tgt.posX();
    posy = MAP_HEIGHT/2;//tgt.posY();
    
    
    
    
   // offset = 12;
    
    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
           // if((x > 0) && (x < MAP_WIDTH) && (y > 0) && (y < MAP_HEIGHT))
           // {
                if(tgt.returnCMap()->cMap[x][y]->explored)
             //   {
               //     if(savedMap->cMap[x][y]->x != tgt.returnCMap()->cMap[x][y]->x || savedMap->cMap[x][y]->y != tgt.returnCMap()->cMap[x][y]->y)
               //     {
                    if( (tgt.returnCMap()->cMap[x][y]->x == posx && tgt.returnCMap()->cMap[x][y]->y < 12) || tgt.returnCMap()->cMap[x][y]->y == posy|| (savedMap->cMap[x][y]->H != tgt.returnCMap()->cMap[x][y]->H) || (savedMap->cMap[x][y]->S != tgt.returnCMap()->cMap[x][y]->S) || (savedMap->cMap[x][y]->V != tgt.returnCMap()->cMap[x][y]->V) || (savedMap->cMap[x][y]->HD != tgt.returnCMap()->cMap[x][y]->HD) || (savedMap->cMap[x][y]->SD != tgt.returnCMap()->cMap[x][y]->SD) || (savedMap->cMap[x][y]->VD != tgt.returnCMap()->cMap[x][y]->VD) || (savedMap->cMap[x][y]->symbol != tgt.returnCMap()->cMap[x][y]->symbol) || (savedMap->cMap[x][y]->visible != tgt.returnCMap()->cMap[x][y]->visible) || (savedMap->cMap[x][y]->blocked != tgt.returnCMap()->cMap[x][y]->blocked) || (savedMap->cMap[x][y]->occupied != tgt.returnCMap()->cMap[x][y]->occupied) )
                    {
                       // tgt.returnCMap()->cMap[x][y]->x = savedMap->cMap[x][y]->x;
                       // tgt.returnCMap()->cMap[x][y]->y = savedMap->cMap[x][y]->y;
                        
                        savedMap->cMap[x][y]->H = tgt.returnCMap()->cMap[x][y]->H;
                        savedMap->cMap[x][y]->S = tgt.returnCMap()->cMap[x][y]->S;
                        savedMap->cMap[x][y]->V = tgt.returnCMap()->cMap[x][y]->V;
                        savedMap->cMap[x][y]->HD = tgt.returnCMap()->cMap[x][y]->HD;
                        savedMap->cMap[x][y]->SD = tgt.returnCMap()->cMap[x][y]->SD;
                        savedMap->cMap[x][y]->VD = tgt.returnCMap()->cMap[x][y]->VD;
                        savedMap->cMap[x][y]->symbol = tgt.returnCMap()->cMap[x][y]->symbol;
                        savedMap->cMap[x][y]->visible = tgt.returnCMap()->cMap[x][y]->visible;
                        savedMap->cMap[x][y]->explored = tgt.returnCMap()->cMap[x][y]->explored;
                        savedMap->cMap[x][y]->blocked = tgt.returnCMap()->cMap[x][y]->blocked;
                        savedMap->cMap[x][y]->occupied = tgt.returnCMap()->cMap[x][y]->occupied;
                        
                        
                        ClientMapPacker *packer = new ClientMapPacker();
                        char *buf = new char[TILE_PACKET_SIZE];
                        memset(buf, '.', TILE_PACKET_SIZE);
                        
                        
                        packer->packToNet( *tgt.returnCMap()->cMap[x][y], (unsigned char*)buf);
                        
                        outbuf->push_back(buf);
                        size++;
                        delete packer;
                    }
                    
              //      }
             //   }
           // }
            
        }
    }
    
    if(size == 0)
    {
       
        
        ClientMapPacker *packer = new ClientMapPacker();
        char *buf = new char[TILE_PACKET_SIZE];
        memset(buf, '.', TILE_PACKET_SIZE);
        
        
        packer->packToNet( *tgt.returnCMap()->cMap[posx][posy], (unsigned char*)buf);
        
        outbuf->push_back(buf);
        size++;
        delete packer;
    }
    
    return size;
}





bool pointInSquare( int x, int y, int n)
{
    
    
    return (y <= n - x &&
            y >= x - n &&
            y <= x + n &&
            y>= -(x + n));
    
}


bool isInteger(const std::string & s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
    
    char * p ;
    strtol(s.c_str(), &p, 10) ;
    
    return (*p == 0) ;
}




