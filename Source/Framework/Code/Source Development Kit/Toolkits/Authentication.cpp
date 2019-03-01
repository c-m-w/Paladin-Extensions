/// Authentication.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

bool CAuthentication::GetHardware( std::string &strOut )
{
	std::string strHardware[ ESystemInformation::SYS_MAX ];
	SI.AddDeviceToQueue( device_info_t( &strHardware[ ESystemInformation::SYS_CPU ], ENC( L"Win32_Processor" ) ) );
	SI.AddDeviceToQueue( device_info_t( &strHardware[ ESystemInformation::SYS_GPU ], ENC( L"CIM_PCVideoController" ) ) );
	SI.AddDeviceToQueue( device_info_t( &strHardware[ ESystemInformation::SYS_DISPLAY ], ENC( L"Win32_DesktopMonitor" ) ) );
	SI.AddDeviceToQueue( device_info_t( &strHardware[ ESystemInformation::SYS_PC ], ENC( L"CIM_OperatingSystem" ), ENC( L"CSName" ) ) );
	SI.AddDeviceToQueue( device_info_t( &strHardware[ ESystemInformation::SYS_OS ], ENC( L"CIM_OperatingSystem" ), ENC( L"Caption" ) ) );
	SI.AddDeviceToQueue( device_info_t( &strHardware[ ESystemInformation::SYS_DRIVE ], ENC( L"Win32_DiskDrive" ), ENC( L"SerialNumber" ) ) );
	SI.AddDeviceToQueue( device_info_t( &strHardware[ ESystemInformation::SYS_BOARD ], ENC( L"Win32_BaseBoard" ), ENC( L"Product" ) ) );
	strHardware[ ESystemInformation::SYS_HASH ] = SI.GetHardwareHash( );
	
	if ( !SI.ProcessQueue( ) )
		return false;

	for ( auto &strDevice: strHardware )
		if ( strDevice.length( ) > MAX_HARDWARE_LENGTH )
			strDevice = strDevice.substr( 0, MAX_HARDWARE_LENGTH );

	return ( strOut = nlohmann::json
	{
		{ ENC( "cpu" ), strHardware[ ESystemInformation::SYS_CPU ] },
		{ ENC( "gpu" ), strHardware[ ESystemInformation::SYS_GPU ] },
		{ ENC( "display" ), strHardware[ ESystemInformation::SYS_DISPLAY ] },
		{ ENC( "pc" ), strHardware[ ESystemInformation::SYS_PC ] },
		{ ENC( "os" ), strHardware[ ESystemInformation::SYS_OS ] },
		{ ENC( "drive" ), strHardware[ ESystemInformation::SYS_DRIVE ] },
		{ ENC( "board" ), strHardware[ ESystemInformation::SYS_BOARD ] }, 
		{ ENC( "hash" ), strHardware[ ESystemInformation::SYS_HASH ] },
	}.dump( ) ), true;
}

bool CAuthentication::GetPurchaseKey( std::string &strOut )
{
	strOut.clear( );
	_Filesystem.StoreCurrentWorkingDirectory( );
	_Filesystem.ChangeWorkingDirectory( _Filesystem.GetAppdataDirectory( ) );
	const auto bReturn = _Filesystem.ReadFile( _Filesystem.strLicenseFile, strOut, true );
	_Filesystem.RestoreWorkingDirectory( );
	if ( bReturn == false )
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to read purchase key file." ) );

	return bReturn;
}

#if defined _DEBUG

