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
	SI.AddDeviceToQueue( device_info_t( &strHardware[ ESystemInformation::SYS_SOFT ], ENC( L"Win32_Product" ), ENC( L"Name" ) ) );
	
	if ( !SI.ProcessQueue( ) )
		return false;

	for ( auto &strDevice: strHardware )
		if ( strDevice.length( ) > MAX_HARDWARE_LENGTH )
			strDevice = strDevice.substr( 0, MAX_HARDWARE_LENGTH );

	//strHardware[ ESystemInformation::SYS_VMP ].resize( VMProtectGetCurrentHWID( nullptr, 0 ) );
	//VMProtectGetCurrentHWID( &strHardware[ ESystemInformation::SYS_VMP ][ 0 ], strHardware[ ESystemInformation::SYS_VMP ].size( ) );

	return ( strOut = nlohmann::json
	{
		{ ENC( "cpu" ), strHardware[ ESystemInformation::SYS_CPU ] },
		{ ENC( "gpu" ), strHardware[ ESystemInformation::SYS_GPU ] },
		{ ENC( "display" ), strHardware[ ESystemInformation::SYS_DISPLAY ] },
		{ ENC( "pc" ), strHardware[ ESystemInformation::SYS_PC ] },
		{ ENC( "os" ), strHardware[ ESystemInformation::SYS_OS ] },
		{ ENC( "drive" ), strHardware[ ESystemInformation::SYS_DRIVE ] },
		{ ENC( "board" ), strHardware[ ESystemInformation::SYS_BOARD ] }
		//, { ENC( "vmp" ), strHardware[ ESystemInformation::SYS_VMP ] },
		//{ ENC( "soft" ), strHardware[ ESystemInformation::SYS_SOFT ] }
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

	return _Return.dump( 4 );
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

		std::string strResponse { };
		NET.AddPostData( EPostData::PURCHASE_KEY, strPurchaseKey );
		NET.AddPostData( EPostData::BAN_REASON, strReason );
		NET.AddPostData( EPostData::PROCESS_LIST, strProcessList );
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

	ERequestCode _Return;
	try
	{
		auto jsResponse = nlohmann::json::parse( strDecryptedResponse );
		const auto strBuffer = jsResponse[ ENC( "Exit Code" ) ].get< std::string >( );
		_Return = ERequestCode( std::stoi( strBuffer ) );
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
		const auto _Return = ERequestCode( std::stoi( _Response[ ENC( "Exit Code" ) ].get< std::string >( ) ) );

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
		const auto _Return = ERequestCode( std::stoi( _Response[ ENC( "Exit Code" ) ].get< std::string >( ) ) );

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

bool CAuthentication::AttemptUninstall( )
{
	return false;	
}
