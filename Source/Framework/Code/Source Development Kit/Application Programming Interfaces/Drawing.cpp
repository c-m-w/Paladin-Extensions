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
	auto &last = vecTextures.emplace_back( std::pair< texture_t, std::pair< D3DXIMAGE_INFO, IDirect3DTexture9* > >( texNew, std::pair< D3DXIMAGE_INFO, IDirect3DTexture9* >( D3DXIMAGE_INFO( ), nullptr ) ) );
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

	constexpr unsigned TEXTURE_DIMENSIONS[ TEXTURE_MAX ][ 2 ]
	{
		{ 50, 50 },
		{ 50, 50 },
		{ 50, 50 },
		{ 32, 29 }
	};

	auto bReturn = true;

	if ( vecTextures.empty( ) )
		for ( auto i = 0; i < TEXTURE_MAX && bReturn; i++ )
			AddTexture( texture_t( TEXTURE_DIMENSIONS[ i ][ 0 ], TEXTURE_DIMENSIONS[ i ][ 1 ], TEXTURE_FILENAMES[ i ] ) );

	for ( auto &texture : vecTextures )
	{
		auto& strTextureData = RESOURCES.GetResource( texture.first.strName );

		if ( !( bReturn &= D3D_OK == D3DXCreateTextureFromFileInMemoryEx( pDevice, &strTextureData[ 0 ], strTextureData.length( ), texture.first.uWidth, texture.first.uHeight, D3DX_FROM_FILE,
																  D3DUSAGE_DYNAMIC, D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &texture.second.first,
																  nullptr, &texture.second.second ) ) )
			_Log.Log( EPrefix::ERROR, ELocation::DRAWING, ENC( "Unable to create texture %s from memory." ), texture.first.strName.c_str( ) );
	}

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

	auto &texMouse = vecTextures[ iCursorTextureIndicies[ iCursorType ] ].first;
	DrawTexture( iCursorTextureIndicies[ iCursorType ], location_t( pntCursor.x + texMouse.uWidth / 2.f - 50.f, pntCursor.y + texMouse.uHeight / 2.f - 50.f ) );
}

bool CDrawing::IsAreaVisible( const rectangle_t &recArea )
{
	if ( recSource.empty( ) )
		return true;

	return recArea.InRectangle( recSource.top( ) );
}

texture_renderable_t &CDrawing::GetTexture( int iTextureID )
{
	return vecTextures[ iTextureID ];
}

