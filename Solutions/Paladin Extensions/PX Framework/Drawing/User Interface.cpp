/// User Interface.cpp

#define PX_NUKLEAR_IMPLEMENTATION

#include "../PX Framework.hpp"

namespace PX::UI
{
	using namespace Render;

	namespace Manager
	{
		Types::cstr_t	szWindowTitle = PX_XOR( "Paladin Extensions" );
		auto			szApplicationTitle = static_cast< char* >( malloc( 32 ) );

		nk_font_atlas* pAtlas;
		struct nk_font *pTahoma, *pTahomaBold, *pRoboto, *pRobotoBold, *pRobotoSmall, *pRobotoBoldSmall, *pEnvy;
		struct nk_rect recComboboxWindowBounds;
		bool bDrawComboboxArrow = false;

		constexpr nk_color clrTextActive { 255, 255, 255, 255 }, clrBlue { 33, 150, 243, 255 }, clrDarkBlue { 43, 60, 75, 255 }, clrBackground { 56, 60, 66, 255 }, clrLightBackground { 61, 65, 72, 255 },
		                   clrDarkBackground { 45, 50, 56, 255 }, clrBorder { 80, 84, 89, 255 }, clrToolbox { 42, 44, 48, 255 }, clrHeader { 33, 36, 40, 255 }, clrBlueActive { 54, 70, 84, 255 },
		                   clrBlueHover { 54, 70, 84, 200 }, clrBlueDormant { 43, 60, 75, 255 }, clrTextDormant { 175, 180, 187, 255 };
		nk_color clrColorTable[ NK_COLOR_COUNT ] { };

		nk_style_button btnTopActive { }, btnTop { }, btnRegularActive { }, btnRegular { }, btnSpecialActive { }, btnSpecial { }, btnCombo { }, btnComboActive { };

		ECursor curCurrent;

		bool bFoundHoverTarget = false;

		nk_font* PX_API AddFont( std::string strFontFileName, unsigned uFontSize, struct nk_font_config fcFontConfiguration, unsigned uFontAwesomeSize = 0 )
		{
			static std::string strFontDirectory( R"(C:\Windows\Fonts\)" );

			nk_d3d9_font_stash_begin( &pAtlas );
			auto pFont = nk_font_atlas_add_from_file( pAtlas, ( strFontDirectory + strFontFileName ).c_str( ), float( uFontSize ), nullptr );
			nk_font_atlas_add_from_file( pAtlas, ( strFontDirectory + PX_XOR( "FontAwesome.ttf" ) ).c_str( ), uFontAwesomeSize ? float( uFontAwesomeSize ) : float( uFontSize ), &fcFontConfiguration );
			nk_d3d9_font_stash_end( );
			return pFont;
		}

