/// Filesystem.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

bool CFilesystem::Initialize( )
{
	strRelativeAppdataDirectory = ENC( "PX_\\" );
	strRelativeResourceDirectory = ENC( "Resources\\" );
	strLogDirectory = ENC( "Logs\\" );
	strCookieFile = ENC( ".cookie" );
	strDataFile = ENC( ".data" );
	strLicenseFile = ENC( ".license" );
	ChangeWorkingDirectory( GetAppdataDirectory( ) );
	EscapeWorkingDirectory( );
	if ( !EnsureDirectoryExists( strRelativeAppdataDirectory ) )
		return false;

	return SetPathVisibility( strRelativeAppdataDirectory, false );
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
	static std::string strBuffer { };

	if ( strBuffer.empty( ) )
	{
		char *szBuffer;
		auto zWrittenBytes = 0u;

		if ( 0 != _dupenv_s( &szBuffer, &zWrittenBytes, ENC( "appdata" ) )
			 || zWrittenBytes == 0 )
			_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, ENC( "Error retrieving appdata environment directory." ) );

		auto strDirectory = std::string( szBuffer );
		FormatDirectory( strDirectory );
		strBuffer = strDirectory + strRelativeAppdataDirectory;
	}

	return strBuffer;
}

std::string CFilesystem::GetExecutableDirectory( bool bIncludeExecutableInPath /*= false*/ )
{
	static std::string strBuffer { };
	static bool bLastCall = false;

	if ( strBuffer.empty( ) || bLastCall != bIncludeExecutableInPath )
	{
		bLastCall = bIncludeExecutableInPath;

		char szBuffer[ MAX_PATH ];
		memset( szBuffer, 0, MAX_PATH );
		GetModuleFileName( nullptr, szBuffer, MAX_PATH ); // should return <= MAX_PATH && != 0
		strBuffer = szBuffer;

		if ( !bIncludeExecutableInPath )
			strBuffer = strBuffer.substr( 0, strBuffer.find_last_of( '\\' ) + 1 );
	}

	return strBuffer;
}

std::string CFilesystem::GetEncryptedFilename( const std::string &strFile )
{
	return GetAbsoluteEncryptedFilename( FileToPath( strFile ) );
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

std::string CFilesystem::GetAbsoluteEncryptedFilename( const std::string &strAbsolutePath )
{
	const auto strFile = CRYPTO.GenerateHash( PathToFile( strAbsolutePath ) );
	return GetAbsoluteContainingDirectory( strAbsolutePath ) + strFile;
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
	return ( _Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) != 0;
}

bool CFilesystem::CheckAbsoluteFileValidity( const std::string &strFile )
{
	return strFile.find_last_of( '\\' ) != strFile.length( )
			&& PathFileExists( strFile.c_str( ) ) == TRUE;
}

std::string CFilesystem::GetAbsoluteContainingDirectory( const std::string &strFile )
{
	const auto zPosition = strFile.substr( 0, strFile.length( ) - 1 ).find_last_of( '\\' );
	auto strReturn = zPosition == std::string::npos ? std::string( ) : strFile.substr( 0, zPosition );

	FormatDirectory( strReturn );
	return strReturn;
}

std::string CFilesystem::PathToFile( const std::string &strPath )
{
	if ( strPath.find( '\\' ) == std::string::npos )
		return strPath;

	return strPath.substr( strPath.find_last_of( '\\' ) + 1 );
}

std::string CFilesystem::PathToDirectory( const std::string &strPath )
{
	auto strFormatted = strPath.substr( 0, strPath.find_last_of( '\\' ) );
	FormatDirectory( strFormatted );
	return strFormatted;
}

void CFilesystem::CloseAllFileHandles( )
{
	const auto iResult = _fcloseall( );

	if ( iResult == EOF )
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, ENC( "Failed to close all open file handles." ) );
	else if ( iResult > 0 )
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, ENC( "%i open file handles were closed." ), iResult );
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

	while ( !_SubDirectories.empty( ) )
	{
		strDirectory += _SubDirectories.top( );
		_SubDirectories.pop( );
		if ( CreateDirectory( strDirectory.c_str( ), nullptr ) == FALSE )
			return false;
	}

	return true;
}

