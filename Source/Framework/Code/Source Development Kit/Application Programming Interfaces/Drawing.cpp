/// Drawing.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

bool CDrawing::Initialize( )
{
	if ( pTarget == nullptr )
	{
		if ( pDevice == nullptr )
		{
			_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "No render target or device was set!" ) );
			return false;
		}
	}
	else
		CreateD3D( );

	if ( FT_Init_FreeType( &libInstance ) != 0
		|| libInstance == nullptr )
	{
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Unable to initialize FreeType." ) );
		return false;
	}

	if ( !Create( ) )
		return false;

	strFontDirectory = ENC( "Fonts\\" );
	strFontFileNames[ TAHOMA ] = ENC( "tahoma.ttf" );
	strFontFileNames[ TAHOMA_BOLD ] = ENC( "TahomaBold.ttf" );
	strFontFileNames[ ROBOTO ] = ENC( "Roboto.ttf" );
	strFontFileNames[ ROBOTO_BOLD ] = ENC( "RobotoBold.ttf" );
	strFontFileNames[ ENVY ] = ENC( "Envy.ttf" );
	strFontFileNames[ FA ] = ENC( "FontAwesome5FreeSolid.ttf" );
	for ( auto &strFont: strFontFileNames )
		if ( !AddFont( strFont ) )
		{
			_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Unable to add font %s." ), strFont.c_str( ) );
			return false;
		}

	return true;
}

bool CDrawing::CreateD3D( )
{
	if ( ( pD3DInstance = Direct3DCreate9( DIRECT3D_VERSION ) ) == nullptr )
	{
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Unable to create D3D instance." ) );
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
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Failed to create D3D device." ) );
		return false;
	}

	bReleaseDevice = true;
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

		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Could not set device state." ) );
		return false;
	};

	if ( pState != nullptr )
	{
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, ENC( "Attempting to create state when state exists." ) );
		return false;
	}

	if ( pDevice->BeginStateBlock( ) != D3D_OK )
	{
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Could not begin state block." ) );
		fnSetState( );
		return false;
	}

	fnSetState( );
	if ( pDevice->EndStateBlock( &pState ) != D3D_OK )
	{
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Could not end state block." ) );
		return false;
	}

	return true;
}

void CDrawing::AddTexture( const texture_t &texNew )
{
	auto _New = new CDrawable< texture_t >( texNew );

	if ( !RegisterDrawable( _New ) )
		delete _New;
	else
		vecDrawables.emplace_back( _New );
}

void CDrawing::Uninitialize( )
{
	PreReset( );
	if ( pDevice && bReleaseDevice )
	{
		pDevice->Release( );
		pDevice = nullptr;
	}
}

void CDrawing::SetTarget( CApplicationWindow *pWindow )
{
	pTarget = pWindow;
}

void CDrawing::SetTarget( IDirect3DDevice9 *pNewDevice )
{
	D3DDEVICE_CREATION_PARAMETERS _CreationParameters;

	pDevice = pNewDevice;
	if ( pDevice->GetCreationParameters( &_CreationParameters ) != D3D_OK )
	{
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Unable to get creation parameters of device!" ) );
		pDevice = nullptr;
	}
	else
		pTarget = std::make_unique< CApplicationWindow >( _CreationParameters.hFocusWindow ).get( );
}

bool CDrawing::SetState( )
{
	if ( pState == nullptr )
		if ( !CreateState( ) )
			return false;

	if ( D3D_OK != pState->Apply( ) )
	{
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, ENC( "Failed to apply state block." ) );
		return false;
	}

	return true;
}

bool CDrawing::BeginFrame( )
{
	if ( !SetState( ) )
		return false;

	if ( D3D_OK != pDevice->Clear( NULL, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, NULL, NULL, NULL ) )
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, ENC( "Failed to clear device." ) );

	if ( D3D_OK != pDevice->BeginScene( ) )
	{
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, ENC( "Failed to begin scene." ) );
		return false;
	}

	return true;
}

