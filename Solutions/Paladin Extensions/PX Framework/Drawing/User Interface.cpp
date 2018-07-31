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

			Tools::cstr_t	szWindowTitle = "Paladin Extensions";
			auto			szApplicationTitle = static_cast< char* >( malloc( 32 ) );

			nk_font_atlas* pAtlas;
			struct nk_font *pTahoma, *pTahomaBold, *pRoboto, *pRobotoBold, *pRobotoSmall, *pRobotoBoldSmall, *pEnvy;
			struct nk_rect recComboboxWindowBounds;

			constexpr nk_color clrTextActive { 255, 255, 255, 255 },	clrBlue { 33, 150, 243, 255 },		clrDarkBlue { 43, 60, 75, 255 },	clrBackground { 56, 60, 66, 255 },	clrLightBackground { 61, 65, 72, 255 },
							   clrDarkBackground { 45, 50, 56, 255 },	clrBorder { 80, 84, 89, 255 },		clrToolbox { 42, 44, 48, 255 },		clrHeader { 33, 36, 40, 255 },		clrBlueActive { 54, 70, 84, 255 },
							   clrBlueHover { 54, 70, 84, 200 },		clrBlueDormant { 43, 60, 75, 255 };
			nk_color clrColorTable[ NK_COLOR_COUNT ] { };

			nk_style_button btnTopActive { }, btnTop { }, btnRegularActive { }, btnRegular { }, btnSpecialActive { }, btnSpecial { }, btnCombo { }, btnComboActive { };

			Render::ECursor curCurrent;

			bool bFoundHoverTarget = false;

			nk_font* PX_API AddFont( std::string strFontFileName, unsigned uFontSize, struct nk_font_config fcFontConfiguration, unsigned uFontAwesomeSize = 0 )
			{
				static auto strFontDirectory = Tools::string_cast< std::string >( Tools::GetDirectory( 3 ) + /*PX_XOR*/( LR"(\Resources\Fonts\)" ) );

				nk_d3d9_font_stash_begin( &pAtlas );
				auto pFont = nk_font_atlas_add_from_file( pAtlas, ( strFontDirectory + strFontFileName ).c_str( ), float( uFontSize ), nullptr );
				nk_font_atlas_add_from_file( pAtlas, ( strFontDirectory + /*PX_XOR*/( "FontAwesome.ttf" ) ).c_str( ), uFontAwesomeSize ? float( uFontAwesomeSize ) : float( uFontSize ), &fcFontConfiguration );
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

				pRoboto = AddFont( /*PX_XOR*/( "Roboto.ttf" ), 21, fcFontAwesomeConfiguration );
				pRobotoBold = AddFont( /*PX_XOR*/( "RobotoBold.ttf" ), 21, fcFontAwesomeConfiguration );
				pRobotoSmall = AddFont( /*PX_XOR*/( "Roboto.ttf" ), 16, fcFontAwesomeConfiguration, 14 );
				pRobotoBoldSmall = AddFont( /*PX_XOR*/( "RobotoBold.ttf" ), 16, fcFontAwesomeConfiguration, 12 );
				pTahoma = AddFont( /*PX_XOR*/( "Tahoma.ttf" ), 16, fcFontAwesomeConfiguration );
				pTahomaBold = AddFont( /*PX_XOR*/( "TahomaBold.ttf" ), 16, fcFontAwesomeConfiguration );
				pEnvy = AddFont( /*PX_XOR*/( "Envy.ttf" ), 14, fcFontAwesomeConfiguration );

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
                szWindowTitle = szApplicationTitle;
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

	        void PX_API Header( Tools::cstr_t szTitle, Tools::cstr_t szApplicationTitle, std::function< void( PX_API )( ) > fnMinimizeCallback, std::function< void( PX_API )( ) > fnCloseCallback )
			{
				static const unsigned uWidth = unsigned( pContext->current->bounds.w );
				auto pRenderBuffer = nk_window_get_canvas( pContext );
				auto pInput = &pContext->input;
				static const auto clrActive = nk_rgba( 155, 189, 247, 255 );
				static auto clrClose = clrBlue, clrMinimize = clrBlue;

				BeginRow( 30, 4, ROW_CUSTOM );
				const int  iTitleWidth				= int( CalculateTextBounds( szTitle, 30 ).x ),
						   iApplicationTitleWidth	= int( CalculateTextBounds( szApplicationTitle, 30 ).x ),
						   iMinimizeButtonWidth		= int( CalculateTextBounds( ICON_FA_MINUS, 30 ).x ),
						   iCloseButtonWidth		= int( CalculateTextBounds( ICON_FA_TIMES, 30 ).x );

				PushCustomRow( 5, 5, iTitleWidth, 30 );
				nk_label( pContext, szTitle, NK_TEXT_CENTERED );
				PushCustomRow( 5 + iTitleWidth, 5, iApplicationTitleWidth, 30 );
				nk_label( pContext, szApplicationTitle, NK_TEXT_CENTERED );
				PushCustomRow( uWidth - iCloseButtonWidth - 5 - iMinimizeButtonWidth, 5, iCloseButtonWidth, 30 );

				const auto vecMinimizeButtonBounds = nk_widget_bounds( pContext );

				nk_label_colored( pContext, ICON_FA_MINUS, NK_TEXT_CENTERED, clrMinimize );
				PushCustomRow( uWidth - iCloseButtonWidth - 5, 5, iCloseButtonWidth, 30 );

				const auto vecCloseButtonBounds = nk_widget_bounds( pContext );

				nk_label_colored( pContext, ICON_FA_TIMES, NK_TEXT_CENTERED, clrClose );

				const bool bHoveringMinimizeButton = nk_input_is_mouse_hovering_rect( pInput, vecMinimizeButtonBounds ),
						   bHoveringCloseButton = nk_input_is_mouse_hovering_rect( pInput, vecCloseButtonBounds ),
						   bClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == CInputManager::EKeyState::DOWN;

				static auto fnSetWidgetActive = [ & ]( )
				{
					pContext->last_widget_state |= NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER;
					bFoundHoverTarget = true;
					curCurrent = Render::CURSOR_HAND;
				};

				if ( bHoveringMinimizeButton )
				{
					clrMinimize = clrActive;
					fnSetWidgetActive( );
					if ( bClicking )
						fnMinimizeCallback( );
				}
				else
					clrMinimize = clrBlue;

				if ( bHoveringCloseButton )
				{
					clrClose = clrActive;
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

			void PX_API BeginRow( unsigned uRowHeight, unsigned uColumns, ERowType rowRowType )
			{
				static std::function< void( PX_API )( unsigned _uRowHeight, unsigned _uColumns ) > fnBeginRow[ ROW_MAX ]
				{
					[ ]( unsigned _uRowHeight, unsigned _uColumns )
					{
						return nk_layout_row_begin( pContext, NK_DYNAMIC, float( _uRowHeight ), _uColumns );
					},
					[ ]( unsigned _uRowHeight, unsigned _uColumns )
					{
						return nk_layout_row_begin( pContext, NK_STATIC, float( _uRowHeight ), _uColumns );
					},
					[ ]( unsigned _uRowHeight, unsigned _uColumns )
					{
						return nk_layout_space_begin( pContext, NK_STATIC, float( _uRowHeight ), _uColumns );
					},
				};

				rowLastRowType = rowRowType;
				iCurrentRowUsedColumns = 0;
				iCurrentRowMaxColumns = uColumns;

				return fnBeginRow[ rowRowType ]( uRowHeight, uColumns );
			}

			void PX_API EndRow( )
			{
				static std::function< void( PX_API )( ) > fnEndRow[ ROW_MAX ]
				{
					[ ]( )
					{
						return nk_layout_row_end( pContext );
					},
					[ ]( )
					{
						return nk_layout_row_end( pContext );
					},
					[ ]( )
					{
						return nk_layout_space_end( pContext );
					},
				};

				dbg::Assert( iCurrentRowUsedColumns == iCurrentRowMaxColumns );
				fnEndRow[ rowLastRowType ]( );
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
