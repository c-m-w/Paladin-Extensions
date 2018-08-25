/// PX Dummy.cpp

#include "PX Dummy.hpp"

void Exit( const std::wstring& wstrExitMessage, const bool bDelete = false )
{
	MessageBox( nullptr, wstrExitMessage.c_str( ), PX_XOR( L"Paladin Extensions: Error Occurred" ), MB_ICONERROR | MB_OK );
	return bDelete ? Delete( ) : exit( -1 );
}

bool bStopMonitoring = false;
std::thread tMonitorDetectionVectors;

void LoadManager( )
{
	auto strDLL = AssembleExtensionInformation( RequestExtension( PX_EXTENSION_MANAGER, false ) );
	const auto zDLL = strDLL.length( );

	const auto pBuffer = VirtualAlloc( nullptr, zDLL + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	memcpy( pBuffer, strDLL.c_str( ), zDLL );
	strDLL.erase( zDLL );

	injection_info_t inj;
	if ( !LoadRawLibrary( pBuffer, &inj ) )
	{
		WipeMemory( pBuffer, zDLL );
		Exit( PX_XOR( L"Local initialization failure. Contact support if this issue persists." ) );
	}
	WipeMemory( pBuffer, zDLL );
	bStopMonitoring = true;
	tMonitorDetectionVectors.join( );
}

//void PX_API UI::Manager::SetLayout( )
//{
//	Example( );
//}

//void PX_API UIExample( )
//{
//	unsigned uDimensions[ 2 ] { 720, 600 };
//	Render::InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
//	UI::Manager::InitializeUI( PX_XOR( "Manager" ) );
//	while ( UI::Manager::Render( ) )
//		Wait( 1 );
//}

void PX_API Manager::DrawOther( )
{ }

void PX_API OnLaunch( )
{
	//tMonitorDetectionVectors = std::thread( [ & ]( )
	//{
	//	while ( !bStopMonitoring )
	//		sys::TerminateProcess( GetProcessID( PX_XOR( L"Steam.exe" ) ) );
	//} );

	if ( !FileWrite( PX_APPDATA + PX_XOR( L"data.px" ), GetExecutableDirectory( ), false ) )
		return;

#if defined NDEBUG
	if ( IsDebuggerPresent( ) )
		Delete( );

	MessageBox( nullptr, PX_XOR( L"The Manager setup will begin once you click OK.\n"
								 "Please wait up to 60 seconds for it to complete before the window appears.\n"
								 "Contact support if a window doesn't appear." ), PX_XOR( L"Paladin Extensions: Notice" ), MB_ICONINFORMATION | MB_OK );
#endif
	const auto iLoginStatus = Login( );

#if defined NDEBUG
	PX_DEF bDelete = true;
#else
	PX_DEF bDelete = false;
#endif
	switch ( iLoginStatus )
	{
		case LOGIN_INVALID_LICENSE_FILE:
			Exit( PX_XOR( L"Your license file is invalid and cannot be recovered. Contact support if this issue persists." ), bDelete );
		case LOGIN_CONNECTION_FAILURE:
			Exit( PX_XOR( L"A connection cannot be established with https://www.paladin.rip currently. Please try again later. Contact support if this issue persists." ) );
		case LOGIN_INVALID_HASH:
			Exit( PX_XOR( L"Your client is outdated. Please download the updated version at https://www.paladin.rip/extensions/1/." ), bDelete );
		case LOGIN_BANNED:
			Exit( PX_XOR( L"You are banned and may not use Paladin Extensions software. Email support@paladin.rip if you believe this to be an error." ), bDelete );
		default:
			break;
	}

	LoadManager( );

	while ( true )
		Wait( 1 );
}
