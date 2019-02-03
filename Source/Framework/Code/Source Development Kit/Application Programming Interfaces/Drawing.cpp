/// Drawing.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

bool CDrawing::Initialize( )
{
	if ( pTarget == nullptr )
	{
		if ( pDevice == nullptr )
		{
			_Log.Log( EPrefix::ERROR, ELocation::DRAWING, XOR( "No render target or device was set!" ) );
			return false;
		}

		return true;
	}

	if ( ( pD3DInstance = Direct3DCreate9( DIRECT3D_VERSION ) ) == nullptr )
	{
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, XOR( "Unable to create D3D instance." ) );
		return false;
	}

	pParameters.Windowed = TRUE;
	pParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	pParameters.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	pParameters.EnableAutoDepthStencil = TRUE;
	pParameters.AutoDepthStencilFormat = D3DFMT_D16;
	pParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if ( pD3DInstance->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, pTarget->GetWindowHandle( ), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pParameters, &pDevice ) != D3D_OK )
	{
		pD3DInstance->Release( );
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, XOR( "Failed to create D3D device." ) );
		return false;
	}

	return true;
}

bool CDrawing::CreateState( )
{
	constexpr auto fnSetState = [ & ]( )
	{
		if ( pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_ZENABLE, FALSE ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_SCISSORTESTENABLE, TRUE ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, UINT_MAX ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, NULL ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE ) == D3D_OK
			&& pDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, TRUE ) == D3D_OK
			&& pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP ) == D3D_OK
			&& pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP ) == D3D_OK
			&& pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP ) == D3D_OK
			&& pDevice->SetSamplerState( NULL, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR ) == D3D_OK
			&& pDevice->SetSamplerState( NULL, D3DSAMP_MINFILTER, D3DTEXF_LINEAR ) == D3D_OK
			&& pDevice->SetSamplerState( NULL, D3DSAMP_SRGBTEXTURE, NULL ) == D3D_OK
			&& pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE ) == D3D_OK
			&& pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, 2 ) == D3D_OK
			&& pDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, NULL ) == D3D_OK
			&& pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE ) == D3D_OK
			&& pDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, 2 ) == D3D_OK
			&& pDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, NULL ) == D3D_OK
			&& pDevice->SetPixelShader( nullptr ) == D3D_OK
			&& pDevice->SetVertexShader( nullptr ) == D3D_OK
			&& pDevice->SetTexture( NULL, nullptr ) == D3D_OK
			&& pDevice->SetFVF( FVF ) == D3D_OK )
			return true;

		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, XOR( "Could not set device state." ) );
		return false;
	};

	if ( pState != nullptr )
	{
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, XOR( "Attempting to create state when state exists." ) );
		return false;
	}

	if ( pDevice->BeginStateBlock( ) != D3D_OK )
	{
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, XOR( "Could not begin state block." ) );
		fnSetState( );
		return false;
	}

	fnSetState( );
	if ( pDevice->EndStateBlock( &pState ) != D3D_OK )
	{
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, XOR( "Could not end state block." ) );
		return false;
	}

	return true;
}

void CDrawing::Shutdown( )
{
	PreReset( );
	if ( pDevice && pTarget )
	{
		pDevice->Release( );
		pDevice = nullptr;
	}
}

void CDrawing::SetTarget( CWindow *pWindow )
{
	pTarget = pWindow;
}

void CDrawing::SetTarget( IDirect3DDevice9 *pNewDevice )
{
	pDevice = pNewDevice;
}

bool CDrawing::SetState( )
{
	if ( pState == nullptr )
		if ( !CreateState( ) )
			return false;

	if ( D3D_OK != pState->Apply( ) )
	{
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, XOR( "Failed to apply state block." ) );
		return false;
	}

	return true;
}

bool CDrawing::BeginFrame( )
{
	if ( !SetState( ) )
		return false;

	if ( D3D_OK != pDevice->Clear( NULL, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, NULL, NULL, NULL ) )
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, XOR( "Failed to clear device." ) );

	if ( D3D_OK != pDevice->BeginScene( ) )
	{
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, XOR( "Failed to begin scene." ) );
		return false;
	}

	return true;
}

