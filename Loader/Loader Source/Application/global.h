#pragma once

typedef long long moment;

#ifdef _DEBUG

#define LOG_DEBUG LogDebugMsg
#define LOG_LAST_ERROR LogLastError

#else

void EmptyFunction( ... );
#define DEBUG EmptyFunction
#define LASTERR EmptyFunction

#endif

#define PI 3.141593f
#define MILLISECONDS_PER_SECOND 1000.f
#define OPEN_MESSAGE( Title, Text, Type ) MessageBoxA( nullptr, Text, Title, Type | MB_OK )

enum class EPremium
{
	BANNED = -2,
	EXPIRED,
	NOT_PREMIUM,
	PREMIUM
};

enum class EElevation
{
	UNTESTED = -1,
	NOT_ADMIN,
	ADMIN
};

enum class EAnticheatStatus
{
	NOT_FOUND = -1,
	FAILED,
	KILLED
};

enum EDebugMessage
{
	SCS = 0, // Success
	DBG = 1, // Debug
	WRN = 2, // Warning
	ERR = 3, // Error
	LER = 4 // Last Windows Error
};

void LogDebugMsg( EDebugMessage, char *, ... );
void LogLastError( );
void Wait( moment );
moment GetMoment( );
