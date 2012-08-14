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

#include "../include/umbra/umbra.hpp"
#include <stdio.h>

int UmbraConfig::rootWidth;
int UmbraConfig::rootHeight;
int UmbraConfig::fontID;
bool UmbraConfig::fullScreen;
UmbraLogLevel UmbraConfig::logLevel;
TCODList <UmbraFont *> UmbraConfig::fonts;
UmbraFont * UmbraConfig::font = NULL;
const char * UmbraConfig::fileName = NULL;
const char * UmbraConfig::fontDir = NULL;
const char * UmbraConfig::moduleChain = NULL;

const char * logLevelName[] = {
	"info",
	"notice",
	"warning",
	"error",
	"fatal error",
	"none"
};

void UmbraConfig::load (const char *fileName) {
	static bool loaded = false;
	std::string l;
	TCODParser parser;
	UmbraLog::openBlock("UmbraConfig::load | Loading configuration variables.");
	if (loaded && strcmp(UmbraConfig::fileName, fileName) == 0) {
		UmbraLog::notice("UmbraConfig::load | Configuraion variables have been loaded previously. Aborting.");
		UmbraLog::closeBlock(UMBRA_LOGRESULT_FAILURE);
		return;
	}

	UmbraConfig::fileName = strdup(fileName);
	//register configuration variables
	TCODParserStruct * config = parser.newStructure("config");
		config->addProperty("rootWidth",TCOD_TYPE_INT,true);
		config->addProperty("rootHeight",TCOD_TYPE_INT,true);
		config->addProperty("fontID",TCOD_TYPE_INT,true);
		config->addProperty("fullScreen",TCOD_TYPE_BOOL,true);
		config->addProperty("logLevel",TCOD_TYPE_STRING,true);
		//optional custom font directory
		config->addProperty("fontDir",TCOD_TYPE_STRING,false);
		//optional module chaining
		config->addProperty("moduleChain",TCOD_TYPE_STRING,false);

	//check if the config file exists
	if (!TCODSystem::fileExists(fileName)) {
		UmbraLog::notice("Configuration file %s is bad or missing. Attempting to create a new one.", fileName);
		//assign defaults
		rootWidth = 80;
		rootHeight = 60;
		fontID = 0;
		fullScreen = false;
		logLevel = UMBRA_LOGLEVEL_ERROR;
		fontDir = "data/img";
		UmbraConfig::save();
	}

	//run the parser
	parser.run(fileName,NULL);

	//assign parsed values to class variables
	rootWidth = parser.getIntProperty("config.rootWidth");
	rootHeight = parser.getIntProperty("config.rootHeight");
	fontID = parser.getIntProperty("config.fontID");
	fullScreen = parser.getBoolProperty("config.fullScreen");
	l = parser.getStringProperty("config.logLevel");
	fontDir = parser.getStringProperty("config.fontDir");
	moduleChain = parser.getStringProperty("config.moduleChain");
	if (fontDir != NULL) fontDir = strdup(fontDir);
	else fontDir = "data/img"; // default value
	if (moduleChain != NULL) moduleChain = strdup(moduleChain);
	//set log level
	for (int i = 0; i <= (int)UMBRA_LOGLEVEL_NONE; i++) {
		if (l == logLevelName[i]) logLevel = (UmbraLogLevel)i;
	}
	loaded = true;
	UmbraLog::closeBlock(UMBRA_LOGRESULT_SUCCESS);
}

void UmbraConfig::save () {
	FILE * out;
	std::string modC = "";

	UmbraLog::info("UmbraConfig::save | Saving configuration variables.");

	out = fopen(fileName,"w");

	if (moduleChain != NULL) {
		modC += "  moduleChain = \"";
		modC += moduleChain;
		modC += "\"\n";
	}

	fprintf(out,"/*\n"
	            " * UMBRA CONFIGURATION FILE\n"
	            " *\n"
	            " * rootWidth (integer): width of the root console in cells\n"
	            " * rootHeight (integer): height of the root console in cells\n"
	            " * fontID (integer): the ID of the font that is to be used\n"
	            " * fullScreen (boolean): whether the application should run in full screen.\n"
	            " *                       * true = run in full screen mode\n"
	            " *                       * false = run in windowed mode (default)\n"
	            " * logLevel (string): which messages are supposed to be logged.\n"
	            " *                    * \"info\" = all messages down to the info level\n"
	            " *                                 (full debug mode)\n"
	            " *                    * \"notice\" = all debug messages down to notices\n"
	            " *                    * \"warning\" = all debug messages down to warnings\n"
	            " *                    * \"error\" = log only errors and fatal errors\n"
	            " *                                  (standard debug mode, default)\n"
	            " *                    * \"fatal error\" = log only fatal errors\n"
	            " *                    * \"none\" = don't create a logfile at all\n"
	            " *                                 (debug mode off)\n"
	            " * fontDir (string): the directory containing font files\n"
	            " * moduleChain (string): the module chain to load (optional)\n"
	            " */\n"
	            "\n"
	            "config {\n"
	            "  rootWidth = %d\n"
	            "  rootHeight = %d\n"
	            "  fontID = %d\n"
	            "  fullScreen = %s\n"
	            "  logLevel = \"%s\"\n"
	            "  fontDir = \"%s\"\n"
	            "%s"
	            "}\n",
	            rootWidth,
	            rootHeight,
	            fontID,
	            (TCODConsole::isFullscreen()?"true":"false"),
	            logLevelName[logLevel],
	            fontDir,
	            modC.c_str());

	fclose(out);
}

void UmbraConfig::registerFont (UmbraFont * _font) {
	UmbraLog::info("UmbraConfig::registerFont | Registered a font.");
	fonts.push(_font);
}

bool UmbraConfig::activateFont (int shift) {
	int s = CLAMP(-1,1,shift);
	//check if there are any registered fonts
	if (fonts.size() == 0) return false; // can happen if a user uses the default terminal.png without registering any font
	//check if the requested ID isn't out of range
	if (fontID+s < 0 || fontID+s >= fonts.size()) return false;
	//check if the font needs changing at all
	if (font != NULL && s == 0) return false;
	//register the font
	font = fonts.get(fontID+s);
	fontID += s;
	return true;
}
