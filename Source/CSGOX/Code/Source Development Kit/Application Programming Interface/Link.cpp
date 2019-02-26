/// Link.cpp

#include "Precompile.hpp"

#include "../../CSGOX.hpp"

bool CLink::Initialize( )
{
	for ( auto z = 0u; z < MODULES_MAX; z++ )
		if ( nullptr == ( fnCreateInterface[ z ] = reinterpret_cast< CreateInterfaceFn >( GetProcAddress( hBases[ z ] = GetModuleHandle( szModuleNames[ z ] ), ENC( "CreateInterface" ) ) ) ) )
			return LOG( ERROR, APPLICATION, "Couldn't create interfaces or get module bases." ), false;

	hkFoo.Attach( pFoo );

	return true;
}

void CLink::Uninitialize( )
{
	hkFoo.Detach( );
}
