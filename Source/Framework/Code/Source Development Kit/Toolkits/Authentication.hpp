/// Authentication.hpp

#pragma once

class CAuthentication
{
private:

	constexpr static auto MAX_HARDWARE_LENGTH = 100;
	inline const static auto NO_OTHER_DATA = ENC( "none" );

	bool bLoggedIn = false;

	bool GetHardware( std::string &strOut );
	__declspec( noreturn ) void UnsafeUninstall( );
	bool Uninstall( );

public:

	enum ERequestCode
	{
		CONNECTION_ERROR,
		SERVER_ERROR,
		BANNED,
		INVALID_KEY,
		INVALID_HARDWARE,
		SUCCESS,
		STAFF_SUCCESS
	};

	enum ELibrary
	{
		CLIENT,
		CSGOX,
		PUBX,
		RSIXX,
		RUSTX
	};

	constexpr static auto PURCHASE_KEY_LENGTH = 12;

#if defined _DEBUG

	[ [ nodiscard ] ] static std::string CreateShellcodeFile( );

#endif

	bool CreateLicenseFile( std::string strPurchaseKey );
	[ [ nodiscard ] ] ERequestCode Login( );
	bool RequestShellcode( unsigned char **pThreadEnvironment, unsigned char **pLoadLibraryExWrapper, unsigned char **pRelocateImageBase, unsigned char **pLoadDependencies,
						   std::size_t *pThreadEnvironmentSize, std::size_t *pLoadLibraryExWrapperSize, std::size_t *pRelocateImageBaseSize, std::size_t *pLoadDependenciesSize );
	bool RequestLibrary( ELibrary _Library, std::string &strOut );
	bool AttemptUninstall( );
} inline _Authentication;

using ELoginCode = CAuthentication::ERequestCode;
using ELibrary = CAuthentication::ELibrary;
