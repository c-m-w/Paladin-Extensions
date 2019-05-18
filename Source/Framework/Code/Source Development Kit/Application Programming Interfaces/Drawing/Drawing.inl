/// Drawing.inl

#pragma once

template< typename _t > bool CDrawable< _t >::Create( )
{
	return false;
}

template< typename _t > void CDrawable< _t >::Draw( )
{ }

template< typename _t > void CDrawable< _t >::Destroy( )
{ }

inline bool CDrawable< vertex_t >::Create( )
{
	if ( bCreated )
		return true;

	D3D11_BUFFER_DESC _VertexBufferDescription { }, _IndexBufferDescription { };
	D3D11_SUBRESOURCE_DATA _VertexBufferData { }, _IndexBufferData { };

	_VertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	_VertexBufferDescription.ByteWidth = sizeof( vertex_t ) * vecVertices.size( );
	_VertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_VertexBufferDescription.CPUAccessFlags = 0;
	_VertexBufferDescription.MiscFlags = 0;
	_IndexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	_IndexBufferDescription.ByteWidth = sizeof( unsigned ) * vecIndices.size( );
	_IndexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	_IndexBufferDescription.CPUAccessFlags = 0;
	_IndexBufferDescription.MiscFlags = 0;
	_VertexBufferData.pSysMem = &vecVertices[ 0 ];
	_IndexBufferData.pSysMem = &vecIndices[ 0 ];

	return bCreated = SUCCEEDED( _Drawing.pDevice->CreateBuffer( &_VertexBufferDescription, &_VertexBufferData, &pVertexBuffer ) )
		&& SUCCEEDED( _Drawing.pDevice->CreateBuffer( &_IndexBufferDescription, &_IndexBufferData, &pIndexBuffer ) );
}