bool CDrawing::EndFrame( )
{
	if ( pDevice->EndScene( ) != D3D_OK )
	{
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, XOR( "Failed to end scene." ) );
		return false;
	}

	const auto hrPresent = pDevice->Present( nullptr, nullptr, nullptr, nullptr );
	if ( hrPresent != D3D_OK )
	{
		if ( hrPresent == D3DERR_DEVICELOST && pDevice->TestCooperativeLevel( ) == D3DERR_DEVICENOTRESET )
		{
			_Log.Log( EPrefix::INFO, ELocation::DRAWING, XOR( "Attempting to reset device after being lost." ) );
			PreReset( );
			if ( D3D_OK != pDevice->Reset( &pParameters ) )
			{
				_Log.Log( EPrefix::ERROR, ELocation::DRAWING, XOR( "Failed to reset device!" ) );
				return false;
			}
			PostReset( );
			return true;
		}

		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, XOR( "Failed to present scene." ) );
		return false;
	}
}

void CDrawing::PreReset( )
{ }

void CDrawing::PostReset( )
{ }

void CDrawing::Polygon( vertex_t *pVertices, std::size_t sVertices, std::size_t sPrimitives )
{
	IDirect3DVertexBuffer9 *pBuffer = nullptr;

	const auto sVertexSize = sizeof( vertex_t ) * sVertices;
	if ( D3D_OK != pDevice->CreateVertexBuffer( sVertexSize, NULL, FVF, D3DPOOL_DEFAULT, &pBuffer, nullptr ) )
	{
		if ( pBuffer )
		{
			pBuffer->Release( );
			pBuffer = nullptr;
		}
		return;
	}

	void *pVertexMemory;
	pBuffer->Lock( 0, sVertexSize, &pVertexMemory, 0 );
	memcpy( pVertexMemory, pVertices, sVertexSize );
	pBuffer->Unlock( );

	if ( D3D_OK != pDevice->SetStreamSource( NULL, pBuffer, NULL, sizeof( vertex_t ) ) )
	{
		pBuffer->Release( );
		pBuffer = nullptr;
		return;
	}

	pDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, sPrimitives );
	pBuffer->Release( );
}

IDirect3DVertexBuffer9 *CDrawing::ConstructPolygon( vertex_t *pVertices, std::size_t sVertices )
{
	IDirect3DVertexBuffer9 *pBuffer = nullptr;

	const auto sVertexSize = sizeof( vertex_t ) * sVertices;
	if ( D3D_OK != pDevice->CreateVertexBuffer( sVertexSize, NULL, FVF, D3DPOOL_DEFAULT, &pBuffer, nullptr ) )
	{
		if ( pBuffer )
			pBuffer->Release( );

		return nullptr;
	}

	void *pVertexMemory;
	pBuffer->Lock( 0, sVertexSize, &pVertexMemory, 0 );
	memcpy( pVertexMemory, pVertices, sVertexSize );
	pBuffer->Unlock( );

	return pBuffer;
}

void CDrawing::DrawPolygon( const polygon_buffer_t &pbPolygon, bool bRelease /*= false*/ )
{
	if ( D3D_OK == pDevice->SetStreamSource( NULL, pbPolygon.pVertexBuffer, NULL, sizeof( vertex_t ) ) )
		pDevice->DrawPrimitive( pbPolygon.ptDraw, 0, pbPolygon.sPrimitives );

	if ( bRelease )
		pbPolygon.pVertexBuffer->Release( );
}

triangle_t::triangle_t( location_t _locLocation, float _flBaseLength, float _flRotation ): locLocation( _locLocation ), flBaseLength( _flBaseLength ), flRotation( _flRotation )
{ }

