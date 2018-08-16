/// Hooks.cpp

#include "../PX CSGO.hpp"

using namespace VirtualTableIndicies;
using namespace Information;
using namespace Interfaces;

namespace PX
{
	namespace Hooks
	{
		bool PX_API SetHooks( )
		{
			return hkDirectXDevice->HookIndex( uEndScene, EndScene );
		}

		bool PX_API Initialize( )
		{
			hkDirectXDevice = new CHook( pDevice );

			return hkDirectXDevice->Succeeded( ) ? SetHooks( ) : false;
		}

		int __stdcall EndScene( IDirect3DDevice9* pDevice )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< endscene_t >( uEndScene );
			return fnOriginal( pDevice );
		}

		int __stdcall Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< reset_t  >( uReset );
			return fnOriginal( pDevice, pParams );
		}
	}
}
