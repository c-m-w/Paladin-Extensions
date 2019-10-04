/// Client.cpp

#include "Precompile.hpp"

#define DLL_ENTRY
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

// todo check VMP debug checks and shit

BOOL OnAttach( )
{
	MessageBox( nullptr, "rape", "men_rape__", 0 );
	
	if ( !SetupFramework( ) )
		return FALSE;
	
	const auto _LoginCode = AUTH.Login( );
	if ( _LoginCode != ELoginCode::SUCCESS && _LoginCode != ELoginCode::STAFF_SUCCESS )
		AUTH.AttemptUninstall( true );

	VMPAUTH( );
	
	//if ( !AUTH.CompareHash( ELibrary::CSGOX, image_info_t( GetModuleHandle( ENC( "csgo.exe" ) ) ).GenerateUniqueHash( ) ) )
	//	return LOG( ERROR, APPLICATION, ENC( "Invalid hash of headers." ) ), false;

	
	
	while ( !_SystemInformation.IsProcessOpen( ENC( "csgo.exe" ) ) ) Sleep( 1 );

	if ( !MEM.SetProcess( ENC( "csgo.exe" ), PROCESS_ALL_ACCESS ) )
		exit( 0 );
	
	std::string strCSGOtoManualMap;
	if ( !AUTH.RequestLibrary( ELibrary::CSGOX, strCSGOtoManualMap ) )
		return FALSE;
	if ( !MEM.ManuallyLoadLibraryEx( strCSGOtoManualMap, false, true, true, true ) )
		return FALSE;
	
	return TRUE;
}

void OnDetach( )
{ }