void CDrawing::RenderTexture( int iTextureID, const location_t &locTexture )
{
	DrawTexture( iTextureID, locTexture );
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

location_t CDrawing::GetTextDimensions( const char *szText, float flSize, std::size_t sFont )
{
	if ( libInstance == nullptr
		|| vecFonts.size( ) <= sFont
		|| vecFonts[ sFont ] == nullptr )
		return location_t( );

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

	return location_t( flTotalAdvance, flMaxHeight );
}

IDirect3DTexture9 *CDrawing::CreateTextTexture( const char *szText, float flSize, std::size_t sFont, const color_t &clrText, location_t &locDimensions, EFontFlags ffFlags, float flMaxWidth /*= -1.f*/ )
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

	locDimensions = location_t( 0.f, 1.f );
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
			if ( GetTextDimensions( strWord.c_str( ), flSize, sFont ).x + pCurrentRow->locRowSize.x > flMaxWidth )
				pCurrentRow = &vecRows.emplace_back( );
		}
	}

	auto iTotalVerticalAddition = 0;
	for ( auto &row: vecRows )
	{
		locDimensions.x = std::max( locDimensions.x, row.locRowSize.x );
		locDimensions.y += row.locRowSize.y + row.iVerticalOffset;
		iTotalVerticalAddition += row.iVerticalAddition;
	}

	if ( ffFlags & DROPSHADOW )
	{
		locDimensions.x += 1.f;
		locDimensions.y += 1.f;
	}

	IDirect3DTexture9 *pReturn = nullptr;
	D3DLOCKED_RECT recLocked { };

	if ( D3D_OK != D3DXCreateTexture( pDevice, unsigned( locDimensions.x ), unsigned( locDimensions.y + iTotalVerticalAddition ), 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pReturn ) )
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

					const auto iByte = int( glCurrent.flHorizontalOffset ) + j + int( i + rowCurrent.iVerticalOffset + int( flSize ) - int( glRenderable.bitmap_top ) + 1 ) * int( locDimensions.x );
					if ( iByte < 0
						|| iByte > int( locDimensions.x * ( locDimensions.y + float( iTotalVerticalAddition ) ) ) )
						continue;

					pBits[ iByte ] = ( dwColor & 0x00FFFFFF ) | ( iAlpha << 24 );
				}
			}
		}

		flVerticalOffset += rowCurrent.locRowSize.y;
	}

	if ( ffFlags & DROPSHADOW )
	{
		std::vector< int > vecBitsToSet { };

		for ( auto y = 0; y < int( locDimensions.y ); y++ )
			for ( auto x = 0; x < int( locDimensions.x ); x++ )
			{
				const auto iTest = ( y + 1 ) * int( locDimensions.x ) + x + 1;
				const auto iCurrent = y * int( locDimensions.x ) + x;

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

void CDrawing::DrawPolygon( const polygon_buffer_t &pbPolygon, bool bRelease /*= false*/ )
{
	if ( D3D_OK == pDevice->SetStreamSource( NULL, pbPolygon.pVertexBuffer, NULL, sizeof( vertex_t ) ) )
		pDevice->DrawPrimitive( pbPolygon.ptDraw, 0, pbPolygon.sPrimitives );

	if ( bRelease )
		pbPolygon.pVertexBuffer->Release( );
}

void CDrawing::DrawTexture( IDirect3DTexture9 *pTexture, const location_t &locLocation )
{
	if ( pTexture == nullptr )
		throw std::runtime_error( ENC( "Invalid drawing texture." ) );

	if ( pSprite->Begin( D3DXSPRITE_ALPHABLEND ) == D3D_OK )
	{
		D3DXVECTOR3 vecLocation( roundf( locLocation.x ), roundf( locLocation.y ), 0.f );
		pSprite->Draw( pTexture, nullptr, nullptr, &vecLocation, 0xFFFFFFFF );
		pSprite->End( );
	}
	else
		_Log.Log( EPrefix::WARNING, ELocation::DRAWING, ENC( "Unable to begin sprite drawing." ) );
}

void CDrawing::DrawTexture( int iTextureID, const location_t &locLocation )
{
	return DrawTexture( vecTextures[ iTextureID ].second.second, locLocation );
}

polygon_t CDrawing::Rectangle( rectangle_t recLocation, color_t clrColor )
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

polygon_t CDrawing::Rectangle( rectangle_t recLocation, color_t *clrColor )
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

#define ROUNDING_VERTICES ( std::size_t( ceilf( flRadius * D3DX_PI / 2.f ) ) )

polygon_t CDrawing::OutlineRectangle( rectangle_t recLocation, color_t clrColor )
{
	const auto dwColor = clrColor.GetARGB( );
	polygon_t lstReturn { };

	lstReturn.vecVertices.emplace_back( recLocation.x, recLocation.y, dwColor );
	lstReturn.vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y, dwColor );
	lstReturn.vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight, dwColor );
	lstReturn.vecVertices.emplace_back( recLocation.x, recLocation.y + recLocation.flHeight, dwColor );

	return lstReturn;
}

polygon_t CDrawing::RoundedRectangle( rectangle_t recLocation, color_t clrColor, bool *bRounding, float flRounding )
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_LEFT ], 0.25f );
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_RIGHT ], 0.25f );
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_RIGHT ], 0.25f );
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_LEFT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( vertex_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ], dwColor ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y + recLocation.flHeight, dwColor );

	return polygon_t( &vecVertices[ 0 ], vecVertices.size( ), sPrimitives );
}

polygon_t CDrawing::OutlineRoundedRectangle( rectangle_t recLocation, color_t clrColor, bool *bRounding, float flRounding )
{
	constexpr float ROTATIONS[ rectangle_t::MAX ] { 270.f, 0.f, 90.f, 180.f };
	const auto flRadius = roundf( std::min( recLocation.flHeight, recLocation.flWidth ) / 2.f * flRounding );
	const auto uResolution = ROUNDING_VERTICES;
	std::vector< location_t > vecVertices { };
	auto sPrimitives { 4u };

	if ( bRounding[ rectangle_t::TOP_LEFT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + flRadius, recLocation.y + flRadius ), flRadius, uResolution );
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_LEFT ], 0.25f );

		vecVertices.emplace_back( location_t( recLocation.x, recLocation.y + flRadius ) );
		for ( auto u = 2u; u <= uResolution; u++ )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		vecVertices.emplace_back( location_t( recLocation.x + flRadius, recLocation.y ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y );

	if ( bRounding[ rectangle_t::TOP_RIGHT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + flRadius ), flRadius, uResolution );
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_RIGHT ], 0.25f );

		vecVertices.emplace_back( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y ) );
		for ( auto u = 1u; u <= uResolution - 1; u++ )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		vecVertices.emplace_back( location_t( recLocation.x + recLocation.flWidth, recLocation.y + flRadius ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y );

	if ( bRounding[ rectangle_t::BOTTOM_RIGHT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + recLocation.flHeight - flRadius ), flRadius, uResolution );
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_RIGHT ], 0.25f );

		vecVertices.emplace_back( location_t( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight - flRadius ) );
		for ( auto u = 2u; u <= uResolution; u++ )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ] ) );

		vecVertices.emplace_back( location_t( recLocation.x + recLocation.flWidth - flRadius, recLocation.y + recLocation.flHeight ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight );

	if ( bRounding[ rectangle_t::BOTTOM_LEFT ] )
	{
		const auto cclTopLeft = circle_t( location_t( recLocation.x + flRadius, recLocation.y + recLocation.flHeight - flRadius ), flRadius, uResolution );
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_LEFT ], 0.25f );

		vecVertices.emplace_back( location_t( recLocation.x + flRadius, recLocation.y + recLocation.flHeight ) );
		for ( auto u = 2u; u <= uResolution; u++ )
			vecVertices.emplace_back( location_t( pVertices[ u ].flVectors[ 0 ] + 0.5f, pVertices[ u ].flVectors[ 1 ] ) );

		vecVertices.emplace_back( location_t( recLocation.x, recLocation.y + recLocation.flHeight - flRadius ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y + recLocation.flHeight );

	polygon_t polReturn;
	polReturn.sPrimitives = sPrimitives;
	for ( auto &location: vecVertices )
		polReturn.vecVertices.emplace_back( roundf( location.x ), roundf( location.y ), clrColor.GetARGB( ) );

	polReturn.vecVertices.emplace_back( polReturn.vecVertices[ 0 ] );
	return polReturn;
}

