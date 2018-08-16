/// PX CSGO.cpp

#define PX_ENTRY_AS_DLL

#define PX_INSTANCE_ID L"CSGO"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX CSGO.hpp"

bool PX_API Initialize( )
{
	return Information::Initialize( )
		&& Hooks::Initialize( );
}

void PX_API OnAttach( )
{
	Initialize( );
	Hooks::hkDirectXDevice->HookIndex( VirtualTableIndicies::uEndScene, Hooks::EndScene );
}

void PX_API OnDetach( )
{
}
