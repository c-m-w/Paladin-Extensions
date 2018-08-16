/// PX CSGO.cpp

#define PX_ENTRY_AS_DLL
#define PX_INSTANCE_ID L"CSGO"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX CSGO.hpp"

bool PX_API Initialize( )
{
	return PX::Information::InitializeInformation( )
		   && PX::Hooks::InitializeHooks( );
}

void PX_API OnAttach( )
{
	Initialize( );
	PX::Hooks::hkDirectXDevice->HookIndex( PX::VirtualTableIndicies::uEndScene, PX::Hooks::EndScene );
}

void PX_API OnDetach( )
{
}
