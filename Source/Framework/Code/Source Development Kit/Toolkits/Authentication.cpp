/// Authentication.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

bool CAuthentication::LicensePresent( )
{
	return false;
}

bool CAuthentication::CreateLicenseFile( const std::string &strPurchaseKey )
{
	return false;	
}

ELoginCode CAuthentication::Login( )
{
	return CONNECTION_ERROR;
}

bool CAuthentication::AttemptUninstall( )
{
	return false;	
}
