/// User Interface.cpp

#define NK_IMPLEMENTATION

#include "../Framework.hpp"

namespace Paladin
{
	LRESULT WINAPI WndProc( HWND hwWindowHandle, UINT uMessage, WPARAM uwParam, LPARAM llParam )
	{
		ui->OnEvent( hwWindowHandle, uMessage, uwParam, llParam );

		switch ( uMessage )
		{
			case WM_SETCURSOR:
				if( llParam == HTCLIENT ) 
					return true;

			case WM_DESTROY:
				PostQuitMessage( 0 );
				return 0;

			case WM_SIZE:
				if ( ui->pDevice )
				{
					const auto uWidth = LOWORD( llParam );
					const auto uHeight = HIWORD( llParam );
					if ( uWidth != 0 && uHeight != 0 &&
						( uWidth != ui->dxParameters.BackBufferWidth || uHeight != ui->dxParameters.BackBufferHeight ) )
					{
						nk_d3d9_release( );
						ui->dxParameters.BackBufferWidth = uWidth;
						ui->dxParameters.BackBufferHeight = uHeight;
						const auto hrReset = ui->pDevice->Reset( &ui->dxParameters );
						dbg::Assert( hrReset >= 0 );
						nk_d3d9_resize( uWidth, uHeight );
					}
				}
				break;
			default:;
		}

		return nk_d3d9_handle_event( hwWindowHandle, uMessage, uwParam, llParam )
			? ( ui->uOldWindowProc
				? CallWindowProc( reinterpret_cast< WNDPROC >( ui->uOldWindowProc ), hwWindowHandle, uMessage, uwParam, llParam )
				: 0 )
			: DefWindowProc( hwWindowHandle, uMessage, uwParam, llParam );
	}

	CUserInterface::CUserInterface( const char *szDesiredNuklearWindowTitle, const char *szDesiredApplicationName, unsigned *uDesiredWindowSize, const wchar_t *szDesiredWindowClassTitle )
		: pContext { }, pAtlas { }, pTahoma { }, pTahomaBold { }, pRoboto { }, pRobotoBold { }, pRobotoSmall { }, pRobotoBoldSmall { }, bDrawComboboxArrow { }, rcComboboxWindowBounds { }, 
		  szNuklearWindowTitle { szDesiredNuklearWindowTitle }, szApplicationTitle { szDesiredApplicationName }, bFoundHoverTarget { }, clrColors { }, clrTextDormant { 175, 180, 187, 255 }, 
		  clrTextActive { 255, 255, 255, 255 }, clrBlue { 33, 150, 243, 255 }, clrDarkBlue { 43, 60, 75, 255 }, clrBackground { 56, 60, 66, 255 }, clrLightBackground { 61, 65, 72, 255 }, 
		  clrDarkBackground { 45, 50, 56, 255 }, clrBorder { 80, 84, 89, 255 }, clrToolbox { 42, 44, 48, 255 }, clrHeader { 33, 36, 40, 255 }, clrBlueActive { 54, 70, 84, 255 }, 
		  clrBlueHover { 54, 70, 84, 200 }, clrBlueDormant { 43, 60, 75, 255 }, btnTopActive { }, btnTop { }, btnRegularActive { }, btnRegular { }, btnSpecialActive { }, btnSpecial { }, 
		  btnCombo { }, btnComboActive { }
	{
		szWindowTitle = szDesiredWindowClassTitle;
		SetWindowSize( uDesiredWindowSize[ 0 ], uDesiredWindowSize[ 1 ] );
	}

	void CUserInterface::Shutdown( )
	{
		nk_d3d9_shutdown( );

		if ( bCreatedDevice )
		{
			pDevice->Release( );
			pObjectEx->Release( );
			UnregisterClass( szWindowTitle, wndWindow.hInstance );
		}
	}

	nk_font *CUserInterface::AddFont( std::string strFontFileName, unsigned uFontSize, struct nk_font_config fcFontConfiguration, unsigned uFontAwesomeSize /*= 0*/ )
	{
		static auto strFontDirectory = string_cast< std::string >( GetDirectory( M_DEPENDENCIES ) + M_WXOR( LR"(\Resources\Fonts\)" ) );

		nk_d3d9_font_stash_begin( &pAtlas );
		auto pFont = nk_font_atlas_add_from_file( pAtlas, ( strFontDirectory + strFontFileName ).c_str( ), uFontSize, nullptr );
		nk_font_atlas_add_from_file( pAtlas, ( strFontDirectory + M_XOR( "FontAwesome.ttf" ) ).c_str( ), uFontAwesomeSize ? uFontAwesomeSize : uFontSize, &fcFontConfiguration );
		nk_d3d9_font_stash_end( );
		return pFont;
	}

