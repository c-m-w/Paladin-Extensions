/// Drawing.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../../Framework.hpp"

rectangle_t::rectangle_t( double x, double y, double w, double h ): vecLocation( x, y ), vecSize( w, h )
{ }

rectangle_t::rectangle_t( RECT recNew )
{
	*this = rectangle_t( float( recNew.left ), float( recNew.top ), float( recNew.right - recNew.left ), float( recNew.bottom - recNew.top ) );
}

rectangle_t& rectangle_t::operator=( const RECT &rhs )
{
	return *this = rectangle_t( rhs );
}

rectangle_t rectangle_t::operator+( const rectangle_t &rhs )
{
	return rectangle_t( x + rhs.x, y + rhs.y, w, h );
}

rectangle_t rectangle_t::operator-( const rectangle_t &rhs )
{
	return rectangle_t( x - rhs.x, y - rhs.y, w, h );
}

rectangle_t rectangle_t::operator*( const rectangle_t &rhs )
{
	return rectangle_t( x * rhs.x, y * rhs.y, w, h );
}

rectangle_t rectangle_t::operator/( const rectangle_t &rhs )
{
	return rectangle_t( x / rhs.x, y / rhs.y, w, h );
}

void rectangle_t::operator+=( const rectangle_t & rhs )
{
	x += rhs.x;
	y += rhs.y;
}

void rectangle_t::operator-=( const rectangle_t & rhs )
{
	x -= rhs.x;
	y -= rhs.y;
}

void rectangle_t::operator*=( double rhs )
{
	x *= rhs;
	y *= rhs;
}

void rectangle_t::operator/=( double rhs )
{
	x /= rhs;
	y /= rhs;
}

double rectangle_t::GetX( ) const
{
	return vecLocation.x;
}

double rectangle_t::GetY( ) const
{
	return vecLocation.y;
}

double rectangle_t::GetW( ) const
{
	return vecSize.x;
}

double rectangle_t::GetH( ) const
{
	return vecSize.y;
}

void rectangle_t::PutX( double x )
{
	vecLocation.x = x;
}

void rectangle_t::PutY( double y )
{
	vecLocation.y = y;
}

void rectangle_t::PutW( double w )
{
	vecSize.x = w;
}

void rectangle_t::PutH( double h )
{
	vecSize.y = h;
}

void rectangle_t::Clamp( const rectangle_t & recClamp )
{
	if ( x < recClamp.x )
		x = recClamp.x;

	if ( y < recClamp.y )
		y = recClamp.y;

	while ( x + w > recClamp.x + recClamp.w )
		w -= 1.0;

	while ( y + h > recClamp.y + recClamp.h )
		h -= 1.0;
}

bool rectangle_t::LocationInRectangle( const vector2_t & locLocation ) const
{
	return locLocation.x >= x
		&& locLocation.x <= x + w
		&& locLocation.y >= y
		&& locLocation.y <= y + h;
}

bool rectangle_t::InRectangle( const rectangle_t & recLocation ) const
{
	return recLocation.LocationInRectangle( vector2_t( x, y ) )
		|| recLocation.LocationInRectangle( vector2_t( x + w, y ) )
		|| recLocation.LocationInRectangle( vector2_t( x + w, y + h ) )
		|| recLocation.LocationInRectangle( vector2_t( x, y + h ) );
}

RECT rectangle_t::ToRect( ) const
{
	return { int( x ), int( y ), int( x + w ), int( y + h ) };
}


vector2_t vertex_t::PixelToRatio( const vector2_t & vecLocation )
{
	return { std::round( vecLocation.x ) * 2.0 / _Drawing.recRenderTarget.w - 1.0,
			std::round( vecLocation.y ) * -2.0 / _Drawing.recRenderTarget.h + 1.0 };
}

vector2_t vertex_t::RatioToPixel( const vector2_t & vecRatio )
{
	return { std::round( ( vecRatio.x + 1.0 ) * _Drawing.recRenderTarget.w / 2.0 ),
			std::round( ( vecRatio.y - 1.0 ) * _Drawing.recRenderTarget.h / -2.0 ) };
}

vertex_t::vertex_t( const vector2_t & vecRatio, color_t clrVertex ):
	x( float( vecRatio.x ) ), y( float( vecRatio.y ) ), clrVertex( clrVertex.rfl, clrVertex.gfl, clrVertex.bfl, clrVertex.afl )
{ }