inline void CDrawable< vertex_t >::Draw( )
{
	if ( !Create( ) )
		return;

	auto uStride = sizeof( vertex_t ), uOffset = 0u;

	_Drawing.pContext->PSSetShader( pTexture == nullptr ? _Drawing.pStandardPixelShader : _Drawing.pTexturedPixelShader, nullptr, 0 );
	_Drawing.pContext->PSSetShaderResources( 0, 1, &pTexture );
	_Drawing.pContext->IASetIndexBuffer( pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	_Drawing.pContext->IASetVertexBuffers( 0, 1, &pVertexBuffer, &uStride, &uOffset );
	_Drawing.pContext->IASetPrimitiveTopology( _Topology );
	_Drawing.pContext->DrawIndexed( vecIndices.size( ), 0, 0 );
}

inline void CDrawable< vertex_t >::Destroy( )
{
	if ( pVertexBuffer != nullptr )
	{
		pVertexBuffer->Release( );
		pVertexBuffer = nullptr;
	}

	if ( pIndexBuffer != nullptr )
	{
		pIndexBuffer->Release( );
		pIndexBuffer = nullptr;
	}

	if ( pTexture != nullptr )
	{
		pTexture->Release( );
		pTexture = nullptr;
	}

	if ( pRenderedTexture != nullptr )
	{
		pRenderedTexture->Release( );
		pRenderedTexture = nullptr;
	}

	bCreated = false;
}

inline void CDrawable< vertex_t >::SetDrawingType( D3D_PRIMITIVE_TOPOLOGY _New )
{
	_Topology = _New;
}

inline void CDrawable< vertex_t >::SetTexture( const std::string &strResourceName )
{
	const auto& strData = _ResourceManager.GetResource( strResourceName );

	if ( pTexture != nullptr )
		pTexture->Release( );

	pTexture = nullptr;
	D3DX11CreateShaderResourceViewFromMemory( _Drawing.pDevice, &strData[ 0 ], strData.size( ), nullptr, nullptr, &pTexture, nullptr );
}

inline void CDrawable< vertex_t >::SetTexture( const bitmap_t& _Bitmap, const color_t& clrText )
{
	const auto vecBytes = _Bitmap.GetColoredBitmapBytes( clrText.GetRGBA( ) );
	D3D11_TEXTURE2D_DESC _TextureDescription { };
	D3D11_SUBRESOURCE_DATA _ResourceData { };
	ID3D11Texture2D* pBufferTexture = nullptr;
	D3D11_SHADER_RESOURCE_VIEW_DESC _ShaderResourceViewDescription { };

	_TextureDescription.Width = std::size_t( _Bitmap.vecSize.x );
	_TextureDescription.Height = std::size_t( _Bitmap.vecSize.y );
	_TextureDescription.MipLevels = 1;
	_TextureDescription.ArraySize = 1;
	_TextureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_TextureDescription.SampleDesc.Count = 1;
	_TextureDescription.SampleDesc.Quality = 0;
	_TextureDescription.Usage = D3D11_USAGE_DEFAULT;
	_TextureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	_TextureDescription.CPUAccessFlags = 0;
	_TextureDescription.MiscFlags = 0;

	_ResourceData.pSysMem = &vecBytes[ 0 ];
	_ResourceData.SysMemPitch = std::size_t( _Bitmap.vecSize.x ) * sizeof( DWORD );
	_ResourceData.SysMemSlicePitch = vecBytes.size( ) * sizeof( DWORD );

	_Drawing.pDevice->CreateTexture2D( &_TextureDescription, &_ResourceData, &pBufferTexture );

	_ShaderResourceViewDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_ShaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	_ShaderResourceViewDescription.Texture2D.MostDetailedMip = 0;
	_ShaderResourceViewDescription.Texture2D.MipLevels = 1;

	_Drawing.pDevice->CreateShaderResourceView( pBufferTexture, &_ShaderResourceViewDescription, &pTexture );
	Rectangle( rectangle_t { 0, 0, _Bitmap.vecSize.x , _Bitmap.vecSize.y }, color_t { 255, 255, 255, 255 } );
}

inline void CDrawable< vertex_t >::SetTexture( const bitmap_t& _Bitmap, ID3D11Texture2D* pColorTexture )
{
	return;
	auto vecBytes = _Bitmap.GetColoredBitmapBytes( 0xFFFFFFFF );
	D3D11_TEXTURE2D_DESC _ColorTextureDescription { };
	D3D11_MAPPED_SUBRESOURCE _TextureData { };
	D3D11_TEXTURE2D_DESC _TextureDescription { };
	D3D11_SUBRESOURCE_DATA _ResourceData { };
	ID3D11Texture2D* pBufferTexture = nullptr;
	D3D11_SHADER_RESOURCE_VIEW_DESC _ShaderResourceViewDescription { };

	pColorTexture->GetDesc( &_ColorTextureDescription );

	if ( _ColorTextureDescription.Width != std::size_t( _Bitmap.vecSize.x )
		 || _ColorTextureDescription.Height != std::size_t( _Bitmap.vecSize.y ) )
		return;

	//_ColorTextureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//_ColorTextureDescription.Usage = D3D11_USAGE_DYNAMIC;
	//_ColorTextureDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	auto hr = _Drawing.pContext->Map( pColorTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &_TextureData );

	for ( auto z = 0u; z < vecBytes.size( ); z++ )
	{
		const auto dwARGB = reinterpret_cast< DWORD* >( _TextureData.pData )[ z ];
		const auto bAlpha = unsigned char( double( vecBytes[ z ] ) / 255.0 * ( dwARGB & 0xFF ) );
		if ( bAlpha > 0 )
			vecBytes[ z ] = ( dwARGB & 0x00FFFFFF ) | ( bAlpha << 24 );
	}

	_Drawing.pContext->Unmap( pColorTexture, 0 );

	_TextureDescription.Width = std::size_t( _Bitmap.vecSize.x );
	_TextureDescription.Height = std::size_t( _Bitmap.vecSize.y );
	_TextureDescription.MipLevels = 1;
	_TextureDescription.ArraySize = 1;
	_TextureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_TextureDescription.SampleDesc.Count = 1;
	_TextureDescription.SampleDesc.Quality = 0;
	_TextureDescription.Usage = D3D11_USAGE_DEFAULT;
	_TextureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	_TextureDescription.CPUAccessFlags = 0;
	_TextureDescription.MiscFlags = 0;

	_ResourceData.pSysMem = &vecBytes[ 0 ];
	_ResourceData.SysMemPitch = std::size_t( _Bitmap.vecSize.x ) * sizeof( DWORD );
	_ResourceData.SysMemSlicePitch = vecBytes.size( ) * sizeof( DWORD );

	_Drawing.pDevice->CreateTexture2D( &_TextureDescription, &_ResourceData, &pBufferTexture );

	_ShaderResourceViewDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_ShaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	_ShaderResourceViewDescription.Texture2D.MostDetailedMip = 0;
	_ShaderResourceViewDescription.Texture2D.MipLevels = 1;

	_Drawing.pDevice->CreateShaderResourceView( pBufferTexture, &_ShaderResourceViewDescription, &pTexture );
	Rectangle( rectangle_t { 0, 0, _Bitmap.vecSize.x , _Bitmap.vecSize.y }, color_t { 255, 255, 255, 255 } );
}

inline void CDrawable< vertex_t >::RemoveTexture( )
{
	pTexture->Release( );
	pTexture = nullptr;
}

inline void CDrawable< vertex_t >::Rectangle( rectangle_t recLocation, color_t clrColor )
{
	vecVertices =
	{
		vertex_t( vertex_t::PixelToRatio( { recLocation.x, recLocation.y } ), { 0.0, 0.0 }, clrColor ),
		vertex_t( vertex_t::PixelToRatio( { recLocation.x + recLocation.w, recLocation.y } ), { 1.0, 0.0 }, clrColor ),
		vertex_t( vertex_t::PixelToRatio( { recLocation.x + recLocation.w, recLocation.y + recLocation.h } ), { 1.0, 1.0 }, clrColor ),
		vertex_t( vertex_t::PixelToRatio( { recLocation.x, recLocation.y + recLocation.h } ), { 0.0, 1.0 }, clrColor )
	};
	vecIndices =
	{
		3, 0, 1,
		3, 2, 1
	};

	DestroyBuffers( );
}

inline void CDrawable< vertex_t >::Rectangle( rectangle_t recLocation, color_t *clrColor )
{
	vecVertices =
	{
		vertex_t( vertex_t::PixelToRatio( { recLocation.x, recLocation.y } ), clrColor[ rectangle_t::TOP_LEFT ] ),
		vertex_t( vertex_t::PixelToRatio( { recLocation.x + recLocation.w, recLocation.y } ), clrColor[ rectangle_t::TOP_RIGHT ] ),
		vertex_t( vertex_t::PixelToRatio( { recLocation.x + recLocation.w, recLocation.y + recLocation.h } ), clrColor[ rectangle_t::BOTTOM_RIGHT ] ),
		vertex_t( vertex_t::PixelToRatio( { recLocation.x, recLocation.y + recLocation.h } ), clrColor[ rectangle_t::BOTTOM_LEFT ] )
	};
	vecIndices =
	{
		3, 0, 1,
		3, 2, 1
	};

	DestroyBuffers( );
}

inline void CDrawable< vertex_t >::RoundedRectangle( rectangle_t recLocation, bool bLeftRounding, bool bRightRounding, color_t clrColor, double dbRoundingWidth )
{
	const auto vecBase = Utilities::vector2_t::GetCirclePoints( dbRoundingWidth, std::size_t( dbRoundingWidth ), 0.0, 0.25 );

}

inline void CDrawable< vertex_t >::Line( Utilities::vector2_t vecStart, Utilities::vector2_t vecEnd, double dThickness, color_t clrColor )
{
	const auto vecLength = vecEnd - vecStart;
	const auto dwColor = clrColor.GetARGB( );
	const auto dLength = vecLength.Length( );
	const auto dRotation = vecLength.Angle( );
	
	vecVertices = decltype( vecVertices )
	{
		vertex_t( vertex_t::PixelToRatio( { vecStart.x, vecStart.y - dThickness / 2.0 } ), dwColor ),
		vertex_t( vertex_t::PixelToRatio( { vecStart.x + dLength, vecStart.y - dThickness / 2.0 } ), dwColor ),
		vertex_t( vertex_t::PixelToRatio( { vecStart.x + dLength, vecStart.y + dThickness / 2.0 } ), dwColor ),
		vertex_t( vertex_t::PixelToRatio( { vecStart.x, vecStart.y + dThickness / 2.0 } ), dwColor )
	};
	
	for ( auto &_Vertex: vecVertices )
		_Vertex.Rotate( dRotation, vecStart );

	DestroyBuffers( );
}

inline void CDrawable< vertex_t >::Circle( const Utilities::vector2_t& vecCenter, double dbRadius, color_t clrColor, std::size_t zResolution /*= 0*/ )
{
	if ( zResolution <= 2u )
		zResolution = std::size_t( std::round( dbRadius * 2.0 * Utilities::vector2_t::PI ) );

	auto vecPoints = Utilities::vector2_t::GetCirclePoints( dbRadius, zResolution );
	const auto zSize = vecPoints.size( );

	vecVertices.clear( );
	vecIndices.clear( );
	vecVertices.emplace_back( vertex_t::PixelToRatio( vecCenter ), clrColor );
	vecVertices.emplace_back( vertex_t::PixelToRatio( vecPoints[ 0 ] + vecCenter ), clrColor );

	for ( auto z = 1u; z < zSize; z++ )
	{
		vecVertices.emplace_back( vertex_t::PixelToRatio( vecPoints[ z ] + vecCenter ), clrColor );
		vecIndices.emplace_back( 0 );
		vecIndices.emplace_back( z - 1 );
		vecIndices.emplace_back( z );
	}

	vecVertices.emplace_back( vecVertices.front( ) );
	vecIndices.emplace_back( 0 );
	vecIndices.emplace_back( 1 );
	vecIndices.emplace_back( zSize - 1 );

	DestroyBuffers( );
}

inline void CDrawable< vertex_t >::Circle( const Utilities::vector2_t& vecCenter, double dbRadius, color_t clrPerimeter, color_t clrCenter, std::size_t zResolution /*= 0*/ )
{
	Circle( vecCenter, dbRadius, clrPerimeter, zResolution );
	auto& _Vertex = vecVertices.front( );
	_Vertex = vertex_t( { _Vertex.x, _Vertex.y }, clrCenter );
}

inline void CDrawable< vertex_t >::DestroyBuffers( )
{
	if ( pVertexBuffer != nullptr )
	{
		pVertexBuffer->Release( );
		pVertexBuffer = nullptr;
	}

	if ( pIndexBuffer != nullptr )
	{
		pIndexBuffer->Release( );
		pIndexBuffer = nullptr;
	}
}

inline ID3D11Texture2D *CDrawable< vertex_t >::RenderToTexture( )
{
	if ( pRenderedTexture )
		return pRenderedTexture;

	Utilities::vector2_t vecMin { DBL_MAX, DBL_MAX }, vecMax { };
	D3D11_TEXTURE2D_DESC _TextureBufferDescription { }, _TextureDescription { };
	ID3D11Texture2D* pRenderedTextureBuffer = nullptr;
	D3D11_RENDER_TARGET_VIEW_DESC _RenderTargetViewDescription { };
	ID3D11RenderTargetView* pNewRenderTarget = nullptr;

	for ( auto& _Vertex : vecVertices )
	{
		const auto vecLocation = vertex_t::RatioToPixel( { double( _Vertex.x ), double( _Vertex.y ) } );

		vecMin.x = std::min( vecMin.x, vecLocation.x );
		vecMin.y = std::min( vecMin.y, vecLocation.y );
		vecMax.x = std::max( vecMax.x, vecLocation.x );
		vecMax.y = std::max( vecMax.y, vecLocation.y );
	}

	_TextureBufferDescription.Width = int( vecMax.x - vecMin.x );
	_TextureBufferDescription.Height = int( vecMax.y - vecMin.y );
	_TextureBufferDescription.MipLevels = 1;
	_TextureBufferDescription.ArraySize = 1;
	_TextureBufferDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_TextureBufferDescription.SampleDesc.Count = 1;
	_TextureBufferDescription.SampleDesc.Quality = 0;
	_TextureBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	_TextureBufferDescription.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	_TextureBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	_TextureBufferDescription.MiscFlags = 0;

	_TextureDescription.Width = int( vecMax.x - vecMin.x );
	_TextureDescription.Height = int( vecMax.y - vecMin.y );
	_TextureDescription.MipLevels = 1;
	_TextureDescription.ArraySize = 1;
	_TextureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_TextureDescription.SampleDesc.Count = 1;
	_TextureDescription.SampleDesc.Quality = 0;
	_TextureDescription.Usage = D3D11_USAGE_DYNAMIC;
	_TextureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	_TextureDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_TextureDescription.MiscFlags = 0;

	_RenderTargetViewDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	_RenderTargetViewDescription.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	_RenderTargetViewDescription.Texture2D.MipSlice = 0;

	_Drawing.pDevice->CreateTexture2D( &_TextureBufferDescription, nullptr, &pRenderedTextureBuffer );
	_Drawing.pDevice->CreateTexture2D( &_TextureDescription, nullptr, &pRenderedTexture );
	_Drawing.pDevice->CreateRenderTargetView( pRenderedTextureBuffer, nullptr, &pNewRenderTarget );
	_Drawing.pContext->OMSetRenderTargets( 1, &pNewRenderTarget, _Drawing.pDepthStencilView );
	_Drawing.pContext->ClearRenderTargetView( pNewRenderTarget, D3DXCOLOR( 0.f, 0.f, 0.f, 0.f ) );
	Draw( );
	_Drawing.pContext->OMSetRenderTargets( 1, &_Drawing.pRenderTargetView, _Drawing.pDepthStencilView );
	_Drawing.pContext->CopyResource( pRenderedTexture, pRenderedTextureBuffer );
	pNewRenderTarget->Release( );

	return pRenderedTexture;
}

