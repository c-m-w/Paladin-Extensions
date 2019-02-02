/// Logging.cpp

#include "Precompile.hpp"

#define USE_NAMESPACES
#include "../Framework.hpp"

bool CLogging::Initialize( )
{
	strErrorTime							= XOR( "Error Retrieving Date/Time" );
	strDateFormat							= XOR( "%B %e, 20%g" );
	strTimeFormat							= XOR( "%H:%M:%S" );
	strLogFileFormat						= XOR( "%Y-%m-%d" );
	strErrorMessage							= XOR( "Contact support if this issue persists." );
	strStatusPrefixes[ PREFIX_INFO ]		= XOR( "[Info]\t" );
	strStatusPrefixes[ PREFIX_DEBUG ]		= XOR( "[Debug]\t" );
	strStatusPrefixes[ PREFIX_SUCCESS ]		= XOR( "[Success]" );
	strStatusPrefixes[ PREFIX_WARNING ]		= XOR( "[Warning]" );
	strStatusPrefixes[ PREFIX_ERROR ]		= XOR( "[Error]\t" );
	for ( auto i = 0; i < LOCATION_MAX; i++ )
		strLocations[ i ] = '[' + std::to_string( i ) + ']';

	for ( auto i = 0; i < ERROR_MAX; i++ )
		strUnloggableErrorTitles[ i ] = '[' + std::to_string( i ) + ']';

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
	return '[' + FormatTime( strDateFormat ) + ']';
}

std::string CLogging::GetTimestamp( )
{
	return '[' + FormatTime( strTimeFormat ) + ']';
}

std::string CLogging::GetCurrentLogFile( )
{
	static const auto strLogFile = FormatTime( strLogFileFormat );
	return strLogFile;
}

void CLogging::ErrorPopup( EUnloggableError _ErrorCode )
{
	MessageBox( nullptr, strErrorMessage.c_str( ), strUnloggableErrorTitles[ _ErrorCode ].c_str( ), MB_OK );
}

void CLogging::WriteToFile( )
{
	mmtLastLogWrite = GetMoment( );
	_Filesystem.ChangeWorkingDirectory( _Filesystem.GetAppdataDirectory( ), 1, _Filesystem.strLogDirectory );
	if ( !_Filesystem.AddToFile( GetCurrentLogFile( ), strBuffer ) )
		if ( !_Filesystem.WriteFile( GetCurrentLogFile( ), strBuffer ) )
			return ErrorPopup( ERROR_CANNOT_WRITE_LOG );

	strBuffer.clear( );
}

void CLogging::TestWriteToFile( )
{
	if ( GetMoment( ) - mmtLastLogWrite > WRITE_INTERVAL )
		WriteToFile( );
}

void CLogging::BeginLog( )
{
	strBuffer = XOR( "-----[ Log Begin | " ) + GetDatestamp( ) + XOR( " ]-----\n" );
	WriteToFile( );
}

void CLogging::EndLog( )
{
	strBuffer += XOR( "-----[ Log End ]-----\n\n" );
	WriteToFile( );
}

void CLogging::Shutdown( )
{
	EndLog( );
}

void CLogging::Log( EPrefix _Prefix, ELocation _Location, const std::string &strLog )
{
	if ( !GetInitializationState( ) )
		return ErrorPopup( ERROR_UNITIALIZED_LOG );

	strBuffer += GetTimestamp( ) + '\t' + strStatusPrefixes[ _Prefix ] + '\t' + strLocations[ _Location ] + strLog + '\n';
}

void CLogging::Log( EPrefix _Prefix, ELocation _Location, const char *szFormat, ... )
{
	if ( !GetInitializationState( ) )
		return ErrorPopup( ERROR_UNITIALIZED_LOG );

	va_list vaArgs;
	char chBuffer[ MAX_LOG_LENGTH ];

	memset( chBuffer, 0, MAX_LOG_LENGTH );
	va_start( vaArgs, szFormat );
	if( _vsnprintf_s( chBuffer, MAX_LOG_LENGTH, szFormat, vaArgs ) == 0 )
		return ErrorPopup( ERROR_FORMAT_VA_FAILED );

	va_end( vaArgs );
	return Log( _Prefix, _Location, chBuffer );
}