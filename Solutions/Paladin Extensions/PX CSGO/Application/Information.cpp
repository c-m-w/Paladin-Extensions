/// Interfaces.cpp

#include "../PX CSGO.hpp"

namespace PX::Information
{
	nlohmann::json jsMemoryInformation;

	bool PX_API InitializeInformation( )
	{
		return Memory::Setup( )
			&& Modules::Setup( )
			&& Interfaces::Setup( );
	}

	namespace Memory
	{
		bool PX_API Setup( )
		{		
			/// Used for updating information file on server dont delete.
			//nlohmann::json js;
			//
			//js[ "Modules" ][ "Engine" ] = "engine.dll";
			//js[ "Modules" ][ "Client" ] = "client.dll";
			//js[ "Modules" ][ "DirectX API" ] = "shaderapidx9.dll";
			//
			//js[ "Versions" ][ "Client Base" ] = "VClient018";
			//
			//js[ "Patterns" ][ "Signatures" ][ "Device" ] = "A1 ? ? ? ? 50 8B 08 FF 51 0C";
			//js[ "Patterns" ][ "Offsets" ][ "Device" ] = 1;
			//
			//std::string str = js.dump( 4 );
			jsMemoryInformation = nlohmann::json::parse( Cryptography::Decrypt( Net::RequestExtension( PX_EXTENSION_CSGO, true ) ) );
			return true;
		}
	}

	namespace Modules
	{
		bool SModule::Setup( std::wstring wstrModule )
		{
			wstrName = wstrModule;
			hModule = GetModuleHandle( wstrName.c_str( ) );
			if ( hModule )
			{
				ciFactory = reinterpret_cast< CreateInterfaceFn >( GetProcAddress( hModule, strCreateInterfaceName.c_str( ) ) );
				return true;
			}
			return false;
		}

		bool PX_API Setup( )
		{
			constexpr auto mmtMaxWaitTime = 7500ull;
			const auto mmtStart = Tools::GetMoment( );
			do
			{
				if( Tools::GetMoment( ) - mmtStart >= mmtMaxWaitTime )
					return false;
			} while( !mEngine.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Engine" ) ].get< std::string >( ) ) )
				|| !mClient.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Client" ) ].get< std::string >( ) ) )
				|| !mDirectX.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "DirectX API" ) ].get< std::string >( ) ) )
				|| !mOverlay.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Overlay" ) ].get< std::string >( ) ) ) );
			return true;
		}
	}

	namespace Interfaces
	{
		bool PX_API Setup( )
		{
			std::cout << "Pattern: " << jsMemoryInformation[ "Patterns" ][ "Signatures" ][ "Device" ].get< std::string >( ) << std::endl;
			std::cout << "Offset: " << jsMemoryInformation[ "Patterns" ][ "Offsets" ][ "Device" ].get< int >( ) << std::endl;

			const auto ptrDeviceAddress = Modules::mDirectX.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Device" ) ].get< std::string >( ) )
				+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Device" ) ].get< int >( );
			std::cout << "Found Address: " << ptrDeviceAddress << std::endl;

			pDevice = **reinterpret_cast< IDirect3DDevice9*** >( ptrDeviceAddress );

			pClientBase = reinterpret_cast< IBaseClientDLL* >( Modules::mClient.ciFactory( 
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Client Base" ) ].get< std::string >( ).c_str( ), nullptr ) );
			std::cout << "Device: " << Types::ptr_t( pDevice ) << std::endl;
			std::cout << "Client Base: " << Types::ptr_t( pClientBase ) << std::endl;

			return pDevice != nullptr
				&& pClientBase != nullptr;
		}
	}
}
