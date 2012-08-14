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

class UmbraPoint {
	public:
		int x, y;
		bool mouseHover;
		bool mouseDown;
		UmbraPoint (): x(0),y(0),mouseHover(false) {}
		UmbraPoint (int x, int y): x(x),y(y),mouseHover(false) {}
		/**
		 * Sets the point's coordinates.
		 * @param x the point's <i>x</i> coordinate
		 * @param y the point's <i>y</i> coordinate
		 */
		inline void set (int x, int y) { this->x=x; this->y=y; }
		/**
		 * Checks whether the point's coordinates match the provided pair.
		 * @param px the <i>x</i> coordinate to be compared
		 * @param py the <i>y</i> coordinate to be compared
		 * @return <code>true</code> if the coordinates match, <code>false</code> if they don't
		 */
		inline bool is (int px, int py) { return px == x && py == y; }
		inline bool operator == (const UmbraPoint &p1) { return p1.x == x && p1.y == y; }
};

