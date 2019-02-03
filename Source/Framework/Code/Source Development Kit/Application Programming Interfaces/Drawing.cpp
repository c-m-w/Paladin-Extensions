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
	auto fnSetState = [ & ]( )
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

polygon_t Rectangle( rectangle_t recLocation, color_t clrColor )
{
	const auto dwColor = clrColor.GetARGB( );

	vertex_t vtxVertices[ 4 ]
	{
		vertex_t( recLocation.x, recLocation.y, dwColor ),
		vertex_t( recLocation.x + recLocation.flWidth, recLocation.y, dwColor ),
		vertex_t( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight, dwColor ),
		vertex_t( recLocation.x, recLocation.y + recLocation.flHeight, dwColor )
	};

	return polygon_t( vtxVertices, 4, 2 );
}

polygon_t Rectangle( rectangle_t recLocation, color_t* clrColor )
{
	vertex_t vtxVertices[ 4 ]
	{
		vertex_t( recLocation.x, recLocation.y, clrColor[ rectangle_t::TOP_LEFT ].GetARGB( ) ),
		vertex_t( recLocation.x + recLocation.flWidth, recLocation.y, clrColor[ rectangle_t::TOP_RIGHT ].GetARGB( ) ),
		vertex_t( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight, clrColor[ rectangle_t::BOTTOM_RIGHT ].GetARGB( ) ),
		vertex_t( recLocation.x, recLocation.y + recLocation.flHeight, clrColor[ rectangle_t::BOTTOM_LEFT ].GetARGB( ) )
	};

	return polygon_t( vtxVertices, 4, 2 );
}

#define ROUNDING_VERTICES ( std::size_t( ceilf( flRadius / 3.f ) ) )

polygon_t OutlineRectangle( rectangle_t recLocation, color_t clrColor )
{
	const auto dwColor = clrColor.GetARGB( );
	polygon_t lstReturn { };

	lstReturn.vecVertices.emplace_back( recLocation.x, recLocation.y, dwColor );
	lstReturn.vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y, dwColor );
	lstReturn.vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight, dwColor );
	lstReturn.vecVertices.emplace_back( recLocation.x, recLocation.y + recLocation.flHeight, dwColor );

	return lstReturn;
}

