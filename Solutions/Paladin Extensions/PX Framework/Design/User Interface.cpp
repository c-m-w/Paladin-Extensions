/// User Interface.cpp

// Nuklear
#include "PX Precompiled.hpp"
#define PX_NUKLEAR_IMPLEMENTATION
#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::UI
{
	namespace Manager
	{
		cstr_t	szWindowTitle = PX_XOR( "Paladin Extensions" );
		auto	szApplicationTitle = static_cast< char* >( malloc( 32 ) );
		unsigned uNuklearWindowWidth, uNuklearWindowHeight;
		struct nk_rect recWindow;

		nk_font_atlas* pAtlas;
		std::deque< nk_font* > dqFonts;
		struct nk_rect recComboboxWindowBounds;
		bool bDrawComboboxArrow = false;

		unsigned uTooltipCounter, uSliderIntCounter, uSliderFloatCounter;
		std::deque< moment_t > mmtStart;
		constexpr nk_color clrTextActive { 255, 255, 255, 255 }, clrBlue { 33, 150, 243, 255 }, clrDarkBlue { 43, 60, 75, 255 }, clrBackground { 56, 60, 66, 255 }, clrLightBackground { 61, 65, 72, 255 },
			clrDarkBackground { 45, 50, 56, 255 }, clrBorder { 80, 84, 89, 255 }, clrToolbox { 42, 44, 48, 255 }, clrHeader { 33, 36, 40, 255 }, clrBlueActive { 54, 70, 84, 255 },
			clrBlueHover { 54, 70, 84, 200 }, clrBlueDormant { 43, 60, 75, 255 }, clrTextDormant { 175, 180, 187, 255 }, clrDisabled { 54, 64, 73, 255 };
		nk_color clrColorTable[ NK_COLOR_COUNT ] { };

		nk_style_button btnTopActive { }, btnTop { }, btnRegularActive { }, btnRegular { }, btnDisabled { }, btnSpecialActive { }, btnSpecial { }, btnCombo { }, btnComboActive { };

		LPD3DXSPRITE pBufferSprite;


		nk_font* PX_API AddFont( Types::str_t strFontFileName, unsigned uFontSize, unsigned uFontAwesomeSize = 0 )
		{
			Types::str_t strFontDirectory( PX_XOR( R"(C:\Windows\Fonts\)" ) );

			const auto flFontAwesomeSize = float( uFontAwesomeSize ? uFontAwesomeSize : uFontSize );
			auto fcFontAwesome = nk_font_config( flFontAwesomeSize );
			static constexpr nk_rune rnIconRange[ ] { ICON_MIN_FA, ICON_MAX_FA, 0 };
			fcFontAwesome.range = rnIconRange;
			fcFontAwesome.merge_mode = 1;

			auto pFont = nk_font_atlas_add_from_file( pAtlas, ( strFontDirectory + strFontFileName ).c_str( ), float( uFontSize ), nullptr );
			nk_font_atlas_add_from_file( pAtlas, ( strFontDirectory + PX_XOR( "FontAwesome.ttf" ) ).c_str( ), flFontAwesomeSize, &fcFontAwesome );
			return pFont;
		}

		void PX_API InitializeNuklear( )
		{
			pContext = nk_d3d9_init( pDevice, uWindowWidth, uWindowHeight );
			recWindow.w = float( uNuklearWindowWidth );
			recWindow.h = float( uNuklearWindowHeight );

			if ( !dqFonts.empty( ) )
				dqFonts.clear( );

			nk_d3d9_font_stash_begin( &pAtlas );
			dqFonts.emplace_back( AddFont( PX_XOR( "tahoma.ttf" ), 16 ) );
			dqFonts.emplace_back( AddFont( PX_XOR( "TahomaBold.ttf" ), 16 ) );
			dqFonts.emplace_back( AddFont( PX_XOR( "Roboto.ttf" ), 26 ) );
			dqFonts.emplace_back( AddFont( PX_XOR( "RobotoBold.ttf" ), 24 ) );
			dqFonts.emplace_back( AddFont( PX_XOR( "Roboto.ttf" ), 14, 14 ) );
			dqFonts.emplace_back( AddFont( PX_XOR( "RobotoBold.ttf" ), 16, 18 ) );
			dqFonts.emplace_back( AddFont( PX_XOR( "Envy.ttf" ), 14 ) );
			nk_d3d9_font_stash_end( );

			px_assert( dqFonts.size( ) == FNT_MAX );

			clrColorTable[ NK_COLOR_TEXT ] = nk_rgba( 255, 255, 255, 255 );
			clrColorTable[ NK_COLOR_WINDOW ] = nk_rgba( 45, 50, 56, 255 );
			clrColorTable[ NK_COLOR_HEADER ] = nk_rgba( 45, 50, 56, 255 );
			clrColorTable[ NK_COLOR_BORDER ] = nk_rgba( 80, 84, 89, 255 );
			clrColorTable[ NK_COLOR_BUTTON ] = nk_rgba( 48, 83, 111, 255 );
			clrColorTable[ NK_COLOR_BUTTON_HOVER ] = nk_rgba( 58, 93, 121, 255 );
			clrColorTable[ NK_COLOR_BUTTON_ACTIVE ] = nk_rgba( 68, 103, 131, 255 );
			clrColorTable[ NK_COLOR_TOGGLE ] = nk_rgba( 42, 44, 48, 255 );
			clrColorTable[ NK_COLOR_TOGGLE_HOVER ] = nk_rgba( 42, 44, 48, 255 );
			clrColorTable[ NK_COLOR_TOGGLE_CURSOR ] = nk_rgba( 48, 83, 111, 255 );
			clrColorTable[ NK_COLOR_SELECT ] = nk_rgba( 57, 67, 61, 255 );
			clrColorTable[ NK_COLOR_SELECT_ACTIVE ] = nk_rgba( 48, 83, 111, 255 );
			clrColorTable[ NK_COLOR_SLIDER ] = nk_rgba( 42, 44, 48, 255 );
			clrColorTable[ NK_COLOR_SLIDER_CURSOR ] = nk_rgba( 53, 88, 116, 255 );
			clrColorTable[ NK_COLOR_SLIDER_CURSOR_HOVER ] = nk_rgba( 58, 93, 121, 255 );
			clrColorTable[ NK_COLOR_SLIDER_CURSOR_ACTIVE ] = nk_rgba( 40, 40, 40, 255 );
			clrColorTable[ NK_COLOR_PROPERTY ] = nk_rgba( 50, 58, 61, 255 );
			clrColorTable[ NK_COLOR_EDIT ] = nk_rgba( 50, 58, 61, 225 );
			clrColorTable[ NK_COLOR_EDIT_CURSOR ] = nk_rgba( 210, 210, 210, 255 );
			clrColorTable[ NK_COLOR_COMBO ] = nk_rgba( 50, 58, 61, 255 );
			clrColorTable[ NK_COLOR_CHART ] = nk_rgba( 50, 58, 61, 255 );
			clrColorTable[ NK_COLOR_CHART_COLOR ] = nk_rgba( 48, 83, 111, 255 );
			clrColorTable[ NK_COLOR_CHART_COLOR_HIGHLIGHT ] = nk_rgba( 255, 0, 0, 255 );
			clrColorTable[ NK_COLOR_SCROLLBAR ] = nk_rgba( 48, 83, 111, 255 );
			clrColorTable[ NK_COLOR_SCROLLBAR_CURSOR ] = nk_rgba( 48, 83, 111, 255 );
			clrColorTable[ NK_COLOR_SCROLLBAR_CURSOR_HOVER ] = nk_rgba( 58, 93, 121, 255 );
			clrColorTable[ NK_COLOR_SCROLLBAR_CURSOR_ACTIVE ] = nk_rgba( 68, 103, 131, 255 );
			clrColorTable[ NK_COLOR_TAB_HEADER ] = nk_rgba( 48, 83, 111, 255 );
			nk_style_from_table( pContext, clrColorTable );

			pContext->style.window.header.close_symbol = NK_SYMBOL_NONE;
			pContext->style.window.header.close_button.text_active = nk_rgba( 43, 60, 75, 255 );
			pContext->style.window.header.close_button.text_hover = nk_rgba( 43, 60, 75, 255 );
			pContext->style.window.header.close_button.text_normal = nk_rgba( 33, 150, 243, 255 );
			pContext->style.window.rounding = 5.f;
			pContext->style.window.padding = nk_vec2( 0, 10 );
			pContext->style.edit.row_padding = 0;
			pContext->style.button.rounding = 3.f;
			pContext->style.button.border = 1;
			pContext->style.button.padding = nk_vec2( 0.f, 0.f );
			pContext->style.button.border_color = nk_rgba( 34, 37, 41, 255 );

			pContext->style.window.tooltip_border = 0.f;
			pContext->style.window.background = clrHeader;

			pContext->style.combo.label_active = nk_rgba( 255, 255, 255, 255 );
			pContext->style.combo.label_hover = nk_rgba( 255, 255, 255, 255 );
			pContext->style.combo.label_normal = nk_rgba( 175, 180, 187, 255 );
			pContext->style.combo.active.data.color = nk_rgba( 61, 65, 72, 255 );
			pContext->style.combo.hover.data.color = nk_rgba( 61, 65, 72, 255 );
			pContext->style.combo.normal.data.color = nk_rgba( 56, 60, 66, 255 );
			pContext->style.combo.symbol_active = nk_rgba( 61, 65, 72, 255 );
			pContext->style.combo.symbol_hover = nk_rgba( 61, 65, 72, 255 );
			pContext->style.combo.symbol_normal = nk_rgba( 56, 60, 66, 255 );
			pContext->style.combo.sym_active = NK_SYMBOL_NONE;
			pContext->style.combo.sym_hover = NK_SYMBOL_NONE;
			pContext->style.combo.sym_normal = NK_SYMBOL_NONE;
			pContext->style.combo.border = 1.f;
			pContext->style.combo.border_color = nk_rgba( 80, 84, 89, 255 );
			pContext->style.combo.rounding = 2.f;
			pContext->style.combo.content_padding = nk_vec2( 8, 0 );
			pContext->style.combo.button_padding = nk_vec2( 0, 0 );
			pContext->style.window.combo_padding = nk_vec2( 0, 0 );
			pContext->style.window.min_row_height_padding = 0;
			pContext->style.window.group_padding = nk_vec2( 0, 0 );

			pContext->style.edit.border = 1.f;
			pContext->style.edit.border_color = nk_rgba( 80, 84, 89, 255 );
			pContext->style.edit.padding = nk_vec2( 5, 0 );
			pContext->style.edit.rounding = 2.f;
			pContext->style.edit.active.data.color = nk_rgba( 61, 65, 72, 255 );
			pContext->style.edit.hover.data.color = nk_rgba( 61, 65, 72, 255 );
			pContext->style.edit.normal.data.color = nk_rgba( 56, 60, 66, 255 );
			pContext->style.edit.text_active = nk_rgba( 255, 255, 255, 255 );
			pContext->style.edit.text_hover = nk_rgba( 255, 255, 255, 255 );
			pContext->style.edit.text_normal = nk_rgba( 175, 180, 187, 255 );
			pContext->style.edit.cursor_text_normal = nk_rgba( 255, 255, 255, 255 );
			pContext->style.edit.cursor_text_hover = nk_rgba( 255, 255, 255, 255 );
			pContext->style.edit.selected_text_hover = nk_rgba( 255, 255, 255, 255 );
			pContext->style.edit.selected_text_normal = nk_rgba( 255, 255, 255, 255 );
			pContext->style.edit.cursor_hover = nk_rgba( 33, 150, 243, 255 );
			pContext->style.edit.cursor_normal = nk_rgba( 11, 62, 146, 255 );
			pContext->style.edit.selected_hover = nk_rgba( 11, 62, 146, 255 );
			pContext->style.edit.cursor_size = 1.f;

			pContext->style.slider.bar_height = 5.f;
			pContext->style.slider.border = 1.f;
			pContext->style.slider.bar_filled = nk_rgba( 33, 150, 243, 170 );
			pContext->style.slider.bar_normal = nk_rgba( 43, 60, 75, 255 );
			pContext->style.slider.cursor_size = nk_vec2( 8, 8 );
			pContext->style.slider.cursor_active.data.color = nk_rgba( 33, 150, 243, 255 );
			pContext->style.slider.cursor_hover.data.color = nk_rgba( 33, 150, 243, 255 );
			pContext->style.slider.cursor_normal.data.color = nk_rgba( 43, 60, 75, 255 );
			pContext->style.slider.padding = nk_vec2( 0, 0 );

			btnTopActive.rounding = 3.f;
			btnTopActive.padding = nk_vec2( 0, 0 );
			btnTopActive.active.data.color = nk_rgba( 61, 65, 72, 255 );
			btnTopActive.hover.data.color = nk_rgba( 61, 65, 72, 255 );
			btnTopActive.normal.data.color = nk_rgba( 61, 65, 72, 255 );
			btnTopActive.text_active = nk_rgba( 33, 150, 243, 255 );
			btnTopActive.text_hover = nk_rgba( 33, 150, 243, 255 );
			btnTopActive.text_normal = nk_rgba( 33, 150, 243, 255 );
			btnTopActive.text_alignment = NK_TEXT_CENTERED;

			btnTop.rounding = 3.f;
			btnTop.padding = nk_vec2( 0, 0 );
			btnTop.active.data.color = nk_rgba( 61, 65, 72, 255 );
			btnTop.hover.data.color = nk_rgba( 33, 36, 40, 255 );
			btnTop.normal.data.color = nk_rgba( 33, 36, 40, 255 );
			btnTop.text_active = nk_rgba( 175, 180, 187, 255 );
			btnTop.text_hover = nk_rgba( 255, 255, 255, 255 );
			btnTop.text_normal = nk_rgba( 175, 180, 187, 255 );
			btnTop.text_alignment = NK_TEXT_CENTERED;

			btnRegularActive.rounding = 0;
			btnRegularActive.padding = nk_vec2( 12, 0 );
			btnRegularActive.active.data.color = nk_rgba( 0, 0, 0, 0 );
			btnRegularActive.hover.data.color = nk_rgba( 0, 0, 0, 0 );
			btnRegularActive.normal.data.color = nk_rgba( 0, 0, 0, 0 );
			btnRegularActive.text_active = nk_rgba( 255, 255, 255, 255 );
			btnRegularActive.text_hover = nk_rgba( 255, 255, 255, 255 );
			btnRegularActive.text_normal = nk_rgba( 33, 150, 243, 255 );
			btnRegularActive.text_alignment = NK_TEXT_LEFT;

			btnRegular.rounding = 0;
			btnRegular.padding = nk_vec2( 12, 0 );
			btnRegular.active.data.color = nk_rgba( 61, 65, 72, 255 );
			btnRegular.hover.data.color = nk_rgba( 61, 65, 72, 255 );
			btnRegular.normal.data.color = nk_rgba( 45, 50, 56, 255 );
			btnRegular.text_active = nk_rgba( 33, 150, 243, 255 );
			btnRegular.text_hover = nk_rgba( 255, 255, 255, 255 );
			btnRegular.text_normal = nk_rgba( 175, 180, 187, 255 );
			btnRegular.text_alignment = NK_TEXT_LEFT;

			btnDisabled.rounding = 3.f;
			btnDisabled.padding = nk_vec2( 1, 0 );
			btnDisabled.touch_padding = nk_vec2( 1, 0 );
			btnDisabled.active.data.color = clrDisabled;
			btnDisabled.hover.data.color = clrDisabled;
			btnDisabled.normal.data.color = clrDisabled;
			btnDisabled.text_active = nk_rgba( 116, 153, 183, 255 );
			btnDisabled.text_hover = nk_rgba( 116, 153, 183, 255 );
			btnDisabled.text_normal = nk_rgba( 116, 153, 183, 255 );
			btnDisabled.text_alignment = NK_TEXT_CENTERED;

			btnSpecialActive.rounding = 3.f;
			btnSpecialActive.padding = nk_vec2( 1, 0 );
			btnSpecialActive.touch_padding = nk_vec2( 1, 0 );
			btnSpecialActive.active.data.color = nk_rgba( 54, 70, 84, 255 );
			btnSpecialActive.hover.data.color = nk_rgba( 54, 70, 84, 255 );
			btnSpecialActive.normal.data.color = nk_rgba( 54, 70, 84, 255 );
			btnSpecialActive.text_active = nk_rgba( 33, 150, 243, 255 );
			btnSpecialActive.text_hover = nk_rgba( 33, 150, 243, 255 );
			btnSpecialActive.text_normal = nk_rgba( 33, 150, 243, 255 );
			btnSpecialActive.text_alignment = NK_TEXT_CENTERED;

			btnSpecial.rounding = 3.f;
			btnSpecial.padding = nk_vec2( 1, 0 );
			btnSpecial.touch_padding = nk_vec2( 1, 0 );
			btnSpecial.active.data.color = nk_rgba( 54, 70, 84, 255 );
			btnSpecial.hover.data.color = nk_rgba( 54, 70, 84, 255 );
			btnSpecial.normal.data.color = nk_rgba( 43, 60, 75, 255 );
			btnSpecial.text_active = nk_rgba( 33, 150, 243, 255 );
			btnSpecial.text_hover = nk_rgba( 33, 150, 243, 255 );
			btnSpecial.text_normal = nk_rgba( 33, 150, 243, 255 );
			btnSpecial.text_alignment = NK_TEXT_CENTERED;

			btnCombo.text_active = nk_rgba( 255, 255, 255, 255 );
			btnCombo.text_hover = nk_rgba( 255, 255, 255, 255 );
			btnCombo.text_normal = nk_rgba( 175, 180, 187, 255 );
			btnCombo.border = 0.f;
			btnCombo.active.data.color = nk_rgba( 56, 60, 66, 255 );
			btnCombo.hover.data.color = nk_rgba( 56, 60, 66, 255 );
			btnCombo.normal.data.color = nk_rgba( 45, 50, 56, 255 );
			btnCombo.text_alignment = NK_TEXT_LEFT;
			btnCombo.padding = nk_vec2( 5, 0 );
			btnCombo.touch_padding = nk_vec2( 5, 5 );

			btnComboActive.text_active = nk_rgba( 255, 255, 255, 255 );
			btnComboActive.text_hover = nk_rgba( 255, 255, 255, 255 );
			btnComboActive.text_normal = nk_rgba( 33, 150, 243, 255 );
			btnComboActive.border = 0.f;
			btnComboActive.active.data.color = nk_rgba( 56, 60, 66, 255 );
			btnComboActive.hover.data.color = nk_rgba( 56, 60, 66, 255 );
			btnComboActive.normal.data.color = nk_rgba( 56, 60, 66, 255 );
			btnComboActive.text_alignment = NK_TEXT_LEFT;
			btnComboActive.padding = nk_vec2( 5, 0 );
			btnComboActive.touch_padding = nk_vec2( 5, 5 );
		}

		bool PX_API CreateSpriteTextures( )
		{
			for each( auto& texTexture in vecTextures )
			{
				const auto wstrFile = GetPXDirectory( ) + PX_XOR( LR"(\Resources\)" ) + texTexture.wstrFileName;
				if ( D3D_OK != D3DXCreateTextureFromFileEx( pDevice, wstrFile.c_str( ),
															texTexture.uWidth, texTexture.uHeight, D3DX_FROM_FILE, D3DUSAGE_DYNAMIC, D3DFMT_FROM_FILE,
															D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, const_cast< D3DXIMAGE_INFO* >( &texTexture.iiImage ),
															nullptr, const_cast< IDirect3DTexture9** >( &texTexture.pTexture ) ) )
					return false;
			}
			return true;
		}

		void PX_API DestroySpriteTextures( )
		{
			texture_t* texTexture;
			for ( auto u = 0u; u < vecTextures.size( )
				  && nullptr != ( texTexture = &vecTextures[ u ] ); u++ )
				if ( texTexture->pTexture )
				{
					texTexture->pTexture->Release( );
					texTexture->pTexture = nullptr;
				}
		}

		bool PX_API InitializeUI( cstr_t _szApplicationTitle, unsigned uWidth /*= uWindowWidth*/, unsigned uHeight /*= uWindowHeight*/ )
		{
			szNuklearWindowTitle = new char[ strlen( _szApplicationTitle ) + 1 ];
			strcpy( szNuklearWindowTitle, _szApplicationTitle );
			uNuklearWindowWidth = uWidth;
			uNuklearWindowHeight = uHeight;
			InitializeNuklear( );

			vecTextures.emplace_back( 32, 29, PX_XOR( LR"(PX Logo.png)" ) ); // TEXTURE_LOGO
			vecTextures.emplace_back( 720, 394, PX_XOR( LR"(PX Loading.png)" ) ); // TEXTURE_LOGO_LOADING
			vecTextures.emplace_back( 100, 100, PX_XOR( LR"(Game Icons\CSGO Sized.png)" ) ); // TEXTURE_ICON_CSGO
			vecTextures.emplace_back( 100, 100, PX_XOR( LR"(Game Icons\PUBG Sized.png)" ) ); // TEXTURE_ICON_PUBG
			vecTextures.emplace_back( 100, 100, PX_XOR( LR"(Game Icons\RSIX Sized.png)" ) ); // TEXTURE_ICON_RSIX
			vecTextures.emplace_back( 50, 50, PX_XOR( LR"(Cursor\Arrow.png)" ) ); // TEXTURE_CURSOR_ARROW
			vecTextures.emplace_back( 50, 50, PX_XOR( LR"(Cursor\Hand.png)" ) ); // TEXTURE_CURSOR_HAND
			vecTextures.emplace_back( 50, 50, PX_XOR( LR"(Cursor\I Beam.png)" ) ); // TEXTURE_CURSOR_IBEAM

			return !vecTextures.empty( )
					&& D3DXCreateSprite( pDevice, &pBufferSprite ) == D3D_OK
					&& CreateSpriteTextures( );
		}

		void PX_API Destruct( )
		{
			OnReset( );
		}

		struct nk_vec2 PX_API CalculateTextBounds( cstr_t szText, unsigned uRowHeight /*= 30*/ )
		{
			static cstr_t szBuffer;
			static struct nk_vec2 vecBuffer;
			static int iBuffer;

			return nk_text_calculate_text_bounds( pContext->style.font, szText, strlen( szText ), float( uRowHeight ), &szBuffer, &vecBuffer, &iBuffer, 0 );
		}

		void PX_API SetFont( EFont fntDesiredFont )
		{
			//std::deque< nk_font* > dqFonts { pTahoma, pTahomaBold, pRoboto, pRobotoBold, pRobotoSmall, pRobotoBoldSmall, pEnvy };
			px_assert( fntDesiredFont >= 0 && fntDesiredFont < FNT_MAX );
			nk_style_set_font( pContext, &dqFonts[ fntDesiredFont ]->handle );
		}

		bool bDestroyedTextures = false;

		void PX_API OnReset( )
		{
			if ( !bDestroyedTextures )
			{
				nk_d3d9_shutdown( );
				pBufferSprite->OnLostDevice( );
				DestroySpriteTextures( );
				bDestroyedTextures = true;
			}
		}

		void PX_API OnSuccessfulReset( int iWidth, int iHeight )
		{
			if ( bDestroyedTextures )
			{
				uWindowWidth = iWidth;
				uWindowHeight = iHeight;
				InitializeNuklear( );
				pBufferSprite->OnResetDevice( );
				CreateSpriteTextures( );
				bDestroyedTextures = false;
			}
		}

		bool PX_API HandleEvent( HWND h, UINT msg, WPARAM w, LPARAM l )
		{
			return nk_d3d9_handle_event( h, msg, w, l );
		}

		bool PX_API HandleWindowInput( )
		{
			auto bShouldDrawInterface = true;
			if ( bCreatedWindow )
			{
				static auto bDrag = false;
				RECT recWindowPos { };
				GetWindowRect( hwWindowHandle, &recWindowPos );
				static POINT pntOldCursorPosRelative { };

				if ( bMinimized )
					bDrag = false;
				else if ( PX_INPUT.GetKeyState( VK_LBUTTON ) )
				{
					POINT pntCursorPos { };
					GetCursorPos( &pntCursorPos );
					POINT pntCursorPosRelative { pntCursorPos.x - recWindowPos.left, pntCursorPos.y - recWindowPos.top };

					if ( pntCursorPosRelative.x > 0 && pntCursorPosRelative.x <= signed( uWindowWidth ) && pntCursorPosRelative.y > 0 && pntCursorPosRelative.y <= 30 || bDrag )
					{
						bDrag = true;
						if ( !pntOldCursorPosRelative.x || !pntOldCursorPosRelative.y ) pntOldCursorPosRelative = pntCursorPosRelative;

						SetWindowPos( hwWindowHandle, nullptr, recWindowPos.left - pntOldCursorPosRelative.x + pntCursorPosRelative.x,
							recWindowPos.top - pntOldCursorPosRelative.y + pntCursorPosRelative.y, uWindowWidth, uWindowHeight, 0 );
						UpdateWindow( hwWindowHandle );
					}
				}
				else
				{
					pntOldCursorPosRelative = { 0, 0 };
					bDrag = false;
				}
				constexpr struct nk_vec2 vecDefaultLocation
				{
					0, 0
				};
				nk_window_set_position( pContext, szNuklearWindowTitle, vecDefaultLocation );
			}

			MSG msgBuffer;
			nk_input_begin( pContext );
			while ( PeekMessage( &msgBuffer, hwWindowHandle, 0, 0, PM_REMOVE ) )
			{
				if ( msgBuffer.message == WM_QUIT )
					bShouldDrawInterface = false;
				TranslateMessage( &msgBuffer );
				DispatchMessage( &msgBuffer );
			}
			nk_input_end( pContext );
			return bShouldDrawInterface;
		}

		void PX_API DrawTextures( )
		{
			if ( pBufferSprite->Begin( D3DXSPRITE_ALPHABLEND ) == D3D_OK )
			{
				for each( const auto& texture in vecImageQueue )
					if ( vecTextures[ texture.iTexture ].pTexture )
						pBufferSprite->Draw( vecTextures[ texture.iTexture ].pTexture, nullptr, nullptr, &texture.vecLocation, texture.clrColor );
				pBufferSprite->End( );
			}
			vecImageQueue.clear( );
		}

		void PX_API HandleWindowMovement( struct nk_rect &recInterfaceWindow, int iWindow )
		{
			if ( !nk_window_has_focus( pContext ) )
				return;

			static bool bClicking[ 2 ] { false, false };
			POINT pntMousePosition;
			static POINT pntOriginalMousePosition;
			static auto vecWindowDifference = nk_vec2( 0, 0 );
			static auto rcOriginalWindowPosition = recInterfaceWindow;

			RECT recWindow;
			GetWindowRect( hwWindowHandle, &recWindow );
			GetCursorPos( &pntMousePosition );
			pntMousePosition.x -= recWindow.left;
			pntMousePosition.y -= recWindow.top;

			if ( ( nk_input_is_mouse_hovering_rect( &pContext->input, nk_rect( recInterfaceWindow.x, recInterfaceWindow.y, recInterfaceWindow.w, 30 ) )
				   && PX_INPUT.GetKeyState( VK_LBUTTON ) == true ) || bClicking[ iWindow ] )
			{
				if ( PX_INPUT.GetKeyState( VK_LBUTTON ) == false )
				{
					bClicking[ iWindow ] = false;
					return;
				}
				if ( !bClicking[ iWindow ] )
				{
					vecWindowDifference = nk_vec2( pntMousePosition.x - recInterfaceWindow.x, pntMousePosition.y - recInterfaceWindow.y );
					pntOriginalMousePosition = pntMousePosition;
					rcOriginalWindowPosition = recInterfaceWindow;
					bClicking[ iWindow ] = true;
				}
				recInterfaceWindow.x = rcOriginalWindowPosition.x + pntMousePosition.x - pntOriginalMousePosition.x;
				recInterfaceWindow.y = rcOriginalWindowPosition.y + pntMousePosition.y - pntOriginalMousePosition.y;

				const auto uCurrentWindowWidth = recWindow.right - recWindow.left;
				const auto uCurrentWindowHeight = recWindow.bottom - recWindow.top;
				const auto recBounds = pContext->current->bounds;

				if ( recInterfaceWindow.x + recBounds.w > uCurrentWindowWidth )
					recInterfaceWindow.x = uCurrentWindowWidth - recBounds.w;
				else if ( recInterfaceWindow.x < 0 )
					recInterfaceWindow.x = 0;
				if ( recInterfaceWindow.y < 0 )
					recInterfaceWindow.y = 0;
				else if ( recInterfaceWindow.y + recBounds.h > uCurrentWindowHeight )
					recInterfaceWindow.y = uCurrentWindowHeight - recBounds.h;
			}
			else
				bClicking[ iWindow ] = false;
		}

		void PX_API ApplyCursor( )
		{
			POINT pntCursor;

			GetCursorPos( &pntCursor );
			ScreenToClient( hwWindowHandle, &pntCursor );

			auto uTextureID = curCurrent == CURSOR_ARROW ? TEXTURE_CURSOR_ARROW : curCurrent == CURSOR_HAND ? TEXTURE_CURSOR_HAND : TEXTURE_CURSOR_IBEAM;
			vecImageQueue.emplace_back( uTextureID, D3DXVECTOR3( float( pntCursor.x + vecTextures[ uTextureID ].uWidth / 2.f - 50 ), float( pntCursor.y + vecTextures[ uTextureID ].uHeight / 2.f - 50 ), 0.f ) );

			while ( ShowCursor( FALSE ) >= 0 );
			if ( bCreatedWindow )
				SetCursor( nullptr );

			curCurrent = CURSOR_ARROW;
			bFoundHoverTarget = false;
			pContext->last_widget_state &= ~( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER );
		}

		bool PX_API Render( )
		{
			auto bShouldDrawUserInterface = true;
			bDrawComboboxArrow = false;
			SetFont( FNT_ROBOTO );

			if ( bCreatedWindow )
				recWindow.x = recWindow.y = 0.f;

			if ( nk_begin( pContext, szNuklearWindowTitle, recWindow, NK_WINDOW_NO_SCROLLBAR ) )
			{
				if ( !bCreatedWindow )
					HandleWindowMovement( recWindow, 0 );

				nk_layout_row_dynamic( pContext, 10, 0 );
				SetFont( FNT_ROBOTO );
				SetLayout( );

				if ( bDrawComboboxArrow )
				{
					const auto pDrawBuffer = nk_window_get_canvas( pContext );
					nk_stroke_line( pDrawBuffer, recComboboxWindowBounds.x, recComboboxWindowBounds.y - 2, recComboboxWindowBounds.x + recComboboxWindowBounds.w, recComboboxWindowBounds.y - 2, 2, clrBorder );
					recComboboxWindowBounds.y -= 3;
					nk_fill_triangle( pDrawBuffer, recComboboxWindowBounds.x + recComboboxWindowBounds.w - 3, recComboboxWindowBounds.y, recComboboxWindowBounds.x + recComboboxWindowBounds.w - 10, recComboboxWindowBounds.y - 7, recComboboxWindowBounds.x + recComboboxWindowBounds.w - 17, recComboboxWindowBounds.y, clrBackground );
					recComboboxWindowBounds.y += 3;
				}

				if ( pActiveEditColor != nullptr )
					ColorPicker( );
				else if( pActiveEditToggle != nullptr )
					nk_fill_rect( nk_window_get_canvas( pContext ), nk_rect( pContext->current->bounds.x, pContext->current->bounds.y, pContext->current->bounds.w, pContext->current->bounds.h ), 0, nk_rgba( 0, 0, 0, 180 ) );
			}
			else
				bShouldDrawUserInterface = false;
			nk_end( pContext );

			if ( pActiveEditToggle != nullptr )
				ToggleEditor( recWindow );

			if ( bCreatedWindow )
			{
				HandleWindowInput( );
				pDevice->Clear( NULL, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, NULL, NULL, NULL );
				pDevice->BeginScene( );
			}
			else
				nk_window_set_bounds( pContext, szNuklearWindowTitle, recWindow );

			IDirect3DStateBlock9* pState;
			pDevice->CreateStateBlock( bCreatedWindow ? D3DSBT_ALL : D3DSBT_PIXELSTATE, &pState );
			nk_d3d9_render( NK_ANTI_ALIASING_ON );
			pState->Apply( );
			pState->Release( );
			ApplyCursor( );
			DrawTextures( );

			if ( bCreatedWindow )
			{
				pDevice->EndScene( );
				pDevice->Present( nullptr, nullptr, nullptr, nullptr );
			}
			uTooltipCounter = uSliderIntCounter = uSliderFloatCounter = 0u;
			if ( !bCreatedWindow && !PopupActive( ) && PX_INPUT.GetKeyState( VK_LBUTTON ) == true )
				nk_d3d9_handle_event( hwWindowHandle, WM_LBUTTONUP, 0, int( pContext->input.mouse.pos.x ) | int( pContext->input.mouse.pos.y ) << 16 );
			return bShouldDrawUserInterface;
		}

		std::array< unsigned, 2 > PX_API GetCurrentWindowDimensions( )
		{
			std::array< unsigned, 2 > uBuffer { unsigned( pContext->current->bounds.w ), unsigned( pContext->current->bounds.h ) };
			return uBuffer;
		}

		void PX_API Example( )
		{
			static const std::deque< cstr_t > dqPrimaryTabs
			{
				"Tab One",
				"Super Wide Tab That Is Dynamically Sized Depending On Text",
				"Tab three!!!" ICON_FA_KEY,
				"Tab Four"
			};

			static const std::deque< cstr_t > dqSubTabs
			{
				"Subtab One",
				"Subtab Two",
				"Subtab Three",
				"Subtab Four"
			};

			static const auto fnSetTabValue = [ ]( int& iCurrentValue, const int iNewValue )
			{
				iCurrentValue = iNewValue >= 0 ? iNewValue : iCurrentValue;
			};

			// Create a JSON object to hold our variables for widgets to use.
			static nlohmann::json jsWidgets
			{
				{ PX_XOR( "PrimaryTab" ), 0 },
				{ PX_XOR( "SubTab" ), 0 },
				{ PX_XOR( "First" ), false },
				{ PX_XOR( "Second" ), false },
				{ PX_XOR( "Third" ), false },
				{ PX_XOR( "Int" ), 0 },
				{ PX_XOR( "Float" ), 0.f }
			};

			// Color pickers
			static color_sequence_t clrFirst( { 255, 0, 0 }, 1000 );
			static color_sequence_t clrSecond( { 0, 255, 0 }, 1000 );
			static color_sequence_t clrThird( { 0, 0, 255 }, 1000 );

			// Create a header with the window title and subtitle, with minimize and close functionality.
			Header( PX_XOR( "Paladin Extensions" ), szNuklearWindowTitle );

			// Create primary tabs.
			fnSetTabValue( jsWidgets[ PX_XOR( "PrimaryTab" ) ].get_ref< int& >( ), Tabs( 10, 0, dqPrimaryTabs, jsWidgets[ PX_XOR( "PrimaryTab" ) ] ) );

			// Separate the primary tabs from the rest of the application.
			Separator( 61, 65, 72, 100 );
			// Set the font for Nuklear to render in.
			SetFont( FNT_ROBOTO_SMALL );

			// Create subtabs.
			fnSetTabValue( jsWidgets[ PX_XOR( "SubTab" ) ].get_ref< int& >( ), SubTabs( 10, 60, 150, 30, dqSubTabs, jsWidgets[ PX_XOR( "SubTab" ) ] ) );

			// Begin a groupbox for all of our widgets to be inside of.
			if ( BeginGroupbox( 200, 150, 500, 420, dqSubTabs.at( jsWidgets[ PX_XOR( "SubTab" ) ] ) ) )
			{
				const static auto iCheckboxTextWidth = CalculateTextBounds( PX_XOR( "Checkbox" ), 30 ).x;
				static char szIntBuffer[ 64 ] { }, szFloatBuffer[ 64 ] { }, buf[ 64 ] { };

				VerticalSpacing( );

				nk_layout_row_dynamic( pContext, 30, 1 );
				static auto iVal = float( );
				iVal = InputboxFloat( 10, buf );

				BeginRow( 15, 12, ROW_STATIC );
				SetRowWidth( 5 );
				Spacing( );
				SetRowWidth( CHECKBOX_ICON_WIDTH + CalculateTextBounds( PX_XOR( "Checkbox" ), 30 ).x );
				Checkbox( PX_XOR( "Checkbox" ), jsWidgets[ PX_XOR( "First" ) ].get_ptr< bool* >( ) );
				SetRowWidth( GROUPBOX_COLUMN_WIDTH - iCheckboxTextWidth - CHECKBOX_ICON_WIDTH - COLOR_BUTTON_WIDTH - COLOR_BUTTON_PADDING * 2 );
				Spacing( );
				SetRowWidth( COLOR_BUTTON_WIDTH );
				ColorButton( "Color 1", &clrFirst );
				SetRowWidth( CHECKBOX_ICON_WIDTH + CalculateTextBounds( PX_XOR( "Checkbox" ), 30 ).x );
				Checkbox( PX_XOR( "Checkbox" ), jsWidgets[ PX_XOR( "Second" ) ].get_ptr< bool* >( ) );
				SetRowWidth( GROUPBOX_COLUMN_WIDTH - iCheckboxTextWidth - CHECKBOX_ICON_WIDTH - COLOR_BUTTON_WIDTH * 2 - COLOR_BUTTON_PADDING * 4 );
				Spacing( );
				SetRowWidth( COLOR_BUTTON_WIDTH );
				ColorButton( "Color 2", &clrSecond );
				ColorButton( "Color 3", &clrThird );
				Checkbox( PX_XOR( "Checkbox" ), jsWidgets[ PX_XOR( "Third" ) ].get_ptr< bool* >( ) );
				EndRow( );

				VerticalSpacing( );

				BeginRow( 30, 6, ROW_CUSTOM );
				jsWidgets[ PX_XOR( "Int" ) ] = Slider( PX_XOR( "Int Slider" ), szIntBuffer, -50, 50, jsWidgets[ PX_XOR( "Int" ) ], 15, 0, GROUPBOX_COLUMN_WIDTH, 30 );
				jsWidgets[ PX_XOR( "Float" ) ] = Slider( PX_XOR( "Float Slider" ), szFloatBuffer, -50.f, 50.f, jsWidgets[ PX_XOR( "Float" ) ], GROUPBOX_COLUMN_WIDTH + 25, 0, GROUPBOX_COLUMN_WIDTH, 30, 1 );
				EndRow( );
				EndGroupbox( );
			}
		}

		bool PX_API MouseHoveringRectangle( unsigned x, unsigned y, unsigned width, unsigned height )
		{
			return nk_input_is_mouse_hovering_rect( &pContext->input, nk_rect( float( x ), float( y ), float( width ), float( height ) ) );
		}

		void SetWidgetPosition( unsigned x, unsigned y )
		{
			pContext->current->layout->at_x = float( x );
			pContext->current->layout->at_y = float( y );
		}
	}

	namespace Widgets
	{
		ERowType rowLastRowType;

		struct nk_rect recLastWidgetLocation;
		cstr_t szColorPickerSubject;

		bool PX_API HoveringNextWidget( )
		{
			return nk_input_is_mouse_prev_hovering_rect( &pContext->input, nk_widget_bounds( pContext ) );
		}

		nk_flags PX_API EditTextBox( nk_context* ctx, nk_flags flags, char* buffer, int max, nk_plugin_filter filter )
		{
			return nk_edit_string_zero_terminated( ctx, flags, buffer, max, filter );
		}

		struct nk_rect PX_API NextWidgetBounds( )
		{
			return nk_widget_bounds( pContext );
		}

		bool PX_API HoverCheck( ECursor curSetCursor )
		{
			if ( pContext->last_widget_state & NK_WIDGET_STATE_ACTIVE || pContext->last_widget_state & NK_WIDGET_STATE_HOVER )
			{
				bFoundHoverTarget = true;
				curCurrent = curSetCursor;
				return true;
			}
			return false;
		}

		void PX_API SetWidgetActive( ECursor curSetCursor )
		{
			pContext->last_widget_state |= NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER;
			bFoundHoverTarget = true;
			curCurrent = curSetCursor;
		}

		void PX_API Tooltip( bool bShowTooltip, cstr_t szTooltip )
		{
			constexpr auto mmtWaitTime = 1000000ull; // micro seconds
			constexpr auto uLineHeight = 22u;
			constexpr auto uRowHeight = 15u;

			const auto uThisTooltipID = uTooltipCounter;
			uTooltipCounter++;

			if ( mmtStart.size( ) <= uThisTooltipID )
				mmtStart.emplace_back( GetMoment( ) );

			if ( !bShowTooltip )
			{
				mmtStart[ uThisTooltipID ] = 0ull;
				return;
			}

			if ( mmtStart[ uThisTooltipID ] == 0ull )
				mmtStart[ uThisTooltipID ] = GetMoment( );

			if ( GetMoment( ) - mmtStart[ uThisTooltipID ] <= mmtWaitTime || PopupActive( ) )
				return;

			constexpr auto uMaxTooltipWidth = 210u;
			constexpr auto uTooltipPadding = 14u;
			constexpr struct nk_text txtTooltip { { 5, 2 }, { 0, 0, 0, 0 }, { 255, 255, 255 ,255 } };
			SetFont( FNT_TAHOMA );

			const auto vecMousePos = pContext->input.mouse.pos;
			const auto flUsableSpaceX = pContext->current->bounds.w - vecMousePos.x;

			struct text_t
			{
				struct nk_vec2 vecSize;
				str_t strText;
				// review why even have a constructor here? just use initializer braces
				text_t( struct nk_vec2 vecSize, str_t strText ): vecSize( vecSize ), strText( strText )
				{ }
			};

			std::deque< text_t > wrdWords;
			std::deque< text_t > dqLines;
			str_t strWord;
			const auto sTextLength = strlen( szTooltip );

			for ( auto z = 0u; z <= sTextLength; z++ )
			{
				if ( szTooltip[ z ] != ' ' && z != sTextLength )
				{
					strWord += szTooltip[ z ];
					continue;
				}
				wrdWords.emplace_back( CalculateTextBounds( strWord.c_str( ), uRowHeight ), strWord );
				strWord.clear( );
			}

			for ( auto z = 0u; z < wrdWords.size( ); z++ )
			{
				static unsigned uUsedSpace = 0u;
				static auto bNewLine = true;
				static str_t strLine;
				auto wrdCurrent = wrdWords[ z ];

				auto fnAddLine = [ & ]( )
				{
					dqLines.emplace_back( nk_vec2( float( uUsedSpace ), float( uRowHeight ) ), strLine );
					strLine.clear( );
					uUsedSpace = unsigned( wrdCurrent.vecSize.x );
					bNewLine = true;
				};

				if ( z == wrdWords.size( ) - 1 )
				{
					if ( uUsedSpace + wrdCurrent.vecSize.x > uMaxTooltipWidth - uTooltipPadding )
						fnAddLine( );
					else
						strLine += ' ';

					strLine += wrdCurrent.strText;
					fnAddLine( );
					break;
				}

				if ( uUsedSpace + wrdCurrent.vecSize.x > uMaxTooltipWidth - uTooltipPadding )
					fnAddLine( );

				if ( !bNewLine )
					strLine += ' ';

				strLine += wrdCurrent.strText;
				uUsedSpace = unsigned( CalculateTextBounds( strLine.c_str( ), 15 ).x );
				bNewLine = false;
			}

			struct nk_rect recTooltip {	vecMousePos.x - pContext->current->layout->clip.x + 20.f, vecMousePos.y - pContext->current->layout->clip.y + 20.f, float( uMaxTooltipWidth ), dqLines.size( ) * uLineHeight + 13.f };
			const auto& recWindowBounds = pContext->current->bounds;
			const struct nk_rect recRealTooltip { recTooltip.x + pContext->current->layout->clip.x, recTooltip.y + pContext->current->layout->clip.y, recTooltip.w, recTooltip.h };
			
			if ( recRealTooltip.y + recRealTooltip.h > recWindowBounds.y + recWindowBounds.h )
				recTooltip.y = recWindowBounds.y + recWindowBounds.h - recTooltip.h - pContext->current->layout->clip.y;
			if ( recRealTooltip.x + recRealTooltip.w > recWindowBounds.x + recWindowBounds.w )
				recTooltip.x = recWindowBounds.x + recWindowBounds.w - recTooltip.w - pContext->current->layout->clip.x;

			auto clrOld = pContext->style.window.background;
			auto flOldRounding = pContext->style.window.rounding;
			pContext->style.window.background.a = 200;
			pContext->style.window.rounding = 3.f;
			if ( nk_popup_begin( pContext, NK_POPUP_DYNAMIC, "__##Tooltip##__", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_BORDER, recTooltip ) )
			{
				pContext->current->layout->flags &= ~nk_flags( NK_WINDOW_ROM );
				pContext->current->popup.type = NK_PANEL_TOOLTIP;
				pContext->current->layout->type = NK_PANEL_TOOLTIP;

				for each ( auto& dqLine in dqLines )
				{
					nk_layout_row_dynamic( pContext, uRowHeight, 1 );
					nk_label( pContext, dqLine.strText.c_str( ), NK_TEXT_LEFT );
				}
				nk_tooltip_end( pContext );
			}

			pContext->style.window.background = clrOld;
			pContext->style.window.rounding = flOldRounding;
		}

		void PX_API Header( cstr_t szTitle, cstr_t _szApplicationTitle, unsigned uFillHeight /*= 102u*/, callback_t fnMinimizeCallback /*= nullptr*/, callback_t fnCloseCallback /*= nullptr*/ )
		{
			auto recMainWindow = pContext->current->bounds;
			vecImageQueue.emplace_back( TEXTURE_LOGO, D3DXVECTOR3( recMainWindow.x + 5.f, recMainWindow.y + 5.f, 0.f ), PopupActive( ) ? D3DCOLOR_ARGB( 170, 170, 170, 170 ) : 0xFFFFFFFF );

			nk_layout_row_dynamic( pContext, 30, 0 );
			auto pOutput = nk_window_get_canvas( pContext );
			constexpr nk_color _clrBlueHover { 115, 189, 247, 255 };
			const auto flWidth = recMainWindow.w;

			struct nk_text txtTitle, txtApplication, txtCloseButton, txtMinimizeButton;
			txtCloseButton.padding = txtApplication.padding = txtTitle.padding = pContext->style.text.padding;
			txtTitle.text = clrTextActive;
			txtApplication.text = clrTextDormant;

			nk_fill_rect( pOutput, nk_rect( recMainWindow.x, recMainWindow.y, flWidth, float( uFillHeight ) ), 0.f, clrHeader );
			nk_stroke_line( pOutput, recMainWindow.x, recMainWindow.y + 40, recMainWindow.x + flWidth, recMainWindow.y + 40, 1, clrColorTable[ NK_COLOR_BORDER ] );

			SetFont( FNT_ROBOTO_BOLD );
			auto vecTitle = CalculateTextBounds( szTitle, 30 );
			nk_widget_text( pOutput, nk_rect( recMainWindow.x + 10.f + vecTextures[ TEXTURE_LOGO ].uWidth, recMainWindow.y + 7, vecTitle.x, 30 ), szTitle, strlen( szTitle ), &txtTitle, NK_TEXT_CENTERED, pContext->style.font );
			SetFont( FNT_ROBOTO );
			auto vecApplicationTitle = CalculateTextBounds( _szApplicationTitle, 30 );
			nk_widget_text( pOutput, nk_rect( recMainWindow.x + 13.f + vecTextures[ TEXTURE_LOGO ].uWidth + vecTitle.x, recMainWindow.y + 7, vecApplicationTitle.x, 30 ), _szApplicationTitle, strlen( _szApplicationTitle ), &txtApplication, NK_TEXT_CENTERED, pContext->style.font );

			static auto clrMinimize = clrBlue, clrClose = clrMinimize;
			txtMinimizeButton.text = clrMinimize;
			txtCloseButton.text = clrClose;
			txtMinimizeButton.padding = txtCloseButton.padding = nk_vec2( 0, 0 );
			struct nk_rect recMinimize = { recMainWindow.x + flWidth - 65, recMainWindow.y + 19, 20, 8 };
			struct nk_rect recCloseButton = { recMainWindow.x + flWidth - 33, recMainWindow.y + 13, 20, 20 };
			nk_widget_text( pOutput, recMinimize, ICON_FA_MINUS, strlen( ICON_FA_MINUS ), &txtMinimizeButton, NK_TEXT_CENTERED, pContext->style.font );
			nk_widget_text( pOutput, recCloseButton, ICON_FA_TIMES, strlen( ICON_FA_TIMES ), &txtCloseButton, NK_TEXT_CENTERED, pContext->style.font );

			const bool bHoveringMinimize = nk_input_is_mouse_hovering_rect( &pContext->input, nk_rect( recMinimize.x + 8, recMinimize.y, recMinimize.w + 2, recMinimize.h ) ),
				bHoveringClose = nk_input_is_mouse_hovering_rect( &pContext->input, recCloseButton ),
				bClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == true;

			if ( GetActiveWindow( ) != hwWindowHandle || bMinimized )
				return;

			if ( bHoveringMinimize )
			{
				clrMinimize = _clrBlueHover;
				SetWidgetActive( CURSOR_HAND );
				if ( bClicking )
				{
					if ( bCreatedWindow )
					{
						pContext->input.mouse.pos.x = pContext->input.mouse.pos.y = 0;
						bMinimized = true;
						ShowWindow( hwWindowHandle, SW_MINIMIZE );
					}
					if ( fnMinimizeCallback )
						fnMinimizeCallback( );
				}
			}
			else
				clrMinimize = clrBlue;

			if ( bHoveringClose )
			{
				clrClose = _clrBlueHover;
				SetWidgetActive( CURSOR_HAND );
				if ( bClicking && fnCloseCallback )
					fnCloseCallback( );
			}
			else
				clrClose = clrBlue;
		}

		bool PX_API PrimaryTab( cstr_t szText, bool bActive )
		{
			iCurrentRowUsedColumns++;

			return nk_button_label_styled( pContext, bActive ? &btnTopActive : &btnTop, szText );
		}

		bool PX_API SecondaryTab( cstr_t szText, bool bActive )
		{
			iCurrentRowUsedColumns++;

			if ( bActive )
			{
				auto recBoundaries = nk_widget_bounds( pContext );
				auto pOutput = nk_window_get_canvas( pContext );

				nk_fill_rect( pOutput, recBoundaries, 0.f, clrBackground );

				recBoundaries.w += recBoundaries.x;
				recBoundaries.h += recBoundaries.y;
				SetFont( FNT_TAHOMA_BOLD );
				const auto bResult = nk_button_label_styled( pContext, &btnRegularActive, szText );
				HoverCheck( CURSOR_HAND );
				SetFont( FNT_TAHOMA );
				nk_stroke_line( pOutput, recBoundaries.x, recBoundaries.y, recBoundaries.x, recBoundaries.h, 2, clrBlue );
				return bResult;
			}
			SetFont( FNT_TAHOMA );
			const auto bReturn = nk_button_label_styled( pContext, &btnRegular, szText );
			HoverCheck( CURSOR_HAND );
			return bReturn;
		}

		void PX_API Separator( int iRed, int iGreen, int iBlue, unsigned uStartHeight, const links_t* pLinkList /*= nullptr*/, bool bUpperBorder /*= false*/, float flHeight /*= 42.f*/ )
		{
			constexpr struct nk_color clrBorderColor = { 85, 88, 94, 255 };
			const auto pDrawBuffer = nk_window_get_canvas( pContext );
			nk_fill_rect( pDrawBuffer, nk_rect( pContext->current->bounds.x, pContext->current->bounds.y + float( uStartHeight ), pContext->current->bounds.w, flHeight ), 0.f, nk_rgba( iRed, iGreen, iBlue, 255 ) );
			nk_stroke_line( pDrawBuffer, pContext->current->bounds.x, pContext->current->bounds.y + float( uStartHeight + flHeight - 1 ), pContext->current->bounds.x + float( pContext->current->bounds.w ), pContext->current->bounds.y + float( uStartHeight + flHeight - 1 ), 0.5f, clrBorderColor );

			if ( bUpperBorder )
				nk_stroke_line( pDrawBuffer, pContext->current->bounds.x, pContext->current->bounds.y + float( uStartHeight + 1 ), pContext->current->bounds.x + float( pContext->current->bounds.w ), pContext->current->bounds.y + float( uStartHeight + 1 ), 0.5f, clrBorderColor );

			if ( pLinkList == nullptr )
				return;

			const static auto uLinkTextHeight = 15u;
			const static auto uLinkTextSpacing = 10u;
			static auto bWasClicking = false; // stop it from opening 10 million pages
			bool bClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == true;
			auto uPosition = uLinkTextSpacing + uLinkTextHeight / 2u;
			const auto uYPosition = uLinkTextHeight / 2u;

			SetFont( FNT_ROBOTO_SMALL );
			BeginRow( 15, pLinkList->size( ), ROW_CUSTOM );
			for each ( const auto& link in *pLinkList )
			{
				auto vecTextSize = CalculateTextBounds( link.szTitle, uLinkTextHeight );
				PushCustomRow( uPosition, uYPosition, unsigned( vecTextSize.x ), uLinkTextHeight );
				auto recTextBounds = nk_widget_bounds( pContext );

				auto clrText = clrTextDormant;

				if ( nk_input_is_mouse_hovering_rect( &pContext->input, recTextBounds ) )
				{
					if ( bClicking && !bWasClicking )
						OpenLink( link.szLink );
					clrText = clrTextActive;
					SetWidgetActive( CURSOR_HAND );
				}

				Text( link.szTitle, { clrText.r, clrText.g, clrText.b, clrText.a } );
				uPosition += unsigned( vecTextSize.x ) + uLinkTextSpacing;
			}
			EndRow( );
			bWasClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == true;
		}

		bool PX_API Button( EPosition pPosition, const char* szText, bool bActive, bool bDisabled, cstr_t szTooltip /*= nullptr*/ )
		{
			iCurrentRowUsedColumns++;

			SetFont( FNT_ROBOTO_BOLD_SMALL );
			const auto recBoundaries = nk_widget_bounds( pContext );
			const auto pOutput = nk_window_get_canvas( pContext );
			auto bHover = false;
			nk_flags fOldFlags = 0;
			if ( !bFoundHoverTarget )
			{
				fOldFlags = pContext->last_widget_state;
				pContext->last_widget_state = 0;
			}
			const auto bReturn = nk_button_label_styled( pContext, bDisabled ? &btnDisabled : bActive ? &btnSpecialActive : &btnSpecial, szText );

			if ( !bFoundHoverTarget && !bDisabled )
			{
				bHover = HoverCheck( CURSOR_HAND );
				pContext->last_widget_state = fOldFlags;
				HoverCheck( CURSOR_HAND );
			}
			nk_color clrCurrentColor { };

			if ( szTooltip )
				Tooltip( bHover, szTooltip );

			if ( bDisabled )
				clrCurrentColor = clrDisabled;
			else
			{
				if ( bHover )
				{
					if ( !bActive )
						clrCurrentColor = clrBlueHover;
				}
				else
					clrCurrentColor = clrBlueDormant;
				if ( bActive )
					clrCurrentColor = clrBlueActive;
			}

			switch ( pPosition )
			{
				case EPosition::LEFT:
				{
					nk_fill_rect( pOutput, nk_rect( recBoundaries.x + recBoundaries.w - 5, recBoundaries.y, 5, recBoundaries.h ), 0.f, clrCurrentColor );
					break;
				}
				case EPosition::CENTER:
				{
					nk_fill_rect( pOutput, nk_rect( recBoundaries.x + recBoundaries.w - 5, recBoundaries.y, 5, recBoundaries.h ), 0.f, clrCurrentColor );
					nk_fill_rect( pOutput, nk_rect( recBoundaries.x, recBoundaries.y, 5, recBoundaries.h ), 0.f, clrCurrentColor );
					break;
				}
				case EPosition::RIGHT:
				{
					nk_fill_rect( pOutput, nk_rect( recBoundaries.x, recBoundaries.y, 5, recBoundaries.h ), 0.f, clrCurrentColor );
					break;
				}
				case EPosition::NONE:
				{
					
				}
				break;

				default:
					return false;
			}
			return bDisabled ? false : bReturn;
		}

		void PX_API Checkbox( cstr_t szText, bool *bActive, cstr_t szTooltip /*= nullptr*/ )
		{
			iCurrentRowUsedColumns += 2;

			static auto bWasClicking = false;

			nk_layout_row_push( pContext, CHECKBOX_ICON_WIDTH );
			const auto recBoundaries = nk_widget_bounds( pContext );
			const auto bHovering = nk_input_is_mouse_hovering_rect( &pContext->input, recBoundaries );
			const auto bClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == true;

			if ( bHovering && !PopupActive( ) )
				SetWidgetActive( CURSOR_HAND );

			if ( bClicking && bHovering && !PopupActive( ) )
			{
				if ( !bWasClicking && !PopupActive( ) )
					*bActive = !*bActive;
				bWasClicking = true;
			}
			else if ( !bClicking )
				bWasClicking = false;

			if ( szTooltip )
				Tooltip( bHovering, szTooltip );

			SetFont( FNT_TAHOMA );
			nk_label_colored( pContext, *bActive ? ICON_FA_CHECK_SQUARE : ICON_FA_SQUARE, NK_TEXT_CENTERED, *bActive ? clrBlue : bHovering && !PopupActive( ) ? ( bClicking ? clrBlue : clrBlue ) : clrTextDormant );
			nk_layout_row_push( pContext, CalculateTextBounds( szText, 15 ).x );
			nk_label_colored( pContext, ( szText + str_t( PX_XOR( "  " ) ) ).c_str( ), NK_TEXT_LEFT, clrTextDormant );
		}

		void PX_API PopupCheckbox( cstr_t szText, bool *bActive )
		{
			iCurrentRowUsedColumns += 2;

			static auto bWasClicking = false;

			nk_layout_row_push( pContext, CHECKBOX_ICON_WIDTH );
			const auto recBoundaries = nk_widget_bounds( pContext );
			const auto bHovering = nk_input_is_mouse_hovering_rect( &pContext->input, recBoundaries );
			const auto bClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == true;

			if ( bHovering )
				SetWidgetActive( CURSOR_HAND );

			if ( bClicking && bHovering )
			{
				if ( !bWasClicking )
					*bActive = !*bActive;
				bWasClicking = true;
			}
			else if ( !bClicking )
				bWasClicking = false;

			SetFont( FNT_TAHOMA );
			nk_label_colored( pContext, *bActive ? ICON_FA_CHECK_SQUARE : ICON_FA_SQUARE, NK_TEXT_CENTERED, *bActive ? clrBlue : bHovering ? ( bClicking ? clrBlue : clrBlue ) : clrTextDormant );
			nk_layout_row_push( pContext, CalculateTextBounds( szText, 15 ).x );
			nk_label_colored( pContext, ( szText + str_t( PX_XOR( "  " ) ) ).c_str( ), NK_TEXT_LEFT, clrTextDormant );
		}

		void PX_API Checkbox( cstr_t szText, toggle_t *bActive, cstr_t szTooltip /*= nullptr*/ )
		{
			iCurrentRowUsedColumns += 2;

			static auto bWasClicking = false;

			nk_layout_row_push( pContext, CHECKBOX_ICON_WIDTH );
			const auto recBoundaries = nk_widget_bounds( pContext );
			const auto bHovering = nk_input_is_mouse_hovering_rect( &pContext->input, recBoundaries );
			const auto bClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == true;

			if ( bHovering && !PopupActive( ) )
			{
				SetWidgetActive( CURSOR_HAND );
				if ( PX_INPUT.GetKeyState( VK_RBUTTON ) )
					pActiveEditToggle = bActive;
			}

			if ( bClicking && bHovering && !PopupActive( ) )
			{
				if ( !bWasClicking && !PopupActive( ) )
					*bActive = !*bActive;
				bWasClicking = true;
			}
			else if ( !bClicking )
				bWasClicking = false;

			if ( szTooltip )
				Tooltip( bHovering, szTooltip );

			SetFont( FNT_TAHOMA );
			nk_label_colored( pContext, !!*bActive ? ICON_FA_CHECK_SQUARE : ICON_FA_SQUARE, NK_TEXT_CENTERED, !!*bActive ? clrBlue : bHovering && !PopupActive( ) ? ( bClicking ? clrBlue : clrBlue ) : clrTextDormant );
			nk_layout_row_push( pContext, CalculateTextBounds( szText, 15 ).x );
			nk_label_colored( pContext, ( szText + str_t( PX_XOR( "  " ) ) ).c_str( ), NK_TEXT_LEFT, clrTextDormant );
		}

		int PX_API Tabs( unsigned uStartX, unsigned uStartY, const std::deque< cstr_t >& dqButtons, unsigned uActiveButton )
		{
			PX_DEF pxTabSpace = 24; // 12 * 2 - 12 px on either side.
			auto iPressedButton = -1;
			auto iXIncrement = 0;
			SetFont( FNT_ROBOTO_BOLD_SMALL );
			BeginRow( 45, dqButtons.size( ), ROW_CUSTOM );
			for ( unsigned i { }; i < dqButtons.size( ); i++ )
			{
				const int iButtonWidth = pxTabSpace + int( CalculateTextBounds( dqButtons.at( i ), 45 ).x );
				PushCustomRow( uStartX + iXIncrement, uStartY, iButtonWidth, 45 );
				iXIncrement += iButtonWidth;
				if ( PrimaryTab( dqButtons.at( i ), i == uActiveButton ) )
					iPressedButton = i;
			}
			HoverCheck( CURSOR_HAND );
			return iPressedButton;
		}

		int PX_API SubTabs( unsigned uStartX, unsigned uStartY, unsigned uButtonWidth, unsigned uButtonHeight, const std::deque< cstr_t >& dqButtons, unsigned uActiveButton )
		{
			nk_layout_space_begin( pContext, NK_STATIC, float( uButtonHeight * dqButtons.size( ) ), dqButtons.size( ) );
			auto iButtonPressed = -1;
			for ( unsigned i { }; i < dqButtons.size( ); i++ )
			{
				nk_layout_space_push( pContext, nk_rect( float( uStartX ), float( uStartY + uButtonHeight * i ), float( uButtonWidth ), float( uButtonHeight ) ) );
				if ( SecondaryTab( dqButtons.at( i ), i == uActiveButton ) )
					iButtonPressed = i;
			}
			nk_layout_space_end( pContext );
			HoverCheck( CURSOR_HAND );
			return iButtonPressed;
		}

		bool PX_API BeginGroupbox( unsigned uStartX, unsigned uStartY, unsigned uBoxWidth, unsigned uBoxHeight, cstr_t szTitle )
		{
			SetFont( FNT_TAHOMA );
			nk_layout_space_begin( pContext, NK_STATIC, float( uBoxHeight ), 1 );
			const auto recBoundaries = nk_widget_bounds( pContext );
			nk_layout_space_push( pContext, nk_rect( pContext->current->bounds.x + float( uStartX - recBoundaries.x ), pContext->current->bounds.y + float( uStartY - recBoundaries.y ), float( uBoxWidth ), float( uBoxHeight ) ) );
			auto recNewBoundaries = nk_widget_bounds( pContext );
			if ( !nk_group_begin( pContext, szTitle, NK_WINDOW_NO_SCROLLBAR ) )
				return false;

			const auto pOutput = nk_window_get_canvas( pContext );
			recNewBoundaries.x += 4;
			recNewBoundaries.y += 20;
			recNewBoundaries.w -= 8;
			recNewBoundaries.h -= 28;
			// Top left, top right, bottom right, bottom left
			const auto uTextWidth = CalculateTextBounds( szTitle, 30 ).x;
			nk_fill_rect_multi_color( pOutput, nk_rect( recNewBoundaries.x + 1.8f, recNewBoundaries.y + 1.f, recNewBoundaries.w - 2.f, recNewBoundaries.h - 2.f ),
									  clrDarkBackground, clrDarkBackground, clrBackground, clrBackground );
			nk_stroke_rect( pOutput, recNewBoundaries, 4.f, 1.f, clrBorder );
			nk_stroke_line( pOutput, recNewBoundaries.x + 7, recNewBoundaries.y, recNewBoundaries.x + 3 + uTextWidth, recNewBoundaries.y, 3, clrDarkBackground );
			BeginRow( 16, 1, ROW_CUSTOM );
			auto recText = nk_widget_bounds( pContext );
			PushCustomRow( unsigned( recNewBoundaries.x + 8 - recText.x ), unsigned( recNewBoundaries.y - recText.y - 10 ), unsigned( uTextWidth ), 16 );
			nk_label( pContext, szTitle, NK_TEXT_LEFT );
			VerticalSpacing( 5 );

			SetFont( FNT_ROBOTO_SMALL );
			return true;
		}

		void PX_API EndGroupbox( )
		{
			return nk_group_end( pContext );
		}

		constexpr float flPopupWidth = 305.f, flPopupHeight = 440.f;

		void PX_API ColorPicker( )
		{
			const auto _uWindowWidth = pContext->current->bounds.w, _uWindowHeight = pContext->current->bounds.h;
			const struct nk_rect recColorPickerBoundaries
			{
				pContext->current->bounds.x + _uWindowWidth / 2 - flPopupWidth / 2, pContext->current->bounds.y + _uWindowHeight / 2 - flPopupHeight / 2, flPopupWidth, flPopupHeight
			};
			const static str_t strBaseTitle = PX_XOR( R"(Color of ')" );

			static struct nk_colorf clrChosenColor;
			static auto bNewColor = true;
			static auto bShouldClose = false;
			static auto bStoppedClicking = false;
			static auto uCurrentSequence = 0u;
			static char szSliderBuffer[ 32 ];
			static auto bWasClicking = false;

			if ( !nk_input_is_mouse_hovering_rect( &pContext->input, recColorPickerBoundaries ) && PX_INPUT.GetKeyState( VK_LBUTTON ) && bStoppedClicking && !bWasClicking )
			{
				bShouldClose = true;
				bNewColor = true;
			}

			if ( !bWasClicking )
				bStoppedClicking = true;

			if ( bNewColor && pActiveEditColor )
			{
				uCurrentSequence = 0u;
				clrChosenColor = { pActiveEditColor->GetColor( uCurrentSequence ).rfl,
					pActiveEditColor->GetColor( uCurrentSequence ).gfl,
					pActiveEditColor->GetColor( uCurrentSequence ).bfl,
					pActiveEditColor->GetColor( uCurrentSequence ).afl };
				sprintf( szSliderBuffer, "%llu", pActiveEditColor->GetDuration( uCurrentSequence ) );
			}
			bNewColor = false;

			nk_fill_rect( nk_window_get_canvas( pContext ), nk_rect( pContext->current->bounds.x, pContext->current->bounds.y, _uWindowWidth, _uWindowHeight ), 0, nk_rgba( 0, 0, 0, 180 ) );

			if ( bShouldClose )
			{
				bShouldClose = false;
				pActiveEditColor = nullptr;
			}

			SetFont( FNT_ROBOTO_BOLD );
			if ( bStoppedClicking && nk_popup_begin( pContext, NK_POPUP_DYNAMIC, ( strBaseTitle + szColorPickerSubject + "'" ).c_str( ),
								 NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_NO_SCROLLBAR,
								 nk_rect( recColorPickerBoundaries.x - pContext->current->bounds.x, recColorPickerBoundaries.y - pContext->current->bounds.y,
										  recColorPickerBoundaries.w, recColorPickerBoundaries.h ), pActiveEditColor == nullptr ) )
			{
				SetFont( FNT_ROBOTO_SMALL );
				nk_layout_row_static( pContext, 255, 295, 1 );
				clrChosenColor = nk_color_picker( pContext, clrChosenColor, NK_RGBA );
				nk_layout_row_dynamic( pContext, 5, 0 );
				nk_layout_row_dynamic( pContext, 16, 4 );
				nk_label( pContext, ( PX_XOR( "R: " ) + std::to_string( int( clrChosenColor.r * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
				nk_label( pContext, ( PX_XOR( "G: " ) + std::to_string( int( clrChosenColor.g * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
				nk_label( pContext, ( PX_XOR( "B: " ) + std::to_string( int( clrChosenColor.b * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
				nk_label( pContext, ( PX_XOR( "A: " ) + std::to_string( int( clrChosenColor.a * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
				nk_layout_row_dynamic( pContext, 10, 1 );
				pContext->style.button.padding = nk_vec2( 0.f, 0.f );
				nk_button_color( pContext, nk_rgba( int( clrChosenColor.r * 255.f ),
													int( clrChosenColor.g * 255.f ),
													int( clrChosenColor.b * 255.f ),
													int( clrChosenColor.a * 255.f ) ) );

				nk_layout_row_begin( pContext, NK_STATIC, 15, pActiveEditColor->zSequences + 3 );
				nk_layout_row_push( pContext, COLOR_BUTTON_WIDTH );

				for ( auto u = 0u; u < pActiveEditColor->zSequences; u++ )
				{
					auto recBoundaries = nk_widget_bounds( pContext );
					if ( nk_button_color( pContext, nk_rgba( pActiveEditColor->GetColor( u ).r,
															 pActiveEditColor->GetColor( u ).g,
															 pActiveEditColor->GetColor( u ).b,
															 pActiveEditColor->GetColor( u ).a ) ) )
					{
						uCurrentSequence = u;
						clrChosenColor = { pActiveEditColor->GetColor( uCurrentSequence ).rfl,
							pActiveEditColor->GetColor( uCurrentSequence ).gfl,
							pActiveEditColor->GetColor( uCurrentSequence ).bfl,
							pActiveEditColor->GetColor( uCurrentSequence ).afl };
						sprintf( szSliderBuffer, "%llu", pActiveEditColor->GetDuration( uCurrentSequence ) );
					}
					if ( u == uCurrentSequence )
					{
						recBoundaries.x += 1;
						recBoundaries.y += 1;
						recBoundaries.w -= 2;
						recBoundaries.h -= 2;
						nk_stroke_rect( nk_window_get_canvas( pContext ), recBoundaries, pContext->style.button.rounding, 1.f, clrBlue );
					}
				}

				auto uPadding = flPopupWidth - COLOR_BUTTON_WIDTH * pActiveEditColor->zSequences - COLOR_BUTTON_PADDING * pActiveEditColor->zSequences * 2 - 170;
				nk_layout_row_push( pContext, uPadding );
				nk_spacing( pContext, 1 );
				nk_layout_row_push( pContext, 75 );

				if ( Button( EPosition::LEFT, PX_XOR( "+" ), false, false ) && !bWasClicking && pActiveEditColor->zSequences < 7 )
				{
					pActiveEditColor->PutNewColorSequence( color_t( ), 1000u );
					uCurrentSequence = pActiveEditColor->zSequences - 1;
					clrChosenColor = { pActiveEditColor->GetColor( uCurrentSequence ).rfl,
						pActiveEditColor->GetColor( uCurrentSequence ).gfl,
						pActiveEditColor->GetColor( uCurrentSequence ).bfl,
						pActiveEditColor->GetColor( uCurrentSequence ).afl };
				}
				if ( Button( EPosition::RIGHT, PX_XOR( "-" ), false, false ) && !bWasClicking && pActiveEditColor->zSequences > 1 )
				{
					pActiveEditColor->DeleteColorSequence( uCurrentSequence );
					uCurrentSequence = 0u;
					clrChosenColor = { pActiveEditColor->GetColor( uCurrentSequence ).rfl,
						pActiveEditColor->GetColor( uCurrentSequence ).gfl,
						pActiveEditColor->GetColor( uCurrentSequence ).bfl,
						pActiveEditColor->GetColor( uCurrentSequence ).afl };
				}

				nk_layout_row_end( pContext );
				pActiveEditColor->GetColor( uCurrentSequence ).rfl = clrChosenColor.r;
				pActiveEditColor->GetColor( uCurrentSequence ).gfl = clrChosenColor.g;
				pActiveEditColor->GetColor( uCurrentSequence ).bfl = clrChosenColor.b;
				pActiveEditColor->GetColor( uCurrentSequence ).afl = clrChosenColor.a;

				nk_layout_space_begin( pContext, NK_STATIC, 30, 3 );
				rowLastRowType = ROW_CUSTOM;
				pActiveEditColor->GetDuration( uCurrentSequence ) = Slider( PX_XOR( "Duration" ), szSliderBuffer, 100, 1000, int( pActiveEditColor->GetDuration( uCurrentSequence ) ), 0, 0, 290, 30, true );
				nk_layout_space_end( pContext );

				nk_layout_row_static( pContext, 25.f, int( flPopupWidth - 5 ), 1 );
				if ( Button( EPosition::LEFT, PX_XOR( "EXIT" ), false, false ) )
				{
					bShouldClose = true;
					bNewColor = true;
				}
				nk_layout_row_dynamic( pContext, 10, 0 );
				nk_popup_end( pContext );
				bWasClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == true;
				return;
			}
			bWasClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == true;
			bNewColor = true;
			bStoppedClicking = false;
		}

		void PX_API ToggleEditor( struct nk_rect recMainWindow )
		{
			const static std::map< int, str_t > mpCustomKeyNames
			{
				{ 0x0, "UNASSIGNED" },
				{ 0x01, "LMB" },
				{ 0x02, "RMB" },
				{ 0x03, "CNCL" },
				{ 0x04, "MMB" },
				{ 0x05, "X1" },
				{ 0x06, "X2" },
				{ 0x07, "UNDF" },
				{ 0x08, "BK" },
				{ 0x09, "TAB" },
				{ 0x0C, "CLR" },
				{ 0x0D, "RTN" },
				{ 0x10, "SHFT" },
				{ 0x11, "CTRL" },
				{ 0x12, "ALT" },
				{ 0x13, "PS" },
				{ 0x14, "CAPS" },
				{ 0x15, "KANA" },
				{ 0x16, "UNDF" },
				{ 0x17, "JNJ" },
				{ 0x18, "FNL" },
				{ 0x19, "HNJ" },
				{ 0x1A, "UNDF" },
				{ 0x1B, "ESC" },
				{ 0x1C, "CONV" },
				{ 0x1D, "NCNV" },
				{ 0x1E, "ACPT" },
				{ 0x1F, "CHNG" },
				{ 0x20, "SPCE" },
				{ 0x21, "PGUP" },
				{ 0x22, "PGDN" },
				{ 0x23, "END" },
				{ 0x24, "HOME" },
				{ 0x25, "LEFT" },
				{ 0x26, "UP" },
				{ 0x27, "RGHT" },
				{ 0x28, "DOWN" },
				{ 0x29, "SLCT" },
				{ 0x2A, "PRNT" },
				{ 0x2B, "EXEC" },
				{ 0x2C, "PRNT" },
				{ 0x2D, "-" },
				{ 0x2E, "DEL" },
				{ 0x2F, "HELP" },
				{ 0x5B, "LWIN" },
				{ 0x5C, "RWIN" },
				{ 0x5D, "APPS" },
				{ 0x5F, "SLP" },
				{ 0x60, "NUM0" },
				{ 0x61, "NUM1" },
				{ 0x62, "NUM2" },
				{ 0x63, "NUM3" },
				{ 0x64, "NUM4" },
				{ 0x65, "NUM5" },
				{ 0x66, "NUM6" },
				{ 0x67, "NUM7" },
				{ 0x68, "NUM8" },
				{ 0x69, "NUM9" },
				{ 0x6A, "*" },
				{ 0x6B, "+" },
				{ 0x6C, "SEP" },
				{ 0x6D, "-" },
				{ 0x6E, "." },
				{ 0x6F, "/" },
				{ 0x70, "F1" },
				{ 0x71, "F2" },
				{ 0x72, "F3" },
				{ 0x73, "F4" },
				{ 0x74, "F5" },
				{ 0x75, "F6" },
				{ 0x76, "F7" },
				{ 0x77, "F8" },
				{ 0x78, "F9" },
				{ 0x79, "F10" },
				{ 0x7A, "F11" },
				{ 0x7B, "F12" },
				{ 0x90, "NMLK" },
				{ 0x91, "SCLK" },
				{ 0xA0, "LSHF" },
				{ 0xA1, "RSHF" },
				{ 0xA2, "LCTL" },
				{ 0xA3, "RCTL" },
				{ 0xA4, "LMNU" },
				{ 0xA5, "RMNU" },
				{ 0xA6, "BACK" },
				{ 0xA7, "FRWD" },
				{ 0xA8, "RFRS" },
				{ 0xA9, "STOP" },
				{ 0xAA, "SRCH" }
			};

			constexpr auto flEditorHeight = 315.f, flEditorWidth = 305.f;

			const auto fnGetKeyName = [ ]( key_t kKey )
			{
				const auto pSearch = mpCustomKeyNames.find( kKey );
				if ( pSearch == mpCustomKeyNames.end( ) )
					return PX_XOR( "INVALID" );
				return pSearch->second.c_str( );
			};

			const static std::deque< cstr_t > dqBindModes
			{
				PX_XOR( "Inactive" ),
				PX_XOR( "Toggle" ),
				PX_XOR( "Enable While Pressed" ),
				PX_XOR( "Disable While Pressed" ),
				PX_XOR( "Enable" ),
				PX_XOR( "Disable" )
			};

			const struct nk_rect recPopupBoundaries
			{
				recMainWindow.x + recMainWindow.w / 2 - flEditorWidth / 2, recMainWindow.y + recMainWindow.h / 2 - flEditorHeight / 2, flEditorWidth, flEditorHeight
			};
			static auto bStoppedClicking = false;
			static auto bWasClicking = false;
			static auto iCurrentBindIndex = 0;
			static auto bSetGlobalKeyCallback = false;
			static key_t* pCurrentEditKey = nullptr;

			if( !bSetGlobalKeyCallback )
			{
				bSetGlobalKeyCallback = true;
				PX_INPUT.AddGlobalCallback( [ ]( unsigned uKey, bool bPressed )
				{
					if ( bPressed && pCurrentEditKey != nullptr )
					{
						*pCurrentEditKey = uKey;
						pCurrentEditKey = nullptr;
					}
				} );
			}

			if ( !nk_input_is_mouse_hovering_rect( &pContext->input, recPopupBoundaries ) && PX_INPUT.GetKeyState( VK_LBUTTON ) && bStoppedClicking && !bWasClicking )
			{
				pActiveEditToggle = nullptr;
				iCurrentBindIndex = 0;
				return;
			}

			SetFont( FNT_ROBOTO_BOLD );
			if( bStoppedClicking && nk_begin( pContext, PX_XOR( "Keybind Editor" ), recPopupBoundaries, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_TITLE ) )
			{
				nk_layout_row_begin( pContext, NK_STATIC, 25, 3 );
				nk_layout_row_push( pContext, 5.f );
				nk_spacing( pContext, 1 );
				nk_layout_row_push( pContext, 140.f );
				if( Button( EPosition::LEFT, PX_XOR( "+" ), false, pActiveEditToggle->GetBinds( ).size( ) >= 7 ) && !bWasClicking )
					pActiveEditToggle->GetBinds( ).emplace_back( toggle_t::keybind_t( ) );
				if ( Button( EPosition::RIGHT, PX_XOR( "-" ), false, pActiveEditToggle->GetBinds( ).empty( ) ) && !bWasClicking )
				{
					pActiveEditToggle->GetBinds( ).erase( pActiveEditToggle->GetBinds( ).begin( ) + iCurrentBindIndex );
					iCurrentBindIndex = 0;
				}
				nk_layout_row_end( pContext );

				nk_layout_row_begin( pContext, NK_STATIC, 30, 3 );
				nk_layout_row_push( pContext, 5.f );
				nk_spacing( pContext, 1 );
				PopupCheckbox( PX_XOR( "Use Keybinds" ), &pActiveEditToggle->UseKeyBinds( ) );
				nk_layout_row_end( pContext );

				if( !pActiveEditToggle->GetBinds( ).empty( ) )
				{
					std::deque< cstr_t > dqKeys;
					for ( auto& keybind : pActiveEditToggle->GetBinds( ) )
						dqKeys.emplace_back( fnGetKeyName( keybind.kKey ) );

					nk_layout_row_begin( pContext, NK_STATIC, 30, 3 );
					nk_layout_row_push( pContext, 5.f );
					nk_spacing( pContext, 1 );
					nk_layout_row_push( pContext, 184.f );
					const auto iNewIndex = Combobox( 30, PX_XOR( "Keys" ), dqKeys, iCurrentBindIndex );
					if ( iNewIndex > -1 )
					{
						iCurrentBindIndex = iNewIndex;
						nk_popup_end( pContext );
					}

					auto& bind = pActiveEditToggle->GetBinds( ).at( iCurrentBindIndex );
					nk_layout_row_push( pContext, 97.f );
					if( Button( EPosition::NONE, fnGetKeyName( bind.kKey ), false, false ) )
					{
						bind.kKey = 0x2D;
						pCurrentEditKey = &bind.kKey;
					}
					nk_layout_row_end( pContext );

					nk_layout_row_begin( pContext, NK_STATIC, 30, 2 );
					nk_layout_row_push( pContext, 5.f );
					nk_spacing( pContext, 1 );
					nk_layout_row_push( pContext, 184.f );
					const auto iNewBindType = Combobox( 30, PX_XOR( "Mode" ), dqBindModes, bind.iKeyBindMode );
					if ( iNewBindType > -1 )
						bind.iKeyBindMode = iNewBindType;
					nk_layout_row_end( pContext );
				}

				if ( bDrawComboboxArrow )
				{
					const auto pDrawBuffer = nk_window_get_canvas( pContext );
					nk_stroke_line( pDrawBuffer, recComboboxWindowBounds.x, recComboboxWindowBounds.y - 2, recComboboxWindowBounds.x + recComboboxWindowBounds.w, recComboboxWindowBounds.y - 2, 2, clrBorder );
					recComboboxWindowBounds.y -= 3;
					nk_fill_triangle( pDrawBuffer, recComboboxWindowBounds.x + recComboboxWindowBounds.w - 3, recComboboxWindowBounds.y, recComboboxWindowBounds.x + recComboboxWindowBounds.w - 10, recComboboxWindowBounds.y - 7, recComboboxWindowBounds.x + recComboboxWindowBounds.w - 17, recComboboxWindowBounds.y, clrBackground );
					recComboboxWindowBounds.y += 3;
				}

				nk_end( pContext );
			}

			if ( !bWasClicking )
				bStoppedClicking = true;
			bWasClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == true;
		}

		bool PX_API PopupActive( )
		{
			return pActiveEditColor != nullptr || pActiveEditToggle != nullptr;
		}

		void PX_API ColorButton( cstr_t szSubject, color_sequence_t* pSequence, float flVerticalPadding /*= 0.f*/ )
		{
			iCurrentRowUsedColumns++;

			const auto clr = pSequence->GetCurrentColor( );
			pContext->style.button.padding = nk_vec2( 0.f, flVerticalPadding );
			if ( nk_button_color( pContext, nk_rgba( clr.r, clr.g, clr.b, clr.a ) ) && pActiveEditColor == nullptr )
			{
				szColorPickerSubject = szSubject;
				pActiveEditColor = pSequence;
			}
			HoverCheck( CURSOR_HAND );
		}

		int PX_API Combobox( unsigned uButtonHeight, cstr_t szTitle, const std::deque< cstr_t >& dqOptions, unsigned uSelectedOption )
		{
			iCurrentRowUsedColumns++;

			auto iSelectedOption = -1;
			auto bDrewCombo = false;
			SetFont( FNT_TAHOMA );
			const auto recComboboxBounds = nk_widget_bounds( pContext );

			const auto pOutput = nk_window_get_canvas( pContext );
			if ( nk_combo_begin_label( pContext, szTitle, nk_vec2( recComboboxBounds.w, float( uButtonHeight ) * dqOptions.size( ) + 4 * ( dqOptions.size( ) - 1 ) ) ) )
			{
				bDrawComboboxArrow = true;
				recComboboxWindowBounds = pContext->current->bounds;
				nk_layout_space_begin( pContext, NK_STATIC, uButtonHeight, dqOptions.size( ) );
				auto y = -1;
				for ( unsigned i { }; i < dqOptions.size( ); i++ )
				{
					if ( !dqOptions.at( i ) )
					{
						nk_spacing( pContext, 1 );
						continue;
					}
					if ( i == uSelectedOption )
						pContext->style.contextual_button = btnComboActive;
					else
						pContext->style.contextual_button = btnCombo;

					nk_layout_space_push( pContext, nk_rect( i == 0 ? 0.f : 5.f, y, recComboboxWindowBounds.w, uButtonHeight ) );
					if ( nk_combo_item_label( pContext, dqOptions.at( i ), NK_TEXT_LEFT ) )
						iSelectedOption = i;
					y += uButtonHeight;
					HoverCheck( CURSOR_HAND );
				}
				nk_layout_space_end( pContext );
				nk_combo_end( pContext );
				bDrewCombo = true;
				if( PopupActive( ) )
					nk_d3d9_handle_event( hwWindowHandle, WM_LBUTTONUP, 0, int( pContext->input.mouse.pos.x ) | int( pContext->input.mouse.pos.y ) << 16 );
			}
			HoverCheck( CURSOR_HAND );
			nk_fill_triangle( pOutput, recComboboxBounds.x + recComboboxBounds.w - 10, recComboboxBounds.y + recComboboxBounds.h / 2 - 3, recComboboxBounds.x + recComboboxBounds.w - 14, recComboboxBounds.y + recComboboxBounds.h / 2 + 3, recComboboxBounds.x + recComboboxBounds.w - 18, recComboboxBounds.y + recComboboxBounds.h / 2 - 3, nk_input_is_mouse_prev_hovering_rect( &pContext->input, recComboboxBounds ) && !bDrewCombo ? clrTextActive : clrTextDormant );
			return iSelectedOption;
		}

		void PX_API TabbedCombobox( unsigned uButtonHeight, cstr_t szTitle, const std::deque< cstr_t >& dqTabs, const std::deque< cstr_t >* pItems, unsigned& uSelectedOption )
		{
			const auto fnGetTrueIndex = [ ]( const std::deque< cstr_t >* pTabs, unsigned uCurrentTab, unsigned uIndex )
			{
				auto uReturn = 0u;
				for ( auto u = 0u; u < uCurrentTab; u++ )
					uReturn += pTabs[ u ].size( );
				return uReturn + uIndex;
			};

			auto uTab = 0u, d = uSelectedOption;
			for ( auto u = 0u; u < dqTabs.size( ); u++ )
			{
				if ( d < pItems[ u ].size( ) )
				{
					uTab = u;
					break;
				}
				d -= pItems[ u ].size( );
			}

			iCurrentRowUsedColumns++;

			auto bDrewCombo = false;
			SetFont( FNT_TAHOMA );
			const auto recComboboxBounds = nk_widget_bounds( pContext );
			const auto pOutput = nk_window_get_canvas( pContext );

			auto dqCurrentItems = pItems[ uTab ];
			if ( nk_combo_begin_label( pContext, szTitle, nk_vec2( recComboboxBounds.w, float( uButtonHeight ) * ( dqCurrentItems.size( ) + 1u ) + 4 * dqCurrentItems.size( ) ) ) )
			{
				bDrawComboboxArrow = true;
				recComboboxWindowBounds = pContext->current->bounds;
				const int iButtonWidth = int( ( recComboboxBounds.w - 10 - ( dqTabs.size( ) - 1 ) * 4 ) / dqTabs.size( ) );
				nk_layout_row_begin( pContext, NK_STATIC, float( uButtonHeight ), dqTabs.size( ) + 1 );
				nk_layout_row_push( pContext, 0 );
				nk_spacing( pContext, 1 );
				nk_layout_row_push( pContext, float( iButtonWidth ) );
				for ( auto u = 0u; u < dqTabs.size( ); u++ )
					if ( PrimaryTab( dqTabs[ u ], u == uTab ) )
					{
						dqCurrentItems = pItems[ ( uTab = u ) ];
						uSelectedOption = fnGetTrueIndex( pItems, uTab, 0u );
					}
				iCurrentRowUsedColumns -= dqTabs.size( );
				nk_layout_row_end( pContext );
				Separator( 61, 65, 72, uButtonHeight - 2.f, nullptr, false, 6.f );
				SetFont( FNT_TAHOMA );

				nk_layout_space_begin( pContext, NK_STATIC, 30, dqCurrentItems.size( ) );
				auto y = -1;
				for ( unsigned i { }; i < dqCurrentItems.size( ); i++ )
				{
					if ( i == d )
						pContext->style.contextual_button = btnComboActive;
					else
						pContext->style.contextual_button = btnCombo;

					nk_layout_space_push( pContext, nk_rect( i == 0 ? 0.f : 5.f, y, recComboboxWindowBounds.w, uButtonHeight ) );
					if ( nk_combo_item_label( pContext, dqCurrentItems.at( i ), NK_TEXT_LEFT ) )
						uSelectedOption = fnGetTrueIndex( pItems, uTab, i );
					y += uButtonHeight;
					HoverCheck( CURSOR_HAND );
				}
				nk_layout_space_end( pContext );
				nk_combo_end( pContext );
				bDrewCombo = true;
				if ( PopupActive( ) )
					nk_d3d9_handle_event( hwWindowHandle, WM_LBUTTONUP, 0, int( pContext->input.mouse.pos.x ) | int( pContext->input.mouse.pos.y ) << 16 );
			}
			HoverCheck( CURSOR_HAND );
			nk_fill_triangle( pOutput, recComboboxBounds.x + recComboboxBounds.w - 10, recComboboxBounds.y + recComboboxBounds.h / 2 - 3, recComboboxBounds.x + recComboboxBounds.w - 14, recComboboxBounds.y + recComboboxBounds.h / 2 + 3, recComboboxBounds.x + recComboboxBounds.w - 18, recComboboxBounds.y + recComboboxBounds.h / 2 - 3, nk_input_is_mouse_prev_hovering_rect( &pContext->input, recComboboxBounds ) && !bDrewCombo ? clrTextActive : clrTextDormant );
		}

		void PX_API ComboboxMulti( unsigned uButtonHeight, cstr_t szTitle, const std::deque< cstr_t >& dqOptions, std::deque< bool* >& dqEnabledOptions )
		{
			iCurrentRowUsedColumns++;

			auto bDrewCombo = false;
			SetFont( FNT_TAHOMA );
			const auto recComboboxBounds = nk_widget_bounds( pContext );

			const auto pOutput = nk_window_get_canvas( pContext );
			if ( nk_combo_begin_label( pContext, szTitle, nk_vec2( recComboboxBounds.w, float( uButtonHeight ) * dqOptions.size( ) + 5 * ( dqOptions.size( ) - 1 ) - 3 ) ) )
			{
				bDrawComboboxArrow = true;
				recComboboxWindowBounds = pContext->current->bounds;
				auto y = -1;
				nk_layout_space_begin( pContext, NK_STATIC, uButtonHeight, dqOptions.size( ) );
				for ( unsigned i { }; i < dqOptions.size( ); i++ )
				{
					if ( !dqOptions[ i ] )
					{
						nk_spacing( pContext, 1 );
						continue;
					}
					nk_layout_space_push( pContext, nk_rect( y == 0 ? 0.f : 5.f, y, recComboboxWindowBounds.w, uButtonHeight ) );
					if ( nk_button_label_styled( pContext, *dqEnabledOptions.at( i ) ? &btnComboActive : &btnCombo, dqOptions.at( i ) ) )
						*dqEnabledOptions.at( i ) = !*dqEnabledOptions.at( i );
					y += uButtonHeight;
					HoverCheck( CURSOR_HAND );
				}
				nk_layout_space_end( pContext );
				nk_combo_end( pContext );
				bDrewCombo = true;
			}
			HoverCheck( CURSOR_HAND );
			nk_fill_triangle( pOutput, recComboboxBounds.x + recComboboxBounds.w - 10, recComboboxBounds.y + recComboboxBounds.h / 2 - 3, recComboboxBounds.x + recComboboxBounds.w - 14, recComboboxBounds.y + recComboboxBounds.h / 2 + 3, recComboboxBounds.x + recComboboxBounds.w - 18, recComboboxBounds.y + recComboboxBounds.h / 2 - 3, nk_input_is_mouse_prev_hovering_rect( &pContext->input, recComboboxBounds ) && !bDrewCombo ? clrTextActive : clrTextDormant );
		}

		void PX_API TabbedComboboxMulti( unsigned uButtonHeight, Types::cstr_t szTitle, const std::deque< Types::cstr_t >& dqTabs, const std::deque< Types::cstr_t >* pItems, std::deque< bool* >& dqEnabledOptions, unsigned& uCurrentTab )
		{
			const auto fnGetTrueIndex = [ ]( const std::deque< cstr_t >* pTabs, unsigned uCurrentTab, unsigned uIndex )
			{
				auto uReturn = 0u;
				for ( auto u = 0u; u < uCurrentTab; u++ )
					uReturn += pTabs[ u ].size( );
				return uReturn + uIndex;
			};

			auto d = fnGetTrueIndex( pItems, uCurrentTab, 0 );

			iCurrentRowUsedColumns++;

			auto bDrewCombo = false;
			SetFont( FNT_TAHOMA );
			const auto recComboboxBounds = nk_widget_bounds( pContext );

			const auto pOutput = nk_window_get_canvas( pContext );
			auto dqCurrentItems = pItems[ uCurrentTab ];
			if ( nk_combo_begin_label( pContext, szTitle, nk_vec2( recComboboxBounds.w, float( uButtonHeight ) * ( dqCurrentItems.size( ) + 1u ) + 4.f * dqCurrentItems.size( ) + 10.f ) ) )
			{
				bDrawComboboxArrow = true;
				recComboboxWindowBounds = pContext->current->bounds;
				const int iButtonWidth = int( ( recComboboxBounds.w - 10 - ( dqTabs.size( ) - 1 ) * 4 ) / dqTabs.size( ) );
				nk_layout_row_begin( pContext, NK_STATIC, float( uButtonHeight ), dqTabs.size( ) + 1 );
				nk_layout_row_push( pContext, 0 );
				nk_spacing( pContext, 1 );
				nk_layout_row_push( pContext, float( iButtonWidth ) );
				for ( auto u = 0u; u < dqTabs.size( ); u++ )
					if ( PrimaryTab( dqTabs[ u ], u == uCurrentTab ) )
					{
						dqCurrentItems = pItems[ ( uCurrentTab = u ) ];
						d = fnGetTrueIndex( pItems, uCurrentTab, 0 );
					}
				iCurrentRowUsedColumns -= dqTabs.size( );
				nk_layout_row_end( pContext );
				Separator( 61, 65, 72, uButtonHeight - 2.f, nullptr, false, 6.f );
				SetFont( FNT_TAHOMA );

				nk_layout_space_begin( pContext, NK_STATIC, 30, dqCurrentItems.size( ) );
				auto y = -1;
				for ( unsigned i { }; i < dqCurrentItems.size( ); i++, d++ )
				{
					if ( !dqCurrentItems[ i ] )
					{
						nk_spacing( pContext, 1 );
						continue;
					}

					nk_layout_space_push( pContext, nk_rect( 0, y, recComboboxWindowBounds.w, uButtonHeight ) );
					if ( nk_button_label_styled( pContext, *dqEnabledOptions.at( d ) ? &btnComboActive : &btnCombo, dqCurrentItems.at( i ) ) )
						*dqEnabledOptions.at( d ) = !*dqEnabledOptions.at( d );
					y += uButtonHeight;
					HoverCheck( CURSOR_HAND );
				}
				nk_layout_space_end( pContext );
				nk_combo_end( pContext );
				bDrewCombo = true;
			}
			HoverCheck( CURSOR_HAND );
			nk_fill_triangle( pOutput, recComboboxBounds.x + recComboboxBounds.w - 10, recComboboxBounds.y + recComboboxBounds.h / 2 - 3, recComboboxBounds.x + recComboboxBounds.w - 14, recComboboxBounds.y + recComboboxBounds.h / 2 + 3, recComboboxBounds.x + recComboboxBounds.w - 18, recComboboxBounds.y + recComboboxBounds.h / 2 - 3, nk_input_is_mouse_prev_hovering_rect( &pContext->input, recComboboxBounds ) && !bDrewCombo ? clrTextActive : clrTextDormant );
		}

		void PX_API Inputbox( unsigned uMaxCharacters, char* szBuffer )
		{
			iCurrentRowUsedColumns++;
			nk_edit_string_zero_terminated( pContext, NK_EDIT_FIELD, szBuffer, uMaxCharacters, nk_filter_ascii );
		}

		int PX_API InputboxInteger( unsigned uMaxCharacters, char* szBuffer )
		{
			iCurrentRowUsedColumns++;
			nk_edit_string_zero_terminated( pContext, NK_EDIT_FIELD, szBuffer, uMaxCharacters, nk_filter_decimal );
			if ( strlen( szBuffer ) > 0 && strcmp( szBuffer, PX_XOR( "-" ) ) )
				return std::stoi( szBuffer );
			return 0;
		}

		bool ValidFloat( char* szFloat )
		{
			return strlen( szFloat ) > 0 && strcmp( szFloat, PX_XOR( "-" ) ) && strcmp( szFloat, PX_XOR( "." ) ) && strcmp( szFloat, PX_XOR( "-." ) );
		}

		float PX_API InputboxFloat( unsigned uMaxCharacters, char* szBuffer )
		{
			iCurrentRowUsedColumns++;
			nk_edit_string_zero_terminated( pContext, NK_EDIT_FIELD, szBuffer, uMaxCharacters, nk_filter_float );
			if ( ValidFloat( szBuffer ) )
				return std::stof( szBuffer );
			return 0.f;
		}

		struct slider_info_t
		{
			bool bInEdit = false, bSetEditValue = false, bWasClickingInBoundaries = false, bWasClicking = false;
		};

		int PX_API Slider( cstr_t szTitle, char* szInputBuffer, int iMin, int iMax, int iCurrentValue, unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight, bool bIgnorePopup /*= false*/ )
		{
			iCurrentRowUsedColumns += 3;

			px_assert( iMax > iMin );
			auto szTexta = std::to_string( iCurrentValue ).substr( 0, std::to_string( iCurrentValue ).size( ) );
			auto szText = szTexta.c_str( );
			static auto bInEdit = false, bSetEditValue = false, bWasClickingInBoundaries = false, bWasClicking = false;

			SetFont( FNT_ROBOTO_SMALL );
			const auto vecTitleSize = CalculateTextBounds( szTitle, 10 );
			auto vecTextSize = CalculateTextBounds( szText, 10 );
			PushCustomRow( uStartX + 5, uStartY, unsigned( vecTitleSize.x ), unsigned( vecTitleSize.y ) );
			nk_label( pContext, szTitle, NK_TEXT_LEFT );
			PushCustomRow( uStartX + uWidth - unsigned( vecTextSize.x ) - 5, uStartY, unsigned( vecTextSize.x ), unsigned( vecTextSize.y ) );

			const auto recBounds = nk_widget_bounds( pContext );
			const auto bHovering = nk_input_is_mouse_hovering_rect( &pContext->input, recBounds );
			const auto bClicking = bool( PX_INPUT.GetKeyState( VK_LBUTTON ) );

			if ( bHovering && !bInEdit )
			{
				bFoundHoverTarget = true;
				SetWidgetActive( CURSOR_HAND );
				if ( bClicking )
				{
					bInEdit = true;
					strcpy( szInputBuffer, szText );
				}
			}
			auto bHoveringInputBox = false;

			if ( bInEdit )
			{
				iCurrentRowUsedColumns--;
				PushCustomRow( uStartX + unsigned( vecTitleSize.x ) + 8, uStartY, uWidth - unsigned( vecTitleSize.x ), unsigned( vecTextSize.y ) + 5 );
				const auto recNewBounds = nk_widget_bounds( pContext );
				iCurrentValue = InputboxInteger( strlen( std::to_string( FLT_MAX ).c_str( ) ), szInputBuffer );
				bHoveringInputBox = nk_input_is_mouse_hovering_rect( &pContext->input, recNewBounds );

				if ( bHoveringInputBox )
					SetWidgetActive( CURSOR_IBEAM );
				if ( PX_INPUT.GetKeyState( VK_RETURN ) == true || !bHoveringInputBox && bClicking )
				{
					bSetEditValue = strlen( szInputBuffer ) > 0;
					bInEdit = false;
				}
			}
			else if ( bSetEditValue )
			{
				bSetEditValue = false;
				const auto iValue = std::stoi( szInputBuffer );
				iCurrentValue = iValue <= iMax ? ( iValue >= iMin ? iValue : iMin ) : iMax;
			}
			else
				nk_label( pContext, szText, NK_TEXT_LEFT );

			PushCustomRow( uStartX, uStartY + unsigned( vecTextSize.y ) + 3, uWidth, uHeight - unsigned( vecTextSize.y ) - 3 );

			const auto recSliderBounds = nk_widget_bounds( pContext );
			if ( nk_input_is_mouse_hovering_rect( &pContext->input, recSliderBounds ) && bClicking && ( PopupActive( ) || bIgnorePopup ) || bWasClickingInBoundaries && bWasClicking )
			{
				bWasClickingInBoundaries = true;
				iCurrentValue = int( iMin + ( pContext->input.mouse.pos.x - recSliderBounds.x ) / recSliderBounds.w * ( iMax - iMin ) );
			}
			else
				bWasClickingInBoundaries = false;

			bWasClicking = bool( PX_INPUT.GetKeyState( VK_LBUTTON ) );

			const auto iNewValue = nk_slide_int( pContext, iMin, iCurrentValue, iMax, ( iMax - iMin ) / 20 );
			if ( !bInEdit )
				iCurrentValue = iNewValue;
			HoverCheck( CURSOR_HAND );
			SetFont( FNT_ROBOTO_SMALL );
			return iCurrentValue;
		}

		float PX_API Slider( cstr_t szTitle, char* szInputBuffer, float flMin, float flMax, float flCurrentValue, unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight, unsigned uDigits )
		{
			static std::vector< slider_info_t > vecSliderInfo;
			if ( uSliderFloatCounter >= vecSliderInfo.size( ) )
				vecSliderInfo.emplace_back( slider_info_t( ) );
			auto& siCurrent = vecSliderInfo.at( uSliderFloatCounter );

			uSliderFloatCounter++;
			iCurrentRowUsedColumns += 3;

			px_assert( flMax > flMin );
			auto szTexta = std::to_string( flCurrentValue ).substr( 0, std::to_string( int( flCurrentValue ) ).size( ) + ( flCurrentValue < 0.f ? 2 : 1 ) + uDigits );
			auto szText = szTexta.c_str( );

			SetFont( FNT_ROBOTO_SMALL );
			auto vecTitleSize = CalculateTextBounds( szTitle, 10 );
			auto vecTextSize = CalculateTextBounds( szText, 10 );
			PushCustomRow( uStartX + 5, uStartY, unsigned( vecTitleSize.x ), unsigned( vecTitleSize.y ) );
			nk_label( pContext, szTitle, NK_TEXT_LEFT );
			PushCustomRow( uStartX + uWidth - unsigned( vecTextSize.x ) - 5, uStartY, unsigned( vecTextSize.x ), unsigned( vecTextSize.y ) );

			const auto recBounds = nk_widget_bounds( pContext );
			const auto bHovering = nk_input_is_mouse_hovering_rect( &pContext->input, recBounds );
			const auto bClicking = PX_INPUT.GetKeyState( VK_LBUTTON );

			if ( bHovering && !siCurrent.bInEdit )
			{
				SetWidgetActive( CURSOR_HAND );
				if ( bClicking )
				{
					siCurrent.bInEdit = true;
					strcpy( szInputBuffer, szText );
				}
			}
			auto bHoveringInputBox = false;

			if ( siCurrent.bInEdit )
			{
				iCurrentRowUsedColumns--;
				PushCustomRow( uStartX + unsigned( vecTitleSize.x ) + 8, uStartY, uWidth - unsigned( vecTitleSize.x ), unsigned( vecTextSize.y ) + 5 );
				const auto recNewBounds = nk_widget_bounds( pContext );
				flCurrentValue = InputboxFloat( strlen( std::to_string( FLT_MAX ).c_str( ) ), szInputBuffer );
				bHoveringInputBox = nk_input_is_mouse_hovering_rect( &pContext->input, recNewBounds );

				if ( bHoveringInputBox )
					SetWidgetActive( CURSOR_IBEAM );

				if ( PX_INPUT.GetKeyState( VK_RETURN ) == true || !bHoveringInputBox && bClicking )
				{
					siCurrent.bSetEditValue = strlen( szInputBuffer ) > 0;
					siCurrent.bInEdit = false;
				}
			}
			else if ( siCurrent.bSetEditValue )
			{
				siCurrent.bSetEditValue = false;
				const auto iValue = ValidFloat( szInputBuffer ) ? std::stof( szInputBuffer ) : flCurrentValue;
				flCurrentValue = iValue <= flMax ? ( iValue >= flMin ? iValue : flMin ) : flMax;
			}
			else
				nk_label( pContext, szText, NK_TEXT_LEFT );

			PushCustomRow( uStartX, uStartY + unsigned( vecTextSize.y ) + 3, uWidth, uHeight - unsigned( vecTextSize.y ) - 3 );

			const auto recSliderBounds = nk_widget_bounds( pContext );
			if ( nk_input_is_mouse_hovering_rect( &pContext->input, recSliderBounds ) && bClicking && !PopupActive( ) || siCurrent.bWasClickingInBoundaries && siCurrent.bWasClicking )
			{
				siCurrent.bWasClickingInBoundaries = true;
				flCurrentValue = flMin + ( pContext->input.mouse.pos.x - recSliderBounds.x ) / recSliderBounds.w * ( flMax - flMin );
			}
			else
				siCurrent.bWasClickingInBoundaries = false;

			siCurrent.bWasClicking = bool( PX_INPUT.GetKeyState( VK_LBUTTON ) );

			if ( nk_input_is_mouse_hovering_rect( &pContext->input, recSliderBounds ) && bClicking && !PopupActive( ) )
				flCurrentValue = flMin + ( pContext->input.mouse.pos.x - recSliderBounds.x ) / recSliderBounds.w * ( flMax - flMin );

			const auto flNewValue = nk_slide_float( pContext, flMin, flCurrentValue, flMax, ( flMax - flMin ) / 20.f );
			if ( !siCurrent.bInEdit )
				flCurrentValue = flNewValue;
			HoverCheck( CURSOR_HAND );
			SetFont( FNT_ROBOTO_SMALL );
			return flCurrentValue;
		}

		void PX_API Text( cstr_t szText, color_t clrText )
		{
			iCurrentRowUsedColumns++;
			return nk_label_colored( pContext, szText, NK_TEXT_CENTERED, nk_rgba( clrText.r, clrText.g, clrText.b, clrText.a ) );
		}

		void PX_API JustifiedText( cstr_t szLeft, cstr_t szRight, color_t clrLeft, color_t clrRight, unsigned uTotalLength )
		{
			auto uLeftTextWidth = CalculateTextBounds( szLeft, 15 ).x, uRightTextWidth = CalculateTextBounds( szRight, 15 ).x;
			auto iSpacing = int( uTotalLength ) - int( uLeftTextWidth + uRightTextWidth );
			px_assert( iSpacing >= 0 );
			auto vec = nk_widget_bounds( pContext );

			SetRowWidth( uLeftTextWidth );
			Text( szLeft, clrLeft );
			SetRowWidth( float( iSpacing ) );
			Spacing( );
			SetRowWidth( uRightTextWidth );
			Text( szRight, clrRight );
		}

		void PX_API BeginRow( unsigned uRowHeight, unsigned uColumns, ERowType rowType )
		{
			typedef void( PX_API* fn_begin_row_t )( nk_context*, nk_layout_format, float, int );
			static fn_begin_row_t fnBeginRow[ ROW_MAX ]
			{
				nk_layout_row_begin,
				nk_layout_row_begin,
				nk_layout_space_begin
			};

			rowLastRowType = rowType;
			iCurrentRowUsedColumns = 0;
			iCurrentRowMaxColumns = uColumns;

			return fnBeginRow[ rowType ]( pContext, rowType == ROW_DYNAMIC ? NK_DYNAMIC : NK_STATIC, float( uRowHeight ), uColumns );
		}

		void PX_API EndRow( )
		{
			typedef void( PX_API* fn_end_row_t )( nk_context* );
			static fn_end_row_t fnEndRow[ ROW_MAX ]
			{
				nk_layout_row_end,
				nk_layout_row_end,
				nk_layout_space_end
			};

			px_assert( iCurrentRowUsedColumns == iCurrentRowMaxColumns );
			fnEndRow[ rowLastRowType ]( pContext );
		}

		void PX_API SetRowWidth( float flRowWidth )
		{
			px_assert( rowLastRowType == ROW_STATIC );
			return nk_layout_row_push( pContext, flRowWidth );
		}

		void PX_API Spacing( unsigned uColumns /*= 1*/ )
		{
			px_assert( ( iCurrentRowUsedColumns += uColumns ) <= iCurrentRowMaxColumns );
			nk_spacing( pContext, uColumns );
			if ( iCurrentRowUsedColumns == iCurrentRowMaxColumns )
				EndRow( );
		}

		void PX_API VerticalSpacing( unsigned uPixels /*= 5*/ )
		{
			BeginRow( uPixels, 0, ROW_STATIC );
			EndRow( );
		}

		void PX_API PushCustomRow( int iStartX, int iStartY, unsigned uWidth, unsigned uHeight )
		{
			px_assert( rowLastRowType == ROW_CUSTOM );
			return nk_layout_space_push( pContext, nk_rect( float( iStartX ), float( iStartY ), float( uWidth ), float( uHeight ) ) );
		}

		void PX_API DisplayBox( cstr_t szData, std::size_t zLength )
		{
			int iLength = zLength;
			iCurrentRowUsedColumns++;
			nk_edit_string( pContext, NK_EDIT_READ_ONLY | NK_EDIT_MULTILINE, const_cast< char* >( szData ), &iLength, iLength + 1, nk_filter_ascii );
		}												  
	}
}
