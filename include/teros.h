/**************************************************
* TEROS ENGINE BETA 0.0.2.7                       *
*                                                 *
* Author: Kyle L. Miskell                         *
* Last Modified: 22 December 2013                 *
*                                                 *
* Description: An ASCII console graphics engine.  *
**************************************************/

#ifndef TEROS_H
#define TEROS_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

#define SCRHEIGHT 50
#define SCRWIDTH 78

#define PI 3.14159265358979323846264338327950288419716939937510f

using namespace std;

int roundnum (double);

double dist (double, double, double, double, double, double);
double findang (double, double);

string doubletostring (double);

class Window
{
	private:
		std::vector <char> content;
		std::vector <bool> cursors;
		std::vector <string> activetext;

		int width;
		int height;
		int tlposx;
		int tlposy;

		char cursorchar;
		char fill;
		char atxtid;
		char cursorid;
		char transparency;

	public:
		Window ();

		void loadfromfile (string);
		void loadfromvector (std::vector <char>, int);
		void modcontent (char, int, int);
		void tlrepos (int, int);
		void setcursor (int, bool);
		void setactivetext (int, string);
		void setfill (char);
		void setcursorchar (char);
		void setatxtid (char);
		void setcursorid (char);
		void settranspid (char);

		bool putcursor (int);

		char readcontent (int, int);
		char putfill ();
		char putcursorchar ();
		char putatxtid ();
		char putcursorid ();
		char puttranspid ();

		int putwidth ();
		int putheight ();
		int puttlposx ();
		int puttlposy ();
		int cursorcount ();
		int activetextcount ();

		string putactivetext (int);
};

class Screen
{
	private:
		char display [SCRWIDTH][SCRHEIGHT];

		std::vector <Window *> layers;

	public:
		Screen ();

		void clrscr ();
		void buildscr ();
		void displayscr ();
		void addlayer (Window *);
		void dellayer (int);
		void swaplayer (int, int);
		void modlayer (int, Window *);

		int layercount ();

		Window * putlayer (int);
};

class Polygon
{
	private:
		double xcoord [3];
		double ycoord [3];
		double zcoord [3];

		char fill;
		char transparency;

		bool texturemode;

	public:
		Polygon ();

		void modp (int, double, double, double);
		void setfill (char);
		void settranspid (char);
		void center (double [3]);
		void putxyz (int, double [3]);
		void settexturemode (bool);

		bool puttexturemode ();

		char putfill ();
		char puttranspid ();

		double centerx ();
		double centery ();
		double centerz ();
		double putpx (int);
		double putpy (int);
		double putpz (int);
};

class R3Object
{
	private:
		std::vector <Polygon *> sides;
		std::vector <R3Object *> olink;
		std::vector <R3Object *> rzlink;
		std::vector <R3Object *> rxlink;
		std::vector <R3Object *> rylink;
		std::vector <Polygon> loadsides;

		double xbasis [3];
		double ybasis [3];
		double zbasis [3];
		double scalep [3];

		bool ctrscale;

	public:
		R3Object ();

		void addside (Polygon *);
		void delside (int);
		void modside (int, Polygon *);
		void rref3x4 (double [3][4]);
		void rot (char, double);
		void basisreset ();
		void putbasis (char, double [3]);
		void modbasis (char, double [3]);
		void shiftctr (double, double, double);
		void setctr (double, double, double);
		void center (double [3]);
		void ctrscaleoff (double, double, double);
		void ctrscaleon ();
		void cpyscalep (double [3]);
		void addolink (R3Object *, bool);
		void addrzlink (R3Object *, bool);
		void addrxlink (R3Object *, bool);
		void addrylink (R3Object *, bool);
		void delolink (int, bool);
		void delrzlink (int, bool);
		void delrxlink (int, bool);
		void delrylink (int, bool);
		void setutexturemode (bool);
		void saveobj (string);
		void clrloadsides ();

		bool putctrscale ();

		int sidenum ();
		int olinknum ();
		int rzlinknum ();
		int rxlinknum ();
		int rylinknum ();
		int loadobj (string);
		int loadsidenum ();

		double centerx ();
		double centery ();
		double centerz ();

		Polygon * putside (int);

		R3Object * putolink (int);
		R3Object * putrzlink (int);
		R3Object * putrxlink (int);
		R3Object * putrylink (int);

		Polygon putloadside (int);

		vector <Polygon> permcpy ();
};

class R3Cam
{
	private:
		std::vector <char> view;
		std::vector <double> viewdepth;
		std::vector <R3Object *> objects;

		double camx;
		double camy;
		double camz;
		double zoomfactor;

		double cambasisx [3];
		double cambasisy [3];
		double cambasisz [3];

		int viewcolumns;

	public:
		R3Cam ();

		void drawobjects ();
		void drawobject (R3Object);
		void drawpolygon (Polygon, R3Object);
		void drawline (double [3], double [3], char);
		void setcampos (double, double, double);
		void addobject (R3Object *);
		void delobject (int);
		void modobject (int, R3Object *);
		void clearview ();
		void rotatecam (char, double);
		void basisreset ();
		void cpybasis (char, double [3]);
		void setviewsize (int, int);
		void modview (char, int, int);
		void modviewdepth (double, int, int);
		void texturepolygon (Polygon, R3Object);
		void applyrotation (double, double, double, double [3], double [3], R3Object);
		void setzoomfactor (double);
		void scalept (double, double, double, double [3]);

		bool twodconvert (double [3], double [3], double [3], R3Object, Polygon);

		char getelement (int, int);
		char getelementraw (int);

		int getelementindex (int, int);
		int objectnum ();
		int putviewsize ();
		int putviewcolumns ();

		double getviewdepth (int, int);
		double getviewdepthraw (int);
		double putcamx ();
		double putcamy ();
		double putcamz ();
		double putzoomfactor ();

		vector <char> putview ();
		vector <double> putviewdepth ();

		R3Object * putobj (int);
};

#endif