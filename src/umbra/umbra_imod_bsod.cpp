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

UmbraModBSOD::UmbraModBSOD () {
	bsod = new TCODConsole(30,8);
	closeButton.set(28,0);
	duration = 5000;
	msgString = "";
	rect.set(getEngine()->getRootWidth()-31,getEngine()->getRootHeight()-9,30,8);
	setDragZone(0,0,28,1);
	setName("umbraBSOD");
}

void UmbraModBSOD::activate () {
	startTime = TCODSystem::getElapsedMilli();
	msgString = UmbraLog::get();
}

bool UmbraModBSOD::update () {
	if (closeButton.mouseDown) setActive(false);
	if (TCODSystem::getElapsedMilli() - startTime >= duration) return false;
	else return true;
}

void UmbraModBSOD::render () {
	bsod->setDefaultBackground(TCODColor::blue);
	bsod->clear();
	bsod->setDefaultForeground(TCODColor::white);
	bsod->printFrame(0,0,30,8,true,TCOD_BKGND_NONE,"Umbra BSOD");
	bsod->printRectEx(15,2,28,5,TCOD_BKGND_NONE,TCOD_CENTER,UmbraLog::get());
	if (closeButton.mouseHover)
		bsod->setDefaultForeground(TCODColor::red);
	bsod->putChar(closeButton.x,closeButton.y,'X',TCOD_BKGND_NONE);
	if (dragZone.mouseHover || isDragging) {
		bsod->setDefaultBackground(TCODColor::lightRed);
		bsod->rect(9,0,12,1,false,TCOD_BKGND_SET);
	}
	TCODConsole::blit(bsod,0,0,rect.w,rect.h,TCODConsole::root,rect.x,rect.y,1.0f,0.5f);
}