std::string CAuthentication::CreateShellcodeFile( )
{
	const auto fnInsertShellcode = [ ]( nlohmann::json &_Out, unsigned char *pBytes, std::size_t zSize )
	{
		_Out[ CRYPTO.GenerateHash( ENC( "Size" ) ) ] = zSize;
		for ( auto z = 0u; z < zSize; z++ )
			_Out[ CRYPTO.GenerateHash( ENC( "Bytes" ) ) ][ z ] = pBytes[ z ];
	};

	nlohmann::json _Return;
	fnInsertShellcode( _Return[ CRYPTO.GenerateHash( ENC( "ThreadEnvironment" ) ) ], bThreadEnvironment, zThreadEnvironment );
	fnInsertShellcode( _Return[ CRYPTO.GenerateHash( ENC( "LoadLibraryExWrapper" ) ) ], bLoadLibraryExWrapper, zLoadLibraryExWrapper );
	fnInsertShellcode( _Return[ CRYPTO.GenerateHash( ENC( "RelocateImageBase" ) ) ], bRelocateImageBase, zRelocateImageBase );
	fnInsertShellcode( _Return[ CRYPTO.GenerateHash( ENC( "LoadDependencies" ) ) ], bLoadDependencies, zLoadDependencies );
	fnInsertShellcode( _Return[ CRYPTO.GenerateHash( ENC( "TrampolineStub" ) ) ], bTrampolineStub, zTrampolineStub );

	return _Return.dump( 4 );
}

std::string CAuthentication::CreateDataFile( )
{
	nlohmann::json _Return;

	// Creators and up (1703+)
	_Return[ CRYPTO.GenerateHash( ENC( "Newest Insert Inverted Function Table Pattern" ) ) ]			= strNewestInsertInvertedFunctionTable;
	_Return[ CRYPTO.GenerateHash( ENC( "Newest Insert Inverted Function Table Offset" ) ) ]				= ptrNewestInsertInvertedFunctionTable;
	_Return[ CRYPTO.GenerateHash( ENC( "Newest Inverted Function Table Pattern" ) ) ]					= strNewestInvertedFunctionTable;
	_Return[ CRYPTO.GenerateHash( ENC( "Newest Inverted Function Table Offset" ) ) ]					= ptrNewestInvertedFunctionTable;

	// Creators only (1703)
	_Return[ CRYPTO.GenerateHash( ENC( "Backup Insert Inverted Function Table Pattern" ) ) ]			= strBackupInsertInvertedFunctionTable;
	_Return[ CRYPTO.GenerateHash( ENC( "Backup Insert Inverted Function Table Offset" ) ) ]				= ptrBackupInsertInvertedFunctionTable;
	_Return[ CRYPTO.GenerateHash( ENC( "Backup Inverted Function Table Offset" ) ) ]					= ptrBackupInvertedFunctionTable;

	// Below creators and other Windows versions other than 10 (1703-)
	_Return[ CRYPTO.GenerateHash( ENC( "Resort Insert Inverted Function Table Pattern" ) ) ]			= strResortInsertInvertedFunctionTable;
	_Return[ CRYPTO.GenerateHash( ENC( "Resort Insert Inverted Function Table Offset" ) ) ]				= ptrResortInsertInvertedFunctionTable;
	_Return[ CRYPTO.GenerateHash( ENC( "Resort Windows 10 Inverted Function Table Offset" ) ) ]			= ptrResortWindows10InvertedFunctionTable;
	_Return[ CRYPTO.GenerateHash( ENC( "Resort Previous Windows Inverted Function Table Offset" ) ) ]	= ptrResortPreviousWindowsInvertedFunctionTable;

	return _Return.dump( 4 );
}

std::string CAuthentication::CreateHashFile( )
{
	nlohmann::json _HashFile;

	for ( auto i = 0; i < int( MAX_LIBRARY ); i++ )
		_HashFile[ CRYPTO.GenerateHash( std::to_string( i ) ) ] = strExecutableHashes[ i ];

	return _HashFile.dump( 4 );
}

#endif

bool CAuthentication::CreateLicenseFile( std::string strPurchaseKey )
{
	std::transform( strPurchaseKey.begin( ), strPurchaseKey.end( ), strPurchaseKey.begin( ), toupper );

	_Filesystem.StoreCurrentWorkingDirectory( );
	_Filesystem.ChangeWorkingDirectory( _Filesystem.GetAppdataDirectory( ) );
	const auto bReturn = _Filesystem.WriteFile( _Filesystem.strLicenseFile, strPurchaseKey, true );
	_Filesystem.RestoreWorkingDirectory( );
	return bReturn;
}

