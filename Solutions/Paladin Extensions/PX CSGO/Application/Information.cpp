/// Interfaces.cpp

#include "../PX CSGO.hpp"

namespace PX::Information
{
	bool PX_API Initialize( )
	{
		return Memory::Setup( )
			&& Modules::Setup( )
			&& Interfaces::Setup( );
	}

	namespace Memory
	{
		bool PX_API Setup( )
		{			
			// Get information for shit from server
			return true;
		}
	}

	namespace Modules
	{
		bool SModule::Setup( std::wstring wstrModule )
		{
			wstrName = wstrModule;
			hModule = GetModuleHandle( wstrName.c_str( ) );
			ciFactory = reinterpret_cast< CreateInterfaceFn >( GetProcAddress( hModule, strCreateInterfaceName.c_str( ) ) );
			return hModule != nullptr
				&& ciFactory != nullptr;
		}

		bool PX_API Setup( )
		{
			return mEngine.Setup( L"engine.dll" )
				&& mClient.Setup( L"client.dll" )
				&& mDirectX.Setup( L"shaderapidx9.dll" );
		}
	}

	namespace Interfaces
	{
		bool PX_API Setup( )
		{
			pDevice = **reinterpret_cast< IDirect3DDevice9*** >( Modules::mDirectX.FindPattern( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 1 );
			pClientBase = reinterpret_cast< IBaseClientDLL* >( Modules::mClient.ciFactory( "VClient018", nullptr ) );

			return pDevice != nullptr
				&& pClientBase != nullptr;
		}
	}
}
