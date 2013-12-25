/**************************************************
* TEROS ENGINE BETA 0.0.2.7                       *
*                                                 *
* Author: Kyle L. Miskell                         *
* Last Modified: 22 December 2013                 *
*                                                 *
* Description: An ASCII console graphics engine.  *
**************************************************/

#include "teros.h"

Window::Window ()
{
	width = 0;
	height = 0;

	tlposx = 0;
	tlposy = SCRHEIGHT - 1;

	cursorchar = '>';
	fill = ' ';
	cursorid = '&';
	atxtid = '%';
	transparency = '`';
}

void Window::loadfromfile (string fname)
{
	width = 0;
	height = 0;

	ifstream input;

	string line;

	input.open (fname.c_str());

	while (!input.eof())
	{
		getline (input, line);

		if (line.size() > width)
		{
			width = line.size ();
		}
	}

	input.close ();

	input.open (fname.c_str());

	content.resize (0);
	cursors.resize (0);
	activetext.resize (0);

	while (!input.eof())
	{
		getline (input, line);

		for (int i = 0; i < width; i++)
		{
			content.resize (content.size () + 1);

			if (i < line.size ())
			{
				content [i + height*width] = line [i];
			}
			else
			{
				content [i + height*width] = fill;
			}

			if (content [i + height*width] == cursorid)
			{
				cursors.resize (cursors.size () + 1);
				cursors [cursors.size () - 1] = false;
			}
			else if (content [i + height*width] == atxtid)
			{
				activetext.resize (activetext.size () + 1);

				activetext [activetext.size () - 1] = "";
			}
		}

		height++;
	}

	input.close ();
}

void Window::loadfromvector (vector <char> input, int columns)
{
	if (input.size ()%columns)
	{
		return;
	}

	content.resize (input.size ());
	cursors.resize (0);
	activetext.resize (0);

	width = columns;
	height = input.size ()/columns;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			content [(height - i - 1)*width + j] = input [(i*width) + j];
		}
	}

	cursorid = '\0';
	atxtid = '\0';
	transparency = '\0';
}

void Window::setatxtid (char atid)
{
	atxtid = atid;
}

void Window::setcursorid (char cid)
{
	cursorid = cid;
}

void Window::modcontent (char c, int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		content [(height - y - 1)*width + x] = c;
	}
}

void Window::tlrepos (int x, int y)
{
	tlposx = x;
	tlposy = y;
}

void Window::setcursor (int index, bool state)
{
	if (index < cursors.size ())
	{
		cursors [index] = state;
	}
}

void Window::setactivetext (int index, string s)
{
	if (index < activetext.size ())
	{
		activetext [index] = s;
	}
}

void Window::setfill (char fillchar)
{
	for (int i = 0; i < content.size (); i++)
	{
		if (content [i] == fill)
		{
			content [i] = fillchar;
		}
	}

	fill = fillchar;
}

void Window::setcursorchar (char cursor)
{
	cursorchar = cursor;
}

bool Window::putcursor (int index)
{
	if (index < cursors.size ())
	{
		return cursors [index];
	}

	return false;
}

char Window::putatxtid ()
{
	return atxtid;
}

char Window::putcursorid ()
{
	return cursorid;
}

char Window::putfill ()
{
	return fill;
}

char Window::putcursorchar ()
{
	return cursorchar;
}

char Window::puttranspid ()
{
	return transparency;
}

char Window::readcontent (int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		return content [(height - y - 1)*width + x];
	}

	return ' ';
}

int Window::putwidth ()
{
	return width;
}

int Window::putheight ()
{
	return height;
}

int Window::puttlposx ()
{
	return tlposx;
}

int Window::puttlposy ()
{
	return tlposy;
}

int Window::cursorcount ()
{
	return cursors.size ();
}

int Window::activetextcount ()
{
	return activetext.size ();
}

string Window::putactivetext (int index)
{
	if (index < activetext.size ())
	{
		return activetext [index];
	}

	return NULL;
}

Screen::Screen ()
{
	clrscr ();
}

void Screen::clrscr ()
{
	int x = 0;
	int y = SCRHEIGHT - 1;

	while (x < SCRWIDTH || y > 0)
	{
		display [x][y] = ' ';

		x++;

		if (x >= SCRWIDTH && y > 0)
		{
			x = 0;
			y--;
		}
	}
}

void Screen::buildscr ()
{
	clrscr ();

	for (int i = 0; i < layers.size (); i++)
	{
		int x = 0;
		int y = SCRHEIGHT - 1;

		int acdetect = 0;
		int ccursor = 0;

		while (x < SCRWIDTH || y > 0)
		{
			if (x >= layers [i] -> puttlposx () && x < layers [i] -> puttlposx () + layers [i] -> putwidth () && y <= layers [i] -> puttlposy () && y > layers [i] -> puttlposy () - layers [i] -> putheight ())
			{
				if (layers [i] -> readcontent (x - layers [i] -> puttlposx (), y - (layers [i] -> puttlposy () - layers [i] -> putheight () + 1)) != layers [i] -> putatxtid () && layers [i] -> readcontent (x - layers [i] -> puttlposx (), y - (layers [i] -> puttlposy () - layers [i] -> putheight () + 1)) != layers [i] -> putcursorid () && layers [i] -> readcontent (x - layers [i] -> puttlposx (), y - (layers [i] -> puttlposy () - layers [i] -> putheight () + 1)) != layers [i] -> puttranspid ())
				{
					display [x][y] = layers [i] -> readcontent (x - layers [i] -> puttlposx (), y - (layers [i] -> puttlposy () - layers [i] -> putheight () + 1));
				}
				else if (layers [i] -> readcontent (x - layers [i] -> puttlposx (), y - (layers [i] -> puttlposy () - layers [i] -> putheight () + 1)) == layers [i] -> putcursorid ())
				{
					if (layers [i] -> putcursor (ccursor))
					{
							display [x][y] = layers [i] -> putcursorchar ();
					}
					else if (layers [i] -> putfill () != layers [i] -> puttranspid ())
					{
						display [x][y] = layers [i] -> putfill ();
					}

					ccursor++;
				}
				else if (layers [i] -> readcontent (x - layers [i] -> puttlposx (), y - (layers [i] -> puttlposy () - layers [i] -> putheight () + 1)) == layers [i] -> putatxtid ())
				{
					string activec = layers [i] -> putactivetext (acdetect);

					for (int ac = 0; ac < activec.size () && x + ac < layers [i] -> puttlposx () + layers [i] -> putwidth () && x + ac < SCRWIDTH; ac++)
					{
						display [x + ac][y] = activec [ac];
	
						if (ac + 1 >= activec.size () || x + ac + 1 >= layers [i] -> puttlposx () + layers [i] -> putwidth () || x + ac + 1 >= SCRWIDTH)
						{
							x += ac;
						}
					}

					acdetect++;
				}
			}

			x++;

			if (x >= SCRWIDTH && y > 0)
			{
				x = 0;
				y--;
			}
		}
	}
}

