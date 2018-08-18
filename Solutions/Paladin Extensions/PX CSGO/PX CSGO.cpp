/// PX CSGO.cpp

#define PX_ENTRY_AS_DLL

// Creating threads with our manual mapping thread hijacking injector WILL crash.
// Do not upload the debug version to the server or it will crash.
// Only use a load library injector that creates a new thread in debug mode.
#ifdef _DEBUG
#define PX_INSECURE_INITIALIZATION
#endif

#define PX_INSTANCE_ID L"CSGO"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX CSGO.hpp"

bool PX_API Initialize( )
{
	unsigned uDimensions[ 2 ] { 720, 600 };
	const auto lgnResult = PX::Net::Login( );
	MessageBox( nullptr, std::to_wstring( lgnResult ).c_str( ), L"MEN", MB_OK );
	return ( lgnResult == PX::Net::LOGIN_SUCCESS
			 || lgnResult == PX::Net::LOGIN_STAFF_SUCCESS )
		   && PX::Information::InitializeInformation( )
		   && PX::Files::Resources::LoadResources( { } )
		   && PX::Render::InitializeRenderTarget( PX::Information::Interfaces::pDevice, uDimensions )
		   && PX::UI::Manager::InitializeUI( PX_XOR( "CS: GO" ) )
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