bool CDrawing::EndFrame( )
{
	if ( pDevice->EndScene( ) != D3D_OK )
	{
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, ENC( "Failed to end scene." ) );
		return false;
	}

	const auto hrPresent = pDevice->Present( nullptr, nullptr, nullptr, nullptr );
	if ( hrPresent != D3D_OK )
	{
		if ( hrPresent == D3DERR_DEVICELOST && pDevice->TestCooperativeLevel( ) == D3DERR_DEVICENOTRESET )
		{
			_Log.Log( EPrefix::INFO, ELocation::DRAWING, ENC( "Attempting to reset device after being lost." ) );
			PreReset( );
			if ( D3D_OK != pDevice->Reset( &pParameters ) )
			{
				_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Failed to reset device!" ) );
				return false;
			}

			return Create( );
		}

		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, ENC( "Failed to present scene." ) );
		return false;
	}

	return true;
}

bool CDrawing::PreReset( )
{
	if ( pSprite )
	{
		if ( pSprite->Release( ) != D3D_OK )
		{
			_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Unable to release sprite." ) );
			return false;
		}

		pSprite = nullptr;
	}

	if ( pState )
	{
		if ( pState->Release( ) != D3D_OK )
		{
			_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Unable to release state." ) );
			return false;
		}

		pState = nullptr;
	}

	for ( auto& pDrawable : vecDrawables )
		pDrawable->Destroy( );

	return true;
}

bool CDrawing::Create( )
{
	constexpr char TEXTURE_FILENAMES[ TEXTURE_MAX ][ MAX_PATH ] // Relative to resources folder
	{
		"Cursor\\Arrow.png",
		"Cursor\\Hand.png",
		"Cursor\\I Beam.png",
		"PX Logo.png"
	};

	constexpr double TEXTURE_DIMENSIONS[ TEXTURE_MAX ][ 2 ]
	{
		{ 50.0, 50.0 },
		{ 50.0, 50.0 },
		{ 50.0, 50.0 },
		{ 32.0, 29.0 }
	};

	auto bReturn = true;

	if ( vecTextures.empty( ) )
		for ( auto i = 0; i < TEXTURE_MAX && bReturn; i++ )
			AddTexture( texture_t( { TEXTURE_DIMENSIONS[ i ][ 0 ], TEXTURE_DIMENSIONS[ i ][ 1 ] }, TEXTURE_FILENAMES[ i ] ) );

	for ( auto &texture : vecTextures )
		bReturn &= texture->Create( );

	iCursorTextureIndicies[ ARROW ] = TEXTURE_ARROW;
	iCursorTextureIndicies[ HAND ] = TEXTURE_HAND;
	iCursorTextureIndicies[ IBEAM ] = TEXTURE_IBEAM;

	if ( !( bReturn &= D3DXCreateSprite( pDevice, &pSprite ) == D3D_OK ) )
		_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Unable to create sprite." ) );

	return bReturn;
}

bool CDrawing::AddFont( const std::string &strFilename )
{
	auto &strData = RESOURCES.GetResource( strFontDirectory + strFilename );
	return libInstance != nullptr
		&& !FT_New_Memory_Face( libInstance,
								reinterpret_cast< FT_Byte* >( const_cast< char* >( &strData[ 0 ] ) ),
								strData.length( ), 0, &vecFonts.emplace_back( ) );
}

bool CDrawing::RemoveFont( std::size_t sFont )
{
	if ( libInstance != nullptr
		&& FT_Done_Face( vecFonts[ sFont ] ) )
	{
		vecFonts.erase( vecFonts.begin( ) + sFont );
		return true;
	}
	return false;
}

void CDrawing::ApplyCursor( int iCursorType )
{
	POINT pntCursor;
	RECT recWindow;

	if ( GetCursorPos( &pntCursor ) != TRUE
		|| ScreenToClient( pTarget->GetWindowHandle( ), &pntCursor ) != TRUE
		|| !pTarget->GetBounds( recWindow )
		|| pntCursor.x < 0.f || pntCursor.y < 0.f
		|| pntCursor.x > int( recWindow.right - recWindow.left )
		|| pntCursor.y > int( recWindow.bottom - recWindow.top ) )
	{
		while ( ShowCursor( TRUE ) <= 0 );
		return;
	}

	while ( ShowCursor( FALSE ) >= 0 );
	SetCursor( nullptr );

	auto &texMouse = vecTextures[ iCursorTextureIndicies[ iCursorType ] ];
	texMouse->SetDrawingLocation( vector2_t( pntCursor.x + texMouse->_TextureInfo.vecDimensions.x / 2.0 - 50.0,
		pntCursor.y + texMouse->_TextureInfo.vecDimensions.y / 2.0 - 50.0 ) );
	texMouse->Draw( );
}

