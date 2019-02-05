/// Filesystem.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

bool CFilesystem::Initialize( )
{
	strRelativeAppdataDirectory = XOR( "PX\\" );
	strRelativeResourceDirectory = XOR( "Resources\\" );
	strLogDirectory = XOR( "Logs\\" );
	strCookieFile = XOR( ".cookie" );
	strDataFile = XOR( ".data" );
	strLicenseFile = XOR( ".license" );
	ChangeWorkingDirectory( GetAppdataDirectory( ) );
	EscapeWorkingDirectory( );
	HidePath( strRelativeAppdataDirectory );

	return true;
}

void CFilesystem::working_directory_t::StoreCurrentWorkingDirectory( )
{
	_DirectoryStack.push( strWorkingDirectory );
}

void CFilesystem::working_directory_t::RestoreWorkingDirectory( )
{
	if ( _DirectoryStack.empty( ) )
		return; // todo log

	strWorkingDirectory = _DirectoryStack.top( );
	_DirectoryStack.pop( );
}

void CFilesystem::Uninitialize( )
{ }

std::string CFilesystem::GetAppdataDirectory( )
{
	char *szBuffer;
	auto zWrittenBytes = 0u;

	if ( 0 != _dupenv_s( &szBuffer, &zWrittenBytes, XOR( "appdata" ) )
		|| zWrittenBytes == 0 )
		_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, XOR( "Error retrieving appdata environment directory." ) );

	auto strDirectory = std::string( szBuffer );
	FormatDirectory( strDirectory );
	return strDirectory + strRelativeAppdataDirectory;
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
	GetThreadDirectories( ).StoreCurrentWorkingDirectory( );
}

void CFilesystem::RestoreWorkingDirectory( )
{
	GetThreadDirectories( ).RestoreWorkingDirectory( );
}

CFilesystem::working_directory_t &CFilesystem::GetThreadDirectories( )
{
	const auto dwThread = GetCurrentThreadId( );

	const auto pSearch = _ThreadDirectories.find( dwThread );
	if ( pSearch == _ThreadDirectories.end( ) )
	{
		_ThreadDirectories.insert( std::pair< DWORD, working_directory_t >( dwThread, working_directory_t( ) ) );
		return GetThreadDirectories( );
	}

	return pSearch->second;
}

bool CFilesystem::CheckAbsoluteDirectoryValidity( const std::string &strDirectory )
{
	auto strFinalDirectory = strDirectory;
	FormatDirectory( strFinalDirectory );

	WIN32_FIND_DATA _Data { };
	SetLastError( ERROR_SUCCESS );
	const auto hFile = FindFirstFile( strFinalDirectory.c_str( ), &_Data );

	if ( hFile == nullptr
		|| hFile == INVALID_HANDLE_VALUE )
		return GetLastError( ) == ERROR_FILE_NOT_FOUND;

	FindClose( hFile );
	return _Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY != 0;
}

bool CFilesystem::CheckAbsoluteFileValidity( const std::string &strFile )
{
	return strFile.find_last_of( '\\' ) != strFile.length( )
			&& PathFileExists( strFile.c_str( ) ) == TRUE;
}

std::string CFilesystem::GetAbsoluteContainingDirectory( const std::string &strFile )
{
	const auto zPosition = strFile.substr( 0, strFile.length( ) - 1 ).find_last_of( '\\' );
	auto strReturn = zPosition == std::string::npos ? strFile : strFile.substr( 0, zPosition );

	FormatDirectory( strReturn );
	return strReturn;
}

bool CFilesystem::EnsureAbsoluteFileDirectoryExists( const std::string &strFilePath )
{
	const auto strBaseDirectory = GetAbsoluteContainingDirectory( strFilePath );
	if ( CheckAbsoluteDirectoryValidity( strBaseDirectory ) )
		return true;

	auto strDirectory = strBaseDirectory;
	std::stack< std::string > _SubDirectories { };

	while ( !CheckAbsoluteDirectoryValidity( strDirectory ) )
	{
		auto strLast = strDirectory;

		strDirectory = GetAbsoluteContainingDirectory( strDirectory );
		strLast = strLast.substr( strDirectory.length( ) );
		FormatDirectory( strLast );
		_SubDirectories.push( strLast );
	}

	while( !_SubDirectories.empty( ) )
	{
		strDirectory += _SubDirectories.top( );
		_SubDirectories.pop( );
		if ( CreateDirectory( strDirectory.c_str( ), nullptr ) == FALSE )
			return false;
	}

	return true;
}

