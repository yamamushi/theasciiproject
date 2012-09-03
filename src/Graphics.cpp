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


#include "BoostLibs.h"
#include "constants.h"

#include "libtcod/libtcod.hpp"
#include "libtcod/gui/gui.hpp"

#include "Graphics.h"
#include "ClientWidgets.h"
#include "ClientSocket.h"
#include "ClientMap.h"


bool drawLogin;
bool drawNewAccount;
bool drawMenuCheck;
bool closeMenuCheck;

std::string user;
std::string pass;

ScrollBox *commandConsole;   // not to be confused with a libtcod console type
ScrollBox *sConsole;    // ditto



GraphicsTCOD::GraphicsTCOD(ClientMap *clientMap){
	init(clientMap);
}

void GraphicsTCOD::init(ClientMap *clientMap){
    
    cMap = clientMap;
    
    drawLogin = false;
    drawNewAccount = false;
    drawMenuCheck = false;
    closeMenuCheck = false;
    
    setlocale(LC_ALL, "en_US.UTF-8");
    TCODConsole::setCustomFont("data/font.png", TCOD_FONT_LAYOUT_ASCII_INROW | TCOD_FONT_TYPE_GRAYSCALE, 32, 2048);
    
    //TCODConsole::setCustomFont("data/arial12x12.png", TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
    TCODConsole::initRoot(MAIN_WIDTH,MAIN_HEIGHT,"The ASCII Project 0.0.0o",false,TCOD_RENDERER_SDL);
    //	TCODConsole::credits();
    
    TCODConsole *mainConsole = new TCODConsole(MAIN_WIDTH, MAIN_HEIGHT);
    TCODSystem::setFps(25);
    output = mainConsole;
    
    serverConsole = new TCODConsole(MAIN_WIDTH/2,13);
    textOutputConsole = new TCODConsole(MAIN_WIDTH/2+1,13);
    mapOutput = new TCODConsole(MAP_WINDOW_WIDTH, MAP_WINDOW_HEIGHT);
    
    
    //textOutputConsole->setDefaultForeground(TCODColor(0,255,0));
    //textOutputConsole->flush();
    TCODConsole::mapAsciiCodesToFont(0, 65535, 0, 0);
    mapOutput->mapAsciiCodesToFont(0, 65535, 0, 0);
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
    
    
    
    TCODConsole::setKeyboardRepeat(100, 10);
    
    output->setDefaultBackground(TCODColor(0, 0, 0));
    output->clear();
    render();
    
}