bool CDrawing::IsAreaVisible( const rectangle_t &recArea )
{
	if ( recSource.empty( ) )
		return true;

	return recArea.InRectangle( recSource.top( ) );
}

CDrawing::CDrawable< texture_t >* CDrawing::GetTexture( int iTextureID )
{
	return vecTextures[ iTextureID ];
}

RECT CDrawing::GetDrawingSpace( )
{
	RECT recBuffer { };
	pDevice->GetScissorRect( &recBuffer );
	return recBuffer;
}

void CDrawing::PushDrawingSpace( rectangle_t recSpace )
{
	if ( !recSource.empty( ) )
		recSpace.Clamp( recSource.top( ) );
	else
	{
		RECT recTemp;
		pDevice->GetScissorRect( &recTemp );
		recSource.push( rectangle_t( recTemp ) );
	}

	const auto recNewSource = recSpace.ToRect( );
	recSource.push( recSpace );
	pDevice->SetScissorRect( &recNewSource );
}

void CDrawing::PopDrawingSpace( )
{
	recSource.pop( );
	const auto &recNew = recSource.top( );
	const auto recNewSource = recNew.ToRect( );
	pDevice->SetScissorRect( &recNewSource );
}

bool CDrawing::RegisterDrawable( IBaseDrawable *pDrawable )
{
	if ( pDrawable == nullptr )
		return false;

	for ( auto& pIteration : vecDrawables )
		if ( pIteration == pDrawable )
			return false;

	vecDrawables.emplace_back( pDrawable );
	return true;
}

bool CDrawing::UnregisterDrawable( IBaseDrawable *pDrawable )
{
	for ( auto z = 0u; z < vecDrawables.size( ); z++ )
		if ( vecDrawables[ z ] == pDrawable )
			return vecDrawables.erase( vecDrawables.begin( ) + z ), true;

	return false;
}

vector2_t CDrawing::GetTextDimensions( const char *szText, float flSize, std::size_t sFont )
{
	if ( libInstance == nullptr
		|| vecFonts.size( ) <= sFont
		|| vecFonts[ sFont ] == nullptr )
		return vector2_t( );

	auto &fFont = vecFonts[ sFont ];
	FT_Set_Char_Size( fFont, 0, int( flSize * powf( 2.f, 6.f ) ), 96, 96 );
	auto flTotalAdvance = 0.f;
	auto iPreviousGlyphIndex = 0;
	auto flMaxHeight = -1.f;

	for ( auto u = 0u; u < strlen( szText ); u++ )
	{
		const auto iIndex = FT_Get_Char_Index( fFont, szText[ u ] );

		if ( iPreviousGlyphIndex != 0 )
		{
			FT_Vector vecDelta;
			FT_Get_Kerning( fFont, iPreviousGlyphIndex, iIndex, FT_KERNING_DEFAULT, &vecDelta );
			flTotalAdvance += vecDelta.x >> 6;
		}

		FT_Load_Glyph( fFont, iIndex, FT_LOAD_DEFAULT );
		FT_Render_Glyph( fFont->glyph, FT_RENDER_MODE_NORMAL );

		flTotalAdvance += fFont->glyph->advance.x >> 6;
		iPreviousGlyphIndex = iIndex;
		const auto flHeight = float( fFont->glyph->metrics.height >> 6 ) + ( flSize - float( fFont->glyph->bitmap_top ) );
		if ( flHeight > flMaxHeight )
			flMaxHeight = flHeight;
	}

	return vector2_t( flTotalAdvance, flMaxHeight );
}