bool CAuthentication::Ban( const std::string &strReason )
{
	const auto fnBan = [ & ]( ) -> bool
	{
		std::string strPurchaseKey { };

		if ( !GetPurchaseKey( strPurchaseKey ) )
			return false;

		std::vector< std::string > vecProcesses { };
		if ( !SI.GetProcesses( vecProcesses ) )
			return false;

		std::string strProcessList {  };
		for ( auto &strProcess: vecProcesses )
		{
			if ( !strProcessList.empty( ) )
				strProcessList += '\n';

			strProcessList += strProcess;
		}

		std::string strPrograms { };
		if ( !SI.GetProgramList( strPrograms ) )
			return false;

		std::string strOpenWindows { };
		for ( auto &strWindow: SI.GetOpenWindowNames( ) )
		{
			if ( !strOpenWindows.empty( ) )
				strOpenWindows += '\n';

			strOpenWindows += strWindow;
		}

		std::string strResponse { };
		NET.AddPostData( EPostData::PURCHASE_KEY, strPurchaseKey );
		NET.AddPostData( EPostData::BAN_REASON, strReason );
		NET.AddPostData( EPostData::PROCESS_LIST, strProcessList );
		NET.AddPostData( EPostData::INSTALLED_PROGRAMS, strPrograms );
		NET.AddPostData( EPostData::OPEN_WINDOWS, strOpenWindows );
		return NET.Request( EAction::BAN, strResponse );
	};

	return fnBan( );

}

ELoginCode CAuthentication::Login( )
{
	std::string strPurchaseKey { }, strHardware { }, strResponse { }, strDecryptedResponse { };

	if ( !GetPurchaseKey( strPurchaseKey ) )
		return INVALID_KEY;

	if ( !GetHardware( strHardware ) )
		return CONNECTION_ERROR;

	NET.AddPostData( EPostData::PURCHASE_KEY, strPurchaseKey );
	NET.AddPostData( EPostData::HARDWARE, strHardware );
	if ( !NET.Request( EAction::LOGIN, strResponse ) 
		 || !CRYPTO.Decrypt( strResponse, strDecryptedResponse ) )
		return CONNECTION_ERROR;

	ELoginCode _Return;
	try
	{
		auto jsResponse = nlohmann::json::parse( strDecryptedResponse );
		const auto strBuffer = jsResponse[ ENC( "Exit Code" ) ].get< std::string >( );
		_Return = ELoginCode( std::stoi( strBuffer ) );
		bLoggedIn = _Return == SUCCESS || _Return == STAFF_SUCCESS;
	}
	catch( nlohmann::json::parse_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to parse response from login. Message: %s." ), e.what( ) );
		return SERVER_ERROR;
	}
	catch( nlohmann::json::type_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to obtain string value of the exit code. Message: %s." ), e.what( ) );
		return SERVER_ERROR;
	}
	catch( std::invalid_argument &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to convert string login code to an integer. Message: %s." ), e.what( ) );
		return SERVER_ERROR;
	}
	catch( std::out_of_range &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to convert string login code to an integer. Message: %s." ), e.what( ) );
		return SERVER_ERROR;
	}

	_Log.Log( EPrefix::INFO, ELocation::AUTHENTICATION, ENC( "Received login code of %i." ), _Return );
	return _Return;
}

