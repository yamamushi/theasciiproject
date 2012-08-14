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

#include "umbra.hpp"

UmbraWidget::UmbraWidget(): mousex(-1),mousey(-1),
	canDrag(false),isDragging(false) {
}

void UmbraWidget::mouse(TCOD_mouse_t &ms) {
	//set mouse positions
	mousex=ms.cx-rect.x;
	mousey=ms.cy-rect.y;
	//check if the mouse is hovering over a button/rectangle
	minimiseButton.mouseHover = minimiseButton.is(mousex,mousey);
	closeButton.mouseHover = closeButton.is(mousex,mousey);
	dragZone.mouseHover = dragZone.contains(mousex,mousey);
	rect.mouseHover = rect.contains(ms.cx,ms.cy);
	//check whether the mouse is down on a button
	if (ms.lbutton && minimiseButton.mouseHover) minimiseButton.mouseDown = true;
	else minimiseButton.mouseDown = false;
	if (ms.lbutton && closeButton.mouseHover) closeButton.mouseDown = true;
	else closeButton.mouseDown = false;
	//deal with dragging
	if (canDrag) {
		if (ms.lbutton && !isDragging && dragZone.contains(mousex,mousey)) {
			isDragging = true;
			dragx = mousex;
			dragy = mousey; // position where the widget is drag
			ms.lbutton = false; // erase event
		} else if (isDragging && !ms.lbutton) {
			isDragging = false;
			ms.lbutton_pressed=false; // erase event
			onDragEnd();
		} else if (isDragging) {
			ms.lbutton=false; // erase event
			rect.x = CLAMP(0,getEngine()->getRootWidth()-rect.w, ms.cx-dragx);
			rect.y = CLAMP(0,getEngine()->getRootHeight()-rect.h,ms.cy-dragy);
			mousex=dragx; mousey=dragy;
			ms.cx=ms.cy=ms.x=ms.y=ms.dx=ms.dy=ms.dcx=ms.dcy=0; // erase mouse move event
		}
	}
}

void UmbraWidget::setDragZone (int x, int y, int w, int h) {
	dragZone.set(x,y,w,h);
	if (w > 0 && h > 0) canDrag = true;
}
