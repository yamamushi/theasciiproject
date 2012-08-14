/*
 * =====================================================================================
 *
 *       Filename:  Graphics.cpp
 *
 *    Description:  Our graphics handling library that relies on libtcod.
 *    		The intention is for this library to handle all reliance on
 *    		the libtcod graphics functions - thereby slowly modularilizing
 *    		the client to be rendered differently.
 *
 *        Version:  1.0
 *        Created:  07/05/2012
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yamamushi (Jon Rumion)
 *   Organization:  The ASCII Project
 *
 *	  License:  GPLv3
 *
 *	  Copyright 2012 Jonathan Rumion
 *
 *   This file is part of The ASCII Project.
 *
 *   The ASCII Project is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   The ASCII Project is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with The ASCII Project.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * =====================================================================================
 */


#include "Headers.h"


bool drawLogin;
bool drawNewAccount;

std::string user;
std::string pass;


GraphicsTCOD::GraphicsTCOD(ClientMap *clientMap){
	init(clientMap);
}

void GraphicsTCOD::init(ClientMap *clientMap){
    
    cMap = clientMap;
    
    extern bool drawLogin;
    extern bool drawNewAccount;
    drawLogin = false;
    drawNewAccount = false;
    
    
    setlocale(LC_ALL, "en_US.UTF-8");
    TCODConsole::setCustomFont("data/font.png", TCOD_FONT_LAYOUT_ASCII_INROW, 32, 2048);
    
    //TCODConsole::setCustomFont("data/arial12x12.png", TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
    TCODConsole::initRoot(MAIN_WIDTH,MAIN_HEIGHT,"The ASCII Project",false,TCOD_RENDERER_SDL);
    //	TCODConsole::credits();
    
    TCODConsole *mainConsole = new TCODConsole(MAIN_WIDTH, MAIN_HEIGHT);
    TCODSystem::setFps(25);    
    output = mainConsole;


    // Apply remap for our non-unicode ascii based box-drawing functions
    TCODConsole::mapAsciiCodeToFont(179, 17, 298);
    TCODConsole::mapAsciiCodeToFont(180, 3, 299);
    TCODConsole::mapAsciiCodeToFont(191, 23, 298);
    TCODConsole::mapAsciiCodeToFont(192, 26, 298);
    TCODConsole::mapAsciiCodeToFont(195, 0, 299);
    TCODConsole::mapAsciiCodeToFont(196, 16, 298);
    TCODConsole::mapAsciiCodeToFont(217, 29, 298);
    TCODConsole::mapAsciiCodeToFont(218, 20, 298);
    
    
    TCODConsole::flush();
    
    
    
    TCODConsole::setKeyboardRepeat(2000, 100);
    
    output->setDefaultBackground(TCODColor(0, 0, 0));
    output->clear();
    render();

}



void GraphicsTCOD::drawMenu()
{
    Widget::setConsole(output);
    
    
    //new StatusBar(0,0,MAP_WIDTH,1);
    
    VBox *vbox=new VBox(MAP_WIDTH/2 - 7,MAP_HEIGHT/2 + 10,0);
    ToolBar *mainMenu = new ToolBar(MAP_WIDTH/2 - 7,MAP_HEIGHT/2 + 10,15,NULL,NULL);
    //stats->addWidget(new Label(MAP_WIDTH/2 - 7,MAP_HEIGHT/2 - 6,"Login","Login"));
    mainMenu->addWidget(new Button("Connect",NULL,loginCbk,NULL));
    //stats->addWidget(new Label(MAP_WIDTH/2 - 7,MAP_HEIGHT/2 - 5,"New Account","New Account"));
    //stats->addWidget(new Button("New Account",NULL,newAccountCbk,NULL));
	//stats->addWidget(new Label(MAP_WIDTH/2 - 7,MAP_HEIGHT/2 - 4,"Options","Options"));
    mainMenu->addWidget(new Button("Options",NULL,NULL,NULL));
    //stats->addWidget(new Label(MAP_WIDTH/2 - 7,MAP_HEIGHT/2 - 3,"Quit","Quit"));
    mainMenu->addWidget(new Button("Quit",NULL,quitCbk,NULL));
    vbox->addWidget(mainMenu);
    
    vbox->setBackgroundColor(TCODColor(0,0,0), TCODColor(128,128,128));
    
    Widget::renderWidgets();
    
    TCODMouse::showCursor(true);
    
    render();
    
    //static char *prompt = (char *)"The ASCII Project 0.0.0k  Yamamushi@gmail.com (c)2012";

    render();
    
    TCODImage *image = new TCODImage("data/images/MenuBackground.png");
    
    
   // bool quit = false;
    while(true)
    {
        TCOD_key_t key;
        TCOD_mouse_t mouse;
        
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&key,&mouse);
        Widget::updateWidgets(key,mouse);
                
        Widget::renderWidgets();   
        
        render();
        
        image->blitRect(output, 2, 0);
        
        output->setDefaultForeground(TCODColor(255, 255, 255));
        output->print(MAP_WIDTH-26, MAP_HEIGHT-3, (const char*)"The ASCII Project 0.0.0k", TCOD_LEFT);
        output->print(MAP_WIDTH-29, MAP_HEIGHT-2, (const char*)"Yamamushi@gmail.com (c)2012", TCOD_LEFT);
        output->rect(0, 0, 20, 1, true);
        
        
        if(drawLogin)
        {
            break;
        }
        
    }
    
    vbox->removeWidget(mainMenu);
    delete vbox;
    
    output->setDefaultBackground(TCODColor(0, 0, 0));
    output->clear();
    render();

    
}


