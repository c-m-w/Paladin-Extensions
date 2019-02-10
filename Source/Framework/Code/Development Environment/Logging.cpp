/// Logging.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_DEFINITIONS
#define USE_NAMESPACES
#include "../Framework.hpp"

bool CLogging::Initialize( )
{
	strErrorTime						= ENC( "Error Retrieving Date/Time" );
	strDateFormat						= ENC( "%B %e, 20%g" );
	strTimeFormat						= ENC( "%H:%M:%S" );
	strLogFileFormat					= ENC( "%Y.%m.%d" );
	strStatusPrefixes[ INFO ]			= ENC( "[Info]\t" );
	strStatusPrefixes[ DEBUG ]			= ENC( "[Debug]\t" );
	strStatusPrefixes[ SUCCESS ]		= ENC( "[Success]" );
	strStatusPrefixes[ WARNING ]		= ENC( "[Warning]" );
	strStatusPrefixes[ ERROR ]			= ENC( "[Error]\t" );
	strLocations[ FILESYSTEM ]			= ENC( "[Filesystem]\t" );
	strLocations[ CRYPTOGRAPHY ]		= ENC( "[Cryptography]\t" );
	strLocations[ CONNECTIVITY ]		= ENC( "[Connectivity]\t" );
	strLocations[ RESOURCE_MANAGER ]	= ENC( "[Resources]\t" );
	strLocations[ WINDOW ]				= ENC( "[Window]\t\t" );
	strLocations[ DRAWING ]				= ENC( "[Drawing]\t" );
	strLocations[ SYSTEM_INFORMATION ]  = ENC( "[System]\t\t" );
	strLocations[ MEMORY_MANAGER ]      = ENC( "[Memory]\t\t" );
	strLocations[ APPLICATION ]			= ENC( "[Application]\t" );

#if defined _DEBUG
	for ( auto &strLocation : strLocations )
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
#if defined _DEBUG
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

void CLogging::ErrorPopup( EUnloggableError _ErrorCode )
{
	MessageBox( nullptr, ENC( "Contact support if this issue persists." ), std::to_string( int( _ErrorCode ) ).c_str( ), MB_OK );
}

void CLogging::WriteToFile( )
{
	mmtLastLogWrite = GetMoment( );
	_Filesystem.StoreCurrentWorkingDirectory( );
	_Filesystem.ChangeWorkingDirectory( _Filesystem.GetAppdataDirectory( ), { _Filesystem.strLogDirectory } );

#if defined _DEBUG
	if ( !_Filesystem.AddToFile( GetCurrentLogFile( ), strBuffer, false ) )
		if ( !_Filesystem.WriteFile( GetCurrentLogFile( ), strBuffer, false ) )
			return ErrorPopup( ERROR_CANNOT_WRITE_LOG );
#else
	if ( !_Filesystem.AddToFile( GetCurrentLogFile( ), strBuffer, true ) )
		if ( !_Filesystem.WriteFile( GetCurrentLogFile( ), strBuffer, true ) )
			return ErrorPopup( ERROR_CANNOT_WRITE_LOG );
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
		return ErrorPopup( ERROR_UNITIALIZED_LOG );

	strBuffer += GetTimestamp( ) + '\t' + strStatusPrefixes[ _Prefix ] + '\t' + strLocations[ _Location ] + '\t' + strLog + '\n';
	if ( _Prefix == ERROR )
		Log( INFO, _Location, ENC( "Last error: %i." ), GetLastError( ) );
}

void CLogging::Log( EPrefix _Prefix, ELocation _Location, const char *szFormat, ... )
{
	if ( !GetInitializationState( ) )
		return ErrorPopup( ERROR_UNITIALIZED_LOG );

	va_list vaArgs;
	char chBuffer[ MAX_LOG_LENGTH ];

	memset( chBuffer, 0, MAX_LOG_LENGTH );
	va_start( vaArgs, szFormat );
	if ( _vsnprintf_s( chBuffer, MAX_LOG_LENGTH, szFormat, vaArgs ) == 0 )
		return ErrorPopup( ERROR_FORMAT_VA_FAILED );

	va_end( vaArgs );
	return Log( _Prefix, _Location, std::string( chBuffer ) );
}
