#pragma once

#ifdef _DEBUG
#define LOG_DEBUG dbg.osDebugStream
#define LOG_LAST_ERROR dbg.LogLastWindowsErrorDebugMessage
#else
#define LOG_DEBUG void
#define LOG_LAST_ERROR void
#endif

#define DBG L" DBG "
#define SCS L" SCS "
#define WRN L" WRN "
#define ERR L" ERR "
#define LER L" LER "

class CDebugging
{
	std::ofstream ofLogFile;
	HANDLE hConsole;
public:
	std::ostream osDebugStream;
	CDebugging( );
};

extern CDebugging dbg;

CDebugging operator<<( const CDebugging & dbg, const wchar_t( & str)[6] )
{
	
}

inline void test( )
{
	dbg << DBG << "uh oh!";
}