bool CFilesystem::GetAbsoluteDirectoryContents( const std::string &strDirectory, bool bFiles, bool bFolders, std::vector< std::string > &vecOut )
{
	auto strFinalDirectory = strDirectory;
	FormatDirectory( strFinalDirectory );

	WIN32_FIND_DATA _FileData;
	const auto hFile = FindFirstFile( ( strFinalDirectory + '*' ).c_str( ), &_FileData );

	if ( ( hFile == nullptr
			|| hFile == INVALID_HANDLE_VALUE )
		&& GetLastError( ) != ERROR_FILE_NOT_FOUND )
		return false;

	vecOut.clear( );
	do
	{
		if ( ( bFiles && !( _FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			|| bFolders && 0 < ( _FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
			 && strcmp( _FileData.cFileName, XOR( "." ) ) && strcmp( _FileData.cFileName, XOR( ".." ) ) )
			vecOut.emplace_back( _FileData.cFileName );
	}
	while ( FindNextFile( hFile, &_FileData ) == TRUE );

	return FindClose( hFile ) == TRUE;
}

bool CFilesystem::GetFoldersInAbsoluteDirectory( const std::string &strDirectory, std::vector< std::string > &vecOut )
{
	return GetAbsoluteDirectoryContents( strDirectory, false, true, vecOut );
}

bool CFilesystem::GetFilesInAbsoluteDirectory( const std::string &strDirectory, std::vector< std::string > &vecOut, const std::string &strExtension /*= std::string( )*/ )
{
	if ( !GetAbsoluteDirectoryContents( strDirectory, true, false, vecOut ) )
		return false;

	if ( !strExtension.empty( ) )
		for ( auto u = 0u; u < vecOut.size( ); u++ )
			if ( vecOut[ u ].find_last_of( strExtension ) != vecOut[ u ].length( ) - strExtension.length( ) )
			{
				vecOut.erase( vecOut.begin( ) + u );
				u--;
			}

	return true;
}

bool CFilesystem::ReadAbsoluteFile( const std::string &strFilename, std::string &strOut, bool bDecode /*= true*/ )
{
	if ( !CheckAbsoluteFileValidity( strFilename ) )
	{
		_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, XOR( "Reading attempted on non-existent file %s." ), strFilename.c_str( ) );
		return false;
	}

	FILE *pFile = nullptr;
	if ( fopen_s( &pFile, strFilename.c_str( ), XOR( "rb" ) ) != 0
		|| pFile == nullptr
		|| pFile == INVALID_HANDLE_VALUE )
	{
		_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, XOR( "Unable to open file %s for reading." ), strFilename.c_str( ) );
		return false;
	}

	fseek( pFile, 0, SEEK_END ); // todo log, 0 == successful
	const auto zSize = ftell( pFile );
	strOut.resize( zSize );
	rewind( pFile );
	if ( zSize != fread( &strOut[ 0 ], sizeof( char ), zSize, pFile ) )
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, XOR( "Unable to read foretold size of %i in file %s." ), zSize, strFilename.c_str( ) );

	if ( fclose( pFile ) == EOF )
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, XOR( "Unable to close file %s successfully." ), strFilename.c_str( ) );

	return true;
}

bool CFilesystem::WriteAbsoluteFile( const std::string &strFilename, const std::string &strData, bool bEncode /*= true*/ )
{
	FILE *pFile = nullptr;
	if ( EnsureAbsoluteFileDirectoryExists( strFilename )
		&& fopen_s( &pFile, strFilename.c_str( ), XOR( "w+b" ) ) != 0
		|| pFile == nullptr
		|| pFile == INVALID_HANDLE_VALUE )
	{
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, XOR( "Error opening file %s. Error code %i." ), strFilename.c_str( ), errno );
		return false;
	}

	if ( fwrite( &strData[ 0 ], sizeof( char ), strData.length( ), pFile ) != strData.length( ) )
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, XOR( "Failed to write all of data into file %s." ), strFilename.c_str( ) );

	if ( fclose( pFile ) == EOF )
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, XOR( "Failed to close file %s successfully." ), strFilename.c_str( ) );

	return true;
}

