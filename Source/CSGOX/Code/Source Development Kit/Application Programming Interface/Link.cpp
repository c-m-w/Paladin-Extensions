/// Link.cpp

#include "Precompile.hpp"

#include "../../CSGOX.hpp"


bool CLink::Initialize( )
{
	for ( auto z = 0u; z < MODULES_MAX; z++ )
		if ( nullptr == ( fnCreateInterface[ z ] = reinterpret_cast< CreateInterfaceFn >( GetProcAddress( hBases[ z ] = GetModuleHandle( szModuleNames[ z ] ), ENC( "CreateInterface" ) ) ) ) )
			return LOG( ERROR, APPLICATION, "Couldn't create interfaces or get module bases." ), false;


	for ( auto z = 0; z < INTERFACES_MAX; z++ )
		_InterfacesContext[ z ].strPattern = ENC( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ),
		_InterfacesContext[ z ].enumModule = SHADERAPIDX9;

	for ( auto z = 0u; z < INTERFACES_MAX; z++ )
		MEM.AddPattern( hBases[ int( _InterfacesContext[ z ].enumModule ) ],
						{ _InterfacesContext[ z ].strPattern, &pInterfaces[ z ], 0 } );

	if ( !hkDirectXDevice.Attach( pDevice ) )
		;

	return true;
}

void CLink::Uninitialize( )
{
	hkDirectXDevice.Detach( );
}

HRESULT CLink::BeginScene( IDirect3DDevice9* pThis )
{
	MessageBox( 0, 0, 0, 0 );
}
