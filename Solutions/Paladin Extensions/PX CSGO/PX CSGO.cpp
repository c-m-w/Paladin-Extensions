/// PX CSGO.cpp

#define PX_ENTRY_AS_DLL

// Creating threads with our manual mapping thread hijacking injector WILL crash.
// Do not upload the debug version to the server or it will crash.
#ifdef _DEBUG
#define PX_INSECURE_INITIALIZATION
#endif

#define PX_INSTANCE_ID L"CSGO"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX CSGO.hpp"

bool PX_API Initialize( )
{
	const auto lgnResult = PX::Net::Login( );
	return( lgnResult == PX::Net::LOGIN_SUCCESS
				  || lgnResult == PX::Net::LOGIN_STAFF_SUCCESS )
		&& PX::Information::InitializeInformation( )
		&& PX::Hooks::InitializeHooks( );
}

void PX_API OnAttach( )
{
	if ( !Initialize( ) )
		exit( -1 );
}

void PX_API OnDetach( )
{
}
