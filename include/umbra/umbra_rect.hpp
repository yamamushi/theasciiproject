/*
* Umbra
* Copyright (c) 2009, 2010 Mingos, Jice
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The names of Mingos or Jice may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY MINGOS & JICE ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL MINGOS OR JICE BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

class UmbraPoint;

class UmbraRect {
	public:
		int x,y,w,h;
		bool mouseHover;
		bool mouseDown;
		UmbraRect (): x(0),y(0),w(0),h(0),mouseHover(false) {}
		UmbraRect (int x, int y): x(x),y(y),w(0),h(0),mouseHover(false) {}
		UmbraRect (const UmbraPoint &p): x(p.x),y(p.y),w(0),h(0),mouseHover(false) {}
		UmbraRect (int x, int y, int w, int h): x(x),y(y),w(w),h(h),mouseHover(false) {}
		UmbraRect (const UmbraPoint &p, int w, int h): x(p.x),y(p.y),w(w),h(h),mouseHover(false) {}
		/**
		 * Sets the rectangle's position.
		 * @param x the rectangle's top left corner's <i>x</i> coordinate
		 * @param y the rectangle's top left corner's <i>y</i> coordinate
		 */
		inline void setPos (int x, int y) { this->x=x; this->y=y; }
		/**
		 * Sets the rectangle's position.
		 * @param p the point whose coordinates are to become the rectangle's top letf corner's coordinates
		 */
		inline void setPos (const UmbraPoint &p) { x=p.x; y=p.y; }
		/**
		 * Sets the rectangle's size, keeping the top left corner's coordinates unchanged.
		 * @param w the rectangle's width
		 * @param h the rectangle's height
		 */
		inline void setSize (int w, int h) { this->w=w;this->h=h; }
		/**
		 * Sets the rectangle's position and size.
		 * @param x the rectangle's top left corner's <i>x</i> coordinate
		 * @param y the rectangle's top left corner's <i>y</i> coordinate
		 * @param w the rectangle's width
		 * @param h the rectangle's height
		 */
		inline void set (int x, int y, int w, int h) { setPos(x,y); setSize(w,h); }
		/**
		 * Sets the rectangle's position and size.
		 * @param p the point whose coordinates are to become the rectangle's top letf corner's coordinates
		 * @param w the rectangle's width
		 * @param h the rectangle's height
		 */
		inline void set (const UmbraPoint &p, int w, int h) { setPos(p.x,p.y); setSize(w,h); }
		/**
		 * Checks whether a set of coordinates is contained within the rectangle.
		 * @param px the <i>x</i> coordinate to be checked
		 * @param py the <i>y</i> coordinate to be checked
		 * @return <code>true</code> if the coordinates are within the rectangle, <code>false</code> otherwise
		 */
		inline bool contains (int px, int py) { return px >= x && px < x+w && py >= y && py < y+h; }
		/**
		 * Checks whether a point is contained within the rectangle.
		 * @param p the point to be checked
		 * @return <code>true</code> if the point is within the rectangle, <code>false</code> otherwise
		 */
		inline bool contains (const UmbraPoint &p) { return p.x >= x && p.x < x+w && p.y >= y && p.y < y+h; }
};