polygon_t CDrawing::OutlineSpacedRoundedRectangle( rectangle_t recLocation, color_t clrColor, bool *bRounding, float flRounding, float flSpacing )
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_LEFT ], 0.25f );
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_LEFT ], 0.25f );
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_RIGHT ], 0.25f );
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_RIGHT ], 0.25f );
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
	for ( auto &location: vecVertices )
		polReturn.vecVertices.emplace_back( location.x, location.y, dwColor );

	polReturn.vecVertices.emplace_back( vertex_t( polReturn.vecVertices[ 0 ].flVectors[ 0 ] + flSpacing, polReturn.vecVertices[ 0 ].flVectors[ 1 ], dwColor ) );
	return polReturn;
}

polygon_t CDrawing::RoundedRectangle( rectangle_t recLocation, color_t *clrColor, bool *bRounding, float flRounding )
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::TOP_RIGHT ], 0.25f );
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_RIGHT ], 0.25f );
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
		const vertex_t *pVertices = cclTopLeft.GetPoints( ROTATIONS[ rectangle_t::BOTTOM_LEFT ], 0.25f );
		for ( auto u = 1u; u <= uResolution + 1; u++ )
			vecVertices.emplace_back( vertex_t( pVertices[ u ].flVectors[ 0 ], pVertices[ u ].flVectors[ 1 ], clrColor[ rectangle_t::BOTTOM_LEFT ].GetARGB( ) ) );

		delete[ ] pVertices;
		sPrimitives += uResolution;
	}
	else
		vecVertices.emplace_back( recLocation.x, recLocation.y + recLocation.flHeight, clrColor[ rectangle_t::BOTTOM_LEFT ].GetARGB( ) );

	return polygon_t( vecVertices, sPrimitives );
}

polygon_t CDrawing::Triangle( location_t locFirst, location_t locSecond, location_t locThird, color_t clrColor )
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

polygon_t CDrawing::Triangle( triangle_t trLocation, color_t *clrColor )
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

polygon_t CDrawing::Circle( circle_t circle, color_t clrColor, float flStartAngle, float flRatio )
{
	const auto pPoints = circle.GetPoints( flStartAngle, flRatio );
	const auto dwColor = clrColor.GetARGB( );

	for ( auto u = 0u; u < circle.sResolution + 2u; u++ )
		pPoints[ u ].dwColor = dwColor;

	const auto polReturn = polygon_t( pPoints, circle.sResolution + 2u, circle.sResolution );

	delete[ ] pPoints;

	return polReturn;
}

polygon_t CDrawing::OutlineCircle( circle_t circle, color_t clrColor, float flStartAngle, float flRatio )
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

polygon_t CDrawing::Circle( circle_t circle, color_t clrCenter, color_t clrOuter, float flStartAngle, float flRatio )
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

polygon_t CDrawing::Circle( circle_t circle, color_t *pColors, float flStartAngle, float flRatio )
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

polygon_t CDrawing::Line( location_t locStart, location_t locEnd, float flThickness, color_t clrColor )
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

	for ( auto &vertex: vtxVertices )
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

CDrawing::glyph_t::glyph_t( FT_GlyphSlotRec_ glCurrent, float flTotalAdvance, unsigned char *bData, std::size_t sDataSize ): glGlyph( glCurrent ), flHorizontalOffset( flTotalAdvance ), bBitmapBuffer( new unsigned char[ sDataSize ] )
{
	memcpy( bBitmapBuffer, bData, sDataSize );
}

