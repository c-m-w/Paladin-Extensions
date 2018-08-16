/// Hooks.cpp

#include "../PX CSGO.hpp"

using namespace PX::VirtualTableIndicies;
using namespace PX::Information;
using namespace Interfaces;

namespace PX
{
	namespace Hooks
	{
		bool PX_API InitializeHooks( )
		{
			hkDirectXDevice = new Tools::CHook( pDevice );

			return hkDirectXDevice->Succeeded( );
		}

		int __stdcall EndScene( IDirect3DDevice9* pDevice )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< Types::endscene_t >( uEndScene );
			return fnOriginal( pDevice );
		}

		int __stdcall Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< Types::reset_t  >( uReset );
			return fnOriginal( pDevice, pParams );
		}
	}
}