bool CFilesystem::EnsureAbsoluteDirectoryExists( const std::string &strDirectory )
{
	return EnsureAbsoluteFileDirectoryExists( strDirectory + '.' ); // dummy file
}

bool CFilesystem::GetAbsolutePathVisibility( const std::string &strPath )
{
	const auto dwAttributes = GetFileAttributes( strPath.c_str( ) );
	if ( dwAttributes == INVALID_FILE_ATTRIBUTES )
	{
		_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, ENC( "Unable to get attributes of file %s." ), strPath.c_str( ) );
		return false;
	}

	return !( dwAttributes & FILE_ATTRIBUTE_HIDDEN );
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
			&& strcmp( _FileData.cFileName, ENC( "." ) ) && strcmp( _FileData.cFileName, ENC( ".." ) ) )
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

bool CFilesystem::DeleteAbsolutePath( const std::string &strPath )
{
	if ( !CheckAbsoluteDirectoryValidity( strPath )
		 && !CheckAbsoluteFileValidity( strPath ) )
	{
		const auto strEncryptedPath = GetAbsoluteEncryptedFilename( strPath );
		return CheckAbsoluteDirectoryValidity( strEncryptedPath ) || CheckAbsoluteFileValidity( strEncryptedPath ) ?
			DeleteAbsolutePath( strEncryptedPath ) : true;
	}

	auto strFinal = strPath;

	CloseAllFileHandles( );
	if ( !GetAbsolutePathVisibility( strFinal ) )
		if ( !SetAbsolutePathVisibility( strFinal, true ) )
			return false;

	if ( CheckAbsoluteDirectoryValidity( strFinal ) )
	{
		FormatDirectory( strFinal );
		std::vector< std::string > vecContents { };

		if ( !GetAbsoluteDirectoryContents( strFinal, true, true, vecContents ) )
			return false;

		for ( auto &strContent: vecContents )
			if ( !DeleteAbsolutePath( strFinal + strContent ) )
				return false;

		if ( RemoveDirectory( strFinal.c_str( ) ) == FALSE )
		{
			_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, ENC( "Unable to delete directory %s." ), strFinal.c_str( ) );
			return false;
		}

		return true;
	}

	if ( DeleteFile( strFinal.c_str( ) ) == FALSE )
	{
		const auto strEncryptedFile = GetAbsoluteEncryptedFilename( strPath );
		if ( CheckAbsoluteFileValidity( strEncryptedFile ) )
			return DeleteAbsolutePath( strEncryptedFile );

		_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, ENC( "Unable to delete file %s." ), strFinal.c_str( ) );
		return false;
	}

	return true;
}

bool CFilesystem::ReadAbsoluteFile( const std::string &strFilename, std::string &strOut, bool bDecrypt /*= true*/ )
{
	std::string strFinalFilename { };

	if ( bDecrypt )
		strFinalFilename = GetAbsoluteEncryptedFilename( strFilename );
	else
		strFinalFilename = strFilename;

	if ( !CheckAbsoluteFileValidity( strFinalFilename ) )
	{
		_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, ENC( "Reading attempted on non-existent file %s." ), strFinalFilename.c_str( ) );
		return false;
	}

	CloseAllFileHandles( );

	FILE *pFile = nullptr;
	if ( fopen_s( &pFile, strFinalFilename.c_str( ), ENC( "rb" ) ) != 0
		|| pFile == nullptr
		|| pFile == INVALID_HANDLE_VALUE )
	{
		_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, ENC( "Unable to open file %s for reading." ), strFinalFilename.c_str( ) );
		return false;
	}

	fseek( pFile, 0, SEEK_END ); // todo log, 0 == successful
	const auto zSize = ftell( pFile );
	strOut.resize( zSize );
	rewind( pFile );
	if ( zSize != fread( &strOut[ 0 ], sizeof( char ), zSize, pFile ) )
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, ENC( "Unable to read foretold size of %i in file %s." ), zSize, strFinalFilename.c_str( ) );

	if ( fclose( pFile ) == EOF )
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, ENC( "Unable to close file %s successfully." ), strFinalFilename.c_str( ) );

	if ( bDecrypt )
	{
		std::string strBuffer;

		if ( !CRYPTO.Decrypt( strOut, strBuffer, CRYPTO.strStaticEncryptionKey, CRYPTO.strStaticInitializationVector ) )
			_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, ENC( "Unable to decrypt file %s." ), strFinalFilename.c_str( ) );

		strOut = strBuffer;
	}

	return true;
}

