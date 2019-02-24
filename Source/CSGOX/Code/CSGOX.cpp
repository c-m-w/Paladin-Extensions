/// CSGOX.cpp

#include "Precompile.hpp"

#define DLL_ENTRY
#include "../../Framework/Code/Framework.hpp"

BOOL OnAttach( )
{
	if ( !SetupFramework( ) )
		return FALSE;

	return TRUE;
}

void OnDetach( )
{
	ShutdownFramework( );
}
