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
			return hkDirectXDevice->HookIndex( uEndScene, reinterpret_cast< void* >( EndScene ) )
				&& hkDirectXDevice->HookIndex( uReset, reinterpret_cast< void* >( Reset ) )
				&& hkDirectXDevice->HookIndex( uPresent, reinterpret_cast< void* >( Present ) );
		}

		bool PX_API InitializeHooks( )
		{
			hkDirectXDevice = new Tools::CHook( pDevice );

			return hkDirectXDevice->Succeeded( ) ? SetHooks( ) : false;
		}

		HRESULT __stdcall EndScene( IDirect3DDevice9* pDeviceParameter )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< Types::endscene_t >( uEndScene );
			static auto ptrDesiredReturnAddress = 0u;
			const auto ptrReturnAddress = Types::ptr_t( _ReturnAddress( ) );

			if( !ptrDesiredReturnAddress )
			{
				if ( Tools::FindAddressOrigin( ptrReturnAddress ) == Modules::mOverlay.hModule )
					ptrDesiredReturnAddress = ptrReturnAddress;
			}

			if( ptrDesiredReturnAddress == ptrReturnAddress )	
			{																	
				DWORD dwColor, dwSRGB;
				IDirect3DVertexDeclaration9* pVertexDeclaration;
				IDirect3DVertexShader9* pVertexShader;
				IDirect3DStateBlock9* pPixelState;

				px_assert( D3D_OK == pDevice->GetRenderState( D3DRS_COLORWRITEENABLE, &dwColor )
						   && D3D_OK == pDevice->GetRenderState( D3DRS_SRGBWRITEENABLE, &dwSRGB )
						   && D3D_OK == pDevice->GetVertexDeclaration( &pVertexDeclaration )
						   && D3D_OK == pDevice->GetVertexShader( &pVertexShader )
						   && D3D_OK == pDevice->CreateStateBlock( D3DSBT_PIXELSTATE, &pPixelState )

						   && D3D_OK == pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, UINT_MAX )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, FALSE )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_SRGBTEXTURE, NULL )

						   && UI::Manager::Render( )

						   && D3D_OK == pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, dwColor )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, dwSRGB )
						   && D3D_OK == pDevice->SetVertexDeclaration( pVertexDeclaration )
						   && D3D_OK == pDevice->SetVertexShader( pVertexShader )
						   && D3D_OK == pPixelState->Apply( )
						   && D3D_OK == pPixelState->Release( ) );
			}
			std::cout << "EndScene has been called." << std::endl;
			return fnOriginal( pDeviceParameter );
		}

		HRESULT __stdcall Reset( IDirect3DDevice9* pDeviceParameter, D3DPRESENT_PARAMETERS* pParams )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< Types::reset_t  >( uReset );
			std::cout << "Reset has been called." << std::endl;
			const auto hrReset = fnOriginal( pDeviceParameter, pParams );
			if ( SUCCEEDED( hrReset ) )
				UI::Manager::OnDeviceReset( );
			return hrReset;
		}

		HRESULT __stdcall Present( IDirect3DDevice9* pDeviceParameter, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< Types::present_t >( uPresent );
			std::cout << "Present has been called." << std::endl;
			return fnOriginal( pDeviceParameter, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
		}
	}
}