IDirect3DTexture9 *CDrawing::CreateTextTexture( const char *szText, float flSize, std::size_t sFont, const color_t &clrText, vector2_t &vecDimensions, EFontFlags ffFlags, float flMaxWidth /*= -1.f*/ )
{
	if ( libInstance == nullptr
		|| vecFonts.size( ) <= sFont
		|| vecFonts[ sFont ] == nullptr )
		return nullptr;

	const auto sLength = ffFlags & ICON ? 1 : strlen( szText );
	const auto dwColor = clrText.GetARGB( );
	auto &fFont = vecFonts[ sFont ];
	std::vector< glyph_row_t > vecRows { };
	auto iPreviousGlyphIndex = 0;
	auto pCurrentRow = &vecRows.emplace_back( );

	vecDimensions = vector2_t( 0.f, 1.f );
	FT_Set_Char_Size( fFont, 0, int( flSize * powf( 2.f, 6.f ) ), 96, 96 );

	for ( auto u = 0u; u < sLength; u++ )
	{
		auto iIndex = 0;

		if ( ffFlags & ICON )
		{
			char chBuffer[ sizeof( unsigned ) * 2 + 1 ] { };
			char *pBuffer = nullptr;

			for ( auto i = 0; i < sizeof( unsigned ); i++ )
				chBuffer[ i ] = '0';

			for ( auto i = sizeof( unsigned ); i < sizeof( unsigned ) * 2; i++ )
				chBuffer[ i ] = szText[ u * sizeof( unsigned ) + i - sizeof( unsigned ) ];

			iIndex = FT_Get_Char_Index( fFont, strtoul( chBuffer, &pBuffer, 16 ) );
		}
		else
			iIndex = FT_Get_Char_Index( fFont, szText[ u ] );

		if ( iPreviousGlyphIndex != 0 )
		{
			FT_Vector vecDelta;
			FT_Get_Kerning( fFont, iPreviousGlyphIndex, iIndex, FT_KERNING_DEFAULT, &vecDelta );
			pCurrentRow->AddKerning( vecDelta.x >> 6 );
		}

		FT_Load_Glyph( fFont, iIndex, FT_LOAD_DEFAULT );
		FT_Render_Glyph( fFont->glyph, FT_RENDER_MODE_NORMAL );
		pCurrentRow->AddGlyph( *fFont->glyph, flSize );
		iPreviousGlyphIndex = iIndex;

		if ( flMaxWidth != -1.f
			&& szText[ u ] == ' ' )
		{
			std::string strWord = &szText[ u ];

			strWord = strWord.substr( 0, strWord.find( ' ' ) - 1 );
			if ( GetTextDimensions( strWord.c_str( ), flSize, sFont ).x + pCurrentRow->vecRowSize.x > flMaxWidth )
				pCurrentRow = &vecRows.emplace_back( );
		}
	}

	auto iTotalVerticalAddition = 0;
	for ( auto &row: vecRows )
	{
		vecDimensions.x = std::max( vecDimensions.x, row.vecRowSize.x );
		vecDimensions.y += row.vecRowSize.y + row.iVerticalOffset;
		iTotalVerticalAddition += row.iVerticalAddition;
	}

	if ( ffFlags & DROPSHADOW )
	{
		vecDimensions.x += 1.f;
		vecDimensions.y += 1.f;
	}

	IDirect3DTexture9 *pReturn = nullptr;
	D3DLOCKED_RECT recLocked { };

	if ( D3D_OK != D3DXCreateTexture( pDevice, unsigned( vecDimensions.x ), unsigned( vecDimensions.y + iTotalVerticalAddition ), 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pReturn ) )
		return nullptr;

	pReturn->LockRect( 0, &recLocked, nullptr, 0 );
	const auto pBits = reinterpret_cast< DWORD* >( recLocked.pBits );
	auto flVerticalOffset = 0.f;

	for ( auto &rowCurrent: vecRows )
	{
		for ( auto &glCurrent: rowCurrent.vecGlyphs )
		{
			auto &glRenderable = glCurrent.glGlyph;

			for ( auto i = 0; i < int( glRenderable.bitmap.rows ); i++ )
			{
				const auto iWidth = int( glRenderable.bitmap.width );
				for ( auto j = 0; j < iWidth; j++ )
				{
					const auto iAlpha = int( glCurrent.bBitmapBuffer[ j + i * iWidth ] ) - ( UCHAR_MAX - clrText.a );
					if ( iAlpha <= 0 )
						continue;

					const auto iByte = int( glCurrent.flHorizontalOffset ) + j + int( i + rowCurrent.iVerticalOffset + int( flSize ) - int( glRenderable.bitmap_top ) + 1 ) * int( vecDimensions.x );
					if ( iByte < 0
						|| iByte > int( vecDimensions.x * ( vecDimensions.y + float( iTotalVerticalAddition ) ) ) )
						continue;

					pBits[ iByte ] = ( dwColor & 0x00FFFFFF ) | ( iAlpha << 24 );
				}
			}
		}

		flVerticalOffset += rowCurrent.vecRowSize.y;
	}

	if ( ffFlags & DROPSHADOW )
	{
		std::vector< int > vecBitsToSet { };

		for ( auto y = 0; y < int( vecDimensions.y ); y++ )
			for ( auto x = 0; x < int( vecDimensions.x ); x++ )
			{
				const auto iTest = ( y + 1 ) * int( vecDimensions.x ) + x + 1;
				const auto iCurrent = y * int( vecDimensions.x ) + x;

				if ( ( pBits[ iTest ] & 0xFF000000 ) < clrText.a
					&& ( pBits[ iCurrent ] & 0xFF000000 ) >= clrText.a )
					vecBitsToSet.emplace_back( iCurrent );
			}

		for ( auto &iBit: vecBitsToSet )
			pBits[ iBit ] = 0xFF000000;
	}

	pReturn->UnlockRect( 0 );

	return pReturn;
}

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

