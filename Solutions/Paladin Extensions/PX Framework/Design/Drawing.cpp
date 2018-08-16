/// Drawing.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Drawing
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DIndexBuffer9* pIndexBuffer;
	ID3DXLine* pLine;

	void PX_API Rectangle( unsigned uX, unsigned uY, unsigned uWidth, unsigned uHeight, DWORD dwColor )
	{
		vertex_t vtxPoints[ 4 ];

		vtxPoints[ 0 ].dwColor = vtxPoints[ 1 ].dwColor = vtxPoints[ 2 ].dwColor = vtxPoints[ 3 ].dwColor = dwColor;

		vtxPoints[ 0 ].flVectors[ 2 ] = vtxPoints[ 1 ].flVectors[ 2 ] = vtxPoints[ 2 ].flVectors[ 2 ] = vtxPoints[ 3 ].flVectors[ 2 ] = 0;
		vtxPoints[ 0 ].flVectors[ 3 ] = vtxPoints[ 1 ].flVectors[ 3 ] = vtxPoints[ 2 ].flVectors[ 3 ] = vtxPoints[ 3 ].flVectors[ 3 ] = 0;

		vtxPoints[ 0 ].flVectors[ 0 ] = float( uX );
		vtxPoints[ 0 ].flVectors[ 1 ] = float( uY );
		vtxPoints[ 1 ].flVectors[ 0 ] = float( uX + uWidth );
		vtxPoints[ 1 ].flVectors[ 1 ] = float( uY );
		vtxPoints[ 2 ].flVectors[ 0 ] = float( uX + uWidth );
		vtxPoints[ 2 ].flVectors[ 1 ] = float( uY + uHeight );
		vtxPoints[ 3 ].flVectors[ 0 ] = float( uX );
		vtxPoints[ 3 ].flVectors[ 1 ] = float( uY + uHeight );

		unsigned short sIndicies[ ] = { 0, 1, 3, 1, 2, 3 };

		pDevice->CreateVertexBuffer( 4 * sizeof( vertex_t ), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &pVertexBuffer, NULL );
		pDevice->CreateIndexBuffer( 2 * sizeof( short ), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIndexBuffer, NULL );

		void* pVertices;
		pVertexBuffer->Lock( 0, sizeof vtxPoints, static_cast< void** >( &pVertices ), 0 );
		memcpy( pVertices, vtxPoints, sizeof vtxPoints );
		pVertexBuffer->Unlock( );

		void* pIndex;
		pIndexBuffer->Lock( 0, sizeof sIndicies, static_cast< void** >( &pIndex ), 0 );
		memcpy( pIndex, sIndicies, sizeof sIndicies );
		pIndexBuffer->Unlock( );

		pDevice->SetTexture( 0, nullptr );
		pDevice->SetPixelShader( nullptr );
		pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		pDevice->SetStreamSource( 0, pVertexBuffer, 0, sizeof( vertex_t ) );
		pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
		pDevice->SetIndices( pIndexBuffer );

		pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );

		pVertexBuffer->Release( );
		pIndexBuffer->Release( );
	}

	void PX_API Line( std::deque< D3DXVECTOR2 > dqPoints, float flWidth, DWORD dwColor, BOOL bAntiAlias /*= TRUE*/ )
	{
		const auto sPoints = dqPoints.size( );

		px_assert( sPoints > 1 );

		if ( D3D_OK != D3DXCreateLine( pDevice, &pLine ) ||
			 D3D_OK != pLine->SetWidth( flWidth ) ||
			 D3D_OK != pLine->SetAntialias( bAntiAlias ) ||
			 D3D_OK != pLine->Begin( ) ||
			 D3D_OK != pLine->Draw( &dqPoints[ 0 ], 2, dwColor ) ||
			 D3D_OK != pLine->End( ) ||
			 D3D_OK != pLine->Release( ) )
			return;

		dqPoints.pop_front( );
		if ( sPoints > 2 )
			Line( dqPoints, flWidth, dwColor, bAntiAlias );
	}
}
