/// Drawing.inl

#pragma once

template< typename _t > bool CDrawing::CDrawable<_t>::Create( )
{
	return false;
}

template< typename _t > void CDrawing::CDrawable<_t>::Draw( )
{ }

template< typename _t > void CDrawing::CDrawable<_t>::Destroy( )
{ }

inline bool CDrawing::CDrawable<CDrawing::vertex_t>::Create( )
{
	if ( bCreated )
		return true;

	return bCreated = _Drawing.ConstructPolygon( &vecVertices[ 0 ], vecVertices.size( ) ) != nullptr;
}

inline void CDrawing::CDrawable< CDrawing::vertex_t >::Draw( )
{
	if ( !Create( ) )
		return;

	if ( D3D_OK == _Drawing.pDevice->SetStreamSource( NULL, pVertexBuffer, NULL, sizeof( vertex_t ) ) )
		_Drawing.pDevice->DrawPrimitive( _DrawType, 0, zPrimitives ), _Drawing.pDevice->SetStreamSource( NULL, nullptr, NULL, 0 );
}

inline void CDrawing::CDrawable<CDrawing::vertex_t>::Destroy( )
{
	if ( !bCreated )
		return;

	pVertexBuffer->Release( );
	pVertexBuffer = nullptr;
	bCreated = false;
}

inline void CDrawing::CDrawable<CDrawing::vertex_t>::SetDrawingType( D3DPRIMITIVETYPE _New )
{
	_DrawType = _New;
}

inline void CDrawing::CDrawable<CDrawing::vertex_t>::Rectangle( rectangle_t recLocation, color_t clrColor )
{
	const auto dwColor = clrColor.GetARGB( );
	
	vecVertices = decltype( vecVertices )
	{
		vertex_t( recLocation.x, recLocation.y, dwColor ),
		vertex_t( recLocation.x + recLocation.w, recLocation.y, dwColor ),
		vertex_t( recLocation.x + recLocation.w, recLocation.y + recLocation.h, dwColor ),
		vertex_t( recLocation.x, recLocation.y + recLocation.h, dwColor )
	};
	zPrimitives = 2;

	Destroy( );
}

inline void CDrawing::CDrawable<CDrawing::vertex_t>::Rectangle( rectangle_t recLocation, color_t *clrColor )
{
	vecVertices = decltype( vecVertices )
	{
		vertex_t( recLocation.x, recLocation.y, clrColor[ rectangle_t::TOP_LEFT ].GetARGB( ) ),
		vertex_t( recLocation.x + recLocation.w, recLocation.y, clrColor[ rectangle_t::TOP_RIGHT ].GetARGB( ) ),
		vertex_t( recLocation.x + recLocation.w, recLocation.y + recLocation.h, clrColor[ rectangle_t::BOTTOM_RIGHT ].GetARGB( ) ),
		vertex_t( recLocation.x, recLocation.y + recLocation.h, clrColor[ rectangle_t::BOTTOM_LEFT ].GetARGB( ) )
	};
	zPrimitives = 2;

	Destroy( );
}

inline void CDrawing::CDrawable<CDrawing::vertex_t>::Line( Utilities::vector2_t vecStart, Utilities::vector2_t vecEnd, float flThickness, color_t clrColor )
{
	const auto vecLength = vecEnd - vecStart;
	const auto dwColor = clrColor.GetARGB( );
	const auto dLength = vecLength.Length( );
	const auto vecRotationPoint = D3DXVECTOR2( vecStart );
	auto dRotation = vecLength.Angle( );
	
	vecVertices = decltype( vecVertices )
	{
		vertex_t( vecStart.x, vecStart.y - flThickness / 2.0, dwColor ),
		vertex_t( vecStart.x + dLength, vecStart.y - flThickness / 2.0, dwColor ),
		vertex_t( vecStart.x + dLength, vecStart.y + flThickness / 2.0, dwColor ),
		vertex_t( vecStart.x, vecStart.y + flThickness / 2.0, dwColor )
	};
	
	if ( vecLength.x < 0.0 )
	{
		if ( vecLength.y < 0.0 || vecLength.y == 0.0 )
			dRotation += 180.0;
		else
			dRotation = 180.0 - std::abs( dRotation );
	}
	
	for ( auto &vecVertex: vecVertices )
		vecVertex.Rotate( dRotation, vecRotationPoint );

	Destroy( );
}

