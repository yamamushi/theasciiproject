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

class UmbraModSpeed: public UmbraWidget {
	friend class UmbraEngine;
	public:
		UmbraModSpeed ();
		/**
		 * Gathers data about time useage.
		 * @return <code>true</code> if Speedo is to continue active, <code>false</code> it it should be deactivated
		 */
		bool update ();
		/**
		 * Displays the Speedo widget.
		 */
		void render ();
		/**
		 * Parses mouse input.
		 */
		void mouse (TCOD_mouse_t &ms);
		/**
		 * Sets the minimised state of the widget.
		 * @param val <code>true</code> for minimised, <code>false</code> for maximised		 
		 */     		
		inline void setMinimised(bool val) { isMinimised=val; }       
	private:
		float cumulatedElapsed;
		float updateTime;
		float renderTime;
		int updatePer, renderPer, sysPer;
		TCODImage * timeBar;
		TCODConsole * speed;
		int fps;
		bool isMinimised;

		/**
		 * Removes the frames per second limit in order to attempt to enforce a 100% load on the CPU.
         */
		void activate ();
		/**
		 * Restores the frames per second limit from before Speedo activation.
         */
		void deactivate ();
		/**
		 * Uptades the update and render times.
		 * @param updateTime the time spend on <code>update()</code> methods
		 * @param renderTime the time spend on <code>render()</code> methods
		 */
		void setTimes(long updateTime, long renderTime); // this is called by engine each frame
};

