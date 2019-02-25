/// CSGOX.cpp

#include "Precompile.hpp"

#define DLL_ENTRY
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

BOOL OnAttach( )
{
	if ( !SetupFramework( )
		 || !AUTH.CompareHash( ELibrary::CSGOX, image_info_t( GetModuleHandle( "csgo.exe" ) ).GenerateUniqueHash( ) ) )
		return FALSE;

	return TRUE;
}

void OnDetach( )
{
	ShutdownFramework( );
}
