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

class UmbraCallback {
	friend class UmbraEngine;
	public:
		UmbraCallback () {}
		virtual ~UmbraCallback () {}
	protected:
		UmbraKey key;
		/**
		 * Checks whether the collected keyboard event corresponds to the one the callback is listening to.
		 * @param k the keyboard event collected by the engine
		 * @return <code>true</code> if the keyboard events match, <code>false</code> otherwise
		 */
		virtual inline bool evaluate (UmbraKey k) { if (k == key) return true; else return false; }
		/**
		 * A pure virtual method (ie. it is mandatory to override it) containing custom code executed whenever the callback encounters a key event it is listening to.
		 */
		virtual void action () = 0;
		/**
		 * Fetches a pointer to the engine.
		 * @return a pointer to the engine
		 */
		inline UmbraEngine * getEngine () { return UmbraEngine::getInstance(); }
};

//Internal callbacks:

//quit game
class UmbraCallbackQuit: public UmbraCallback {
	public:
		UmbraCallbackQuit ();
	private:
		UmbraKey key2;
		/**
		 * Checks whether the collected keyboard event corresponds to one of the Quit key combinations.
		 * @param k the keyboard event collected by the engine
		 * @return <code>true</code> if the keyboard events match, <code>false</code> otherwise
		 */
		inline bool evaluate (UmbraKey k) { if (k == key || k == key2) return true; else return false; }
		/**
		 * Quits the application.
		 */
		void action ();
};

//switch fullscreen
class UmbraCallbackFullscreen: public UmbraCallback {
	public:
		UmbraCallbackFullscreen ();
	private:
		/**
		 * Toggles fullscreen mode on/off.
		 */
		void action ();
};

//save screenshot
class UmbraCallbackScreenshot: public UmbraCallback {
	public:
		UmbraCallbackScreenshot ();
	private:
		/**
		 * Saves a screenshot.
		 */
		void action ();
};

//font up
class UmbraCallbackFontUp: public UmbraCallback {
	public:
		UmbraCallbackFontUp ();
	private:
		/**
		 * Switches the font to the next one in the registered fonts list.
		 */
		void action ();
};

//switch font down
class UmbraCallbackFontDown: public UmbraCallback {
	public:
		UmbraCallbackFontDown ();
	private:
		/**
		 * Switches the font to the previous one in the registered fonts list.
		 */
		void action ();
};

//pause the program
class UmbraCallbackPause: public UmbraCallback {
	public:
		UmbraCallbackPause ();
	private:
	    /**
	     * Toggles the engine's paused state.
	     */
		void action ();
};

//pause the program
class UmbraCallbackSpeedometer: public UmbraCallback {
	public:
		UmbraCallbackSpeedometer ();
	private:
	    /**
	     * Turns the Speedometer on and off.
	     */
		void action ();
};