location_t triangle_t::GetPoint( int iPoint )
{
	const auto flHeight = flBaseLength / 2.f * tan( 60.f / 180.f * D3DX_PI ) / 2.f;
	auto locReturn = locLocation;

	switch ( iPoint )
	{
		case TOP:
		{
			locReturn.y -= flHeight;
		}
		break;

		case RIGHT:
		{
			locReturn.y += flHeight;
			locReturn.x += flBaseLength / 2.f;
		}
		break;

		case LEFT:
		{
			locReturn.y += flHeight;
			locReturn.x -= flBaseLength / 2.f;
		}
		break;

		default:
			break;
	}

	locReturn.Rotate( flRotation, locLocation );
	return locReturn;
}

rectangle_t::rectangle_t( float _x, float _y, float _flWidth, float _flHeight ): x( _x ), y( _y ), flWidth( _flWidth ), flHeight( _flHeight )
{ }

rectangle_t::rectangle_t( RECT recNew )
{
	*this = rectangle_t( float( recNew.left ), float( recNew.top ), float( recNew.right - recNew.left ), float( recNew.bottom - recNew.top ) );
}

void rectangle_t::operator+=( const rectangle_t &rhs )
{
	x += rhs.x;
	y += rhs.y;
}

void rectangle_t::Clamp( const rectangle_t &recClamp )
{
	if ( x < recClamp.x )
		x = recClamp.x;

	if ( y < recClamp.y )
		y = recClamp.y;

	while ( x + flWidth > recClamp.x + recClamp.flWidth )
		flWidth -= 1.f;

	while ( y + flHeight > recClamp.y + recClamp.flHeight )
		flHeight -= 1.f;
}

bool rectangle_t::LocationInRectangle( const location_t &locLocation ) const
{
	return locLocation.x >= x
			&& locLocation.x <= x + flWidth
			&& locLocation.y >= y
			&& locLocation.y <= y + flHeight;
}

bool rectangle_t::InRectangle( const rectangle_t &recLocation ) const
{
	return recLocation.LocationInRectangle( location_t( x, y ) )
			|| recLocation.LocationInRectangle( location_t( x + flWidth, y ) )
			|| recLocation.LocationInRectangle( location_t( x + flWidth, y + flHeight ) )
			|| recLocation.LocationInRectangle( location_t( x, y + flHeight ) );
}

RECT rectangle_t::ToRect( ) const
{
	return { int( x ), int( y ), int( x + flWidth ), int( y + flHeight ) };
}

circle_t::circle_t( location_t _locLocation, float _flRadius, std::size_t _sResolution ): locLocation( _locLocation ), flRadius( _flRadius ), sResolution( _sResolution )
{ }

vertex_t *circle_t::GetPoints( float flStartAngle, float flRatio ) const
{
	const auto pReturn = new vertex_t[ sResolution + 2u ];
	const auto flAngle = 360.f * flRatio / float( sResolution );
	const auto vecRotationPoint = D3DXVECTOR2( locLocation.x, locLocation.y );
	auto locCurrent = locLocation;

	pReturn[ 0 ] = vertex_t( locCurrent.x, locCurrent.y, NULL ).Round( );
	locCurrent.y -= flRadius;
	if ( flStartAngle != 0.f )
		locCurrent.Rotate( flStartAngle, locLocation );

	pReturn[ 1 ] = vertex_t( locCurrent.x, locCurrent.y, NULL ).Round( );
	for ( auto u = 2u; u <= sResolution; u++ )
	{
		pReturn[ u ] = pReturn[ 1 ];
		pReturn[ u ].Rotate( flAngle * float( u - 1 ), vecRotationPoint );
		pReturn[ u ].Round( );
	}
	pReturn[ sResolution + 1u ] = pReturn[ 1 ];
	pReturn[ sResolution + 1u ].Rotate( 360.f * flRatio, vecRotationPoint );

	return pReturn;
}

vertex_t::vertex_t( float x, float y, DWORD _dwColor )
{
	flVectors[ 0 ] = x;
	flVectors[ 1 ] = y;
	flVectors[ 2 ] = 0.f;
	flVectors[ 3 ] = 1.f;
	dwColor = _dwColor;
}

