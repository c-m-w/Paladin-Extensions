/// Drawing.cpp

#include "../PX Framework.hpp"

using namespace PX::Render;

namespace PX::Drawing
{
	IDirect3DVertexBuffer9* pVertexBuffer;

	void PX_API Polygon( std::deque< vertex_t > vtxPoints )
	{
		if ( vtxPoints.empty( ) )
			return;

		const auto sVertexSize = sizeof( vertex_t ) * vtxPoints.size( );
		if ( pDevice->CreateVertexBuffer( sVertexSize, D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &pVertexBuffer, nullptr ) != D3D_OK )
			return;

		vertex_t* pVertices;

		if ( pVertexBuffer->Lock( NULL, NULL, reinterpret_cast< void** >( &pVertices ), NULL ) != D3D_OK )
		{
			pVertexBuffer->Unlock( );
			return;
		}

		for ( auto u = 0u; u < vtxPoints.size( ); u++ )
			pVertices[ u ] = vtxPoints[ u ];

		if ( pVertexBuffer->Unlock( ) != D3D_OK )
			return;

		if(	D3D_OK != pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE ) ||
			D3D_OK != pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) ||
			D3D_OK != pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA ) ||
			D3D_OK != pDevice->SetStreamSource( NULL, pVertexBuffer, NULL, sizeof( vertex_t ) ) )
			return;

		auto hr = pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2);
		pVertexBuffer->Release( );
	}
}