void Screen::displayscr ()
{
	buildscr ();

	int x = 0;
	int y = SCRHEIGHT - 1;

	cout << "\n ";

	while (x < SCRWIDTH && y > 0)
	{
		cout << display [x][y];

		x++;

		if (x >= SCRWIDTH && y > 0)
		{
			cout << "\n ";

			x = 0;
			y--;
		}
	}
}

void Screen::addlayer (Window * overlay)
{
	layers.resize (layers.size () + 1);

	layers [layers.size () - 1] = overlay;
}

void Screen::dellayer (int index)
{
	if (index < layers.size ())
	{
		layers.erase (layers.begin () + index);
	}
}

void Screen::swaplayer (int index1, int index2)
{
	if (index1 < layers.size () && index2 < layers.size ())
	{
		Window * temp = layers [index1];

		layers [index1] = layers [index2];
		layers [index2] = temp;
	}
}

void Screen::modlayer (int index, Window * replacement)
{
	if (index < layers.size ())
	{
		layers [index] = replacement;
	}
}

int Screen::layercount ()
{
	return layers.size ();
}

Window * Screen::putlayer (int index)
{
	if (index < layers.size () && index >= 0)
	{
		return layers [index];
	}

	return NULL;
}

Polygon::Polygon ()
{
	texturemode = true;

	fill = char (176);
	transparency = '`';

	xcoord [0] = 0;
	xcoord [1] = 0;
	xcoord [2] = 0;

	ycoord [0] = 0;
	ycoord [1] = 0;
	ycoord [2] = 0;

	zcoord [0] = 0;
	zcoord [1] = 0;
	zcoord [2] = 0;
}

void Polygon::modp (int index, double x, double y, double z)
{
	if (index < 3 && index >= 0)
	{
		xcoord [index] = x;

		ycoord [index] = y;

		zcoord [index] = z;
	}
}

void Polygon::setfill (char filler)
{
	fill = filler;
}

void Polygon::settranspid (char trans)
{
	transparency = trans;
}

void Polygon::center (double ctr [3])
{
	ctr [0] = centerx ();
	ctr [1] = centery ();
	ctr [2] = centerz ();
}

void Polygon::putxyz (int index, double xyz [3])
{
	if (index >= 0 && index < 3)
	{
		xyz [0] = xcoord [index];
		xyz [1] = ycoord [index];
		xyz [2] = zcoord [index];
	}
}

void Polygon::settexturemode (bool mode)
{
	texturemode = mode;
}

bool Polygon::puttexturemode ()
{
	return texturemode;
}

char Polygon::puttranspid ()
{
	return transparency;
}

char Polygon::putfill ()
{
	return fill;
}

double Polygon::centerx ()
{
	return (xcoord [0] + xcoord [1] + xcoord [2])/3.0;
}

double Polygon::centery ()
{
	return (ycoord [0] + ycoord [1] + ycoord [2])/3.0;
}

double Polygon::centerz ()
{
	return (zcoord [0] + zcoord [1] + zcoord [2])/3.0;
}

double Polygon::putpx (int index)
{
	if (index < 3 && index >= 0)
	{
		return xcoord [index];
	}

	return 0;
}

double Polygon::putpy (int index)
{
	if (index < 3 && index >= 0)
	{
		return ycoord [index];
	}

	return 0;
}

double Polygon::putpz (int index)
{
	if (index < 3 && index >= 0)
	{
		return zcoord [index];
	}

	return 0;
}

R3Object::R3Object ()
{
	sides.resize (0);
	olink.resize (0);
	rzlink.resize (0);
	rxlink.resize (0);
	rylink.resize (0);
	loadsides.resize (0);

	ctrscale = true;

	scalep [0] = 0.0;
	scalep [1] = 0.0;
	scalep [2] = 0.0;

	basisreset ();
}

void R3Object::addside (Polygon * side)
{
	sides.resize (sides.size () + 1);

	sides [sides.size () - 1] = side;
}

void R3Object::delside (int index)
{
	if (index < sides.size ())
	{
		sides.erase (sides.begin () + index);
	}
}

void R3Object::modside (int index, Polygon * side)
{
	if (index < sides.size ())
	{
		sides [index] = side;
	}
}

void R3Object::rref3x4 (double B [3][4])
{
	double multiple;

	if (B [0][0] < 0.00000000001 && B [0][0] > -0.00000000001)
	{
		double buffer;

		if (B [1][0] != 0)
		{
			buffer = B [1][0];
			B [1][0] = B [0][0];
			B [0][0] = buffer;

			buffer = B [1][1];

			B [1][1] = B [0][1];
			B [0][1] = buffer;

			buffer = B [1][2];

			B [1][2] = B [0][2];
			B [0][2] = buffer;

			buffer = B [1][3];

			B [1][3] = B [0][3];
			B [0][3] = buffer;
		}
		else
		{
			buffer = B [2][0];

			B [2][0] = B [0][0];
			B [0][0] = buffer;

			buffer = B [2][1];

			B [2][1] = B [0][1];
			B [0][1] = buffer;

			buffer = B [2][2];
	
			B [2][2] = B [0][2];
			B [0][2] = buffer;

			buffer = B [2][3];

			B [2][3] = B [0][3];
			B [0][3] = buffer;
		}
	}

	multiple = B [0][0];

	for (int j = 0; j < 4; j++)
	{
		B [0][j] /= multiple;
	}

	multiple = B [1][0];

	for (int i = 1; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			B [i][j] = B [i][j] - B [0][j]*multiple;
		}

		multiple = B [2][0];
	}

	if (B [1][1] < 0.00000000001 && B [1][1] > -0.00000000001)
	{
		double buffer;

		buffer = B [2][1];

		B [2][1] = B [1][1];
		B [1][1] = buffer;

		buffer = B [2][2];

		B [2][2] = B [1][2];
		B [1][2] = buffer;

		buffer = B [2][3];

		B [2][3] = B [1][3];
		B [1][3] = buffer;
	}

	multiple = B [1][1];

	for (int j = 0; j < 4; j++)
	{
		B [1][j] /= multiple;
	}

	multiple = B [0][1];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (i != 1)
			{
				B [i][j] -= B [1][j]*multiple;
			}
		}

		multiple = B [2][1];
	}

	multiple = B [2][2];

	for (int j = 0; j < 4; j++)
	{
		B [2][j] /= multiple;
	}

	multiple = B [0][2];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 2; j < 4; j++)
		{
			B [i][j] -= B [2][j]*multiple;
		}

		multiple = B [1][2];
	}

	double norm = sqrt(pow(B[0][3], 2) + pow (B[1][3], 2) + pow(B[2][3], 2));

	if (norm != 0)
	{
		B [0][3] /= norm;
		B [1][3] /= norm;
		B [2][3] /= norm;
	}
}