CDrawing::glyph_row_t::glyph_row_t( ) : vecGlyphs( { } ), locRowSize( { } ), iVerticalOffset( 0 ), iVerticalAddition( 0 )
{ }

void CDrawing::glyph_row_t::AddGlyph( FT_GlyphSlotRec_ glCurrent, float flTargetSize )
{
	vecGlyphs.emplace_back( glCurrent, locRowSize.x + glCurrent.bitmap_left, glCurrent.bitmap.buffer, ( glCurrent.metrics.height >> 6 ) * ( glCurrent.metrics.width >> 6 ) );
	locRowSize.x += glCurrent.advance.x >> 6;

	const auto iBaselineOffset = int( flTargetSize ) - int( glCurrent.bitmap_top );
	if ( iBaselineOffset < 0 )
		iVerticalOffset = std::max( iVerticalOffset, abs( iBaselineOffset ) );

	const auto flHeight = glCurrent.bitmap.rows + iBaselineOffset + 1 - float( glCurrent.metrics.height >> 6 ) + float( glCurrent.metrics.horiBearingY >> 6 );
	if ( flHeight > locRowSize.y )
		locRowSize.y = flHeight;

	const auto iCurrentVerticalAddition = glCurrent.bitmap.rows + iBaselineOffset + 1 - int( flHeight );
	if ( iCurrentVerticalAddition > iVerticalAddition )
		iVerticalAddition = iCurrentVerticalAddition;
}

void CDrawing::glyph_row_t::AddKerning( float flMagnitude )
{
	locRowSize.x += flMagnitude;
}

text_t::text_t( ): strText( std::string( ) ), iFont( 0 ), iSize( 0 ), locDimensions( location_t( ) ), pText( nullptr )
{ }

text_t::text_t( const std::string &_strText, int _iFont, int _iSize, int _iHorizontalAlignment, int _iVerticalAlignment ) : strText( _strText ), iFont( _iFont ), iSize( _iSize ),
																															iHorizontalAlignment( _iHorizontalAlignment ), iVerticalAlignment( _iVerticalAlignment ), locDimensions( location_t( ) ), pText( nullptr )
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

	return ( pText = _Drawing.CreateTextTexture( strText.c_str( ), iSize, iFont, clrText, locDimensions, ffFlags ) ) != nullptr;
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

location_t text_t::GetDimensions( ) const
{
	return locDimensions;
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

void text_t::Draw( const location_t &locLocation )
{
	if ( pText == nullptr )
		return;

	_Drawing.DrawTexture( pText, locLocation );
}

void text_t::Draw( const rectangle_t &recUsableSpace )
{
	location_t locLocation { };

	switch ( iHorizontalAlignment )
	{
		case LEFT:
		{
			locLocation.x = recUsableSpace.x;
		}
		break;

		case CENTER:
		{
			locLocation.x = recUsableSpace.x + recUsableSpace.flWidth / 2.f - GetWidth( ) / 2.f;
		}
		break;

		case RIGHT:
		{
			locLocation.x = recUsableSpace.x + recUsableSpace.flWidth - GetWidth( );
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
			locLocation.y = recUsableSpace.y + recUsableSpace.flHeight / 2.f - GetHeight( ) / 2.f;
		}
		break;

		case BOTTOM:
		{
			locLocation.y = recUsableSpace.y + recUsableSpace.flHeight - GetHeight( );
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

	for ( auto &_Vertex: vecTemp )
	{
		_Vertex.flVectors[ 0 ] += recRelative.x;
		_Vertex.flVectors[ 1 ] += recRelative.y;
		_Vertex.dwColor = dwColor;
	}
	_Drawing.Polygon( &vecTemp[ 0 ], vecTemp.size( ), sPrimitives );
}

void polygon_t::Join( const polygon_t &other )
{
	for ( const auto &vertex: other.vecVertices )
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

	for ( auto &_Vertex: vecTemp )
	{
		_Vertex.flVectors[ 0 ] += recRelative.x;
		_Vertex.flVectors[ 1 ] += recRelative.y;
	}
	_Drawing.Polygon( &vecTemp[ 0 ], vecTemp.size( ), sPrimitives );
}

polygon_buffer_t polygon_t::GetBuffer( D3DPRIMITIVETYPE ptDraw /*= D3DPT_TRIANGLEFAN*/ )
{
	if ( vecVertices.empty( ) )
		throw std::runtime_error( ENC( "Invalid buffer vertices." ) );

	return polygon_buffer_t( _Drawing.ConstructPolygon( &vecVertices[ 0 ], vecVertices.size( ) ), sPrimitives, ptDraw );
}

texture_t::texture_t( unsigned _uWidth, unsigned _uHeight, const std::string &_strName ): uWidth( _uWidth ), uHeight( _uHeight ), strName( _strName )
{ }

CDrawing _Drawing;
