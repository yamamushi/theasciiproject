
#include "Headers.h"



std::string make_daytime_string()
{
    time_t now = time(0);
    return ctime(&now);
};


int renderForPlayer(Entity *target, vector<char *> *outbuf)
{
    
    int x, y;
    int size = 0;
    
    target->refreshFov();
    int offset, posx, posy;
    posx = target->posX();
    posy = target->posY();
    offset = 11;
    
    
    for (x = (posx-offset); x < (posx+offset); x++) {
        for (y = (posy-offset); y < (posy+offset); y++) {
            if((x > 0) && (x < MAP_WIDTH) && (y > 0) && (y < MAP_HEIGHT))
            {
                if(target->fov[x][y] || target->returnCMap()->cMap[x][y]->explored)
                {
                    ClientMapPacker *packer = new ClientMapPacker();
                    char *buf = new char[TILE_PACKET_SIZE];
                    memset(buf, '.', TILE_PACKET_SIZE);
                    
                    packer->packToNet( *target->returnCMap()->cMap[x][y], (unsigned char*)buf);
                    
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