bool CFilesystem::WriteAbsoluteFile( const std::string &strFilename, const std::string &strData, bool bEncrypt /*= true*/ )
{
	CloseAllFileHandles( );

	std::string strFinalData { };
	std::string strFinalFilename { };

	if ( bEncrypt )
	{
		strFinalFilename = GetAbsoluteEncryptedFilename( strFilename );
		if ( !CRYPTO.Encrypt( strData, strFinalData, CRYPTO.strStaticEncryptionKey, CRYPTO.strStaticInitializationVector ) )
		{
			_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, ENC( "Unable to encrypt data to write to file %s. Writing unencrypted data." ), strFilename.c_str( ) );
			strFinalData = strData;
		}
	}
	else
	{
		strFinalData = strData;
		strFinalFilename = strFilename;
	}

	auto bHidden = false;
	if ( CheckAbsoluteFileValidity( strFinalFilename.c_str( ) ) )
		if ( ( bHidden = !GetAbsolutePathVisibility( strFinalFilename ) ) )
			if ( !SetAbsolutePathVisibility( strFinalFilename, true ) )
				return false;

	FILE *pFile = nullptr;
	if ( EnsureAbsoluteFileDirectoryExists( strFinalFilename )
		&& fopen_s( &pFile, strFinalFilename.c_str( ), ENC( "w+b" ) ) != 0
		|| pFile == nullptr
		|| pFile == INVALID_HANDLE_VALUE )
	{
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, ENC( "Error opening file %s. Error code %i." ), strFinalFilename.c_str( ), errno );
		return false;
	}

	if ( fwrite( &strFinalData[ 0 ], sizeof( char ), strFinalData.length( ), pFile ) != strFinalData.length( ) )
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, ENC( "Failed to write all of data into file %s." ), strFinalFilename.c_str( ) );

	if ( fclose( pFile ) == EOF )
		_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, ENC( "Failed to close file %s successfully." ), strFinalFilename.c_str( ) );

	return bHidden ? SetAbsolutePathVisibility( strFinalFilename, false ) : true;
}

bool CFilesystem::AddToAbsoluteFile( const std::string &strFilename, const std::string &strData, bool bEncrypt )
{
	std::string strBuffer { };
	if ( !ReadAbsoluteFile( strFilename, strBuffer, bEncrypt ) )
		return false;

	strBuffer += strData;
	return WriteAbsoluteFile( strFilename, strBuffer, bEncrypt );
}

bool CFilesystem::EncryptAbsoluteFile( const std::string &strFilename )
{
	std::string strContents;
	return ReadAbsoluteFile( strFilename, strContents, false )
		&& WriteAbsoluteFile( strFilename, strContents, true );
}

bool CFilesystem::DecryptAbsoluteFile( const std::string &strFilename )
{
	std::string strContents;
	return ReadAbsoluteFile( strFilename, strContents, true )
		&& WriteAbsoluteFile( strFilename, strContents, false );
}

