#pragma once

/*
 *	If in debug mode, we define debug/lasterr to point to the debug output functions
 *	If not in debug, they point to nothing which means the functions won't be called
 */
#ifdef _DEBUG
#define DEBUG LogDebugMsg
#define LASTERR LogLastError
#else
#define DEBUG
#define LASTERR
#endif

enum DBG_MSG
{
	SCS = 0,
	DBG = 1,
	WRN = 2,
	ERR = 3,
	LER = 4
};

void LogDebugMsg(DBG_MSG type, unsigned int layer, char *msg, ...);
void LogLastError(unsigned int layer);