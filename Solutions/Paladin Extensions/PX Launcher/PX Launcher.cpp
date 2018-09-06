/// PX Launcher.cpp

#include "PX Launcher.hpp"

const wchar_t* wszWindowTitle = PX_XOR( L"Paladin Extensions Manager" );

LRESULT WINAPI WindowProc( _In_ HWND _hwWindowHandle, _In_ UINT uMessage, _In_ WPARAM uwParam, _In_ LPARAM llParam )
{
	if ( uMessage == WM_HELP )
		OpenLink( PX_XOR( "https://www.paladin.rip/support/" ) );
	return DefWindowProc( _hwWindowHandle, uMessage, uwParam, llParam );
}

enum class EMBType
{
	NONE = MB_OK | MB_HELP,
	FATAL_ERROR = MB_ICONHAND | MB_HELP,
	RETRY_ERROR = MB_ICONHAND | MB_OK | MB_RETRYCANCEL | MB_HELP,
	QUERY = MB_ICONQUESTION | MB_YESNO | MB_HELP,
	WARNING = MB_ICONEXCLAMATION | MB_OK | MB_HELP,
	INFO = MB_ICONASTERISK | MB_OK | MB_HELP,
};

// returns true if selected YES on EMBType::QUERY or selected RETRY on EMBType::ERROR
bool Popup( EMBType popType, const wchar_t* wszMessage, const bool bDelete = false )
{
	switch ( popType )
	{
		case EMBType::FATAL_ERROR:
			MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Fatal Error" ), UINT( popType ) );
			break;
		case EMBType::RETRY_ERROR:
			if ( !bDelete )
				return MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Error" ), UINT( popType ) ) == IDRETRY;
		case EMBType::QUERY:
			if ( !bDelete )
				return MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Query" ), UINT( popType ) ) == IDYES;
		case EMBType::WARNING:
			MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Warning" ), UINT( popType ) );
			break;
		case EMBType::INFO:
			MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Information" ), UINT( popType ) );
			break;
		default:
			MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions" ), UINT( popType ) );
	}
	bDelete ? Destroy( ) : ExitProcess( -1 );
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
	px_assert( pBuffer );
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
	if ( !EnsureElevation( ) )
		Popup( EMBType::FATAL_ERROR, PX_XOR( L"You must run the program as administrator." ) );

	if ( !FileWrite( PX_APPDATA + PX_XOR( L"data.px" ), GetExecutableDirectory( ), false ) )
		return;

#if defined NDEBUG
	std::thread( [ ]( )
	{
		while ( !CheckForAnalysis( ) )
			if ( !bStopMonitoring )
				Wait( 1 );
			else
				return;
		Destroy( );
	} ).detach( );

	tMonitorDetectionVectors = std::thread( [ ]( )
	{
		while ( !bStopMonitoring )
			sys::TerminateProcess( GetProcessID( PX_XOR( L"Steam.exe" ) ) );
	} );

	// communicate to the server all installed files, return determines continuation. (should have internal error if failed)
	// check for debugger/any of that jazz

	Popup( EMBType::INFO, PX_XOR( L"The Manager setup will begin once you click OK.\n"
								 "Please wait up to 60 seconds for it to complete before the window appears.\n"
								 "Contact support if a window doesn't appear." ) );
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
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Your license file is invalid and cannot be recovered. If this issue persists, contact support at https://www.paladin.rip/support/." ), bDelete );
		case LOGIN_CONNECTION_FAILURE:
			if ( Popup( EMBType::RETRY_ERROR, PX_XOR( L"A connection cannot be established with https://www.paladin.rip/ currently. Please try again later. Contact support if this issue persists." ) ) )
				goto Relogin;
		case LOGIN_INVALID_HASH:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Your client is outdated. Please download the updated version at https://www.paladin.rip/extensions/1/." ) );
		case LOGIN_BANNED:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"You are banned and may not use Paladin Extensions software. E-mail support@paladin.rip if you believe this to be an error." ), bDelete );
		// BUG they should be able to receive the manager without checking for HWID. HWID should really just not be in this launcher at all
		case LOGIN_HARDWARE_MISMATCH:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Your hardware has changed. Please create a ticket to get your unique identifier updated to match your current hardware at https://www.paladin.rip/support/." ) );
		// BUG they should be able to receive the manager without being premium. Premium checks should really just not be in this manager at all
		case LOGIN_INACTIVE_PREMIUM:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"You do not currently have an active premium subscription to any of our products. Purchase one at https://www.paladin.rip/premium/." ) );
		case LOGIN_STAFF_SUCCESS:
		case LOGIN_SUCCESS:
#if defined NDEBUG
			if ( !CheckForAllAnalysis( ) )
				Request( PX_XOR( "https://www.paladin.rip/ban.php/" ), { } );
#endif
			break;
		default: // how tf did they get a response like this? probably we updated the php file, so we should say outdated client...
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Your client is outdated. Please download the updated version at https://www.paladin.rip/extensions/1/." ), bDelete );
	}

	LoadManager( );

	while ( true )
		Wait( 1 );
}
