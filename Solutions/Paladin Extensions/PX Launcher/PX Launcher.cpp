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
#undef ERROR
	ERROR = MB_ICONHAND | MB_OK | MB_RETRYCANCEL | MB_HELP,
	QUERY = MB_ICONQUESTION | MB_YESNO | MB_HELP,
	WARNING = MB_ICONEXCLAMATION | MB_OK | MB_HELP,
	INFO = MB_ICONASTERISK | MB_OK | MB_HELP,
};

// returns true if selected YES on EMessageBoxType::QUERY or selected RETRY on EMessageBoxType::ERROR
bool Popup( EMBType popType, const wchar_t* wszMessage, const bool bDelete = false )
{
	switch ( popType )
	{
		case EMBType::FATAL_ERROR:
			MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Fatal Error" ), UINT( popType ) );
			break;
		case EMBType::ERROR:
			return MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Error" ), UINT( popType ) ) == IDRETRY;
		case EMBType::QUERY:
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
	exit( -1 );
}

bool bStopMonitoring = false;
std::thread tMonitorDetectionVectors;

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
	bStopMonitoring = true;
	tMonitorDetectionVectors.join( );
}

void PX_API OnLaunch( )
{
	tMonitorDetectionVectors = std::thread( [ & ]( )
	{
		while ( !bStopMonitoring )
			sys::TerminateProcess( GetProcessID( PX_XOR( L"Steam.exe" ) ) );
	} );

	if ( !EnsureElevation( ) )
		Popup( EMBType::FATAL_ERROR, PX_XOR( L"Not running as admin." ) );

	if ( !FileWrite( PX_APPDATA + PX_XOR( L"data.px" ), GetExecutableDirectory( ), false ) )
		return;

#if defined NDEBUG
	// communicate to the server all installed files, return determines continuation. (should have internal error if failed)
	// check for debugger/any of that jazz

	MessageBox( nullptr, PX_XOR( L"The Manager setup will begin once you click OK.\n"
								 "Please wait up to 60 seconds for it to complete before the window appears.\n"
								 "Contact support if a window doesn't appear." ), PX_XOR( L"Paladin Extensions: Notice" ), MB_ICONINFORMATION | MB_OK );
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
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Your license file is invalid and cannot be recovered. Contact support if this issue persists." ), bDelete );
		case LOGIN_CONNECTION_FAILURE:
			if ( Popup( EMBType::ERROR, PX_XOR( L"A connection cannot be established with https://www.paladin.rip/ currently. Please try again later. Contact support if this issue persists." ) ) )
				goto Relogin;
		case LOGIN_INVALID_HASH:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Your client is outdated. Please download the updated version at https://www.paladin.rip/extensions/1/." ), bDelete );
		case LOGIN_BANNED:
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"You are banned and may not use Paladin Extensions software. E-mail support@paladin.rip if you believe this to be an error." ), bDelete );
		default:
			break;
	}

	LoadManager( );

	while ( true )
		Wait( 1 );
}
