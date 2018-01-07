#pragma once

class CPatternScanner 
{
	MODULEENTRY32 GetModule(char *module);
	uintptr_t FindPattern(char* base, unsigned long size, char* pattern, char *mask);

public:
	uintptr_t FindPatternEx(HANDLE hProcess, char *module, char *pattern, char *mask);
};

extern CPatternScanner scan;