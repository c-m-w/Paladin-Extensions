/// User Interface.cpp

#include "../PX CSGO.hpp"

using namespace PX::Information;
using namespace Interfaces;
using namespace Modules;

namespace PX::UI::Manager
{
	namespace CSGO
	{
		bool PX_API Initialize( )
		{
			int iDimensions[ 2 ];
			unsigned uDimensions[ 2 ];

			pEngineClient->GetScreenSize( iDimensions[ 0 ], iDimensions[ 1 ] );
			memcpy( uDimensions, iDimensions, sizeof( int ) * 2 );
			Render::bShouldRender = false;

			PX_INPUT.AddKeyCallback( VK_HOME, [ = ]( bool bIsPressed )
			{
				if( bIsPressed )
					Render::bShouldRender = !Render::bShouldRender;
				while( ShowCursor( true ) <= 0 );
			} );

			return Render::InitializeRenderTarget( pDevice, uDimensions )
				&& InitializeUI( PX_XOR( "CSGO" ), 720u, 600u );
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
				IDirect3DStateBlock9* pNewState = nullptr;
				IDirect3DVertexDeclaration9* pVertexDeclaration = nullptr;
				IDirect3DVertexShader9* pVertexShader = nullptr;
				DWORD dwColorWrite, dwSRGBWrite;

				pDevice->CreateStateBlock( D3DSBT_PIXELSTATE, &pNewState );

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
			}
		}

		void PX_API OnReset( )
		{
			Render::bShouldRender = false;
			bCreatedTextures = false;
		}

		void PX_API OnSuccessfulReset( unsigned uWidth, unsigned uHeight )
		{
			bCreatedTextures = true;
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
