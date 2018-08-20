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

#define print( var ) ( std::cout << #var << ": " << var << std::endl )
#define printn( var, num ) ( std::cout << #var << "[ " << num << " ]: " << var << std::endl )
	print( pDeviceParameter->GetAvailableTextureMem( ) );
	{
		struct anon
		{
			DWORD FVF;
		} *pDevice = new anon;
		pDeviceParameter->GetFVF( &pDevice->FVF );
		delete pDevice;
	}
	print( pDeviceParameter->GetNPatchMode( ) );
	{
		struct anon
		{
			D3DMATERIAL9 Material;
		} *pDevice = new anon;
		pDeviceParameter->GetMaterial( &pDevice->Material );
		print( pDevice->Material.Ambient.a );
		print( pDevice->Material.Ambient.b );
		print( pDevice->Material.Ambient.g );
		print( pDevice->Material.Ambient.r );
		print( pDevice->Material.Diffuse.a );
		print( pDevice->Material.Diffuse.b );
		print( pDevice->Material.Diffuse.g );
		print( pDevice->Material.Diffuse.r );
		print( pDevice->Material.Emissive.a );
		print( pDevice->Material.Emissive.b );
		print( pDevice->Material.Emissive.g );
		print( pDevice->Material.Emissive.r );
		print( pDevice->Material.Power );
		print( pDevice->Material.Specular.a );
		print( pDevice->Material.Specular.b );
		print( pDevice->Material.Specular.g );
		print( pDevice->Material.Specular.r );
		delete pDevice;
	}
	//{
	//	struct anon
	//	{
	//		IDirect3DPixelShader9* PixelShader;
	//	} *pDevice = new anon;
	//	pDeviceParameter->GetPixelShader( &pDevice->PixelShader );
	//	void* pData = NULL;
	//	pDevice->PixelShader->GetFunction( pData, NULL );
	//	void* pDevicePixelShaderGetFunctionData = NULL;
	//	pDevice->PixelShader->GetFunction( pDevicePixelShaderGetFunctionData, static_cast< UINT* >( pData ) );
	//	print( pDevicePixelShaderGetFunctionData );
	//	delete pDevice;
	//}
	print( pDeviceParameter->GetNumberOfSwapChains( ) );
	const UINT uSwapChains = pDeviceParameter->GetNumberOfSwapChains( );
	{
		struct anon
		{
			std::vector< D3DRASTER_STATUS > RasterStatus;
		} *pDevice = new anon;
		pDevice->RasterStatus.resize( uSwapChains );
		for ( auto u = 0u; u < uSwapChains; u++ )
			pDeviceParameter->GetRasterStatus( u, &pDevice->RasterStatus[ u ] );
		for ( auto u = 0u; u < uSwapChains; u++ )
		{
			printn( pDevice->RasterStatus.at( u ).InVBlank, u );
			printn( pDevice->RasterStatus.at( u ).ScanLine, u );
		}
		delete pDevice;
	}
	{
		struct anon
		{
			std::vector< IDirect3DSurface9* > Type;
		} *pDevice = new anon;
		pDevice->Type.resize( uSwapChains );
		for ( auto u = 0u; u < uSwapChains; u++ )
			pDeviceParameter->GetBackBuffer( u, 0, D3DBACKBUFFER_TYPE_MONO, &pDevice->Type[ u ] );
		std::cout << "\t\tBACK BUFFER" << std::endl;
		for ( auto u = 0u; u < uSwapChains; u++ )
		{
			printn( pDevice->Type.at( u )->DCCount, u );
			printn( pDevice->Type.at( u )->Format, u );
			void* pContainerIID;
			IID bufIID;
			pDevice->Type.at( u )->GetContainer( bufIID, &pContainerIID );
			printn( pContainerIID, u );
			printn( bufIID.Data1, u );
			printn( bufIID.Data2, u );
			printn( bufIID.Data3, u );
			printn( bufIID.Data4, u );
			HDC bufHDC;
			pDevice->Type.at( u )->GetDC( &bufHDC );
			printn( bufHDC->unused, u );
			D3DSURFACE_DESC bufDESC;
			pDevice->Type.at( u )->GetDesc( &bufDESC );
			printn( bufDESC.Format, u );
			printn( bufDESC.Usage, u );
			printn( bufDESC.Type, u );
			printn( bufDESC.Height, u );
			printn( bufDESC.Width, u );
			printn( bufDESC.MultiSampleQuality, u );
			printn( bufDESC.MultiSampleType, u );
			printn( bufDESC.Pool, u );
			printn( pDevice->Type.at( u )->Name, u );
			printn( pDevice->Type.at( u )->GetType( ), u );
			printn( pDevice->Type.at( u )->Usage, u );
			printn( pDevice->Type.at( u )->Width, u );
		}
		std::cout << "\t\tEND BACK BUFFER" << std::endl;
		delete pDevice;
	}
	print( pDeviceParameter->GetSoftwareVertexProcessing( ) );
	{
		struct anon
		{
			float ClipPlane;
		} *pDevice = new anon;
		for ( auto u = 0; u < 24; u++ )
		{
			pDeviceParameter->GetClipPlane( u, &pDevice->ClipPlane );
			printn( pDevice->ClipPlane, u );
		}
		delete pDevice;
	}
	{
		struct anon
		{
			D3DCLIPSTATUS9 ClipStatus;
		} *pDevice = new anon;
		pDeviceParameter->GetClipStatus( &pDevice->ClipStatus );
		print( pDevice->ClipStatus.ClipIntersection );
		print( pDevice->ClipStatus.ClipUnion );
		delete pDevice;
	}
	{
		struct anon
		{
			D3DDEVICE_CREATION_PARAMETERS CreationParameters;
		} *pDevice = new anon;
		pDeviceParameter->GetCreationParameters( &pDevice->CreationParameters );
		print( pDevice->CreationParameters.AdapterOrdinal );
		print( pDevice->CreationParameters.BehaviorFlags );
		print( pDevice->CreationParameters.DeviceType );
		print( pDevice->CreationParameters.hFocusWindow );
		delete pDevice;
	}
	{
		struct anon
		{
			UINT CurrentTexturePalette;
		} *pDevice = new anon;
		pDeviceParameter->GetCurrentTexturePalette( &pDevice->CurrentTexturePalette );
		print( pDevice->CurrentTexturePalette );
		delete pDevice;
	}
	{
		struct anon
		{
			IDirect3DSurface9* DepthStencilSurface;
		} *pDevice = new anon;
		pDeviceParameter->GetDepthStencilSurface( &pDevice->DepthStencilSurface );
		print( pDevice->DepthStencilSurface ); // ??????
		delete pDevice;
	}

	
	
	/*
	{
		struct anon
		{
			____ NAME;
		} *pDevice = new anon;
		pDeviceParameter->Get( &pDevice->NAME );
		print( pDevice->NAME );
		delete pDevice;
	}
	*/


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	for ( auto uState : uVertexRenderStates )
	{
		struct anon
		{
			DWORD RenderState;
		} *pDevice = new anon;
		pDeviceParameter->GetRenderState( uState, &pDevice->RenderState );

		printn( pDevice->RenderState, uState );
		delete pDevice;
	}

	for ( auto uState : uSamplerStates )
	{
		struct anon
		{
			DWORD SamplerState;
		} *pDevice = new anon;
		pDeviceParameter->GetSamplerState( NULL, uState, &pDevice->SamplerState );

		printn( pDevice->SamplerState, uState );
		delete pDevice;
	}

	for ( auto uState : uTextureStates )
	{
		struct anon
		{
			DWORD TextureStageState;
		} *pDevice = new anon;
		pDeviceParameter->GetTextureStageState( NULL, uState, &pDevice->TextureStageState );

		printn( pDevice->TextureStageState, uState );
		delete pDevice;
	}

#undef print
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
