/*
* Umbra
* Copyright (c) 2009 Mingos
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The name of Mingos may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY MINGOS ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL MINGOS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../include/umbra/umbra.hpp"
#include <stdarg.h>
#include <stdio.h>

FILE * UmbraLog::out = NULL;
int UmbraLog::indent = 0;
TCODList <UmbraLog::UmbraLogMessage*> UmbraLog::messages;

const char * logTypeString[] = {
	"INF.",
	"NOT.",
	"WAR.",
	"ERR.",
	"FAT."
};

const char * logTypeStringFull[] = {
	"INFO",
	"NOTICE",
	"WARNING",
	"ERROR",
	"FATAL ERROR"
};

const char * logTypeStringLong[] = {
	"INFO",
	"NOTIFICATION",
	"WARNING",
	"ERROR",
	"FATAL ERROR"
};

const char * resultString[] = {
	"[END BLOCK: FAILURE]",
	"[END BLOCK: SUCCESS]",
	"[END BLOCK]"
};

void UmbraLog::initialise () {
	out = fopen("log.txt","w");
	fprintf(out,UMBRA_TITLE" ver. "UMBRA_VERSION" ("UMBRA_STATUS") Log file, Running time on creation: %dms.\n"
	            "---===---\n"
	            "INF. = INFORMATION. Informative message.\n"
	            "NOT. = NOTICE. Something unexpected that does not affect the program execution.\n"
	            "WAR. = WARNING. An error that may potentially provoke some misbehaviour.\n"
	            "ERR. = ERROR. An error that is guaranteed to provoke some misbehaviour.\n"
	            "FAT. = FATAL ERROR. An error that prevents the program from continuing.\n"
	            "---===---",
	            TCODSystem::getElapsedMilli());
	fflush(out);
}

void UmbraLog::save () {
	indent = 0;
	UmbraLog::info("Log file saved.");
	if (out != NULL) fclose(out);
}

int UmbraLog::output (UmbraLogType type, UmbraLogResult res, int ind, const char * str) {
	if (UmbraConfig::logLevel > (UmbraLogLevel)type) return 0;
	if (out == NULL) {
		initialise();
		if (res >= UMBRA_LOGRESULT_FAILURE && indent == 0) {
			return error("UmbraLog::closeBlock | Tried to close a block, but it hasn't been opened in the first place.");
		}
	}
	//create the message
	UmbraLogMessage * msg = new UmbraLogMessage();
	msg->msg = str;
	msg->indent = indent;
	msg->logType = type;
	msg->result = res;
	msg->time = TCODSystem::getElapsedMilli();
	//create the arrows marking the indent level
	std::string arrows;
	for (int i = 0; i < indent; i++)
		if (i < indent - 1) arrows += "|   ";
		else {
			if (res >= UMBRA_LOGRESULT_FAILURE) arrows += "\\---";
			else arrows += "|   ";
		}
	//if result is a negative number, then it's not a block close
	if (res < UMBRA_LOGRESULT_FAILURE)
		fprintf(out,"\n%s %06d %s%s", logTypeString[msg->logType], msg->time, arrows.c_str(), msg->msg.c_str());
	//else we're closing a block (no message, just block close notification)
	else
		fprintf(out,"\n%s %06d %s%s", logTypeString[msg->logType], msg->time, arrows.c_str(), resultString[msg->result]);
	fflush(out);
	indent += ind;
	messages.push(msg);
	return messages.size();
}

int UmbraLog::output (UmbraLogType type, UmbraLogResult res, int ind, std::string str) {
	return output(type,res,ind,str.c_str());
}

int UmbraLog::openBlock (const char* str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	return output(UMBRA_LOGTYPE_INFO,(UmbraLogResult)(-1),1,s);
}

int UmbraLog::openBlock (std::string str) {
	return output(UMBRA_LOGTYPE_INFO,(UmbraLogResult)(-1),1,str);
}

int UmbraLog::info (const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	return output(UMBRA_LOGTYPE_INFO,(UmbraLogResult)(-1),0,s);
}

int UmbraLog::info (std::string str) {
	return output(UMBRA_LOGTYPE_INFO,(UmbraLogResult)(-1),0,str);
}

int UmbraLog::notice (const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	return output(UMBRA_LOGTYPE_NOTICE,(UmbraLogResult)(-1),0,s);
}

int UmbraLog::notice (std::string str) {
	return output(UMBRA_LOGTYPE_NOTICE,(UmbraLogResult)(-1),0,str);
}

int UmbraLog::warning (const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	return output(UMBRA_LOGTYPE_WARNING,(UmbraLogResult)(-1),0,s);
}

int UmbraLog::warning (std::string str) {
	return output(UMBRA_LOGTYPE_WARNING,(UmbraLogResult)(-1),0,str);
}

int UmbraLog::error (const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	return output(UMBRA_LOGTYPE_ERROR,(UmbraLogResult)(-1),0,s);
}

int UmbraLog::error (std::string str) {
	return output(UMBRA_LOGTYPE_ERROR,(UmbraLogResult)(-1),0,str);
}

int UmbraLog::fatalError (const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	return output(UMBRA_LOGTYPE_FATAL,(UmbraLogResult)(-1),0,s);
}

int UmbraLog::fatalError (std::string str) {
	return output(UMBRA_LOGTYPE_FATAL,(UmbraLogResult)(-1),0,str);
}

int UmbraLog::closeBlock (UmbraLogResult result) {
	return output(UMBRA_LOGTYPE_INFO,result,-1,"");
}

int UmbraLog::size(UmbraLogType type) {
	int count = 0;
	if (type < UMBRA_LOGTYPE_INFO || type > UMBRA_LOGTYPE_FATAL) {
		error("UmbraLog::size | Specified an invalid log message type.");
		return 0;
	}
	for (UmbraLogMessage ** msg = messages.begin(); msg != messages.end(); msg++)
		if ((*msg)->logType == type) ++count;
	return count;
}

const char * UmbraLog::get (int idx) {
	UmbraLogMessage * msg;
	std::string ret = "";
	if (idx == -1) {
		if (messages.size() > 0) msg = messages.peek();
		else return "No messages logged.";
	}
	else if (idx < -1 || idx >= messages.size()) {
		error ("UmbraLog::get | Tried to retrieve a message with index %d, but such an index does not exist.",idx);
		msg = messages.peek();
	}
	else msg = messages.get(idx);
	ret = logTypeStringFull[msg->logType];
	ret += ": ";
	ret += msg->msg;
	return ret.c_str();
}
