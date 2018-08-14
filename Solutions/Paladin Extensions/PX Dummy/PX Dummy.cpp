/// PX Dummy.cpp

#include "PX Dummy.hpp"

using namespace PX;
using namespace Types;
using namespace Files;
using namespace Net;

void Inject( )
{
	const auto strDLL = RequestExtensionInformation( PX_EXTENSION_MANAGER );
	auto pBuffer = VirtualAlloc( nullptr, strDLL.length( ) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	memcpy( pBuffer, strDLL.c_str( ), strDLL.length( ) );

	sys::injection_info_t inj { };
	LocalInject( pBuffer, &inj );
}

void Exit( const std::wstring& wstrExitMessage )
{
	MessageBox( nullptr, wstrExitMessage.c_str( ), PX_XOR( L"Paladin Extensions: Error Occurred" ), MB_ICONERROR | MB_OK );
	exit( -1 );
}

void PX_API OnLaunch( )
{
	const auto iLoginStatus = Login( );
	switch ( iLoginStatus )
	{
		case LOGIN_INVALID_LICENSE_FILE:
			Exit( PX_XOR( L"Your license file is invalid and cannot be recovered. Please create a support ticket." ) );
		case LOGIN_CONNECTION_FAILURE:
			Exit( PX_XOR( L"A connection cannot be established with https://www.paladin.rip currently. Please try again later. Contact support if this issue persists." ) );
		case LOGIN_INVALID_HASH:
			Exit( PX_XOR( L"Your client is outdated. Please download the updated version at https://www.paladin.rip/extensions/1/." ) );
		case LOGIN_BANNED:
			Exit( PX_XOR( L"You are banned and may not use Paladin Extensions software. Contact support if you believe this to be an error." ) );			
	}

	Inject( );
}
