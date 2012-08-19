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
    
    // We do our intitial conversion and setup of our converted render_t struct
    
    
    
    wchar_t *wstr = cMap.symbol;
    char* ascii = new char[wcslen(cMap.symbol) + 1];
    size_t size = wcstombs(ascii, wstr, sizeof (wchar_t));
    
    lMap.size = (int)size;
    int i;
    for (i = 0; i < size; i++) {
        lMap.ASCII[i] = ascii[i];
    }
    
    free(ascii);
    
    
    lMap.x = cMap.x;
    lMap.y = cMap.y;
    lMap.H = (double) cMap.H;
    lMap.S = (double) cMap.S;
    lMap.V = (double) cMap.V;
    lMap.HD = (double) cMap.HD;
    lMap.SD = (double) cMap.SD;
    lMap.VD = (double) cMap.VD;
    
    if (cMap.explored) {
        lMap.explored = 1;
    } else {
        lMap.explored = 0;
    }
    
    if (cMap.occupied) {
        lMap.occupied = 1;
    } else {
        lMap.occupied = 0;
    }
    
    if (cMap.visible) {
        lMap.visible = 1;
    } else {
        lMap.visible = 0;
    }
    
    return lMap;
}

render_t ClientMapPacker::serialToClient(s_render_t lMap)
{
    
    
    setlocale(LC_ALL, "en_US.UTF-8");
    
    render_t cMap;
    
    size_t size = lMap.size;
    wchar_t *wstr = new wchar_t[1];
    
    
    mbstowcs(wstr, lMap.ASCII, size);
    
    rMap->symbol = wstr;
    
    
    cMap.x = lMap.x;
    cMap.y = lMap.y;
    cMap.H = (float) lMap.H;
    cMap.S = (float) lMap.S;
    cMap.V = (float) lMap.V;
    cMap.HD = (float) lMap.HD;
    cMap.SD = (float) lMap.SD;
    cMap.VD = (float) lMap.VD;
    
    
    
    if (lMap.explored == 1) {
        cMap.explored = true;
    } else {
        cMap.explored = false;
    }
    
    if (lMap.occupied == 1) {
        cMap.occupied = true;
    } else {
        cMap.occupied = false;
    }
    
    if (lMap.visible == 1) {
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
    tn = tpl_map((char *)"S(ic#iiffffffiii)", &sMap, sizeof(sMap.ASCII));
    tpl_pack(tn, 0);
    tpl_dump(tn, TPL_MEM | TPL_PREALLOCD, buf, TILE_PACKET_SIZE);
    tpl_free(tn);
}

void ClientMapPacker::unpackFromNet(ClientMap *client, unsigned char *buf, GraphicsTCOD *screen)
{
    clientMap = client;
    s_render_t sMap;
    
    tn = tpl_map((char *)"S(ic#iiffffffiii)", &sMap, sizeof(sMap.ASCII));
    
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
        clientMap->cMap[cMap.x][cMap.y]->HD = cMap.HD;
        clientMap->cMap[cMap.x][cMap.y]->SD = cMap.SD;
        clientMap->cMap[cMap.x][cMap.y]->VD = cMap.VD;
        clientMap->cMap[cMap.x][cMap.y]->explored = cMap.explored;
        clientMap->cMap[cMap.x][cMap.y]->occupied = cMap.occupied;
        clientMap->cMap[cMap.x][cMap.y]->visible = cMap.visible;
        
        //screen->drawAt(cMap.x, cMap.y);

        //clientMap->refreshSquare(sMap.x, sMap.y);
        
    }
    
    
    tpl_free(tn);
    
}


