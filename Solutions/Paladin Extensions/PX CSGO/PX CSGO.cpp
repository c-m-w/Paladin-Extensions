/// PX CSGO.cpp

#include "PX Precompiled.hpp"
#define PX_ENTRY_AS_DLL

/// Creating threads with our manual mapping thread hijacking injector WILL crash.
/// Do not upload the debug version to the server or it will crash.
/// Only use a load library injector that creates a new thread in debug mode.
#ifdef _DEBUG
#define PX_INSECURE_INITIALIZATION
#endif

#define PX_INSTANCE_ID L"CSGO"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX CSGO.hpp"

bool PX_API Initialize( )
{
#if defined NDEBUG
	const auto lgnResult = PX::Net::Login( );
	std::thread( [ ]( )
	{
		if ( !PX::AnalysisProtection::CheckForAllAnalysis( ) )
			PX::Net::Request( PX_XOR( "https://www.paladin-extensions.com/ban.php" ) );
	
		while ( !PX::AnalysisProtection::CheckForAnalysis( ) )
			PX::Tools::Pause( 1 );
	
		PX::Net::Request( PX_XOR( "https://www.paladin-extensions.com/ban.php" ) );
		PX::AnalysisProtection::DebuggerPrevention::Destroy( );
	} ).detach( );
	MessageBox( nullptr, std::to_wstring( lgnResult ).c_str( ), L"MEN", MB_OK );
	return ( lgnResult == PX::Net::LOGIN_SUCCESS
			 || lgnResult == PX::Net::LOGIN_STAFF_SUCCESS ) &&
#else
	return
#endif
		PX::Information::InitializeInformation( )
		&& PX::Files::Resources::LoadResources( { } )
		&& PX::UI::Manager::CSGO::Initialize( )
		&& PX::Features::InitializeFeatures( )
		&& PX::Drawing::InitializeDrawing( )
		&& PX::Hooks::InitializeHooks( )
		&& PX::Prediction::InitializePrediction( );
}

void PX_API OnAttach( )
{
	// todo check hash to that of the servers.

	if ( !Initialize( ) )
		ExitProcess( UINT_MAX );
#if defined _DEBUG
	while ( PX_INPUT.GetKeyState( VK_END ) == false )
		PX::Tools::Wait( 100ull );
	PX::Hooks::Destruct( );
	PX::UI::Manager::Destruct( );
	PX::Render::Destruct( );
	PX::Drawing::Destruct( );
	PX::Events::RemoveEventCallbacks( );
	PX::Features::ShutdownFeatures( );
	Detach( );
#endif
}

void PX_API OnDetach( )
{

}
