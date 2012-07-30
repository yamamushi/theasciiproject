
#include "Headers.h"



std::string make_daytime_string()
{
    time_t now = time(0);
    return ctime(&now);
};


void renderForPlayer(Entity *target, vector<char *> *outbuf)
{
    
    
    int x, y;
    
    while(outbuf->size() < 128)
    {
        for (x = 0; x < MAP_WIDTH; x++) {
            for (y = 0; y < MAP_HEIGHT; y++) {
                 if ((target->fov[x][y]) || (target->returnCMap()->cMap[x][y]->explored) ){
                    ClientMapPacker *packer = new ClientMapPacker();
                    char *buf = new char[128];
                    
                    packer->packToNet( *target->returnCMap()->cMap[x][y], (unsigned char*)buf);
                   
                    outbuf->push_back(buf);
                    delete packer;
                    
                }
            }
        }
    }
    
    /* for ( x = 0; x < outbuf->size(); x++)
     {
     cout << "FOV at " << x << " is currently: " << endl;
     printf("%s\n", outbuf->at((size_t)x));
     } */
    
}                



