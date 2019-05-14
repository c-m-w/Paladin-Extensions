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
	if ( !bCreated )
		return;

	pVertexBuffer->Release( );
	pVertexBuffer = nullptr;
	bCreated = false;
}

inline void CDrawable< vertex_t >::SetDrawingType( D3D_PRIMITIVE_TOPOLOGY _New )
{
	_Topology = _New;
}

inline void CDrawable< vertex_t >::AddTexture( const std::string &strResourceName )
{
	const auto pResourceData = &_ResourceManager.GetResource( strResourceName )[ 0 ];
	//...
}

inline void CDrawable< vertex_t >::RemoveTexture( )
{
	pTexture->Release( );
	pTexture = nullptr;
}

inline void CDrawable< vertex_t >::Rectangle( rectangle_t recLocation, color_t clrColor )
{
	const auto dwColor = clrColor.GetARGB( );

	vecVertices =
	{
		vertex_t( { recLocation.x, recLocation.y + recLocation.h }, dwColor ),
		vertex_t( { recLocation.x, recLocation.y }, dwColor ),
		vertex_t( { recLocation.x + recLocation.w, recLocation.y }, dwColor ),
		vertex_t( { recLocation.x + recLocation.w, recLocation.y + recLocation.h }, dwColor )
	};
	vecIndices =
	{
		0, 1, 2,
		0, 2, 3
	};

	Destroy( );
}

inline void CDrawable< vertex_t >::Rectangle( rectangle_t recLocation, color_t *clrColor )
{
	auto test = vertex_t::RatioToPixel( { -0.964285731, 0.923076928 } );
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

	Destroy( );
}

inline void CDrawable< vertex_t >::Line( Utilities::vector2_t vecStart, Utilities::vector2_t vecEnd, double dThickness, color_t clrColor )
{
	const auto vecLength = vecEnd - vecStart;
	const auto dwColor = clrColor.GetARGB( );
	const auto dLength = vecLength.Length( );
	auto dRotation = vecLength.Angle( );
	
	vecVertices = decltype( vecVertices )
	{
		vertex_t( vertex_t::PixelToRatio( { vecStart.x, vecStart.y - dThickness / 2.0 } ), dwColor ),
		vertex_t( vertex_t::PixelToRatio( { vecStart.x + dLength, vecStart.y - dThickness / 2.0 } ), dwColor ),
		vertex_t( vertex_t::PixelToRatio( { vecStart.x + dLength, vecStart.y + dThickness / 2.0 } ), dwColor ),
		vertex_t( vertex_t::PixelToRatio( { vecStart.x, vecStart.y + dThickness / 2.0 } ), dwColor )
	};
	
	for ( auto &_Vertex: vecVertices )
		_Vertex.Rotate( dRotation, vecStart );

	Destroy( );
}
