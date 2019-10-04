/// Logging.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_DEFINITIONS
#define USE_NAMESPACES
#include "../Framework.hpp"

bool CLogging::Initialize( )
{
#if defined _DEBUG || true
	for ( auto &strLocation: strLocations )
		if ( strLocation.empty( ) )
			throw std::runtime_error( ENC( "Ensure that all location strings are initialized." ) );
#endif

	BeginLog( );
	return true;
}

std::string CLogging::FormatTime( const std::string &strFormat )
{
	char szBuffer[ TIME_STRING_LENGTH ];
	auto tmNow = time_t( GetMoment( ) );
	tm tmTime;

	memset( szBuffer, 0, TIME_STRING_LENGTH );
	time( &tmNow );
	if ( localtime_s( &tmTime, &tmNow ) != 0 )
		memcpy( szBuffer, &strErrorTime[ 0 ], strErrorTime.length( ) );
	else
		strftime( szBuffer, TIME_STRING_LENGTH, strFormat.c_str( ), &tmTime );

	return std::string( szBuffer );
}

std::string CLogging::GetDatestamp( )
{
	return FormatTime( strDateFormat );
}

std::string CLogging::GetTimestamp( )
{
	return '[' + FormatTime( strTimeFormat ) + ']';
}

std::string CLogging::GetCurrentLogFile( )
{
#if defined _DEBUG || true
	static const auto strLogFile = FormatTime( strLogFileFormat ) + 'd';
#else
	static const auto strLogFile = FormatTime( strLogFileFormat );
#endif
	return strLogFile;
}

std::string CLogging::GetLogEncryptionKey( )
{
	static const auto strEncryptionKey = CRYPTO.GenerateHash( GetCurrentLogFile( ) ).substr( 0, CCryptography::ENCRYPTION_KEY_SIZE );
	return strEncryptionKey;
}

std::string CLogging::GetLogInitializationVector( )
{
	static const auto strInitializationVector = GetLogEncryptionKey( ).substr( 0, CCryptography::INITIALIZATION_VECTOR_SIZE );
	return strInitializationVector;
}

void CLogging::HandleUnloggableError( EUnloggableError _ErrorCode )
{
	if ( bUnsafeUninstalling )
		return;

	if ( _ErrorCode == ERROR_CANNOT_WRITE_LOG )
	{
		std::string strEncryptedBuffer { };
		if ( CRYPTO.Encrypt( strBuffer, strEncryptedBuffer, CRYPTO.strStaticEncryptionKey, CRYPTO.strStaticInitializationVector )
			&& SI.SetClipboardData( strEncryptedBuffer ) )
		{
			MessageBox( nullptr, ENC( "An error log has been copied to your clipboard. If this issue persists,\n"
									 "please open a support ticket with the copied error log in the appropriate box." ), ENC( "Error" ), MB_OK );
			return;
		}
	}

	MessageBox( nullptr, ENC( "An error has occurred. If this issue persists, please contact\n"
							 "support and include a screenshot of this message box." ), std::to_string( int( _ErrorCode ) ).c_str( ), MB_OK );
}

void CLogging::WriteToFile( )
{
	mmtLastLogWrite = GetMoment( );
	_Filesystem.StoreCurrentWorkingDirectory( );
	_Filesystem.ChangeWorkingDirectory( _Filesystem.GetAppdataDirectory( ), { _Filesystem.strLogDirectory } );

#if defined _DEBUG || true
	if ( !_Filesystem.AddToFile( GetCurrentLogFile( ), strBuffer, false ) )
		if ( !_Filesystem.WriteFile( GetCurrentLogFile( ), strBuffer, false ) )
			return HandleUnloggableError( ERROR_CANNOT_WRITE_LOG );
#else
	if ( !_Filesystem.AddToFile( GetCurrentLogFile( ), strBuffer, true ) )
		if ( !_Filesystem.WriteFile( GetCurrentLogFile( ), strBuffer, true ) )
			return HandleUnloggableError( ERROR_CANNOT_WRITE_LOG );
#endif

	_Filesystem.RestoreWorkingDirectory( );
	strBuffer.clear( );
}

void CLogging::TestWriteToFile( )
{
	if ( GetMoment( ) - mmtLastLogWrite > WRITE_INTERVAL )
		WriteToFile( );
}

void CLogging::BeginLog( )
{
	strBuffer = ENC( "-----[ Log Begin | " ) + GetDatestamp( ) + ENC( " ]-----\n" );
}

void CLogging::EndLog( )
{
	WriteToFile( );
	strBuffer += ENC( "-----[ Log End ]-----\n\n" );
	WriteToFile( );
}

void CLogging::Uninitialize( )
{
	EndLog( );
}

void CLogging::Log( EPrefix _Prefix, ELocation _Location, const std::string &strLog )
{
	if ( !GetInitializationState( ) )
		return HandleUnloggableError( ERROR_UNITIALIZED_LOG );

	const auto strFormattedLog = GetTimestamp( ) + '\t' + strStatusPrefixes[ _Prefix ] + '\t' + strLocations[ _Location ] + '\t' + strLog + '\n';

	strBuffer += strFormattedLog;

#if defined _DEBUG
	printf( strFormattedLog.c_str( ) );
#endif

	if ( _Prefix == ERROR )
		Log( INFO, _Location, ENC( "Last error: %i." ), GetLastError( ) ), SetLastError( ERROR_SUCCESS );
}

void CLogging::Log( EPrefix _Prefix, ELocation _Location, const char *szFormat, ... )
{
	if ( !GetInitializationState( ) )
		return HandleUnloggableError( ERROR_UNITIALIZED_LOG );

	va_list vaArgs;
	char chBuffer[ MAX_LOG_LENGTH ];

	memset( chBuffer, 0, MAX_LOG_LENGTH );
	va_start( vaArgs, szFormat );
	if ( _vsnprintf_s( chBuffer, MAX_LOG_LENGTH, szFormat, vaArgs ) == 0 )
		return HandleUnloggableError( ERROR_FORMAT_VA_FAILED );

	va_end( vaArgs );
	return Log( _Prefix, _Location, std::string( chBuffer ) );
}
