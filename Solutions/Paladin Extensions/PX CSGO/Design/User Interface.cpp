/// User Interface.cpp

#include "../PX CSGO.hpp"

using namespace PX::Information;
using namespace Interfaces;
using namespace Modules;

void PrintD3DeviceInfo( IDirect3DDevice9* pDeviceParameter )
{
	_D3DRENDERSTATETYPE uVertexRenderStates[ ]
	{
		D3DRS_ZENABLE ,
		D3DRS_FILLMODE ,
		D3DRS_SHADEMODE ,
		D3DRS_ZWRITEENABLE ,
		D3DRS_ALPHATESTENABLE ,
		D3DRS_LASTPIXEL ,
		D3DRS_SRCBLEND ,
		D3DRS_DESTBLEND ,
		D3DRS_CULLMODE ,
		D3DRS_ZFUNC ,
		D3DRS_ALPHAREF ,
		D3DRS_ALPHAFUNC ,
		D3DRS_DITHERENABLE ,
		D3DRS_ALPHABLENDENABLE ,
		D3DRS_FOGENABLE ,
		D3DRS_SPECULARENABLE ,
		D3DRS_FOGCOLOR ,
		D3DRS_FOGTABLEMODE ,
		D3DRS_FOGSTART ,
		D3DRS_FOGEND ,
		D3DRS_FOGDENSITY ,
		D3DRS_RANGEFOGENABLE ,
		D3DRS_STENCILENABLE ,
		D3DRS_STENCILFAIL ,
		D3DRS_STENCILZFAIL ,
		D3DRS_STENCILPASS ,
		D3DRS_STENCILFUNC ,
		D3DRS_STENCILREF ,
		D3DRS_STENCILMASK ,
		D3DRS_STENCILWRITEMASK ,
		D3DRS_TEXTUREFACTOR ,
		D3DRS_WRAP0 ,
		D3DRS_WRAP1 ,
		D3DRS_WRAP2 ,
		D3DRS_WRAP3 ,
		D3DRS_WRAP4 ,
		D3DRS_WRAP5 ,
		D3DRS_WRAP6 ,
		D3DRS_WRAP7 ,
		D3DRS_CLIPPING ,
		D3DRS_LIGHTING ,
		D3DRS_AMBIENT ,
		D3DRS_FOGVERTEXMODE ,
		D3DRS_COLORVERTEX ,
		D3DRS_LOCALVIEWER ,
		D3DRS_NORMALIZENORMALS ,
		D3DRS_DIFFUSEMATERIALSOURCE ,
		D3DRS_SPECULARMATERIALSOURCE ,
		D3DRS_AMBIENTMATERIALSOURCE ,
		D3DRS_EMISSIVEMATERIALSOURCE ,
		D3DRS_VERTEXBLEND ,
		D3DRS_CLIPPLANEENABLE ,
		D3DRS_POINTSIZE ,
		D3DRS_POINTSIZE_MIN ,
		D3DRS_POINTSPRITEENABLE ,
		D3DRS_POINTSCALEENABLE ,
		D3DRS_POINTSCALE_A ,
		D3DRS_POINTSCALE_B ,
		D3DRS_POINTSCALE_C ,
		D3DRS_MULTISAMPLEANTIALIAS ,
		D3DRS_MULTISAMPLEMASK ,
		D3DRS_PATCHEDGESTYLE ,
		D3DRS_DEBUGMONITORTOKEN ,
		D3DRS_POINTSIZE_MAX ,
		D3DRS_INDEXEDVERTEXBLENDENABLE ,
		D3DRS_COLORWRITEENABLE ,
		D3DRS_TWEENFACTOR ,
		D3DRS_BLENDOP ,
		D3DRS_POSITIONDEGREE ,
		D3DRS_NORMALDEGREE ,
		D3DRS_SCISSORTESTENABLE ,
		D3DRS_SLOPESCALEDEPTHBIAS ,
		D3DRS_ANTIALIASEDLINEENABLE ,
		D3DRS_MINTESSELLATIONLEVEL ,
		D3DRS_MAXTESSELLATIONLEVEL ,
		D3DRS_ADAPTIVETESS_X ,
		D3DRS_ADAPTIVETESS_Y ,
		D3DRS_ADAPTIVETESS_Z ,
		D3DRS_ADAPTIVETESS_W ,
		D3DRS_ENABLEADAPTIVETESSELLATION,
		D3DRS_TWOSIDEDSTENCILMODE ,
		D3DRS_CCW_STENCILFAIL ,
		D3DRS_CCW_STENCILZFAIL ,
		D3DRS_CCW_STENCILPASS ,
		D3DRS_CCW_STENCILFUNC ,
		D3DRS_COLORWRITEENABLE1 ,
		D3DRS_COLORWRITEENABLE2 ,
		D3DRS_COLORWRITEENABLE3 ,
		D3DRS_BLENDFACTOR ,
		D3DRS_SRGBWRITEENABLE ,
		D3DRS_DEPTHBIAS ,
		D3DRS_WRAP8 ,
		D3DRS_WRAP9 ,
		D3DRS_WRAP10 ,
		D3DRS_WRAP11 ,
		D3DRS_WRAP12 ,
		D3DRS_WRAP13 ,
		D3DRS_WRAP14 ,
		D3DRS_WRAP15 ,
		D3DRS_SEPARATEALPHABLENDENABLE ,
		D3DRS_SRCBLENDALPHA ,
		D3DRS_DESTBLENDALPHA ,
		D3DRS_BLENDOPALPHA
	};

	_D3DSAMPLERSTATETYPE uSamplerStates[ ]
	{
		D3DSAMP_ADDRESSU ,
		D3DSAMP_ADDRESSV ,
		D3DSAMP_ADDRESSW ,
		D3DSAMP_BORDERCOLOR ,
		D3DSAMP_MAGFILTER ,
		D3DSAMP_MINFILTER ,
		D3DSAMP_MIPFILTER ,
		D3DSAMP_MIPMAPLODBIAS ,
		D3DSAMP_MAXMIPLEVEL ,
		D3DSAMP_MAXANISOTROPY ,
		D3DSAMP_SRGBTEXTURE ,
		D3DSAMP_ELEMENTINDEX ,
		D3DSAMP_DMAPOFFSET
	};

	_D3DTEXTURESTAGESTATETYPE uTextureStates[ ]
	{
		D3DTSS_COLOROP ,
		D3DTSS_COLORARG1 ,
		D3DTSS_COLORARG2 ,
		D3DTSS_ALPHAOP ,
		D3DTSS_ALPHAARG1 ,
		D3DTSS_ALPHAARG2 ,
		D3DTSS_BUMPENVMAT00 ,
		D3DTSS_BUMPENVMAT01 ,
		D3DTSS_BUMPENVMAT10 ,
		D3DTSS_BUMPENVMAT11 ,
		D3DTSS_TEXCOORDINDEX ,
		D3DTSS_BUMPENVLSCALE ,
		D3DTSS_BUMPENVLOFFSET ,
		D3DTSS_TEXTURETRANSFORMFLAGS,
		D3DTSS_COLORARG0 ,
		D3DTSS_ALPHAARG0 ,
		D3DTSS_RESULTARG ,
		D3DTSS_CONSTANT
	};

	DWORD dwValue;
	for ( auto uState : uVertexRenderStates )
	{
		pDeviceParameter->GetRenderState( uState, &dwValue );
		std::cout << "Render State " << uState << ": " << dwValue << std::endl;
	}

	for ( auto uState : uSamplerStates )
	{
		pDeviceParameter->GetSamplerState( NULL, uState, &dwValue );
		std::cout << "Sampler State " << uState << ": " << dwValue << std::endl;
	}

	for ( auto uState : uTextureStates )
	{
		pDeviceParameter->GetTextureStageState( NULL, uState, &dwValue );
		std::cout << "Texture State " << uState << ": " << dwValue << std::endl;
	}
}

