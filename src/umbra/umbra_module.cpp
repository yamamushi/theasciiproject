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

UmbraModule::UmbraModule () {
	id = -1;
	priority = 1;
	status = UMBRA_UNINITIALISED;
	fallback = -1;
	timeout = 0;
	timeoutEnd = 0xffffffff;
}
UmbraModule::UmbraModule (const char *name) {
	id = -1;
	priority = 1;
	status = UMBRA_UNINITIALISED;
	fallback = -1;
	timeout = 0;
	timeoutEnd = 0xffffffff;
	setName(name);
}

void UmbraModule::setActive (bool active) {
	if (status == UMBRA_UNINITIALISED) {
		onInitialise();
		status=UMBRA_INACTIVE;
	}
	if (active && status == UMBRA_INACTIVE) {
		status = UMBRA_ACTIVE;
		onActivate();
	} else if (!active && status >= UMBRA_ACTIVE) {
		status = UMBRA_INACTIVE;
		onDeactivate();
	}
}

void UmbraModule::setPause (bool paused) {
	if (status == UMBRA_UNINITIALISED) {
		onInitialise();
		status=UMBRA_INACTIVE;
	}
	if (paused && status != UMBRA_PAUSED) {
		status=UMBRA_PAUSED;
		onPause();
	} else if (!paused && status == UMBRA_PAUSED) {
		status=UMBRA_ACTIVE;
		onResume();
	}
}

void UmbraModule::initialiseTimeout() {
	if (timeout == 0) return;
	else timeoutEnd = TCODSystem::getElapsedMilli() + timeout;
}

void UmbraModule::setFallback(const char *name) {
	UmbraModule *mod=getEngine()->getModule(name);
	if (mod) {
		setFallback(mod->getID());
	} else {
		UmbraLog::error("UmbraModule::setFallback | Unknown module \"%s\".", name);
	}
}

void UmbraModule::setParametre(const char *name,TCOD_value_t value) {
	if (name == NULL) return;
	for (UmbraModuleParametre *it=params.begin(); it != params.end(); it++) {
		if (strcmp(it->name,name) == 0) {
			// already exists. update value
			// this happens when value is overriden in module.cfg
			it->value=value;
			return;
		}
	}
	// new parametre
	UmbraModuleParametre mod;
	mod.name=strdup(name);
	mod.value=value;
	params.push(mod);
}

UmbraModule::UmbraModuleParametre &UmbraModule::getParametre(const char *name) {
	static UmbraModuleParametre def = {NULL,{0}};
	for (UmbraModuleParametre *it=params.begin(); it != params.end(); it++) {
		if (strcmp(it->name,name) == 0) return *it;
	}
	return def;
}
