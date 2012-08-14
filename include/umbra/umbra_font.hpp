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

#include <iostream>

class UmbraFont {
	public:
		UmbraFont ();
		~UmbraFont ();
		/**
		 * Initialises a font. Used for manual initialisation (ie, when automatic font detection isn't used).
		 * @param c number of columns of characters in the font image file
		 * @param r number of rows of characters in the font image file
		 * @param fn the filename of the font image file
		 * @param f font layout flags
		 */
		void initialise (int c, int r, const char * fn, int f = TCOD_FONT_LAYOUT_TCOD); //initialise manually
		/**
		 * Gets the font image's filename
		 * @return the font image's filename
		 */
		inline const char * filename () { return _filename.c_str(); }
		/**
		 * Gets the font image's number of columns
		 * @return the font image's number of columns
		 */
		inline int columns () { return _columns; }
		/**
		 * Gets the font image's number of rows
		 * @return the font image's number of rows
		 */
		inline int rows () { return _rows; }
		/**
		 * Gets the font image's layout flags
		 * @return the font image's layout flags
		 */
		inline int flags () { return _flags; }

	private:
		std::string _filename;
		int _columns;
		int _rows;
		int _flags;
};
