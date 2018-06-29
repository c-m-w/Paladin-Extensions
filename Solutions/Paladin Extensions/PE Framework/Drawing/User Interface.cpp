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

#define M_ITEM_WIDTH 15
#define M_ITEM_HEIGHT 25
#define M_DYNAMIC_HEIGHT 25
#define M_TOOLTIP_DELAY 20

namespace Paladin
{
	LRESULT WINAPI WndProc( HWND hwWindowHandle, UINT uMessage, WPARAM uwParam, LPARAM llParam )
	{
		ui->OnEvent( hwWindowHandle, uMessage, uwParam, llParam );

		switch ( uMessage )
		{
			case WM_DESTROY:
				PostQuitMessage( 0 );
				return 0;

			case WM_SIZE:
				if ( ui->pDevice )
				{
					const auto uWidth = LOWORD( llParam ); // over-using auto
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

	CUserInterface::SWidget::SWidget( std::string strText, std::string strTooltip )
	{
		wgtWidgetType = TEXT_BOX;
		this->strText = strText;
		this->strTooltip = strTooltip;
	}

	CUserInterface::SWidget::SWidget( std::string strText, std::string strTooltip, unsigned uAlignment )
	{
		wgtWidgetType = LABEL;
		this->strText = strText;
		this->strTooltip = strTooltip;
		this->uAlignment = uAlignment;
	}

	CUserInterface::SWidget::SWidget( std::string strText, std::string strTooltip, std::function< void( ) > fnCallback )
	{
		wgtWidgetType = BUTTON;
		this->strText = strText;
		this->strTooltip = strTooltip;
		this->fnCallback = fnCallback;
	}

	CUserInterface::SWidget::SWidget( std::string strText, std::string strTooltip, int *iActive )
	{
		wgtWidgetType = CHECK_BOX;
		this->strText = strText;
		this->strTooltip = strTooltip;
		this->pActive = iActive;
	}

	CUserInterface::SWidget::SWidget( std::string strText, std::string strTooltip, const char *pItems[ ], int iItems, int iSelected )
	{
		wgtWidgetType = COMBO_BOX;
		this->strText = strText;
		this->strTooltip = strTooltip;
		this->pItems = pItems;
		this->iItems = iItems;
		this->iSelected = iSelected;
	}

	CUserInterface::SWidget::SWidget( std::string strText, std::string strTooltip, bool bUseAlpha, BYTE *bColor )
	{
		wgtWidgetType = COLOR_PICKER;
		this->strText = strText;
		this->strTooltip = strTooltip;
		this->bUseAlpha = bUseAlpha;
		for ( int i = 0; i < 4; i++ )
			this->bColor[ i ] = bColor[ i ];
	}

	CUserInterface::SWidget::SWidget( std::string strText, std::string strTooltip, int iMinimum, int iValue, int iMaximum, int iStep )
	{
		wgtWidgetType = INT_SLIDER;
		this->strText = strText;
		this->strTooltip = strTooltip;
		this->iMinimum = iMinimum;
		this->iValue = iValue;
		this->iMaximum = iMaximum;
		this->iStep = iStep;
	}

	CUserInterface::SWidget::SWidget( std::string strText, std::string strTooltip, float flMinimum, float flValue, float flMaximum, float flStep )
	{
		wgtWidgetType = FLOAT_SLIDER;
		this->strText = strText;
		this->strTooltip = strTooltip;
		this->flMinimum = flMinimum;
		this->flValue = flValue;
		this->flMaximum = flMaximum;
		this->flStep = flStep;
	}

	CUserInterface::CUserInterface( const char *szDesiredNuklearWindowTitle, unsigned *uDesiredWindowSize, const wchar_t *szDesiredWindowClassTitle )
		: pContext { }, fcFontConfiguration { }, pAtlas { }, pFontAwesome { }, pTahoma { }, pRoboto { }
	{
		szNuklearWindowTitle = szDesiredNuklearWindowTitle;
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

	void CUserInterface::InitializeNuklear( )
	{
		pContext = nk_d3d9_init( pDevice, uWindowWidth, uWindowHeight );
		fcFontConfiguration = new struct nk_font_config;
		*fcFontConfiguration = nk_font_config( 14 );
		fcFontConfiguration->oversample_h = 1;
		fcFontConfiguration->oversample_v = 1;
		fcFontConfiguration->range = nk_font_default_glyph_ranges( );

		nk_d3d9_font_stash_begin( &pAtlas );
		pFontAwesome = nk_font_atlas_add_from_file( pAtlas, M_XOR( R"(C:\Windows\Fonts\fontawesome-webfont.ttf)" ), 16, fcFontConfiguration );
		pTahoma = nk_font_atlas_add_from_file( pAtlas, M_XOR( R"(C:\Windows\Fonts\Tahoma.ttf)" ), 16, fcFontConfiguration );
		pRoboto = nk_font_atlas_add_from_file( pAtlas, M_XOR( R"(C:\Windows\Fonts\Roboto-Regular.ttf)" ), 20, fcFontConfiguration );
		nk_d3d9_font_stash_end( );

		struct nk_color clrColors[ NK_COLOR_COUNT ];
		clrColors[ NK_COLOR_TEXT ] = nk_rgba( 210, 210, 210, 255 );
		clrColors[ NK_COLOR_WINDOW ] = nk_rgba( 56, 60, 66, 255 );
		clrColors[ NK_COLOR_HEADER ] = nk_rgba( 56, 60, 66, 255 );
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

	bool CUserInterface::DrawUserInterface( )
	{
		nk_style_set_font( pContext, &pRoboto->handle );
		if ( nk_begin( pContext, szNuklearWindowTitle, nk_rect( 0, 0, float( uWindowWidth ), float( uWindowHeight ) ),
					   NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_CLOSABLE | NK_WINDOW_NO_SCROLLBAR )
			 && HandleWindowInput( ) )
		{
			if ( !dqWidgets.empty( ) )
				for ( auto dqWidget : dqWidgets )
				{
					nk_layout_row_dynamic( pContext, M_DYNAMIC_HEIGHT, 3 );
					switch ( dqWidget.wgtWidgetType )
					{
						case SWidget::LABEL:
							nk_label( pContext, dqWidget.strText.c_str( ), dqWidget.uAlignment );
							{
								static int iHover;
								if ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) )
								{
									SetActiveCursor( HAND );
									if ( iHover > M_TOOLTIP_DELAY )
										nk_tooltip( pContext, dqWidget.strTooltip.c_str( ) );
									iHover++;
								}
								else
									iHover = 0;
							}
							break;
						case SWidget::BUTTON:
							if ( nk_button_label( pContext, dqWidget.strText.c_str( ) ) )
								dqWidget.fnCallback( );
							{
								static int iHover;
								if ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) )
								{
									SetActiveCursor( HAND );
									if ( iHover > M_TOOLTIP_DELAY )
										nk_tooltip( pContext, dqWidget.strTooltip.c_str( ) );
									iHover++;
								}
								else
									iHover = 0;
							}
							break;
						case SWidget::TEXT_BOX:
							nk_edit_string_zero_terminated( pContext, NK_EDIT_BOX | NK_EDIT_AUTO_SELECT | NK_EDIT_NO_HORIZONTAL_SCROLL | NK_TEXT_EDIT_SINGLE_LINE,
															&dqWidget.strText[ 0 ], 16, nk_filter_ascii );
							{
								static int iHover;
								if ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) )
								{
									SetActiveCursor( IBEAM );
									if ( iHover > M_TOOLTIP_DELAY )
										nk_tooltip( pContext, dqWidget.strTooltip.c_str( ) );
									iHover++;
								}
								else
									iHover = 0;
							}
							break;
						case SWidget::CHECK_BOX:
							nk_checkbox_label( pContext, dqWidget.strText.c_str( ), dqWidget.pActive );
							{
								static int iHover;
								if ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) )
								{
									SetActiveCursor( HAND );
									if ( iHover > M_TOOLTIP_DELAY )
										nk_tooltip( pContext, dqWidget.strTooltip.c_str( ) );
									iHover++;
								}
								else
									iHover = 0;
							}
							break;
						case SWidget::COMBO_BOX:
							nk_combobox( pContext, dqWidget.pItems, dqWidget.iItems, &dqWidget.iSelected, M_ITEM_HEIGHT, { M_ITEM_WIDTH, M_ITEM_HEIGHT } );
							{
								static int iHover;
								if ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) )
								{
									SetActiveCursor( HAND );
									if ( iHover > M_TOOLTIP_DELAY )
										nk_tooltip( pContext, dqWidget.strTooltip.c_str( ) );
									iHover++;
								}
								else
									iHover = 0;
							}
							break;
						case SWidget::COLOR_PICKER:
							nk_color_picker( pContext, { float( int( dqWidget.bColor[ 0 ] ) ), float( int( dqWidget.bColor[ 1 ] ) ),
														 float( int( dqWidget.bColor[ 2 ] ) ), float( int( dqWidget.bColor[ 3 ] ) ) },
											 dqWidget.bUseAlpha ? NK_RGBA : NK_RGB );
							{
								static int iHover;
								if ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) )
								{
									SetActiveCursor( HAND );
									if ( iHover > M_TOOLTIP_DELAY )
										nk_tooltip( pContext, dqWidget.strTooltip.c_str( ) );
									iHover++;
								}
								else
									iHover = 0;
							}
							break;
						case SWidget::INT_SLIDER:
							nk_slider_int( pContext, dqWidget.iMinimum, &dqWidget.iValue, dqWidget.iMaximum, dqWidget.iStep );
							{
								static int iHover;
								if ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) )
								{
									SetActiveCursor( HAND );
									if ( iHover > M_TOOLTIP_DELAY )
										nk_tooltip( pContext, dqWidget.strTooltip.c_str( ) );
									iHover++;
								}
								else
									iHover = 0;
							}
							break;
						case SWidget::FLOAT_SLIDER:
							nk_slider_float( pContext, dqWidget.flMinimum, &dqWidget.flValue, dqWidget.flMaximum, dqWidget.flStep );
							{
								static int iHover;
								if ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) )
								{
									SetActiveCursor( HAND );
									if ( iHover > M_TOOLTIP_DELAY )
										nk_tooltip( pContext, dqWidget.strTooltip.c_str( ) );
									iHover++;
								}
								else
									iHover = 0;
							}
							break;
						case SWidget::NONE:
						default:
							throw std::exception( "Unknown widget type" );
					}
				}
		}
		else
			bShouldDrawInterface = false; // Top right 'x' button has been clicked.
		nk_end( pContext );

		RenderUserInterface( );
		return bShouldDrawInterface;
	}
}
