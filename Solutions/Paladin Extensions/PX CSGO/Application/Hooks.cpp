/// Hooks.cpp

#include "../PX CSGO.hpp"

void PrintD3DeviceInfo( IDirect3DDevice9* pDeviceParameter )
{
	DWORD dwFVF;
	pDeviceParameter->GetFVF( &dwFVF );

	float flNPatchMode = pDeviceParameter->GetNPatchMode( );

	D3DMATERIAL9 matMaterial;
	pDeviceParameter->GetMaterial( &matMaterial );

	IDirect3DPixelShader9* pShader;
	pDeviceParameter->GetPixelShader( &pShader );

	const UINT uSwapChains = pDeviceParameter->GetNumberOfSwapChains( );
	std::vector< D3DRASTER_STATUS > statRaster;
	statRaster.resize( uSwapChains );
	for ( auto u = 0u; u < uSwapChains; u++ )
		pDeviceParameter->GetRasterStatus( u, &statRaster[ u ] );

	std::vector< D3DRENDERSTATETYPE > vecRenderStateTypes {
		D3DRS_ZENABLE,
		D3DRS_FILLMODE,
		D3DRS_SHADEMODE,
		D3DRS_ZWRITEENABLE,
		D3DRS_ALPHATESTENABLE,
		D3DRS_LASTPIXEL,
		D3DRS_SRCBLEND,
		D3DRS_DESTBLEND,
		D3DRS_CULLMODE,
		D3DRS_ZFUNC,
		D3DRS_ALPHAREF,
		D3DRS_ALPHAFUNC,
		D3DRS_DITHERENABLE,
		D3DRS_ALPHABLENDENABLE,
		D3DRS_FOGENABLE,
		D3DRS_SPECULARENABLE,
		D3DRS_FOGCOLOR,
		D3DRS_FOGTABLEMODE,
		D3DRS_FOGSTART,
		D3DRS_FOGEND,
		D3DRS_FOGDENSITY,
		D3DRS_RANGEFOGENABLE,
		D3DRS_STENCILENABLE,
		D3DRS_STENCILFAIL,
		D3DRS_STENCILZFAIL,
		D3DRS_STENCILPASS,
		D3DRS_STENCILFUNC,
		D3DRS_STENCILREF,
		D3DRS_STENCILMASK,
		D3DRS_STENCILWRITEMASK,
		D3DRS_TEXTUREFACTOR,
		D3DRS_WRAP0,
		D3DRS_WRAP1,
		D3DRS_WRAP2,
		D3DRS_WRAP3,
		D3DRS_WRAP4,
		D3DRS_WRAP5,
		D3DRS_WRAP6,
		D3DRS_WRAP7,
		D3DRS_CLIPPING,
		D3DRS_LIGHTING,
		D3DRS_AMBIENT,
		D3DRS_FOGVERTEXMODE,
		D3DRS_COLORVERTEX,
		D3DRS_LOCALVIEWER,
		D3DRS_NORMALIZENORMALS,
		D3DRS_DIFFUSEMATERIALSOURCE,
		D3DRS_SPECULARMATERIALSOURCE,
		D3DRS_AMBIENTMATERIALSOURCE,
		D3DRS_EMISSIVEMATERIALSOURCE,
		D3DRS_VERTEXBLEND,
		D3DRS_CLIPPLANEENABLE,
		D3DRS_POINTSIZE,
		D3DRS_POINTSIZE_MIN,
		D3DRS_POINTSPRITEENABLE,
		D3DRS_POINTSCALEENABLE,
		D3DRS_POINTSCALE_A,
		D3DRS_POINTSCALE_B,
		D3DRS_POINTSCALE_C,
		D3DRS_MULTISAMPLEANTIALIAS,
		D3DRS_MULTISAMPLEMASK,
		D3DRS_PATCHEDGESTYLE,
		D3DRS_DEBUGMONITORTOKEN,
		D3DRS_POINTSIZE_MAX,
		D3DRS_INDEXEDVERTEXBLENDENABLE,
		D3DRS_COLORWRITEENABLE,
		D3DRS_TWEENFACTOR,
		D3DRS_BLENDOP,
		D3DRS_POSITIONDEGREE,
		D3DRS_NORMALDEGREE,
		D3DRS_SCISSORTESTENABLE,
		D3DRS_SLOPESCALEDEPTHBIAS,
		D3DRS_ANTIALIASEDLINEENABLE,
		D3DRS_MINTESSELLATIONLEVEL,
		D3DRS_MAXTESSELLATIONLEVEL,
		D3DRS_ADAPTIVETESS_X,
		D3DRS_ADAPTIVETESS_Y,
		D3DRS_ADAPTIVETESS_Z,
		D3DRS_ADAPTIVETESS_W,
		D3DRS_ENABLEADAPTIVETESSELLATION,
		D3DRS_TWOSIDEDSTENCILMODE,
		D3DRS_CCW_STENCILFAIL,
		D3DRS_CCW_STENCILZFAIL,
		D3DRS_CCW_STENCILPASS,
		D3DRS_CCW_STENCILFUNC,
		D3DRS_COLORWRITEENABLE1,
		D3DRS_COLORWRITEENABLE2,
		D3DRS_COLORWRITEENABLE3,
		D3DRS_BLENDFACTOR,
		D3DRS_SRGBWRITEENABLE,
		D3DRS_DEPTHBIAS,
		D3DRS_WRAP8,
		D3DRS_WRAP9,
		D3DRS_WRAP10,
		D3DRS_WRAP11,
		D3DRS_WRAP12,
		D3DRS_WRAP13,
		D3DRS_WRAP14,
		D3DRS_WRAP15,
		D3DRS_SEPARATEALPHABLENDENABLE,
		D3DRS_SRCBLENDALPHA,
		D3DRS_DESTBLENDALPHA,
		D3DRS_BLENDOPALPHA,
		D3DRS_FORCE_DWORD
	};
	std::vector< DWORD > vecRenderStates;
	vecRenderStates.resize( vecRenderStateTypes.size( ) );
	for each ( auto rsType in vecRenderStateTypes )
	{
		pDeviceParameter->GetRenderState( rsType, &vecRenderStates[ rsType ] );
	}

	std::vector< D3DSAMPLERSTATETYPE > vecSamplerStateTypes {
		D3DSAMP_ADDRESSU,
		D3DSAMP_ADDRESSV,
		D3DSAMP_ADDRESSW,
		D3DSAMP_BORDERCOLOR,
		D3DSAMP_MAGFILTER,
		D3DSAMP_MINFILTER,
		D3DSAMP_MIPFILTER,
		D3DSAMP_MIPMAPLODBIAS,
		D3DSAMP_MAXMIPLEVEL,
		D3DSAMP_MAXANISOTROPY,
		D3DSAMP_SRGBTEXTURE,
		D3DSAMP_ELEMENTINDEX,
		D3DSAMP_DMAPOFFSET,
		D3DSAMP_FORCE_DWORD
	};
	std::vector< DWORD > vecSamplerStates;
	vecSamplerStates.resize( vecSamplerStateTypes.size( ) );
	for each ( auto ssType in vecSamplerStateTypes )
	{
		pDeviceParameter->GetSamplerState( NULL, ssType, &vecSamplerStates[ ssType ] );
	}

	BOOL bSoftwareVertexProcessing = pDeviceParameter->GetSoftwareVertexProcessing( );
	IDirect3DVertexShader9* pShader2;
	pDeviceParameter->GetVertexShader( &pShader2 );
}

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
				static IDirect3DStateBlock9* pState = nullptr;
				IDirect3DStateBlock9* pCurrentState;
				DWORD dwColor, dwSRGB;
				IDirect3DVertexDeclaration9* pVertexDeclaration;
				IDirect3DVertexShader9* pVertexShader;

				if ( !pState )
					pDevice->CreateStateBlock( D3DSBT_ALL, &pState );
				pDevice->CreateStateBlock( D3DSBT_ALL, &pCurrentState );

				pState->Apply( );

				px_assert( //D3D_OK == pDevice->GetRenderState( D3DRS_COLORWRITEENABLE, &dwColor )
						   //&& D3D_OK == pDevice->GetRenderState( D3DRS_SRGBWRITEENABLE, &dwSRGB )
						    D3D_OK == pDevice->GetVertexDeclaration( &pVertexDeclaration )
						   && D3D_OK == pDevice->GetVertexShader( &pVertexShader )
						   
						   //&& D3D_OK == pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, UINT_MAX )
						   //&& D3D_OK == pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, FALSE )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_SRGBTEXTURE, NULL )

						   && UI::Manager::Render( )

						   //&& D3D_OK == pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, dwColor )
						   //&& D3D_OK == pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, dwSRGB )
						   && D3D_OK == pDevice->SetVertexDeclaration( pVertexDeclaration )
						   && D3D_OK == pDevice->SetVertexShader( pVertexShader ) );

				pCurrentState->Apply( );
				pCurrentState->Release( );
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