void CDrawing::DrawTexture( IDirect3DTexture9 *pTexture, vector2_t vecLocation )
{
	if ( pTexture == nullptr )
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, "Invalid texture to draw." );
	else
	{
		if ( _Drawing.pSprite->Begin( D3DXSPRITE_ALPHABLEND ) == D3D_OK )
		{
			vecLocation.Round( );
			auto vecNewLocation = D3DXVECTOR3( vector3_t( vecLocation ) );
			pSprite->Draw( pTexture, nullptr, nullptr, &vecNewLocation, 0xFFFFFFFF );
			pSprite->End( );
		}
		else
			_Log.Log( EPrefix::WARNING, ELocation::DRAWING, ENC( "Unable to begin sprite drawing." ) );
	}
}

//polygon_t CDrawing::Rectangle( rectangle_t recLocation, color_t clrColor )
//{
//	const auto dwColor = clrColor.GetARGB( );
//
//	vertex_t vtxVertices[ 4 ]
//	{
//		vertex_t( recLocation.x, recLocation.y, dwColor ),
//		vertex_t( recLocation.x + recLocation.w, recLocation.y, dwColor ),
//		vertex_t( recLocation.x + recLocation.w, recLocation.y + recLocation.h, dwColor ),
//		vertex_t( recLocation.x, recLocation.y + recLocation.h, dwColor )
//	};
//
//	return polygon_t( vtxVertices, 4, 2 );
//}
//
//polygon_t CDrawing::Rectangle( rectangle_t recLocation, color_t *clrColor )
//{
//	vertex_t vtxVertices[ 4 ]
//	{
//		vertex_t( recLocation.x, recLocation.y, clrColor[ rectangle_t::TOP_LEFT ].GetARGB( ) ),
//		vertex_t( recLocation.x + recLocation.w, recLocation.y, clrColor[ rectangle_t::TOP_RIGHT ].GetARGB( ) ),
//		vertex_t( recLocation.x + recLocation.w, recLocation.y + recLocation.h, clrColor[ rectangle_t::BOTTOM_RIGHT ].GetARGB( ) ),
//		vertex_t( recLocation.x, recLocation.y + recLocation.h, clrColor[ rectangle_t::BOTTOM_LEFT ].GetARGB( ) )
//	};
//
//	return polygon_t( vtxVertices, 4, 2 );
//}
//
//polygon_t CDrawing::OutlineRectangle( rectangle_t recLocation, color_t clrColor )
//{
//	const auto dwColor = clrColor.GetARGB( );
//	polygon_t lstReturn { };
//
//	lstReturn.vecVertices.emplace_back( recLocation.x, recLocation.y, dwColor );
//	lstReturn.vecVertices.emplace_back( recLocation.x + recLocation.w, recLocation.y, dwColor );
//	lstReturn.vecVertices.emplace_back( recLocation.x + recLocation.w, recLocation.y + recLocation.h, dwColor );
//	lstReturn.vecVertices.emplace_back( recLocation.x, recLocation.y + recLocation.h, dwColor );
//
//	return lstReturn;
//}
//
//polygon_t CDrawing::Line( vector2_t locStart, vector2_t locEnd, float flThickness, color_t clrColor )
//{
//	const auto locLength = locEnd - locStart;
//	const auto dwColor = clrColor.GetARGB( );
//	const auto flLength = locLength.Length( );
//	const auto vecRotationPoint = D3DXVECTOR2( locStart );
//	auto flRotation = locLength.Angle( );
//	vertex_t vtxVertices[ ]
//	{
//		vertex_t( locStart.x, locStart.y - flThickness / 2.f, dwColor ),
//		vertex_t( locStart.x + flLength, locStart.y - flThickness / 2.f, dwColor ),
//		vertex_t( locStart.x + flLength, locStart.y + flThickness / 2.f, dwColor ),
//		vertex_t( locStart.x, locStart.y + flThickness / 2.f, dwColor )
//	};
//
//	if ( locLength.x < 0.f )
//	{
//		if ( locLength.y < 0.f || locLength.y == 0.f )
//			flRotation += 180.f;
//		else
//			flRotation = 180.f - fabsf( flRotation );
//	}
//
//	for ( auto &vertex: vtxVertices )
//		vertex.Rotate( flRotation, vecRotationPoint );
//
//	return polygon_t( vtxVertices, 4, 2 );
//}

