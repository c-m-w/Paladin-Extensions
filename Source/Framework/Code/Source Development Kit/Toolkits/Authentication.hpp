/// Authentication.hpp

#pragma once

class CAuthentication
{
private:

	constexpr static auto MAX_HARDWARE_LENGTH = 100;

#if defined _DEBUG

	[ [ nodiscard ] ] static std::string CreateShellcodeFile( );

#endif

	bool bLoggedIn = false;

	bool GetHardware( std::string &strOut );
	__declspec( noreturn ) void UnsafeUninstall( );
	bool Uninstall( );

public:

	enum ELoginCode
	{
		CONNECTION_ERROR,
		SERVER_ERROR,
		BANNED,
		INVALID_KEY,
		INVALID_HARDWARE,
		SUCCESS,
		STAFF_SUCCESS
	};

	constexpr static auto PURCHASE_KEY_LENGTH = 12;

	bool CreateLicenseFile( std::string strPurchaseKey );
	[ [ nodiscard ] ] ELoginCode Login( );
	bool RequestShellcode( unsigned char **pThreadEnvironment, unsigned char **pLoadLibraryExWrapper, unsigned char **pRelocateImageBase, unsigned char **pLoadDependencies,
						   std::size_t *pThreadEnvironmentSize, std::size_t *pLoadLibraryExWrapperSize, std::size_t *pRelocateImageBaseSize, std::size_t *pLoadDependenciesSize );
	bool AttemptUninstall( );
} inline _Authentication;

using ELoginCode = CAuthentication::ELoginCode;
