/// Authentication.hpp

#pragma once

class CAuthentication
{
private:

	bool bLoggedIn = false;

	__declspec( noreturn ) void Uninstall( );

public:

	enum ELoginCode
	{
		CONNECTION_ERROR,
		INVALID_LICENSE,
		INVALID_HARDWARE,
		LOGIN_SUCCESS,
		LOGIN_STAFF_SUCCESS
	};

	constexpr static auto PURCHASE_KEY_LENGTH = 12;

	bool LicensePresent( );
	bool CreateLicenseFile( const std::string& strPurchaseKey );
	[ [ nodiscard ] ] ELoginCode Login( );
	bool AttemptUninstall( );
} inline _Authentication;

using ELoginCode = CAuthentication::ELoginCode;