vertex_t::vertex_t( const vector2_t & vecRatio, const vector2_t & vecTextureRatio, color_t clrVertex ) :
	x( float( vecRatio.x ) ), y( float( vecRatio.y ) ), u( float( vecTextureRatio.x ) ), v( float( vecTextureRatio.y ) ),
	clrVertex( clrVertex.rfl, clrVertex.gfl, clrVertex.bfl, clrVertex.afl )
{ }

void vertex_t::Rotate( double dAngle, const vector2_t & vecRotationPoint )
{
	auto vecCurrent = RatioToPixel( vector2_t( double( x ), double( y ) ) );

	vecCurrent.Rotate( dAngle, vecRotationPoint );
	const auto vecNew = PixelToRatio( vecCurrent );

	x = float( vecNew.x );
	y = float( vecNew.y );
}

bool CDrawable::Create( )
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

void CDrawable::Draw( )
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

void CDrawable::Destroy( )
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

void CDrawable::SetDrawingType( D3D_PRIMITIVE_TOPOLOGY _New )
{
	_Topology = _New;
}

void CDrawable::SetTexture( const std::string& strResourceName )
{
	const auto& strData = _ResourceManager.GetResource( strResourceName );

	if ( pTexture != nullptr )
		pTexture->Release( );

	pTexture = nullptr;
	D3DX11CreateShaderResourceViewFromMemory( _Drawing.pDevice, &strData[ 0 ], strData.size( ), nullptr, nullptr, &pTexture, nullptr );
}

void CDrawable::SetTexture( ID3D11Texture2D * pNewTexture )
{
	if ( pTexture != nullptr )
		pTexture->Release( );

	D3D11_TEXTURE2D_DESC _TextureDescription { };
	D3D11_SHADER_RESOURCE_VIEW_DESC _ShaderResourceViewDescription { };

	_ShaderResourceViewDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_ShaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	_ShaderResourceViewDescription.Texture2D.MostDetailedMip = 0;
	_ShaderResourceViewDescription.Texture2D.MipLevels = 1;
	_Drawing.pDevice->CreateShaderResourceView( pNewTexture, &_ShaderResourceViewDescription, &pTexture );
}


void CDrawable::SetTexture( const bitmap_t & _Bitmap, const color_t & clrText )
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

