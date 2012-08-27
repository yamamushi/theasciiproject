#include "Headers.h"

ClientMapPacker::ClientMapPacker()
{
}

void ClientMapPacker::associateClientMap(ClientMap *cMap)
{
}

s_render_t ClientMapPacker::clientToSerial(render_t source)
{
    
    
    render_t cMap = source;
    s_render_t lMap;
    
    setlocale(LC_ALL, "en_US.UTF-8");

    lMap.ASCII = (int)*cMap.symbol;
    
    lMap.x = cMap.x;
    lMap.y = cMap.y;
    
    if (cMap.visible)
    {
        lMap.H = (double) cMap.H;
        lMap.S = (double) cMap.S;
        lMap.V = (double) cMap.V;
    }
    else
    {
        lMap.H = (double) cMap.HD;
        lMap.S = (double) cMap.SD;
        lMap.V = (double) cMap.VD;
    }
    
    
    if (!cMap.explored && !cMap.visible) {
        lMap.drawMe = 0;
    }
    else
    {
        lMap.drawMe = 1;
    }
    
    return lMap;
}

render_t ClientMapPacker::serialToClient(s_render_t lMap)
{
    
    
    setlocale(LC_ALL, "en_US.UTF-8");
    
    render_t cMap;

    wchar_t *wstr = new wchar_t[2];
    
    wstr[0] = (wchar_t)lMap.ASCII;
    wstr[1] = '\0';

    rMap->symbol = wstr;
    
    
    cMap.x = lMap.x;
    cMap.y = lMap.y;
    cMap.H = (float) lMap.H;
    cMap.S = (float) lMap.S;
    cMap.V = (float) lMap.V;

    
    
    
    if (lMap.drawMe == 1) {
        cMap.explored = true;
    } else {
        cMap.explored = false;
    }
    
    
    if (lMap.drawMe == 1) {
        cMap.visible = true;
    } else {
        cMap.visible = false;
    }
    
    return cMap;
}

void ClientMapPacker::packToNet(render_t source, unsigned char *buf)
{
    tpl_node *tn; // may need to remove this declaration later
    
    // We prepare our s_render_t lMap struct for packing
    s_render_t sMap = clientToSerial(source);
    
    /* fixed-length array of s_render_t structures */
    tn = tpl_map((char *)"S(iiifffi)", &sMap);
    tpl_pack(tn, 0);
    tpl_dump(tn, TPL_MEM | TPL_PREALLOCD, buf, TILE_PACKET_SIZE);
    tpl_free(tn);
}

void ClientMapPacker::unpackFromNet(ClientMap *client, unsigned char *buf, GraphicsTCOD *screen)
{
    clientMap = client;
    s_render_t sMap;
    
    tn = tpl_map((char *)"S(iiifffi)", &sMap);
    
    if(!tpl_load(tn, TPL_MEM | TPL_EXCESS_OK, buf, TILE_PACKET_SIZE))
    {
        
        tpl_unpack(tn, 0);
        
        clientMap->refreshSquare(sMap.x, sMap.y);
                
        rMap = clientMap->cMap[sMap.x][sMap.y];
        render_t cMap = serialToClient(sMap);
        
        clientMap->cMap[cMap.x][cMap.y]->x = cMap.x;
        clientMap->cMap[cMap.x][cMap.y]->y = cMap.y;
        clientMap->cMap[cMap.x][cMap.y]->H = cMap.H;
        clientMap->cMap[cMap.x][cMap.y]->S = cMap.S;
        clientMap->cMap[cMap.x][cMap.y]->V = cMap.V;
        clientMap->cMap[cMap.x][cMap.y]->explored = cMap.explored; 
        clientMap->cMap[cMap.x][cMap.y]->visible = cMap.visible;
        
        
    }
    
    
    tpl_free(tn);
    
}


