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
#include <stdio.h>
#include <stdarg.h>

TCOD_renderer_t UmbraEngine::renderer = TCOD_RENDERER_SDL;
UmbraEngine * UmbraEngine::engineInstance = NULL;

// specific parser for module.txt file
class UmbraModuleConfigParser: public ITCODParserListener {
private:
	// name of the chain to parse. If NULL, use the first one in the file
	const char * chainName;
	// current module being parsed
	UmbraModule * module;
	// shall we skip the current moduleChain ?
	bool skip;
	// whether the active chain has already been parsed (skip other chains)
	bool chainDone;
	// factory that creates a module from its name
	UmbraModuleFactory *factory;
	// module to activate
	TCODList<UmbraModule *> toActivate;
	// custom parameters defined at the module chain level
	TCODList<UmbraModule::UmbraModuleParametre> chainParameters;
	// all the modules in the chain
	TCODList<UmbraModule *> chainModules;
public :
	UmbraModuleConfigParser(UmbraModuleFactory *factory,const char *chainName): chainName(chainName), module(NULL),skip(false),chainDone(false),factory(factory) {
	}
    bool parserNewStruct(TCODParser * parser, const TCODParserStruct * str, const char * name) {
    	if (strcmp(str->getName(),"moduleChain") == 0) {
    		chainModules.clear();
    		//parse a new module chain
			if (chainDone || (chainName && strcmp(name,chainName) != 0)) {
				//this is not the chain we're looking for. skip it
				skip = true;
			}
		} else if (strcmp(str->getName(),"module") == 0 && !skip) {
			//parse a module for current chain
			if (UmbraEngine::getInstance()->isNameFree(name)) {
				// module doesn't exist yet. try to get it from the factory
				if (factory) {
					module = factory->createModule(name);
					if ( module ) UmbraEngine::getInstance()->registerModule(module,name);
				}
				if (! module) {
					// could not get the module. abort
					char tmp[256];
					sprintf(tmp,"Unknown module '%s'",name);
					error(tmp);
					return false;
				}
			}
			chainModules.push(module);
		}
		return true;
	}
    bool parserFlag(TCODParser * parser, const char * name) {
    	if (skip) return true;
    	if (strcmp(name,"active") == 0) {
    		// deferred activation (cannot activate before all params have been parsed)
    		toActivate.push(module);
		}
		return true;
	}
    bool parserProperty(TCODParser * parser, const char * name, TCOD_value_type_t type, TCOD_value_t value) {
    	if (skip) return true;
    	if (strcmp(name,"timeout") == 0) {
    		module->setTimeout(value.i);
    	} else if (strcmp(name,"priority") == 0) {
    		module->setPriority(value.i);
    	} else if (strcmp(name,"fallback") == 0) {
    		UmbraModule *fallback = UmbraEngine::getInstance()->getModule(value.s);
    		if (! fallback) {
    			// fallback references a module that doesn't exist yet. get it from the factory
				if (factory) {
					fallback = factory->createModule(value.s);
					if ( fallback ) {
						UmbraEngine::getInstance()->registerModule(fallback,value.s);
					}
				}
				if (! fallback) {
					char tmp[256];
					sprintf(tmp,"Unknown module '%s'",value.s);
					error(tmp);
					return false;
				}
			}
			module->setFallback(value.s);
		} else {
    		// dynamically declared property.
    		if ( module ) {
    			// at module level
    			module->setParametre(name,value);
    		} else {
    			// at module chain level
				UmbraModule::UmbraModuleParametre mod;
				mod.name=strdup(name); 
				mod.value=value;
				chainParameters.push(mod);
			}
		}
		return true;
	}
    bool parserEndStruct(TCODParser * parser, const TCODParserStruct * str, const char * name) {
    	if (strcmp(str->getName(),"moduleChain") == 0) {
    		if (skip) {
    			skip = false;
			} else {
				//finished parsing requested chain. skip other chains
				// copy module chain parameters into modules
				for (UmbraModule **mod=chainModules.begin();mod!=chainModules.end(); mod++) {
					// inherits all chain parameters 
					// those parameters can be overloaded in the module declaration
					for (UmbraModule::UmbraModuleParametre *chainParam=chainParameters.begin(); chainParam != chainParameters.end(); chainParam++) {
						UmbraModule::UmbraModuleParametre moduleParam=(*mod)->getParametre(chainParam->name);
						if( moduleParam.name == NULL ) {
							(*mod)->setParametre(chainParam->name,chainParam->value);
						} // else parameter overloaded by the module. 
					}
				}
				// activate active modules
				for (UmbraModule **it=toActivate.begin(); it != toActivate.end(); it++) {
					UmbraEngine::getInstance()->activateModule(*it);
				}
				chainDone=true;
			}
		} else if (strcmp(str->getName(),"module") == 0 ) {
			module=NULL;
		}
		return true;
	}
    void error(const char * msg) {
    	UmbraLog::error("UmbraModuleConfigParser | %s",msg);
	}
};

