/// Drawing.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Drawing
{
	IDirect3DVertexBuffer9* pVertexBuffer = nullptr;;
	ID3DXLine* pLine;

	void PX_API Polygon( vertex_t* pVertices, std::size_t zVertexCount, std::size_t zPrimitiveCount, D3DPRIMITIVETYPE ptDrawingType /*= D3DPT_TRIANGLEFAN*/ )
	{
		const auto sVertexSize = sizeof( vertex_t ) * zVertexCount;
		if( D3D_OK != pDevice->CreateVertexBuffer( sVertexSize, NULL, PX_CUSTOM_FVF, D3DPOOL_DEFAULT, &pVertexBuffer, nullptr ) )
		{
			pVertexBuffer->Release( );
			pVertexBuffer = nullptr;
			return;
		}

		void* pVertexMemory;
		pVertexBuffer->Lock( 0, sVertexSize, &pVertexMemory, 0 );
		memcpy( pVertexMemory, pVertices, sVertexSize );
		pVertexBuffer->Unlock( );

		if ( D3D_OK != pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE )
			|| D3D_OK != pDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, TRUE )
			|| D3D_OK != pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA )
			|| D3D_OK != pDevice->SetStreamSource( NULL, pVertexBuffer, NULL, sizeof( vertex_t ) )
			|| D3D_OK != pDevice->SetPixelShader( nullptr )
			|| D3D_OK != pDevice->SetVertexShader( nullptr )
			|| D3D_OK != pDevice->SetTexture( NULL, nullptr )
			|| D3D_OK != pDevice->SetFVF( PX_CUSTOM_FVF ) )
		{
			pVertexBuffer->Release( );
			pVertexBuffer = nullptr;
			return;
		}

		px_assert( D3D_OK == pDevice->DrawPrimitive( ptDrawingType, 0, zPrimitiveCount ) );
		pVertexBuffer->Release( );
		pVertexBuffer = nullptr;
	}

	void PX_API Line( const D3DXVECTOR2* pPoints, std::size_t sPointCount, float flWidth, DWORD dwColor, BOOL bAntiAlias /*= TRUE*/ )
	{
		px_assert( sPointCount > 1 );

		if ( D3D_OK != D3DXCreateLine( pDevice, &pLine )
			|| D3D_OK != pLine->SetWidth( flWidth )
			|| D3D_OK != pLine->SetAntialias( bAntiAlias )
			|| D3D_OK != pLine->Begin( ) )
		{
			pLine->Release( );
			return;
		}

		px_assert( D3D_OK == pLine->Draw( pPoints, sPointCount, dwColor ) );
		pLine->End( );
		pLine->Release( );
	}
}
