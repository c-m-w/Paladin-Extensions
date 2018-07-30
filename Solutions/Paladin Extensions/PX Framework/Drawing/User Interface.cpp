/// User Interface.cpp

#define PX_NUKLEAR_IMPLEMENTATION

#include "../PX Framework.hpp"

namespace Paladin
{
    namespace UI
    {
		namespace Manager
		{
			using PX::Render::pDevice;
			using PX::Render::dxParameters;

			LRESULT WINAPI WndProc( HWND hwWindowHandle, UINT uMessage, WPARAM uwParam, LPARAM llParam )
			{
				PX_INPUT.OnEvent( hwWindowHandle, uMessage, uwParam, llParam );

				switch ( uMessage )
				{
					case WM_SETCURSOR:
						if ( llParam == HTCLIENT )
							return true;

					case WM_DESTROY:
						PostQuitMessage( 0 );
						return 0;

					case WM_SIZE:
						if ( pDevice )
						{
							const auto uWidth = LOWORD( llParam );
							const auto uHeight = HIWORD( llParam );
							if ( uWidth != 0 && uHeight != 0 &&
								( uWidth != dxParameters.BackBufferWidth || uHeight != dxParameters.BackBufferHeight ) )
							{
								nk_d3d9_release( );
								dxParameters.BackBufferWidth = uWidth;
								dxParameters.BackBufferHeight = uHeight;
								const auto hrReset = pDevice->Reset( &dxParameters );
								PX::dbg::Assert( hrReset >= 0 );
								nk_d3d9_resize( uWidth, uHeight );
							}
						}
						break;
					default:
						break;
				}
			}
		}

        namespace Widgets
        {

        }
    }
}
