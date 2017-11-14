#pragma once

#ifdef _DEBUG
#define DEBUG LogDebugMsg
#define LASTERR LogLastError
#else
	#define DEBUG
	#define LASTERR
#endif

enum DebugMessage {
	SCS = 0, //Success
	DBG = 1, //Debug
	WRN = 2, //Warning
	ERR = 3, //Error
	LER = 4 //Last Error (Windows)
};

void LogDebugMsg(DebugMessage type, char *msg, ...);
void LogLastError();