//constructor
UmbraEngine::UmbraEngine (const char *fileName, UmbraRegisterCallbackFlag flag): keyboardMode(UMBRA_KEYBOARD_RELEASED) {
	UmbraLog::openBlock("UmbraEngine::UmbraEngine | Instantiating the engine object.");
	//load configuration variables
	UmbraConfig::load(fileName);
	paused = false;
	setWindowTitle("%s ver. %s (%s)", UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS);
	engineInstance = this;
	//register internal modules
	registerInternalModule(UMBRA_INTERNAL_SPEEDOMETER,new UmbraModSpeed());
	registerInternalModule(UMBRA_INTERNAL_BSOD,new UmbraModBSOD());
	registerInternalModule(UMBRA_INTERNAL_CREDITS,new UmbraModCredits());
	//register default callbacks
	if (flag & UMBRA_REGISTER_DEFAULT) {
		registerCallback(new UmbraCallbackQuit());
		registerCallback(new UmbraCallbackFullscreen());
		registerCallback(new UmbraCallbackScreenshot());
		registerCallback(new UmbraCallbackFontUp());
		registerCallback(new UmbraCallbackFontDown());
		registerCallback(new UmbraCallbackPause());
	}
	if (flag & UMBRA_REGISTER_ADDITIONAL) {
		registerCallback(new UmbraCallbackSpeedometer());
	}
	UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
}

UmbraEngine::UmbraEngine (const char *fileName): keyboardMode(UMBRA_KEYBOARD_RELEASED) {
	UmbraLog::openBlock("UmbraEngine::UmbraEngine | Instantiating the engine object.");
	//load configuration variables
	UmbraConfig::load(fileName);
	paused = false;
	setWindowTitle("%s ver. %s (%s)", UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS);
	engineInstance = this;
	//register internal modules
	registerInternalModule(UMBRA_INTERNAL_SPEEDOMETER,new UmbraModSpeed());
	registerInternalModule(UMBRA_INTERNAL_BSOD,new UmbraModBSOD());
	registerInternalModule(UMBRA_INTERNAL_CREDITS,new UmbraModCredits());
	//register default callbacks
	registerCallback(new UmbraCallbackQuit());
	registerCallback(new UmbraCallbackFullscreen());
	registerCallback(new UmbraCallbackScreenshot());
	registerCallback(new UmbraCallbackFontUp());
	registerCallback(new UmbraCallbackFontDown());
	registerCallback(new UmbraCallbackPause());
	UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
}

