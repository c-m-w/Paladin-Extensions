/// CSGOX.cpp

#include "Precompile.hpp"

#define ENTRY_SOURCE
#define USE_INTERNAL_NAMESPACES
#define USE_INTERNAL_DEFINITIONS
#include "CSGOX.hpp"

CApplicationWindow *pWindow;
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

	if ( !AUTH.CompareHash( ELibrary::CSGOX, image_info_t( GetModuleHandle( ENC( "csgo.exe" ) ) ).GenerateUniqueHash( ) ) )
		return LOG( ERROR, APPLICATION, ENC( "Invalid hash of headers." ) ), false;

	if ( !Initialize( ) )
		return FALSE;

	pWindow = new CApplicationWindow( FindWindow( nullptr, "Counter-Strike: Global Offensive") );
	
	CJumpAutomation bhop;
	CAutonomousTrigger trigger;
	trigger.AddKeybind( { VK_XBUTTON1, trigger.HOLD_TO_ACTIVATE }, trigger._Keys );
	CFlashUtility noflash;
	noflash.AddKeybind( { key_t( 0ui8 ), noflash.ACTIVE }, noflash._Keys );
	CTriggerAutomation autopistol;
	autopistol.AddKeybind( { VK_LBUTTON, autopistol.HOLD_TO_ACTIVATE }, autopistol._Keys );
	CStaminaBugAutomation jumpbug;
	jumpbug.AddKeybind( { VkKeyScan( 'b' ), jumpbug.HOLD_TO_ACTIVATE }, jumpbug._Keys );

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
	if ( !InitializeMemory( ) || !HOOKS.Setup( ) )
	{
		LOG( ERROR, APPLICATION, ENC( "Unable to initialize." ) );
		return false;
	}

	return true;
}

void Uninitialize( )
{
	HOOKS.Shutdown( );
}
