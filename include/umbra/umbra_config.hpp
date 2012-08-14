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

#ifndef UMBRA_CONFIG_HPP
#define UMBRA_CONFIG_HPP

class UmbraFont;

enum UmbraLogLevel {
	UMBRA_LOGLEVEL_INFO,
	UMBRA_LOGLEVEL_NOTICE,
	UMBRA_LOGLEVEL_WARN,
	UMBRA_LOGLEVEL_ERROR,
	UMBRA_LOGLEVEL_FATAL,
	UMBRA_LOGLEVEL_NONE
};

class UmbraConfig {
	friend class UmbraEngine;
	friend class UmbraLog;
private:
	static int rootWidth;
	static int rootHeight;
	static bool fullScreen;
	static UmbraLogLevel logLevel;
	static UmbraFont * font;
	static const char * fileName;
	static const char * fontDir;
	static const char * moduleChain;
	static int fontID;
	static TCODList <UmbraFont *> fonts;
	/**
	 * Activates a different font. This method is called by the engine.
	 * @param shift a number indicating whether to activate the next or the previous font in the registered fonts list.<br>This can be -1 (switch down) or 1 (switch up). All other numbers will be clamped to these values.<br>A value of 0 results in doing nothing.
	 * @return <code>true</code> if the font has been successfully changed, <code>false</code> otherwise
	 */
	static bool activateFont (int shift = 0);
	/**
	 * Loads configuration variables from a config file.
	 * @param fileName the filename (with path to it) of the configuration file
	 */
	static void load (const char *fileName);
	/**
	 * Saves the configuration to a config file. It is called on application exit, so any changes to the configuration are stored.
	 */
	static void save ();
	/**
	 * Adds a font to the registered fonts list
	 * @param _font the font object to be added to the list
	 */
	static void registerFont (UmbraFont * _font);
};

#endif
