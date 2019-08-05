/// Memory.cpp

#include "Precompile.hpp"

#define USE_INTERNAL_NAMESPACES
#define USE_INTERNAL_DEFINITIONS
#include "../CSGOX.hpp"

bool CLinkage::Initialize( )
{
	for ( auto i = 0; i < MODULE_MAX; i++ )
	{
		auto &_Module = _Modules[ i ];

		_Module._Module = GetModuleHandle( Linkage::strModules[ i ].c_str( ) );
		if ( !_Module.Valid( ) )
			return LOG( ERROR, APPLICATION, "Unable to obtain information of module %i.", i ), false;
	}

	if ( !MEM.AddPattern( _Client, Linkage::_ClientBaseVersion )
		 || !MEM.AddPattern( _Client, Linkage::_EngineClientVersion )
		 || !MEM.AddPattern( _Client, Linkage::_EngineSoundClientVersion )
		 || !MEM.AddPattern( _Direct3DAPI, Linkage::_DevicePattern )
		 || !MEM.FindPatterns( ) )
		return LOG( ERROR, APPLICATION, "Unable to find patterns." ), false;

	if ( !_Client( Linkage::szClientBaseVersion, &pClientBase )
		 || !_Engine( Linkage::szEngineClientVersion, &pEngineClient ) )
		return LOG( ERROR, APPLICATION, "Unable to retrieve interface(s) from factories." ), false;

	return true;
}

void CLinkage::Uninitialize( )
{ }
