#include "headers.h"


ClientMapPacker::ClientMapPacker(){

        tpl_node *tn;

}

s_render_t ClientMapPacker::clientToSerial(render_t source){


    render_t cMap = source;
    s_render_t lMap;

    // We do our intitial conversion and setup of our converted render_t struct
    //int x = cMap.x;
   // int y = cMap.y;

    setlocale(LC_ALL, "en_US.UTF-8");

    wchar_t *wstr = cMap.symbol;
    char *ascii = new char[wcslen(cMap.symbol) + 1];
    wcstombs(ascii, cMap.symbol, sizeof (wchar_t));

    printf("\n String check - %S \n", (wchar_t *)ascii);





    printf("symbol char before compression = %c \n", cMap.symbol);
    printf("symbol string before compression is = %S \n", cMap.symbol);
    printf ("symbol is %u big.\n",(unsigned)sizeof(cMap.symbol));
    printf ("symbol is %u long.\n",(unsigned)wcslen(cMap.symbol));
    printf ("symbol is %u big.\n",(unsigned)sizeof(cMap.symbol));
    printf("wchar_t is %u big.\n\n", (unsigned)sizeof(wchar_t));






    lMap.ASCII = ascii;

    printf("symbol char after conversion = %c \n", lMap.ASCII);
    printf("symbol string after conversion is = %S \n", lMap.ASCII);
    printf ("symbol is %u big.\n",(unsigned)sizeof(lMap.ASCII));
    ///printf ("symbol is %u long.\n",(unsigned)mblen(lMap.ASCII, sizeof(wchar_t)));
    printf ("symbol is %u big.\n",(unsigned)sizeof(lMap.ASCII));
    //printf("int value of char* after conversion is %d\n", ()lMap.ASCII);



    // we would use c# to pack a char[];

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

render_t ClientMapPacker::serialToClient(s_render_t lMap){


    setlocale(LC_ALL, "en_US.UTF-8");

    //s_render_t lMap = source;
    render_t cMap;


   // char *ascii = lMap.ASCII;
    //wchar_t *wstr;
   // mbstowcs(wstr, ascii, sizeof(wchar_t));

    printf("ASCII char* after transfer = %c \n", lMap.ASCII);
    //printf("symbol string after compression is = %s \n", lMap.ASCII);
    //printf ("symbol is %u big.\n",(unsigned)sizeof(lMap.ASCII));
    //printf ("symbol is %u long.\n",(unsigned)mblen(lMap.ASCII, sizeof(wchar_t)));
    //printf ("symbol is %u long.\n",(unsigned)wcslen(lMap.ASCII));
    //printf ("symbol is %u big.\n",(unsigned)sizeof(lMap.ASCII));
    //printf("wchar_t is %u big.\n", (unsigned)sizeof(wchar_t));

    //mbstowcs(wstr, ascii, sizeof(wchar_t));
    //printf("strlen of char* after transfer is %d", strlen(lMap.ASCII));

    cMap.symbol = L"\uFFF8";//source.ASCII;
    cMap.x = lMap.x;
    printf("lMap.x is now %d\n", lMap.x);
    cMap.y = lMap.y;
    printf("lMap.y is now %d\n", lMap.y);
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

    return cMap;

}



void ClientMapPacker::packToNet(render_t source, unsigned char *buf){

    // We prepare our s_render_t lMap struct for packing
    s_render_t sMap = clientToSerial(source);

    /* fixed-length array of s_render_t structures */
    tn = tpl_map("S(c#iiffffffiii)", &sMap, sizeof(sMap.ASCII));
    tpl_pack(tn, 0);
    tpl_dump(tn, TPL_MEM|TPL_PREALLOCD, buf, 128);

}

void ClientMapPacker::unpackFromNet(ClientMap *dest, unsigned char *buf)
{

    s_render_t sMap;

    tn = tpl_map("S(c#iiffffffiii)", &sMap, sizeof(sMap.ASCII));
    printf("Buffer has been mapped\n");
    tpl_load(tn, TPL_MEM|TPL_EXCESS_OK, buf, 128);
    printf("Buffer Loaded\n");
    tpl_unpack( tn, 0);
    printf("Buffer Unpack Attempted\n");

    printf("\n\n ... Attempting to convert Struct \n\n");

    render_t cMap = serialToClient(sMap);

    printf("Struct Converted\n\n");


    dest->cMap[sMap.x][sMap.y].symbol = cMap.symbol;
    dest->cMap[sMap.x][sMap.y].x = cMap.x;
    dest->cMap[sMap.x][sMap.y].y = cMap.y;
    dest->cMap[sMap.x][sMap.y].H = cMap.H;
    dest->cMap[sMap.x][sMap.y].S = cMap.S;
    dest->cMap[sMap.x][sMap.y].V = cMap.V;
    dest->cMap[sMap.x][sMap.y].HD = cMap.HD;
    dest->cMap[sMap.x][sMap.y].SD = cMap.SD;
    dest->cMap[sMap.x][sMap.y].VD = cMap.VD;
    dest->cMap[sMap.x][sMap.y].explored = cMap.explored;
    dest->cMap[sMap.x][sMap.y].occupied = cMap.occupied;
    dest->cMap[sMap.x][sMap.y].visible = cMap.visible;
//    tpl_free(tn);

}


