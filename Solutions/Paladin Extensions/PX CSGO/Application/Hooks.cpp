/// Hooks.cpp

#include "../PX CSGO.hpp"

using namespace PX::VirtualTableIndicies;
using namespace PX::Information;
using namespace Interfaces;

namespace PX
{
	namespace Hooks
	{
		bool PX_API SetHooks( )
		{
			return hkDirectXDevice->HookIndex( uEndScene, reinterpret_cast< void* >( EndScene ) );
		}

		bool PX_API InitializeHooks( )
		{
			hkDirectXDevice = new Tools::CHook( pDevice );
			return true;
			//return hkDirectXDevice->Succeeded( ) ? SetHooks( ) : false;
		}

		int __stdcall EndScene( IDirect3DDevice9* pDevice )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< Types::endscene_t >( uEndScene );
			std::cout << "EndScene has been called." << std::endl;
			return fnOriginal( pDevice );
		}

		int __stdcall Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< Types::reset_t  >( uReset );
			std::cout << "Reset has been called." << std::endl;
			return fnOriginal( pDevice, pParams );
		}
	}
}
