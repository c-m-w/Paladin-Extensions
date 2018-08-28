/// Drawing.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Drawing
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	ID3DXLine* pLine;

	void PX_API Polygon( vertex_t* pVertices, std::size_t sVertexCount, D3DPRIMITIVETYPE ptDrawingType /*= D3DPT_TRIANGLEFAN*/ )
	{
		const auto sVertexSize = sizeof( vertex_t ) * sVertexCount;
		pDevice->CreateVertexBuffer( sVertexSize, NULL, PX_CUSTOM_FVF, D3DPOOL_DEFAULT, &pVertexBuffer, nullptr );

		void* pVertexMemory;
		pVertexBuffer->Lock( 0, sVertexSize, &pVertexMemory, 0 );
		memcpy( pVertexMemory, pVertices, sVertexSize );
		pVertexBuffer->Unlock( );

		pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		pDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, TRUE );
		pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		pDevice->SetStreamSource( 0, pVertexBuffer, 0, sizeof( vertex_t ) );
		pDevice->SetFVF( PX_CUSTOM_FVF );

		pDevice->DrawPrimitive( ptDrawingType, 0, sVertexCount );
		pVertexBuffer->Release( );
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
		pLine->Draw( &dqPoints[ 0 ], sPoints, dwColor );
		pLine->End( );
		dqPoints.pop_front( );
		pLine->Release( );
		if ( sPoints > 2 )
			Line( dqPoints, flWidth, dwColor, bAntiAlias );
	}
}
