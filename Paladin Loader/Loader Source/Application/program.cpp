#include "../main.h"

void CProgram::GetUserInfo( )
{
	wchar_t wchBuffer[ 257 ];
	DWORD dwBufferSize = 257;
	GetUserName( wchBuffer, &dwBufferSize );
	uCurrentUser.wstrWindowsName = wchBuffer;
	LOG_DEBUG( DBG, L"Current User Username: %s", uCurrentUser.wstrWindowsName.c_str( ) );

	SYSTEM_INFO siCurrentUser { };
	GetSystemInfo( &siCurrentUser );
	uCurrentUser.iHardwareID = siCurrentUser.dwActiveProcessorMask * siCurrentUser.dwNumberOfProcessors;
	LOG_DEBUG( DBG, L"Current User HWID: %i", uCurrentUser.iHardwareID );

	std::wifstream fsRegKey( "reg.key" );
	std::wstring wstrBuffer { };

	std::getline( fsRegKey, wstrBuffer );
	uCurrentUser.iUserID = std::stoi( wstrBuffer );
	std::getline( fsRegKey, wstrBuffer );
	uCurrentUser.wstrSecretKey = wstrBuffer;
}

void CProgram::DeleteUserInfo( )
{
	uCurrentUser.iUserID = 0;
	uCurrentUser.wstrSecretKey = nullptr;
	uCurrentUser.wstrWindowsName = nullptr;
	uCurrentUser.iHardwareID = 0;
}

unsigned WriteCallback( void *lpContents, unsigned uSize, unsigned uMember, void *lpUser )
{
	static_cast< std::wstring* >( lpUser )->append( static_cast< wchar_t* >( lpContents ), uSize * uMember ); // TODO tranny, check if wstring works here
	return uSize * uMember;
}

EPremium CProgram::GetPremium( )
{
	if ( EPOCH_TO_JANUARY_2017 > GetMoment( ) )
	{
		LOG_DEBUG( ERR, L"Date Mismatch: %lli > %lli", EPOCH_TO_JANUARY_2017, GetMoment( ) );
		return EPremium::NOT_PREMIUM;
	}

	GetUserInfo( );

	const wchar_t *szParameters = ( std::wstring( L"user_id=" ) + std::to_wstring( uCurrentUser.iUserID ) + L"&secret_key=" + uCurrentUser.wstrSecretKey +
		L"&windows_name=" + uCurrentUser.wstrWindowsName + L"&hardware_id=" + std::to_wstring( uCurrentUser.iHardwareID ) ).c_str( );
	std::wstring strResponse { };

	// CONNECT

	DeleteUserInfo( );

	return strResponse.c_str( ) ? EPremium( std::stoi( strResponse ) ) : EPremium::NOT_PREMIUM;
}

EElevation CProgram::GetElevationState( HANDLE hTarget )
{
	HANDLE hTokenTarget;
	TOKEN_ELEVATION teTarget;
	DWORD dwReturnLength = sizeof( TOKEN_ELEVATION);
	if ( OpenProcessToken( hTarget, TOKEN_QUERY, &hTokenTarget ) &&
		GetTokenInformation( hTokenTarget, TokenElevation, &teTarget, dwReturnLength, &dwReturnLength ) )
	{
		CloseHandle( hTokenTarget );
		return EElevation( teTarget.TokenIsElevated );
	}
	CloseHandle( hTokenTarget );
	return EElevation::NOT_ADMIN;
}

EAnticheatStatus CProgram::KillAnticheat( LPCWSTR cstrAnticheatName, const wchar_t *chAnticheatExe )
{
	if ( FindWindow( nullptr, cstrAnticheatName ) )
	{
		if ( GetElevationState( GetCurrentProcess( ) ) == EElevation::ADMIN )
		{
			system( &"taskkill /F /T /IM "[ *chAnticheatExe ] );
			LOG_DEBUG( WRN, L"Found anticheat ''%s'' open and terminated it", cstrAnticheatName );
			return EAnticheatStatus::KILLED;
		}
		LOG_DEBUG( WRN, L"Found anticheat ''%s'' open", cstrAnticheatName );
		return EAnticheatStatus::FAILED;
	}
	LOG_DEBUG( WRN, L"Didn't find anticheat ''%s'' open", cstrAnticheatName );
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
