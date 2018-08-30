/// Drawing.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Drawing
{
	IDirect3DVertexBuffer9* pVertexBuffer = nullptr;;
	ID3DXLine* pLine;

	void PX_API Polygon( vertex_t* pVertices, std::size_t sVertexCount, std::size_t sPrimitiveCount, D3DPRIMITIVETYPE ptDrawingType /*= D3DPT_TRIANGLEFAN*/ )
	{
		const auto sVertexSize = sizeof( vertex_t ) * sVertexCount;
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

		px_assert( D3D_OK == pDevice->DrawPrimitive( ptDrawingType, 0, sPrimitiveCount ) );
		pVertexBuffer->Release( );
		pVertexBuffer = nullptr;
	}

	IDirect3DVertexBuffer9* g_pVB = nullptr;
	IDirect3DIndexBuffer9* g_pIB = nullptr;

	void BoxFilled( float x, float y, float w, float h, DWORD color )
	{
		vertex_t V[ 4 ];

		V[ 0 ].dwColor = V[ 1 ].dwColor = V[ 2 ].dwColor = V[ 3 ].dwColor = color;

		V[ 0 ].flVectors[ 2 ] = V[ 1 ].flVectors[ 2 ] = V[ 2 ].flVectors[ 2 ] = V[ 3 ].flVectors[ 2 ] = 0;
		V[ 0 ].flVectors[ 3 ] = V[ 1 ].flVectors[ 3 ] = V[ 2 ].flVectors[ 3 ] = V[ 3 ].flVectors[ 3 ] = 0;

		V[ 0 ].flVectors[ 0 ] = x;
		V[ 0 ].flVectors[ 1 ] = y;
		V[ 1 ].flVectors[ 0 ] = x + w;
		V[ 1 ].flVectors[ 1 ] = y;
		V[ 2 ].flVectors[ 0 ] = x + w;
		V[ 2 ].flVectors[ 1 ] = y + h;
		V[ 3 ].flVectors[ 0 ] = x;
		V[ 3 ].flVectors[ 1 ] = y + h;

		unsigned short indexes[ ] = { 0, 1, 3, 0, 2, 3 };

		pDevice->CreateVertexBuffer( 4 * sizeof( vertex_t ), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL );
		pDevice->CreateIndexBuffer( 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL );

		VOID* pVertices;
		g_pVB->Lock( 0, sizeof( V ), ( void** )&pVertices, 0 );
		memcpy( pVertices, V, sizeof( V ) );
		g_pVB->Unlock( );

		VOID* pIndex;
		g_pIB->Lock( 0, sizeof( indexes ), ( void** )&pIndex, 0 );
		memcpy( pIndex, indexes, sizeof( indexes ) );
		g_pIB->Unlock( );

		pDevice->SetTexture( 0, NULL );
		pDevice->SetPixelShader( NULL );
		pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		pDevice->SetStreamSource( 0, g_pVB, 0, sizeof( vertex_t ) );
		pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
		pDevice->SetIndices( g_pIB );

		pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );

		g_pVB->Release( );
		g_pIB->Release( );
	}

	void PX_API Line( std::deque< D3DXVECTOR2 > dqPoints, float flWidth, DWORD dwColor, BOOL bAntiAlias /*= TRUE*/ )
	{
		const auto sPoints = dqPoints.size( );

		px_assert( sPoints > 1 );

		if ( D3D_OK != D3DXCreateLine( pDevice, &pLine ) ||
			 D3D_OK != pLine->SetWidth( flWidth ) ||
			 D3D_OK != pLine->SetAntialias( bAntiAlias ) )
		{
			pLine->Release( );
			return;
		}

		pLine->Begin( );
		pLine->Draw( &dqPoints[ 0 ], 2, dwColor );
		pLine->End( );
		dqPoints.pop_front( );
		pLine->Release( );
		if ( sPoints > 2 )
			Line( dqPoints, flWidth, dwColor, bAntiAlias );
	}
}