bool CFilesystem::SetAbsolutePathVisibility( const std::string &strPath, bool bVisible )
{
	CloseAllFileHandles( );
	auto strFinalPath = strPath;
	auto dwAttributes = GetFileAttributes( strFinalPath.c_str( ) );

	if ( dwAttributes == INVALID_FILE_ATTRIBUTES )
	{
		const auto strEncryptedFile = GetAbsoluteEncryptedFilename( strPath );
		if ( CheckAbsoluteFileValidity( strEncryptedFile ) )
			return SetAbsolutePathVisibility( strEncryptedFile, bVisible );

		_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, ENC( "Unable to get attributes of path %s." ), strFinalPath.c_str( ) );
		return false;
	}

	if ( bVisible )
		dwAttributes &= ~FILE_ATTRIBUTE_HIDDEN;
	else
		dwAttributes |= FILE_ATTRIBUTE_HIDDEN;

	if ( SetFileAttributes( strFinalPath.c_str( ), dwAttributes ) != TRUE )
	{
		const auto strEncryptedFile = GetAbsoluteEncryptedFilename( strPath );
		if ( CheckAbsoluteFileValidity( strEncryptedFile ) )
			return SetAbsolutePathVisibility( strEncryptedFile, bVisible );

		_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, ENC( "Unable to set attributes of file %s." ), strFinalPath.c_str( ) );
		return false;
	}

	auto bReturn = true;

	if ( CheckAbsoluteDirectoryValidity( strFinalPath.c_str( ) ) )
	{
		FormatDirectory( strFinalPath );
		std::vector< std::string > vecContents { };

		if ( bReturn &= GetAbsoluteDirectoryContents( strFinalPath, true, true, vecContents ) )
			for ( const auto &strContent: vecContents )
				bReturn &= SetAbsolutePathVisibility( strFinalPath + strContent, bVisible );
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

std::string CFilesystem::ChangeWorkingDirectory( std::string strNew, std::initializer_list< std::string > initSubDirectories /*= { }*/, bool bHashSubDirectories /*= true*/ )
{
	auto &strWorkingDirectory = GetWorkingDirectory( );

	strWorkingDirectory = strNew;
	FormatDirectory( strWorkingDirectory );

	for ( auto strSubDirectory: initSubDirectories )
	{
		if ( strSubDirectory.empty( ) )
			continue;

		std::vector< std::string > vecSubDirectories { };

		do
		{
			auto strFolder = strSubDirectory.substr( 0, strSubDirectory.find_first_of( '\\' ) + 1 );
			FormatDirectory( strFolder );
			vecSubDirectories.emplace_back( strFolder );
			strSubDirectory = strSubDirectory.substr( strFolder.length( ) );
		} while ( strSubDirectory.find_first_of( '\\' ) != std::string::npos );

		for ( auto &strFolder: vecSubDirectories )
			strWorkingDirectory += bHashSubDirectories ? CRYPTO.GenerateHash( strFolder.substr( 0, strFolder.length( ) - 1 ) ) + '\\' : strFolder;
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
	auto strFinalFile = strFile;
	if ( strFinalFile[ 0 ] == '\\' )
		strFinalFile.erase( strFinalFile.begin( ) );

	if ( strFinalFile.find( '\\' ) != std::string::npos
		 && strFinalFile.find( '\\' ) != strFinalFile.length( ) - 1 )
		throw std::runtime_error( ENC( "Cannot format a file in a non-current path."
									 /*"Change the working directory rather than entering a relative directory;\n"
									   "You may only modify a file in the current working directory."*/ ) );

	FormatDirectory( GetWorkingDirectory( ) );
	return GetWorkingDirectory( ) + strFinalFile;
}

bool CFilesystem::ReadFile( const std::string &strFilename, std::string &strOut, bool bDecrypt )
{
	return ReadAbsoluteFile( FileToPath( strFilename ), strOut, bDecrypt );
}

bool CFilesystem::WriteFile( const std::string &strFilename, const std::string &strData, bool bEncrypt )
{
	return WriteAbsoluteFile( FileToPath( strFilename ), strData, bEncrypt );
}

bool CFilesystem::AddToFile( const std::string &strFilename, const std::string &strData, bool bEncrypt )
{
	return AddToAbsoluteFile( FileToPath( strFilename ), strData, bEncrypt );
}

bool CFilesystem::EncryptFile( const std::string &strFilename )
{
	return EncryptAbsoluteFile( FileToPath( strFilename ) );
}

bool CFilesystem::DecryptFile( const std::string &strFilename )
{
	return DecryptAbsoluteFile( FileToPath( strFilename ) );
}

bool CFilesystem::EnsureFileDirectoryExists( const std::string &strFile )
{
	return EnsureAbsoluteFileDirectoryExists( FileToPath( strFile ) );
}

bool CFilesystem::EnsureDirectoryExists( const std::string &strDirectory )
{
	return EnsureAbsoluteDirectoryExists( FileToPath( strDirectory ) );
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

bool CFilesystem::DeleteCurrentDirectory( )
{
	return DeleteAbsolutePath( GetWorkingDirectory( ) );
}

bool CFilesystem::DeletePath( const std::string &strRelativePath )
{
	return DeleteAbsolutePath( FileToPath( strRelativePath ) );
}

bool CFilesystem::SetPathVisibility( const std::string &strPath, bool bVisible )
{
	return SetAbsolutePathVisibility( FileToPath( strPath ), bVisible );
}

CFilesystem _Filesystem;
