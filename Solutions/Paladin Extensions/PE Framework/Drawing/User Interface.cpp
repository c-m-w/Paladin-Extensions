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
    LRESULT WINAPI WndProc( HWND hwHWND, UINT uMessage, WPARAM uwParam, LPARAM llParam )
    {
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
        }

        if ( nk_d3d9_handle_event( hwHWND, uMessage, uwParam, llParam ) )
            return 0;

        return DefWindowProcW( hwHWND, uMessage, uwParam, llParam );
    }

    CUserInterface::CUserInterface( const char *szDesiredNuklearWindowTitle, unsigned uDesiredWindowSize[ 2 ] )
    {
        szNuklearWindowTitle = szDesiredNuklearWindowTitle;
        SetWindowSize( uDesiredWindowSize[ 0 ], uDesiredWindowSize[ 1 ] );
    }

    void CUserInterface::InitializeNuklear( )
    {
        pContext = nk_d3d9_init( pDevice, uWindowWidth, uWindowHeight );
        *fcFontConfiguration = nk_font_config( 14 );
        fcFontConfiguration->oversample_h = 1;
        fcFontConfiguration->oversample_v = 1;
        fcFontConfiguration->range = nk_font_default_glyph_ranges( );

        nk_d3d9_font_stash_begin( &pAtlas );
        pFontAwesome = nk_font_atlas_add_from_file( pAtlas, XOR( R"(C:\Windows\Fonts\fontawesome-webfont.ttf)" ), 16, fcFontConfiguration );
        pTahoma = nk_font_atlas_add_from_file( pAtlas, XOR( R"(C:\Windows\Fonts\Tahoma.ttf)" ), 16, fcFontConfiguration );
        pRoboto = nk_font_atlas_add_from_file( pAtlas, XOR( R"(C:\Windows\Fonts\Roboto-Regular.ttf)" ), 20, fcFontConfiguration );
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
        CreateRenderTarget( );
        InitializeDirectX( );
        InitializeNuklear( );
    }

    void CUserInterface::HandleWindowInput( )
    {
        auto pos = nk_window_get_position( pContext );
        RECT rcWindowRectangle;
        GetWindowRect( hWnd, &rcWindowRectangle );

        rcWindowRectangle.top += int( pos.y );
        rcWindowRectangle.bottom += int( pos.y );
        rcWindowRectangle.left += int( pos.x );
        rcWindowRectangle.right += int( pos.x );

        SetWindowPos( hWnd, nullptr, rcWindowRectangle.left, rcWindowRectangle.top, uWindowWidth, uWindowHeight, SWP_SHOWWINDOW );
        nk_window_set_position( pContext, szNuklearWindowTitle, nk_vec2( 0, 0 ) );
    }

    void CUserInterface::RenderUserInterface( )
    {
        BeginRender( );
        nk_d3d9_render( NK_ANTI_ALIASING_ON );
        EndRender( );
    }

    void CUserInterface::DrawUserInterface( )
    {
        HandleWindowInput( );
        RenderUserInterface( );
    }

    CUserInterface *ui;
}