UmbraEngine::UmbraEngine (UmbraRegisterCallbackFlag flag): keyboardMode(UMBRA_KEYBOARD_RELEASED) {
	UmbraLog::openBlock("UmbraEngine::UmbraEngine | Instantiating the engine object.");
	//load configuration variables
	UmbraConfig::load("data/cfg/umbra.txt");
	paused = false;
	setWindowTitle("%s ver. %s (%s)", UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS);
	engineInstance = this;
	//register internal modules
	registerInternalModule(UMBRA_INTERNAL_SPEEDOMETER,new UmbraModSpeed());
	registerInternalModule(UMBRA_INTERNAL_BSOD,new UmbraModBSOD());
	registerInternalModule(UMBRA_INTERNAL_CREDITS,new UmbraModCredits());
	//register default callbacks
	if (flag & UMBRA_REGISTER_DEFAULT) {
		registerCallback(new UmbraCallbackQuit());
		registerCallback(new UmbraCallbackFullscreen());
		registerCallback(new UmbraCallbackScreenshot());
		registerCallback(new UmbraCallbackFontUp());
		registerCallback(new UmbraCallbackFontDown());
		registerCallback(new UmbraCallbackPause());
	}
	if (flag & UMBRA_REGISTER_ADDITIONAL) {
		registerCallback(new UmbraCallbackSpeedometer());
	}
	UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
}

UmbraEngine::UmbraEngine (): keyboardMode(UMBRA_KEYBOARD_RELEASED) {
	UmbraLog::openBlock("UmbraEngine::UmbraEngine | Instantiating the engine object.");
	//load configuration variables
	UmbraConfig::load("data/cfg/umbra.txt");
	paused = false;
	setWindowTitle("%s ver. %s (%s)", UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS);
	engineInstance = this;
	//register internal modules
	registerInternalModule(UMBRA_INTERNAL_SPEEDOMETER,new UmbraModSpeed());
	registerInternalModule(UMBRA_INTERNAL_BSOD,new UmbraModBSOD());
	registerInternalModule(UMBRA_INTERNAL_CREDITS,new UmbraModCredits());
	//register default callbacks
	registerCallback(new UmbraCallbackQuit());
	registerCallback(new UmbraCallbackFullscreen());
	registerCallback(new UmbraCallbackScreenshot());
	registerCallback(new UmbraCallbackFontUp());
	registerCallback(new UmbraCallbackFontDown());
	registerCallback(new UmbraCallbackPause());
	UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
}

void UmbraEngine::setWindowTitle (const char * title, ...) {
	char f[512];
	va_list ap;
	va_start(ap,title);
	vsprintf(f,title,ap);
	va_end(ap);
	windowTitle = (const char *)f;
}

void UmbraEngine::setWindowTitle (std::string title) {
	windowTitle = title.c_str();
}

//check whether there already exists a module with a given name
bool UmbraEngine::isNameFree(const char * name) {
	for (UmbraModule **it=modules.begin(); it != modules.end(); it++)
		if ( (*it)->name.compare(name) == 0 ) return false;
	return true;
}

//add a module to the modules list
int UmbraEngine::registerModule (UmbraModule * module, const char * name) {
	if (name != NULL) UmbraLog::info("UmbraEngine::registerModule | Registering a module named \"%s\".",name);
	else UmbraLog::info("UmbraEngine::registerModule | Registering a module.");
	modules.push(module);
	char n[2048];
	if (name == NULL) {
		if ( module->name == "" ) sprintf(n,"module%d",modules.size()-1);
		else strcpy(n,module->name.c_str());
	} else strcpy(n,name);
	module->setName(n);
	module->id = modules.size()-1;
	return module->id;
}

// fetch a pointer to a module from its name
UmbraModule * UmbraEngine::getModule (const char *name) {
	for (UmbraModule **it=modules.begin(); it != modules.end(); it++) {
		if ( (*it)->name.compare(name) == 0 ) return *it;
	}
	UmbraLog::error("UmbraEngine::getModule | Tried to retrieve a module named \"%s\", but such a module was not found.",name);
	return NULL;
}

