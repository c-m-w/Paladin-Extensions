/// Memory.cpp

#include "Precompile.hpp"

#define USE_INTERNAL_NAMESPACES
#define USE_INTERNAL_DEFINITIONS
#include "../CSGOX.hpp"

module_info_t::operator HMODULE( ) const
{
	return _Module;
}

void *module_info_t::operator( )( const char *szInterface ) const
{
	if ( _CreateInterface == nullptr )
		return LOG( WARNING, APPLICATION, "Attempting to call CreateInterface when it was not found." ), nullptr;

	return _CreateInterface( szInterface, nullptr );
}

bool module_info_t::Valid( )
{
	if ( !_Module )
		return false;

	if ( _CreateInterface == nullptr )
		_CreateInterface = decltype( _CreateInterface )( GetProcAddress( _Module, CLinkage::strCreateInterfaceImport.c_str( ) ) );

	return true;
}

bool CLinkage::Initialize( )
{
	for ( auto i = 0; i < MODULE_MAX; i++ )
	{
		auto &_Module = _Modules[ i ];

		_Module._Module = GetModuleHandle( strModules[ i ].c_str( ) );
		if ( !_Module.Valid( ) )
			return LOG( ERROR, APPLICATION, "Unable to obtain information of module %i.", i ), false;
	}

	if ( !MEM.AddPattern( _Direct3DAPI, _DevicePattern )
		 || !MEM.AddPattern( _Direct3D, _ResetPattern )
		 || !MEM.AddPattern( _Direct3D, _BeginScenePattern )
		 || !MEM.AddPattern( _Direct3D, _EndScenePattern )
		 || !MEM.FindPatterns( ) )
		return LOG( ERROR, APPLICATION, "Unable to find patterns." ), false;

	return true;
}

void CLinkage::Uninitialize( )
{ }
