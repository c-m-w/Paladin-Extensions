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
#if defined _DEBUG
	return
#else
	const auto lgnResult = PX::Net::Login( );
	//MessageBox( nullptr, std::to_wstring( lgnResult ).c_str( ), L"MEN", MB_OK );
	return ( lgnResult == PX::Net::LOGIN_SUCCESS
			 || lgnResult == PX::Net::LOGIN_STAFF_SUCCESS ) &&
#endif
		PX::Information::InitializeInformation( )
		&& PX::Files::Resources::LoadResources( { } )
		&& PX::UI::Manager::CSGO::Initialize( )
		&& PX::Features::InitializeFeatures( )
		&& PX::Hooks::InitializeHooks( );
}

void PX_API OnAttach( )
{
	if ( !Initialize( ) )
		exit( -1 );
#if defined _DEBUG
	while ( !PX_INPUT.GetKeyState( VK_DELETE ) )
		PX::Tools::Wait( 1 );
	PX::Hooks::Destruct( );
	PX::UI::Manager::Destruct( );
	PX::Render::Destruct( );
#endif
}

void PX_API OnDetach( )
{
}
