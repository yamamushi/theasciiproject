
#include "Headers.h"



std::string make_daytime_string()
{
    time_t now = time(0);
    return ctime(&now);
};


void renderForPlayer(Entity *target, vector<char *> *outbuf)
{
    
    
    int x, y;
    
    
    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            if (target->fov[x][y])
            {
                ClientMapPacker *packer = new ClientMapPacker();
                char *buf = new char[128];
                
                packer->packToNet( *target->returnCMap()->cMap[x][y], (unsigned char*)buf);
                
                outbuf->push_back(buf);
                
                delete packer;
                
            }
        }
    }
    
}



