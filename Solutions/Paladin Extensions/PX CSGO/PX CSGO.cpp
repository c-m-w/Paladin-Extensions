/// PX CSGO.cpp

#define PX_ENTRY_AS_DLL

// Creating threads with our manual mapping thread hijacking injector WILL crash.
// Do not upload the debug version to the server or it will crash.
//#ifdef _DEBUG
//#define PX_INSECURE_INITIALIZATION
//#endif

#define PX_INSTANCE_ID L"CSGO"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX CSGO.hpp"

bool PX_API Initialize( )
{
	const auto lgnResult = PX::Net::Login( );
	MessageBox( NULL, std::to_wstring( lgnResult ).c_str( ), L"MEN", MB_OK );
	return( lgnResult == PX::Net::LOGIN_SUCCESS
			|| lgnResult == PX::Net::LOGIN_STAFF_SUCCESS )
		&& PX::Information::InitializeInformation( )
		&& PX::Hooks::InitializeHooks( );
}

void PX_API OnAttach( )
{
	if ( !Initialize( ) )
		MessageBox( NULL, L"setup failed", L"MEN", MB_OK );
}

void PX_API OnDetach( )
{
}
