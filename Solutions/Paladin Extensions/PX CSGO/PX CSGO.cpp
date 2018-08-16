/// PX CSGO.cpp

#define PX_ENTRY_AS_DLL
#define PX_INSTANCE_ID L"CSGO"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX CSGO.hpp"

bool PX_API Initialize( )
{
<<<<<<< HEAD
	const auto lgnResult = Net::Login( );
	return ( lgnResult == Net::LOGIN_SUCCESS
			 || lgnResult == Net::LOGIN_STAFF_SUCCESS )
		&& Information::Initialize( )
		&& Hooks::Initialize( );
=======
	return PX::Information::InitializeInformation( )
		   && PX::Hooks::InitializeHooks( );
>>>>>>> 0d3965065accae6dee106ae23579fd5acd0cb49a
}

void PX_API OnAttach( )
{
<<<<<<< HEAD
	if ( !Initialize( ) )
		exit( -1 );
=======
	Initialize( );
	PX::Hooks::hkDirectXDevice->HookIndex( PX::VirtualTableIndicies::uEndScene, PX::Hooks::EndScene );
>>>>>>> 0d3965065accae6dee106ae23579fd5acd0cb49a
}

void PX_API OnDetach( )
{
}