polygon_t RoundedRectangle( rectangle_t recLocation, color_t clrColor, bool* bRounding, float flRounding )
{
	constexpr float ROTATIONS[ rectangle_t::MAX ] { 270.f, 0.f, 90.f, 180.f };
	const auto flRadius = roundf( std::min( recLocation.flHeight, recLocation.flWidth ) / 2.f * flRounding );
	const auto uResolution = ROUNDING_VERTICES;
	const auto dwColor = clrColor.GetARGB( );
	std::vector< vertex_t > vecVertices { };
	auto sPrimitives { 2u };

	if ( bRounding[ rectangle_t::TOP_LEFT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + flRadius, recLocation.y + flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_LEFT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( vertex_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ], dwColor ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y, dwColor );

	if ( bRounding[ rectangle_t::TOP_RIGHT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_RIGHT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( vertex_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ], dwColor ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y, dwColor );

	if ( bRounding[ rectangle_t::BOTTOM_RIGHT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + recLocation.flHeight - flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_RIGHT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( vertex_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ], dwColor ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight, dwColor );

	if ( bRounding[ rectangle_t::BOTTOM_LEFT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + flRadius, recLocation.y + recLocation.flHeight - flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_LEFT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( vertex_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ], dwColor ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y + recLocation.flHeight, dwColor );

	return polygon_t( &vecVertices[ 0 ], vecVertices.size( ), sPrimitives );
}

polygon_t OutlineRoundedRectangle( rectangle_t recLocation, color_t clrColor, bool* bRounding, float flRounding )
{
	constexpr float ROTATIONS[ rectangle_t::MAX ] { 270.f, 0.f, 90.f, 180.f };
	const auto flRadius = roundf( std::min( recLocation.flHeight, recLocation.flWidth ) / 2.f * flRounding );
	const auto uResolution = ROUNDING_VERTICES;
	std::vector< location_t > vecVertices { };
	auto sPrimitives { 4u };

	if ( bRounding[ rectangle_t::TOP_LEFT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + flRadius, recLocation.y + flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_LEFT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y );

	if ( bRounding[ rectangle_t::TOP_RIGHT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_RIGHT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y );

	if ( bRounding[ rectangle_t::BOTTOM_RIGHT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + recLocation.flHeight - flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_RIGHT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight );

	if ( bRounding[ rectangle_t::BOTTOM_LEFT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + flRadius, recLocation.y + recLocation.flHeight - flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_LEFT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y + recLocation.flHeight );

	polygon_t polReturn;
	polReturn.sPrimitives = sPrimitives;
	for ( auto& location : vecVertices )
		polReturn.vecVertices.emplace_back( location.x, location.y, clrColor.GetARGB( ) );

	polReturn.vecVertices.emplace_back( polReturn.vecVertices[ 0 ] );
	return polReturn;
}

polygon_t OutlineSpacedRoundedRectangle( rectangle_t recLocation, color_t clrColor, bool* bRounding, float flRounding, float flSpacing )
{
	constexpr float ROTATIONS[ rectangle_t::MAX ] { 270.f, 0.f, 90.f, 180.f };
	const auto flRadius = roundf( std::min( recLocation.flHeight, recLocation.flWidth ) / 2.f * flRounding );
	const auto uResolution = ROUNDING_VERTICES;
	std::vector< location_t > vecVertices { };
	auto sPrimitives { 5u };

	vecVertices.emplace_back( recLocation.x + std::min( recLocation.flHeight, recLocation.flWidth ) * flRounding, recLocation.y );

	if ( bRounding[ rectangle_t::TOP_LEFT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + flRadius, recLocation.y + flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_LEFT ], 0.25f );
		for ( auto u = uResolution + 1; u >= 1; u-- )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y );

	if ( bRounding[ rectangle_t::BOTTOM_LEFT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + flRadius, recLocation.y + recLocation.flHeight - flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_LEFT ], 0.25f );
		for ( auto u = uResolution + 1; u >= 1; u-- )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y + recLocation.flHeight );

	if ( bRounding[ rectangle_t::BOTTOM_RIGHT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + recLocation.flHeight - flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_RIGHT ], 0.25f );
		for ( auto u = uResolution + 1; u >= 1; u-- )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight );

	if ( bRounding[ rectangle_t::TOP_RIGHT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_RIGHT ], 0.25f );
		for ( auto u = uResolution + 1; u >= 1; u-- )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y );

	const auto dwColor = clrColor.GetARGB( );
	polygon_t polReturn;
	polReturn.sPrimitives = sPrimitives;
	for ( auto& location : vecVertices )
		polReturn.vecVertices.emplace_back( location.x, location.y, dwColor );

	polReturn.vecVertices.emplace_back( vertex_t( polReturn.vecVertices[ 0 ].flVectors[ 0 ] + flSpacing, polReturn.vecVertices[ 0 ].flVectors[ 1 ], dwColor ) );
	return polReturn;
}

polygon_t RoundedRectangle( rectangle_t recLocation, color_t* clrColor, bool* bRounding, float flRounding )
{
	constexpr float ROTATIONS[ rectangle_t::MAX ] { 270.f, 0.f, 90.f, 180.f };
	const auto flRadius = roundf( std::min( recLocation.flHeight, recLocation.flWidth ) / 2.f * flRounding );
	const auto uResolution = ROUNDING_VERTICES;
	std::vector< vertex_t > vecVertices { };
	auto sPrimitives { 2u };

	if ( bRounding[ rectangle_t::TOP_LEFT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + flRadius, recLocation.y + flRadius ), flRadius, uResolution );
		auto pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_LEFT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( vertex_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ], clrColor[ rectangle_t::TOP_LEFT ].GetARGB( ) ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y, clrColor[ rectangle_t::TOP_LEFT ].GetARGB( ) );

	if ( bRounding[ rectangle_t::TOP_RIGHT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_RIGHT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( vertex_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ], clrColor[ rectangle_t::TOP_RIGHT ].GetARGB( ) ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y, clrColor[ rectangle_t::TOP_RIGHT ].GetARGB( ) );

	if ( bRounding[ rectangle_t::BOTTOM_RIGHT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + recLocation.flHeight - flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_RIGHT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( vertex_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ], clrColor[ rectangle_t::BOTTOM_RIGHT ].GetARGB( ) ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight, clrColor[ rectangle_t::BOTTOM_RIGHT ].GetARGB( ) );

	if ( bRounding[ rectangle_t::BOTTOM_LEFT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + flRadius, recLocation.y + recLocation.flHeight - flRadius ), flRadius, uResolution );
		const vertex_t* pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_LEFT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( vertex_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ], clrColor[ rectangle_t::BOTTOM_LEFT ].GetARGB( ) ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y + recLocation.flHeight, clrColor[ rectangle_t::BOTTOM_LEFT ].GetARGB( ) );

	return polygon_t( vecVertices, sPrimitives );
}

polygon_t Triangle( location_t locFirst, location_t locSecond, location_t locThird, color_t clrColor )
{
	const auto dwColor = clrColor.GetARGB( );

	vertex_t vtxVertices[ ]
	{
		vertex_t( locFirst.x, locFirst.y, dwColor ),
		vertex_t( locSecond.x, locSecond.y, dwColor ),
		vertex_t( locThird.x, locThird.y, dwColor )
	};

	return polygon_t( vtxVertices, 3, 1 );
}

polygon_t Triangle( triangle_t trLocation, color_t* clrColor )
{
	const auto locTop = trLocation.GetPoint( triangle_t::TOP ),
		locRight = trLocation.GetPoint( triangle_t::RIGHT ),
		locLeft = trLocation.GetPoint( triangle_t::LEFT );
	vertex_t vtxVertices[ ]
	{
		vertex_t( locTop.x, locTop.y, clrColor[ triangle_t::TOP ].GetARGB( ) ),
		vertex_t( locRight.x, locRight.y, clrColor[ triangle_t::RIGHT ].GetARGB( ) ),
		vertex_t( locLeft.x, locLeft.y, clrColor[ triangle_t::LEFT ].GetARGB( ) )
	};

	return polygon_t( vtxVertices, 3, 1 );
}

polygon_t Circle( circle_t circle, color_t clrColor, float flStartAngle, float flRatio )
{
	const auto pPoints = circle.GetPoints( flStartAngle, flRatio );
	const auto dwColor = clrColor.GetARGB( );

	for ( auto u = 0u; u < circle.sResolution + 2u; u++ )
		pPoints[ u ].dwColor = dwColor;

	const auto polReturn = polygon_t( pPoints, circle.sResolution + 2u, circle.sResolution );

	delete[ ] pPoints;

	return polReturn;
}

polygon_t OutlineCircle( circle_t circle, color_t clrColor, float flStartAngle, float flRatio )
{
	const auto pPoints = circle.GetPoints( flStartAngle, flRatio );
	const auto dwColor = clrColor.GetARGB( );
	polygon_t polReturn;

	for ( auto u = 1u; u <= circle.sResolution + 1u; u++ )
		polReturn.vecVertices.emplace_back( pPoints[ u ].flVectors[ 0 ], pPoints[ u ].flVectors[ 1 ], dwColor );

	polReturn.vecVertices.emplace_back( pPoints[ 1 ].flVectors[ 0 ], pPoints[ 1 ].flVectors[ 1 ], dwColor );

	delete[ ] pPoints;

	return polReturn;
}

polygon_t Circle( circle_t circle, color_t clrCenter, color_t clrOuter, float flStartAngle, float flRatio )
{
	const auto pPoints = circle.GetPoints( flStartAngle, flRatio );
	const auto dwColor = clrOuter.GetARGB( );

	pPoints[ 0 ].dwColor = clrCenter.GetARGB( );
	for ( auto u = 1u; u < circle.sResolution + 2u; u++ )
		pPoints[ u ].dwColor = dwColor;

	const auto polReturn = polygon_t( pPoints, circle.sResolution + 2u, circle.sResolution );

	delete[ ] pPoints;

	return polReturn;
}

polygon_t Circle( circle_t circle, color_t* pColors, float flStartAngle, float flRatio )
{
	const auto pPoints = circle.GetPoints( flStartAngle, flRatio );
	const auto sPoints = std::size_t( circle.sResolution * flRatio ) + 1u;

	for ( auto u = 0u; u <= circle.sResolution + 1u; u++ )
		pPoints[ u ].dwColor = pColors[ u ].GetARGB( );
	pPoints[ 1 ].dwColor = pPoints[ sPoints ].dwColor;

	const auto polReturn = polygon_t( pPoints, circle.sResolution + 2u, circle.sResolution );

	delete[ ] pPoints;

	return polReturn;
}

polygon_t Line( location_t locStart, location_t locEnd, float flThickness, color_t clrColor )
{
	const auto locLength = locEnd - locStart;
	const auto dwColor = clrColor.GetARGB( );
	const auto flLength = locLength.Length( );
	const auto vecRotationPoint = D3DXVECTOR2( locStart.x, locStart.y );
	auto flRotation = locLength.Angle( );
	vertex_t vtxVertices[ ]
	{
		vertex_t( locStart.x, locStart.y - flThickness / 2.f, dwColor ),
		vertex_t( locStart.x + flLength, locStart.y - flThickness / 2.f, dwColor ),
		vertex_t( locStart.x + flLength, locStart.y + flThickness / 2.f, dwColor ),
		vertex_t( locStart.x, locStart.y + flThickness / 2.f, dwColor )
	};

	if ( locLength.x < 0.f )
	{
		if ( locLength.y < 0.f || locLength.y == 0.f )
			flRotation += 180.f;
		else
			flRotation = 180.f - fabsf( flRotation );
	}

	for ( auto& vertex : vtxVertices )
		vertex.Rotate( flRotation, vecRotationPoint );

	return polygon_t( vtxVertices, 4, 2 );
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

	const auto dwColor = clrColor.GetARGB( );
	auto vecTemp = vecVertices;

	for each ( auto &vtx in vecTemp )
	{
		vtx.flVectors[ 0 ] += recRelative.x;
		vtx.flVectors[ 1 ] += recRelative.y;
		vtx.dwColor = dwColor;
	}
	_Drawing.Polygon( &vecTemp[ 0 ], vecTemp.size( ), sPrimitives );
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

	_Drawing.Polygon( &vecVertices[ 0 ], vecVertices.size( ), sPrimitives );
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
	_Drawing.Polygon( &vecTemp[ 0 ], vecTemp.size( ), sPrimitives );
}

polygon_buffer_t polygon_t::GetBuffer( D3DPRIMITIVETYPE ptDraw /*= D3DPT_TRIANGLEFAN*/ )
{
	if ( vecVertices.empty( ) )
		throw std::runtime_error( XOR( "Attempting to create a buffer from no vertices." ) );

	return polygon_buffer_t( _Drawing.ConstructPolygon( &vecVertices[ 0 ], vecVertices.size( ) ), sPrimitives, ptDraw );
}
