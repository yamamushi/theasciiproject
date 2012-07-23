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
    char* ascii = new char[wcslen(cMap.symbol) + 1];
    size_t size = wcstombs(ascii, wstr, sizeof(wchar_t));
    printf("\n String check - %S \n", wstr);
    printf("size check %d\n", wcslen(cMap.symbol)+1);
    printf("value of ""size"" %d\n", size);
    //lMap.ASCII = ascii;
    lMap.size = size;
    int i;
    for (i=0; i < size; i++){
        //printf("char %d is equal to %c \n", i, ascii[i]);
        lMap.ASCII[i] = ascii[i];
    }

  // printf("\n\nTesting string %S\n", lMap.ASCII);

 //  wchar_t *dmp;
 //  mbstowcs(dmp, ascii, size);
 //  printf("\n after conversion %S\n", dmp);




    printf("symbol char before compression = %c \n", cMap.symbol);
    printf("symbol string before compression is = %S \n", cMap.symbol);
    printf ("symbol is %u big.\n",(unsigned)sizeof(cMap.symbol));
    printf ("symbol is %u long.\n",(unsigned)wcslen(cMap.symbol));
    printf ("symbol is %u big.\n",(unsigned)sizeof(cMap.symbol));
    printf("wchar_t is %u big.\n\n", (unsigned)sizeof(wchar_t));








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

    size_t size = lMap.size;
    const char * ascii = lMap.ASCII;
    char tmp[8];

    strncpy( tmp, lMap.ASCII, size);
    printf("if our char copied properly we should have %s\n", tmp);
    wchar_t wstr[1];

    //mbstowcs( dst, ascii, size);
    mbstowcs( cMap.symbol, lMap.ASCII, size);
    printf("if this went right.. %S\n", cMap.symbol);
    //rMap->symbol = cMap.symbol;


   //  wchar_t destination[wcslen(cMap.symbol)];
   //wchar_t * return_string;
   //return_string = wcscpy(cMap.symbol, wstr);
   //printf("return_string is now %S\n", return_string);
   //printf("cmap symbol is now %S\n", cMap.symbol);
   // return_string = wcscpy(cMap.symbol, destination);




    printf("\n\n ASCII char* after transfer = %c \n", lMap.ASCII);
   // printf("symbol string after compression is = %S \n", cMap.symbol);
    //printf ("symbol is %u big.\n",(unsigned)sizeof(lMap.ASCII));
    //printf ("symbol is %u long.\n",(unsigned)mblen(lMap.ASCII, sizeof(wchar_t)));
    //printf ("symbol is %u long.\n",(unsigned)wcslen(lMap.ASCII));
    //printf ("symbol is %u big.\n",(unsigned)sizeof(lMap.ASCII));
    //printf("wchar_t is %u big.\n", (unsigned)sizeof(wchar_t));


    cMap.x = lMap.x;
    printf("cMap.x is now %d\n", cMap.x);
    cMap.y = lMap.y;
    printf("cMap.y is now %d\n", cMap.y);
    cMap.H = (float)lMap.H;
    cMap.S = (float)lMap.S;
    cMap.V = (float)lMap.V;
    cMap.HD = (float)lMap.HD;
    cMap.SD = (float)lMap.SD;
    cMap.VD = (float)lMap.VD;



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



void ClientMapPacker::packToNet(render_t source, unsigned char *buf){
tpl_node *tn;

    // We prepare our s_render_t lMap struct for packing
    s_render_t sMap = clientToSerial(source);

    /* fixed-length array of s_render_t structures */
    tn = tpl_map("S(ic#iiffffffiii)", &sMap, sizeof(sMap.ASCII));
    //tn = tpl_map("S(ic#iiffffffiii)", &sMap, );
    tpl_pack(tn, 0);
    tpl_dump(tn, TPL_MEM|TPL_PREALLOCD, buf, 128);
    tpl_free(tn);
}

void ClientMapPacker::unpackFromNet(ClientMap *dest, unsigned char *buf)
{

    //tpl_node *tn;
    s_render_t sMap;

    clientMap = dest;

    tn = tpl_map("S(ic#iiffffffiii)", &sMap, sizeof(sMap.ASCII));
    printf("Buffer has been mapped\n");
    tpl_load(tn, TPL_MEM|TPL_EXCESS_OK, buf, 128);
    printf("Buffer Loaded\n");
    tpl_unpack( tn, 0);
    printf("Buffer Unpack Attempted\n");

    printf("\n\n ... Attempting to convert Struct \n\n");

    rMap = dest->cMap[sMap.x][sMap.y];

    render_t cMap = serialToClient(sMap);

    printf("Struct Converted\n\n");


    //dest->importSquare(cMap.x, cMap.y, &cMap);
    printf("symbol for here is %S\n", cMap.symbol);

    //return_string = wcscpy( *dest->cMap[cMap.x][cMap.y]->symbol, cMap.symbol);

    dest->cMap[cMap.x][cMap.y]->symbol = cMap.symbol;
    //printf("symbol for here after updated: %S\n", dest->cMap[cMap.x-1][cMap.y-1]->symbol);





    dest->cMap[cMap.x][cMap.y]->x = cMap.x;
    dest->cMap[cMap.x][cMap.y]->y = cMap.y;

    wchar_t *return_string;
    return_string = wcscpy(dest->cMap[cMap.x][cMap.y]->symbol, cMap.symbol);
    printf("symbol for here now is %S\n", dest->cMap[cMap.x][cMap.y]->symbol);

    dest->cMap[cMap.x][cMap.y]->H = cMap.H;
    dest->cMap[cMap.x][cMap.y]->S = cMap.S;
    dest->cMap[cMap.x][cMap.y]->V = cMap.V;
    dest->cMap[cMap.x][cMap.y]->HD = cMap.HD;
    dest->cMap[cMap.x][cMap.y]->SD = cMap.SD;
    dest->cMap[cMap.x][cMap.y]->VD = cMap.VD;
    dest->cMap[cMap.x][cMap.y]->explored = cMap.explored;
    dest->cMap[cMap.x][cMap.y]->occupied = cMap.occupied;
    dest->cMap[cMap.x][cMap.y]->visible = cMap.visible;

    //tpl_free(tn);

}


