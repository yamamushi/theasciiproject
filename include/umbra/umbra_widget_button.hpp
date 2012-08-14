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

class UmbraWidget;
class UmbraRect;

class UmbraButton {
	public:
		UmbraRect area; //the rectangle where the object is contained
		UmbraWidget * parent; //reference to the widget that contains the object
		bool visible; //visibility (can be toggled)
		std::string tag; //the descriptive tag

		UmbraButton ();
		virtual ~UmbraButton() {}
		UmbraButton (UmbraWidget * parent, int x, int y, int w, int h, const char * tag = "");
		UmbraButton (UmbraWidget * parent, int x, int y, int w, int h, std::string tag = "");
        /**
		 * Sets the basic properties of the button: parent widget, position in the console, size and tag.
		 * @param parent a pointer to the UmbraWidget containing the button
		 * @param x the <code>x</code> coordinate of the top left corner of the button area
		 * @param y the <code>y</code> coordinate of the top left corner of the button area
		 * @param w the button area's width
		 * @param h the button area's height
		 * @param tag the tag's text
		 */
		void set (UmbraWidget * parent, int x, int y, int w, int h, const char * tag = "");
		/**
		 * Sets the basic properties of the button: parent widget, position in the console, size and tag.
		 * @param parent a pointer to the UmbraWidget containing the button
		 * @param x the <code>x</code> coordinate of the top left corner of the button area
		 * @param y the <code>y</code> coordinate of the top left corner of the button area
		 * @param w the button area's width
		 * @param h the button area's height
		 * @param tag the tag's text
		 */
		inline void set (UmbraWidget * parent, int x, int y, int w, int h, std::string tag = "") { set(parent, x, y, w, h, tag.c_str()); }
        /**
		 * Renders the button.
		 */
		virtual void render (TCODConsole * con);
		/**
		 * Checks the mouse status and calls <code>onMouseHover()</code> and <code>onMouseDown()</code> if necessary
		 */
		void mouse (TCOD_mouse_t &ms); //checks the status
		/**
		 * Custom code launched when the button is clicked
		 */
		virtual void onMouseDown () {}
		/**
		 * Custom code launched when the mouse cursor is over the button area
		 */
		virtual void onMouseOver () {}
};
