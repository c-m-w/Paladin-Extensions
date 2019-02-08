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
		INVALID_LICENSE,
		LOGIN_SUCCESS,
		LOGIN_STAFF_SUCCESS
	};

	bool LicensePresent( );
	bool CreateLicenseFile( const std::string& strPurchaseKey );
	[ [ nodiscard ] ] ELoginCode Login( );
	bool AttemptUninstall( );
} inline _Authentication;

using ELoginCode = CAuthentication::ELoginCode;
