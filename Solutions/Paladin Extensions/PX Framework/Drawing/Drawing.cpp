/// Drawing.cpp

#include "../PX Framework.hpp"

using namespace PX::Render;

namespace PX::Drawing
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DIndexBuffer9* pIndexBuffer;

	void PX_API Polygon( std::deque< vertex_t > vtxPoints )
	{
		if ( vtxPoints.empty( ) )
			return;

		unsigned short indexes[ ] = { 0, 1, 3, 1, 2, 3 };

		const auto sVertexSize = sizeof( vertex_t ) * vtxPoints.size( );
		if ( pDevice->CreateVertexBuffer( sVertexSize, D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &pVertexBuffer, nullptr ) != D3D_OK
			|| pDevice->CreateIndexBuffer( 2 * sizeof( short ), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIndexBuffer, nullptr ) != D3D_OK )
			return;

		vertex_t* pVertices;
		void* pIndices;
		if ( pVertexBuffer->Lock( NULL, NULL, reinterpret_cast< void** >( &pVertices ), NULL ) != D3D_OK )
		{
			pVertexBuffer->Unlock( );
			return;
		}

		for ( auto u = 0u; u < vtxPoints.size( ); u++ )
			pVertices[ u ] = vtxPoints[ u ];

		if ( pVertexBuffer->Unlock( ) != D3D_OK )
			return;

		if( pIndexBuffer->Lock( NULL, sizeof indexes, &pIndices, NULL ) != D3D_OK )
		{
			pIndexBuffer->Unlock( );
			return;
		}

		memcpy( pIndices, indexes, sizeof indexes );

		if ( pIndexBuffer->Unlock( ) != D3D_OK )
			return;

		if( D3D_OK != pDevice->SetTexture( NULL, nullptr ) ||
			D3D_OK != pDevice->SetPixelShader( nullptr ) ||
			D3D_OK != pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, 0x1 ) ||
			D3D_OK != pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) ||
			D3D_OK != pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA ) ||
			D3D_OK != pDevice->SetStreamSource( NULL, pVertexBuffer, NULL, sizeof( vertex_t ) ) ||
			D3D_OK != pDevice->SetIndices( pIndexBuffer ) )
			return;
		pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );

		pVertexBuffer->Release( );
		pIndexBuffer->Release( );
	}
}