	void CUserInterface::InitializeNuklear( )
	{
		pContext = nk_d3d9_init( pDevice, uWindowWidth, uWindowHeight );

		//
		// We only need a font configuration for FontAwesome because it needs font merging and a specific glyph range.
		//
		struct nk_font_config fcFontAwesomeConfiguration { };
		static constexpr nk_rune rnIconRange[ ] { ICON_MIN_FA, ICON_MAX_FA, 0 };

		fcFontAwesomeConfiguration = nk_font_config( 16 );
		fcFontAwesomeConfiguration.range = rnIconRange;
		fcFontAwesomeConfiguration.merge_mode = 1;

		pRoboto				= AddFont( M_XOR( "Roboto.ttf"		),	21, fcFontAwesomeConfiguration		);
		pRobotoBold			= AddFont( M_XOR( "RobotoBold.ttf"	),	21, fcFontAwesomeConfiguration		);
		pRobotoSmall		= AddFont( M_XOR( "Roboto.ttf"		),	16, fcFontAwesomeConfiguration, 14	);
		pRobotoBoldSmall	= AddFont( M_XOR( "RobotoBold.ttf"	),	16, fcFontAwesomeConfiguration, 12	);
		pTahoma				= AddFont( M_XOR( "Tahoma.ttf"		),	16, fcFontAwesomeConfiguration		);
		pTahomaBold			= AddFont( M_XOR( "TahomaBold.ttf"	),	16, fcFontAwesomeConfiguration		);
		pEnvy				= AddFont( M_XOR( "Envy.ttf"		),	14, fcFontAwesomeConfiguration		);

		clrColors[ NK_COLOR_TEXT ] = nk_rgba( 255, 255, 255, 255 );
		clrColors[ NK_COLOR_WINDOW ] = nk_rgba( 45, 50, 56, 255 );
		clrColors[ NK_COLOR_HEADER ] = nk_rgba( 45, 50, 56, 255 );
		clrColors[ NK_COLOR_BORDER ] = nk_rgba( 80, 84, 89, 255 );
		clrColors[ NK_COLOR_BUTTON ] = nk_rgba( 48, 83, 111, 255 );
		clrColors[ NK_COLOR_BUTTON_HOVER ] = nk_rgba( 58, 93, 121, 255 );
		clrColors[ NK_COLOR_BUTTON_ACTIVE ] = nk_rgba( 68, 103, 131, 255 );
		clrColors[ NK_COLOR_TOGGLE ] = nk_rgba( 42, 44, 48, 255 );
		clrColors[ NK_COLOR_TOGGLE_HOVER ] = nk_rgba( 42, 44, 48, 255 );
		clrColors[ NK_COLOR_TOGGLE_CURSOR ] = nk_rgba( 48, 83, 111, 255 );
		clrColors[ NK_COLOR_SELECT ] = nk_rgba( 57, 67, 61, 255 );
		clrColors[ NK_COLOR_SELECT_ACTIVE ] = nk_rgba( 48, 83, 111, 255 );
		clrColors[ NK_COLOR_SLIDER ] = nk_rgba( 42, 44, 48, 255 );
		clrColors[ NK_COLOR_SLIDER_CURSOR ] = nk_rgba( 53, 88, 116, 255 );
		clrColors[ NK_COLOR_SLIDER_CURSOR_HOVER ] = nk_rgba( 58, 93, 121, 255 );
		clrColors[ NK_COLOR_SLIDER_CURSOR_ACTIVE ] = nk_rgba( 40, 40, 40, 255 );
		clrColors[ NK_COLOR_PROPERTY ] = nk_rgba( 50, 58, 61, 255 );
		clrColors[ NK_COLOR_EDIT ] = nk_rgba( 50, 58, 61, 225 );
		clrColors[ NK_COLOR_EDIT_CURSOR ] = nk_rgba( 210, 210, 210, 255 );
		clrColors[ NK_COLOR_COMBO ] = nk_rgba( 50, 58, 61, 255 );
		clrColors[ NK_COLOR_CHART ] = nk_rgba( 50, 58, 61, 255 );
		clrColors[ NK_COLOR_CHART_COLOR ] = nk_rgba( 48, 83, 111, 255 );
		clrColors[ NK_COLOR_CHART_COLOR_HIGHLIGHT ] = nk_rgba( 255, 0, 0, 255 );
		clrColors[ NK_COLOR_SCROLLBAR ] = nk_rgba( 48, 83, 111, 255 );
		clrColors[ NK_COLOR_SCROLLBAR_CURSOR ] = nk_rgba( 48, 83, 111, 255 );
		clrColors[ NK_COLOR_SCROLLBAR_CURSOR_HOVER ] = nk_rgba( 58, 93, 121, 255 );
		clrColors[ NK_COLOR_SCROLLBAR_CURSOR_ACTIVE ] = nk_rgba( 68, 103, 131, 255 );
		clrColors[ NK_COLOR_TAB_HEADER ] = nk_rgba( 48, 83, 111, 255 );
		nk_style_from_table( pContext, clrColors );

		pContext->style.window.header.close_symbol = NK_SYMBOL_NONE;
		pContext->style.window.header.close_button.text_active = nk_rgba( 43, 60, 75, 255 );
		pContext->style.window.header.close_button.text_hover = nk_rgba( 43, 60, 75, 255 );
		pContext->style.window.header.close_button.text_normal = nk_rgba( 33, 150, 243, 255 );
		pContext->style.window.rounding = 5.f;
		pContext->style.window.padding = nk_vec2( 0, 10 );
		pContext->style.edit.row_padding = 0;
		pContext->style.button.rounding = 1.f;
		pContext->style.button.border = 1;
		pContext->style.button.border_color = nk_rgba( 80, 84, 89, 255 );

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
		//pContext->style.slider.rounding = 2.f;
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
		btnCombo.text_hover = nk_rgba( 33, 150, 243, 255 );
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
		btnComboActive.text_normal = nk_rgba( 255, 255, 255, 255 );
		btnComboActive.border = 0.f;
		btnComboActive.active.data.color = nk_rgba( 56, 60, 66, 255 );
		btnComboActive.hover.data.color = nk_rgba( 56, 60, 66, 255 );
		btnComboActive.normal.data.color = nk_rgba( 56, 60, 66, 255 );
		btnComboActive.text_alignment = NK_TEXT_LEFT;
		btnComboActive.padding = nk_vec2( 5, 0 );
		btnComboActive.touch_padding = nk_vec2( 5, 5 );
	}

