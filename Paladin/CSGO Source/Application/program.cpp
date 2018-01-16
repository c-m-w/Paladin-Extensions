#include "../main.h"

void CProgram::GetPremiumUsers( )
{
	uPremiumUsers[ 0 ].lpstrUsername = "bhopfu1";
	uPremiumUsers[ 0 ].iHardwareID = 12 * 4095;
	uPremiumUsers[ 0 ].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[ 0 ].bValid = true;
	uPremiumUsers[ 0 ].bBanned = false;
	uPremiumUsers[ 1 ].lpstrUsername = "MiKe";
	uPremiumUsers[ 1 ].iHardwareID = 8 * 255;
	uPremiumUsers[ 1 ].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[ 1 ].bValid = true;
	uPremiumUsers[ 1 ].bBanned = false;
	uPremiumUsers[ 2 ].lpstrUsername = "Skel";
	uPremiumUsers[ 2 ].iHardwareID = 8 * 255;
	uPremiumUsers[ 2 ].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[ 2 ].bValid = true;
	uPremiumUsers[ 2 ].bBanned = false;
	uPremiumUsers[ 3 ].lpstrUsername = "Cole";
	uPremiumUsers[ 3 ].iHardwareID = 4 * 15;
	uPremiumUsers[ 3 ].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[ 3 ].bValid = true;
	uPremiumUsers[ 3 ].bBanned = false;
	uPremiumUsers[ 4 ].lpstrUsername = "Bean"; // TODO BEAN
	uPremiumUsers[ 4 ].iHardwareID = 0;
	uPremiumUsers[ 4 ].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[ 4 ].bValid = true;
	uPremiumUsers[ 4 ].bBanned = false;
}

bool CProgram::CompareName( user_t uPremiumUser, user_t uCurrentUser )
{
	for ( unsigned short usUserID { }; usUserID < 256; usUserID++ )
	{
		if ( uPremiumUser.lpstrUsername[ usUserID ] && !uCurrentUser.lpstrUsername[ usUserID ] )
		{
			return false;
		}
		if ( !uPremiumUser.lpstrUsername[ usUserID ] && uCurrentUser.lpstrUsername[ usUserID ] )
		{
			return false;
		}
		if ( !uPremiumUser.lpstrUsername[ usUserID ] && !uCurrentUser.lpstrUsername[ usUserID ] )
		{
			break;
		}
		if ( uPremiumUser.lpstrUsername[ usUserID ] != uCurrentUser.lpstrUsername[ usUserID ] )
		{
			return false;
		}
	}
	return true;
}

EPremium CProgram::CheckPremiumStatus( )
{
	if ( DECEMBER_FIRST > GetMoment( ) )
	{
		LOG_DEBUG( ERR, "Date Mismatch: %lld > %lld", DECEMBER_FIRST, GetMoment( ) );
		return EPremium::NOT_PREMIUM;
	}
	GetPremiumUsers( );
	user_t uCurrentUser { };
	char chBuffer[ 257 ];
	DWORD dwBufferSize = 257;
	GetUserNameA( chBuffer, &dwBufferSize );
	uCurrentUser.lpstrUsername = chBuffer;
	LOG_DEBUG( DBG, "Current User Username: %s", uCurrentUser.lpstrUsername );
	unsigned short usUserID { };
	for ( ; usUserID <= PREMIUM_USERS; usUserID++ )
	{
		if ( uPremiumUsers[ usUserID ].bValid )
		{
			if ( uPremiumUsers[ usUserID ].lpstrUsername && CompareName( uPremiumUsers[ usUserID ], uCurrentUser ) )
			{
				break;
			}
		}
		else
		{
			LOG_DEBUG( ERR, "Username did not match any users in database" );
			return EPremium::NOT_PREMIUM;
		}
	}
	LOG_DEBUG( DBG, "Current User Database ID: %i", usUserID );
	SYSTEM_INFO siCurrentUser;
	GetSystemInfo( &siCurrentUser );
	uCurrentUser.iHardwareID = siCurrentUser.dwActiveProcessorMask * siCurrentUser.dwNumberOfProcessors;
	LOG_DEBUG( DBG, "Current User HWID: %i", uCurrentUser.iHardwareID );
	if ( uCurrentUser.iHardwareID != uPremiumUsers[ usUserID ].iHardwareID )
	{
		LOG_DEBUG( ERR, "HWID did not match any users in database" );
		return EPremium::NOT_PREMIUM;
	}
	uCurrentUser.tExpiration = uPremiumUsers[ usUserID ].tExpiration;
	LOG_DEBUG( DBG, "Current User Premium Time: %lld", uCurrentUser.tExpiration );
	if ( uCurrentUser.tExpiration < GetMoment( ) )
	{
		LOG_DEBUG( ERR, "%lld < %lld", uCurrentUser.tExpiration, GetMoment( ) );
		LOG_DEBUG( ERR, "User is out of premium" );
		return EPremium::EXPIRED;
	}
	uCurrentUser.bBanned = uPremiumUsers[ usUserID ].bBanned;
	if ( uCurrentUser.bBanned )
	{
		LOG_DEBUG( SCS, "User is banned" );
		return EPremium::BANNED;
	}
	LOG_DEBUG( SCS, "User is premium!" );
	return EPremium::PREMIUM;
}

EElevation CProgram::GetElevationState( HANDLE hTarget )
{
	HANDLE hTokenTarget;
	TOKEN_ELEVATION teTarget;
	DWORD dwReturnLength = sizeof( TOKEN_ELEVATION );
	if ( OpenProcessToken( hTarget, TOKEN_QUERY, &hTokenTarget ) && GetTokenInformation( hTokenTarget, TokenElevation, &teTarget, dwReturnLength, &dwReturnLength ) )
	{
		CloseHandle( hTokenTarget );
		return EElevation( teTarget.TokenIsElevated );
	}
	CloseHandle( hTokenTarget );
	return EElevation::NOT_ADMIN;
}

EAnticheatStatus CProgram::KillAnticheat( LPCSTR cstrAnticheatName, char chAnticheatExe )
{
	if ( FindWindow( nullptr, cstrAnticheatName ) )
	{
		if ( GetElevationState( GetCurrentProcess( ) ) == EElevation::ADMIN )
		{
			system( &"taskkill /F /T /IM "[ chAnticheatExe ] );
			LOG_DEBUG( WRN, "Found anticheat %s open and terminated it", cstrAnticheatName );
			return EAnticheatStatus::KILLED;
		}
		LOG_DEBUG( WRN, "Found anticheat %s open", cstrAnticheatName );
		return EAnticheatStatus::FAILED;
	}
	LOG_DEBUG( WRN, "Did not find anticheat %s open", cstrAnticheatName );
	return EAnticheatStatus::NOT_FOUND;
}

float CProgram::GetWindowsSensitivity( )
{
	unsigned short usWindowsSensitivity;
	if ( SystemParametersInfo( SPI_GETMOUSESPEED, 0, &usWindowsSensitivity, false ) )
	{
		return float( usWindowsSensitivity ) / 20.f;
	}
	return 1.f;
}

CProgram pro;