namespace PX::UI::Manager
{
	namespace CSGO
	{
		bool PX_API Initialize( )
		{
			unsigned uDimensions[ 2 ] { 720, 600 };

			PX_INPUT.AddKeyCallback( VK_HOME, [ = ]( bool bIsPressed )
			{
				if( bIsPressed )
					Render::bShouldRender = !Render::bShouldRender;
				while( ShowCursor( true ) <= 0 );
			} );

			return Render::InitializeRenderTarget( pDevice, uDimensions )
				&& InitializeUI( PX_XOR( "CS: GO" ) );
		}

		void PX_API OnEndScene( Types::ptr_t ptrReturnAddress )
		{
			static auto ptrDesiredReturnAddress = 0u;
			static auto bPrintedStates = false;
			auto bPrintStates = bool( PX_INPUT.GetKeyState( VK_RETURN ) ) && !bPrintedStates;

			if ( !ptrDesiredReturnAddress )
			{
				if ( Tools::FindAddressOrigin( ptrReturnAddress ) == mOverlay.hModule )
					ptrDesiredReturnAddress = ptrReturnAddress;
			}

			if ( ptrDesiredReturnAddress == ptrReturnAddress )
			{
				static IDirect3DStateBlock9* pState = nullptr;
				IDirect3DStateBlock9* pNewState = nullptr;
				IDirect3DVertexDeclaration9* pVertexDeclaration = nullptr;
				IDirect3DVertexShader9* pVertexShader = nullptr;
				DWORD dwColorWrite, dwSRGBWrite;


				if ( !pState )
					pDevice->CreateStateBlock( D3DSBT_ALL, &pState );
				pDevice->CreateStateBlock( D3DSBT_ALL, &pNewState );
				
				pState->Apply( );
				pState->Release( );

				if( bPrintStates )
				{
					std::cout << "Working State: " << std::endl;
					PrintD3DeviceInfo( pDevice );
				}

				px_assert( D3D_OK == pDevice->GetVertexDeclaration( &pVertexDeclaration )
						   && D3D_OK == pDevice->GetVertexShader( &pVertexShader )

						   && D3D_OK == pDevice->GetRenderState( D3DRS_COLORWRITEENABLE, &dwColorWrite )
						   && D3D_OK == pDevice->GetRenderState( D3DRS_SRGBWRITEENABLE, &dwSRGBWrite )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, UINT_MAX )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, NULL )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO )

						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_MAGFILTER, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_SRGBTEXTURE, NULL ) );

				if ( Render::bShouldRender && bCreatedTextures )
					Render( );

				px_assert( D3D_OK == pDevice->SetVertexDeclaration( pVertexDeclaration )
						   && D3D_OK == pDevice->SetVertexShader( pVertexShader )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, dwColorWrite )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, dwSRGBWrite ) );


				pNewState->Apply( );
				pNewState->Release( );

				if ( bPrintStates )
				{
					std::cout << "\n\nNot Working State: " << std::endl;
					PrintD3DeviceInfo( pDevice );
					bPrintedStates = true;
				}
			}
		}
	}

	void PX_API SetLayout( )
	{
		Example( );
	}

	void PX_API DrawOther( )
	{
	}
}