vertex_t vertex_t::operator+( const vertex_t &rhs )
{
	flVectors[ 0 ] += rhs.flVectors[ 0 ];
	flVectors[ 1 ] += rhs.flVectors[ 1 ];
	return *this;
}

vertex_t vertex_t::operator/( float flDivisor )
{
	flVectors[ 0 ] /= flDivisor;
	flVectors[ 1 ] /= flDivisor;
	return *this;
}

void vertex_t::Rotate( float flAngle, D3DXVECTOR2 vecRotationPoint )
{
	const auto flRadians = D3DXToRadian( flAngle );
	const auto flSin = sin( flRadians );
	const auto flCos = cos( flRadians );
	const D3DXVECTOR2 vecRelative { flVectors[ 0 ] - vecRotationPoint.x, flVectors[ 1 ] - vecRotationPoint.y };

	flVectors[ 0 ] = ( vecRelative.x * flCos ) - ( vecRelative.y * flSin ) + vecRotationPoint.x;
	flVectors[ 1 ] = ( vecRelative.x * flSin ) + ( vecRelative.y * flCos ) + vecRotationPoint.y;
}

vertex_t vertex_t::Round( )
{
	for each ( auto &vector in flVectors )
		vector = roundf( vector );

	return *this;
}

polygon_buffer_t::polygon_buffer_t( IDirect3DVertexBuffer9 *_pVertexBuffer, std::size_t _sPrimitives, D3DPRIMITIVETYPE _ptDraw ): pVertexBuffer( _pVertexBuffer ), sPrimitives( _sPrimitives ),
																																  ptDraw( _ptDraw )
{ }

polygon_t::polygon_t( ): vecVertices( { } ), sPrimitives( 0 )
{ }

polygon_t::polygon_t( vertex_t *pVertices, std::size_t sVertices, std::size_t _sPrimitives )
{
	vecVertices = decltype( vecVertices )( );

	for ( auto u = 0u; u < sVertices; u++ )
		vecVertices.emplace_back( pVertices[ u ] );

	sPrimitives = _sPrimitives;
}

polygon_t::polygon_t( std::vector< vertex_t > _vecVertices, std::size_t _sPrimitives ):
	vecVertices( _vecVertices ), sPrimitives( _sPrimitives )
{ }

void polygon_t::Draw( rectangle_t recRelative, color_t clrColor )
{
	if ( vecVertices.empty( ) )
		return;

	const auto dwColor = clrColor.Hex( );
	auto vecTemp = vecVertices;

	for each ( auto &vtx in vecTemp )
	{
		vtx.flVectors[ 0 ] += recRelative.x;
		vtx.flVectors[ 1 ] += recRelative.y;
		vtx.dwColor = dwColor;
	}
	Polygon( &vecTemp[ 0 ], vecTemp.size( ), sPrimitives );
}

void polygon_t::Join( const polygon_t &other )
{
	for each ( auto &vertex in other.vecVertices )
		vecVertices.emplace_back( vertex );

	sPrimitives += other.sPrimitives;
}

void polygon_t::Draw( )
{
	if ( vecVertices.empty( ) )
		return;

	Polygon( &vecVertices[ 0 ], vecVertices.size( ), sPrimitives );
}

void polygon_t::Draw( rectangle_t recRelative )
{
	if ( vecVertices.empty( ) )
		return;

	auto vecTemp = vecVertices;

	for each ( auto &vtx in vecTemp )
	{
		vtx.flVectors[ 0 ] += recRelative.x;
		vtx.flVectors[ 1 ] += recRelative.y;
	}
	Polygon( &vecTemp[ 0 ], vecTemp.size( ), sPrimitives );
}

polygon_buffer_t polygon_t::GetBuffer( D3DPRIMITIVETYPE ptDraw /*= D3DPT_TRIANGLEFAN*/ )
{
	assert( !vecVertices.empty( ) );

	return polygon_buffer_t( ConstructPolygon( &vecVertices[ 0 ], vecVertices.size( ) ), sPrimitives, ptDraw );
}