// get module id from its reference
int UmbraEngine::getModuleId(UmbraModule *mod) {
	if (!mod || mod == NULL) {
		UmbraLog::error("UmbraEngine::getModuleId | Tried to retrieve the module's ID, but the pointer to a module given either is NULL or points to an invalid module.");
		displayError();
		return -1;
	}
	else return mod->getID();
}

//get module ID from the name
int UmbraEngine::getModuleId (const char * name) {
	UmbraModule * mod = getModule(name);
	if (!mod || mod == NULL) {
		UmbraLog::error("UmbraEngine::getModuleId | Tried to retrieve the module's ID, but could not get a module pointer based on the specified name \"%s\".",name);
		displayError();
		return -1;
	}
	else return mod->getID();
}

//register a font
void UmbraEngine::registerFont (int columns, int rows, const char * filename, int flags) {
	UmbraLog::openBlock("UmbraEngine::registerFont | Registering font \"%s\"",filename);
	if (!TCODSystem::fileExists(filename)) {
		UmbraLog::error("UmbraEngine::registerFont | Tried to register a font file that does not exist: %s.",filename);
		UmbraLog::closeBlock(UMBRA_LOGRESULT_FAILURE);
		return;
	}
	UmbraFont * file = new UmbraFont; //don't delete this later
	file->initialise(columns,rows,filename,flags);
	UmbraConfig::registerFont(file);
	UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
}

// temporary internal font storage structure
struct TmpFontData {
	int rows;
	int columns;
	char name[512];
	int flags;
	int size;
};

#define MAX_FONTS 16
bool UmbraEngine::registerFonts () {
	UmbraLog::openBlock("UmbraEngine::registerFonts | Attempting to automatically register fonts.");
	// if fonts registered by the user, do nothing
	if (getNbFonts() > 0) return true;
	TmpFontData dat[MAX_FONTS];
	TCODList<TmpFontData *> fontDataList;
	// look for font*png in font directory
	TCODList<const char *> dir=TCODSystem::getDirectoryContent(getFontDir(),"font*.png");
	if (dir.size() > 0) {
		int fontNum=0;
		for (const char **fontName = dir.begin(); fontName != dir.end() && fontNum < MAX_FONTS; fontName++) {
			int charWidth;
			int charHeight;
			char layout[32]="";
			if (sscanf(*fontName,"font%dx%d%s",&charWidth,&charHeight,layout) >= 2) {
				if (charWidth > 0 && charHeight > 0) {
					int fontFlag = TCOD_FONT_TYPE_GREYSCALE;
					if (layout[0] == '_') {
						// parse font layout
						if (strncasecmp(layout,"_TCOD.",6) == 0) fontFlag |= TCOD_FONT_LAYOUT_TCOD;
						else if (strncasecmp(layout,"_INCOL.",7) == 0) fontFlag |= TCOD_FONT_LAYOUT_ASCII_INCOL;
						else if (strncasecmp(layout,"_INROW.",7) == 0) fontFlag |= TCOD_FONT_LAYOUT_ASCII_INROW;
					} else {
						// default is TCOD |GREYSCALE
						fontFlag|=TCOD_FONT_LAYOUT_TCOD;
					}
					// compute font grid size from image size & char size
					int w,h;
					sprintf(dat[fontNum].name,"%s/%s",getFontDir(),*fontName);
					TCODImage tmp(dat[fontNum].name);
					tmp.getSize(&w,&h);
					dat[fontNum].size = charWidth*charHeight;
					dat[fontNum].rows=h/charHeight;
					dat[fontNum].columns=w/charWidth;
					dat[fontNum].flags=fontFlag;
					// sort this font by size
					int idx=0;
					while (idx < fontDataList.size() && fontDataList.get(idx)->size < dat[fontNum].size) idx ++;
					fontDataList.insertBefore(&dat[fontNum],idx);
					fontNum++;
				}
			}
		}
		for (TmpFontData **dat=fontDataList.begin(); dat != fontDataList.end(); dat ++) {
			// register the fonts from smallest to biggest
			registerFont((*dat)->columns,(*dat)->rows,(*dat)->name,(*dat)->flags);
		}
	}
	else {
		UmbraLog::fatalError("UmbraEngine::registerFonts | No fonts registered. The font directory \"%s\" is empty.",getFontDir());
		UmbraLog::closeBlock(UMBRA_LOGRESULT_FAILURE);
		return false;
	}

	if (getNbFonts() == 0) {
		UmbraLog::fatalError("UmbraEngine::registerFonts | No fonts registered. Autodetection found no fonts matching the naming pattern font<WIDTH>x<HEIGHT>[_<LAYOUT>].png in the specified directory \"%s\".",getFontDir());
		UmbraLog::closeBlock(UMBRA_LOGRESULT_FAILURE);
		return false;
	}
	else {
		UmbraLog::info("UmbraEngine::registerFonts | Successfully registered %d fonts.",getNbFonts());
		UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
		return true;
	}
}