void CDrawable::SetTexture( const bitmap_t & _Bitmap, ID3D11Texture2D* pColorTexture )
{
	auto vecBytes = _Bitmap.GetColoredBitmapBytes( 0xFFFFFFFF );
	D3D11_TEXTURE2D_DESC _ColorTextureDescription { };
	ID3D11Texture2D* pCopiedTexture = nullptr;
	D3D11_MAPPED_SUBRESOURCE _TextureData { };
	D3D11_TEXTURE2D_DESC _TextureDescription { };
	D3D11_SUBRESOURCE_DATA _ResourceData { };
	ID3D11Texture2D* pBufferTexture = nullptr;
	D3D11_SHADER_RESOURCE_VIEW_DESC _ShaderResourceViewDescription { };

	pColorTexture->GetDesc( &_ColorTextureDescription );

	if ( _ColorTextureDescription.Width < std::size_t( _Bitmap.vecSize.x )
		 || _ColorTextureDescription.Height < std::size_t( _Bitmap.vecSize.y ) )
		return;

	_ColorTextureDescription.BindFlags = 0;
	_ColorTextureDescription.Usage = D3D11_USAGE_STAGING;
	_ColorTextureDescription.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	_Drawing.pDevice->CreateTexture2D( &_ColorTextureDescription, nullptr, &pCopiedTexture );
	_Drawing.pContext->CopyResource( pCopiedTexture, pColorTexture );
	auto hr = _Drawing.pContext->Map( pCopiedTexture, 0, D3D11_MAP_READ, 0, &_TextureData );

	for ( auto y = 0u; y < std::size_t( _Bitmap.vecSize.y ); y++ )
		for ( auto x = 0u; x < std::size_t( _Bitmap.vecSize.x ); x++ )
		{
			const auto dwABGR = reinterpret_cast< DWORD* >( _TextureData.pData )[ y * _TextureData.RowPitch / sizeof( DWORD ) + x ];
			auto& dwCurrent = vecBytes[ _Bitmap.GetBitIndex( x, y ) ];
			const auto bAlpha = unsigned char( double( dwCurrent >> 24 & 0xFF ) / 255.0 * double( dwABGR >> 24 ) );
			dwCurrent = dwABGR & 0x00FFFFFF | bAlpha << 24;
		}

	_Drawing.pContext->Unmap( pCopiedTexture, 0 );
	pCopiedTexture->Release( );

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

void CDrawable::SetTexture( const bitmap_t &_Bitmap, const std::string &strResourceName )
{
	const auto& strData = _ResourceManager.GetResource( strResourceName );
	ID3D11ShaderResourceView* pTemporaryTexture = nullptr;
	ID3D11Resource* pTextureData = nullptr;

	if ( pTexture != nullptr )
		pTexture->Release( );

	D3DX11CreateShaderResourceViewFromMemory( _Drawing.pDevice, &strData[ 0 ], strData.size( ), nullptr, nullptr, &pTemporaryTexture, nullptr );
	pTemporaryTexture->GetResource( &pTextureData );
	SetTexture( _Bitmap, reinterpret_cast< ID3D11Texture2D* >( pTextureData ) );
	pTemporaryTexture->Release( );
}

void CDrawable::RemoveTexture( )
{
	pTexture->Release( );
	pTexture = nullptr;
}

void CDrawable::Rectangle( rectangle_t recLocation, color_t clrColor )
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

void CDrawable::Rectangle( rectangle_t recLocation, color_t * clrColor )
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

void CDrawable::RoundedRectangle( rectangle_t recLocation, bool bLeftRounding, bool bRightRounding, color_t clrColor, double dbRoundingWidth )
{
	const auto vecBase = Utilities::vector2_t::GetCirclePoints( dbRoundingWidth, std::size_t( dbRoundingWidth ), 0.0, 0.25 );

}

void CDrawable::Line( Utilities::vector2_t vecStart, Utilities::vector2_t vecEnd, double dThickness, color_t clrColor )
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

	for ( auto& _Vertex : vecVertices )
		_Vertex.Rotate( dRotation, vecStart );

	DestroyBuffers( );
}

void CDrawable::Circle( const Utilities::vector2_t& vecCenter, double dbRadius, color_t clrColor, std::size_t zResolution /*= 0*/ )
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

void CDrawable::Circle( const Utilities::vector2_t & vecCenter, double dbRadius, color_t clrPerimeter, color_t clrCenter, std::size_t zResolution /*= 0*/ )
{
	Circle( vecCenter, dbRadius, clrPerimeter, zResolution );
	auto& _Vertex = vecVertices.front( );
	_Vertex = vertex_t( { _Vertex.x, _Vertex.y }, clrCenter );
}

void CDrawable::DestroyBuffers( )
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

	bCreated = false;
}

ID3D11Texture2D* CDrawable::RenderToTexture( )
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
	_TextureBufferDescription.BindFlags = D3D11_BIND_RENDER_TARGET;
	_TextureBufferDescription.CPUAccessFlags = 0;
	_TextureBufferDescription.MiscFlags = 0;

	_TextureDescription.Width = int( vecMax.x - vecMin.x );
	_TextureDescription.Height = int( vecMax.y - vecMin.y );
	_TextureDescription.MipLevels = 1;
	_TextureDescription.ArraySize = 1;
	_TextureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_TextureDescription.SampleDesc.Count = 1;
	_TextureDescription.SampleDesc.Quality = 0;
	_TextureDescription.Usage = D3D11_USAGE_DEFAULT;
	_TextureDescription.BindFlags = 0;
	_TextureDescription.CPUAccessFlags = 0;
	_TextureDescription.MiscFlags = 0;

	_RenderTargetViewDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_RenderTargetViewDescription.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	_RenderTargetViewDescription.Texture2D.MipSlice = 0;

	_Drawing.pDevice->CreateTexture2D( &_TextureBufferDescription, nullptr, &pRenderedTextureBuffer );
	_Drawing.pDevice->CreateTexture2D( &_TextureDescription, nullptr, &pRenderedTexture );
	_Drawing.pDevice->CreateRenderTargetView( pRenderedTextureBuffer, &_RenderTargetViewDescription, &pNewRenderTarget );
	_Drawing.pContext->OMSetRenderTargets( 1, &pNewRenderTarget, nullptr );
	_Drawing.pContext->ClearRenderTargetView( pNewRenderTarget, D3DXCOLOR( 0.f, 0.f, 0.f, 0.f ) );
	Draw( );
	_Drawing.pContext->CopyResource( pRenderedTexture, pRenderedTextureBuffer );
	_Drawing.pContext->OMSetRenderTargets( 1, &_Drawing.pRenderTargetView, _Drawing.pDepthStencilView );
	pNewRenderTarget->Release( );

	return pRenderedTexture;
}

