/// PX Launcher.cpp

#include "PX Precompiled.hpp"

#define PX_INSTANCE_ID L"Launcher"

#include "PX Launcher.hpp"

// todo title + windowproc
const wchar_t *wszWindowTitle = PX_XOR( L"Paladin Extensions Manager" );

LRESULT WINAPI WindowProc( _In_ HWND _hwWindowHandle, _In_ UINT uMessage, _In_ WPARAM uwParam, _In_ LPARAM llParam )
{
	if ( uMessage == WM_HELP )
		OpenLink( PX_XOR( "https://www.paladin-extensions.com/support/" ) );
	return DefWindowProc( _hwWindowHandle, uMessage, uwParam, llParam );
}

#if defined NDEBUG
bool bStopMonitoring = false;
std::thread tMonitorDetectionVectors;
#endif

void LoadManager( )
{
	auto strDLL = AssembleExtensionInformation( RequestExtension( PX_EXTENSION_MANAGER, false ) );
	const auto zDLL = strDLL.length( );

	const auto pBuffer = VirtualAlloc( nullptr, zDLL + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	// review should really do a safety check on pBuffer
	memcpy( pBuffer, strDLL.c_str( ), zDLL );
	strDLL.clear( );

	{
		injection_info_t inj;
		if ( !LoadRawLibrary( pBuffer, &inj ) )
		{
			WipeMemory( pBuffer, zDLL );
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Local initialization failure. Contact support if this issue persists." ) );
		}
	}
	WipeMemory( pBuffer, zDLL );
#if defined NDEBUG
	bStopMonitoring = true;
	tMonitorDetectionVectors.join( );
#endif
}

void PX_API OnLaunch( )
{
	// todo check hash to that of the servers.

	if ( !EnsureElevation( ) )
		Popup( EMBType::FATAL_ERROR, PX_XOR( L"You must run the program as administrator." ) );

	if ( !FileWrite( PX_APPDATA + PX_XOR( L"data.px" ), GetExecutableDirectory( ), false ) )
		return;

#if defined NDEBUG
	//std::thread( [ ]( )
	//{
	//	while ( CheckForAnalysis( ) )
	//		if ( !bStopMonitoring )
	//			Pause( 1 );
	//		else
	//			return;
	//
	//	Destroy( );
	//} ).detach( );

	//tMonitorDetectionVectors = std::thread( [ ]( )
	//{
	//	//while ( !bStopMonitoring )
	//		//sys::TerminateProcess( GetProcessID( PX_XOR( L"Steam.exe" ) ) ), sys::TerminateProcess( GetProcessID( PX_XOR( L"csgo.exe" ) ) );
	//} );

	// communicate to the server all installed files, return determines continuation. (should have internal error if failed)
	// check for debugger/any of that jazz

	Popup( EMBType::INFO, PX_XOR( L"The Manager setup will begin once you click OK.\n"
			   "Please wait up to 60 seconds for it to complete before the window appears.\n"
			   "Contact support if a window doesn't appear. [men]" ) );
#endif
Relogin:
	const auto iLoginStatus = Login( );

#if defined NDEBUG
	PX_DEF bDelete = true;
#else
	PX_DEF bDelete = false;
#endif
	switch ( iLoginStatus )
	{
		case LOGIN_INVALID_LICENSE_FILE:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Your license file is invalid and cannot be recovered. If this issue persists, contact support at https://www.paladin-extensions.com/support/." ), bDelete );
		case LOGIN_CONNECTION_FAILURE:
			if ( Popup( EMBType::RETRY_ERROR, PX_XOR( L"A connection cannot be established with https://www.paladin-extensions.com/ currently. Please try again later. Contact support if this issue persists." ) ) )
				goto Relogin;
			ExitProcess( UINT_MAX );
		case LOGIN_INVALID_HASH:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Your client is outdated. Please download the updated version at https://www.paladin-extensions.com/extensions/1/." ) );
		case LOGIN_BANNED:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"You are banned and may not use Paladin Extensions software. E-mail support@paladin-extensions.com if you believe this to be an error." ), bDelete );
			// BUG they should be able to receive the manager without checking for HWID. HWID should really just not be in this launcher at all
		case LOGIN_HARDWARE_MISMATCH:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Your hardware has changed. Please create a ticket to get your unique identifier updated to match your current hardware at https://www.paladin-extensions.com/support/." ) );
			// BUG they should be able to receive the manager without being premium. Premium checks should really just not be in this manager at all
		case LOGIN_INACTIVE_PREMIUM:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"You do not currently have an active premium subscription to any of our products. Purchase one at https://www.paladin-extensions.com/extensions/." ) );
		case LOGIN_STAFF_SUCCESS:
		case LOGIN_SUCCESS:
#if defined NDEBUG
			if ( !CheckForAnalysis( ) )
				Request( PX_XOR( "https://www.paladin-extensions.com/ban.php/" ) );
#endif
			break;
		default: // how tf did they get a response like this? probably we updated the php file, so we should say outdated client...
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Your client is outdated. Please download the updated version at https://www.paladin-extensions.com/extensions/1/." ), bDelete );
	}

	LoadManager( );

	while ( true )
		Pause( 1 );
}
