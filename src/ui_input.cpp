/*
* Copyright (c) 2010 Jice
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The name of Jice may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY Jice ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL Jice BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Headers.h"

void TextInput::init(const char *title, const char *text, int maxSize) {
	this->title=title;
	this->text=text;
	this->maxSize=maxSize;
	width=(int)strlen(title)+8;
	width=MAX(30,width);
	height = TCODConsole::root->getHeightRect(MAIN_WIDTH/2-width/2+2,0,width-4,0, text) + 6;
	if ( con ) delete con;
	if ( txt ) delete txt;
	txt=NULL;
	con = new TCODConsole(width,height);
	con->setDefaultForeground(TCODColor::lightGrey);
	con->setDefaultBackground(TCODColor::lightYellow);
	con->printFrame(0,0,width,height,false,TCOD_BKGND_SET,title);
	con->setDefaultBackground(TCODColor::grey);
	con->setDefaultForeground(TCODColor::lightYellow);
	con->rect(0,0,width,height,false,TCOD_BKGND_SET);
	con->rect(1,1,width-2,height-2,true,TCOD_BKGND_NONE);
	con->printRect(2,2,width-4,0,text);
}

TextInput::~TextInput() {
	if ( txt ) delete txt;
	if ( con ) delete con;
}

void TextInput::render(int x, int y) {
	if (! txt ) txt = new TCODText(x-width/2+2,y+height-3,MIN(maxSize,width-4),1,maxSize);
    TCODConsole::blit(con,0,0,0,0,TCODConsole::root,x,y);
	txt->render(TCODConsole::root);
}

bool TextInput::update(float elapsed, TCOD_key_t k) {
	if (txt) return txt->update(k);
	return true;
}