bool CDrawing::Initialize( )
{
	RECT recWindowBoundsBuffer { };

	if ( pTarget == nullptr
		 || !pTarget->GetBounds( recWindowBoundsBuffer ) )
	{
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Invalid render target." ) );
		return false;
	}

	recRenderTarget = recWindowBoundsBuffer;
	DXGI_MODE_DESC _BackBufferDescription { };
	DXGI_SWAP_CHAIN_DESC _SwapChainDescription { };

	_BackBufferDescription.Width = unsigned( recRenderTarget.w );
	_BackBufferDescription.Height = unsigned( recRenderTarget.h );
	_BackBufferDescription.RefreshRate.Numerator = 60;
	_BackBufferDescription.RefreshRate.Denominator = 1;
	_BackBufferDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_BackBufferDescription.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	_BackBufferDescription.Scaling = DXGI_MODE_SCALING_STRETCHED;
	_SwapChainDescription.BufferDesc = _BackBufferDescription;
	_SwapChainDescription.SampleDesc.Count = 4;
	_SwapChainDescription.SampleDesc.Quality = 16;
	_SwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	_SwapChainDescription.BufferCount = 2;
	_SwapChainDescription.OutputWindow = pTarget->GetWindowHandle( );
	_SwapChainDescription.Windowed = TRUE;
	_SwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if ( !SUCCEEDED( D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, NULL, nullptr, NULL,
													D3D11_SDK_VERSION, &_SwapChainDescription, &pSwapChain, &pDevice, nullptr, &pContext ) ) )
		return LOG( ERROR, DRAWING, "Unable to create swap chain." ), false;

	return Create( ) && FONTS.Setup( );
}

void CDrawing::Uninitialize( )
{
	Destroy( );
	if ( pDevice )
	{
		pDevice->Release( );
		pDevice = nullptr;
	}

	if ( pContext )
	{
		pContext->Release( );
		pContext = nullptr;
	}

	if ( pSwapChain )
	{
		pSwapChain->Release( );
		pSwapChain = nullptr;
	}
}

void CDrawing::BeginFrame( )
{
	pContext->OMSetRenderTargets( 1, &pRenderTargetView, pDepthStencilView );
	pContext->PSSetSamplers( 0, 1, &pSamplerState );
	pContext->VSSetShader( pVertexShader, nullptr, 0 );
	pContext->IASetInputLayout( pVertexLayout );
	pContext->ClearRenderTargetView( pRenderTargetView, D3DXCOLOR( 0.f, 0.f, 0.f, 0.f ) );
	pContext->ClearDepthStencilView( pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0 );
}

bool CDrawing::EndFrame( )
{
	if ( !SUCCEEDED( pSwapChain->Present( 0, 0 ) ) )
		return LOG( WARNING, DRAWING, "Failed to present." ), false;

	return true;
}

bool CDrawing::ChangeTarget( CApplicationWindow *pNewTarget )
{
	Shutdown( );
	return ( pTarget = pNewTarget ) != nullptr && Setup( );
}