bool CFilesystem::AddToAbsoluteFile( const std::string &strFilename, const std::string &strData, bool bEncode /*= true*/ )
{
	std::string strBuffer { };
	if ( !ReadAbsoluteFile( strFilename, strBuffer, bEncode ) )
		return false;

	strBuffer += strData;
	return WriteAbsoluteFile( strFilename, strBuffer, bEncode );
}

bool CFilesystem::HideAbsolutePath( const std::string &strPath )
{
	auto strFinalPath = strPath;

	if ( SetFileAttributes( strFinalPath.c_str( ), FILE_ATTRIBUTE_HIDDEN ) != TRUE )
		return false;

	auto bReturn = true;

	if ( CheckAbsoluteDirectoryValidity( strFinalPath.c_str( ) ) )
	{
		FormatDirectory( strFinalPath );
		std::vector< std::string > vecContents { };

		if ( bReturn &= GetAbsoluteDirectoryContents( strFinalPath, true, true, vecContents ) )
			for each ( auto &strContent in vecContents )
				bReturn &= HideAbsolutePath( strFinalPath + strContent );
	}

	return bReturn;
}

void CFilesystem::FormatDirectory( std::string &strDirectory )
{
	if ( strDirectory.find_last_of( '\\' ) != strDirectory.length( ) - 1 )
		strDirectory += '\\';
	else
		while ( strDirectory[ strDirectory.length( ) ] == '\\'
			&& strDirectory[ strDirectory.length( ) - 1 ] == '\\' )
			strDirectory.erase( strDirectory.end( ) );
}

std::string CFilesystem::ChangeWorkingDirectory( std::string strNew, std::initializer_list< std::string > initSubDirectories /*= { }*/ )
{
	auto &strWorkingDirectory = GetWorkingDirectory( );

	strWorkingDirectory = strNew;
	FormatDirectory( strWorkingDirectory );

	for ( auto strSubDirectory: initSubDirectories )
	{
		FormatDirectory( strSubDirectory );
		strWorkingDirectory += strSubDirectory;
	}

	return strWorkingDirectory;
}

void CFilesystem::EscapeWorkingDirectory( )
{
	ChangeWorkingDirectory( GetAbsoluteContainingDirectory( GetWorkingDirectory( ) ) );
}

std::string &CFilesystem::GetWorkingDirectory( )
{
	return GetThreadDirectories( ).strWorkingDirectory;
}

std::string CFilesystem::FileToPath( const std::string &strFile )
{
	return GetWorkingDirectory( ) + strFile;
}

bool CFilesystem::ReadFile( const std::string &strFilename, std::string &strOut, bool bDecode /*= true*/ )
{
	return ReadAbsoluteFile( FileToPath( strFilename ), strOut, bDecode );
}

bool CFilesystem::WriteFile( const std::string &strFilename, const std::string &strData, bool bEncode /*= true*/ )
{
	return WriteAbsoluteFile( FileToPath( strFilename ), strData, bEncode );
}

bool CFilesystem::AddToFile( const std::string &strFilename, const std::string &strData, bool bEncode /*= true*/ )
{
	return AddToAbsoluteFile( FileToPath( strFilename ), strData, bEncode );
}

bool CFilesystem::GetDirectoryContents( const std::string &strDirectory, bool bFiles, bool bFolders, std::vector< std::string > &vecOut )
{
	return GetAbsoluteDirectoryContents( FileToPath( strDirectory ), bFiles, bFolders, vecOut );
}

bool CFilesystem::GetFoldersInDirectory( const std::string &strDirectory, std::vector< std::string > &vecOut )
{
	return GetFoldersInAbsoluteDirectory( FileToPath( strDirectory ), vecOut );
}

bool CFilesystem::GetFilesInDirectory( const std::string &strDirectory, std::vector< std::string > &vecOut, const std::string &strExtension /*= std::string( )*/ )
{
	return GetFilesInAbsoluteDirectory( FileToPath( strDirectory ), vecOut, strExtension );
}

bool CFilesystem::HidePath( const std::string &strPath )
{
	return HideAbsolutePath( FileToPath( strPath ) );
}
