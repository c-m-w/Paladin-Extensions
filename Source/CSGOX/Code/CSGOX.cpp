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

	CChams cham;
	{

	}
	CGlow glow;
	{
		
	}
	CNotificationSystem notif;
	{
		
	}
	//CAutonomousTrigger trigger;
	//{
	//	trigger.AddKeybind( { VK_XBUTTON2, trigger.HOLD_TO_ACTIVATE }, trigger._Keys );
	//	
	//}
	//CAimAssistance aimbot;
	//{
	//	aimbot.AddKeybind( { VK_LBUTTON, aimbot.HOLD_TO_ACTIVATE }, aimbot._Keys );
	//	aimbot.flFieldOfView = 10.f;
	//}
	CFlashUtility noflash;
	{
		noflash.AddKeybind( { key_t( 0ui8 ), noflash.ACTIVE }, noflash._Keys );
		noflash.flFullFlashMaximum = 0.8f;
		noflash.flPartialFlashMaximum = 0.25f;
	}
	//CTriggerAutomation autopistol;
	//{
	//	autopistol.AddKeybind( { VK_LBUTTON, autopistol.HOLD_TO_ACTIVATE }, autopistol._Keys );
	//}
	//CJumpAutomation bhop;
	//{
	//	bhop.bUseJumpButton = true;
	//	bhop.u8JumpChance = 100ui8;
	//	bhop.u8MaximumExtraJumps = 7ui8;
	//	bhop.flExtraJumpWindow = 0.25f;
	//	bhop.bJumpBeforeHopping = true;
	//	bhop.bJumpAfterHopping = true;
	//}
	//CStaminaBugAutomation jumpbug;
	//{
	//	jumpbug.AddKeybind( { VkKeyScan( 'b' ), jumpbug.HOLD_TO_ACTIVATE }, jumpbug._Keys );
	//	jumpbug.bUseDuckButton = true;
	//	jumpbug.bDisableWhenManuallyDucking = true;
	//}
	CInventoryManager inv;
	{
		
	}
	
	
	
	while ( !_Input.GetKeyState( VK_DELETE ) )
		Pause( 1 );
	
	FreeLibraryAndExitThread( GetModuleHandle( nullptr ), TRUE );
}

void OnDetach( )
{
	Uninitialize( );
	ShutdownFramework( );
}

bool Initialize( )
{
	pWindow = new CApplicationWindow( FindWindow( nullptr, "Counter-Strike: Global Offensive") );

	if ( !DRAW.ChangeTarget( pWindow ) )
		return false;

	_GUI.Setup( );
	static auto test = new CWindow ({ 0, 0, 5, 5 } );
	test->SetTitle( "test" );
	test->ShowIcon();
	_GUI.AddWindow( test);
	
	
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
