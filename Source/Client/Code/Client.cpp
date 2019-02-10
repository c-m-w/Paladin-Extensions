/// Client.cpp

#include "Precompile.hpp"

#define DLL_ENTRY
#include "../../Framework/Code/Framework.hpp"

void OnAttach( )
{
	MessageBox( nullptr, ENC( "test" ), ENC( "test" ), 0 );
}

void OnDetach( )
{ }
