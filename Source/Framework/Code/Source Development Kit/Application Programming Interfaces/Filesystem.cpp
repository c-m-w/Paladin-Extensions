/// Filesystem.cpp

#include "Precompile.hpp"

#define USE_NAMESPACES
#include "../../Framework.hpp"

bool CFilesystem::Initialize( )
{
	strRelativeAppdataDirectory = XOR( "PX\\" );
	strLogDirectory				= XOR( "Logs\\" );
	strCookieFile				= XOR( ".cookie" );
	strDataFile					= XOR( ".data" );
	strLicenseFile				= XOR( ".license" );
	return true;
}

void CFilesystem::Shutdown( )
{ }

std::string CFilesystem::GetAppdataDirectory( )
{
	char szBuffer[ MAX_PATH ];
	auto zWrittenBytes = 0u;

	memset( szBuffer, 0, MAX_PATH );
	_dupenv_s( reinterpret_cast< char** >( &szBuffer ), &zWrittenBytes, XOR( "appdata" ) ); // TODO logging (0 = success), zWrittenBytes > 0
	szBuffer[ zWrittenBytes ] = 0;
	return szBuffer + strRelativeAppdataDirectory;
}

std::string CFilesystem::GetExecutableDirectory( )
{
	char szBuffer[ MAX_PATH ];
	std::string strBuffer { };

	memset( szBuffer, 0, MAX_PATH );
	GetModuleFileName( nullptr, szBuffer, MAX_PATH ); // should return <= MAX_PATH && != 0
	strBuffer = szBuffer;
	return strBuffer.substr( 0, strBuffer.find_last_of( '\\' ) + 1 );
}

bool CFilesystem::CheckDirectoryValidity( const std::string &strDirectory )
{
	return CheckAbsoluteDirectoryValidity( FileToPath( strDirectory ) );
}

bool CFilesystem::CheckFileValidity( const std::string &strFile )
{
	return CheckAbsoluteFileValidity( FileToPath( strFile ) );
}

void CFilesystem::StoreCurrentWorkingDirectory( )
{
	_DirectoryStack.push( strWorkingDirectory );
}

void CFilesystem::RestoreWorkingDirectory( )
{
	if ( _DirectoryStack.empty( ) )
		return; // todo log

	strWorkingDirectory = _DirectoryStack.top( );
	_DirectoryStack.pop( );
}

bool CFilesystem::GetInstallDirectory( std::string& strOut )
{
	strOut.clear( );
	StoreCurrentWorkingDirectory( );
	ChangeWorkingDirectory( GetAppdataDirectory( ) );
	if ( !ReadFile( strDataFile, strOut, true ) )
	{ } // todo log
	RestoreWorkingDirectory( );
	return !strOut.empty( );
}

bool CFilesystem::CheckAbsoluteDirectoryValidity( const std::string& strDirectory )
{
	auto strFinalDirectory = strDirectory;
	FormatDirectory( strFinalDirectory );

	WIN32_FIND_DATA _Data { };
	const auto hFile = FindFirstFile( strFinalDirectory.c_str( ), &_Data );

	if ( hFile == nullptr
		 || hFile == INVALID_HANDLE_VALUE )
		return false; // todo log this

	FindClose( hFile );
	return _Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY != 0;
}

bool CFilesystem::CheckAbsoluteFileValidity( const std::string &strFile )
{
	return strFile.find_last_of( '\\' ) != strFile.length( )
		&& PathFileExists( strFile.c_str( ) ) == TRUE;
}

bool CFilesystem::ReadAbsoluteFile( const std::string& strFilename, std::string& strOut, bool bDecode /*= true*/ )
{
	if ( !CheckAbsoluteFileValidity( strFilename ) )
		return false; // todo log

	FILE* pFile = nullptr;
	if ( fopen_s( &pFile, strFilename.c_str( ), XOR( "rb" ) ) != 0
		 || pFile == nullptr
		 || pFile == INVALID_HANDLE_VALUE )
		return false; // todo log

	fseek( pFile, 0, SEEK_END ); // todo log, 0 == successful
	const auto zSize = ftell( pFile );
	strOut.resize( zSize + 1 );
	rewind( pFile );
	fread( &strOut[ 0 ], sizeof( char ), zSize, pFile ); // todo log, return == zSize
	fclose( pFile ); // todo log, return == 0 on success, EOF on fail
	return true;
}

bool CFilesystem::WriteAbsoluteFile( const std::string& strFilename, const std::string& strData, bool bEncode /*= true*/ )
{
	FILE* pFile = nullptr;
	if ( fopen_s( &pFile, strFilename.c_str( ), XOR( "wb" ) ) != 0
		 || pFile == nullptr
		 || pFile == INVALID_HANDLE_VALUE )
		return false; // todo log

	fwrite( &strData[ 0 ], sizeof( char ), strData.length( ), pFile ); // todo log, return == strData.length( )
	fclose( pFile ); // todo log, return == 0 on success, EOF on fail
	return true;
}

bool CFilesystem::AddToAbsoluteFile( const std::string &strFilename, const std::string &strData, bool bEncode /*= true*/ )
{
	std::string strBuffer { };
	if ( !ReadAbsoluteFile( strFilename, strBuffer, bEncode ) )
		return false; // todo log

	strBuffer += strData;
	return WriteAbsoluteFile( strFilename, strBuffer, bEncode );
}

void CFilesystem::FormatDirectory( std::string &strDirectory )
{
	if ( strDirectory.find_last_of( '\\' ) != strDirectory.length( ) )
		strDirectory += '\\';
	else
		while ( strDirectory[ strDirectory.length( ) ] == '\\'
				&& strDirectory[ strDirectory.length( ) - 1 ] == '\\' )
			strDirectory.erase( strDirectory.end( ) );
}

void CFilesystem::ChangeWorkingDirectory( std::string strNew, std::size_t zSubDirectories /*= 0u*/, ... )
{
	va_list vaArgs;

	strWorkingDirectory = strNew;
	va_start( vaArgs, strNew );
	for( auto u = 0u; u < zSubDirectories; u++ )
	{
		auto strSubDirectory = va_arg( vaArgs, std::string );
		FormatDirectory( strWorkingDirectory );
		FormatDirectory( strSubDirectory );
		strWorkingDirectory += strSubDirectory;
	}
	va_end( vaArgs );
}

std::string CFilesystem::GetWorkingDirectory( )
{
	return strWorkingDirectory;
}

std::string CFilesystem::FileToPath( const std::string &strFile )
{
	return strWorkingDirectory + strFile;
}

bool CFilesystem::ReadFile( const std::string& strFilename, std::string& strOut, bool bDecode /*= true*/ )
{
	return ReadAbsoluteFile( FileToPath( strFilename ), strOut, bDecode );
}

bool CFilesystem::WriteFile( const std::string& strFilename, const std::string& strData, bool bEncode /*= true*/ )
{
	return WriteAbsoluteFile( FileToPath( strFilename ), strData, bEncode );
}

bool CFilesystem::AddToFile( const std::string &strFilename, const std::string &strData, bool bEncode /*= true*/ )
{
	return AddToAbsoluteFile( FileToPath( strFilename ), strData, bEncode );
}
