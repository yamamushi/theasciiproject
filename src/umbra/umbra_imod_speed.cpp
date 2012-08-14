/*
* Umbra
* Copyright (c) 2009 Mingos
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The name of Mingos may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY MINGOS ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL MINGOS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "umbra.hpp"

#define MAXIMISED_MODE_WIDTH 30
#define MAXIMISED_MODE_HEIGHT 8
#define TIMEBAR_LENGTH (MAXIMISED_MODE_WIDTH-4)*2

UmbraModSpeed::UmbraModSpeed (): cumulatedElapsed(0.0f), updateTime(0.0f), renderTime(0.0f),
	updatePer(0),renderPer(0),sysPer(0),isMinimised(false) {
	speed = new TCODConsole(MAXIMISED_MODE_WIDTH,MAXIMISED_MODE_HEIGHT);
	rect.set((getEngine()->getRootWidth()/2)-15,(getEngine()->getRootHeight()/2)-3,30,MAXIMISED_MODE_HEIGHT);
	// the title bar is drag-sensible
	setDragZone(0,0,MAXIMISED_MODE_WIDTH-3,1);
	//the buttons:
	minimiseButton.set(MAXIMISED_MODE_WIDTH-3,0);
	closeButton.set(MAXIMISED_MODE_WIDTH-2,0);
	setPriority(-2000000000); // high priority for internal modules
	timeBar = new TCODImage(TIMEBAR_LENGTH,2);
	setName("umbraSpeedometer");
}

void UmbraModSpeed::mouse (TCOD_mouse_t &ms) {
	UmbraWidget::mouse(ms);
	if (ms.lbutton_pressed) {
		//minimise button is pressed
		if (minimiseButton.is(mousex,mousey)) {
			isMinimised = !isMinimised;
			ms.lbutton_pressed=false; // erase event
			if (isMinimised) {
				rect.setSize(9,1);
				minimiseButton.set(7,0);
				closeButton.set(8,0);
				dragZone.w = 7;
				rect.x = rect.x+MAXIMISED_MODE_WIDTH-10;
			} else {
				rect.setSize(MAXIMISED_MODE_WIDTH,MAXIMISED_MODE_HEIGHT);
				minimiseButton.set(MAXIMISED_MODE_WIDTH-3,0);
				closeButton.set(MAXIMISED_MODE_WIDTH-2,0);
				dragZone.w = MAXIMISED_MODE_WIDTH-3;
				// when the widget maximizes, it might cross the screen borders
				rect.x = rect.x+10-MAXIMISED_MODE_WIDTH;
				rect.x=MAX(0,rect.x);
				rect.y=MIN(getEngine()->getRootHeight()-rect.h,rect.y);
			}
		}
		//close button is pressed
		else if (closeButton.is(mousex,mousey)) {
			getEngine()->deactivateModule(this);
			ms.lbutton_pressed=false; // erase event
		}
	}
}

bool UmbraModSpeed::update () {
	cumulatedElapsed += TCODSystem::getLastFrameLength();

	if (cumulatedElapsed >= 1.0f) {
		updatePer = (int)(updateTime * 100.0f / (cumulatedElapsed));
		renderPer = (int)(renderTime * 100.0f / (cumulatedElapsed));
		sysPer = 100 - updatePer - renderPer;
		cumulatedElapsed = updateTime = renderTime = 0.0f;
		// compute time bar picture
		for (int px = 0; px < TIMEBAR_LENGTH; px++) {
			TCODColor col;
			if (px < TIMEBAR_LENGTH * updatePer/100) col = TCODColor::green;
			else if ( px < TIMEBAR_LENGTH*(updatePer+renderPer)/100 ) col = TCODColor::yellow;
			else col = TCODColor::red;
			timeBar->putPixel(px,0,col);
			timeBar->putPixel(px,1,col);
		}
	}
	if (getStatus() == UMBRA_ACTIVE) return true;
	else return false;
}

void UmbraModSpeed::setTimes(long updateTime, long renderTime) {
	this->updateTime += updateTime * 0.001f;
	this->renderTime += renderTime * 0.001f;
}

void UmbraModSpeed::render () {
	speed->setDefaultBackground(TCODColor::black);
	speed->setDefaultForeground(TCODColor::white);
	if ( isMinimised ) {
		speed->printEx(0,0,TCOD_BKGND_SET,TCOD_LEFT,"%4dfps ",TCODSystem::getFps());
		TCODConsole::blit(speed,0,0,8,1,TCODConsole::root,rect.x,rect.y,1.0f,0.5f);
	} else {
		speed->printFrame(0,0,MAXIMISED_MODE_WIDTH,MAXIMISED_MODE_HEIGHT,true,TCOD_BKGND_SET,"Speed-o-meter");
		speed->printEx(MAXIMISED_MODE_WIDTH/2,2,TCOD_BKGND_NONE,TCOD_CENTER,"last frame: %3d ms",(int)(TCODSystem::getLastFrameLength()*1000));
		speed->printEx(MAXIMISED_MODE_WIDTH/2,3,TCOD_BKGND_NONE,TCOD_CENTER,"frames per second: %3d",TCODSystem::getFps());
		// summary
		speed->printEx(MAXIMISED_MODE_WIDTH/2,5,TCOD_BKGND_NONE,TCOD_CENTER,
			"%c%c%c%cUpd%c %2d%% %c%c%c%cRender%c %2d%% %c%c%c%cSys%c %2d%%",
			TCOD_COLCTRL_FORE_RGB,1,255,1,TCOD_COLCTRL_STOP,
			updatePer,
			TCOD_COLCTRL_FORE_RGB,255,255,1,TCOD_COLCTRL_STOP,
			renderPer,
			TCOD_COLCTRL_FORE_RGB,255,1,1,TCOD_COLCTRL_STOP,
			sysPer);
		if ( dragZone.mouseHover || isDragging) {
			speed->setDefaultBackground(TCODColor::lightRed);
			speed->rect(7,0,15,1,false,TCOD_BKGND_SET);
		}
	}
	speed->setDefaultBackground(TCODColor::black);
	// draw minimize button
	if (minimiseButton.mouseHover) speed->setDefaultForeground(TCODColor::white); //button is active
	else speed->setDefaultForeground(TCODColor::lightGrey); //button is not active
	speed->putChar(minimiseButton.x,minimiseButton.y, isMinimised ? '+' : '-', TCOD_BKGND_SET);
	//draw close button
	if (closeButton.mouseHover) speed->setDefaultForeground(TCODColor::red); //button is active
	else speed->setDefaultForeground(TCODColor::lightGrey); //button is not active
	speed->putChar(closeButton.x,closeButton.y, 'X', TCOD_BKGND_SET);
	//blit the console
	TCODConsole::blit(speed,0,0,rect.w,rect.h,TCODConsole::root,rect.x,rect.y,1.0f,0.52f);
	// render non transparent timebar (until libtcod subcell over subcell blitting is fixed...)
	if (! isMinimised ) timeBar->blit2x(TCODConsole::root,rect.x+2,rect.y+4);
}

void UmbraModSpeed::activate () {
	fps = TCODSystem::getFps();
	TCODSystem::setFps(0);
}

void UmbraModSpeed::deactivate () {
	TCODSystem::setFps(fps);
}
