/// Client.cpp

#include "Precompile.hpp"

#define DLL_ENTRY
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

// todo check VMP debug checks and shit

BOOL OnAttach( )
{
	auto x = AUTH.Login( );
	if ( x != ELoginCode::SUCCESS && x != ELoginCode::STAFF_SUCCESS )
	{
		MessageBox( nullptr, "Emergency Error: shut down your computer.", "Contact Support", 0 );
		AUTH.AttemptUninstall( true );
	}
	
	//if ( !AUTH.CompareHash( ELibrary::CSGOX, image_info_t( GetModuleHandle( ENC( "csgo.exe" ) ) ).GenerateUniqueHash( ) ) )
	//	return LOG( ERROR, APPLICATION, ENC( "Invalid hash of headers." ) ), false;

	while ( !MEM.SetProcess( ENC( "csgo.exe" ), PROCESS_ALL_ACCESS ) ) Sleep( 1 );
	
	std::string strCSGOtoManualMap;
	if ( !AUTH.RequestLibrary( ELibrary::CSGOX, strCSGOtoManualMap ) )
		return FALSE;
	if ( !MEM.ManuallyLoadLibraryEx( strCSGOtoManualMap, false, true, true, true ) )
		return FALSE;
	
	return TRUE;
}

void OnDetach( )
{ }
