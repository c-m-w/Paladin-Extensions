/// Drawing.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Drawing
{
	IDirect3DVertexBuffer9* pVertexBuffer = nullptr;;
	ID3DXLine* pLine;

	std::vector< polygon_t > vecPolygonList;
	std::vector< line_t > vecLineList;

	void PX_API Polygon( vertex_t* pVertices, std::size_t zVertexCount, std::size_t zPrimitiveCount, D3DPRIMITIVETYPE ptDrawingType /*= D3DPT_TRIANGLEFAN*/ )
	{
		vecPolygonList.emplace_back( polygon_t( pVertices, zVertexCount, zPrimitiveCount, ptDrawingType ) );
	}

	void PX_API Line( const D3DXVECTOR2* pPoints, std::size_t sPointCount, float flWidth, DWORD dwColor, BOOL bAntiAlias /*= TRUE*/ )
	{
		vecLineList.emplace_back( line_t( pPoints, sPointCount, flWidth, dwColor, bAntiAlias ) );
	}

	void PX_API DrawFigures( )
	{
		for( auto& polygon : vecPolygonList )
		{
			const auto sVertexSize = sizeof( vertex_t ) * polygon.vecVertices.size( );
			if ( D3D_OK != pDevice->CreateVertexBuffer( sVertexSize, NULL, PX_CUSTOM_FVF, D3DPOOL_DEFAULT, &pVertexBuffer, nullptr ) )
			{
				pVertexBuffer->Release( );
				pVertexBuffer = nullptr;
				return;
			}

			void* pVertexMemory;
			pVertexBuffer->Lock( 0, sVertexSize, &pVertexMemory, 0 );
			memcpy( pVertexMemory, &polygon.vecVertices[ 0 ], sVertexSize );
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
				continue;
			}

			px_assert( D3D_OK == pDevice->DrawPrimitive( polygon.ptType, 0, polygon.sPrimitives ) );
			pVertexBuffer->Release( );
			pVertexBuffer = nullptr;
		}
		vecPolygonList.clear( );

		if ( D3D_OK == D3DXCreateLine( pDevice, &pLine ) )
		{
			for ( auto& line : vecLineList )
			{
				px_assert( line.vecVertices.size( ) > 1 );
				if ( D3D_OK != pLine->SetWidth( line.flWidth )
					 || D3D_OK != pLine->SetAntialias( line.bAntiAlias )
					 || D3D_OK != pLine->Begin( ) )
					break;
				px_assert( D3D_OK == pLine->Draw( &line.vecVertices[ 0 ], line.vecVertices.size( ), line.dwColor ) );
				pLine->End( );
			}
			pLine->Release( );
			pLine = nullptr;
		}
		vecLineList.clear																											( );
	}
}