void R3Object::rot (char norm, double angle)
{
	int rnum;

	double * primarybasis [3];
	double * secondarybasis [3];
	double * normalbasis [3];

	if (norm == 'z' || norm == 'Z')
	{
		rnum = rzlink.size ();
		
	}
	else if (norm == 'x' || norm == 'X')
	{
		rnum = rxlink.size ();
	}
	else if (norm == 'y' || norm == 'Y')
	{
		rnum = rylink.size ();
	}

	for (int i = -1; i < rnum; i++)
	{
		R3Object * cobj;

		if (i == -1)
		{
			cobj = this;
		}
		else if (norm == 'z' || norm == 'Z')
		{
			cobj = rzlink [i];
		}
		else if (norm == 'x' || norm == 'X')
		{
			cobj = rxlink [i];
		}
		else if (norm == 'y' || norm == 'Y')
		{
			cobj = rylink [i];
		}

		double lxbasis [3];
		double lybasis [3];
		double lzbasis [3];

		cobj -> putbasis ('x', lxbasis);
		cobj -> putbasis ('y', lybasis);
		cobj -> putbasis ('z', lzbasis);
			
		if (norm == 'z' || norm == 'Z')
		{
			primarybasis [0] = &lybasis [0];
			primarybasis [1] = &lybasis [1];
			primarybasis [2] = &lybasis [2];
	
			secondarybasis [0] = &lxbasis [0];
			secondarybasis [1] = &lxbasis [1];
			secondarybasis [2] = &lxbasis [2];
	
			normalbasis [0] = &lzbasis [0];
			normalbasis [1] = &lzbasis [1];
			normalbasis [2] = &lzbasis [2];
		}
		else if (norm == 'x' || norm == 'X')
		{
			primarybasis [0] = &lzbasis [0];
			primarybasis [1] = &lzbasis [1];
			primarybasis [2] = &lzbasis [2];	

			secondarybasis [0] = &lybasis [0];
			secondarybasis [1] = &lybasis [1];
			secondarybasis [2] = &lybasis [2];

			normalbasis [0] = &lxbasis [0];
			normalbasis [1] = &lxbasis [1];
			normalbasis [2] = &lxbasis [2];
		}
		else if (norm == 'y' || norm == 'Y')
		{
			primarybasis [0] = &lxbasis [0];
			primarybasis [1] = &lxbasis [1];
			primarybasis [2] = &lxbasis [2];

			secondarybasis [0] = &lzbasis [0];
			secondarybasis [1] = &lzbasis [1];
			secondarybasis [2] = &lzbasis [2];

			normalbasis [0] = &lybasis [0];
			normalbasis [1] = &lybasis [1];
			normalbasis [2] = &lybasis [2];
		}
		else
		{
			return;
		}	

		double transformation [3][4];

		transformation [0][0] = *primarybasis [0];
		transformation [0][1] = *primarybasis [1];
		transformation [0][2] = *primarybasis [2];
		transformation [0][3] = cos (angle);

		transformation [1][0] = *normalbasis [0];
		transformation [1][1] = *normalbasis [1];
		transformation [1][2] = *normalbasis [2];
		transformation [1][3] = 0;

		transformation [2][0] = *secondarybasis [0];
		transformation [2][1] = *secondarybasis [1];
		transformation [2][2] = *secondarybasis [2];
		transformation [2][3] = cos (PI/2.0 + angle);

		rref3x4 (transformation);

		*primarybasis [0] = transformation [0][3];
		*primarybasis [1] = transformation [1][3];
		*primarybasis [2] = transformation [2][3];

		transformation [0][0] = *secondarybasis [0];
		transformation [0][1] = *secondarybasis [1];
		transformation [0][2] = *secondarybasis [2];
		transformation [0][3] = cos (angle);

		transformation [1][0] = *normalbasis [0];
		transformation [1][1] = *normalbasis [1];
		transformation [1][2] = *normalbasis [2];
		transformation [1][3] = 0;

		transformation [2][0] = *primarybasis [0];
		transformation [2][1] = *primarybasis [1];
		transformation [2][2] = *primarybasis [2];
		transformation [2][3] = 0;

		rref3x4 (transformation);

		*secondarybasis [0] = transformation [0][3];
		*secondarybasis [1] = transformation [1][3];
		*secondarybasis [2] = transformation [2][3];

		cobj -> modbasis ('x', lxbasis);
		cobj -> modbasis ('y', lybasis);
		cobj -> modbasis ('z', lzbasis);
	}
}

void R3Object::basisreset ()
{
	xbasis [0] = 1;
	xbasis [1] = 0;
	xbasis [2] = 0;

	ybasis [0] = 0;
	ybasis [1] = 1;
	ybasis [2] = 0;

	zbasis [0] = 0;
	zbasis [1] = 0;
	zbasis [2] = 1;
}

void R3Object::putbasis (char basis, double receptacle [3])
{
	if (basis == 'x' || basis == 'X')
	{
		receptacle [0] = xbasis [0];
		receptacle [1] = xbasis [1];
		receptacle [2] = xbasis [2];
	}
	else if (basis == 'y' || basis == 'Y')
	{
		receptacle [0] = ybasis [0];
		receptacle [1] = ybasis [1];
		receptacle [2] = ybasis [2];
	}
	else if (basis == 'z' || basis == 'Z')
	{
		receptacle [0] = zbasis [0];
		receptacle [1] = zbasis [1];
		receptacle [2] = zbasis [2];
	}
}

void R3Object::modbasis (char basis, double nbasis [3])
{
	if (basis == 'x' || basis == 'X')
	{
		xbasis [0] = nbasis [0];
		xbasis [1] = nbasis [1];
		xbasis [2] = nbasis [2];
	}
	else if (basis == 'y' || basis == 'Y')
	{
		ybasis [0] = nbasis [0];
		ybasis [1] = nbasis [1];
		ybasis [2] = nbasis [2];
	}
	else if (basis == 'z' || basis == 'Z')
	{
		zbasis [0] = nbasis [0];
		zbasis [1] = nbasis [1];
		zbasis [2] = nbasis [2];
	}
}
void R3Object::shiftctr (double sx, double sy, double sz)
{
	for (int n = -1; n < int(olink.size ()); n++)
	{
		R3Object * cobj;

		if (n == -1)
		{
			cobj = this;
		}
		else
		{
			cobj = olink [n];
		}

		for (int i = 0; i < cobj -> sidenum (); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				double x = cobj -> putside(i) -> putpx (j);
				double y = cobj -> putside(i) -> putpy (j);
				double z = cobj -> putside(i) -> putpz (j);

				x += sx;
				y += sy;
				z += sz;

				cobj -> putside (i) -> modp (j, x, y, z);
			}
		}
	}
}

void R3Object::setctr (double cx, double cy, double cz)
{
	double c [3];

	center (c);

	double diffx = cx - c [0];
	double diffy = cy - c [1];
	double diffz = cz - c [2];

	shiftctr (diffx, diffy, diffz);
}

