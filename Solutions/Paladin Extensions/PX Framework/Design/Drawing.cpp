/// Drawing.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Drawing
{
	std::vector< polygon_t > vecPolygonList;
	std::vector< text_t > vecTextList;
	std::vector< line_t > vecLineList;
	IDirect3DVertexBuffer9* pVertexBuffer = nullptr;;
	LPD3DXSPRITE pTextSprite = nullptr;
	ID3DXLine* pLine = nullptr;

	bool PX_API InitializeDrawing( )
	{
		return D3D_OK == D3DXCreateFont( pDevice, 16, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
										 NONANTIALIASED_QUALITY, DEFAULT_PITCH, PX_XOR( L"Tahoma" ), &pFonts[ FONT_TAHOMA ] )
			&& D3D_OK == D3DXCreateFont( pDevice, 16, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
										 ANTIALIASED_QUALITY, DEFAULT_PITCH, PX_XOR( L"Roboto" ), &pFonts[ FONT_ROBOTO ] )
			&& D3D_OK == D3DXCreateSprite( pDevice, &pTextSprite )
			&& D3D_OK == D3DXCreateLine( pDevice, &pLine );
	}

	void PX_API Destruct( )
	{
		for( auto& font : pFonts )
			if( font )
			{
				font->Release( );
				font = nullptr;
			}

		if( pTextSprite )
		{
			pTextSprite->Release( );
			pTextSprite = nullptr;
		}

		if ( pLine )
		{
			pLine->Release( );
			pLine = nullptr;
		}
	}

	PX_EXT PX_INL void PX_API Polygon( vertex_t* pVertices, std::size_t zVertexCount, std::size_t zPrimitiveCount, D3DPRIMITIVETYPE ptDrawingType /*= D3DPT_TRIANGLEFAN*/ )
	{
		vecPolygonList.emplace_back( polygon_t( pVertices, zVertexCount, zPrimitiveCount, ptDrawingType ) );
	}

	PX_EXT PX_INL void PX_API Line( const D3DXVECTOR2* pPoints, std::size_t sPointCount, float flWidth, DWORD dwColor, BOOL bAntiAlias /*= TRUE*/ )
	{
		vecLineList.emplace_back( line_t( pPoints, sPointCount, flWidth, dwColor, bAntiAlias ) );
	}

	extern __forceinline void PX_API Text( ED3DFont iFont, int x, int y, const wchar_t *wszText, bool bOutlined, DWORD dwFlags, DWORD dwColor, DWORD dwOutline /*= 0*/ )
	{
		vecTextList.emplace_back( text_t( int( iFont ), x, y, wszText, bOutlined, dwFlags, dwColor, dwOutline ) );
	}

	extern __forceinline RECT PX_API GetTextSize( ED3DFont iFont, const wchar_t *wszText )
	{
		RECT recText { };

		if ( !pFonts[ int( iFont ) ] )
			return recText;
		pFonts[ int( iFont ) ]->DrawText( nullptr, wszText, -1, &recText, DT_CALCRECT, 0 );
		return recText;
	}

	void PX_API DrawQueue( )
	{
		for each ( auto& polPolygon in vecPolygonList )
		{
			const auto sVertexSize = sizeof( vertex_t ) * polPolygon.vecVertices.size( );
			if ( D3D_OK != pDevice->CreateVertexBuffer( sVertexSize, NULL, PX_CUSTOM_FVF, D3DPOOL_DEFAULT, &pVertexBuffer, nullptr ) )
			{
				pVertexBuffer->Release( );
				pVertexBuffer = nullptr;
				return;
			}

			void* pVertexMemory;
			pVertexBuffer->Lock( 0, sVertexSize, &pVertexMemory, 0 );
			memcpy( pVertexMemory, &polPolygon.vecVertices[ 0 ], sVertexSize );
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

			px_assert( D3D_OK == pDevice->DrawPrimitive( polPolygon.ptType, 0, polPolygon.sPrimitives ) );
			pVertexBuffer->Release( );
			pVertexBuffer = nullptr;
		}
		vecPolygonList.clear( );

		if ( pLine && pLine->Begin( ) == D3D_OK )
		{
			static auto flCurrentWidth = 0.f;
			static auto bCurrentlyAntiAliased = FALSE;
			auto bEndFinalLine = true;

			auto fnNewLine = [ ]( ID3DXLine*& pTargetLine, float flWidth, BOOL bAntiAlias )
			{
				return D3D_OK == pTargetLine->End( )
				 && D3D_OK == pTargetLine->SetWidth( flWidth )
				 && D3D_OK == pTargetLine->SetAntialias( bAntiAlias )
				 && D3D_OK == pTargetLine->Begin( );
			};

			for each ( auto& lnLine in vecLineList )
			{
				px_assert( lnLine.vecVertices.size( ) > 1 );
				if ( lnLine.flWidth != flCurrentWidth || lnLine.bAntiAlias != bCurrentlyAntiAliased )
					if ( !fnNewLine( pLine, lnLine.flWidth, lnLine.bAntiAlias ) )
					{
						bEndFinalLine = false;
						break;
					}
				px_assert( D3D_OK == pLine->Draw( &lnLine.vecVertices[ 0 ], lnLine.vecVertices.size( ), lnLine.dwColor ) );
			}
			if( bEndFinalLine )
				pLine->End( );
		}
		vecLineList.clear( );

		if ( pTextSprite && pTextSprite->Begin( D3DXSPRITE_ALPHABLEND ) == D3D_OK )
		{
			for ( auto& text : vecTextList )
			{
				if ( !pFonts[ text.iFont ] )
					continue;
				RECT recText { text.x - 1, text.y - 1, text.x, text.y };
				if ( text.bOutlined )
				{
					RECT recOutline[ ] { { text.x - 2l, text.y - 2l, text.x - 1l, text.y - 1l },
						{ text.x, text.y - 2l, text.x + 1l, text.y - 1l },
						{ text.x - 2l, text.y, text.x - 1l, text.y + 1l },
						{ text.x, text.y, text.x + 1l, text.y + 1l } };

					for ( auto& rect : recOutline )
						px_assert( NULL != pFonts[ text.iFont ]->DrawText( pTextSprite, text.wstrText.c_str( ), -1, &rect, text.dwFlags, text.dwOutline ) );
				}
				px_assert( NULL != pFonts[ text.iFont ]->DrawText( pTextSprite, text.wstrText.c_str( ), -1, &recText, text.dwFlags, text.dwColor ) );
			}
			pTextSprite->End( );
		}
		vecTextList.clear( );
	}
}
