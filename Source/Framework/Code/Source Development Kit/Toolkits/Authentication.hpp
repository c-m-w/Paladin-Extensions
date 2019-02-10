/// Authentication.hpp

#pragma once

class CAuthentication
{
private:

	constexpr static auto MAX_HARDWARE_LENGTH = 100;

	bool bLoggedIn = false;

	bool GetHardware( std::string &strOut );
	__declspec( noreturn ) void UnsafeUninstall( );
	bool Uninstall( );

public:

	enum ELoginCode
	{
		CONNECTION_ERROR,
		SERVER_ERROR,
		SERVER_CONNECTION_ERROR,
		BANNED,
		INVALID_KEY,
		INVALID_HARDWARE,
		SUCCESS,
		STAFF_SUCCESS
	};

	constexpr static auto PURCHASE_KEY_LENGTH = 12;

	bool CreateLicenseFile( std::string strPurchaseKey );
	[ [ nodiscard ] ] ELoginCode Login( );
	bool AttemptUninstall( );
} inline _Authentication;

using ELoginCode = CAuthentication::ELoginCode;