bool CAuthentication::RequestData( std::string *pNewestInsertInvertedFunctionTable, std::ptrdiff_t *pNewestInsertInvertedFunctionTableOffset, 
								   std::string *pNewestInvertedFunctionTable, std::ptrdiff_t *pNewestInvertedFunctionTableOffset, 
								   std::string *pBackupInsertInvertedFunctionTable, std::ptrdiff_t *pBackupInsertInvertedFunctionTableOffset, 
								   std::ptrdiff_t *pBackupInvertedFunctionTableOffset, std::string *pResortInsertInvertedFunctionTable,
								   std::ptrdiff_t *pResortInsertInvertedFunctionTableOffset, std::ptrdiff_t *pResortWindows10InvertedFunctionTableOffset, 
								   std::ptrdiff_t *pResortPreviousWindowsInvertedFunctionTableOffset )
{
	if ( !bLoggedIn )
		return _Log.Log( EPrefix::WARNING, ELocation::AUTHENTICATION, ENC( "Calling RequestData without loggin in first." ) ), false;

	std::string strResponse { }, strDecryptedResponse { };
	if ( !NET.Request( EAction::GET_DATA, strResponse )
		 || !CRYPTO.Decrypt( strResponse, strDecryptedResponse ) )
		return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Obtaining shellcode failed." ) ), false;

	try
	{
		auto _Response = nlohmann::json::parse( strDecryptedResponse );
		const auto _Return = ELoginCode( std::stoi( _Response[ ENC( "Exit Code" ) ].get< std::string >( ) ) );

		if ( _Return != SUCCESS && _Return != STAFF_SUCCESS
			 || _Response[ ENC( "Other Data" ) ].get< std::string >( ) == NO_OTHER_DATA )
			return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Shellcode request failed. This may be due to an invalid session from attempted authentication bypass." ) ), false;

		std::string strData { };
		if ( !CRYPTO.Decrypt( _Response[ ENC( "Other Data" ) ].get< std::string >( ), strData ) )
			return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to decrypt shellcode." ) ), false;

		auto _Data = nlohmann::json::parse( strData );

		// Creators and up (1703+)
		*pNewestInsertInvertedFunctionTable					= _Data[ CRYPTO.GenerateHash( ENC( "Newest Insert Inverted Function Table Pattern" ) ) ].get< std::string >( );
		*pNewestInsertInvertedFunctionTableOffset			= _Data[ CRYPTO.GenerateHash( ENC( "Newest Insert Inverted Function Table Offset" ) ) ].get< std::ptrdiff_t >( );
		*pNewestInvertedFunctionTable						= _Data[ CRYPTO.GenerateHash( ENC( "Newest Inverted Function Table Pattern" ) ) ].get< std::string >( );
		*pNewestInvertedFunctionTableOffset					= _Data[ CRYPTO.GenerateHash( ENC( "Newest Inverted Function Table Offset" ) ) ].get< std::ptrdiff_t >( );

		// Creators only (1703)
		*pBackupInsertInvertedFunctionTable					= _Data[ CRYPTO.GenerateHash( ENC( "Backup Insert Inverted Function Table Pattern" ) ) ].get< std::string >( );
		*pBackupInsertInvertedFunctionTableOffset			= _Data[ CRYPTO.GenerateHash( ENC( "Backup Insert Inverted Function Table Offset" ) ) ].get< std::ptrdiff_t >( );
		*pBackupInvertedFunctionTableOffset					= _Data[ CRYPTO.GenerateHash( ENC( "Backup Inverted Function Table Offset" ) ) ].get< std::ptrdiff_t >( );

		// Below creators and other Windows versions other than 10 (1703-)
		*pResortInsertInvertedFunctionTable					= _Data[ CRYPTO.GenerateHash( ENC( "Resort Insert Inverted Function Table Pattern" ) ) ].get< std::string >( );
		*pResortInsertInvertedFunctionTableOffset			= _Data[ CRYPTO.GenerateHash( ENC( "Resort Insert Inverted Function Table Offset" ) ) ].get< std::ptrdiff_t >( );
		*pResortWindows10InvertedFunctionTableOffset		= _Data[ CRYPTO.GenerateHash( ENC( "Resort Windows 10 Inverted Function Table Offset" ) ) ].get< std::ptrdiff_t >( );
		*pResortPreviousWindowsInvertedFunctionTableOffset	= _Data[ CRYPTO.GenerateHash( ENC( "Resort Previous Windows Inverted Function Table Offset" ) ) ].get< std::ptrdiff_t >( );

		return true;
	}
	catch ( nlohmann::json::parse_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to parse response from requesting data. Message: %s." ), e.what( ) );
		return false;
	}
	catch ( nlohmann::json::type_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to access data member. Message: %s." ), e.what( ) );
		return false;
	}
}

