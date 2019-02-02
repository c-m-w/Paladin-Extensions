/// Connectivity.hpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

bool CConnectivity::Initialize( )
{
	return curl_global_init( CURL_GLOBAL_ALL ) == CURLE_OK && ( pConnection = curl_easy_init( ) ) != nullptr;
}

void CConnectivity::Shutdown( )
{
	return curl_easy_cleanup( pConnection );
}