void R3Object::center (double store [3])
{
	store [0] = 0;
	store [1] = 0;
	store [2] = 0;

	double ptnum = 0;

	for (int i = 0; i < sides.size (); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			store [0] += sides [i] -> putpx (j);
			store [1] += sides [i] -> putpy (j);
			store [2] += sides [i] -> putpz (j);
		}

		ptnum += 3;
	}

	if (ptnum != 0)
	{
		store [0] /= ptnum;
		store [1] /= ptnum;
		store [2] /= ptnum;
	}
}

void R3Object::ctrscaleoff (double x, double y, double z)
{
	ctrscale = false;

	scalep [0] = x;
	scalep [1] = y;
	scalep [2] = z;
}

void R3Object::ctrscaleon ()
{
	ctrscale = true;
}

void R3Object::cpyscalep (double p [3])
{
	p [0] = scalep [0];
	p [1] = scalep [1];
	p [2] = scalep [2];
}

void R3Object::addolink (R3Object * linko, bool mode)
{	
	for (int i = 0; i < olink.size (); i++)
	{
		if (olink [i] == linko)
		{
			return;
		}
	}

	if (mode)
	{
		for (int i = 0; i < linko -> olinknum (); i++)
		{
			linko -> putolink (i) -> addolink (this, false);

			olink.resize (olink.size () + 1);

			olink [olink.size () - 1] = linko -> putolink (i);

			for (int s = 0; s < olink.size (); s++)
			{
				olink [s] -> addolink (linko -> putolink (i), false);
				linko -> putolink (i) -> addolink (olink [s], false);
			}
		}

		linko -> addolink (this, false);

		for (int i = 0; i < olink.size (); i++)
		{
			olink [i] -> addolink (linko, false);
			linko -> addolink (olink [i], false);
		}
	}

	olink.resize (olink.size () + 1);

	olink [olink.size () - 1] = linko;
}

void R3Object::addrzlink (R3Object * linkrz, bool mode)
{
	for (int i = 0; i < rzlink.size (); i++)
	{
		if (rzlink [i] == linkrz)
		{
			return;
		}
	}

	if (mode)
	{
		for (int i = 0; i < linkrz -> rzlinknum (); i++)
		{
			linkrz -> putrzlink (i) -> addrzlink (this, false);

			rzlink.resize (rzlink.size () + 1);

			rzlink [rzlink.size () - 1] = linkrz -> putrzlink (i);

			for (int s = 0; s < rzlink.size (); s++)
			{
				rzlink [s] -> addrzlink (linkrz -> putrzlink (i), false);
				linkrz -> putrzlink (i) -> addrzlink (rzlink [s], false);
			}
		}

		linkrz -> addrzlink (this, false);

		for (int i = 0; i < rzlink.size (); i++)
		{
			rzlink [i] -> addrzlink (linkrz, false);
			linkrz -> addrzlink (rzlink [i], false);
		}
	}

	rzlink.resize (rzlink.size () + 1);

	rzlink [rzlink.size () - 1] = linkrz;
}

void R3Object::addrxlink (R3Object * linkrx, bool mode)
{
	for (int i = 0; i < rxlink.size (); i++)
	{
		if (rxlink [i] == linkrx)
		{
			return;
		}
	}

	if (mode)
	{
		for (int i = 0; i < linkrx -> rxlinknum (); i++)
		{
			linkrx -> putrxlink (i) -> addrxlink (this, false);

			rxlink.resize (rxlink.size () + 1);

			rxlink [rxlink.size () - 1] = linkrx -> putrxlink (i);

			for (int s = 0; s < rxlink.size (); s++)
			{
				rxlink [s] -> addrxlink (linkrx -> putrxlink (i), false);
				linkrx -> putrxlink (i) -> addrxlink (rxlink [s], false);
			}
		}

		linkrx -> addrxlink (this, false);

		for (int i = 0; i < rxlink.size (); i++)
		{
			rxlink [i] -> addrxlink (linkrx, false);
			linkrx -> addrxlink (rxlink [i], false);
		}
	}

	rxlink.resize (rxlink.size () + 1);

	rxlink [rxlink.size () - 1] = linkrx;
}

void R3Object::addrylink (R3Object * linkry, bool mode)
{
	for (int i = 0; i < rylink.size (); i++)
	{
		if (rylink [i] == linkry)
		{
			return;
		}
	}

	if (mode)
	{
		for (int i = 0; i < linkry -> rylinknum (); i++)
		{
			linkry -> putrylink (i) -> addrylink (this, false);

			rylink.resize (rylink.size () + 1);

			rylink [rylink.size () - 1] = linkry -> putrylink (i);

			for (int s = 0; s < rylink.size (); s++)
			{
				rylink [s] -> addrylink (linkry -> putrylink (i), false);
				linkry -> putrylink (i) -> addrylink (rylink [s], false);
			}
		}

		linkry -> addrylink (this, false);

		for (int i = 0; i < rylink.size (); i++)
		{
			rylink [i] -> addrylink (linkry, false);
			linkry -> addrylink (rylink [i], false);
		}
	}

	rylink.resize (rylink.size () + 1);

	rylink [rylink.size () - 1] = linkry;
}

void R3Object::delolink (int index, bool mode)
{
	if (olink.size () == 0)
	{
		return;
	}

	if (mode)
	{
		for (int i = 0; i < olink.size (); i++)
		{
			for (int j = 0; j < olink [i] -> olinknum (); j++)
			{
				if (olink [i] -> putolink (j) == this)
				{
					olink [i] -> delolink (j, false);
				}
			}
		}

		olink.resize (0);
	}
	else
	{
		olink.erase (olink.begin () + index);
	}
}

void R3Object::delrzlink (int index, bool mode)
{
	if (rzlink.size () == 0)
	{
		return;
	}

	if (mode)
	{
		for (int i = 0; i < rzlink.size (); i++)
		{
			for (int j = 0; j < rzlink [i] -> rzlinknum (); j++)
			{
				if (rzlink [i] -> putrzlink (j) == this)
				{
					rzlink [i] -> delrzlink (j, false);
				}
			}
		}

		rzlink.resize (0);
	}
	else
	{
		rzlink.erase (rzlink.begin () + index);
	}
}

void R3Object::delrxlink (int index, bool mode)
{
	if (rxlink.size () == 0)
	{
		return;
	}

	if (mode)
	{
		for (int i = 0; i < rxlink.size (); i++)
		{
			for (int j = 0; j < rxlink [i] -> rxlinknum (); j++)
			{
				if (rxlink [i] -> putrxlink (j) == this)
				{
					rxlink [i] -> delrxlink (j, false);
				}
			}
		}

		rxlink.resize (0);
	}
	else
	{
		rxlink.erase (rxlink.begin () + index);
	}
}

