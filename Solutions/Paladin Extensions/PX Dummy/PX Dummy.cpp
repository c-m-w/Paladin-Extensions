/// PX Dummy.cpp

#include "PX Dummy.hpp"

using namespace PX;
using namespace Types;
using namespace Files;

void PX_API OnLaunch( )
{
	{
		auto bExtraPageCreationGuard = new byte_t[ PX_PAGE * 2 ];
		delete[ ] bExtraPageCreationGuard;
	}

	const auto pDLL = fopen( R"(C:\Users\bhopfu1\Desktop\Messagebox.dll)", "rb" );
	
	if ( !pDLL )
		return;

	fseek( pDLL, 0, SEEK_END );
	const auto lSize = ftell( pDLL );
	rewind( pDLL );
	const auto pBuffer = VirtualAlloc( nullptr, lSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	fread( pBuffer, 1, lSize, pDLL );
	
	if ( !lSize && !pBuffer )
		return;
	
	sys::injection_info_t inj { };
	Inject( pBuffer, GetCurrentExecutableName( ), &inj );

	Wait( 5000 );

	// Cryptography::Initialize( );
	// Net::InitializeConnection( );
}
