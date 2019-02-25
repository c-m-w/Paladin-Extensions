/// Client.cpp

#include "Precompile.hpp"

#define DLL_ENTRY
#include "../../Framework/Code/Framework.hpp"

BOOL OnAttach( )
{
	auto str = image_info_t( GetModuleHandle( "csgo.exe" ) ).GenerateUniqueHash( );
	MessageBox( nullptr, str.c_str( ), "", 0 );
	return TRUE;
}

void OnDetach( )
{ }
