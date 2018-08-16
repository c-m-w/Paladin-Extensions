/// Interfaces.hpp

#pragma once

#include "../SDK/Valve/Interfaces/IAppSystem.hpp"
#include "../SDK/Valve/Interfaces/IBaseClientDll.hpp"


namespace PX::Information
{
	bool PX_API Initialize( );

	namespace Memory
	{
		bool PX_API Setup( );
	}
	
	namespace Modules
	{
		PX_SDK std::string strCreateInterfaceName = PX_XOR( "CreateInterface" );
		struct SModule : module_t
		{
			CreateInterfaceFn ciFactory { };

			bool Setup( std::wstring wstrModule );
		};

		bool PX_API Setup( );

		PX_SDK SModule mEngine;
		PX_SDK SModule mClient;
		PX_SDK SModule mDirectX;
	}

	namespace Interfaces
	{
		bool PX_API Setup( );

		PX_SDK IDirect3DDevice9* pDevice;
		PX_SDK IBaseClientDLL* pClientBase;
	}	
}