// load external module configuration
bool UmbraEngine::loadModuleConfiguration(const char *filename, UmbraModuleFactory *factory, const char *chainName) {
	if (chainName == NULL && filename == NULL) UmbraLog::openBlock("UmbraEngine::loadModuleConfiguration | Attempting to load module configuration.");
	else if (chainName == NULL && filename != NULL) UmbraLog::openBlock("UmbraEngine::loadModuleConfiguration | Attempting to load a module configuration from file \"%s\".",filename);
	else if (chainName != NULL && filename == NULL) UmbraLog::openBlock("UmbraEngine::loadModuleConfiguration | Attempting to load \"%s\" module configuration.",chainName);
	else UmbraLog::openBlock("UmbraEngine::loadModuleConfiguration | Attempting to load \"%s\" module configuration from file \"%s\".",chainName,filename);
	//TODO: if file name == NULL, retrieve from UmbraConfig
	if (!filename) {
		UmbraLog::fatalError("UmbraEngine::loadModuleConfiguration | specified an empty filename.");
		UmbraLog::closeBlock(UMBRA_LOGRESULT_FAILURE);
		return false; // no configuration file is defined
	}
	if (!TCODSystem::fileExists(filename)) {
		UmbraLog::fatalError("UmbraEngine::loadModuleConfiguration | there exists no file with the specified filename \"%s\".",filename);
		UmbraLog::closeBlock(UMBRA_LOGRESULT_FAILURE);
		return false; // file doesn't exist
	}
	TCODParser parser;
	TCODParserStruct * moduleChain = parser.newStructure("moduleChain");
	TCODParserStruct * module = parser.newStructure("module");
	moduleChain->addStructure(module);
	module->addProperty("timeout",TCOD_TYPE_INT,false);
	module->addProperty("priority",TCOD_TYPE_INT,false);
	module->addProperty("fallback",TCOD_TYPE_STRING,false);
	module->addFlag("active");
	if (chainName == NULL && UmbraConfig::moduleChain != NULL) {
		parser.run(filename,new UmbraModuleConfigParser(factory,UmbraConfig::moduleChain));
	}
	else parser.run(filename,new UmbraModuleConfigParser(factory,chainName));
	UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
	return true;
}

// load external module configuration
bool UmbraEngine::loadModuleConfiguration(const char *filename, const char *chainName) {
	return loadModuleConfiguration(filename,NULL,chainName);
}

// public function registering the module for activation next frame, by id
void UmbraEngine::activateModule (int moduleId) {
	if ( moduleId < 0 || moduleId >= modules.size() ) {
		UmbraLog::warning("UmbraEngine::activateModule | Tried to activate an invalid module: ID %d.",moduleId);
		displayError();
		return;
	}
	UmbraModule *module = modules.get(moduleId);
	activateModule(module);
}

