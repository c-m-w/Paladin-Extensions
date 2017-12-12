#pragma once

#ifdef _DEBUG
#define DEBUG LogDebugMsg
#define LASTERR LogLastError
#else
#define DEBUG
#define LASTERR
#endif

enum EDebugMessage
{
	SCS = 0,
	//Success
	DBG = 1,
	//Debug
	WRN = 2,
	//Warning
	ERR = 3,
	//Error
	LER = 4 //Last Error (Windows)
};

extern std::string strLog;

void LogDebugMsg( EDebugMessage, char *, ... );
void LogLastError( );