inline CDrawing::CDrawable< std::string >::CDrawable( const std::string &strText, int iFont, int iSize, int iHorizontalAlignment, int iVerticalAlignment, const color_t& clrText, EFontFlags ffFlags ) :
	strText( strText ), iFont( iFont ), iSize( iSize ), iHorizontalAlignment( iHorizontalAlignment ), iVerticalAlignment( iVerticalAlignment ), clrText( clrText ), ffFlags( ffFlags )
{ }

inline bool CDrawing::CDrawable< std::string >::Create( )
{
	if ( bCreated )
		return true;

	return bCreated = ( pTexture = _Drawing.CreateTextTexture( strText.c_str( ), iSize, iFont, clrText, vecDimensions, ffFlags ) ) != nullptr;
}

inline void CDrawing::CDrawable< std::string >::Draw( )
{
	if ( !Create( ) )
		return;

	_Drawing.DrawTexture( pTexture, vecDrawingLocation );
}

inline void CDrawing::CDrawable< std::string >::Destroy( )
{
	if ( !bCreated )
		return;

	pTexture->Release( );
	pTexture = nullptr;
	bCreated = false;
}

inline void CDrawing::CDrawable< std::string >::SetDrawingLocation( const Utilities::vector2_t& vecNew )
{
	vecDrawingLocation = vecNew;
}

inline void CDrawing::CDrawable< std::string >::SetDrawingLocation( const rectangle_t &recUsableSpace )
{
	switch ( iHorizontalAlignment )
	{
		case LEFT:
		{
			vecDrawingLocation.x = recUsableSpace.x;
		}
		break;

		case CENTER:
		{
			vecDrawingLocation.x = recUsableSpace.x + recUsableSpace.w / 2.0 - GetWidth( ) / 2.0;
		}
		break;

		case RIGHT:
		{
			vecDrawingLocation.x = recUsableSpace.x + recUsableSpace.w - GetWidth( );
		}
		break;

		default:
			return;
	}

	switch ( iVerticalAlignment )
	{
		case TOP:
		{
			vecDrawingLocation.y = recUsableSpace.y;
		}
		break;

		case CENTER:
		{
			vecDrawingLocation.y = recUsableSpace.y + recUsableSpace.h / 2.0 - GetHeight( ) / 2.0;
		}
		break;

		case BOTTOM:
		{
			vecDrawingLocation.y = recUsableSpace.y + recUsableSpace.h - GetHeight( );
		}
		break;

		default:
			return;
	}
}

inline double CDrawing::CDrawable< std::string >::GetWidth( )
{
	return vecDimensions.x;
}

inline double CDrawing::CDrawable< std::string >::GetHeight( )
{
	return vecDimensions.y;
}

inline CDrawing::CDrawable< CDrawing::texture_t >::CDrawable( const texture_t &_TextureInfo ) :
	_TextureInfo( _TextureInfo )
{ }

inline bool CDrawing::CDrawable< CDrawing::texture_t >::Create( )
{
	if ( bCreated )
		return true;

	auto& strTextureData = _ResourceManager.GetResource( _TextureInfo.strFileName );

	if ( !( bCreated = D3D_OK == D3DXCreateTextureFromFileInMemoryEx( _Drawing.pDevice, &strTextureData[ 0 ], strTextureData.length( ), _TextureInfo.vecDimensions.x, _TextureInfo.vecDimensions.y, D3DX_FROM_FILE,
		D3DUSAGE_DYNAMIC, D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &_ImageInfo,
		nullptr, &pTexture ) ) )
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Unable to create texture %s from memory." ), _TextureInfo.strFileName.c_str( ) );

	return bCreated;
}

inline void CDrawing::CDrawable< CDrawing::texture_t >::Draw( )
{
	if ( !Create( ) )
		return;

	_Drawing.DrawTexture( pTexture, vecDrawingLocation );
}

inline void CDrawing::CDrawable< CDrawing::texture_t >::Destroy( )
{
	if ( !bCreated )
		return;

	pTexture->Release( );
	pTexture = nullptr;
	bCreated = false;
}

inline void CDrawing::CDrawable<CDrawing::texture_t>::SetDrawingLocation( const Utilities::vector2_t &vecNew )
{
	vecDrawingLocation = vecNew;
}
