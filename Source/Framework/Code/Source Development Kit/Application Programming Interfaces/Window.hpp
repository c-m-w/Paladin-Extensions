/// Window.hpp

#pragma once

LRESULT CALLBACK DefaultWindowInputProcessor( HWND, UINT, WPARAM, LPARAM );

class CWindow
{
private:

	WNDCLASSEX _WindowInformation { };
	HWND hwHandle;
	void* pOldWindowInputProcessor;

public:

	static std::vector< HWND > GetCurrentProcessWindows( );

	CWindow( const std::string& strTitle, const Utilities::vector2_t& vecSize, HINSTANCE hModule, WNDPROC _WindowInputProcessor = DefaultWindowInputProcessor );
	CWindow( const HWND& hwWindow, WNDPROC _WindowInputProcessor = DefaultWindowInputProcessor );
	~CWindow( );

	HWND GetWindowHandle( );
};
