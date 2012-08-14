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
class UmbraRect;

class UmbraWidget: public UmbraModule {
	friend class UmbraCheckbox;
	friend class UmbraButton;
	public:
		UmbraWidget ();
		/**
		 * Custom, widget-specific code interpreting the mouse input.
		 * @param ms reference to the mouse object
		 */
		void mouse (TCOD_mouse_t &ms);
	protected:
		UmbraRect rect; // part of the screen where the widget is
		UmbraRect dragZone; // part of the widget we can click to drag it
		UmbraPoint minimiseButton; //minimise button coordinates
		UmbraPoint closeButton; //close button coordinates
		int mousex, mousey;
		int dragx, dragy;
		bool canDrag, isDragging;
		/**
		 * Sets the widget's active zone reacting to dragging.
		 * @param x the drag zone's top left corner's <i>x</i> coordinate
		 * @param y the drag zone's top left corner's <i>y</i> coordinate
		 * @param w the drag zone's width
		 * @param h the drag zone's height
		 */
		void setDragZone (int x, int y, int w, int h);
		/**
		 * Custom code that is executed when the user release the mouse button
		 * after dragging the widget		  
		 */		 		
		virtual void onDragEnd() {}
		
};
