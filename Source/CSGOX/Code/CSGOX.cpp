/// CSGOX.cpp

#include "Precompile.hpp"

#define DLL_ENTRY
#include "../../Framework/Code/Framework.hpp"

void OnAttach( )
{
	if ( !SetupFramework( ) )
		return;

	ShutdownFramework( );
}

void OnDetach( )
{
	
}
