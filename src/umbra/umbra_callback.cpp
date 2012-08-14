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

//quit program
UmbraCallbackQuit::UmbraCallbackQuit () {
	key.assign(TCODK_F4,0,true,false,false);
}

void UmbraCallbackQuit::action () {
	getEngine()->deactivateAll();
}

//switch fullscreen
UmbraCallbackFullscreen::UmbraCallbackFullscreen () {
	key.assign(TCODK_ENTER,'\r',true,false,false);
}

void UmbraCallbackFullscreen::action () {
	TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
}

//save screenshot
UmbraCallbackScreenshot::UmbraCallbackScreenshot () {
	key.assign(TCODK_PRINTSCREEN,0,false,false,false);
}

void UmbraCallbackScreenshot::action () {
	TCODSystem::saveScreenshot(NULL);
}

//switch font up
UmbraCallbackFontUp::UmbraCallbackFontUp () {
	key.assign(TCODK_PAGEUP,0,false,false,false);
}

void UmbraCallbackFontUp::action () {
	if (getEngine()->activateFont(1)) getEngine()->reinitialise();
}

//switch font down
UmbraCallbackFontDown::UmbraCallbackFontDown () {
	key.assign(TCODK_PAGEDOWN,0,false,false,false);
}

void UmbraCallbackFontDown::action () {
	if (getEngine()->activateFont(-1)) getEngine()->reinitialise();
}

//pause the program
UmbraCallbackPause::UmbraCallbackPause () {
	key.assign(TCODK_PAUSE,0,false,false,false);
}

void UmbraCallbackPause::action () {
	getEngine()->setPause(!getEngine()->getPause());
}

//pause the program
UmbraCallbackSpeedometer::UmbraCallbackSpeedometer () {
	key.assign(TCODK_F5,0,false,false,false);
}

void UmbraCallbackSpeedometer::action () {
	if (getEngine()->getModule(UMBRA_INTERNAL_SPEEDOMETER)->getActive()) {
		getEngine()->deactivateModule(UMBRA_INTERNAL_SPEEDOMETER);
	}
	else {
		getEngine()->activateModule(UMBRA_INTERNAL_SPEEDOMETER);
	}
}