rectangle_t::rectangle_t( double x, double y, double dWidth, double dHeight ): vecLocation( x, y ), vecSize( dWidth, dHeight )
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

void CDrawing::rectangle_t::operator-=( const rectangle_t &rhs )
{
	x -= rhs.x;
	y -= rhs.y;
}

void CDrawing::rectangle_t::operator*=( double rhs )
{
	x *= rhs;
	y *= rhs;
}

void CDrawing::rectangle_t::operator/=( double rhs )
{
	x /= rhs;
	y /= rhs;
}

double CDrawing::rectangle_t::GetX( ) const
{
	return vecLocation.x;
}

double CDrawing::rectangle_t::GetY( ) const
{
	return vecLocation.y;
}

double CDrawing::rectangle_t::GetW( ) const
{
	return vecSize.x;
}

double CDrawing::rectangle_t::GetH( ) const
{
	return vecSize.y;
}

void CDrawing::rectangle_t::PutX( double x )
{
	vecLocation.x = x;
}

void CDrawing::rectangle_t::PutY( double y )
{
	vecLocation.y = y;
}

void CDrawing::rectangle_t::PutW( double w )
{
	vecSize.x = w;
}

void CDrawing::rectangle_t::PutH( double h )
{
	vecSize.y = h;
}

void rectangle_t::Clamp( const rectangle_t &recClamp )
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

bool rectangle_t::LocationInRectangle( const vector2_t &locLocation ) const
{
	return locLocation.x >= x
			&& locLocation.x <= x + w
			&& locLocation.y >= y
			&& locLocation.y <= y + h;
}

bool rectangle_t::InRectangle( const rectangle_t &recLocation ) const
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

CDrawing::glyph_t::glyph_t( FT_GlyphSlotRec_ glCurrent, float flTotalAdvance, unsigned char *bData, std::size_t sDataSize ): glGlyph( glCurrent ), flHorizontalOffset( flTotalAdvance ), bBitmapBuffer( new unsigned char[ sDataSize ] )
{
	memcpy( bBitmapBuffer, bData, sDataSize );
}

CDrawing::glyph_row_t::glyph_row_t( ) : vecGlyphs( { } ), vecRowSize( { } ), iVerticalOffset( 0 ), iVerticalAddition( 0 )
{ }