void GraphicsTCOD::loginCbk(Widget *w, void *userData)
{
    extern bool drawLogin;
    drawLogin = true;
}


void GraphicsTCOD::quitCbk(Widget *w, void *userData)
{
    exit(0);
}


void GraphicsTCOD::drawMainInterface()
{
    Widget::setConsole(output);
    
    
    //new StatusBar(0,0,MAP_WIDTH-20,1);
    
    HBox *hMenu=new HBox(4,-1,0);
    ToolBar *menuToolbar = new ToolBar(0,0,6,NULL,NULL);
    menuToolbar->addWidget(new Button("Menu",NULL,NULL,NULL));
    hMenu->addWidget(menuToolbar);
    
    
    ToolBar *playerToolbar = new ToolBar(0,0,6, NULL, NULL);
    playerToolbar->addWidget(new Button("Player", NULL, NULL, NULL));
    hMenu->addWidget(playerToolbar);
    
    ToolBar *socialToolbar = new ToolBar(0,0,6, NULL, NULL);
    socialToolbar->addWidget(new Button("Social", NULL, NULL, NULL));
    hMenu->addWidget(socialToolbar);
    
    
    ToolBar *worldToolbar = new ToolBar(0,0,6, NULL, NULL);
    worldToolbar->addWidget(new Button("World", NULL, NULL, NULL));
    hMenu->addWidget(worldToolbar);
    
    
    ToolBar *toolsToolbar = new ToolBar(0,0,6, NULL, NULL);
    toolsToolbar->addWidget(new Button("Tools", NULL, NULL, NULL));
    hMenu->addWidget(toolsToolbar);
    
    
    ToolBar *helpToolbar = new ToolBar(0,0,6, NULL, NULL);
    helpToolbar->addWidget(new Button("Help", NULL, NULL, NULL));
    hMenu->addWidget(helpToolbar);
    
    
    hMenu->setBackgroundColor(TCODColor(0,0,0), TCODColor(128,128,128));
    
 
    output->vline(MAP_WIDTH-18, 0, 32);
    output->vline(MAP_WIDTH/2, 32, 13);
    output->hline(0, 32, MAP_WIDTH);
    output->hline(MAP_WIDTH/2 + 1, MAP_HEIGHT-3, MAP_WIDTH/2);
    output->hline(MAP_WIDTH/2 + 1, MAP_HEIGHT-1, MAP_WIDTH/2);
    
    
    output->print(MAP_WIDTH/2, 32, L"\u2566");
    output->print(MAP_WIDTH-18, 32, L"\u2569");
    output->print(MAP_WIDTH/2, MAP_HEIGHT-3, L"\u2560");
    output->print(MAP_WIDTH/2, MAP_HEIGHT-1, L"\u2560");
    
    
    char *prompt = (char *)"$>";
    TCODText *inputText = new TCODText(MAIN_WIDTH/2 + 1, MAIN_HEIGHT-2, MAIN_WIDTH/2 - 3, 1, MAIN_WIDTH/2 - 6);
    inputText->setProperties(32, 1000, (const char *)prompt, 1);
    inputText->setColors(TCODColor(0,255,0), TCODColor(0,0,0), 1.0f);

    inputText->render(output);
    
    
    while(true)
    {
        TCOD_key_t key;
        TCOD_mouse_t mouse;
        
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&key,&mouse);
        Widget::updateWidgets(key,mouse);
        
        inputText->update(key);
        Widget::renderWidgets();
        inputText->render(output);
        
        render();
        
        
        
        
        if(key.vk == TCODK_ENTER)
        {
            exit(0);
        }
    
    }
    
}




void GraphicsTCOD::getUser()
{
    extern std::string user;
    
    output->setDefaultBackground(TCODColor(0, 0, 0));
    output->clear();
    render();
    
    char *prompt = (char *)"Username: ";
    TCODText *testText = new TCODText(MAIN_WIDTH/2 - 7, MAIN_HEIGHT/2 - 7, 36, 1, 16);
    testText->setProperties(33, 5, (const char *)prompt, 5);
    
    
    testText->render(output);
    render();
    
    bool quit = false;
    while(!quit)
    {
        TCOD_key_t key = TCODConsole::waitForKeypress(true);
        
        testText->update(key);
        
        testText->render(output);
        
        render();
        
        if(key.vk == TCODK_ENTER)
        {
            quit = true;
        }
        
    }
    
    const char *userName = testText->getText();
    
    user = userName;
    
    testText->reset();
    delete testText;
    output->clear();
    render();

}


