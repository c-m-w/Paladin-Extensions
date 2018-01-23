#pragma once

typedef long long moment;

#ifdef _DEBUG
#define LOG_DEBUG LogDebugMessage
#define LOG_LAST_ERROR LogLastError
#else
#define DEBUG void
#define LASTERR void
#endif

#define EPOCH_TO_JANUARY_2017 moment( 1514764800000 )
#define PI 3.141593f
#define MILLISECONDS_PER_SECOND 1000.f
#define OPEN_MESSAGE( Title, Text, Type ) MessageBoxA( nullptr, Text, Title, Type | MB_OK )

enum class EPremium
{
	BANNED = -1,
	NOT_PREMIUM,
	CONNECTION_FAILURE,
	HARDWARE_MISMATCH,
	EXPIRED,
	PREMIUM,
	DEVELOPER
};

enum class EElevation
{
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

void LogDebugMessage( EDebugMessage, char *, ... );
void LogLastError( );
void Wait( moment );
moment GetMoment( );
