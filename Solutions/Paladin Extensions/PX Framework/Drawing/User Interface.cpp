/// User Interface.cpp

#define PX_NUKLEAR_IMPLEMENTATION

#include "../PX Framework.hpp"

namespace PX
{
	namespace UI
	{
		namespace Manager
		{
			using Render::pDevice;
			using Render::dxParameters;

			Tools::cstr_t	szWindowTitle = PX_XOR( "Paladin Extensions" );
			auto			szApplicationTitle = static_cast< char* >( malloc( 32 ) );

			nk_font_atlas* pAtlas;
			struct nk_font *pTahoma, *pTahomaBold, *pRoboto, *pRobotoBold, *pRobotoSmall, *pRobotoBoldSmall, *pEnvy;
			struct nk_rect recComboboxWindowBounds;

			constexpr nk_color clrTextActive { 255, 255, 255, 255 }, clrBlue { 33, 150, 243, 255 }, clrDarkBlue { 43, 60, 75, 255 }, clrBackground { 56, 60, 66, 255 }, clrLightBackground { 61, 65, 72, 255 },
				clrDarkBackground { 45, 50, 56, 255 }, clrBorder { 80, 84, 89, 255 }, clrToolbox { 42, 44, 48, 255 }, clrHeader { 33, 36, 40, 255 }, clrBlueActive { 54, 70, 84, 255 },
				clrBlueHover { 54, 70, 84, 200 }, clrBlueDormant { 43, 60, 75, 255 }, clrTextDormant { 175, 180, 187, 255 };
			nk_color clrColorTable[ NK_COLOR_COUNT ] { };

			nk_style_button btnTopActive { }, btnTop { }, btnRegularActive { }, btnRegular { }, btnSpecialActive { }, btnSpecial { }, btnCombo { }, btnComboActive { };

			Render::ECursor curCurrent;

			bool bFoundHoverTarget = false;

			nk_font* PX_API AddFont( std::string strFontFileName, unsigned uFontSize, struct nk_font_config fcFontConfiguration, unsigned uFontAwesomeSize = 0 )
			{
				static auto strFontDirectory = Tools::string_cast< std::string >( Tools::GetDirectory( 3 ) + PX_XOR( LR"(\Resources\Fonts\)" ) );

				nk_d3d9_font_stash_begin( &pAtlas );
				auto pFont = nk_font_atlas_add_from_file( pAtlas, ( strFontDirectory + strFontFileName ).c_str( ), float( uFontSize ), nullptr );
				nk_font_atlas_add_from_file( pAtlas, ( strFontDirectory + PX_XOR( "FontAwesome.ttf" ) ).c_str( ), uFontAwesomeSize ? float( uFontAwesomeSize ) : float( uFontSize ), &fcFontConfiguration );
				nk_d3d9_font_stash_end( );
				return pFont;
			}

