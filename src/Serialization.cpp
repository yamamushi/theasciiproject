#include "headers.h"

s_render_t ClientMapPacker::clientToSerial(render_t source){


    render_t cMap = source;
    s_render_t lMap;

    // We do our intitial conversion and setup of our converted render_t struct
    int x = cMap.x;
    int y = cMap.y;

    wchar_t *wstr = cMap.symbol;
    char *ascii = new char[wcslen(wstr) + 1];
    wcstombs(ascii, wstr, sizeof(wchar_t));

    printf("ascii before compression = %c \n", ascii);
    printf("wstr before compression is = %S \n", wstr);
    printf ("ascii is %u big.\n",(unsigned)sizeof(ascii));
    printf ("ascii is %u long.\n",(unsigned)mblen(ascii, sizeof(wchar_t)));
    printf ("wstr is %u long.\n",(unsigned)wcslen(wstr));
    printf ("wstr is %u big.\n",(unsigned)sizeof(wstr));


    // we would use c# to pack a char[];

    lMap.ASCII = ascii;

    lMap.x = cMap.x;
    lMap.y = cMap.y;
    lMap.H = (double)cMap.H;
    lMap.S = (double)cMap.S;
    lMap.V = (double)cMap.V;
    lMap.HD = (double)cMap.HD;
    lMap.SD = (double)cMap.SD;
    lMap.VD = (double)cMap.VD;

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

render_t ClientMapPacker::serialToClient(s_render_t source){

    s_render_t lMap = source;
    render_t cMap;

    char *ascii = source.ASCII;
    wchar_t *wstr;
    mbstowcs(wstr, ascii, sizeof(wchar_t));

    printf("ascii after decompression is = %c \n", source.ASCII);
    printf("wstr after decompression is = %S \n", wstr);
    printf ("ascii is %u big.\n",(unsigned)sizeof(ascii));
    printf ("ascii is %u long.\n",(unsigned)mblen(ascii, sizeof(wchar_t)));
    printf ("wstr is %u long.\n",(unsigned)wcslen(wstr));
    printf ("wstr is %u big.\n",(unsigned)sizeof(wstr));



    // we would use c# to pack a char[];

    cMap.symbol = wstr;
    cMap.x = (float)lMap.x;
    cMap.y = (float)lMap.y;
    cMap.H = (float)lMap.H;
    cMap.S = (float)lMap.S;
    cMap.V = (float)lMap.V;
    cMap.HD = (float)lMap.HD;
    cMap.SD = (float)lMap.SD;
    cMap.VD = (float)lMap.VD;



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

    printf("lMap visibility is %d", lMap.visible);
    return cMap;

}



void ClientMapPacker::packToNet(render_t source, unsigned char *buf){

    // We prepare our s_render_t lMap struct for packing
    s_render_t sMap = clientToSerial(source);

    /* fixed-length array of s_render_t structures */
    tn = tpl_map("S(c#iiffffffiii)", &sMap, 8);
    tpl_pack(tn, 0);
    tpl_dump(tn, TPL_MEM|TPL_PREALLOCD, buf, 1024);

}

void ClientMapPacker::unpackFromNet(ClientMap *dest, unsigned char *buf)
{

    s_render_t csMap;

    tn = tpl_map("S(c#iiffffffiii)", &csMap, 8);
    tpl_load(tn, TPL_MEM|TPL_EXCESS_OK, buf, 1024);
    tpl_unpack( tn, 0);

    render_t cMap = serialToClient(csMap);

    dest->cMap[csMap.x][csMap.y].symbol = cMap.symbol;
    dest->cMap[csMap.x][csMap.y].x = cMap.x;
    dest->cMap[csMap.x][csMap.y].y = cMap.y;
    dest->cMap[csMap.x][csMap.y].H = cMap.H;
    dest->cMap[csMap.x][csMap.y].S = cMap.S;
    dest->cMap[csMap.x][csMap.y].V = cMap.V;
    dest->cMap[csMap.x][csMap.y].HD = cMap.HD;
    dest->cMap[csMap.x][csMap.y].SD = cMap.SD;
    dest->cMap[csMap.x][csMap.y].VD = cMap.VD;
    dest->cMap[csMap.x][csMap.y].explored = cMap.explored;
    dest->cMap[csMap.x][csMap.y].occupied = cMap.occupied;
    dest->cMap[csMap.x][csMap.y].visible = cMap.visible;

}