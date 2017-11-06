#pragma once
#include "../global.h"
#ifdef _DEBUG
#define DEBUG LogDebugMsg
#define LASTERR LogLastError
#else
#define DEBUG
#define LASTERR
#endif
enum DebugMessage {
	SCS = 0,
	DBG = 1,
	WRN = 2,
	ERR = 3,
	LER = 4
};

void LogDebugMsg(DebugMessage dmType, unsigned short iLayer, char * cMessage, ...);
void LogLastError(unsigned int layer);
