#include "../dllmain.h"

void CGeneral::GetPremiumUsers( )
{
	uPremiumUsers[0].lpstrUsername = "bhopfu1";
	uPremiumUsers[0].iHardwareID = 12 * 4095;
	uPremiumUsers[0].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[0].bValid = true;
	uPremiumUsers[0].bBanned = false;
	uPremiumUsers[1].lpstrUsername = ""; // TODO MIKE
	uPremiumUsers[1].iHardwareID = 0;
	uPremiumUsers[1].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[1].bValid = true;
	uPremiumUsers[1].bBanned = false;
	uPremiumUsers[2].lpstrUsername = ""; // TODO SKEL
	uPremiumUsers[2].iHardwareID = 0;
	uPremiumUsers[2].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[2].bValid = true;
	uPremiumUsers[2].bBanned = false;
	uPremiumUsers[3].lpstrUsername = "Cole";
	uPremiumUsers[3].iHardwareID = 4 * 15;
	uPremiumUsers[3].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[3].bValid = true;
	uPremiumUsers[3].bBanned = false;
	uPremiumUsers[4].lpstrUsername = "Bean"; // TODO BEAN
	uPremiumUsers[4].iHardwareID = 0;
	uPremiumUsers[4].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[4].bValid = true;
	uPremiumUsers[4].bBanned = false;
}

bool CGeneral::CompareName( user_t uPremiumUser, user_t uCurrentUser )
{
	for ( int i = 0; i < 256; i++ )
	{
		if ( uPremiumUser.lpstrUsername[i] && !uCurrentUser.lpstrUsername[i] )
		{
			return false;
		}
		if ( !uPremiumUser.lpstrUsername[i] && uCurrentUser.lpstrUsername[i] )
		{
			return false;
		}
		if ( !uPremiumUser.lpstrUsername[i] && !uCurrentUser.lpstrUsername[i] )
		{
			break;
		}
		if ( uPremiumUser.lpstrUsername[i] != uCurrentUser.lpstrUsername[i] )
		{
			return false;
		}
	}
	return true;
}

EPremium CGeneral::CheckPremiumStatus( )
{
	if ( DECEMBER_FIRST > GetTime( ) )
	{
		LogDebugMsg( ERR, "Date Mismatch: %i > %i", DECEMBER_FIRST, GetTime( ) );
		return EPremium::NOT_PREMIUM;
	}
	GetPremiumUsers( );
	user_t uCurrentUser;
	char chBuffer[257];
	DWORD dwBufferSize = 257;
	GetUserNameA( chBuffer, &dwBufferSize );
	uCurrentUser.lpstrUsername = chBuffer;
	LogDebugMsg( DBG, "Current User Username: %s", uCurrentUser.lpstrUsername );
	int i;
	for ( i = 0; i <= PREMIUM_USERS; i++ )
	{
		if ( uPremiumUsers[i].bValid )
		{
			if ( uPremiumUsers[i].lpstrUsername && CompareName( uPremiumUsers[i], uCurrentUser ) )
			{
				break;
			}
		}
		else
		{
			LogDebugMsg( ERR, "Username did not match any users in database" );
			return EPremium::NOT_PREMIUM;
		}
	}
	LogDebugMsg( DBG, "Current User Database ID: %i", i );
	SYSTEM_INFO siCurrentUser;
	GetSystemInfo( &siCurrentUser );
	uCurrentUser.iHardwareID = siCurrentUser.dwActiveProcessorMask * siCurrentUser.dwNumberOfProcessors;
	LogDebugMsg( DBG, "Current User HWID: %i", uCurrentUser.iHardwareID );
	if ( uCurrentUser.iHardwareID != uPremiumUsers[i].iHardwareID )
	{
		LogDebugMsg( ERR, "HWID did not match any users in database" );
		return EPremium::NOT_PREMIUM;
	}
	uCurrentUser.tExpiration = uPremiumUsers[i].tExpiration;
	LogDebugMsg( DBG, "Current User Premium Time: %i", uCurrentUser.tExpiration );
	if ( uCurrentUser.tExpiration < GetTime( ) )
	{
		LogDebugMsg( ERR, "%i < %i", uCurrentUser.tExpiration, GetTime( ) );
		LogDebugMsg( ERR, "User is out of premium" );
		return EPremium::EXPIRED;
	}
	uCurrentUser.bBanned = uPremiumUsers[i].bBanned;
	if ( uCurrentUser.bBanned )
	{
		LogDebugMsg( SCS, "User is banned" );
		return EPremium::BANNED;
	}
	LogDebugMsg( SCS, "User is premium!" );
	return EPremium::PREMIUM;
}

EElevation CGeneral::GetElevationState( )
{
	HANDLE hTokenSelf;
	TOKEN_ELEVATION teSelf;
	DWORD dwReturnLength = sizeof(TOKEN_ELEVATION);
	if ( OpenProcessToken( GetCurrentProcess( ), TOKEN_QUERY, &hTokenSelf ) &&
		GetTokenInformation( hTokenSelf, TokenElevation, &teSelf, dwReturnLength, &dwReturnLength ) )
	{
		eElevationState = EElevation( teSelf.TokenIsElevated );
	}
	else
	{
		eElevationState = EElevation::NOT_ADMIN;
	}
	CloseHandle( hTokenSelf );
	return eElevationState;
}

EElevation CGeneral::GetElevationState( HANDLE hTarget )
{
	HANDLE hTokenTarget;
	TOKEN_ELEVATION teTarget;
	DWORD dwReturnLength = sizeof(TOKEN_ELEVATION);
	if ( OpenProcessToken( hTarget, TOKEN_QUERY, &hTokenTarget ) &&
		GetTokenInformation( hTokenTarget, TokenElevation, &teTarget, dwReturnLength, &dwReturnLength ) )
	{
		CloseHandle( hTokenTarget );
		return EElevation( teTarget.TokenIsElevated );
	}
	CloseHandle( hTokenTarget );
	return EElevation::NOT_ADMIN;
}

EAnticheatStatus CGeneral::KillAnticheat( LPCSTR cstrAnticheatName, char chAnticheatExe )
{
	if ( eElevationState == EElevation::UNTESTED )
	{
		GetElevationState( );
	}
	if ( FindWindowA( nullptr, cstrAnticheatName ) )
	{
		if ( eElevationState == EElevation::ADMIN )
		{
			system( "taskkill /F /T /IM " + chAnticheatExe );
			LogDebugMsg( WRN, "Found anticheat %s open and terminated it", cstrAnticheatName );
			return EAnticheatStatus::KILLED;
		}
		LogDebugMsg( WRN, "Found anticheat %s open", cstrAnticheatName );
		return EAnticheatStatus::FAILED;
	}
	LogDebugMsg( WRN, "Did not find anticheat %s open", cstrAnticheatName );
	return EAnticheatStatus::NOT_FOUND;
}

float CGeneral::GetWindowsSensitivity( )
{
	int iWindowsSensitivity;
	if ( SystemParametersInfo( SPI_GETMOUSESPEED, 0, &iWindowsSensitivity, false ) )
	{
		return float( iWindowsSensitivity ) / 20.f;
	}
	return 1.f;
}

CGeneral all;
