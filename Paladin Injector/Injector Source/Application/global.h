#pragma once

/*

enum EDebugMessage
{
	SCS = 0, // Success
	DBG = 1, // Debug
	WRN = 2, // Warning
	ERR = 3, // Error
	LER = 4 // Last Windows Error
};

#ifdef _DEBUG

extern HANDLE hStandardIn[ 2 ], hStandardOut[ 2 ], hStandardError[ 2 ];

void SetDebug( );
void RestoreDebug( );

void LogDebugMessage( EDebugMessage dmType, wchar_t *szMessage, ... );
void LogLastError( );

#define SET_DEBUG SetDebug
#define RESTORE_DEBUG RestoreDebug
#define LOG_DEBUG LogDebugMessage
#define LOG_ERROR LogLastError
#else
#define SET_DEBUG void
#define RESTORE_DEBUG void
#define LOG_DEBUG void
#define LOG_ERROR void
#endif

*/

typedef long long moment;

#define EPOCH_TO_JANUARY_2017 moment( 1514764800000 )
#define PI 3.141593f
#define MILLISECONDS_PER_SECOND 1000.f

//void Wait( moment ); // TODO multimedia timer
moment GetMoment( );