		void PX_API InitializeNuklear( )
		{
			pContext = nk_d3d9_init( pDevice, uWindowWidth, uWindowHeight );

			//
			// We only need a font configuration for FontAwesome because it needs font merging and a specific glyph range.
			//
			struct nk_font_config fcFontAwesomeConfiguration
					{ };
			static constexpr nk_rune rnIconRange[ ] { ICON_MIN_FA, ICON_MAX_FA, 0 };

			fcFontAwesomeConfiguration = nk_font_config( 16 );
			fcFontAwesomeConfiguration.range = rnIconRange;
			fcFontAwesomeConfiguration.merge_mode = 1;

			pRoboto = AddFont( PX_XOR( "Roboto-Regular.ttf" ), 23, fcFontAwesomeConfiguration );
			pRobotoBold = AddFont( PX_XOR( "RobotoBold.ttf" ), 21, fcFontAwesomeConfiguration );
			pRobotoSmall = AddFont( PX_XOR( "Roboto-Regular.ttf" ), 16, fcFontAwesomeConfiguration, 14 );
			pRobotoBoldSmall = AddFont( PX_XOR( "RobotoBold.ttf" ), 16, fcFontAwesomeConfiguration, 18 );
			pTahoma = AddFont( PX_XOR( "tahoma.ttf" ), 16, fcFontAwesomeConfiguration );
			pTahomaBold = AddFont( PX_XOR( "tahomabd.ttf" ), 16, fcFontAwesomeConfiguration );
			pEnvy = AddFont( PX_XOR( "Envy.ttf" ), 14, fcFontAwesomeConfiguration );

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
			pContext->style.button.border_color = nk_rgba( 34, 37, 41, 255 );

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

		void PX_API Initialize( Types::cstr_t _szApplicationTitle )
		{
			szNuklearWindowTitle = _szApplicationTitle;
			InitializeNuklear( );
		}

		struct nk_vec2 PX_API CalculateTextBounds( Types::cstr_t szText, unsigned uRowHeight /*= 30*/ )
		{
			static Types::cstr_t szBuffer;
			static struct nk_vec2 vecBuffer;
			static int iBuffer;

			return nk_text_calculate_text_bounds( pContext->style.font, szText, strlen( szText ), float( uRowHeight ), &szBuffer, &vecBuffer, &iBuffer, 0 );
		}

		void PX_API SetFont( EFont fntDesiredFont )
		{
			static std::deque< nk_font* > dqFonts { pTahoma, pTahomaBold, pRoboto, pRobotoBold, pRobotoSmall, pRobotoBoldSmall, pEnvy };
			dbg::Assert( fntDesiredFont >= 0 && fntDesiredFont < FONT_MAX );
			return nk_style_set_font( pContext, &dqFonts[ fntDesiredFont ]->handle );
		}

		void PX_API OnRelease( )
		{
			nk_d3d9_release( );
		}

		void PX_API Resize( unsigned uWidth, unsigned uHeight )
		{
			nk_d3d9_resize( uWidth, uHeight );
		}

		bool PX_API OnEvent( HWND h, UINT msg, WPARAM w, LPARAM l )
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

				if ( PX_INPUT.GetKeyState( VK_LBUTTON ) && !bMinimized )
				{
					POINT pntCursorPos { };
					GetCursorPos( &pntCursorPos );
					POINT pntCursorPosRelative { pntCursorPos.x - recWindowPos.left, pntCursorPos.y - recWindowPos.top };

					if ( ( pntCursorPosRelative.x > 0 && pntCursorPosRelative.x <= signed( uWindowWidth ) && pntCursorPosRelative.y > 0 && pntCursorPosRelative.y <= 30 ) || bDrag )
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

		void PX_API ApplyCursor( )
		{
			SetCursor( curCurrent );
			curCurrent = CURSOR_ARROW;
			bFoundHoverTarget = false;
			pContext->last_widget_state &= ~( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER );
		}

		bool PX_API Render( )
		{
			auto bShouldDrawUserInterface = true;
			SetFont( FONT_ROBOTO );

			bCreatedWindow && HandleWindowInput( );

			if ( nk_begin( pContext, szNuklearWindowTitle, nk_rect( 0, 0, float( uWindowWidth ), float( uWindowHeight ) ),
			               NK_WINDOW_NO_SCROLLBAR ) )
			{
				nk_layout_row_dynamic( pContext, 10, 0 );
				SetFont( FONT_ROBOTO );
				SetLayout( );

				if ( bDrawComboboxArrow )
				{
					const auto pDrawBuffer = nk_window_get_canvas( pContext );
					nk_stroke_line( pDrawBuffer, recComboboxWindowBounds.x, recComboboxWindowBounds.y - 2, recComboboxWindowBounds.x + recComboboxWindowBounds.w, recComboboxWindowBounds.y - 2, 2, clrBorder );
					recComboboxWindowBounds.y -= 3;
					nk_fill_triangle( pDrawBuffer, recComboboxWindowBounds.x + recComboboxWindowBounds.w - 3, recComboboxWindowBounds.y, recComboboxWindowBounds.x + recComboboxWindowBounds.w - 10, recComboboxWindowBounds.y - 7, recComboboxWindowBounds.x + recComboboxWindowBounds.w - 17, recComboboxWindowBounds.y, clrBackground );
				}

				if ( Widgets::pActiveEditColor != nullptr )
					Widgets::ColorPicker( );
			}
			else
				bShouldDrawUserInterface = false;
			nk_end( pContext );

			ApplyCursor( );
			if ( bCreatedWindow )
			{
				pDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB( 0, 0, 0, 0 ), 0, 0 );
				pDevice->BeginScene( );
				nk_d3d9_render( NK_ANTI_ALIASING_ON );
				pDevice->EndScene( );
				pDevice->Present( nullptr, nullptr, nullptr, nullptr );
			}
			else
				nk_d3d9_render( NK_ANTI_ALIASING_ON );

			return bShouldDrawUserInterface;
		}
	}

	namespace Widgets
	{
		using namespace Manager;

		ERowType rowLastRowType;

		struct nk_rect recLastWidgetLocation;
		Types::cstr_t szColorPickerSubject;

		bool PX_API HoveringNextWidget( )
		{
			return nk_input_is_mouse_prev_hovering_rect( &pContext->input, nk_widget_bounds( pContext ) );
		}

