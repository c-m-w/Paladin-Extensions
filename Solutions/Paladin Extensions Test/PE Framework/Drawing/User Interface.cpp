/// User Interface.cpp

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_IMPLEMENTATION
#define NK_D3D9_IMPLEMENTATION

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
		: pContext { }, pAtlas { }, pTahoma { }, pTahomaBold { }, pRoboto { }, pRobotoBold { }, pRobotoSmall { }, pRobotoBoldSmall { }, szNuklearWindowTitle { szDesiredNuklearWindowTitle }, 
		  szApplicationTitle { szDesiredApplicationName }, bFoundHoverTarget { }, clrColors { }, clrTextDormant { }, clrTextActive { }, btnTopActive { }, btnTop { }, btnRegularActive	{ }, 
		  btnRegular { }, btnSpecialActive { }, btnSpecial { }
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

		pRoboto				= AddFont( M_XOR( "Roboto.ttf" ), 21, fcFontAwesomeConfiguration );
		pRobotoBold			= AddFont( M_XOR( "RobotoBold.ttf" ), 21, fcFontAwesomeConfiguration );
		pRobotoSmall		= AddFont( M_XOR( "Roboto.ttf" ), 16, fcFontAwesomeConfiguration, 12 );
		pRobotoBoldSmall	= AddFont( M_XOR( "RobotoBold.ttf" ), 16, fcFontAwesomeConfiguration, 12 );
		pTahoma				= AddFont( M_XOR( "Tahoma.ttf" ), 16, fcFontAwesomeConfiguration );
		pTahomaBold			= AddFont( M_XOR( "TahomaBold.ttf" ), 16, fcFontAwesomeConfiguration );

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
		pContext->style.window.padding = nk_vec2( 0, 8 );
		pContext->style.edit.row_padding = 0;

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
		btnTop.hover.data.color = nk_rgba( 56, 60, 66, 255 );
		btnTop.normal.data.color = nk_rgba( 45, 50, 56, 255 );
		btnTop.text_active = nk_rgba( 175, 180, 187, 255 );
		btnTop.text_hover = nk_rgba( 175, 180, 187, 255 );
		btnTop.text_normal = nk_rgba( 175, 180, 187, 255 );
		btnTop.text_alignment = NK_TEXT_CENTERED;

		btnRegularActive.rounding = 0;
		btnRegularActive.padding = nk_vec2( 12, 0 );
		btnRegularActive.active.data.color = nk_rgba( 61, 65, 72, 255 );
		btnRegularActive.hover.data.color = nk_rgba( 61, 65, 72, 255 );
		btnRegularActive.normal.data.color = nk_rgba( 61, 65, 72, 255 );
		btnRegularActive.text_active = nk_rgba( 33, 150, 243, 255 );
		btnRegularActive.text_hover = nk_rgba( 255, 255, 255, 255 );
		btnRegularActive.text_normal = nk_rgba( 33, 150, 243, 255 );
		btnRegularActive.text_alignment = NK_TEXT_LEFT;

		btnRegular.rounding = 0;
		btnRegular.padding = nk_vec2( 10, 0 );
		btnRegular.active.data.color = nk_rgba( 61, 65, 72, 255 );
		btnRegular.hover.data.color = nk_rgba( 56, 60, 66, 255 );
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
		btnSpecial.hover.data.color = nk_rgba( 54, 70, 84, 200 );
		btnSpecial.normal.data.color = nk_rgba( 43, 60, 75, 255 );
		btnSpecial.text_active = nk_rgba( 33, 150, 243, 255 );
		btnSpecial.text_hover = nk_rgba( 33, 150, 243, 255 );
		btnSpecial.text_normal = nk_rgba( 33, 150, 243, 255 );
		btnSpecial.text_alignment = NK_TEXT_CENTERED;

		clrTextActive = nk_rgba( 255, 255, 255, 255 );
		clrTextDormant = nk_rgba( 175, 180, 187, 255 );
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
		SetFont( EFont::ROBOTO );

		if ( nk_begin( pContext, szNuklearWindowTitle, nk_rect( 0, 0, float( uWindowWidth ), float( uWindowHeight ) ),
					   NK_WINDOW_NO_SCROLLBAR ) && wdg.Header( szNuklearWindowTitle, szApplicationTitle, uWindowWidth ) && HandleWindowInput( ) )
		{
			nk_layout_row_dynamic( pContext, 10, 0 );
			SetFont( EFont::TAHOMA );
			SetLayout( );

			//pContext->current->bounds = nk_rect( 210, 60, 390, 130 );
			//pContext->style.window.fixed_background.data.color = nk_rgba( 61, 65, 72, 255 );
			//nk_panel_begin( pContext, szNuklearWindowTitle, NK_PANEL_POP );
			//nk_panel_end( pContext );
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
			default:
				nk_style_set_font( pContext, &pTahoma->handle );
		}
	}

	void CUserInterface::CWidgets::urmom( ) 
	{
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

		nk_fill_rect( pOutput, nk_rect( 0, 0, uWidth, 40 ), 0.f, ui->clrColors[ NK_COLOR_HEADER ] );
		nk_stroke_line( pOutput, 0, 40, uWidth, 40, 1, ui->clrColors[ NK_COLOR_BORDER ] );

		ui->SetFont( EFont::ROBOTOBOLD );
		nk_widget_text( pOutput, nk_rect( 12, 7, 150, 30 ), szTitle, strlen( szTitle ), &txtTitle, NK_TEXT_CENTERED, ui->pContext->style.font );
		ui->SetFont( EFont::ROBOTO );
		nk_widget_text( pOutput, nk_rect( 122, 7, 150, 30 ), szApplicationTitle, strlen( szApplicationTitle ), &txtApplication, NK_TEXT_CENTERED, ui->pContext->style.font );

		static auto clrIconColor = nk_rgba( 33, 150, 243, 255 );
		txtCloseButton.text = clrIconColor;
		constexpr struct nk_rect rcCloseButton = { 567, 13, 20, 20 };
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
			constexpr nk_color clrBlueLine { 33, 150, 243, 255 };
			auto rcBoundaries = nk_widget_bounds( ui->pContext );
			rcBoundaries.w += rcBoundaries.x;
			rcBoundaries.h += rcBoundaries.y;

			auto pOutput = nk_window_get_canvas( ui->pContext );

			ui->SetFont( EFont::TAHOMABOLD );
			const auto bResult = nk_button_label_styled( ui->pContext, &ui->btnRegularActive, szText );
			ui->SetFont( EFont::TAHOMA );
			nk_stroke_line( pOutput, rcBoundaries.x + 2, rcBoundaries.y, rcBoundaries.x + 2, rcBoundaries.h, 2, clrBlueLine );
			return bResult;
		}
		const auto bReturn = nk_button_label_styled( ui->pContext, &ui->btnRegular, szText );
		ui->HoverCheck( HAND );
		return bReturn;
	}

	bool CUserInterface::CWidgets::SpecialButton( EPosition pPosition, const char *szText, bool bActive )
	{
		ui->SetFont( EFont::ROBOTOBOLDSMALL );

		constexpr struct nk_color clrActiveColor = { 54, 70, 84, 255 };
		constexpr struct nk_color clrHoverColor = { 54, 70, 84, 200 };
		constexpr struct nk_color clrDormantColor = { 43, 60, 75, 255 };

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
				clrCurrentColor = clrHoverColor;
		}
		else
			clrCurrentColor = clrDormantColor;
		if ( bActive )
			clrCurrentColor = clrActiveColor;

		//ui->pContext->last_widget_state = fOldFlags;
		
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
		constexpr struct nk_color clrDormant { 175, 180, 187, 255 }, clrHover { 33, 150, 243, 200 }, clrActive { 33, 150, 243, 255 };
		static auto bWasClicking = false;

		nk_layout_row_push( ui->pContext, 15 );
		const auto rcBoundaries = nk_widget_bounds( ui->pContext );
		const auto bHovering = nk_input_is_mouse_hovering_rect( &ui->pContext->input, rcBoundaries );
		const auto bClicking = ui->GetKeyState( VK_LBUTTON ) == EKeyState::DOWN;

		if ( bClicking && bHovering )
		{
			if ( !bWasClicking )
				*bActive = !*bActive;
			bWasClicking = true;
		}
		else if( !bClicking )
			bWasClicking = false;

		nk_label_colored( ui->pContext, *bActive ? ICON_FA_CHECK_SQUARE : ICON_FA_SQUARE, NK_TEXT_CENTERED, *bActive ? clrActive : bHovering ? ( bClicking ? clrActive : clrHover ) : clrDormant );
		nk_layout_row_push( ui->pContext, 40 );
		nk_label_colored( ui->pContext, ( szText + std::string( "  " ) ).c_str( ), NK_TEXT_LEFT, nk_rgba( 175, 180, 187, 255 ) );
	}

	void CUserInterface::CWidgets::NewRow( unsigned uHeight /*= 30*/, unsigned uColumns /*= 3*/ )
	{
		return nk_layout_row_dynamic( ui->pContext, uHeight, uColumns );
	}

	void CUserInterface::CWidgets::BeginRow( unsigned uHeight /*= 30*/, unsigned uColumns /*= 6*/ ) 
	{
		if ( bBeganRow )
			nk_layout_row_end( ui->pContext );
		bBeganRow = true;
		return nk_layout_row_begin( ui->pContext, NK_STATIC, uHeight, uColumns );
	}

	void CUserInterface::CWidgets::EndRow( ) 
	{
		bBeganRow = false;
		return nk_layout_row_end( ui->pContext );
	}

	void CUserInterface::CWidgets::NewStaticRow( unsigned uWidth, unsigned uHeight /*= 30*/, unsigned uColumns /*= 3*/ )
	{
		return nk_layout_row_static( ui->pContext, uHeight, uWidth, uColumns );
	}
}