			void PX_API InitializeNuklear( )
			{
				pContext = nk_d3d9_init( pDevice, Render::uWindowWidth, Render::uWindowHeight );

				//
				// We only need a font configuration for FontAwesome because it needs font merging and a specific glyph range.
				//
				struct nk_font_config fcFontAwesomeConfiguration
				{ };
				static constexpr nk_rune rnIconRange[ ] { ICON_MIN_FA, ICON_MAX_FA, 0 };

				fcFontAwesomeConfiguration = nk_font_config( 16 );
				fcFontAwesomeConfiguration.range = rnIconRange;
				fcFontAwesomeConfiguration.merge_mode = 1;

				pRoboto = AddFont( PX_XOR( "Roboto.ttf" ), 21, fcFontAwesomeConfiguration );
				pRobotoBold = AddFont( PX_XOR( "RobotoBold.ttf" ), 21, fcFontAwesomeConfiguration );
				pRobotoSmall = AddFont( PX_XOR( "Roboto.ttf" ), 16, fcFontAwesomeConfiguration, 14 );
				pRobotoBoldSmall = AddFont( PX_XOR( "RobotoBold.ttf" ), 16, fcFontAwesomeConfiguration, 12 );
				pTahoma = AddFont( PX_XOR( "Tahoma.ttf" ), 16, fcFontAwesomeConfiguration );
				pTahomaBold = AddFont( PX_XOR( "TahomaBold.ttf" ), 16, fcFontAwesomeConfiguration );
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

			void PX_API Initialize( Tools::cstr_t szApplicationTitle )
			{
				szNuklearWindowTitle = szApplicationTitle;
				InitializeNuklear( );
			}

			struct nk_vec2 PX_API CalculateTextBounds( Tools::cstr_t szText, unsigned uRowHeight /*= 30*/ )
			{
				static Tools::cstr_t szBuffer;
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

			bool OnEvent( HWND h, UINT msg, WPARAM w, LPARAM l )
			{
				return nk_d3d9_handle_event( h, msg, w, l );
			}

			bool HandleWindowInput( )
			{
				auto bShouldDrawInterface = true;
				if ( Render::bCreatedWindow )
				{
					static auto bDrag = false;
					RECT recWindowPos { };
					GetWindowRect( Render::hwWindowHandle, &recWindowPos );
					static POINT pntOldCursorPosRelative { };

					if ( PX_INPUT.GetKeyState( VK_LBUTTON ) && !Render::bMinimized )
					{
						POINT pntCursorPos { };
						GetCursorPos( &pntCursorPos );
						POINT pntCursorPosRelative { pntCursorPos.x - recWindowPos.left, pntCursorPos.y - recWindowPos.top };

						if ( ( pntCursorPosRelative.x > 0 && pntCursorPosRelative.x <= signed( Render::uWindowWidth ) && pntCursorPosRelative.y > 0 && pntCursorPosRelative.y <= 30 ) || bDrag )
						{
							bDrag = true;
							if ( !pntOldCursorPosRelative.x || !pntOldCursorPosRelative.y ) pntOldCursorPosRelative = pntCursorPosRelative;

							SetWindowPos( Render::hwWindowHandle, nullptr, ( recWindowPos.left - pntOldCursorPosRelative.x ) + pntCursorPosRelative.x,
								( recWindowPos.top - pntOldCursorPosRelative.y ) + pntCursorPosRelative.y, Render::uWindowWidth, Render::uWindowHeight, 0 );
							UpdateWindow( Render::hwWindowHandle );
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
				while ( PeekMessage( &msgBuffer, Render::hwWindowHandle, 0, 0, PM_REMOVE ) )
				{
					if ( msgBuffer.message == WM_QUIT )
						bShouldDrawInterface = false;
					TranslateMessage( &msgBuffer );
					DispatchMessage( &msgBuffer );
				}
				nk_input_end( pContext );
				return bShouldDrawInterface;
			}

			void ApplyCursor( )
			{
				SetCursor( curCurrent );
				curCurrent = Render::CURSOR_ARROW;
				bFoundHoverTarget = false;
				pContext->last_widget_state &= ~( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER );
			}

			bool Render( )
			{
				auto bShouldDrawUserInterface = true;
				SetFont( FONT_ROBOTO );

				Render::bCreatedWindow && HandleWindowInput( );

				if ( nk_begin( pContext, szNuklearWindowTitle, nk_rect( 0, 0, float( Render::uWindowWidth ), float( Render::uWindowHeight ) ),
							   NK_WINDOW_NO_SCROLLBAR ) )
				{
					nk_layout_row_dynamic( pContext, 10, 0 );
					SetFont( FONT_ROBOTO );
					SetLayout( );
				}
				else
					bShouldDrawUserInterface = false;
				nk_end( pContext );

				ApplyCursor( );
				if ( Render::bCreatedWindow )
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
			Tools::cstr_t szColorPickerSubject;
			Tools::byte_t* pActiveEditColor = nullptr;

			bool PX_API HoveringNextWidget( )
			{
				return nk_input_is_mouse_prev_hovering_rect( &pContext->input, nk_widget_bounds( pContext ) );
			}

			nk_flags PX_API EditTextBox( nk_context* ctx, nk_flags flags, char* buffer, int max, nk_plugin_filter filter )
			{
				__asm call nk_edit_string_zero_terminated
			}

			void HoverCheck( Render::ECursor curSetCursor )
			{
				if ( pContext->last_widget_state & NK_WIDGET_STATE_ACTIVE || pContext->last_widget_state & NK_WIDGET_STATE_HOVER )
				{
					bFoundHoverTarget = true;
					curCurrent = curSetCursor;
				}
			}

			void PX_API Header( Tools::cstr_t szTitle, Tools::cstr_t szApplicationTitle, Tools::fn_callback_t fnMinimizeCallback, Tools::fn_callback_t fnCloseCallback )
			{
				nk_layout_row_dynamic( pContext, 30, 0 );
				auto pOutput = nk_window_get_canvas( pContext );
				auto pInput = &pContext->input;
				constexpr nk_color clrBlueHover { 115, 189, 247, 255 };
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
				auto vecApplicationTitle = CalculateTextBounds( szApplicationTitle, 30 );
				nk_widget_text( pOutput, nk_rect( 23 + vecTitle.x, 7, vecApplicationTitle.x, 30 ), szApplicationTitle, strlen( szApplicationTitle ), &txtApplication, NK_TEXT_CENTERED, pContext->style.font );

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
				if ( GetActiveWindow( ) != Render::hwWindowHandle || Render::bMinimized || Tools::GetMoment( ) - Render::mmtRestoreWindow < 500u )
					return;

				static auto fnSetWidgetActive = [ & ]( )
				{
					pContext->last_widget_state |= NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER;
					bFoundHoverTarget = true;
					curCurrent = Render::CURSOR_HAND;
				};

				if ( bHoveringMinimize )
				{
					clrMinimize = clrBlueHover;
					fnSetWidgetActive( );
					if ( bClicking )
					{
						if ( Render::bCreatedWindow )
						{
							Render::bMinimized = true;
							ShowWindow( Render::hwWindowHandle, SW_MINIMIZE );
						}
						fnMinimizeCallback( );
					}
				}
				else
					clrMinimize = clrBlue;

				if ( bHoveringClose )
				{
					clrClose = clrBlueHover;
					fnSetWidgetActive( );
					if ( bClicking )
						fnCloseCallback( );
				}
				else
					clrClose = clrBlue;
			}

			bool PX_API PrimaryTab( Tools::cstr_t szText, bool bActive )
			{
				return nk_button_label_styled( pContext, bActive ? &btnTopActive : &btnTop, szText );
			}

			bool SecondaryTab( Tools::cstr_t szText, bool bActive )
			{
				if ( bActive )
				{
					auto rcBoundaries = nk_widget_bounds( pContext );
					auto pOutput = nk_window_get_canvas( pContext );
					nk_fill_rect_multi_color( pOutput, rcBoundaries, clrBorder, clrDarkBackground, clrDarkBackground, clrBorder );

					rcBoundaries.w += rcBoundaries.x;
					rcBoundaries.h += rcBoundaries.y;
					SetFont( FONT_TAHOMABOLD );
					const auto bResult = nk_button_label_styled( pContext, &btnRegularActive, szText );
					HoverCheck( Render::CURSOR_HAND );
					SetFont( FONT_TAHOMA );
					nk_stroke_line( pOutput, rcBoundaries.x + 2, rcBoundaries.y, rcBoundaries.x + 2, rcBoundaries.h, 2, clrBlue );
					return bResult;
				}
				SetFont( FONT_TAHOMA );
				const auto bReturn = nk_button_label_styled( pContext, &btnRegular, szText );
				HoverCheck( Render::CURSOR_HAND );
				return bReturn;
			}

			void Separator( float bRed, float bGreen, float bBlue, unsigned uStartHeight, unsigned uRowSize /*= 3*/, bool bUpperBorder /*= false*/ )
			{
				constexpr auto uSeparatorHeight = 42u;
				constexpr struct nk_color clrBorderColor = { 85, 88, 94, 255 };
				const auto pDrawBuffer = nk_window_get_canvas( pContext );
				nk_fill_rect( pDrawBuffer, nk_rect( 0, uStartHeight, Render::uWindowWidth, uSeparatorHeight ), 0.f, nk_rgba( bRed, bGreen, bBlue, 255 ) );
				nk_stroke_line( pDrawBuffer, 0, uStartHeight + uSeparatorHeight - 1, pContext->current->bounds.w, uStartHeight + uSeparatorHeight - 1, 0.5, clrBorderColor );

				if ( bUpperBorder )
					nk_stroke_line( pDrawBuffer, 0, uStartHeight + 1, pContext->current->bounds.w, uStartHeight + 1, 0.5, clrBorderColor );
			}

			void PX_API BeginRow( unsigned uRowHeight, unsigned uColumns, ERowType rowRowType )
			{
				static std::function< void( PX_API )( nk_context*, nk_layout_format, float, int ) > fnBeginRow[ ROW_MAX ]
				{
					nk_layout_row_begin,
					nk_layout_row_begin,
					nk_layout_space_begin
				};

				rowLastRowType = rowRowType;
				iCurrentRowUsedColumns = 0;
				iCurrentRowMaxColumns = uColumns;

				return fnBeginRow[ rowRowType ]( pContext, rowRowType == ROW_DYNAMIC ? NK_DYNAMIC : NK_STATIC, uRowHeight, uColumns );
			}

			void PX_API EndRow( )
			{
				static std::function< void( PX_API )( nk_context* ) > fnEndRow[ ROW_MAX ]
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
}
