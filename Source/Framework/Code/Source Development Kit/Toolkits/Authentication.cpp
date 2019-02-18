/// Authentication.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

#if defined _DEBUG

std::string CAuthentication::CreateShellcodeFile( )
{
	const auto fnInsertShellcode = [ ]( nlohmann::json &_Out, unsigned char *pBytes, std::size_t zSize )
	{
		_Out[ ENC( "Size" ) ] = zSize;
		for ( auto z = 0u; z < zSize; z++ )
			_Out[ ENC( "Bytes" ) ][ z ] = pBytes[ z ];
	};

	nlohmann::json _Return;
	fnInsertShellcode( _Return[ ENC( "ThreadEnvironment" ) ], bThreadEnvironment, zThreadEnvironment );
	fnInsertShellcode( _Return[ ENC( "LoadLibraryExWrapper" ) ], bLoadLibraryExWrapper, zLoadLibraryExWrapper );
	fnInsertShellcode( _Return[ ENC( "RelocateImageBase" ) ], bRelocateImageBase, zRelocateImageBase );
	fnInsertShellcode( _Return[ ENC( "LoadDependencies" ) ], bLoadDependencies, zLoadDependencies );

	return _Return.dump( 4 );
}

#endif

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
		{ ENC( "board" ), strHardware[ ESystemInformation::SYS_BOARD ] }
	}.dump( ) ), true;
}

bool CAuthentication::CreateLicenseFile( std::string strPurchaseKey )
{
	std::transform( strPurchaseKey.begin( ), strPurchaseKey.end( ), strPurchaseKey.begin( ), toupper );

	_Filesystem.StoreCurrentWorkingDirectory( );
	_Filesystem.ChangeWorkingDirectory( _Filesystem.GetAppdataDirectory( ) );
	const auto bReturn = _Filesystem.WriteFile( _Filesystem.strLicenseFile, strPurchaseKey, true );
	_Filesystem.RestoreWorkingDirectory( );
	return bReturn;
}

ELoginCode CAuthentication::Login( )
{
	std::string strPurchaseKey { }, strHardware { }, strResponse { }, strDecryptedResponse { };

	_Filesystem.StoreCurrentWorkingDirectory( );
	_Filesystem.ChangeWorkingDirectory( _Filesystem.GetAppdataDirectory( ) );
	if ( !_Filesystem.ReadFile( _Filesystem.strLicenseFile, strPurchaseKey, true ) )
		return _Filesystem.RestoreWorkingDirectory( ), INVALID_KEY;

	if ( !GetHardware( strHardware ) )
		return _Filesystem.RestoreWorkingDirectory( ), CONNECTION_ERROR;

	NET.AddPostData( EPostData::PURCHASE_KEY, strPurchaseKey );
	NET.AddPostData( EPostData::HARDWARE, strHardware );
	if ( !NET.Request( EAction::LOGIN, strResponse ) 
		 || !CRYPTO.Decrypt( strResponse, strDecryptedResponse ) )
		return _Filesystem.RestoreWorkingDirectory( ), CONNECTION_ERROR;

	ELoginCode _Return;
	try
	{
		auto jsResponse = nlohmann::json::parse( strDecryptedResponse );
		const auto strBuffer = jsResponse[ "Exit Code" ].get< std::string >( );
		_Return = ELoginCode( std::stoi( strBuffer ) );
	}
	catch( nlohmann::json::parse_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to parse response from login. Message: %s." ), e.what( ) );
		return _Filesystem.RestoreWorkingDirectory( ), SERVER_ERROR;
	}
	catch( nlohmann::json::type_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to obtain string value of the exit code. Message: %s." ), e.what( ) );
		return _Filesystem.RestoreWorkingDirectory( ), SERVER_ERROR;
	}
	catch( std::invalid_argument &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to convert string login code to an integer. Message: %s." ), e.what( ) );
		return _Filesystem.RestoreWorkingDirectory( ), SERVER_ERROR;
	}
	catch( std::out_of_range &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Unable to convert string login code to an integer. Message: %s." ), e.what( ) );
		return _Filesystem.RestoreWorkingDirectory( ), SERVER_ERROR;
	}

	_Log.Log( EPrefix::INFO, ELocation::AUTHENTICATION, ENC( "Received login code of %i." ), _Return );
	return _Filesystem.RestoreWorkingDirectory( ), _Return;
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
		const auto fnLoadShellcode = [ & ]( nlohmann::json _Source, unsigned char *pOut, std::size_t &zSize ) -> bool
		{
			zSize = _Source[ ENC( "Size" ) ].get< std::size_t >( );
			if ( zSize == 0 )
				return _Log.Log( EPrefix::ERROR, ELocation::AUTHENTICATION, ENC( "Invalid shellcode size." ) ), false;

			pOut = new unsigned char[ zSize ];
			for ( auto z = 0u; z < zSize; z++ )
				pOut[ z ] = _Source[ ENC( "Bytes" ) ][ z ].get< unsigned char >( );

			return true;
		};

		auto _Shellcode = nlohmann::json::parse( strDecryptedResponse );
		return fnLoadShellcode( _Shellcode[ ENC( "ThreadEnvironment" ) ], *pThreadEnvironment, *pThreadEnvironmentSize )
				&& fnLoadShellcode( _Shellcode[ ENC( "LoadLibraryExWrapper" ) ], *pLoadLibraryExWrapper, *pLoadLibraryExWrapperSize )
				&& fnLoadShellcode( _Shellcode[ ENC( "RelocateImageBase" ) ], *pRelocateImageBase, *pRelocateImageBaseSize )
				&& fnLoadShellcode( _Shellcode[ ENC( "LoadDependencies" ) ], *pLoadDependencies, *pLoadDependenciesSize );
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

bool CAuthentication::AttemptUninstall( )
{
	return false;	
}
