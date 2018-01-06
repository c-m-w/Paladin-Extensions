#pragma once

class CPatternScanner 
{
private:
	MODULEENTRY32 getModule(char *module);
	uintptr_t findPattern(char* base, unsigned int size, char* pattern, char *mask);

public:
	uintptr_t findPatternEx(HANDLE hProcess, char *module, char *pattern, char *mask);
};

extern CPatternScanner scan;