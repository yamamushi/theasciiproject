
#include "Headers.h"



std::string make_daytime_string()
{
    time_t now = time(0);
    return ctime(&now);
};


void renderForPlayer(Entity *target, vector<char *> *outbuf)
{

    
    
    cout << "Client Map Packer initialized\n";
    
    
    int x, y;
    
    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            if ((target->fov[x][y])) {
                ClientMapPacker *packer = new ClientMapPacker();
                char *buf = new char[128];
                cout << "Unsigned char created\n";                           
               //render_t* tmp = target->returnCMap()->cMap[target->posX()][target->posY()];
                cout << "render_t assigned\n";
                packer->packToNet( *target->returnCMap()->cMap[x][y], (unsigned char*)buf);
                cout << "render packed\n";
                cout << "unsigned char buf assigned to vector\n";
                cout << "Tile packed\n";
                outbuf->push_back(buf);
                cout << "FOV size is now " << outbuf->size() << endl;
                delete packer;
                                             
            }
        }
    }
    
    for ( x = 0; x < outbuf->size(); x++)
    {
        cout << "FOV at " << x << " is currently: " << endl;
        printf("%s\n", outbuf->at((size_t)x));
    }
    
}                

    
    