	void CUserInterface::InitializeUserInterface( )
	{
		if ( szWindowTitle )
			CreateRenderTarget( );

		InitializeDirectX( );
		InitializeNuklear( );
	}

	bool CUserInterface::HandleWindowInput( )
	{
		if ( bCreatedDevice )
		{
			static auto bDrag = false;
			RECT recWindowPos { };
			GetWindowRect( hwWindowHandle, &recWindowPos );
			static POINT pntOldCursorPosRelative { };

			if ( GetKeyState( VK_LBUTTON ) == EKeyState::DOWN )
			{
				POINT pntCursorPos { };
				GetCursorPos( &pntCursorPos );
				POINT pntCursorPosRelative { pntCursorPos.x - recWindowPos.left, pntCursorPos.y - recWindowPos.top };

				if ( ( pntCursorPosRelative.x > 0 && pntCursorPosRelative.x <= signed( uWindowWidth ) && pntCursorPosRelative.y > 0 && pntCursorPosRelative.y <= signed( uTitleBarHeight ) ) || bDrag )
				{
					bDrag = true;
					if ( !pntOldCursorPosRelative.x || !pntOldCursorPosRelative.y ) pntOldCursorPosRelative = pntCursorPosRelative;

					SetWindowPos( hwWindowHandle, nullptr, ( recWindowPos.left - pntOldCursorPosRelative.x ) + pntCursorPosRelative.x,
						( recWindowPos.top - pntOldCursorPosRelative.y ) + pntCursorPosRelative.y, uWindowWidth, uWindowHeight, 0 );
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

	void CUserInterface::RenderUserInterface( )
	{
		BeginRender( );
		nk_d3d9_render( NK_ANTI_ALIASING_ON );
		EndRender( );
	}

	bool CUserInterface::HoverCheck( ECursor curSetCursor ) 
	{
		if ( bFoundHoverTarget )
			return false;
		if ( ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) ) )
		{
			bFoundHoverTarget = true;
			curFoundCursorType = curSetCursor;
			return true;
		}
		return false;
	}

	void CUserInterface::ResetHoverState( ) 
	{
		SetActiveCursor( curFoundCursorType );
		curFoundCursorType = ARROW;
		bFoundHoverTarget = false;
		pContext->last_widget_state &= ~( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER );
	}

	bool CUserInterface::DrawUserInterface( )
	{
		bDrawComboboxArrow = false;
		SetFont( EFont::ROBOTO );

		if ( nk_begin( pContext, szNuklearWindowTitle, nk_rect( 0, 0, float( uWindowWidth ), float( uWindowHeight ) ),
					   NK_WINDOW_NO_SCROLLBAR ) && wdg.Header( szNuklearWindowTitle, szApplicationTitle, uWindowWidth ) && HandleWindowInput( ) )
		{
			nk_layout_row_dynamic( pContext, 10, 0 );
			SetFont( EFont::TAHOMA );
			SetLayout( );

			if ( bDrawComboboxArrow )
			{
				auto pOutput = nk_window_get_canvas( ui->pContext );
				nk_stroke_line( pOutput, rcComboboxWindowBounds.x, rcComboboxWindowBounds.y - 2, rcComboboxWindowBounds.x + rcComboboxWindowBounds.w, rcComboboxWindowBounds.y - 2, 2, ui->clrBorder );
				rcComboboxWindowBounds.y -= 3;
				nk_fill_triangle( pOutput, rcComboboxWindowBounds.x + rcComboboxWindowBounds.w - 3, rcComboboxWindowBounds.y, rcComboboxWindowBounds.x + rcComboboxWindowBounds.w - 10, rcComboboxWindowBounds.y - 7, rcComboboxWindowBounds.x + rcComboboxWindowBounds.w - 17, rcComboboxWindowBounds.y, ui->clrBackground );
			}
		}
		else
			bShouldDrawInterface = false;
		nk_end( pContext );

		RenderUserInterface( );
		ResetHoverState( );

		return bShouldDrawInterface;
	}

	void CUserInterface::SetFont( EFont fntFont )
	{
		switch ( fntFont )
		{
			case EFont::TAHOMA:
				nk_style_set_font( pContext, &pTahoma->handle );
				break;
			case EFont::TAHOMABOLD:
				nk_style_set_font( pContext, &pTahomaBold->handle );
				break;
			case EFont::ROBOTO:
				nk_style_set_font( pContext, &pRoboto->handle );
				break;
			case EFont::ROBOTOBOLD:
				nk_style_set_font( pContext, &pRobotoBold->handle );
				break;
			case EFont::ROBOTOSMALL:
				nk_style_set_font( pContext, &pRobotoSmall->handle );
				break;
			case EFont::ROBOTOBOLDSMALL:
				nk_style_set_font( pContext, &pRobotoBoldSmall->handle );
				break;
			case EFont::ENVY:
				nk_style_set_font( pContext, &pEnvy->handle );
				break;
			default:
				nk_style_set_font( pContext, &pTahoma->handle );
		}
	}

	struct nk_vec2 CUserInterface::GetTextSize( const char *szText, unsigned uRowHeight /*= 30*/ )
	{
		return nk_text_calculate_text_bounds( pContext->style.font, szText, strlen( szText ), uRowHeight, new const char *, new struct nk_vec2, new int, 0 );
	}

	bool CUserInterface::CWidgets::Header( const char *szTitle, const char *szApplicationTitle, unsigned uWidth )
	{	
		nk_layout_row_dynamic( ui->pContext, 30, 0 );
		auto pOutput = nk_window_get_canvas( ui->pContext );
		auto pInput = &ui->pContext->input;

		struct nk_text txtTitle, txtApplication, txtCloseButton;
		txtCloseButton.padding = txtApplication.padding = txtTitle.padding = ui->pContext->style.text.padding;
		txtTitle.text = ui->clrTextActive;
		txtApplication.text = ui->clrTextDormant;

		nk_fill_rect( pOutput, nk_rect( 0, 0, uWidth, 102 ), 0.f, ui->clrHeader );
		nk_stroke_line( pOutput, 0, 40, uWidth, 40, 1, ui->clrColors[ NK_COLOR_BORDER ] );

		ui->SetFont( EFont::ROBOTOBOLD );
		nk_widget_text( pOutput, nk_rect( 12, 7, 150, 30 ), szTitle, strlen( szTitle ), &txtTitle, NK_TEXT_CENTERED, ui->pContext->style.font );
		ui->SetFont( EFont::ROBOTO );
		nk_widget_text( pOutput, nk_rect( 122, 7, 150, 30 ), szApplicationTitle, strlen( szApplicationTitle ), &txtApplication, NK_TEXT_CENTERED, ui->pContext->style.font );

		static auto clrIconColor = nk_rgba( 33, 150, 243, 255 );
		txtCloseButton.text = clrIconColor;
		const static struct nk_rect rcCloseButton = { ui->uWindowWidth - 33, 13, 20, 20 };
		nk_widget_text( pOutput, rcCloseButton, ICON_FA_TIMES, strlen( ICON_FA_TIMES ), &txtCloseButton, NK_TEXT_CENTERED, ui->pContext->style.font );

		const auto iHoveringPanel = nk_input_is_mouse_hovering_rect( &ui->pContext->input, rcCloseButton );
		if( iHoveringPanel ) 
		{
			clrIconColor = nk_rgba( 115, 189, 247, 255 );
			if ( ui->GetKeyState( VK_LBUTTON ) == EKeyState::DOWN )
				return false;
			ui->pContext->last_widget_state |= NK_WIDGET_STATE_ACTIVE;
			ui->pContext->last_widget_state |= NK_WIDGET_STATE_HOVER;
			ui->bFoundHoverTarget = true;
			ui->curFoundCursorType = HAND;
			ui->SetActiveCursor( HAND );
		}
		else
			clrIconColor = nk_rgba( 33, 150, 243, 255 );

		return true;
	}

	void CUserInterface::CWidgets::Separator( unsigned char bRed, unsigned char bGreen, unsigned char bBlue, unsigned uStartHeight, unsigned uRowSize /*= 3*/, bool bUpperBorder /*= false*/ )
	{
		constexpr auto uSeparatorHeight = 420u / 10u;
		constexpr struct nk_color clrBorderColor = { 85, 88, 94, 255 };
		auto pOutput = nk_window_get_canvas( ui->pContext );
		nk_fill_rect( pOutput, nk_rect( 0, uStartHeight, ui->uWindowWidth, uSeparatorHeight ), 0.f, nk_rgba( bRed, bGreen, bBlue, 255 ) );
		nk_stroke_line( pOutput, 0, uStartHeight + uSeparatorHeight - 1, ui->uWindowWidth, uStartHeight + uSeparatorHeight - 1, 0.5, clrBorderColor );

		if( bUpperBorder )
			nk_stroke_line( pOutput, 0, uStartHeight + 1, ui->uWindowWidth, uStartHeight + 1, 0.5, clrBorderColor );
	}

	bool CUserInterface::CWidgets::TopButton( const char *szText, bool bActive )
	{
		return nk_button_label_styled( ui->pContext, bActive ? &ui->btnTopActive : &ui->btnTop, szText );
	}

	bool CUserInterface::CWidgets::RegularButton( const char *szText, bool bActive )
	{
		if ( bActive )
		{
			auto rcBoundaries = nk_widget_bounds( ui->pContext );
			auto pOutput = nk_window_get_canvas( ui->pContext );
			nk_fill_rect_multi_color( pOutput, rcBoundaries, ui->clrBorder, ui->clrDarkBackground, ui->clrDarkBackground, ui->clrBorder );

			rcBoundaries.w += rcBoundaries.x;
			rcBoundaries.h += rcBoundaries.y;
			ui->SetFont( EFont::TAHOMABOLD );
			const auto bResult = nk_button_label_styled( ui->pContext, &ui->btnRegularActive, szText );
			ui->HoverCheck( HAND );
			ui->SetFont( EFont::TAHOMA );
			nk_stroke_line( pOutput, rcBoundaries.x + 2, rcBoundaries.y, rcBoundaries.x + 2, rcBoundaries.h, 2, ui->clrBlue );
			return bResult;
		}
		ui->SetFont( EFont::TAHOMA );
		const auto bReturn = nk_button_label_styled( ui->pContext, &ui->btnRegular, szText );
		ui->HoverCheck( HAND );
		return bReturn;
	}

	bool CUserInterface::CWidgets::SpecialButton( EPosition pPosition, const char *szText, bool bActive )
	{
		ui->SetFont( EFont::ROBOTOBOLDSMALL );

		const auto rcBoundaries = nk_widget_bounds( ui->pContext );
		const auto pOutput = nk_window_get_canvas( ui->pContext );
		auto bHover = false;
		nk_flags fOldFlags = 0;
		if ( !ui->bFoundHoverTarget )
		{
			fOldFlags = ui->pContext->last_widget_state;
			ui->pContext->last_widget_state = 0;
		}
		const auto bReturn = nk_button_label_styled( ui->pContext, bActive ? &ui->btnSpecialActive : &ui->btnSpecial, szText );
		if( !ui->bFoundHoverTarget )
		{
			bHover = ui->HoverCheck( HAND );
			ui->pContext->last_widget_state = fOldFlags;
			ui->HoverCheck( HAND );
		}
		nk_color clrCurrentColor;
		if ( bHover )
		{
			if ( !bActive )
				clrCurrentColor = ui->clrBlueHover;
		}
		else
			clrCurrentColor = ui->clrBlueDormant;
		if ( bActive )
			clrCurrentColor = ui->clrBlueActive;
		
		switch (pPosition ) 
		{
			case EPosition::LEFT:
			{
				nk_fill_rect( pOutput, nk_rect( rcBoundaries.x + rcBoundaries.w - 5, rcBoundaries.y, 5, rcBoundaries.h ), 0.f, clrCurrentColor );
				break;
			}
			case EPosition::CENTER:
			{
				nk_fill_rect( pOutput, nk_rect( rcBoundaries.x + rcBoundaries.w - 5, rcBoundaries.y, 5, rcBoundaries.h ), 0.f, clrCurrentColor );
				nk_fill_rect( pOutput, nk_rect( rcBoundaries.x, rcBoundaries.y, 5, rcBoundaries.h ), 0.f, clrCurrentColor );
				break;
			}
			case EPosition::RIGHT:
			{
				nk_fill_rect( pOutput, nk_rect( rcBoundaries.x, rcBoundaries.y, 5, rcBoundaries.h ), 0.f, clrCurrentColor );
				break;
			}
			default:
				return false;
		}
		return bReturn;
	}

	void CUserInterface::CWidgets::Checkbox( const char *szText, bool *bActive ) 
	{
		static auto bWasClicking = false;

		nk_layout_row_push( ui->pContext, 25 );
		const auto rcBoundaries = nk_widget_bounds( ui->pContext );
		const auto bHovering = nk_input_is_mouse_hovering_rect( &ui->pContext->input, rcBoundaries );
		const auto bClicking = ui->GetKeyState( VK_LBUTTON ) == EKeyState::DOWN;

		if ( bHovering )
			ui->SetActiveCursor( HAND );

		if ( bClicking && bHovering )
		{
			if ( !bWasClicking )
				*bActive = !*bActive;
			bWasClicking = true;
		}
		else if( !bClicking )
			bWasClicking = false;

		nk_label_colored( ui->pContext, *bActive ? ICON_FA_CHECK_SQUARE : ICON_FA_SQUARE, NK_TEXT_CENTERED, *bActive ? ui->clrBlue : bHovering ? ( bClicking ? ui->clrBlue : ui->clrBlue ) : ui->clrTextDormant );
		nk_layout_row_push( ui->pContext, ui->GetTextSize( szText, 15 ).x );
		nk_label_colored( ui->pContext, ( szText + std::string( "  " ) ).c_str( ), NK_TEXT_LEFT, ui->clrTextDormant );
	}

	int CUserInterface::CWidgets::Tabs( unsigned uStartX, unsigned uStartY, unsigned uButtonWidth, unsigned uButtonHeight, std::deque< const char * > dqButtons, unsigned uActiveButton ) 
	{
		ui->SetFont( EFont::ROBOTOBOLDSMALL );
		BeginCustomRow( uButtonHeight, dqButtons.size( ) );
		auto iPressedButton = -1;
		for( unsigned i { }; i < dqButtons.size( ); i++ ) 
		{
			PushCustomRow( uStartX + ( uButtonWidth * i ), uStartY, uButtonWidth, uButtonHeight );
			if ( TopButton( dqButtons.at( i ), i == uActiveButton ) )
				iPressedButton = i;
		}
		return iPressedButton;
	}

	int CUserInterface::CWidgets::Sidebar( unsigned uButtonHeight, unsigned uButtonWidth, unsigned uStartX, unsigned uStartY, std::deque< const char * > dqButtons, unsigned uSelectedButton )
	{
		nk_layout_space_begin( ui->pContext, NK_STATIC, uButtonHeight * dqButtons.size( ), dqButtons.size( ) );
		auto iButtonPressed = -1;
		for( unsigned i { }; i < dqButtons.size( ); i++ )
		{
			nk_layout_space_push( ui->pContext, nk_rect( uStartX, uStartY + ( uButtonHeight * i ), uButtonWidth, uButtonHeight ) );
			if ( RegularButton( dqButtons.at( i ), i == uSelectedButton ) )
				iButtonPressed = i;
		}
		nk_layout_space_end( ui->pContext );
		return iButtonPressed;
	}

	void CUserInterface::CWidgets::BeginGroupbox( unsigned uBoxWidth, unsigned uBoxHeight, unsigned uStartX, unsigned uStartY, const char *szTitle, unsigned uTextWidth )
	{
		ui->SetFont( EFont::TAHOMA );
		nk_layout_space_begin( ui->pContext, NK_STATIC, uBoxHeight, 1 );
		const auto rcBoundaries = nk_widget_bounds( ui->pContext );
		nk_layout_space_push( ui->pContext, nk_rect( uStartX - rcBoundaries.x, uStartY - rcBoundaries.y, uBoxWidth, uBoxHeight ) );
		auto rcNewBoundaries = nk_widget_bounds( ui->pContext );
		nk_group_begin( ui->pContext, szTitle, NK_WINDOW_NO_SCROLLBAR );

		const auto pOutput = nk_window_get_canvas( ui->pContext );
		rcNewBoundaries.x += 4;
		rcNewBoundaries.y += 20;
		rcNewBoundaries.w -= 8;
		rcNewBoundaries.h -= 28;
		// Top left, top right, bottom right, bottom left
		nk_fill_rect_multi_color( pOutput, nk_rect( rcNewBoundaries.x + 1.8, rcNewBoundaries.y + 1, rcNewBoundaries.w - 2, rcNewBoundaries.h - 2 ), ui->clrDarkBackground, ui->clrDarkBackground, ui->clrBackground, ui->clrBackground );
		nk_stroke_rect( pOutput, rcNewBoundaries, 4.f, 1.f, ui->clrBorder );
		nk_stroke_line( pOutput, rcNewBoundaries.x + 7, rcNewBoundaries.y, rcNewBoundaries.x + 3 + uTextWidth, rcNewBoundaries.y, 3, ui->clrDarkBackground );
		BeginCustomRow( 16, 1 );
		auto rcText = nk_widget_bounds( ui->pContext );
		PushCustomRow( rcNewBoundaries.x + 8 - rcText.x, rcNewBoundaries.y - rcText.y - 10, uTextWidth, 16 );
		nk_label( ui->pContext, szTitle, NK_TEXT_LEFT );
		NewRow( 5, 0 );

		ui->SetFont( EFont::ROBOTOSMALL );
	}

	void CUserInterface::CWidgets::EndGroupbox( )
	{
		nk_group_end( ui->pContext );
	}

	void CUserInterface::CWidgets::ColorButton( const char *szSubject, px_color_t *pColor ) 
	{
		if ( nk_button_color( ui->pContext, nk_rgba( ( *pColor )[ 0 ], ( *pColor )[ 1 ], ( *pColor )[ 2 ], ( *pColor )[ 3 ] ) ) && pActiveEditColor == nullptr )
		{
			szColorPickerSubject = szSubject;
			pActiveEditColor = pColor;
		}
		ui->HoverCheck( HAND );
	}

	void CUserInterface::CWidgets::ColorPicker( )
	{
		constexpr struct nk_vec2 vecColorPickerSize { 305, 375 };
		const static struct nk_rect rcColorPickerBoundaries { ( ui->uWindowWidth / 2 ) - ( vecColorPickerSize.x / 2 ), ( ui->uWindowHeight / 2 ) - ( vecColorPickerSize.y / 2 ), vecColorPickerSize.x, vecColorPickerSize.y };
		const static std::string strBaseTitle = R"(Color of ')";

		static struct nk_colorf clrChosenColor;
		static auto bNewColor = true;
		static auto bShouldClose = false;
		static auto bStoppedClicking = false;

		if ( ui->GetKeyState( VK_LBUTTON ) == EKeyState::UP )
			bStoppedClicking = true;
		if ( bNewColor && pActiveEditColor )
			clrChosenColor = { ( *pActiveEditColor )[ 0.f ] / 255.f, ( *pActiveEditColor )[ 1.f ] / 255.f, ( *pActiveEditColor )[ 2.f ] / 255.f, ( *pActiveEditColor )[ 3.f ] / 255.f };
		bNewColor = false;

		const auto pOutput = nk_window_get_canvas( ui->pContext );
		nk_fill_rect( pOutput, nk_rect( 0, 0, ui->uWindowWidth, ui->uWindowHeight ), 0, nk_rgba( 0, 0, 0, 180 ) );

		if( bShouldClose )
		{
			bShouldClose = false;
			pActiveEditColor = nullptr;
		}

		if ( nk_popup_begin( ui->pContext, NK_POPUP_DYNAMIC, ( strBaseTitle + szColorPickerSubject + R"(')" ).c_str( ), NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_NO_SCROLLBAR,
							 rcColorPickerBoundaries, pActiveEditColor == nullptr ) )
		{
			nk_layout_row_static( ui->pContext, 255, 295, 1 );
			clrChosenColor = nk_color_picker( ui->pContext, clrChosenColor, NK_RGBA );
			nk_layout_row_dynamic( ui->pContext, 5, 0 );
			nk_layout_row_dynamic( ui->pContext, 16, 4 );
			nk_label( ui->pContext, ( "R: " + std::to_string( int( clrChosenColor.r * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
			nk_label( ui->pContext, ( "G: " + std::to_string( int( clrChosenColor.g * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
			nk_label( ui->pContext, ( "B: " + std::to_string( int( clrChosenColor.b * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
			nk_label( ui->pContext, ( "A: " + std::to_string( int( clrChosenColor.a * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
			nk_layout_row_dynamic( ui->pContext, 10, 1 );
			nk_button_color( ui->pContext, nk_rgba( clrChosenColor.r * 255.f, clrChosenColor.g * 255.f, clrChosenColor.b * 255.f, clrChosenColor.a * 255.f ) );
			nk_layout_row_static( ui->pContext, 25, vecColorPickerSize.x / 2 - 10, 2 );
			if ( SpecialButton( EPosition::LEFT, "CANCEL", false ) )
			{
				bShouldClose = true;
				bNewColor = true;
			}
			if ( SpecialButton( EPosition::RIGHT, "CONFIRM", false ) )
			{
				*pActiveEditColor = px_color_t( { clrChosenColor.r, clrChosenColor.g, clrChosenColor.b, clrChosenColor.a } );
				bNewColor = true;
				bShouldClose = true;
			}
			if ( !nk_input_is_mouse_prev_hovering_rect( &ui->pContext->input, rcColorPickerBoundaries ) && ( ui->GetKeyState( VK_LBUTTON ) == EKeyState::DOWN ) && bStoppedClicking )
			{
				bShouldClose = true;
				bNewColor = true;
			}
			nk_layout_row_dynamic( ui->pContext, 10, 0 );
			nk_popup_end( ui->pContext );
			return;
		}
		bNewColor = true;
		bStoppedClicking = false;
	}

	int CUserInterface::CWidgets::Combobox( unsigned uWidth, unsigned uHeight, const char *szTitle, std::deque< const char * > dqOptions, unsigned uSelectedOption )
	{
		auto iSelectedOption = -1;
		bool bDrewCombo = false;
		ui->SetFont( EFont::TAHOMA );
		auto rcComboBounds = nk_widget_bounds( ui->pContext );

		dbg::Assert( rcComboBounds.w == uWidth );

		const auto pOutput = nk_window_get_canvas( ui->pContext );
		if ( nk_combo_begin_label( ui->pContext, szTitle, nk_vec2( uWidth, uHeight * dqOptions.size( ) + 5 * ( dqOptions.size( ) - 1 ) - 3 ) ) )
		{
			ui->bDrawComboboxArrow = true;
			ui->rcComboboxWindowBounds = ui->pContext->current->bounds;
			for ( unsigned i { }; i < dqOptions.size( ); i++ )
			{
				if ( i == uSelectedOption )
					ui->pContext->style.contextual_button = ui->btnComboActive;
				else
					ui->pContext->style.contextual_button = ui->btnCombo;

				nk_layout_row_dynamic( ui->pContext, uHeight, 1 );
				if ( nk_combo_item_label( ui->pContext, dqOptions.at( i ), NK_TEXT_LEFT ) )
					iSelectedOption = i;
			}
			nk_combo_end( ui->pContext );
			bDrewCombo = true;
		}
		nk_fill_triangle( pOutput, rcComboBounds.x + rcComboBounds.w - 10, rcComboBounds.y + ( rcComboBounds.h / 2 ) - 3, rcComboBounds.x + rcComboBounds.w - 14, rcComboBounds.y + ( rcComboBounds.h / 2 ) + 3, rcComboBounds.x + rcComboBounds.w - 18, rcComboBounds.y + ( rcComboBounds.h / 2 ) - 3, nk_input_is_mouse_prev_hovering_rect( &ui->pContext->input, rcComboBounds ) && !bDrewCombo ? ui->clrTextActive : ui->clrTextDormant );
		return iSelectedOption;
	}

	void CUserInterface::CWidgets::ComboboxToggle( unsigned uWidth, unsigned uHeight, const char *szTitle, std::deque< const char * > dqOptions, std::deque< bool > &dqEnabledOptions )
	{
		bool bDrewCombo = false;
		ui->SetFont( EFont::TAHOMA );
		auto rcComboBounds = nk_widget_bounds( ui->pContext );

		dbg::Assert( rcComboBounds.w == uWidth );

		const auto pOutput = nk_window_get_canvas( ui->pContext );
		if ( nk_combo_begin_label( ui->pContext, szTitle, nk_vec2( uWidth, uHeight * dqOptions.size( ) + 5 * ( dqOptions.size( ) - 1 ) - 3 ) ) )
		{
			ui->bDrawComboboxArrow = true;
			ui->rcComboboxWindowBounds = ui->pContext->current->bounds;
			for ( unsigned i { }; i < dqOptions.size( ); i++ )
			{
				nk_layout_row_dynamic( ui->pContext, uHeight, 1 );
				if ( nk_button_label_styled( ui->pContext, dqEnabledOptions.at( i ) ? &ui->btnComboActive : &ui->btnCombo, dqOptions.at( i ) ) )
					dqEnabledOptions.at( i ) = !dqEnabledOptions.at( i );
			}
			nk_combo_end( ui->pContext );
			bDrewCombo = true;
		}
		nk_fill_triangle( pOutput, rcComboBounds.x + rcComboBounds.w - 10, rcComboBounds.y + ( rcComboBounds.h / 2 ) - 3, rcComboBounds.x + rcComboBounds.w - 14, rcComboBounds.y + ( rcComboBounds.h / 2 ) + 3, rcComboBounds.x + rcComboBounds.w - 18, rcComboBounds.y + ( rcComboBounds.h / 2 ) - 3, nk_input_is_mouse_prev_hovering_rect( &ui->pContext->input, rcComboBounds ) && !bDrewCombo ? ui->clrTextActive : ui->clrTextDormant );
	}

	void CUserInterface::CWidgets::NewRow( unsigned uHeight /*= 30*/, unsigned uColumns /*= 3*/ )
	{
		rwLastRowType = ERowType::DYNAMIC;
		return nk_layout_row_dynamic( ui->pContext, uHeight, uColumns );
	}

	void CUserInterface::CWidgets::BeginRow( unsigned uHeight /*= 30*/, unsigned uColumns /*= 6*/ ) 
	{
		rwLastRowType = ERowType::MANUAL;
		return nk_layout_row_begin( ui->pContext, NK_STATIC, uHeight, uColumns );
	}

	void CUserInterface::CWidgets::SetRowWidth( float flWidth ) 
	{
		dbg::Assert( rwLastRowType == ERowType::MANUAL );
		return nk_layout_row_push( ui->pContext, flWidth );
	}

	void CUserInterface::CWidgets::EndRow( ) 
	{
		dbg::Assert( rwLastRowType == ERowType::MANUAL );
		bBeganRow = false;
		return nk_layout_row_end( ui->pContext );
	}

	void CUserInterface::CWidgets::NewStaticRow( unsigned uWidth, unsigned uHeight /*= 30*/, unsigned uColumns /*= 3*/ )
	{
		rwLastRowType = ERowType::STATIC;
		return nk_layout_row_static( ui->pContext, uHeight, uWidth, uColumns );
	}

	void CUserInterface::CWidgets::BeginCustomRow( unsigned uHeight /*= 30*/, unsigned uWidgetCount /*= 3*/ ) 
	{
		rwLastRowType = ERowType::CUSTOM;
		return nk_layout_space_begin( ui->pContext, NK_STATIC, uHeight, uWidgetCount );
	}

	void CUserInterface::CWidgets::EndCustomRow( )
	{
		return nk_layout_space_end( ui->pContext );
	}

	void CUserInterface::CWidgets::PushCustomRow( unsigned uXModification, unsigned uYModification, unsigned uWidth, unsigned uHeight ) 
	{
		dbg::Assert( rwLastRowType == ERowType::CUSTOM );
		return nk_layout_space_push( ui->pContext, nk_rect( uXModification, uYModification, uWidth, uHeight ) );
	}

	void CUserInterface::CWidgets::BeginPaddedRow( unsigned uPadding, unsigned uWidth, unsigned uHeight /*= 30*/, unsigned uColumns /*= 3*/ )
	{
		rwLastRowType = ERowType::CUSTOM;
		BeginRow( uHeight, uColumns + 1u );
		SetRowWidth( uPadding );
		Spacing( );
		return SetRowWidth( uWidth );
	}

	void CUserInterface::CWidgets::Spacing( unsigned uColumns /*= 1*/ ) 
	{
		return nk_spacing( ui->pContext, uColumns );
	}

	void CUserInterface::CWidgets::VerticalSpacing( unsigned uPixels /*= 5*/ )
	{ 
		return nk_layout_row_dynamic( ui->pContext, uPixels, 0 );
	}
}
