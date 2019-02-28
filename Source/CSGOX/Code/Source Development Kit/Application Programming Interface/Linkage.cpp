/// Linkage.cpp

#include "Precompile.hpp"

#include "../../CSGOX.hpp"
#include "../Toolkits/Features/Features Context.hpp"

bool Linkage::SetupLinkage( )
{
	// todo: get data from server and assign it here

	for ( auto z = 0; z < Interfaces::INTERFACES_MAX; z++ )
		Interfaces::_InterfacesContext[ z ].strPattern = ENC( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ),
		Interfaces::_InterfacesContext[ z ].enumModule = Modules::D3D9;

	for ( auto z = 0u; z < Indices::INDICES_MAX; z++ )
		Indices::pIndices[ z ].get() = 0u;

	for ( auto z = 0u; z < Offsets::OFFSETS_MAX; z++ )
		Offsets::pOffsets[ z ].get() = 0;

	return Modules::LinkModules( )
		&& Interfaces::LinkInterfaces( )
		&& Hooks::SetupHooks( );
}

void Linkage::RemoveLinkage( )
{
	Hooks::DestroyHooks( );
}

bool Linkage::Modules::LinkModules( )
{
	for ( auto z = 0u; z < MODULES_MAX; z++ )
		if ( nullptr == (  hBases[ z ].get( ) = GetModuleHandle( szModuleNames[ z ] ) ) )
			return LOG( ERROR, APPLICATION, "Couldn't create get module base of %s.", szModuleNames[ z ] ), false;

	return true;
}

bool Linkage::Interfaces::LinkInterfaces( )
{
	for ( std::size_t z = Modules::INTERFACEABLE_MODULES; z < Modules::MODULES_MAX; z++ )
		if ( nullptr == ( fnCreateInterface[ z ] = reinterpret_cast< CreateInterfaceFn >( GetProcAddress( Modules::hBases[ z ], ENC( "CreateInterface" ) ) ) ) )
			return LOG( ERROR, APPLICATION, "Couldn't create get CreateInterface in %s.", Modules::szModuleNames[ z ] ), false;

	for ( auto z = 0u; z < INTERFACES_MAX; z++ )
		MEM.AddPattern( Modules::hBases[ int( _InterfacesContext[ z ].enumModule ) ],
						CMemoryManager::pattern_t ( _InterfacesContext[ z ].strPattern, reinterpret_cast<void**>(&pInterfaces[ z ]), 0 ) );

	MEM.FindPatterns( );
	return true;
}

bool Linkage::Hooks::SetupHooks( )
{
	return hkDirectXDevice.Attach( nullptr );
}

void Linkage::Hooks::DestroyHooks( )
{
	hkDirectXDevice.Detach( );
}
