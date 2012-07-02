#include "libtcod.hpp"
// size of the heightmap
#define HM_WIDTH 100
#define HM_HEIGHT 80
#include <math.h>
void addHill(TCODHeightMap *hm,int nbHill, float baseRadius, float radiusVar, float height)  {
	for (int i=0; i<  nbHill; i++ ) {
		float hillMinRadius=baseRadius*(1.0f-radiusVar);
		float hillMaxRadius=baseRadius*(1.0f+radiusVar);
		TCODRandom *myRandom = new TCODRandom();
		float radius = myRandom->getFloat(hillMinRadius, hillMaxRadius);
		float theta = myRandom->getFloat(0.0f, 6.283185f); // between 0 and 2Pi
		float dist = myRandom->getFloat(0.0f, (float)MIN(HM_WIDTH,HM_HEIGHT)/2 - radius);
		int xh = (int) (HM_WIDTH/2 + cos(theta) * dist);
		int yh = (int) (HM_HEIGHT/2 + sin(theta) * dist);
		hm->addHill((float)xh,(float)yh,radius,height);
	}
}
// function building the heightmap
void buildMap(TCODHeightMap *hm) {
	addHill(hm,25,10,0.5,0.5);
}
// test code to print the heightmap
// to compile this file on Linux :
//  g++ hm.cpp -o hm -I include/ -L . -ltcod -ltcod++
// to compile this file on Windows/mingw32 :
//  g++ hm.cpp -o hm.exe -I include/ -L lib -ltcod-mingw
int main(int argc, char *argv[]) {
	TCODHeightMap hm(HM_WIDTH,HM_HEIGHT);
	buildMap(&hm);
	TCODConsole::initRoot(HM_WIDTH,HM_HEIGHT,"height map test",false);
	for (int x=0; x < HM_WIDTH; x ++ ) {
		for (int y=0;y < HM_HEIGHT; y++ ) {
			float z = hm.getValue(x,y);
			uint8 val=(uint8)(z*255);
			TCODColor c(val,val,val);
			TCODConsole::root->setCharBackground(x,y,c);
		}
	}
	TCODConsole::root->flush();
	TCODConsole::waitForKeypress(true);
	return 0;
}
