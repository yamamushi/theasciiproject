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


int renderForPlayer(Entity *target, vector<char *> *outbuf)
{
    
    int x, y;
    int size = 0;
    int offset, posx, posy;
    
    
    Entity tgt = *target;
    
    posx = MAP_WIDTH/2;//tgt.posX();
    posy = MAP_HEIGHT/2;//tgt.posY();
    
    

 
    offset = 10;

    for (x = (posx-offset); x < (posx+offset); x++) {
        for (y = (posy-offset); y < (posy+offset); y++) {
            if((x > 0) && (x < MAP_WIDTH) && (y > 0) && (y < MAP_HEIGHT))
            {
                if( tgt.fov[x][y] == true || tgt.returnCMap()->cMap[x][y]->explored)
                {   
                    
                    ClientMapPacker *packer = new ClientMapPacker();
                    char *buf = new char[TILE_PACKET_SIZE];
                    memset(buf, '.', TILE_PACKET_SIZE);
                    
                                    
                    packer->packToNet( *tgt.returnCMap()->cMap[x][y], (unsigned char*)buf);
                    
                    outbuf->push_back(buf);
                    size++;
                    delete packer;
                }
            }
            
        }
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




