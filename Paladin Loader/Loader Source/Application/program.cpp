#include "../main.h"

void CProgram::GetUserInfo( )
{
	char chBuffer[ 257 ];
	DWORD dwBufferSize = 257;
	GetUserNameA( chBuffer, &dwBufferSize );
	uCurrentUser.strWindowsName = chBuffer;
	LOG_DEBUG( DBG, "Current User Username: %s", uCurrentUser.strWindowsName.c_str( ) );

	SYSTEM_INFO siCurrentUser { };
	GetSystemInfo( &siCurrentUser );
	uCurrentUser.iHardwareID = siCurrentUser.dwActiveProcessorMask * siCurrentUser.dwNumberOfProcessors;
	LOG_DEBUG( DBG, "Current User HWID: %i", uCurrentUser.iHardwareID );

	std::ifstream fsRegKey( "reg.key" );
	std::string strBuffer { };

	std::getline( fsRegKey, strBuffer );
	uCurrentUser.iUserID = std::stoi( strBuffer );
	std::getline( fsRegKey, strBuffer );
	uCurrentUser.strSecretKey = strBuffer;
}

void CProgram::DeleteUserInfo( )
{
	uCurrentUser.iUserID = 0;
	uCurrentUser.strSecretKey = nullptr;
	uCurrentUser.strWindowsName = nullptr;
	uCurrentUser.iHardwareID = 0;
}

unsigned WriteCallback( void *lpContents, unsigned uSize, unsigned uMember, void *lpUser )
{
	static_cast< std::string* >( lpUser )->append( static_cast< char* >( lpContents ), uSize * uMember );
	return uSize * uMember;
}

EPremium CProgram::GetPremium( )
{
	if ( EPOCH_TO_JANUARY_2017 > GetMoment( ) )
	{
		LOG_DEBUG( ERR, "Date Mismatch: %lli > %lli", EPOCH_TO_JANUARY_2017, GetMoment( ) );
		return EPremium::NOT_PREMIUM;
	}

	GetUserInfo( );

	const char *szParameters = ( std::string( "user_id=" ) + std::to_string( uCurrentUser.iUserID ) + "&secret_key=" + uCurrentUser.strSecretKey +
								 "&windows_name=" + uCurrentUser.strWindowsName + "&hardware_id=" + std::to_string( uCurrentUser.iHardwareID ) ).c_str( );
	std::string strResponse { };

	curl_global_init( CURL_GLOBAL_ALL );
	void *lpCurlConnectionType = curl_easy_init( );
	curl_easy_setopt( lpCurlConnectionType, CURLOPT_URL, "https://paladin.rip/auth.php" );
	curl_easy_setopt( lpCurlConnectionType, CURLOPT_POSTFIELDS, szParameters );
	curl_easy_setopt( lpCurlConnectionType, CURLOPT_WRITEFUNCTION, WriteCallback );
	curl_easy_setopt( lpCurlConnectionType, CURLOPT_WRITEDATA, &strResponse );
	curl_easy_perform( lpCurlConnectionType );
	curl_easy_cleanup( lpCurlConnectionType );

	DeleteUserInfo( );

	return strResponse.c_str( ) ? EPremium( std::stoi( strResponse ) ) : EPremium::NOT_PREMIUM;
}

EElevation CProgram::GetElevationState( HANDLE hTarget )
{
	HANDLE hTokenTarget;
	TOKEN_ELEVATION teTarget;
	DWORD dwReturnLength = sizeof( TOKEN_ELEVATION );
	if ( OpenProcessToken( hTarget, TOKEN_QUERY, &hTokenTarget ) &&
		 GetTokenInformation( hTokenTarget, TokenElevation, &teTarget, dwReturnLength, &dwReturnLength ) )
	{
		CloseHandle( hTokenTarget );
		return EElevation( teTarget.TokenIsElevated );
	}
	CloseHandle( hTokenTarget );
	return EElevation::NOT_ADMIN;
}

EAnticheatStatus CProgram::KillAnticheat( LPCSTR cstrAnticheatName, char *chAnticheatExe )
{
	if ( FindWindow( nullptr, cstrAnticheatName ) )
	{
		if ( GetElevationState( GetCurrentProcess( ) ) == EElevation::ADMIN )
		{
			system( &"taskkill /F /T /IM "[ *chAnticheatExe ] );
			LOG_DEBUG( WRN, "Found anticheat ''%s'' open and terminated it", cstrAnticheatName );
			return EAnticheatStatus::KILLED;
		}
		LOG_DEBUG( WRN, "Found anticheat ''%s'' open", cstrAnticheatName );
		return EAnticheatStatus::FAILED;
	}
	LOG_DEBUG( WRN, "Didn't find anticheat ''%s'' open", cstrAnticheatName );
	return EAnticheatStatus::NOT_FOUND;
}

const char *CProgram::GetFileHash( char *szFileName )
{
	std::ifstream fsFile( szFileName );
	std::stringstream strsHash { };

	int iHashSeed = 7531;
	char chBuffer { };
	
	while ( fsFile.get( chBuffer ) )
	{
		iHashSeed = ( iHashSeed << 5 ) + iHashSeed + chBuffer;
	}

	strsHash << std::hex << std::setw( 8 ) << std::setfill( '0' ) << iHashSeed;

	return strsHash.str( ).c_str( );
}

float CProgram::GetWindowsSensitivity( )
{
	unsigned short usWindowsSensitivity;
	if ( SystemParametersInfoA( SPI_GETMOUSESPEED, 0, &usWindowsSensitivity, false ) )
	{
		return float( usWindowsSensitivity ) / 20.f;
	}
	return 1.f;
}

CProgram pro;
