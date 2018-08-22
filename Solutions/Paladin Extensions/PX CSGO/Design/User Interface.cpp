/// User Interface.cpp

#include "../PX CSGO.hpp"

using namespace PX::Information;
using namespace Interfaces;
using namespace Modules;

void PrintBetterDeviceStateInfo( IDirect3DDevice9* pDeviceParameter )
{
#define nameof( var ) ( #var )
#define print( name, var ) ( std::cout << name << ": " << var << std::endl )
#define printn( var ) ( std::cout << #var << ": " << var << std::endl )
#define printv( var, index, varval ) ( std::cout << #var << "[ " << index << " ]" << ": " << varval << std::endl )
#define printvv( var, index, index2, varval ) ( std::cout << #var << "[ " << index << " ]" << "[ " << index2 << " ]" << ": " << varval << std::endl )
#define printvvv( var, index, index2, index3, varval ) ( std::cout << #var << "[ " << index << " ]" << "[ " << index2 << " ]" << "[ " << index3 << " ]" << ": " << varval << std::endl )
#define printnv( name, index, varval ) ( std::cout << name << "[ " << index << " ]" << ": " << varval << std::endl )
#define printnvv( name, index, index2, varval ) ( std::cout << name << "[ " << index << " ]" << "[ " << index2 << " ]" << ": " << varval << std::endl )



	D3DMATRIX GetTransformWorld, GetTransformView, GetTransformProjection, GetTransformTextures[ D3DTS_TEXTURE7 - D3DTS_TEXTURE0 + 1 ];
	pDeviceParameter->GetTransform( D3DTS_WORLD, &GetTransformWorld );
	pDeviceParameter->GetTransform( D3DTS_VIEW, &GetTransformView );
	pDeviceParameter->GetTransform( D3DTS_PROJECTION, &GetTransformProjection );
	for ( int i = D3DTS_TEXTURE0; i <= D3DTS_TEXTURE7; i++ )
		pDeviceParameter->GetTransform( D3DTRANSFORMSTATETYPE( D3DTS_TEXTURE0 + i ), &GetTransformTextures[ i ] );
	for ( int i = 0; i < 4; i++ )
		for ( int ii = 0; ii < 4; ii++ )
		{
			printvv( GetTransformWorld, i, ii, GetTransformWorld.m[ i ][ ii ] );
			printvv( GetTransformView, i, ii, GetTransformView.m[ i ][ ii ] );
			printvv( GetTransformProjection, i, ii, GetTransformProjection.m[ i ][ ii ] );
			for ( int iii = 0; iii < 8; iii++ )
				printvvv( GetTransformTextures, i, ii, iii, GetTransformTextures[ iii ].m[ i ][ ii ] );
		}



	DWORD GetRenderStateCOLORWRITEENABLE, GetRenderStateSRGBWRITEENABLE, GetFVF;
	pDeviceParameter->GetRenderState( D3DRS_COLORWRITEENABLE, &GetRenderStateCOLORWRITEENABLE );
	pDeviceParameter->GetRenderState( D3DRS_SRGBWRITEENABLE, &GetRenderStateSRGBWRITEENABLE );
	pDeviceParameter->GetFVF( &GetFVF );
	printn( GetRenderStateCOLORWRITEENABLE );
	printn( GetRenderStateSRGBWRITEENABLE );
	printn( GetFVF );



	IDirect3DVertexBuffer9* GetStreamSourceData;
	UINT GetStreamSourceOffset, GetStreamSourceStride;
	pDeviceParameter->GetStreamSource( 0, &GetStreamSourceData, &GetStreamSourceOffset, &GetStreamSourceStride );
	printn( GetStreamSourceData->Priority );
	printn( GetStreamSourceData->Pool );
	printn( GetStreamSourceData->Name );
	printn( GetStreamSourceData->LockCount );
	printn( GetStreamSourceData->Length );
	printn( GetStreamSourceData->Usage );
	printn( GetStreamSourceData->CreationCallStack );
	printn( GetStreamSourceData->FVF );
	printn( GetStreamSourceOffset );
	printn( GetStreamSourceStride );



	IDirect3DBaseTexture9* GetTexture;
	IDirect3DSurface9* GetRenderTarget;
	IDirect3DIndexBuffer9* GetIndices;
	IDirect3DVertexDeclaration9* GetVertexDeclaration;
	IDirect3DPixelShader9* GetPixelShader;
	IDirect3DVertexShader9* GetVertexShader;
	pDeviceParameter->GetTexture( 0, &GetTexture );
	pDeviceParameter->GetRenderTarget( 0, &GetRenderTarget );
	pDeviceParameter->GetIndices( &GetIndices );
	pDeviceParameter->GetVertexDeclaration( &GetVertexDeclaration );
	pDeviceParameter->GetPixelShader( &GetPixelShader );
	pDeviceParameter->GetVertexShader( &GetVertexShader );
	printn( GetTexture->GetAutoGenFilterType( ) );
	printn( GetTexture->GetLOD( ) );
	printn( GetTexture->GetLevelCount( ) );
	printn( GetTexture->GetType( ) );
	printn( GetRenderTarget->DCCount );
	printn( GetRenderTarget->MultiSampleType );
	printn( GetRenderTarget->MultiSampleQuality );
	printn( GetRenderTarget->Width );
	printn( GetRenderTarget->Height );
	printn( GetRenderTarget->Format );
	printn( GetRenderTarget->Priority );
	printn( GetRenderTarget->Pool );
	printn( GetRenderTarget->Name );
	printn( GetRenderTarget->LockCount );
	printn( GetRenderTarget->Usage );
	printn( GetRenderTarget->CreationCallStack );
	printn( GetIndices->Format );
	printn( GetIndices->Priority );
	printn( GetIndices->Pool );
	printn( GetIndices->Name );
	printn( GetIndices->LockCount );
	printn( GetIndices->Usage );
	printn( GetIndices->CreationCallStack );
	printn( GetIndices->Length );
	printn( GetVertexDeclaration->CreationCallStack );
	printn( GetPixelShader->CreationCallStack );
	printn( GetPixelShader->Version );
	printn( GetVertexShader->CreationCallStack );
	printn( GetVertexShader->Version );



	// REALLY hoping there is no safety required for calling "release"
	GetStreamSourceData->Release( );
	GetTexture->Release( );
	GetRenderTarget->Release( );
	GetIndices->Release( );
	GetVertexDeclaration->Release( );
	GetPixelShader->Release( );
	GetVertexShader->Release( );
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
