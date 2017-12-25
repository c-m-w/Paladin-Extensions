#pragma once

typedef long long moment;

#ifdef _DEBUG
#define DEBUG LogDebugMsg
#define LASTERR LogLastError
#else
#define DEBUG
#define LASTERR
#endif
#define PI 3.141593f
#define MILLISECONDS_PER_SECOND 1000.f

#define PREMIUM_USERS unsigned __int8(55)
#define MESSAGE( Title, Text, Type ) MessageBox( nullptr, Text, Title, (Type) | MB_OK )
#define DECEMBER_FIRST moment( 1512086400000 ) // time since epoch in milliseconds to december first 2017
#define DAY moment( 8640000 ) // day in milliseconds

enum class EQuitReasons
{
	UNKNOWN = -1,
	LOAD_LIBRARY_ERROR,
	SUCCESS,
	BLACKLISTED_CALL,
	PANIC
};

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
	LER = 4 //Last Error (Windows)
};

extern std::string strLog;

void LogDebugMsg( EDebugMessage, char *, ... );
void LogLastError( );

struct angle_t
{
	float flPitch, flYaw, flRoll; // rotation of x/pitch axis, rotation of y/yaw axis, rotation of z/roll axis; visibly y, x, z

	bool operator==( angle_t );
	bool operator!=( angle_t );
	angle_t operator+( angle_t );
	angle_t operator-( angle_t );
	angle_t operator*( float );
	angle_t operator/( float );
	angle_t operator+=( angle_t );
	angle_t operator-=( angle_t );
	angle_t operator*=( float );
	angle_t operator/=( float );
};

struct color_t
{
	BYTE bRed, bGreen, bBlue, bAlpha;
};

struct coordinate_t
{
	float flX, flY, flZ;
};

struct vector_t
{
	float flDeltaX, flDeltaY, flDeltaZ;

	vector_t( );
	vector_t( coordinate_t, coordinate_t );
};

void Wait( unsigned long );
moment GetMoment( );

template< typename xDatatype, typename xDatatype2 > void Limit( xDatatype &xStatus, xDatatype2 xMinimum, xDatatype2 xMaximum )
{
	if ( xDatatype( xMinimum ) > xStatus )
	{
		xStatus = xDatatype( xMinimum );
	}
	else if ( xStatus > xDatatype( xMaximum ) )
	{
		xStatus = xDatatype( xMaximum );
	}
}

template< typename xDatatype > void Absolute( xDatatype &xStatus )
{
	if ( xStatus < 0 )
	{
		xStatus = -xStatus;
	}
}