void GraphicsTCOD::getPassword()
{

    extern std::string pass;
    output->clear();
    render();
    
    char *prompt = (char *)"Password: ";
    TCODText *testText = new TCODText(MAIN_WIDTH/2 - 7, MAIN_HEIGHT/2 - 7, 20, 1, 16);
    testText->setProperties(33, 5, (const char *)prompt, 5);

    testText->render(output);
    render();
    
    
    TCODText *inputText = new TCODText(MAIN_WIDTH/2 + 3, MAIN_HEIGHT/2 - 7, 20, 1, 16);
    inputText->setProperties(33, 5, (const char *)"", 5);
    //inputText->setColors(TCODColor(0,0,0), TCODColor(0,0,0), 1.0);
    
    inputText->render(output);
    render();
    
    bool quit = false;
    while(!quit)
    {
        TCOD_key_t key = TCODConsole::waitForKeypress(true);
        
        inputText->update(key);
        
        inputText->render(output);
        
        render();
        
        if(key.vk == TCODK_ENTER)
        {
            quit = true;
        }
        
    }
    
    const char *userPass = inputText->getText();
    
    pass = userPass;
    
    testText->reset();
    delete testText;
    
    inputText->reset();
    delete inputText;
    
    output->clear();
    render();
    
    extern bool drawLogin;
    drawLogin = false;
    extern bool drawNewAccount;
    drawNewAccount = false;
}


void GraphicsTCOD::loginError()
{
    
    output->clear();
    render();
    
    char *prompt = (char *)"Login Error - Invalid Username or Password";
    TCODText *loginErrorText = new TCODText(MAIN_WIDTH/2 - 20, MAIN_HEIGHT/2-7, 45, 1, 16);
    loginErrorText->setProperties(33, 5, (const char *)prompt, 5);
    loginErrorText->setColors(TCODColor(255,0,0), TCODColor(0,0,0), 1.0);
    
    loginErrorText->render(output);
    render();
    
    bool quit = false;
    while(!quit)
    {
        TCOD_key_t key = TCODConsole::checkForKeypress();
        
        if(key.vk == TCODK_ENTER)
        {
            quit = true;
        }
        
    }
    cout << "login error" << endl;
    
    loginErrorText->reset();
    output->clear();
    render();
    delete loginErrorText;
    
}


void GraphicsTCOD::render(){
    
    
    output->setDirty(0, 0, MAIN_WIDTH, MAIN_HEIGHT);
	TCODConsole::blit(output, 0, 0, MAP_WIDTH, MAP_HEIGHT, TCODConsole::root, 0, 0);
    
    TCODConsole::flush();
    
    
}

void GraphicsTCOD::flushScreen(){
    TCODConsole::flush();
    
}

void GraphicsTCOD::drawAt(int x, int y)
{
    if (cMap->returnVisible(x, y)){
        H = cMap->returnH(x, y);
        S = cMap->returnS(x, y);
        V = cMap->returnV(x, y);
        
        output->setCharBackground(x, y, TCODColor(0,0,0));
        output->setDefaultForeground(TCODColor(H, S, V));
        
        output->print(x, y, cMap->cMap[x][y]->symbol);
    }
    else{
        HD = cMap->returnHD(x, y);
        SD = cMap->returnSD(x, y);
        VD = cMap->returnVD(x, y);
        output->setCharBackground(x, y, TCODColor(0,0,0));
        output->setDefaultForeground(TCODColor(HD, SD, VD));
        
        output->print(x, y, cMap->cMap[x][y]->symbol);
    }
}


void GraphicsTCOD::drawAll(){
    
    for(int x = 0; x < MAP_WIDTH; x++)
    {
        for(int y=0; y < MAP_HEIGHT; y++)
        {
            if(!cMap->testIgnore(x, y))
                drawAt(x, y);
        }
    }
}





void GraphicsTCOD::prepare(int x, int y){
    
    if (!cMap->returnVisible(x, y) && cMap->returnExplored(x, y))
    {
        HD = cMap->returnHD(x, y);
        SD = cMap->returnSD(x, y);
        VD = cMap->returnVD(x, y);
        output->setCharBackground(x, y, TCODColor(0,0,0));
        output->setDefaultForeground(TCODColor(HD, SD, VD));
        
        output->print(x, y, cMap->cMap[x][y]->symbol);
    }
}



void GraphicsTCOD::clearScreen(){
    
	output->clear();
    
}













