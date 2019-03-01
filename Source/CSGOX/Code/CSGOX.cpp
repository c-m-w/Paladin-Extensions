/// CSGOX.cpp

#include "Precompile.hpp"

#define ENTRY_SOURCE
#include "CSGOX.hpp"

BOOL OnAttach( )
{
	if ( !SetupFramework( )
		 /*|| !AUTH.CompareHash( ELibrary::CSGOX, image_info_t( GetModuleHandle( "csgo.exe" ) ).GenerateUniqueHash( ) )*/ )
		return FALSE;

	if ( !Linkage::SetupLinkage( ) )
		return FALSE;

	return TRUE;
}

void OnDetach( )
{
	ShutdownFramework( );
}
