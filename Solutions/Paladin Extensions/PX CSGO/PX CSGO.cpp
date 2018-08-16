/// PX CSGO.cpp

#define PX_ENTRY_AS_DLL
#define PX_INSECURE_INITIALIZATION

#define PX_INSTANCE_ID L"CSGO"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX CSGO.hpp"

bool PX_API Initialize( )
{
	const auto lgnResult = Net::Login( );
	return ( lgnResult == Net::LOGIN_SUCCESS
			 || lgnResult == Net::LOGIN_STAFF_SUCCESS )
		&& Information::Initialize( )
		&& Hooks::Initialize( );
}

void PX_API OnAttach( )
{
	if ( !Initialize( ) )
		exit( -1 );
}

void PX_API OnDetach( )
{
}