bool CDrawing::Create( )
{
	const auto strShaderData = GetShaderData( );
	const auto pShaderData = &strShaderData[ 0 ];
	const auto zShaderData = strShaderData.size( );
	ID3D11Texture2D* pBackBufferTexture = nullptr;
	D3D11_SAMPLER_DESC _SamplerDescription { };
	D3D11_TEXTURE2D_DESC _DepthStencilDescription { };
	D3D11_BLEND_DESC _BlendStateDescription { };
	D3D11_INPUT_ELEMENT_DESC _Layout[ ] =
	{
		{ ENC( "POSITION" ), 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ ENC( "TEXCOORD" ), 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ ENC( "COLOR" ), 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	D3D11_RASTERIZER_DESC _RasterizerDescription { };
	D3D11_VIEWPORT _Viewport { };

	if ( !SUCCEEDED( pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast< void** >( &pBackBufferTexture ) ) ) )
		return LOG( ERROR, DRAWING, "Unable to get swap chain backbuffer." ), false;

	if ( !SUCCEEDED( pDevice->CreateRenderTargetView( pBackBufferTexture, nullptr, &pRenderTargetView ) ) )
		return LOG( ERROR, DRAWING, "Unable to create render target view." ), false;

	pBackBufferTexture->Release( );

	_DepthStencilDescription.Width = unsigned( recRenderTarget.w );
	_DepthStencilDescription.Height = unsigned( recRenderTarget.h );
	_DepthStencilDescription.MipLevels = 1;
	_DepthStencilDescription.ArraySize = 1;
	_DepthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	_DepthStencilDescription.SampleDesc.Count = 4;
	_DepthStencilDescription.SampleDesc.Quality = 16;
	_DepthStencilDescription.Usage = D3D11_USAGE_DEFAULT;
	_DepthStencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_DepthStencilDescription.CPUAccessFlags = 0;
	_DepthStencilDescription.MiscFlags = 0;

	if ( !SUCCEEDED( pDevice->CreateTexture2D( &_DepthStencilDescription, nullptr, &pDepthStencilBuffer ) ) )
		return LOG( ERROR, DRAWING, "Unable to create texture for depth stencil buffer." ), false;

	if ( !SUCCEEDED( pDevice->CreateDepthStencilView( pDepthStencilBuffer, nullptr, &pDepthStencilView ) ) )
		return LOG( ERROR, DRAWING, "Unable to create depth stencil view." ), false;

	pContext->OMSetRenderTargets( 1, &pRenderTargetView, pDepthStencilView );

	_SamplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	_SamplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	_SamplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	_SamplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	_SamplerDescription.ComparisonFunc = D3D11_COMPARISON_NEVER;
	_SamplerDescription.MinLOD = 0;
	_SamplerDescription.MaxLOD = D3D11_FLOAT32_MAX;

	if ( !SUCCEEDED( pDevice->CreateSamplerState( &_SamplerDescription, &pSamplerState ) ) )
		return LOG( ERROR, DRAWING, "Unable to create sampler state." ), false;

	pContext->PSSetSamplers( 0, 1, &pSamplerState );

	_BlendStateDescription.AlphaToCoverageEnable = FALSE;
	_BlendStateDescription.RenderTarget[ 0 ].BlendEnable = TRUE;
	_BlendStateDescription.RenderTarget[ 0 ].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	_BlendStateDescription.RenderTarget[ 0 ].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	_BlendStateDescription.RenderTarget[ 0 ].BlendOp = D3D11_BLEND_OP_ADD;
	_BlendStateDescription.RenderTarget[ 0 ].SrcBlendAlpha = D3D11_BLEND_ONE;
	_BlendStateDescription.RenderTarget[ 0 ].DestBlendAlpha = D3D11_BLEND_ZERO;
	_BlendStateDescription.RenderTarget[ 0 ].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	_BlendStateDescription.RenderTarget[ 0 ].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if ( !SUCCEEDED( pDevice->CreateBlendState( &_BlendStateDescription, &pBlendState ) ) )
		return LOG( ERROR, DRAWING, "Unable to create blend state." ), false;

	pContext->OMSetBlendState( pBlendState, D3DXCOLOR( 0.f, 0.f, 0.f, 0.f ), 0xFFFFFFFF );

	D3DX11CompileFromMemory( pShaderData, zShaderData, nullptr, nullptr, nullptr, ENC( "StandardVertexShader" ), ENC( "vs_4_0" ), 0, 0, nullptr, &pVertexShaderBuffer, nullptr, nullptr );
	D3DX11CompileFromMemory( pShaderData, zShaderData, nullptr, nullptr, nullptr, ENC( "StandardPixelShader" ), ENC( "ps_4_0" ), 0, 0, nullptr, &pStandardPixelShaderBuffer, nullptr, nullptr );
	D3DX11CompileFromMemory( pShaderData, zShaderData, nullptr, nullptr, nullptr, ENC( "TexturedPixelShader" ), ENC( "ps_4_0" ), 0, 0, nullptr, &pTexturedPixelShaderBuffer, nullptr, nullptr );
	pDevice->CreateVertexShader( pVertexShaderBuffer->GetBufferPointer( ), pVertexShaderBuffer->GetBufferSize( ), nullptr, &pVertexShader );
	pContext->VSSetShader( pVertexShader, nullptr, 0 );
	pDevice->CreatePixelShader( pStandardPixelShaderBuffer->GetBufferPointer( ), pStandardPixelShaderBuffer->GetBufferSize( ), nullptr, &pStandardPixelShader );
	pDevice->CreatePixelShader( pTexturedPixelShaderBuffer->GetBufferPointer( ), pTexturedPixelShaderBuffer->GetBufferSize( ), nullptr, &pTexturedPixelShader );
	pContext->PSSetShader( pStandardPixelShader, nullptr, 0 );
	pDevice->CreateInputLayout( _Layout, ARRAYSIZE( _Layout ), pVertexShaderBuffer->GetBufferPointer( ), pVertexShaderBuffer->GetBufferSize( ), &pVertexLayout );
	pContext->IASetInputLayout( pVertexLayout );

	_RasterizerDescription.FillMode = D3D11_FILL_SOLID;
	_RasterizerDescription.CullMode = D3D11_CULL_NONE;
	_RasterizerDescription.MultisampleEnable = TRUE;
	_RasterizerDescription.AntialiasedLineEnable = TRUE;
	pDevice->CreateRasterizerState( &_RasterizerDescription, &pRasterizer );
	pContext->RSSetState( pRasterizer );

	_Viewport.TopLeftX = 0;
	_Viewport.TopLeftY = 0;
	_Viewport.Width = float( recRenderTarget.w );
	_Viewport.Height = float( recRenderTarget.h );
	_Viewport.MinDepth = 0.f;
	_Viewport.MaxDepth = 0.f;

	pContext->RSSetViewports( 1, &_Viewport );

	auto bReturn = true;

	for ( auto& pDrawable : vecDrawables )
		bReturn &= pDrawable->Create( );

	return bReturn;
}

bool CDrawing::Destroy( )
{
	if ( pRenderTargetView )
	{
		pRenderTargetView->Release( );
		pRenderTargetView = nullptr;
	}

	if ( pDepthStencilBuffer )
	{
		pDepthStencilBuffer->Release( );
		pDepthStencilBuffer = nullptr;
	}

	if ( pDepthStencilView )
	{
		pDepthStencilView->Release( );
		pDepthStencilView = nullptr;
	}

	if ( pSamplerState )
	{
		pSamplerState->Release( );
		pSamplerState = nullptr;
	}

	if ( pBlendState )
	{
		pBlendState->Release( );
		pBlendState = nullptr;
	}

	if ( pVertexShader )
	{
		pVertexShader->Release( );
		pVertexShader = nullptr;
	}

	if ( pStandardPixelShader )
	{
		pStandardPixelShader->Release( );
		pStandardPixelShader = nullptr;
	}

	if ( pTexturedPixelShader )
	{
		pTexturedPixelShader->Release( );
		pTexturedPixelShader = nullptr;
	}

	if ( pVertexLayout )
	{
		pVertexLayout->Release( );
		pVertexLayout = nullptr;
	}

	for ( auto& pDrawable : vecDrawables )
		pDrawable->Destroy( );

	return true;
}	

bool CDrawing::IsAreaVisible( const rectangle_t &recArea )
{
	if ( recSource.empty( ) )
		return true;

	return recArea.InRectangle( recSource.top( ) );
}

bool CDrawing::RegisterDrawable( CDrawable*pDrawable )
{
	if ( pDrawable == nullptr )
		return false;

	for ( auto& pIteration : vecDrawables )
		if ( pIteration == pDrawable )
			return false;

	vecDrawables.emplace_back( pDrawable );
	return true;
}

bool CDrawing::UnregisterDrawable( CDrawable*pDrawable )
{
	for ( auto z = 0u; z < vecDrawables.size( ); z++ )
		if ( vecDrawables[ z ] == pDrawable )
			return vecDrawables.erase( vecDrawables.begin( ) + z ), true;

	return false;
}

CDrawing _Drawing;