void R3Object::delrylink (int index, bool mode)
{
	if (rylink.size () == 0)
	{
		return;
	}

	if (mode)
	{
		for (int i = 0; i < rylink.size (); i++)
		{
			for (int j = 0; j < rylink [i] -> rylinknum (); j++)
			{
				if (rylink [i] -> putrylink (j) == this)
				{
					rylink [i] -> delrylink (j, false);
				}
			}
		}

		rylink.resize (0);
	}
	else
	{
		rylink.erase (rylink.begin () + index);
	}
}

void R3Object::setutexturemode (bool state)
{
	for (int i = 0; i < sides.size (); i++)
	{
		sides [i] -> settexturemode (state);
	}
}

void R3Object::saveobj (string filename)
{
	ofstream outfile;

	filename += ".tr3";

	outfile.open (filename.c_str ());

	for (int i = 0; i < sidenum (); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			outfile << putside (i) -> putpx (j) << " ";
			outfile << putside (i) -> putpy (j) << " ";
			outfile << putside (i) -> putpz (j) << " \n";
		}

		outfile << int (putside (i) -> putfill ()) << "\n";
		outfile << int (putside (i) -> puttranspid ()) << "\n";
		outfile << putside (i) -> puttexturemode ();

		if (!(i + 1 == sidenum ()))
		{
			outfile << "\n";
		}
	}

	outfile.close ();
}

void R3Object::clrloadsides ()
{
	loadsides.resize (0);
}

bool R3Object::putctrscale ()
{
	return ctrscale;
}

int R3Object::sidenum ()
{
	return sides.size ();
}

int R3Object::olinknum ()
{
	return olink.size ();
}

int R3Object::rzlinknum ()
{
	return rzlink.size ();
}

int R3Object::rxlinknum ()
{
	return rxlink.size ();
}

int R3Object::rylinknum ()
{
	return rylink.size ();
}

int R3Object::loadobj (string filename)
{
	bool txtmde = false;

	int linenum = 0;
	int intbuff = 0;

	double coordbffx = 0.0;
	double coordbffy = 0.0;
	double coordbffz = 0.0;

	string line;

	ifstream infile;

	if (!(filename [filename.size () - 1] == '3' && filename [filename.size () - 2] == 'r' && filename [filename.size () - 3] == 't' && filename [filename.size () - 4] == '.'))
	{
		return 1;
	}

	infile.open (filename.c_str ());

	while (!infile.eof())
	{
		getline (infile, line);
		linenum++;
	}

	infile.close ();

	if (linenum%6)
	{
		return 2;
	}

	sides.resize (0);
	olink.resize (0);
	rzlink.resize (0);
	rxlink.resize (0);
	rylink.resize (0);
	loadsides.resize (0);

	ctrscale = true;

	scalep [0] = 0.0;
	scalep [1] = 0.0;
	scalep [2] = 0.0;

	basisreset ();

	infile.open (filename.c_str ());

	for (int ln = 0; ln < linenum/6; ln++)
	{
		loadsides.resize (loadsides.size () + 1);

		for (int i = 0; i < 3; i++)
		{
			infile >> coordbffx >> coordbffy >> coordbffz;
			loadsides [loadsides.size () - 1].modp (i, coordbffx, coordbffy, coordbffz);
		}

		infile >> intbuff;
		loadsides [loadsides.size () - 1].setfill (char(intbuff));

		infile >> intbuff;
		loadsides [loadsides.size () - 1].settranspid (char(intbuff));

		infile >> txtmde;
		loadsides [loadsides.size () - 1].settexturemode (txtmde);
	}

	for (int i = 0; i < loadsides.size (); i++)
	{
		addside (&(loadsides [i]));
	}

	infile.close ();

	return 0;
}

int R3Object::loadsidenum ()
{
	return loadsides.size ();
}

double R3Object::centerx ()
{
	double x [3];

	center (x);

	return x [0];
}		

double R3Object::centery ()
{
	double y [3];

	center (y);

	return y [1];
}

double R3Object::centerz ()
{
	double z [3];

	center (z);

	return z [2];
}


Polygon * R3Object::putside (int index)
{
	if (index < sides.size () && index >= 0)
	{
		return sides [index];
	}
}

R3Object * R3Object::putolink (int index)
{
	if (index >= 0 && index < olink.size ())
	{
		return olink [index];
	}
}

R3Object * R3Object::putrzlink (int index)
{
	if (index >= 0 && index < rzlink.size ())
	{
		return rzlink [index];
	}
}

R3Object * R3Object::putrxlink (int index)
{
	if (index >= 0 && index < rxlink.size ())
	{
		return rxlink [index];
	}
}

R3Object * R3Object::putrylink (int index)
{
	if (index >= 0 && index < rylink.size ())
	{
		return rylink [index];
	}
}

Polygon R3Object::putloadside (int index)
{
	if (index >=0 && index < loadsides.size ())
	{
		return loadsides [index];
	}
}

vector <Polygon> R3Object::permcpy ()
{
	vector <Polygon> newpolygons (0);

	newpolygons.resize (sidenum ());

	if (ctrscale)
	{
		center (scalep);
	}

	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	for (int i = 0; i < newpolygons.size (); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			x = (putside (i) -> putpx (j)) - scalep [0];
			y = (putside (i) -> putpy (j)) - scalep [1];
			z = (putside (i) -> putpz (j)) - scalep [2];

			(newpolygons [i]).modp (j, (x*xbasis [0] + y*ybasis [0] + z*zbasis [0] + scalep [0]), (x*xbasis [1] + y*ybasis [1] + z*zbasis [1] + scalep [1]), (x*xbasis [2] + y*ybasis [2] + z*zbasis [2] + scalep [2]));
		}

		(newpolygons [i]).setfill (putside (i) -> putfill ());
		(newpolygons [i]).settexturemode (putside (i) -> puttexturemode ());
		(newpolygons [i]).settranspid (putside (i) -> puttranspid ());
	}

	return newpolygons;
}

R3Cam::R3Cam ()
{
	setviewsize (SCRWIDTH, SCRHEIGHT);

	clearview ();

	camx = 0;
	camy = 0;
	camz = 0;
	zoomfactor = 10;

	basisreset ();
}

void R3Cam::drawobjects ()
{
	clearview ();

	for (int i = 0; i < objects.size (); i++)
	{
		drawobject (*objects [i]);
	}
}

void R3Cam::drawobject (R3Object obj)
{
	for (int i = 0; i < obj.sidenum (); i++)
	{
		Polygon * temp = obj.putside (i);

		drawpolygon (*temp, obj);
	}
}

void R3Cam::drawpolygon (Polygon cpolygon, R3Object obj)
{
	if (cpolygon.puttexturemode ())
	{
		texturepolygon (cpolygon, obj);
	}
	else
	{
		double p1 [3];
		double p2 [3];
		double p3 [3];

		if (!twodconvert (p1, p2, p3, obj, cpolygon))
		{
			return;
		}

		drawline (p1, p2, cpolygon.putfill ());
		drawline (p2, p3, cpolygon.putfill ());
		drawline (p3, p1, cpolygon.putfill ());
	}
}

