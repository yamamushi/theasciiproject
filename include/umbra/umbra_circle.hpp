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

class UmbraCircle {
	public:
		int x,y,r;
		bool mouseHover;
		bool mouseDown;
		UmbraCircle (): x(0),y(0),r(0),mouseHover(false) {}
		UmbraCircle (int r): x(0),y(0),r(r),mouseHover(false) {}
		UmbraCircle (int x, int y): x(x),y(y),r(0),mouseHover(false) {}
		UmbraCircle (int x, int y, int r): x(x),y(y),r(r),mouseHover(false) {}
		UmbraCircle (const UmbraPoint &p): x(p.x),y(p.y),r(0),mouseHover(false) {}
		UmbraCircle (const UmbraPoint &p, int r): x(p.x),y(p.y),r(r),mouseHover(false) {}
		/**
		 * Sets the circle's position.
		 * @param x the circle centre's <i>x</i> coordinate
		 * @param y the circle centre's <i>y</i> coordinate
		 */
		inline void setPos (int x, int y) { this->x=x; this->y=y; }
		/**
		 * Sets the circle's position.
         * @param p the point whose coordinates are to be come the circle's centre
         */
		inline void setPos (const UmbraPoint &p) { x=p.x; y=p.y; }
		/**
		 * Sets the circle's radius, keeping the position unchanged.
		 * @param r the circle's radius
		 */
		inline void setRadius (int r) { this->r=r; }
		/**
		 * Sets the circle's position and radius.
		 * @param x the circle centre's <i>x</i> coordinate
		 * @param y the circle centre's <i>y</i> coordinate
		 * @param r the circle's radius
		 */
		inline void set (int x, int y, int r) { setPos(x,y); setRadius(r); }
		/**
		 * Sets the circle's position and radius.
         * @param p the point whose coordinates are to be come the circle's centre
         * @param r the circle's radius
         */
		inline void set (const UmbraPoint &p, int r) { setPos(x,y); setRadius(r); }
		/**
		 * Checks whether a set of coordinates is contained within the circle.
		 * @param px the <i>x</i> coordinate to be checked
		 * @param py the <i>y</i> coordinate to be checked
		 * @return <code>true</code> if the coordinates are within the circle, <code>false</code> otherwise
		 */
		inline bool contains (int px, int py) { return (x - px) * (x - px) + (y - py) * (y - py) <= r * r; }
		/**
		 * Checks whether a point is contained within the circle.
		 * @param p the point to be checked
		 * @return <code>true</code> if the point is within the circle, <code>false</code> otherwise
		 */
		inline bool contains (const UmbraPoint &p) { return (((x-p.x)*(x-p.x))+((y-p.y)*(y-p.y))) <= (r*r); }
};
