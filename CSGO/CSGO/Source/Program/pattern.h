#pragma once

class CPatternScanner
{
	MODULEENTRY32 GetModule( char * );
	uintptr_t FindPattern( char *, unsigned int, char *, char * );

public:
	uintptr_t FindPatternEx( HANDLE, char *, char *, char * );
};

extern CPatternScanner scan;