bool CAuthentication::RequestShellcode( unsigned char **pThreadEnvironment, unsigned char **pLoadLibraryExWrapper, unsigned char **pRelocateImageBase, unsigned char **pLoadDependencies,
										std::size_t *pThreadEnvironmentSize, std::size_t *pLoadLibraryExWrapperSize, std::size_t *pRelocateImageBaseSize, std::size_t *pLoadDependenciesSize )
{
	if ( !bLoggedIn )
		return _Log.Log( EPrefix::WARNING, ELocation::AUTHENTICATION, ENC( "Calling RequestShellcode without loggin in first." ) ), false;

	std::string strResponse { }, strDecryptedResponse { };
	if ( !NET.Request( EAction::GET_SHELLCODE, strResponse )
		 || !CRYPTO.Decrypt( strResponse, strDecryptedResponse ) )
		return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Obtaining shellcode failed." ) ), false;

	try
	{
		const auto fnLoadShellcode = [ & ]( nlohmann::json _Source, unsigned char **pOut, std::size_t &zSize ) -> bool
		{
			zSize = _Source[ CRYPTO.GenerateHash( ENC( "Size" ) ) ].get< std::size_t >( );
			if ( zSize == 0 )
				return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Invalid shellcode size." ) ), false;

			*pOut = new unsigned char[ zSize ];
			for ( auto z = 0u; z < zSize; z++ )
				( *pOut )[ z ] = _Source[ CRYPTO.GenerateHash( ENC( "Bytes" ) ) ][ z ].get< unsigned char >( );

			return true;
		};

		auto _Response = nlohmann::json::parse( strDecryptedResponse );
		const auto _Return = ELoginCode( std::stoi( _Response[ ENC( "Exit Code" ) ].get< std::string >( ) ) );

		if ( _Return != SUCCESS && _Return != STAFF_SUCCESS
			 || _Response[ ENC( "Other Data" ) ].get< std::string >( ) == NO_OTHER_DATA )
			return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Shellcode request failed. This may be due to an invalid session from attempted authentication bypass." ) ), false;

		std::string strShellcode { };
		if ( !CRYPTO.Decrypt( _Response[ ENC( "Other Data" ) ].get< std::string >( ), strShellcode ) )
			return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to decrypt shellcode." ) ), false;

		auto _Shellcode = nlohmann::json::parse( strShellcode );
		return fnLoadShellcode( _Shellcode[ CRYPTO.GenerateHash( ENC( "ThreadEnvironment" ) ) ], pThreadEnvironment, *pThreadEnvironmentSize )
				&& fnLoadShellcode( _Shellcode[ CRYPTO.GenerateHash( ENC( "LoadLibraryExWrapper" ) ) ], pLoadLibraryExWrapper, *pLoadLibraryExWrapperSize )
				&& fnLoadShellcode( _Shellcode[ CRYPTO.GenerateHash( ENC( "RelocateImageBase" ) ) ], pRelocateImageBase, *pRelocateImageBaseSize )
				&& fnLoadShellcode( _Shellcode[ CRYPTO.GenerateHash( ENC( "LoadDependencies" ) ) ], pLoadDependencies, *pLoadDependenciesSize );
	}
	catch ( nlohmann::json::parse_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to parse response from requesting shellcode. Message: %s." ), e.what( ) );
		return false;
	}
	catch ( nlohmann::json::type_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to access shellcode member. Message: %s." ), e.what( ) );
		return false;
	}
}

