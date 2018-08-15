/// PX Dummy.cpp

#include "PX Dummy.hpp"

using namespace PX;
using namespace Types;
using namespace Files;
using namespace Net;

void Exit( const std::wstring& wstrExitMessage, bool bDelete = false )
{
	MessageBox( nullptr, wstrExitMessage.c_str( ), PX_XOR( L"Paladin Extensions: Error Occurred" ), MB_ICONERROR | MB_OK );
	bDelete ? sys::Delete( ) : exit( -1 );
}

void LoadManager( )
{
	auto strDLL = RequestExtensionInformation( PX_EXTENSION_MANAGER );
	const auto zDLL = strDLL.length( );

	const auto pBuffer = VirtualAlloc( nullptr, zDLL + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	memcpy( pBuffer, strDLL.c_str( ), zDLL );
	strDLL.erase( zDLL );

	sys::injection_info_t inj;
	if ( !LoadRawLibrary( pBuffer, &inj ) )
	{
		sys::WipeMemory( pBuffer, zDLL );
		Exit( PX_XOR( L"Local initialization failure. Contact support if this issue persists." ) );
	}
	sys::WipeMemory( pBuffer, zDLL );
}

using namespace UI::Widgets;

char szInputbox[ 32 ] { };

void PX_API UI::Manager::SetLayout( )
{
	Example( );
}

void PX_API UIExample( )
{
	unsigned uDimensions[ 2 ] { 720, 600 };
	Render::InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
	UI::Manager::Initialize( PX_XOR( "Manager" ) );
	while ( UI::Manager::Render( ) )
		Wait( 1 );
}

void PX_API UI::Manager::DrawOther( )
{
}

void PX_API OnLaunch( )
{
	FileWrite( PX_APPDATA + PX_XOR( L"data.px" ), GetExecutablePath( ), false );

#if defined NDEBUG
	if ( IsDebuggerPresent( ) )
		sys::Delete( );
#endif

#if defined RETARDED_MESSAGEBOX_THAT_IS_RETARDED
	MessageBox( nullptr, PX_XOR( L"The Manager setup will begin once you click OK.\n"
								 "Please wait up to 60 seconds for it to complete before the window appears.\n"
								 "Contact support if a window doesn't appear." ), PX_XOR( L"Paladin Extensions: Notice" ), MB_OK );
#endif

	const auto iLoginStatus = Login( );
	switch ( iLoginStatus )
	{
		case LOGIN_INVALID_LICENSE_FILE:
			Exit( PX_XOR( L"Your license file is invalid and cannot be recovered. Contact support if this issue persists." ), true );
		case LOGIN_CONNECTION_FAILURE:
			Exit( PX_XOR( L"A connection cannot be established with https://www.paladin.rip currently. Please try again later. Contact support if this issue persists." ) );
		case LOGIN_INVALID_HASH:
			Exit( PX_XOR( L"Your client is outdated. Please download the updated version at https://www.paladin.rip/extensions/1/." ), true );
		case LOGIN_BANNED:
			Exit( PX_XOR( L"You are banned and may not use Paladin Extensions software. Email support@paladin.rip if you believe this to be an error." ), true );
		default: 
			break;
	}

	LoadManager( );

	while ( true )
		Wait( 1 );
}