void R3Cam::drawline (double p1 [3], double p2 [3], char fill)
{
	double snorm = 0;

	bool swap = false;

	if (!(p2 [1] >= 0 && p2 [1] <= viewcolumns - 1 && p2 [2] >= 0 && p2 [2] <= view.size ()/viewcolumns - 1))
	{
		if (p1 [1] >= 0 && p1 [1] <= viewcolumns - 1 && p1 [2] >= 0 && p1 [2] <= view.size ()/viewcolumns - 1)
		{
			double buffer [3];

			buffer [0] = p2 [0];
			buffer [1] = p2 [1];
			buffer [2] = p2 [2];

			p2 [0] = p1 [0];
			p2 [1] = p1 [1];
			p2 [2] = p1 [2];

			p1 [0] = buffer [0];
			p1 [1] = buffer [1];
			p1 [2] = buffer [2];

			swap = true;
		}
		else
		{
			if (p1 [1] - p2 [1] != 0)
			{
				double ux = -1;
				double uy = -1;
				double dx = -1;
				double dy = -1;
				double lx = -1;
				double ly = -1;
				double rx = -1;
				double ry = -1;

				double up;
				double dp;
				double lp;
				double rp;

				double m = (p1 [2] - p2 [2])/(p1 [1] - p2 [1]);
				double b = p1 [2] - p1 [1]*m;

				if ((view.size ()/viewcolumns - 1 - b)/m >= 0 && (view.size ()/viewcolumns - 1 - b)/m <= viewcolumns - 1)
				{
					ux = (view.size ()/viewcolumns - 1 - b)/m;
					uy = view.size ()/viewcolumns - 1;
				}

				if ((0 - b)/m >= 0 && (0 - b)/m <= viewcolumns - 1)
				{
					dx = (0 - b)/m;
					dy = 0;
				}

				if (0*m + b >= 0 && 0*m + b <= view.size ()/viewcolumns - 1)
				{
					lx = 0;
					ly = 0*m + b;
				}

				if ((viewcolumns - 1)*m + b >= 0 && (viewcolumns - 1)*m + b <= view.size ()/viewcolumns - 1)
				{
					rx = viewcolumns - 1;
					ry = (viewcolumns - 1)*m + b;
				}

				up = dist (ux, uy, 0, p2 [1], p2 [2], 0);
				dp = dist (dx, dy, 0, p2 [1], p2 [2], 0);
				lp = dist (lx, ly, 0, p2 [1], p2 [2], 0);
				rp = dist (rx, ry, 0, p2 [1], p2 [2], 0);

				if (ux != -1 && lx != -1)
				{
					if (up < lp)
					{
						snorm = up;
					}
					else
					{
						snorm = lp;
					}
				}
				else if (ux != -1 && dx != -1)
				{
					if (up < dp)
					{
						snorm = up;
					}
					else
					{
						snorm = dp;
					}
				}
				else if (ux != -1 && rx != -1)
				{
					if (up < rp)
					{
						snorm = up;
					}
					else
					{
						snorm = rp;
					}
				}
				else if (rx != -1 && dx != -1)
				{
					if (rp < dp)
					{
						snorm = rp;
					}
					else
					{
						snorm = dp;
					}
				}
				else if (rx != -1 && lx != -1)
				{
					if (rp < lp)
					{
						snorm = rp;
					}
					else
					{
						snorm = lp;
					}
				}
				else if (dx != -1 && lx != -1)
				{
					if (dp < lp)
					{
						snorm = dp;
					}
					else
					{
						snorm = lp;
					}
				}
				else
				{
					return;
				}
			}
			else
			{
				if (p2 [1] >= 0 && p2 [1] <= viewcolumns - 1)
				{
					if (abs(p2 [2] - view.size ()/viewcolumns - 1) < abs(p2 [2] - 0))
					{
						snorm = abs(p2 [2] - view.size ()/viewcolumns - 1);
					}
					else
					{
						snorm = abs(p2 [2] - 0);
					}
				}
			}
		}
	}

	double dispx = p1 [1] - p2 [1];
	double dispy = p1 [2] - p2 [2];

	double normdispxy = dist (dispx, dispy, 0, 0, 0, 0);

	dispx /= normdispxy;
	dispy /= normdispxy;

	for (double norm = snorm; norm < normdispxy; norm += 0.5)
	{
		if (getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2])) == -1)
		{
			if (swap)
			{
				double buffer [3];

				buffer [0] = p2 [0];
				buffer [1] = p2 [1];
				buffer [2] = p2 [2];

				p2 [0] = p1 [0];
				p2 [1] = p1 [1];
				p2 [2] = p1 [2];

				p1 [0] = buffer [0];
				p1 [1] = buffer [1];
				p1 [2] = buffer [2];
			}

			return;
		}

		if (((norm/normdispxy)*(p1 [0] - p2 [0])) + p2 [0] > 0 && (((norm/normdispxy)*(p1 [0] - p2 [0])) + p2 [0] < viewdepth [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))] || viewdepth [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))] == -1))
		{
			view [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))] = fill;
			viewdepth [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))] = norm/normdispxy*(p1 [0] - p2 [0]) + p2 [0];
		}
	}
}

void R3Cam::setcampos (double x, double y, double z)
{
	camx = x;
	camy = y;
	camz = z;
}

void R3Cam::addobject (R3Object * nextelement)
{
	objects.resize (objects.size () + 1);

	objects [objects.size () - 1] = nextelement;
}

void R3Cam::delobject (int index)
{
	if (index < objects.size ())
	{
		objects.erase (objects.begin () + index);
	}
}

void R3Cam::modobject (int index, R3Object * newelement)
{
	if (index < objects.size ())
	{
		objects [index] = newelement;
	}
}

void R3Cam::clearview ()
{
	for (int i = 0; i < view.size (); i++)
	{
		view [i] = ' ';
		viewdepth [i] = -1.0;
	}
}