		nk_flags PX_API EditTextBox( nk_context* ctx, nk_flags flags, char* buffer, int max, nk_plugin_filter filter )
		{
			return nk_edit_string_zero_terminated( ctx, flags, buffer, max, filter );
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

		void PX_API Header( Types::cstr_t szTitle, Types::cstr_t _szApplicationTitle, Types::fn_callback_t fnMinimizeCallback, Types::fn_callback_t fnCloseCallback )
		{
			nk_layout_row_dynamic( pContext, 30, 0 );
			auto pOutput = nk_window_get_canvas( pContext );
			//auto pInput = &pContext->input;
			constexpr nk_color _clrBlueHover { 115, 189, 247, 255 };
			const auto uWidth = pContext->current->bounds.w;

			struct nk_text txtTitle, txtApplication, txtCloseButton, txtMinimizeButton;
			txtCloseButton.padding = txtApplication.padding = txtTitle.padding = pContext->style.text.padding;
			txtTitle.text = clrTextActive;
			txtApplication.text = clrTextDormant;

			nk_fill_rect( pOutput, nk_rect( 0, 0, uWidth, 102 ), 0.f, clrHeader );
			nk_stroke_line( pOutput, 0, 40, uWidth, 40, 1, clrColorTable[ NK_COLOR_BORDER ] );

			SetFont( FONT_ROBOTOBOLD );
			auto vecTitle = CalculateTextBounds( szTitle, 30 );
			nk_widget_text( pOutput, nk_rect( 15, 7, vecTitle.x, 30 ), szTitle, strlen( szTitle ), &txtTitle, NK_TEXT_CENTERED, pContext->style.font );
			SetFont( FONT_ROBOTO );
			auto vecApplicationTitle = CalculateTextBounds( _szApplicationTitle, 30 );
			nk_widget_text( pOutput, nk_rect( 23 + vecTitle.x, 7, vecApplicationTitle.x, 30 ), _szApplicationTitle, strlen( _szApplicationTitle ), &txtApplication, NK_TEXT_CENTERED, pContext->style.font );

			static auto clrMinimize = clrBlue, clrClose = clrMinimize;
			txtMinimizeButton.text = clrMinimize;
			txtCloseButton.text = clrClose;
			const struct nk_rect recMinimize = { uWidth - 70, 19, 20, 8 };
			const struct nk_rect recCloseButton = { uWidth - 33, 13, 20, 20 };
			nk_widget_text( pOutput, recMinimize, ICON_FA_MINUS, strlen( ICON_FA_MINUS ), &txtMinimizeButton, NK_TEXT_CENTERED, pContext->style.font );
			nk_widget_text( pOutput, recCloseButton, ICON_FA_TIMES, strlen( ICON_FA_TIMES ), &txtCloseButton, NK_TEXT_CENTERED, pContext->style.font );

			const bool bHoveringMinimize = nk_input_is_mouse_hovering_rect( &pContext->input, nk_rect( recMinimize.x + 8, recMinimize.y, recMinimize.w + 2, recMinimize.h ) ),
			           bHoveringClose = nk_input_is_mouse_hovering_rect( &pContext->input, recCloseButton ),
			           bClicking = PX_INPUT.GetKeyState( VK_LBUTTON );

			// Wait at least 200 ms for Nuklear to fix it's mouse pos stuff, and ensure that the window is in focus and not minimized.
			if ( GetActiveWindow( ) != hwWindowHandle || bMinimized || Tools::GetMoment( ) - mmtRestoreWindow < 500u )
				return;

			if ( bHoveringMinimize )
			{
				clrMinimize = _clrBlueHover;
				SetWidgetActive( CURSOR_HAND );
				if ( bClicking )
				{
					if ( bCreatedWindow )
					{
						bMinimized = true;
						ShowWindow( hwWindowHandle, SW_MINIMIZE );
					}
					fnMinimizeCallback( );
				}
			}
			else
				clrMinimize = clrBlue;

			if ( bHoveringClose )
			{
				clrClose = _clrBlueHover;
				SetWidgetActive( CURSOR_HAND );
				if ( bClicking )
					fnCloseCallback( );
			}
			else
				clrClose = clrBlue;
		}

		bool PX_API PrimaryTab( Types::cstr_t szText, bool bActive )
		{
			iCurrentRowUsedColumns++;

			if( nk_button_label_styled( pContext, bActive ? &btnTopActive : &btnTop, szText ) )
			{
				if( !bActive )
					Tools::EmitSound( L"ButtonClick.wav" );
				return true;
			}
			return false;
		}

		bool PX_API SecondaryTab( Types::cstr_t szText, bool bActive )
		{
			iCurrentRowUsedColumns++;

			if ( bActive )
			{
				auto rcBoundaries = nk_widget_bounds( pContext );
				auto pOutput = nk_window_get_canvas( pContext );
				nk_fill_rect_multi_color( pOutput, rcBoundaries, clrBorder, clrDarkBackground, clrDarkBackground, clrBorder );

				rcBoundaries.w += rcBoundaries.x;
				rcBoundaries.h += rcBoundaries.y;
				SetFont( FONT_TAHOMABOLD );
				const auto bResult = nk_button_label_styled( pContext, &btnRegularActive, szText );
				HoverCheck( CURSOR_HAND );
				SetFont( FONT_TAHOMA );
				nk_stroke_line( pOutput, rcBoundaries.x + 2, rcBoundaries.y, rcBoundaries.x + 2, rcBoundaries.h, 2, clrBlue );
				return bResult;
			}
			SetFont( FONT_TAHOMA );
			const auto bReturn = nk_button_label_styled( pContext, &btnRegular, szText );
			if ( bReturn )
				Tools::EmitSound( L"ButtonClick.wav" );
			HoverCheck( CURSOR_HAND );
			return bReturn;
		}

		void PX_API Separator( int iRed, int iGreen, int iBlue, unsigned uStartHeight, bool bUpperBorder /*= false*/ )
		{
			constexpr auto uSeparatorHeight = 42u;
			constexpr struct nk_color clrBorderColor = { 85, 88, 94, 255 };
			const auto pDrawBuffer = nk_window_get_canvas( pContext );
			nk_fill_rect( pDrawBuffer, nk_rect( 0.f, float( uStartHeight ), float( uWindowWidth ), float( uSeparatorHeight ) ), 0.f, nk_rgba( iRed, iGreen, iBlue, 255 ) );
			nk_stroke_line( pDrawBuffer, 0.f, float( uStartHeight + uSeparatorHeight - 1 ), float( pContext->current->bounds.w ), float( uStartHeight + uSeparatorHeight - 1 ), 0.5f, clrBorderColor );

			if ( bUpperBorder )
				nk_stroke_line( pDrawBuffer, 0.f, float( uStartHeight + 1 ), float( pContext->current->bounds.w ), float( uStartHeight + 1 ), 0.5f, clrBorderColor );
		}

		bool PX_API Button( EPosition pPosition, const char* szText, bool bActive )
		{
			iCurrentRowUsedColumns++;

			SetFont( FONT_ROBOTOBOLDSMALL );
			const auto rcBoundaries = nk_widget_bounds( pContext );
			const auto pOutput = nk_window_get_canvas( pContext );
			auto bHover = false;
			nk_flags fOldFlags = 0;
			if ( !bFoundHoverTarget )
			{
				fOldFlags = pContext->last_widget_state;
				pContext->last_widget_state = 0;
			}
			const auto bReturn = nk_button_label_styled( pContext, bActive ? &btnSpecialActive : &btnSpecial, szText );

			if( bReturn )
				Tools::EmitSound( L"ButtonClick.wav" );

			if ( !bFoundHoverTarget )
			{
				bHover = HoverCheck( CURSOR_HAND );
				pContext->last_widget_state = fOldFlags;
				HoverCheck( CURSOR_HAND );
			}
			nk_color clrCurrentColor { };
			if ( bHover )
			{
				if ( !bActive )
					clrCurrentColor = clrBlueHover;
			}
			else
				clrCurrentColor = clrBlueDormant;
			if ( bActive )
				clrCurrentColor = clrBlueActive;

			switch ( pPosition )
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

		void PX_API Checkbox( Types::cstr_t szText, bool *bActive )
		{
			iCurrentRowUsedColumns += 2;

			static auto bWasClicking = false;

			nk_layout_row_push( pContext, 25 );
			const auto rcBoundaries = nk_widget_bounds( pContext );
			const auto bHovering = nk_input_is_mouse_hovering_rect( &pContext->input, rcBoundaries );
			const auto bClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == CInputManager::EKeyState::DOWN;

			if ( bHovering )
				SetWidgetActive( CURSOR_HAND );

			if ( bClicking && bHovering )
			{
				if ( !bWasClicking )
				{
					*bActive = !*bActive;
					Tools::EmitSound( *bActive ? LR"(Tick.wav)" : LR"(Untick.wav)" );
				}
				bWasClicking = true;
			}
			else if ( !bClicking )
				bWasClicking = false;

			SetFont( FONT_TAHOMA );
			nk_label_colored( pContext, *bActive ? ICON_FA_CHECK_SQUARE : ICON_FA_SQUARE, NK_TEXT_CENTERED, *bActive ? clrBlue : bHovering ? ( bClicking ? clrBlue : clrBlue ) : clrTextDormant );
			nk_layout_row_push( pContext, CalculateTextBounds( szText, 15 ).x );
			nk_label_colored( pContext, ( szText + std::string( "  " ) ).c_str( ), NK_TEXT_LEFT, clrTextDormant );
		}

		int PX_API Tabs( unsigned uStartX, unsigned uStartY, const std::deque< Types::cstr_t >& dqButtons, unsigned uActiveButton )
		{
			PX_DEF pxTabSpace = 24; // 12 * 2 - 12 px on either side.
			auto iPressedButton = -1;
			auto iXIncrement = 0;
			SetFont( FONT_ROBOTOBOLDSMALL );
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

		int PX_API SubTabs( unsigned uStartX, unsigned uStartY, unsigned uButtonWidth, unsigned uButtonHeight, const std::deque< Types::cstr_t >& dqButtons, unsigned uActiveButton )
		{
			nk_layout_space_begin( pContext, NK_STATIC, float( uButtonHeight * dqButtons.size( ) ), dqButtons.size( ) );
			auto iButtonPressed = -1;
			for ( unsigned i { }; i < dqButtons.size( ); i++ )
			{
				nk_layout_space_push( pContext, nk_rect( float( uStartX ), float( uStartY + ( uButtonHeight * i ) ), float( uButtonWidth ), float( uButtonHeight ) ) );
				if ( SecondaryTab( dqButtons.at( i ), i == uActiveButton ) )
					iButtonPressed = i;
			}
			nk_layout_space_end( pContext );
			HoverCheck( CURSOR_HAND );
			return iButtonPressed;
		}

		void PX_API BeginGroupbox( unsigned uStartX, unsigned uStartY, unsigned uBoxWidth, unsigned uBoxHeight, Types::cstr_t szTitle )
		{
			SetFont( FONT_TAHOMA );
			nk_layout_space_begin( pContext, NK_STATIC, float( uBoxHeight ), 1 );
			const auto rcBoundaries = nk_widget_bounds( pContext );
			nk_layout_space_push( pContext, nk_rect( float( uStartX - rcBoundaries.x ), float( uStartY - rcBoundaries.y ), float( uBoxWidth ), float( uBoxHeight ) ) );
			auto rcNewBoundaries = nk_widget_bounds( pContext );
			nk_group_begin( pContext, szTitle, NK_WINDOW_NO_SCROLLBAR );

			const auto pOutput = nk_window_get_canvas( pContext );
			rcNewBoundaries.x += 4;
			rcNewBoundaries.y += 20;
			rcNewBoundaries.w -= 8;
			rcNewBoundaries.h -= 28;
			// Top left, top right, bottom right, bottom left
			const auto uTextWidth = CalculateTextBounds( szTitle, 30 ).x;
			nk_fill_rect_multi_color( pOutput, nk_rect( rcNewBoundaries.x + 1.8f, rcNewBoundaries.y + 1.f, rcNewBoundaries.w - 2.f, rcNewBoundaries.h - 2.f ), clrDarkBackground, clrDarkBackground, clrBackground, clrBackground );
			nk_stroke_rect( pOutput, rcNewBoundaries, 4.f, 1.f, clrBorder );
			nk_stroke_line( pOutput, rcNewBoundaries.x + 7, rcNewBoundaries.y, rcNewBoundaries.x + 3 + uTextWidth, rcNewBoundaries.y, 3, clrDarkBackground );
			BeginRow( 16, 1, ROW_CUSTOM );
			auto rcText = nk_widget_bounds( pContext );
			PushCustomRow( unsigned( rcNewBoundaries.x + 8 - rcText.x ), unsigned( rcNewBoundaries.y - rcText.y - 10 ), unsigned( uTextWidth ), 16 );
			nk_label( pContext, szTitle, NK_TEXT_LEFT );
			VerticalSpacing( 5 );

			SetFont( FONT_ROBOTOSMALL );
		}

		void PX_API EndGroupbox( )
		{
			return nk_group_end( pContext );
		}

		void PX_API ColorPicker( )
		{
			constexpr struct nk_vec2 vecColorPickerSize
			{
				305, 440
			};
			const auto _uWindowWidth = pContext->current->bounds.w, _uWindowHeight = pContext->current->bounds.h;
			const struct nk_rect rcColorPickerBoundaries
			{
				( _uWindowWidth / 2 ) - ( vecColorPickerSize.x / 2 ), ( _uWindowHeight / 2 ) - ( vecColorPickerSize.y / 2 ), vecColorPickerSize.x, vecColorPickerSize.y
			};
			const static std::string strBaseTitle = R"(Color of ')";

			static struct nk_colorf clrChosenColor;
			static auto bNewColor = true;
			static auto bShouldClose = false;
			static auto bStoppedClicking = false;
			static auto iCurrentSequence = 0u;

			if ( !PX_INPUT.GetKeyState( VK_LBUTTON ) )
				bStoppedClicking = true;
			if ( bNewColor && pActiveEditColor )
			{
				iCurrentSequence = 0;
				clrChosenColor = { pActiveEditColor->GetColor( iCurrentSequence ).rfl, pActiveEditColor->GetColor( iCurrentSequence ).gfl, pActiveEditColor->GetColor( iCurrentSequence ).bfl, pActiveEditColor->GetColor( iCurrentSequence ).afl };
			}
			bNewColor = false;

			const auto pOutput = nk_window_get_canvas( pContext );
			nk_fill_rect( pOutput, nk_rect( 0, 0, _uWindowWidth, _uWindowHeight ), 0, nk_rgba( 0, 0, 0, 180 ) );

			if ( bShouldClose )
			{
				bShouldClose = false;
				pActiveEditColor = nullptr;
			}

			if ( !bStoppedClicking )
				return;

			if ( nk_popup_begin( pContext, NK_POPUP_DYNAMIC, ( strBaseTitle + szColorPickerSubject + R"(')" ).c_str( ), NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_NO_SCROLLBAR,
			                     rcColorPickerBoundaries, pActiveEditColor == nullptr ) )
			{
				nk_layout_row_static( pContext, 255, 295, 1 );
				clrChosenColor = nk_color_picker( pContext, clrChosenColor, NK_RGBA );
				nk_layout_row_dynamic( pContext, 5, 0 );
				nk_layout_row_dynamic( pContext, 16, 4 );
				nk_label( pContext, ( "R: " + std::to_string( int( clrChosenColor.r * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
				nk_label( pContext, ( "G: " + std::to_string( int( clrChosenColor.g * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
				nk_label( pContext, ( "B: " + std::to_string( int( clrChosenColor.b * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
				nk_label( pContext, ( "A: " + std::to_string( int( clrChosenColor.a * 255.f ) ) ).c_str( ), NK_TEXT_CENTERED );
				nk_layout_row_dynamic( pContext, 10, 1 );
				nk_button_color( pContext, nk_rgba( int( clrChosenColor.r * 255.f ), int( clrChosenColor.g * 255.f ), int( clrChosenColor.b * 255.f ), int( clrChosenColor.a * 255.f ) ) );

				nk_layout_row_begin( pContext, NK_STATIC, 15, pActiveEditColor->uSequenceCount + 3 );
				nk_layout_row_push( pContext, COLOR_BUTTON_WIDTH );

				for ( auto u = 0u; u < pActiveEditColor->CountSequences( ); u++ )
				{
					auto recBoundaries = nk_widget_bounds( pContext );
					if ( nk_button_color( pContext, nk_rgba( pActiveEditColor->GetColor( u ).r, pActiveEditColor->GetColor( u ).g, pActiveEditColor->GetColor( u ).b, pActiveEditColor->GetColor( u ).a ) ) )
					{
						iCurrentSequence = u;
						clrChosenColor = { pActiveEditColor->GetColor( iCurrentSequence ).rfl, pActiveEditColor->GetColor( iCurrentSequence ).gfl, pActiveEditColor->GetColor( iCurrentSequence ).bfl, pActiveEditColor->GetColor( iCurrentSequence ).afl };
					}
					if ( u == iCurrentSequence )
					{
						recBoundaries.x += 1;
						recBoundaries.y += 1;
						recBoundaries.w -= 2;
						recBoundaries.h -= 2;
						nk_stroke_rect( nk_window_get_canvas( pContext ), recBoundaries, pContext->style.button.rounding, 1.f, clrBlue );
					}
				}

				auto uPadding = vecColorPickerSize.x - ( COLOR_BUTTON_WIDTH * pActiveEditColor->CountSequences( ) ) - ( COLOR_BUTTON_PADDING * pActiveEditColor->CountSequences( ) * 2 ) - 170;
				nk_layout_row_push( pContext, uPadding );
				nk_spacing( pContext, 1 );
				nk_layout_row_push( pContext, 75 );

				if ( Button( EPosition::LEFT, "+", false ) )
				{
					pActiveEditColor->PutNewColorSequence( Tools::color_t( ), 100u );
					iCurrentSequence = pActiveEditColor->uSequenceCount - 1;
					clrChosenColor = { pActiveEditColor->GetColor( iCurrentSequence ).rfl, pActiveEditColor->GetColor( iCurrentSequence ).gfl, pActiveEditColor->GetColor( iCurrentSequence ).bfl, pActiveEditColor->GetColor( iCurrentSequence ).afl };
				}
				if ( Button( EPosition::RIGHT, "-", false ) )
				{
					pActiveEditColor->DeleteColorSequence( iCurrentSequence );
					iCurrentSequence = 0;
					clrChosenColor = { pActiveEditColor->GetColor( iCurrentSequence ).rfl, pActiveEditColor->GetColor( iCurrentSequence ).gfl, pActiveEditColor->GetColor( iCurrentSequence ).bfl, pActiveEditColor->GetColor( iCurrentSequence ).afl };
				}

				nk_layout_row_end( pContext );

				nk_layout_row_static( pContext, 25, int( vecColorPickerSize.x - 5 ), 1 );
				if ( Button( EPosition::RIGHT, "SET", false ) )
				{
					pActiveEditColor->GetColor( iCurrentSequence ).rfl = clrChosenColor.r;
					pActiveEditColor->GetColor( iCurrentSequence ).gfl = clrChosenColor.g;
					pActiveEditColor->GetColor( iCurrentSequence ).bfl = clrChosenColor.b;
					pActiveEditColor->GetColor( iCurrentSequence ).afl = clrChosenColor.a;
				}
				nk_layout_row_static( pContext, 25, int( vecColorPickerSize.x - 5 ), 1 );
				if ( Button( EPosition::LEFT, "EXIT", false ) )
				{
					bShouldClose = true;
					bNewColor = true;
				}
				if ( !nk_input_is_mouse_prev_hovering_rect( &pContext->input, rcColorPickerBoundaries ) && ( PX_INPUT.GetKeyState( VK_LBUTTON ) ) && bStoppedClicking )
				{
					bShouldClose = true;
					bNewColor = true;
				}
				nk_layout_row_dynamic( pContext, 10, 0 );
				nk_popup_end( pContext );
				return;
			}
			bNewColor = true;
			bStoppedClicking = false;
		}

		void PX_API ColorButton( Types::cstr_t szSubject, Tools::color_sequence_t* pColor )
		{
			iCurrentRowUsedColumns++;
			
			auto clr = pColor->GetCurrentColor( );
			if ( nk_button_color( pContext, nk_rgba( clr.r, clr.g, clr.b, clr.a ) ) && pActiveEditColor == nullptr )
			{
				szColorPickerSubject = szSubject;
				pActiveEditColor = pColor;
			}
			HoverCheck( CURSOR_HAND );
		}

		int PX_API Combobox( unsigned uButtonHeight, Types::cstr_t szTitle, const std::deque< Types::cstr_t >& dqOptions, unsigned uSelectedOption )
		{
			iCurrentRowUsedColumns++;

			auto iSelectedOption = -1;
			auto bDrewCombo = false;
			SetFont( FONT_TAHOMA );
			const auto recComboboxBounds = nk_widget_bounds( pContext );

			const auto pOutput = nk_window_get_canvas( pContext );
			if ( nk_combo_begin_label( pContext, szTitle, nk_vec2( recComboboxBounds.w, float( uButtonHeight ) * dqOptions.size( ) + 5 * ( dqOptions.size( ) - 1 ) - 3 ) ) )
			{
				bDrawComboboxArrow = true;
				recComboboxWindowBounds = pContext->current->bounds;
				for ( unsigned i { }; i < dqOptions.size( ); i++ )
				{
					if ( i == uSelectedOption )
						pContext->style.contextual_button = btnComboActive;
					else
						pContext->style.contextual_button = btnCombo;

					nk_layout_row_dynamic( pContext, float( uButtonHeight ), 1 );
					if ( nk_combo_item_label( pContext, dqOptions.at( i ), NK_TEXT_LEFT ) )
						iSelectedOption = i;
				}
				nk_combo_end( pContext );
				bDrewCombo = true;
			}
			nk_fill_triangle( pOutput, recComboboxBounds.x + recComboboxBounds.w - 10, recComboboxBounds.y + ( recComboboxBounds.h / 2 ) - 3, recComboboxBounds.x + recComboboxBounds.w - 14, recComboboxBounds.y + ( recComboboxBounds.h / 2 ) + 3, recComboboxBounds.x + recComboboxBounds.w - 18, recComboboxBounds.y + ( recComboboxBounds.h / 2 ) - 3, nk_input_is_mouse_prev_hovering_rect( &pContext->input, recComboboxBounds ) && !bDrewCombo ? clrTextActive : clrTextDormant );
			return iSelectedOption;
		}

		void PX_API ComboboxMulti( unsigned uButtonHeight, Types::cstr_t szTitle, const std::deque< Types::cstr_t >& dqOptions, std::deque<bool>& dqEnabledOptions )
		{
			iCurrentRowUsedColumns++;

			auto bDrewCombo = false;
			SetFont( FONT_TAHOMA );
			auto recComboboxBounds = nk_widget_bounds( pContext );

			const auto pOutput = nk_window_get_canvas( pContext );
			if ( nk_combo_begin_label( pContext, szTitle, nk_vec2( recComboboxBounds.w, float( uButtonHeight ) * dqOptions.size( ) + 5 * ( dqOptions.size( ) - 1 ) - 3 ) ) )
			{
				bDrawComboboxArrow = true;
				recComboboxWindowBounds = pContext->current->bounds;
				for ( unsigned i { }; i < dqOptions.size( ); i++ )
				{
					nk_layout_row_dynamic( pContext, float( uButtonHeight ), 1 );
					if ( nk_button_label_styled( pContext, dqEnabledOptions.at( i ) ? &btnComboActive : &btnCombo, dqOptions.at( i ) ) )
						dqEnabledOptions.at( i ) = !dqEnabledOptions.at( i );
				}
				nk_combo_end( pContext );
				bDrewCombo = true;
			}
			nk_fill_triangle( pOutput, recComboboxBounds.x + recComboboxBounds.w - 10, recComboboxBounds.y + ( recComboboxBounds.h / 2 ) - 3, recComboboxBounds.x + recComboboxBounds.w - 14, recComboboxBounds.y + ( recComboboxBounds.h / 2 ) + 3, recComboboxBounds.x + recComboboxBounds.w - 18, recComboboxBounds.y + ( recComboboxBounds.h / 2 ) - 3, nk_input_is_mouse_prev_hovering_rect( &pContext->input, recComboboxBounds ) && !bDrewCombo ? clrTextActive : clrTextDormant );
		}

		int PX_API Slider( Types::cstr_t szTitle, char* szInputBuffer, int iMin, int iMax, int iCurrentValue, unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight )
		{
			iCurrentRowUsedColumns += 3 ;

			dbg::Assert( iMax > iMin );
			auto szTexta = std::to_string( iCurrentValue ).substr( 0, std::to_string( iCurrentValue ).size( ) );
			auto szText = szTexta.c_str( );
			static auto bInEdit = false, bSetEditValue = false;

			SetFont( FONT_ROBOTOSMALL );
			const auto vecTitleSize = CalculateTextBounds( szTitle, 10 );
			auto vecTextSize = CalculateTextBounds( szText, 10 );
			PushCustomRow( uStartX + 5, uStartY, unsigned( vecTitleSize.x ), unsigned( vecTitleSize.y ) );
			nk_label( pContext, szTitle, NK_TEXT_LEFT );
			PushCustomRow( uStartX + uWidth - unsigned( vecTextSize.x ) - 5, uStartY, unsigned( vecTextSize.x ), unsigned( vecTextSize.y ) );

			const auto recBounds = nk_widget_bounds( pContext );
			const auto bHovering = nk_input_is_mouse_hovering_rect( &pContext->input, recBounds );
			const bool bClicking = PX_INPUT.GetKeyState( VK_LBUTTON );

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
				static auto bSetBuffer = false;
				static unsigned uSetKey = 0;
				const auto fnWriteBuffer = [ = ]( unsigned uKey )
				{
					if ( ( uKey >= '0' && uKey <= '9' || uKey == '-' ) && bSetBuffer )
						uSetKey = uKey;
				};
				static auto bSetCallback = false;

				if ( !strcmp( szInputBuffer, "0" ) )
					bSetBuffer = true;

				if( uSetKey != 0 && bSetBuffer )
				{
					strcpy( szInputBuffer, "" );
					uSetKey = 0;
					pContext->text_edit.select_start = 1;
					pContext->text_edit.select_end = 1;
					pContext->text_edit.string.len = 1;
					bSetBuffer = false;
				}

				if ( !bSetCallback )
				{
					PX_INPUT.AddGlobalCallback( fnWriteBuffer );
					bSetCallback = true;
				}

				iCurrentRowUsedColumns--;
				PushCustomRow( uStartX + unsigned( vecTitleSize.x ) + 8, uStartY, uWidth - unsigned( vecTitleSize.x ), unsigned( vecTextSize.y ) + 5 );
				const auto recNewBounds = nk_widget_bounds( pContext );
				iCurrentValue = Inputbox< int >( strlen( std::to_string( FLT_MAX ).c_str( ) ), szInputBuffer );
				bHoveringInputBox = nk_input_is_mouse_hovering_rect( &pContext->input, recNewBounds );

				//auto urdad = pContext;

				if ( bHoveringInputBox )
					SetWidgetActive( CURSOR_IBEAM );
				if ( !bHoveringInputBox && bClicking )
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
			if ( nk_input_is_mouse_hovering_rect( &pContext->input, recSliderBounds ) && bClicking && !pActiveEditColor )
				iCurrentValue = int( iMin + ( pContext->input.mouse.pos.x - recSliderBounds.x ) / recSliderBounds.w * ( iMax - iMin ) );

			const auto iNewValue = nk_slide_int( pContext, iMin, iCurrentValue, iMax, ( iMax - iMin ) / 20 );
			if ( !bInEdit )
				iCurrentValue = iNewValue;
			HoverCheck( CURSOR_HAND );
			SetFont( FONT_ROBOTOSMALL );
			return iCurrentValue;
		}

		float PX_API Slider( Types::cstr_t szTitle, char* szInputBuffer, float flMin, float flMax, float flCurrentValue, unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight, unsigned uDigits )
		{
			iCurrentRowUsedColumns += 3;

			dbg::Assert( flMax > flMin );
			auto szTexta = std::to_string( flCurrentValue ).substr( 0, std::to_string( int( flCurrentValue ) ).size( ) + 1 + uDigits );
			auto szText = szTexta.c_str( );
			static auto bInEdit = false, bSetEditValue = false;

			SetFont( FONT_ROBOTOSMALL );
			auto vecTitleSize = CalculateTextBounds( szTitle, 10 );
			auto vecTextSize = CalculateTextBounds( szText, 10 );
			PushCustomRow( uStartX + 5, uStartY, unsigned( vecTitleSize.x ), unsigned( vecTitleSize.y ) );
			nk_label( pContext, szTitle, NK_TEXT_LEFT );
			PushCustomRow( uStartX + uWidth - unsigned( vecTextSize.x ) - 5, uStartY, unsigned( vecTextSize.x ), unsigned( vecTextSize.y ) );

			const auto recBounds = nk_widget_bounds( pContext );
			const auto bHovering = nk_input_is_mouse_hovering_rect( &pContext->input, recBounds );
			const auto bClicking = PX_INPUT.GetKeyState( VK_LBUTTON );

			if ( bHovering && !bInEdit )
			{
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
				static auto bSetBuffer = false;
				static unsigned uSetKey = 0;
				const auto fnWriteBuffer = [ = ]( unsigned uKey )
				{
					if ( ( uKey >= '0' && uKey <= '9' || uKey == '-' || uKey == '.' ) && bSetBuffer )
						uSetKey = uKey;
				};
				static auto bSetCallback = false;

				if ( !strcmp( szInputBuffer, "0" ) )
					bSetBuffer = true;

				if ( uSetKey != 0 && bSetBuffer )
				{
					strcpy( szInputBuffer, "" );
					uSetKey = 0;
					pContext->text_edit.select_start = 1;
					pContext->text_edit.select_end = 1;
					pContext->text_edit.string.len = 1;
					bSetBuffer = false;
				}

				if ( !bSetCallback )
				{
					PX_INPUT.AddGlobalCallback( fnWriteBuffer );
					bSetCallback = true;
				}

				iCurrentRowUsedColumns--;
				PushCustomRow( uStartX + unsigned( vecTitleSize.x ) + 8, uStartY, uWidth - unsigned( vecTitleSize.x ), unsigned( vecTextSize.y ) + 5 );
				const auto recNewBounds = nk_widget_bounds( pContext );
				flCurrentValue = Inputbox< float >( strlen( std::to_string( FLT_MAX ).c_str( ) ), szInputBuffer );
				bHoveringInputBox = nk_input_is_mouse_hovering_rect( &pContext->input, recNewBounds );

				if ( bHoveringInputBox )
					SetWidgetActive( CURSOR_IBEAM );
				else if ( bClicking || PX_INPUT.GetKeyState( VK_RETURN ) )
				{
					bSetEditValue = strlen( szInputBuffer ) > 0;
					bInEdit = false;
				}
			}
			else if ( bSetEditValue )
			{
				bSetEditValue = false;
				const auto iValue = std::stof( szInputBuffer );
				flCurrentValue = iValue <= flMax ? ( iValue >= flMin ? iValue : flMin ) : flMax;
			}
			else
				nk_label( pContext, szText, NK_TEXT_LEFT );

			PushCustomRow( uStartX, uStartY + unsigned( vecTextSize.y ) + 3, uWidth, uHeight - unsigned( vecTextSize.y ) - 3 );

			const auto recSliderBounds = nk_widget_bounds( pContext );
			if( nk_input_is_mouse_hovering_rect( &pContext->input, recSliderBounds ) && bClicking && !pActiveEditColor )
				flCurrentValue = flMin + ( ( pContext->input.mouse.pos.x - recSliderBounds.x ) / recSliderBounds.w ) * ( flMax - flMin );

			const auto flNewValue = nk_slide_float( pContext, flMin, flCurrentValue, flMax, ( flMax - flMin ) / 20.f );
			if ( !bInEdit )
				flCurrentValue = flNewValue;
			HoverCheck( CURSOR_HAND );
			SetFont( FONT_ROBOTOSMALL );
			return flCurrentValue;
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

			dbg::Assert( iCurrentRowUsedColumns == iCurrentRowMaxColumns );
			fnEndRow[ rowLastRowType ]( pContext );
		}

		void PX_API SetRowWidth( float flRowWidth )
		{
			dbg::Assert( rowLastRowType == ROW_STATIC );
			return nk_layout_row_push( pContext, flRowWidth );
		}

		void PX_API Spacing( unsigned uColumns /*= 1*/ )
		{
			dbg::Assert( iCurrentRowUsedColumns++ < iCurrentRowMaxColumns );
			nk_spacing( pContext, uColumns );
			if ( iCurrentRowUsedColumns == iCurrentRowMaxColumns )
				EndRow( );
		}

		void PX_API VerticalSpacing( unsigned uPixels /*= 5*/ )
		{
			BeginRow( uPixels, 0, ROW_STATIC );
			EndRow( );
		}

		void PX_API PushCustomRow( unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight )
		{
			dbg::Assert( rowLastRowType == ROW_CUSTOM );
			return nk_layout_space_push( pContext, nk_rect( float( uStartX ), float( uStartY ), float( uWidth ), float( uHeight ) ) );
		}
	}
}