//public function registering an internal module for activation next frame, by id
void UmbraEngine::activateModule (UmbraInternalModuleID id) {
	if (id < 0 || id >= UMBRA_INTERNAL_MAX) {
		UmbraLog::warning("UmbraEngine::activateModule | Tried to activate an invalid internal module: ID %d.",(int)id);
		displayError();
		return;
	}
	activateModule(internalModules[id]);
}

// public function registering the module for activation next frame, by reference
void UmbraEngine::activateModule(UmbraModule *module) {
	if (module != NULL && ! module->getActive()) {
		toActivate.push(module);
		UmbraLog::info("UmbraEngine::activateModule | Activated module \"%s\" (ID: %d).",module->getName(),module->getID());
	}
}


void UmbraEngine::activateModule (const char *name) {
	UmbraModule *mod=getModule(name);
	if (mod) activateModule(mod);
	else {
		UmbraLog::warning("UmbraEngine::activateModule | Tried to activate a module named \"%s\", but such a module was not found.",name);
		displayError();
	}
}

// the internal function actually putting a module in active list
void UmbraEngine::doActivateModule( UmbraModule *mod ) {
  if (!mod->getActive()) {
	mod->setActive(true);
	mod->initialiseTimeout();
	//insert the module at the right pos, sorted by priority
		int idx = 0;
		while (idx < activeModules.size() && activeModules.get(idx)->getPriority() < mod->getPriority()) idx++;
		if (idx < activeModules.size()) activeModules.insertBefore(mod,idx);
		else activeModules.push(mod);
	}
}

// register the module for deactivation by id
void UmbraEngine::deactivateModule (int moduleId) {
	if (moduleId < 0 || moduleId >= modules.size()) {
		UmbraLog::warning("UmbraEngine::deactivateModule | Tried to deactivate an invalid module: ID %d.",moduleId);
		displayError();
	}
	UmbraModule *module = modules.get(moduleId);
	if (!module->getActive()) {
		UmbraLog::notice("UmbraEngine::deactivateModule | Tried to deactivate the module with an ID %d, but it's already inactive.",moduleId);
		displayError();
	}
	else deactivateModule(module);
}

void UmbraEngine::deactivateModule (UmbraInternalModuleID id) {
	if (id < 0 || id >= UMBRA_INTERNAL_MAX) {
		UmbraLog::warning("UmbraEngine::deactivateModule | Tried to deactivate an invalid internal module: ID %d.",(int)id);
		displayError();
	}
	else if (!internalModules[id]->getActive()) {
		UmbraLog::notice("UmbraEngine::deactivateModule | Tried to deactivate an internal module with an ID %d, but it's already inactive.",(int)id);
		displayError();
	}
	else deactivateModule(internalModules[id]);
}

// register the module for deactivation by reference
void UmbraEngine::deactivateModule(UmbraModule *module) {
	if (module != NULL && module->getActive()) {
		toDeactivate.push(module);
		module->setActive(false);
		UmbraLog::info("UmbraEngine::deactivateModule | Deactivated \"%s\" module (ID: %d).",module->getName(),module->getID());
	}
	else if (module != NULL && !module->getActive()) {
		UmbraLog::notice("UmbraEngine::deactivateModule | Tried to deactivate a module, but it's already inactive.");
		displayError();
	}
	else if (module == NULL) {
		UmbraLog::warning("UmbraEngine::deactivateModule | Tried to deactivate a module, but the module pointer given is null.");
		displayError();
	}
	else {
		UmbraLog::warning("UmbraEngine::deactivateModule | Tried to deactivate a module, but the module pointer given does not point to a module on the modules list.");
		displayError();
	}
}

void UmbraEngine::deactivateModule (const char *name) {
	UmbraModule *mod=getModule(name);
	if (mod)  {
		if (mod->getActive()) deactivateModule(mod);
		else {
			UmbraLog::notice("UmbraEngine::deactivateModule | Tried to deactivate a module named \"%s\", but it's already inactive.",name);
			displayError();
		}
	}
	else {
		UmbraLog::warning("UmbraEngine::deactivateModule | Tried to deactivate a module, but the module name \"%s\" was not found.",name);
		displayError();
	}
}

