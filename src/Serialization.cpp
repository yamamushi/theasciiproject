#include "headers.h"

ClientMapPacker::ClientMapPacker()
{

    tpl_node *tn;

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
    printf("\n String check - %S \n", wstr);
    printf("size check %d\n", wcslen(cMap.symbol) + 1);
    printf("value of ""size"" %d\n", size);
    //lMap.ASCII = ascii;
    lMap.size = size;
    int i;
    for (i = 0; i < size; i++) {
        lMap.ASCII[i] = ascii[i];
    }




    printf("symbol char before compression = %c \n", cMap.symbol);
    printf("symbol string before compression is = %S \n", cMap.symbol);
    printf("symbol is %u big.\n", (unsigned) sizeof (cMap.symbol));
    printf("symbol is %u long.\n", (unsigned) wcslen(cMap.symbol));
    printf("symbol is %u big.\n", (unsigned) sizeof (cMap.symbol));
    printf("wchar_t is %u big.\n\n", (unsigned) sizeof (wchar_t));
    printf("symbol char after conversion = %c \n", lMap.ASCII);
    printf("symbol string after conversion is = %S \n", lMap.ASCII);
    printf("symbol is %u big.\n", (unsigned) sizeof (lMap.ASCII));
    printf("symbol is %u big.\n", (unsigned) sizeof (lMap.ASCII));


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
    //const char * ascii = lMap.ASCII;
    //char tmp[8];

    //strncpy( tmp, lMap.ASCII, size);
    //printf("if our char copied properly we should have %s\n", tmp);
    wchar_t *wstr = new wchar_t[1];

    mbstowcs(wstr, lMap.ASCII, size);
    rMap->symbol = wstr;
    //printf("after assignment %S\n", clientMap->cMap[cMap.x][cMap.y]->symbol);


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
        printf("explored = true\n");
    } else {
        cMap.explored = false;
        printf("explored = false\n");
    }

    if (lMap.occupied == 1) {
        cMap.occupied = true;
        printf("occupied = true\n");
    } else {
        cMap.occupied = false;
        printf("occupied = false\n");
    }

    if (lMap.visible == 1) {
        cMap.visible = true;
        printf("visible = true\n");
    } else {
        cMap.visible = false;
        printf("visible = false\n");
    }

    return cMap;
}

void ClientMapPacker::packToNet(render_t source, unsigned char *buf)
{
    tpl_node *tn; // may need to remove this declaration later

    // We prepare our s_render_t lMap struct for packing
    s_render_t sMap = clientToSerial(source);

    /* fixed-length array of s_render_t structures */
    tn = tpl_map("S(ic#iiffffffiii)", &sMap, sizeof (sMap.ASCII));
    tpl_pack(tn, 0);
    tpl_dump(tn, TPL_MEM | TPL_PREALLOCD, buf, 128);
    tpl_free(tn);
}

void ClientMapPacker::unpackFromNet(ClientMap *dest, unsigned char *buf)
{

    s_render_t sMap;

    clientMap = dest;

    tn = tpl_map("S(ic#iiffffffiii)", &sMap, sizeof (sMap.ASCII));
    printf("Buffer has been mapped\n");
    tpl_load(tn, TPL_MEM | TPL_EXCESS_OK, buf, 128);
    printf("Buffer Loaded\n");
    tpl_unpack(tn, 0);
    printf("Buffer Unpack Attempted\n");

    printf("\n\n ... Attempting to convert Struct \n\n");

    rMap = dest->cMap[sMap.x][sMap.y];

    render_t cMap = serialToClient(sMap);
    printf("Struct Converted\n\n");
    printf("symbol for %d,%d is: %S\n", sMap.x, sMap.y, rMap->symbol);

    dest->cMap[cMap.x][cMap.y]->x = cMap.x;
    dest->cMap[cMap.x][cMap.y]->y = cMap.y;
    dest->cMap[cMap.x][cMap.y]->H = cMap.H;
    dest->cMap[cMap.x][cMap.y]->S = cMap.S;
    dest->cMap[cMap.x][cMap.y]->V = cMap.V;
    dest->cMap[cMap.x][cMap.y]->HD = cMap.HD;
    dest->cMap[cMap.x][cMap.y]->SD = cMap.SD;
    dest->cMap[cMap.x][cMap.y]->VD = cMap.VD;
    dest->cMap[cMap.x][cMap.y]->explored = cMap.explored;
    dest->cMap[cMap.x][cMap.y]->occupied = cMap.occupied;
    dest->cMap[cMap.x][cMap.y]->visible = cMap.visible;

}


