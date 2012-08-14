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

UmbraButton::UmbraButton () {
	parent = NULL;
	area.set(0,0,0,0);
	tag = "";
	visible = true;
}

UmbraButton::UmbraButton (UmbraWidget * parent, int x, int y, int w, int h, const char * tag) {
	this->parent = parent;
	area.set(x, y, w, h);
	this->tag = tag;
	visible = true;
}

UmbraButton::UmbraButton (UmbraWidget * parent, int x, int y, int w, int h, std::string tag) {
	this->parent = parent;
	area.set(x, y, w, h);
	this->tag = tag;
	visible = true;
}

void UmbraButton::set (UmbraWidget * parent, int x, int y, int w, int h, const char * tag) {
	this->parent = parent;
	area.set(x, y, w, h);
	this->tag = tag;
	visible = true;
}

void UmbraButton::mouse (TCOD_mouse_t &ms) {
	if (!visible)
		return;
	if (area.contains(ms.cx-parent->rect.x, ms.cy-parent->rect.y)) {
		area.mouseHover = true;
		onMouseOver();
	}
	else
		area.mouseHover = false;
	if (area.mouseHover && ms.lbutton) {
		area.mouseDown = true;
		ms.lbutton_pressed=false;
		onMouseDown();
	}
	else area.mouseDown = false;
}

void UmbraButton::render (TCODConsole * con) {
	if (!visible)
		return;
	TCODColor col=con->getDefaultForeground();
	con->setDefaultForeground(area.mouseHover ? TCODColor::white : TCODColor::lighterBlue); //placeholder!
	con->printFrame(area.x,area.y,area.w,area.h,false,TCOD_BKGND_NONE,NULL);
	if (!tag.empty())
		con->printRectEx(area.x+(area.w/2),area.y+(area.h/2),area.w-2,area.h-2,TCOD_BKGND_NONE,TCOD_CENTER,tag.c_str());
	con->setDefaultForeground(col);
}