void UmbraEngine::deactivateAll (bool ignoreFallbacks) {
	UmbraLog::openBlock("UmbraEngine::deactivateAll | Deactivating all modules%s.",ignoreFallbacks ? ", ignoring fallbacks" : "");
	for (UmbraModule ** mod = activeModules.begin(); mod != activeModules.end(); mod++) {
		if (ignoreFallbacks) (*mod)->setFallback(-1);
		deactivateModule((*mod));
	}
	UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
}

bool UmbraEngine::initialise (TCOD_renderer_t renderer) {
	// autodetect fonts if needed
	bool retVal;
	UmbraLog::openBlock("UmbraEngine::initialise | Initialising the root console.");
	retVal = registerFonts();
	//activate the base font
	if (retVal) {
		UmbraEngine::renderer=renderer;
		UmbraConfig::activateFont();
		//initialise console
		TCODConsole::setCustomFont(UmbraConfig::font->filename(),UmbraConfig::font->flags(),UmbraConfig::font->columns(),UmbraConfig::font->rows());
		TCODConsole::initRoot(getRootWidth(),getRootHeight(),windowTitle.c_str(), UmbraConfig::fullScreen, renderer);
		TCODSystem::setFps(25);
		TCODMouse::showCursor(true);
		if (TCODConsole::root != NULL) UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
		else UmbraLog::closeBlock(UMBRA_LOGRESULT_FAILURE);
	}
	else UmbraLog::closeBlock(UMBRA_LOGRESULT_FAILURE);
	return retVal;
}

int UmbraEngine::run () {
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	memset(&mouse,0,sizeof(TCOD_mouse_t));
    
	if (modules.size() == 0) {
		//UmbraError::add(UMBRA_ERRORLEVEL_FATAL_ERROR,"UmbraEngine::run: No modules have been registered!");
		exit(1);
	}
    
	while(!TCODConsole::isWindowClosed()) {
		//execute only when paused
		if (paused) {
			TCODSystem::checkForEvent(TCOD_EVENT_KEY_RELEASE|TCOD_EVENT_MOUSE_RELEASE,&key,NULL);
			keyboard(key);
			TCODConsole::root->flush();
			continue; //don't update or render anything anew
		}
        
		// deactivate modules
		for (UmbraModule ** mod = toDeactivate.begin(); mod != toDeactivate.end(); mod++) {
			(*mod)->setActive(false);
			activeModules.remove(*mod);
		}
		toDeactivate.clear();
        
		// activate new modules
		for (UmbraModule ** mod = toActivate.begin(); mod != toActivate.end(); mod++) {
			doActivateModule(*mod);
		}
		toActivate.clear();
        
		if (activeModules.size() == 0) break; // exit game
        
		// update all active modules
		switch (keyboardMode) {
			case UMBRA_KEYBOARD_WAIT :
				TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&key,&mouse,true) ;
				break;
			case UMBRA_KEYBOARD_WAIT_NOFLUSH :
				TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&key,&mouse,false) ;
				break;
			case UMBRA_KEYBOARD_PRESSED :
				TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&key,&mouse) ;
				break;
			case UMBRA_KEYBOARD_PRESSED_RELEASED :
				TCODSystem::checkForEvent(TCOD_EVENT_KEY|TCOD_EVENT_MOUSE,&key,&mouse) ;
				break;
			case UMBRA_KEYBOARD_RELEASED :
			default :
				TCODSystem::checkForEvent(TCOD_EVENT_KEY_RELEASE|TCOD_EVENT_MOUSE,&key,&mouse) ;
				break;
		}
		keyboard(key);
		uint32 startTime=TCODSystem::getElapsedMilli();
		// update all active modules by priority order
		UmbraModule ** tmpMod;
		for (tmpMod = activeModules.begin(); tmpMod != activeModules.end(); tmpMod++) {
			if (!(*tmpMod)->getPause()) {
				// handle input
				(*tmpMod)->keyboard(key);
				(*tmpMod)->mouse(mouse);
				if ((*tmpMod)->isTimedOut(startTime) || !(*tmpMod)->update() || !(*tmpMod)->getActive()) {
					UmbraModule *module = *tmpMod;
					int fallback = module->getFallback();
					// deactivate module
					module->setActive(false);
					tmpMod = activeModules.remove(tmpMod);
					if (fallback != -1) {
						// register fallback for activation
						UmbraModule *fallbackModule = modules.get(fallback);
						if (fallbackModule != NULL && !fallbackModule->getActive()) toActivate.push(fallbackModule);
					}
				}
			}
		}
		uint32 updateTime=TCODSystem::getElapsedMilli() - startTime;
		TCODConsole::root->setDefaultBackground(TCODColor::black);
		TCODConsole::root->clear();
		// render active modules by inverted priority order
		for (tmpMod = activeModules.end(); tmpMod != activeModules.begin(); ) {
			tmpMod--;
			(*tmpMod)->render();
		}
		uint32 renderTime = TCODSystem::getElapsedMilli() - startTime - updateTime;
		if ( internalModules[UMBRA_INTERNAL_SPEEDOMETER]->getActive() ) {
			((UmbraModSpeed *)internalModules[UMBRA_INTERNAL_SPEEDOMETER])->setTimes(updateTime,renderTime);
		}
		//flush the screen
		TCODConsole::root->flush();
	}
	UmbraConfig::save();
	return 0;
}



