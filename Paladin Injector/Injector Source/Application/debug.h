#pragma once

enum DebugMessage 
{
	BGN = 0,	//Beginning
	END = 1,	//Ending
	DBG = 2,	//Debug
	SCS = 3,	//Success
	WRN = 4,	//Warning
	ERR = 5,	//Error
	LER = 6		//Last Error (Windows)
};

enum ColorMode 
{
	MONO = 0,	//Everything is gray
	DUAL = 1,	//Only tag is colored
	FULL = 2	//Whole message is colored
};

class Debug 
{
public:
	~Debug();

private:
	bool initialized = false;
	bool allowSecondaryReporting = false;

	ColorMode color = DUAL;

	HANDLE hIn	= INVALID_HANDLE_VALUE;
	HANDLE hOut = INVALID_HANDLE_VALUE;
	//HANDLE hErr = INVALID_HANDLE_VALUE;

	FILE *chIn	= nullptr;
	FILE *chOut = nullptr;
	//FILE *chErr = nullptr;

	errno_t errIn	= NULL;
	errno_t errOut	= NULL;
	//errno_t errErr	= NULL;

public:
	//Initialization
	bool Init();
	bool IsInit() { return initialized; }

	//Color mode
	void SetColorMode(ColorMode mode) { color = mode; }

	//Logging
	void LogDebugMsg(DebugMessage type, wchar_t *msg, ...);
	void LogLastErrorA();
	void LogLastErrorB();
};

extern Debug *dbg;