void GraphicsTCOD::drawMenu()
{
    Widget::setConsole(output);
    
    
    //new StatusBar(0,0,MAP_WINDOW_WIDTH,1);
    
    VBox *vbox=new VBox(MAIN_WIDTH/2 - 7,MAIN_HEIGHT/2 + 10,0);
    ToolBar *mainMenu = new ToolBar(MAIN_WIDTH/2 - 7,MAIN_HEIGHT/2 + 10,15,NULL,NULL);
    //stats->addWidget(new Label(MAP_WINDOW_WIDTH/2 - 7,MAP_WINDOW_HEIGHT/2 - 6,"Login","Login"));
    mainMenu->addWidget(new Button("Connect",NULL,loginCbk,NULL));
    //stats->addWidget(new Label(MAP_WINDOW_WIDTH/2 - 7,MAP_WINDOW_HEIGHT/2 - 5,"New Account","New Account"));
    //stats->addWidget(new Button("New Account",NULL,newAccountCbk,NULL));
	//stats->addWidget(new Label(MAP_WINDOW_WIDTH/2 - 7,MAP_WINDOW_HEIGHT/2 - 4,"Options","Options"));
    mainMenu->addWidget(new Button("Options",NULL,NULL,NULL));
    //stats->addWidget(new Label(MAP_WINDOW_WIDTH/2 - 7,MAP_WINDOW_HEIGHT/2 - 3,"Quit","Quit"));
    mainMenu->addWidget(new Button("Quit",NULL,quitCbk,NULL));
    vbox->addWidget(mainMenu);
    
    Widget::setBackgroundColor(TCODColor(0,0,0), TCODColor(128,128,128));
    Widget::setForegroundColor(TCODColor(255,255,255), TCODColor(255,255,255));
    
    Widget::renderWidgets();
    
    TCODMouse::showCursor(true);
    
    TCODImage *image = new TCODImage("data/images/MenuBackground.png");
    
    
    // bool quit = false;
    while(!TCODConsole::isWindowClosed())
    {
        TCOD_key_t key;
        TCOD_mouse_t mouse;
        
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&key,&mouse);
        Widget::updateWidgets(key,mouse);
        
        Widget::renderWidgets();
        
        render();
        
        image->blitRect(output, 2, 0);
        
        output->setDefaultForeground(TCODColor(255, 255, 255));
        output->print(MAIN_WIDTH-26, MAIN_HEIGHT-3, (const char*)"The ASCII Project 0.0.0o", TCOD_LEFT);
        output->print(MAIN_WIDTH-29, MAIN_HEIGHT-2, (const char*)"TheASCIIProject.com (c)2012", TCOD_LEFT);
        output->rect(0, 0, 20, 1, true);
        
        
        if(drawLogin || key.vk == TCODK_ENTER)
        {
            break;
        }
        else if( key.vk == TCODK_ESCAPE)
        {
            exit(0);
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

void GraphicsTCOD::menuCbk(Widget *w, void *userData)
{
    if(!drawMenuCheck)
        drawMenuCheck = true;
    else
        drawMenuCheck = false;
    
}

void GraphicsTCOD::closeMenuCbk(Widget *w, void *userData)
{
    if(closeMenuCheck)
        closeMenuCheck = false;
    else
        closeMenuCheck = true;
    
}


void GraphicsTCOD::drawMainInterface()
{
    Widget::setConsole(output);
    
    HBox *hMenu=new HBox(12,-1,0);
    ToolBar *menuToolbar = new ToolBar(0,0,6,NULL,NULL);
    menuToolbar->addWidget(new Button("Menu",NULL,menuCbk,NULL));
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
    
    
    
    
    chatBox = new ScrollBox(0, 0, textOutputConsole->getWidth(), textOutputConsole->getHeight(), 512, textOutputConsole, cMap, this);
    serverBox = new ScrollBox(0, 0, serverConsole->getWidth(), serverConsole->getHeight()-2, 512, serverConsole, cMap, this);
    //serverBox->setConsole(serverConsole);
    chatBox->setRealPosition(0, 32);
    chatBox->takeCommands(true);
    commandConsole = chatBox;
    
    serverBox->setRealPosition(MAIN_WIDTH/2, 32);
    serverBox->takeCommands(true);
    
    
    serverBox->insertText("Welcome to The ASCII Project");
    serverBox->insertText(" Version 0.0.0o ");
    serverBox->insertText(" ");
    serverBox->insertText("Tip: all server input begins with ");
    serverBox->insertText("The / character.");
    
    serverBox->insertText(" ");
    serverBox->insertText(" ");
    serverBox->insertText(" ");
    
    serverBox->insertText("Please /connect to continue...");
    
    sConsole = chatBox;
    
    inputText = new TCODText(1, serverConsole->getHeight()-2, serverConsole->getWidth()-2, 1, serverConsole->getWidth()-2);
    inputText->setProperties(32, 1000, "$>", 1);
    inputText->setColors(TCODColor(0,255,0), TCODColor(0,0,0), 1.0f);
    inputText->render(serverConsole);
    
    
    //offscreenConsole->print(0,0, "Welcome To The ASCII Project");
    serverConsole->hline(0,serverConsole->getHeight()-1, serverConsole->getWidth());
    serverConsole->hline(0,serverConsole->getHeight()-3, serverConsole->getWidth());
    serverConsole->vline(0,0, serverConsole->getHeight());
    serverConsole->vline(serverConsole->getWidth()-1,0, serverConsole->getHeight());
    
    bool textInput = false;
    bool popupOpen = false;
    
    
    
    //bool placeActionMode = false;
    
    connected = false;
    loggedIn = false;
    commandMode = false;
    APIinQueue = false;
    chatMessageInQueue = false;
    
    actionMode = "placeFloor";
    chatText = "";
    
    boost::asio::io_service pri_io_service;
    tcp::resolver pri_resolver(pri_io_service);
    
    if(DEBUG_MODE)
    {
        tcp::resolver::query pri_query("localhost", "5250");
        
        tcp::resolver::iterator iterator = pri_resolver.resolve(pri_query);
        
        cnet = new ClientSession(pri_io_service, iterator, cMap, this);
        
        
    }
    else
    {
        tcp::resolver::query pri_query("pub.theasciiproject.com", "5250");
        
        tcp::resolver::iterator iterator = pri_resolver.resolve(pri_query);
        
        cnet = new ClientSession(pri_io_service, iterator, cMap, this);
        
        
        
    }
    
    boost::thread netThread(&GraphicsTCOD::requestMap, this);
    
    
    //TCODConsole::disableKeyboardRepeat();
    
    
    while( !TCODConsole::isWindowClosed() )
    {
        TCOD_key_t key;
        TCOD_mouse_t mouse;
        
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&key,&mouse);
        Widget::updateWidgets(key,mouse);
        
        if(!popupOpen)
        {
            if(textInput)
                inputText->update(key);
            
            chatBox->update(mouse);
            serverBox->update(mouse);
            
            
            
        }
        
        
        
        
        
        
        
        
        if(drawMenuCheck)
        {
            menuPopup=new VBox(35,10,0);
            ToolBar *menuPopupOptions = new ToolBar(0,0,6,NULL,NULL);
            menuPopupOptions->addWidget(new Button("Return",NULL,closeMenuCbk,NULL));
            menuPopupOptions->addWidget(new Button("Quit",NULL,quitCbk,NULL));
            menuPopup->addWidget(menuPopupOptions);
            
            popupOpen = true;
            drawMenuCheck = false;
        }
        
        if(closeMenuCheck)
        {
            menuPopup->clear();
            delete menuPopup;
            output->clear();
            
            fixBottom();
            
            popupOpen = false;
            closeMenuCheck = false;
        }
        
        if(!textInput && loggedIn)
        {
            
            if(key.vk == TCODK_SPACE)
            {
                if(commandMode)
                    commandMode = false;
                else
                    commandMode = true;
            }
            if(key.vk == TCODK_UP)
            {
                apiCall = "/8";
                APIinQueue = true;
            }
            else if(key.vk == TCODK_DOWN)
            {
                
                apiCall = "/2";
                APIinQueue = true;
            }
            else if(key.vk == TCODK_RIGHT)
            {
                
                apiCall = "/6";
                APIinQueue = true;
            }
            else if(key.vk == TCODK_LEFT)
            {
                
                apiCall = "/4";
                APIinQueue = true;
            }
            
            else if(key.c == 'w' && !commandMode)
            {
                
                apiCall = "/8";
                APIinQueue = true;
                
                
            }
            else if(key.c == 'a' && !commandMode)
            {
                
                apiCall = "/4";
                APIinQueue = true;
                
                
            }
            else if(key.c == 's' && !commandMode)
            {
                
                apiCall = "/2";
                APIinQueue = true;
                
            }
            else if(key.c == 'd' && !commandMode)
            {
                
                apiCall = "/6";
                APIinQueue = true;
                
            }
            
            
            
            else if(key.c == '<' && !commandMode)
            {
                
                apiCall = "/5";
                APIinQueue = true;
                
            }
            else if(key.c == '>' && !commandMode)
            {
                
                apiCall = "/15";
                APIinQueue = true;
            }
            
            else if(key.c == 'i' && !commandMode)
            {
                if(actionMode == "removeTile")
                    apiCall = "/18";
                else if(actionMode == "placeWall")
                    apiCall = "/28";
                else if(actionMode == "placeFloor")
                    apiCall = "/38";
                else if(actionMode == "digHole")
                    apiCall = "/48";
                
                APIinQueue = true;
                
            }
            else if(key.c == 'j' && !commandMode)
            {
                if(actionMode == "removeTile")
                    apiCall = "/14";
                else if(actionMode == "placeWall")
                    apiCall = "/24";
                else if(actionMode == "placeFloor")
                    apiCall = "/34";
                else if(actionMode == "digHole")
                    apiCall = "/44";
                
                
                APIinQueue = true;
                
                
            }
            else if(key.c == 'k' && !commandMode)
            {
                if(actionMode == "removeTile")
                    apiCall = "/12";
                else if(actionMode == "placeWall")
                    apiCall = "/22";
                else if(actionMode == "placeFloor")
                    apiCall = "/32";
                else if(actionMode == "digHole")
                    apiCall = "/42";
                
                APIinQueue = true;
                
            }
            else if(key.c == 'l' && !commandMode)
            {
                if(actionMode == "removeTile")
                    apiCall = "/16";
                else if(actionMode == "placeWall")
                    apiCall = "/26";
                else if(actionMode == "placeFloor")
                    apiCall = "/36";
                else if(actionMode == "digHole")
                    apiCall = "/46";
                
                APIinQueue = true;
                
            }
            else if(key.c == 'u' && !commandMode)
            {
                if(actionMode == "digHole")
                {
                    apiCall = "/25";
                    
                    APIinQueue = true;
                }
                
            }
            else if(key.c == 'o' && !commandMode)
            {
                if(actionMode == "digHole")
                {
                    apiCall = "/35";
                    
                    APIinQueue = true;
                }
                
            }
            
            
            else if((key.c == 'd' || key.c == 'r') && commandMode)
            {
                actionMode = "removeTile";
            }
            else if(key.c == 'w' && commandMode)
            {
                actionMode = "placeWall";
            }
            else if(key.c == 'D' && commandMode)
            {
                actionMode = "digHole";
            }
            else if(key.c == 'f' && commandMode)
            {
                actionMode = "placeFloor";
            }
            
        }
        
        
        
        
        
        
        if(key.vk == TCODK_ESCAPE)
        {
            if(!textInput && !popupOpen)
            {
                drawMenuCheck = true;
                
            }
            
            inputText->reset();
            textInput = false;
            
            if(popupOpen)
            {
                closeMenuCheck = true;
            }
        }
        
        if(key.vk == TCODK_ENTER && textInput == true)
        {
            
            
            std::string tmpText = inputText->getText();
            
            if(tmpText != "" && tmpText.at(0) != '/')
            {
                if(!connected)
                {
                    
                    chatText = tmpText;
                    serverBox->insertText(chatText);
                    chatText = "";
                }
                else
                {
                    //chatText.clear();
                    chatText = tmpText;
                    chatMessageInQueue = true;
                    
                }
                
            }
            if(tmpText != "" &&  tmpText.at(0) == '/')
            {
                if(tmpText == "/connect" && !connected)
                {
                    // Begin Networking
                    
                    if(cnet->Connect())
                    {
                        chatBox->insertText("Connected Successfully");
                        chatBox->insertText(" ");
                        cnet->getLoginScreen();
                        chatBox->insertText(" ");
                        chatBox->insertText(" ");
                        connected = true;
                    }
                    else
                    {
                        chatBox->insertText("Failed to Connect, please retry");
                        connected = false;
                        
                    }
                    
                }
                else if(tmpText == "/connect" && connected)
                {
                    chatBox->insertText("Already Connected");
                }
                else if(tmpText == "/quit"  && connected)
                {
                    serverCommandInQueue = true;
                    serverCall = "/quit";
                    
                }
                else if (tmpText == "/quit" && !connected)
                {
                    exit(0);
                }
                else
                {
                    if(!connected)
                    {
                        chatBox->insertText("Not Connected, please /connect first");
                        
                    }
                    else if(connected && !loggedIn)
                    {
                        cnet->sendCommand(tmpText);
                        cnet->getResponse();
                    }
                    
                    else if(connected && loggedIn)
                    {
                        serverCommandInQueue = true;
                        serverCall = tmpText;
                    }
                }
            }
            
            inputText->reset();
            delete inputText;
            
            inputText = new TCODText(1, serverConsole->getHeight()-2, serverConsole->getWidth()-2, 1, serverConsole->getWidth()-2);
            inputText->setProperties(32, 1000, "$>", 1);
            inputText->setColors(TCODColor(0,255,0), TCODColor(0,0,0), 1.0f);
            
            textInput = false;
            
        }
        else if(key.vk == TCODK_ENTER && textInput == false)
        {
            textInput = true;
        }
        
        //mapOutput->clear();
        
        if(connected && loggedIn && !commandMode)
        {
            mapOutput->setDefaultForeground(TCODColor(255,255,255));
            mapOutput->printEx(mapOutput->getWidth()/2, mapOutput->getHeight()-1, TCOD_BKGND_NONE, TCOD_CENTER, "Action Mode", TCODColor(255,255,255));
        }
        else if(connected && loggedIn && commandMode)
        {
            mapOutput->setDefaultForeground(TCODColor(255,255,255));
            mapOutput->printEx(mapOutput->getWidth()/2, mapOutput->getHeight()-1, TCOD_BKGND_NONE, TCOD_CENTER, "Select Mode", TCODColor(255,255,255));
        }
        
        //requestMap();
        drawAll();
        TCODConsole::blit(mapOutput, 0, 0, 0, 0, output, 0, 2);
        inputText->render(serverConsole);
        chatBox->render();
        serverBox->render();
        Widget::renderWidgets();
        fixBottom();
        
        
        
        TCODConsole::blit(serverConsole,0,0,0,0,output,MAIN_WIDTH/2,32, 1.0f, 1.0f);
        TCODConsole::blit(textOutputConsole,0,0,0,0,output,0,32, 1.0f, 1.0f);
        render();
        //mapOutput->clear();
        
        
        /* if((key.c == 'a' || key.c == 's' || key.c == 'w' || key.c == 'd') && connected && loggedIn && !textInput)
         {
         while(key.vk != TCODK_NONE)
         {
         TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&key,&mouse);
         }
         } */
        
        
    }
    
    
    
}



void GraphicsTCOD::requestMap()
{
    
    
    while(true)
    {
        if(connected && loggedIn)
        {
            
            if(connected && APIinQueue)
            {
                
                cnet->sendCommand(apiCall);
                cnet->ignoreResponse();
                APIinQueue = false;
                
            }
            
            if(connected && serverCommandInQueue)
            {
                
                cnet->sendCommand(serverCall);
                cnet->getResponse();
                
                serverCommandInQueue = false;
                
                if(serverCall == "/quit")
                {
                    cnet->close();
                    connected = false;
                    loggedIn = false;
                    //break;
                }
                
            }
            
            if(connected)
            {
                //if(chatMessageInQueue)
                {
                    //cnet->sendCommand("/0");
                    //cnet->ignoreResponse();
                    cnet->sendCommand("/chat");
                    cnet->getChatMessage();
                    cnet->sendChatMessage(chatText);
                    chatText.clear();
                    cnet->ignoreResponse();
                    
                    if(chatMessageInQueue)
                    {
                        
                        chatMessageInQueue = false;
                    }
                    
                    
                    
                    cnet->sendCommand("/0");
                    cnet->ignoreResponse();
                    
                }
                /*  else
                 {
                 chatText = "";
                 cnet->sendCommand("/chat");
                 cnet->sendChatMessage(chatText);
                 cnet->getChatMessage();
                 } */
                
            }
            
            //cMap->clientRefresh();
            
            if(connected && loggedIn)
            {
                cnet->sizeMap();
                int dataSize = cnet->confirmSize();
                cnet->sendCommand("/");
                if(dataSize > 0)
                    cnet->read_map(dataSize);
            }
            
            //boost::posix_time::seconds sleepTime(1);
            //boost::this_thread::sleep(sleepTime);
            
        }
    }
    
}


void GraphicsTCOD::fixBottom()
{
    
    output->rect(0, 0, 8, 3, true);
    
    output->setColorControl(TCOD_COLCTRL_1, TCODColor(255,255,255), TCODColor(0,0,0));
    
    output->vline(MAIN_WIDTH/2, 32, 13);
    output->hline(0, 32, MAIN_WIDTH);
    output->hline(MAIN_WIDTH/2 + 1, MAIN_HEIGHT-3, MAIN_HEIGHT/2);
    output->hline(0, MAIN_WIDTH-1, MAIN_HEIGHT);
    output->vline(MAIN_WIDTH-1, 32, 13);
    
    output->print(MAIN_WIDTH/2, 32, L"\u2566", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    output->print(MAIN_WIDTH/2, MAIN_HEIGHT-3, L"\u2560", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    output->print(MAIN_WIDTH/2, MAIN_HEIGHT-1, L"\u2569", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    output->print(0, 32, L"\u2554", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    output->print(0, MAIN_WIDTH-1, L"\u255A", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    output->print(MAIN_WIDTH-1, 32, L"\u2557", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    output->print(MAIN_WIDTH-1, MAIN_HEIGHT-1, L"\u255D", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    output->print(MAIN_WIDTH-1, MAIN_HEIGHT-3, L"\u2563", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    
    serverConsole->print(0,0,L"\u2566", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    serverConsole->print(0,serverConsole->getHeight()-3,L"\u2560", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    serverConsole->print(0,serverConsole->getHeight()-1,L"\u2569", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    serverConsole->print(serverConsole->getWidth()-1,serverConsole->getHeight()-3,L"\u2563", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    serverConsole->print(serverConsole->getWidth()-1,serverConsole->getHeight()-1,L"\u255D", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    
    textOutputConsole->print(textOutputConsole->getWidth()-1,0,L"\u2566", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    textOutputConsole->print(textOutputConsole->getWidth()-1,textOutputConsole->getHeight()-1,L"\u2569", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    textOutputConsole->print(textOutputConsole->getWidth()-1,textOutputConsole->getHeight()-3,L"\u2560", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    
}


void GraphicsTCOD::render(){
    
    //drawAll();
    
    
    
	TCODConsole::blit(output, 0, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);
    
    TCODConsole::flush();
    
    
    
}

void GraphicsTCOD::flushScreen(){
    TCODConsole::flush();
    
}

void GraphicsTCOD::drawAt(int x, int y)
{
    if (cMap->returnVisible(x, y) || cMap->returnExplored(x,y))
    {
        H = cMap->returnH(x, y);
        S = cMap->returnS(x, y);
        V = cMap->returnV(x, y);
        
        mapOutput->setCharBackground(x, y, TCODColor(0,0,0));
        mapOutput->setDefaultForeground(TCODColor((float)H, (float)S, (float)V));
        
        mapOutput->print(x, y, (const wchar_t*)cMap->cMap[x][y]->symbol);
    }
}


void GraphicsTCOD::drawAll()
{
    
    for(int x = 0; x < MAP_WINDOW_WIDTH; x++)
    {
        for(int y=0; y < MAP_WINDOW_HEIGHT; y++)
        {
            
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
        mapOutput->setCharBackground(x, y, TCODColor(0,0,0));
        mapOutput->setDefaultForeground(TCODColor(HD, SD, VD));
        
        mapOutput->print(x, y, cMap->cMap[x][y]->symbol);
    }
}



void GraphicsTCOD::clearScreen(){
    
	output->clear();
    
}













