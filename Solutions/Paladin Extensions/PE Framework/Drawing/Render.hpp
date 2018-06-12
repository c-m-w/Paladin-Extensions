/// Render.hpp

#pragma once

namespace Paladin
{
	LRESULT WINAPI WndProc( HWND, UINT, WPARAM, LPARAM );

	class CRender
	{
	protected:
		IDirect3D9Ex					*pObjectEx { };
		D3DDEVICE_CREATION_PARAMETERS	cpCreationParameters { };

		HWND			hWnd { nullptr };
		unsigned		uWindowWidth { }, uWindowHeight { };
		const unsigned  uTitleBarHeight { 25 };
		const long		uWindowStyle { WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_LAYERED };

		const unsigned	uScreenWidth = GetSystemMetrics( SM_CXSCREEN ), uScreenHeight = GetSystemMetrics( SM_CYSCREEN );
		const unsigned	uWindowStartPosition[ 2 ] { uScreenWidth / 2 - uWindowWidth / 2, uScreenHeight / 2 - uWindowHeight / 2 };
		wchar_t			*szWindowTitle { static_cast< wchar_t* >( malloc( 32 ) ) };
		WNDCLASSEX		wndWindow { sizeof( WNDCLASSEX ), NULL, WndProc , 0, 0, GetModuleHandle( nullptr ), nullptr,
			LoadCursor( nullptr, IDC_ARROW ), nullptr, nullptr, szWindowTitle, nullptr };

		void CreateRenderTarget( );
		virtual void InitializeDirectX( );
		void BeginRender( );
		void EndRender( );
	public:
		virtual ~CRender( ) = default;
		IDirect3DDevice9		*pDevice { };
		D3DPRESENT_PARAMETERS	dxParameters { };
		
		void SetWindowSize( unsigned, unsigned );
	};
}
