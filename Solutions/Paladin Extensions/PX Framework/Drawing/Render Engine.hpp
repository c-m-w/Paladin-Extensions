/// Render.hpp

#pragma once

/** \brief Contains utilities to render an interface for the user to the screen. */
namespace PX::Render
{
	/** \brief Types of available cursors. */
	enum ECursor
	{
		CURSOR_NONE,
		CURSOR_ARROW,
		CURSOR_HAND,
		CURSOR_IBEAM,
		CURSOR_MAX
	};

	/** \brief Title of the window that will be created. */
	PX_SDK wcstr_t wszWindowTitle = static_cast< wchar_t* >( malloc( 32 ) );
	/** \brief Width of the window. */
	PX_SDK unsigned uWindowWidth;
	/** \brief Height of the window. */
	PX_SDK unsigned uWindowHeight;
	/** \brief Window class containing information about how we want our window to function. */
	PX_SDK WNDCLASSEX wndWindow { sizeof( WNDCLASSEX ), CS_DBLCLKS, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr, nullptr, wszWindowTitle, nullptr };
	/** \brief Handle to the created window. */
	PX_SDK HWND hwWindowHandle;

	PX_SDK D3DPRESENT_PARAMETERS dxParameters;
	PX_SDK IDirect3D9Ex* pObjectEx;
	PX_SDK IDirect3DDevice9* pDevice;
	/** \brief Used to decide how to handle window related events. */
	PX_SDK auto bCreatedWindow = false;
	/** \brief Tracks whether or not the window is currently minimized. */
	PX_SDK auto bMinimized = false;
	/** \brief Resizes the created window. */
	/**	\param uWidth New width of the window. */
	/**	\param uHeight New height of the window. */
	void PX_API SetWindowSize( unsigned uWidth, unsigned uHeight );
	/** \brief Creates a window and sets up the ability to render to it. */
	/**	\param pDimensions Array of the dimensions of the render target, elements being in order width, height. */
	/**	\param szNewWindowTitle Title of the window. */
	void PX_API InitializeRenderTarget( unsigned* pDimensions, wcstr_t szNewWindowTitle = nullptr );

	/** \brief The address of the old Window Proc. */
	PX_SDK ptr_t uOldWindowProc;
	/** \brief HWND of the window which we set the Window Proc for. */
	PX_SDK HWND hwOldWindowHandle;
	/** \brief Set the Window Proc of the HWND being used by a d3d device, to receive input from the window through our WndProc function. */
	/** \param pTargetDevice Device to get the HWND from to retarget the Window Proc. */
	void PX_API SetWindowProc( IDirect3DDevice9* pTargetDevice );
}
