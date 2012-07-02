#include <stdlib.h>
#include "libtcod.h"
// size of the heightmap
#define HM_WIDTH 100
#define HM_HEIGHT 80
#include <math.h>
void addHill(TCOD_heightmap_t *hm,int nbHill, float baseRadius, float radiusVar, float height)  {
	int i;
	for (i=0; i<  nbHill; i++ ) {
		float hillMinRadius=baseRadius*(1.0f-radiusVar);
		float hillMaxRadius=baseRadius*(1.0f+radiusVar);
		float radius = TCOD_random_get_float(rnd,hillMinRadius, hillMaxRadius);
		float theta = TCOD_random_get_float(rnd,0.0f, 6.283185f); // between 0 and 2Pi
		float dist = TCOD_random_get_float(rnd,0.0f, (float)MIN(HM_WIDTH,HM_HEIGHT)/2 - radius);
		int xh = (int) (HM_WIDTH/2 + cos(theta) * dist);
		int yh = (int) (HM_HEIGHT/2 + sin(theta) * dist);
		TCOD_heightmap_add_hill(hm,(float)xh,(float)yh,radius,height);
	}
}
// function building the heightmap
void buildMap(TCOD_heightmap_t *hm) {
	addHill(hm,25,10,0.5,0.5);
}
// test code to print the heightmap
// to compile this file on Linux :
//  gcc hm.c -o hm -I include/ -L . -ltcod
// to compile this file on Windows/mingw32 :
//  gcc hm.c -o hm.exe -I include/ -L lib -ltcod-mingw
int main(int argc, char *argv[]) {
	int x,y;
	TCOD_heightmap_t *hm=TCOD_heightmap_new(HM_WIDTH,HM_HEIGHT);
	buildMap(hm);
	TCOD_console_init_root(HM_WIDTH,HM_HEIGHT,"height map test",false);
	for (x=0; x < HM_WIDTH; x ++ ) {
		for (y=0;y < HM_HEIGHT; y++ ) {
			float z = TCOD_heightmap_get_value(hm,x,y);
			uint8 val=(uint8)(z*255);
			TCOD_color_t c={val,val,val};
			TCOD_console_set_back(NULL,x,y,c,TCOD_BKGND_SET);
		}
	}
	TCOD_console_flush();
	TCOD_console_wait_for_keypress(true);
	return 0;
}
