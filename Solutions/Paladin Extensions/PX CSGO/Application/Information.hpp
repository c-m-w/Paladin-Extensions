/// Interfaces.hpp

#pragma once

namespace PX::Information
{
	bool PX_API InitializeInformation( );

	namespace Memory
	{
		bool PX_API Setup( );
	}
	
	namespace Modules
	{
		PX_SDK std::string strCreateInterfaceName = PX_XOR( "CreateInterface" );
		struct SModule: Types::module_t
		{
			CreateInterfaceFn ciFactory { };

			bool Setup( std::wstring wstrModule );
		};

		bool PX_API Setup( );

		PX_SDK SModule mEngine;
		PX_SDK SModule mClient;
		PX_SDK SModule mDirectX;
		PX_SDK SModule mOverlay;
	}

	namespace Interfaces
	{
		bool PX_API Setup( );

		PX_SDK IDirect3DDevice9* pDevice;
		PX_SDK IBaseClientDLL* pClientBase;
	}	
}