void UmbraEngine::keyboard (TCOD_key_t &key) {
	if (key.vk == TCODK_NONE || key.pressed) return;

	UmbraKey k(key.vk, key.c, key.ralt|key.lalt, key.rctrl|key.lctrl, key.shift);

	bool val = false;

	for (UmbraCallback ** cbk = callbacks.begin(); cbk != callbacks.end(); cbk++) {
		if ((*cbk)->evaluate(k)) {
			(*cbk)->action();
			val = true;
			break;
		}
	}

	if (val) {
		// "erase" key event
		memset(&key,0,sizeof(TCOD_key_t));
	}
}

void UmbraEngine::reinitialise (TCOD_renderer_t renderer) {
	UmbraLog::openBlock("UmbraEngine::reinitialise | Reinitialising the root console.");
	delete TCODConsole::root;
	TCODConsole::root = NULL;
	TCODConsole::setCustomFont(UmbraConfig::font->filename(),UmbraConfig::font->flags(),UmbraConfig::font->columns(),UmbraConfig::font->rows());
	UmbraEngine::renderer=renderer;
	TCODConsole::initRoot(getRootWidth(),getRootHeight(),windowTitle.c_str(), UmbraConfig::fullScreen, this->renderer);
	if (TCODConsole::root != NULL) UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
	else UmbraLog::closeBlock(UMBRA_LOGRESULT_FAILURE);
}

void UmbraEngine::registerInternalModule (UmbraInternalModuleID id, UmbraModule * module) {
	UmbraLog::info("UmbraEngine::registerInternalModule | Registering an internal module.");
	internalModules[id] = module;
}

void UmbraEngine::displayError () {
	if (TCODConsole::root != NULL) {
		if (internalModules[UMBRA_INTERNAL_BSOD]->getActive())
			toDeactivate.push(internalModules[UMBRA_INTERNAL_BSOD]);
		toActivate.push(internalModules[UMBRA_INTERNAL_BSOD]);
	}
}

void UmbraEngine::printCredits (int x, int y, uint32 duration) {
	((UmbraModCredits *)internalModules[UMBRA_INTERNAL_CREDITS])->set(x,y,duration);
	activateModule(internalModules[UMBRA_INTERNAL_CREDITS]);
}