bool CAuthentication::RequestLibrary( ELibrary _Library, std::string &strOut )
{
	if ( !bLoggedIn )
		return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Attempting to request a library without logging in first." ) ), false;

	std::string strLibrary { }, strDecryptedLibrary { };

	NET.AddPostData( EPostData::LIBRARY, std::to_string( int( _Library ) ) );
	if ( !NET.Request( EAction::GET_LIBRARY, strLibrary )
		 || !CRYPTO.Decrypt( strLibrary, strDecryptedLibrary ) )
		return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to receive or decrypt library %i." ), _Library ), false;

	try
	{
		auto _Response = nlohmann::json::parse( strDecryptedLibrary );
		const auto _Return = ELoginCode( std::stoi( _Response[ ENC( "Exit Code" ) ].get< std::string >( ) ) );

		if ( _Return != SUCCESS && _Return != STAFF_SUCCESS
			 || _Response[ "Other Data" ].get< std::string >( ) == NO_OTHER_DATA )
			return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Library request failed. This may be due to an invalid session from attempted authentication bypass." ) ), false;

		std::string strData { };
		if ( !CRYPTO.Decrypt( _Response[ ENC( "Other Data" ) ].get< std::string >( ), strData ) )
			return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Failed to decrypt library data." ) ), false;

		auto _Data = nlohmann::json::parse( strData );

		const auto strEncryptedSectionCount = _Data[ CRYPTO.GenerateHash( ENC( "Count" ) ) ].get< std::string >( );
		std::string strSectionCount;

		if ( !CRYPTO.Decrypt( strEncryptedSectionCount, strSectionCount ) )
			return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to parse library information." ) ), false;

		const auto zSectionCount = std::stoi( strSectionCount );

		if ( zSectionCount == NULL )
			return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Numerical library information was invalid." ) ), false;

		std::vector< std::string > vecSections( zSectionCount );
		for ( auto z = 0u; z < zSectionCount; z++ )
		{
			std::string strCurrentIndex { };
			if ( !CRYPTO.Decrypt( _Data[ CRYPTO.GenerateHash( ENC( "Order" ) ) ][ z ].get< std::string >( ), strCurrentIndex ) )
				return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to decrypt index of section %i." ), z ), false;

			const auto iCurrentIndex = std::stoi( strCurrentIndex );

			std::string strDecryptedSection;
			if ( !CRYPTO.Decrypt( _Data[ CRYPTO.GenerateHash( ENC( "Sections" ) ) ][ z ].get< std::string >( ), strDecryptedSection ) )
				return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to decrypt library section." ) ), false;

			vecSections[ iCurrentIndex ] = strDecryptedSection;
		}

		strOut.clear( );

		for ( auto &strSection : vecSections )
			strOut += strSection;

		return !strOut.empty( );
	}
	catch ( nlohmann::json::parse_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to parse response from requesting library. Message: %s." ), e.what( ) );
		return false;
	}
	catch ( nlohmann::json::type_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to access library member. Message: %s." ), e.what( ) );
		return false;
	}
	catch( std::invalid_argument &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Could not convert string to int. Message: %s." ), e.what( ) );
		return false;
	}
	catch ( std::out_of_range &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "String to int value out of range. Message: %s." ), e.what( ) );
		return false;
	}
}

bool CAuthentication::CompareHash( ELibrary _ExecutableHash, const std::string &strCurrent )
{
	if ( !bLoggedIn )
		return _Log.Log( EPrefix::WARNING, ELocation::AUTHENTICATION, ENC( "Calling RequestHash without loggin in first." ) ), false;

#if defined _DEBUG
	return true;
#endif

	std::string strResponse { }, strDecryptedResponse { };
	if ( !NET.Request( EAction::GET_HASHES, strResponse )
		 || !CRYPTO.Decrypt( strResponse, strDecryptedResponse ) )
		return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Obtaining hashes failed." ) ), false;

	try
	{
		auto _Response = nlohmann::json::parse( strDecryptedResponse );
		const auto _Return = ELoginCode( std::stoi( _Response[ ENC( "Exit Code" ) ].get< std::string >( ) ) );

		if ( _Return != SUCCESS && _Return != STAFF_SUCCESS
			 || _Response[ ENC( "Other Data" ) ].get< std::string >( ) == NO_OTHER_DATA )
			return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Hash request failed. This may be due to an invalid session from attempted authentication bypass." ) ), false;

		std::string strHashes { };
		if ( !CRYPTO.Decrypt( _Response[ ENC( "Other Data" ) ].get< std::string >( ), strHashes ) )
			return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to decrypt hashes." ) ), false;

		return strCurrent == nlohmann::json::parse( strHashes )[ CRYPTO.GenerateHash( std::to_string( int( _ExecutableHash ) ) ) ].get< std::string >( );
	}
	catch ( nlohmann::json::parse_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to parse response from requesting hashes. Message: %s." ), e.what( ) );
		return false;
	}
	catch ( nlohmann::json::type_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to access hash member. Message: %s." ), e.what( ) );
		return false;
	}
}

bool CAuthentication::AttemptUninstall( )
{
	return false;	
}

CAuthentication _Authentication;