void CDrawing::glyph_row_t::AddGlyph( FT_GlyphSlotRec_ glCurrent, float flTargetSize )
{
	vecGlyphs.emplace_back( glCurrent, vecRowSize.x + glCurrent.bitmap_left, glCurrent.bitmap.buffer, ( glCurrent.metrics.height >> 6 ) * ( glCurrent.metrics.width >> 6 ) );
	vecRowSize.x += glCurrent.advance.x >> 6;

	const auto iBaselineOffset = int( flTargetSize ) - int( glCurrent.bitmap_top );
	if ( iBaselineOffset < 0 )
		iVerticalOffset = std::max( iVerticalOffset, abs( iBaselineOffset ) );

	const auto flHeight = glCurrent.bitmap.rows + iBaselineOffset + 1 - float( glCurrent.metrics.height >> 6 ) + float( glCurrent.metrics.horiBearingY >> 6 );
	if ( flHeight > vecRowSize.y )
		vecRowSize.y = flHeight;

	const auto iCurrentVerticalAddition = glCurrent.bitmap.rows + iBaselineOffset + 1 - int( flHeight );
	if ( iCurrentVerticalAddition > iVerticalAddition )
		iVerticalAddition = iCurrentVerticalAddition;
}

void CDrawing::glyph_row_t::AddKerning( float flMagnitude )
{
	vecRowSize.x += flMagnitude;
}

text_t::text_t( ): strText( std::string( ) ), iFont( 0 ), iSize( 0 ), vecDimensions( vector2_t( ) ), pText( nullptr )
{ }

text_t::text_t( const std::string &_strText, int _iFont, int _iSize, int _iHorizontalAlignment, int _iVerticalAlignment ) : strText( _strText ), iFont( _iFont ), iSize( _iSize ),
																															iHorizontalAlignment( _iHorizontalAlignment ), iVerticalAlignment( _iVerticalAlignment ), vecDimensions( vector2_t( ) ), pText( nullptr )
{ }

text_t::~text_t( )
{
	if ( pText )
	{
		pText->Release( );
		pText = nullptr;
	}
}

bool text_t::Initialize( const color_t &clrText, EFontFlags ffFlags )
{
	if ( pText )
	{
		pText->Release( );
		pText = nullptr;
	}

	return ( pText = _Drawing.CreateTextTexture( strText.c_str( ), iSize, iFont, clrText, vecDimensions, ffFlags ) ) != nullptr;
}

void text_t::ChangeText( const text_t &txtNew, const color_t &clrText, EFontFlags ffFlags )
{
	if ( pText )
	{
		pText->Release( );
		pText = nullptr;
	}

	*this = txtNew;
	Initialize( clrText, ffFlags );
}

vector2_t text_t::GetDimensions( ) const
{
	return vecDimensions;
}

float text_t::GetWidth( ) const
{
	return GetDimensions( ).x;
}

float text_t::GetHeight( ) const
{
	return GetDimensions( ).y;
}

bool text_t::Initialized( ) const
{
	return pText != nullptr;
}

void text_t::Draw( const vector2_t &locLocation )
{
	if ( pText == nullptr )
		return;

	_Drawing.DrawTexture( pText, locLocation );
}

void text_t::Draw( const rectangle_t &recUsableSpace )
{
	vector2_t locLocation { };

	switch ( iHorizontalAlignment )
	{
		case LEFT:
		{
			locLocation.x = recUsableSpace.x;
		}
		break;

		case CENTER:
		{
			locLocation.x = recUsableSpace.x + recUsableSpace.w / 2.0 - GetWidth( ) / 2.0;
		}
		break;

		case RIGHT:
		{
			locLocation.x = recUsableSpace.x + recUsableSpace.w - GetWidth( );
		}
		break;

		default:
			return;
	}

	switch ( iVerticalAlignment )
	{
		case TOP:
		{
			locLocation.y = recUsableSpace.y;
		}
		break;

		case CENTER:
		{
			locLocation.y = recUsableSpace.y + recUsableSpace.h / 2.0 - GetHeight( ) / 2.0;
		}
		break;

		case BOTTOM:
		{
			locLocation.y = recUsableSpace.y + recUsableSpace.h - GetHeight( );
		}
		break;

		default:
			return;
	}

	return Draw( locLocation );
}

void text_t::Destruct( )
{
	pText->Release( );
	memset( this, 0, sizeof( decltype( *this ) ) );
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
	for ( auto &vector: flVectors )
		vector = roundf( vector );

	return *this;
}

texture_t::texture_t( vector2_t vecDimensions, const std::string &_strName ): vecDimensions( vecDimensions ), strFileName( _strName )
{ }

CDrawing _Drawing;