void R3Cam::rotatecam (char absnorm, double angle)
{
	double radius;
	double cangle;

	if (absnorm == 'z' || absnorm == 'Z')
	{
		radius = dist (cambasisx [0], cambasisx [1], 0, 0, 0, 0);
		cangle = findang (cambasisx [0], cambasisx [1]);

		cambasisx [0] = radius*cos(cangle + angle);
		cambasisx [1] = radius*sin(cangle + angle);

		radius = dist (cambasisy [0], cambasisy [1], 0, 0, 0, 0);
		cangle = findang (cambasisy [0], cambasisy [1]);

		cambasisy [0] = radius*cos(cangle + angle);
		cambasisy [1] = radius*sin(cangle + angle);

		radius = dist (cambasisz [0], cambasisz [1], 0, 0, 0, 0);
		cangle = findang (cambasisz [0], cambasisz [1]);

		cambasisz [0] = radius*cos(cangle + angle);
		cambasisz [1] = radius*sin(cangle + angle);
	}
	else if (absnorm == 'x' || absnorm == 'X')
	{
		radius = dist (0, cambasisx [1], cambasisx [2], 0, 0, 0);
		cangle = findang (cambasisx [1], cambasisx [2]);

		cambasisx [1] = radius*cos(cangle + angle);
		cambasisx [2] = radius*sin(cangle + angle);

		radius = dist (0, cambasisy [1], cambasisy [2], 0, 0, 0);
		cangle = findang (cambasisy [1], cambasisy [2]);

		cambasisy [1] = radius*cos(cangle + angle);
		cambasisy [2] = radius*sin(cangle + angle);

		radius = dist (0, cambasisz [1], cambasisz [2], 0, 0, 0);
		cangle = findang (cambasisz [1], cambasisz [2]);

		cambasisz [1] = radius*cos(cangle + angle);
		cambasisz [2] = radius*sin(cangle + angle);

	}
	else if (absnorm == 'y' || absnorm == 'Y')
	{
		radius = dist (cambasisx [0], 0, cambasisx [2], 0, 0, 0);
		cangle = findang (cambasisx [0], cambasisx [2]);

		cambasisx [0] = radius*cos(cangle + angle);
		cambasisx [2] = radius*sin(cangle + angle);

		radius = dist (cambasisy [0], 0, cambasisy [2], 0, 0, 0);
		cangle = findang (cambasisy [0], cambasisy [2]);

		cambasisy [0] = radius*cos(cangle + angle);
		cambasisy [2] = radius*sin(cangle + angle);

		radius = dist (cambasisz [0], 0, cambasisz [2], 0, 0, 0);
		cangle = findang (cambasisz [0], cambasisz [2]);

		cambasisz [0] = radius*cos(cangle + angle);
		cambasisz [2] = radius*sin(cangle + angle);
	}
}

void R3Cam::basisreset ()
{
	cambasisx [0] = 1;
	cambasisx [1] = 0;
	cambasisx [2] = 0;

	cambasisy [0] = 0;
	cambasisy [1] = 1;
	cambasisy [2] = 0;

	cambasisz [0] = 0;
	cambasisz [1] = 0;
	cambasisz [2] = 1;
}

void R3Cam::cpybasis (char axis, double store [3])
{
	if (axis == 'x' || axis == 'X')
	{
		store [0] = cambasisx [0];
		store [1] = cambasisx [1];
		store [2] = cambasisx [2];
	}
	else if (axis == 'y' || axis == 'Y')
	{
		store [0] = cambasisy [0];
		store [1] = cambasisy [1];
		store [2] = cambasisy [2];
	}
	else if (axis == 'z' || axis == 'Z')
	{
		store [0] = cambasisz [0];
		store [1] = cambasisz [1];
		store [2] = cambasisz [2];
	}
}

void R3Cam::setviewsize (int rows, int columns)
{
	if (columns > 0 && rows > 0)
	{
		viewcolumns = columns;
		view.resize (columns*rows);
		viewdepth.resize (view.size ());
	}
}

void R3Cam::modview (char elem, int x, int y)
{
	if (getelementindex (x, y) != -1)
	{
		view [getelementindex (x, y)] = elem;
	}
}

void R3Cam::texturepolygon (Polygon cpolygon, R3Object obj)
{
	if (cpolygon.putfill () == cpolygon.puttranspid ())
	{
		return;
	}

	double p1 [3];
	double p2 [3];
	double p3 [3];

	if (!twodconvert (p1, p2, p3, obj, cpolygon))
	{
		return;
	}

	double minx = p1 [1];
	double maxx = p1 [1];
	double miny = p1 [2];
	double maxy = p1 [2];

	if (p2 [1] < minx)
	{
		minx = p2 [1];
	}

	if (p3 [1] < minx)
	{
		minx = p3 [1];
	}

	if (p2 [2] < miny)
	{
		miny = p2 [2];
	}

	if (p3 [2] < miny)
	{
		miny = p3 [2];
	}

	if (p2 [1] > maxx)
	{
		maxx = p2 [1];
	}

	if (p3 [1] > maxx)
	{
		maxx = p3 [1];
	}

	if (p2 [2] > maxy)
	{
		maxy = p2 [2];
	}

	if (p3 [2] > maxy)
	{
		maxy = p3 [2];
	}

	if (maxx > viewcolumns - 1)
	{
		maxx = viewcolumns - 1;
	}

	if (maxy > view.size ()/viewcolumns - 1)
	{
		maxy = view.size ()/viewcolumns - 1;
	}

	if (minx < 0)
	{
		minx = 0;
	}

	if (miny < 0)
	{
		miny = 0;
	}

	int x = minx;
	int y = maxy;

	double a = ((p2 [1] - p1 [1])*(p3 [2] - p1 [2]) - (p3 [1] - p1 [1])*(p2 [2] - p1 [2]));
	double b = ((p2 [2] - p1 [2])*(p3 [0] - p1 [0]) - (p3 [2] - p1 [2])*(p2 [0] - p1 [0]));
	double c = ((p2 [0] - p1 [0])*(p3 [1] - p1 [1]) - (p3 [0] - p1 [0])*(p2 [1] - p1 [1]));
	double d = -1*(a*p1 [0] + b*p1 [1] + c*p1 [2]);

	while (x <= maxx || y > miny)
	{
		double v1 [2] = {x - p1 [1], y - p1 [2]};
		double v2 [2] = {x - p2 [1], y - p2 [2]};
		double v3 [2] = {x - p3 [1], y - p3 [2]};

		double norm;

		norm = dist (v1 [0], v1 [1], 0, 0, 0, 0)*1.000001;

		v1 [0] /= norm;
		v1 [1] /= norm;

		norm = dist (v2 [0], v2 [1], 0, 0, 0, 0)*1.000001;

		v2 [0] /= norm;
		v2 [1] /= norm;

		norm = dist (v3 [0], v3 [1], 0, 0, 0, 0)*1.000001;

		v3 [0] /= norm;
		v3 [1] /= norm;

		double angletotal = 0;
	
		angletotal += acos(v1 [0]*v2[0] + v1 [1]*v2 [1]) + acos(v1 [0]*v3 [0] + v1 [1]*v3 [1]) + acos(v2 [0]*v3 [0] + v2 [1]*v3[1]);		

		if (((-1*d - c*y - b*x)/a < viewdepth [getelementindex (x, y)] || viewdepth [getelementindex (x, y)] == -1) && (-1*d - c*y - b*x)/a > 0 && angletotal > 2*PI - 0.01 && angletotal < 2*PI + 0.01)
		{
			view [getelementindex (x, y)] = cpolygon.putfill ();
			viewdepth [getelementindex (x, y)] = (-1*d - c*y - b*x)/a;
		}

		x++;

		if (x > maxx && y > miny)
		{
			x = minx;
			y--;
		}
	}
}

void R3Cam::modviewdepth (double d, int x, int y)
{
	if (getelementindex (x, y) != -1)
	{
		viewdepth [getelementindex (x, y)] = d;
	}
}

