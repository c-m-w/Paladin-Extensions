/// CSGOX.cpp

#include "Precompile.hpp"

#define ENTRY_SOURCE
#define USE_INTERNAL_NAMESPACES
#define USE_INTERNAL_DEFINITIONS
#include "CSGOX.hpp"

bool Initialize( );
void Uninitialize( );

BOOL OnAttach( )
{
	if ( !SetupFramework( ) )
		return FALSE;

	const auto _LoginCode = AUTH.Login( );

	if ( _LoginCode != ELoginCode::SUCCESS
		 && _LoginCode != ELoginCode::STAFF_SUCCESS )
		return FALSE;

	if ( !AUTH.CompareHash( ELibrary::CSGOX, image_info_t( GetModuleHandle( "csgo.exe" ) ).GenerateUniqueHash( ) ) )
		return LOG( ERROR, APPLICATION, "Invalid hash of headers." ), false;

	if ( !Initialize( ) )
		return FALSE;

	while ( true )
		Pause( 1 );

	return TRUE;
}

void OnDetach( )
{
	Uninitialize( );
	ShutdownFramework( );
}

bool Initialize( )
{
	if ( !LINK.Setup( )
		 || !HOOKS.Setup( ) )
	{
		LOG( ERROR, APPLICATION, "Unable to initialize." );
		return false;
	}

	return true;
}


void Uninitialize( )
{
	HOOKS.Shutdown( );
	LINK.Shutdown( );
}