void R3Cam::applyrotation (double x, double y, double z, double frompt [3], double returnpt [3], R3Object obj)
{
	double objbasisx [3];
	double objbasisy [3];
	double objbasisz [3];

	obj.putbasis ('x', objbasisx);
	obj.putbasis ('y', objbasisy);
	obj.putbasis ('z', objbasisz);

	x = x - frompt [0];
	y = y - frompt [1];
	z = z - frompt [2];

	returnpt [0] = x*objbasisx [0] + y*objbasisy [0] + z*objbasisz [0] + frompt [0];
	returnpt [1] = x*objbasisx [1] + y*objbasisy [1] + z*objbasisz [1] + frompt [1];
	returnpt [2] = x*objbasisx [2] + y*objbasisy [2] + z*objbasisz [2] + frompt [2];

	x = returnpt [0] - camx;
	y = returnpt [1] - camy;
	z = returnpt [2] - camz;

	returnpt [0] = x*cambasisx [0] + y*cambasisy [0] + z*cambasisz [0];
	returnpt [1] = x*cambasisx [1] + y*cambasisy [1] + z*cambasisz [1];
	returnpt [2] = x*cambasisx [2] + y*cambasisy [2] + z*cambasisz [2];
}

void R3Cam::setzoomfactor (double zfac)
{
	zoomfactor = zfac;
}

void R3Cam::scalept (double ptscalex, double ptscaley, double ptscalez, double store [3])
{
	store [0] = ptscalex;
	store [1] = zoomfactor*(ptscaley)/(ptscalex > 0 ? ptscalex/3 : 0.1) + viewcolumns/2;
	store [2] = zoomfactor*(ptscalez)/(ptscalex > 0 ? ptscalex/3 : 0.1) + (view.size ()/viewcolumns)/2;
}

bool R3Cam::twodconvert (double p1 [3], double p2 [3], double p3 [3], R3Object obj, Polygon cpolygon)
{
	int nogo = 0;

	double pscale [3];
	double actpt [3];

	if (obj.putctrscale ())
	{
		pscale [0] = obj.centerx ();
		pscale [1] = obj.centery ();
		pscale [2] = obj.centerz ();
	}
	else
	{
		obj.cpyscalep (pscale);
	}

	applyrotation (cpolygon.putpx (0), cpolygon.putpy (0), cpolygon.putpz (0), pscale, actpt, obj);

	if (actpt [0] < 0)
	{
		nogo++;
	}

	scalept (actpt[0], actpt [1], actpt [2], p1);

	applyrotation (cpolygon.putpx (1), cpolygon.putpy (1), cpolygon.putpz (1), pscale, actpt, obj);

	if (actpt [0] < 0)
	{
		nogo++;
	}

	scalept (actpt[0], actpt [1], actpt [2], p2);

	applyrotation (cpolygon.putpx (2), cpolygon.putpy (2), cpolygon.putpz (2), pscale, actpt, obj);

	if (actpt [0] < 0)
	{
		nogo++;
	}

	if (nogo >= 3)
	{
		return false;
	}

	scalept (actpt[0], actpt [1], actpt [2], p3);

	return true;
}

char R3Cam::getelement (int x, int y)
{
	if (getelementindex (x, y) != -1)
	{
		return view [getelementindex (x, y)];
	}

	return ' ';
}

char R3Cam::getelementraw (int index)
{
	if (index < view.size ())
	{
		return view [index];
	}

	return ' ';
}

int R3Cam::getelementindex (int x, int y)
{
	if (x >= 0 && x < viewcolumns && y >= 0 && y < view.size ()/viewcolumns)
	{
		return (x + y*viewcolumns);
	}

	return -1;
}

int R3Cam::objectnum ()
{
	return objects.size ();
}

int R3Cam::putviewsize ()
{
	return view.size ();
}

int R3Cam::putviewcolumns ()
{
	return viewcolumns;
}

double R3Cam::getviewdepth (int x, int y)
{
	if (getelementindex (x, y) != -1)
	{
		return viewdepth [getelementindex (x, y)];
	}

	return -1;
}

double R3Cam::getviewdepthraw (int index)
{
	if (index < viewdepth.size () && index > 0)
	{
		return viewdepth [index];
	}

	return -1;
}

double R3Cam::putcamx ()
{
	return camx;
}

double R3Cam::putcamy ()
{
	return camy;
}

double R3Cam::putcamz ()
{
	return camz;
}

double R3Cam::putzoomfactor ()
{
	return zoomfactor;
}

vector <char> R3Cam::putview ()
{
	return view;
}

vector <double> R3Cam::putviewdepth ()
{
	return viewdepth;
}

R3Object * R3Cam::putobj (int index)
{
	if (index >= 0 && index < objects.size ())
	{
		return objects [index];
	}

	return NULL;
}

int roundnum (double toround)
{
	if (toround - floor(toround) >= 0.5)
	{
		return ceil(toround);
	}

	return floor(toround);
}

double dist (double a, double b, double c, double x, double y, double z)
{
	return sqrt(pow (abs(a - x), 2) + pow (abs(b - y), 2) + pow (abs(c - z), 2));
}

double findang (double q, double r)
{
	double angle = 0;

	if (q != 0 && r != 0)
	{
		angle = atan(abs(r)/abs(q));
	}

	if (q < 0 && r > 0)
	{
		angle = PI - angle;
	}
	else if (q < 0 && r < 0)
	{
		angle = PI + angle;
	}
	else if (q > 0 && r < 0)
	{
		angle = 2.0*PI - angle;
	}

	if (abs(r) == 0 && q > 0)
	{
		angle = 0;
	}
	else if (abs(r) == 0 && q < 0)
	{
		angle = PI;
	}
	else if (abs(q) == 0 && r > 0)
	{
		angle = PI*0.5;
	}
	else if (abs(q) == 0 && r < 0)
	{
		angle = PI*1.5;
	}
	else if (abs(q) == 0 && abs(r) == 0)
	{
		angle = -1;
	}

	return angle;
}

string doubletostring (double num)
{
	string rstring = "";
	string rstring2 = "";

	num *= pow (10, 6);

	int lcounter = 0;

	bool neg = false;
	bool tripdec = false;

	if (num == 0)
	{
		return "0.000000";
	}
	else if (num < 0)
	{
		neg = true;
		num *= -1;
	}

	while (int(num) > 0)
	{
		if (lcounter == 6)
		{
			rstring += ".";
			tripdec = true;
		}

		rstring += char(int(num) % 10 + 48);
		num = int(num)/10;

		lcounter++;
	}

	if (!tripdec)
	{
		rstring += ".0";
	}

	if (neg)
	{
		rstring += "-";
	}

	lcounter = 0;

	rstring2.resize (rstring.size ());

	for (int i = rstring.size () - 1; i >= 0; i--)
	{
		rstring2 [lcounter] = rstring [i];

		lcounter++;
	}
		
	return rstring2;
}