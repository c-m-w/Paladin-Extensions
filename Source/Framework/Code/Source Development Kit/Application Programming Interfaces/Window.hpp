/// Window.hpp

#pragma once

LRESULT CALLBACK DefaultWindowInputProcessor( HWND, UINT, WPARAM, LPARAM );

class CApplicationWindow
{
private:

	WNDCLASSEX _WindowInformation { };
	HWND hwHandle;
	void *pOldWindowInputProcessor;

public:

	static std::vector< HWND > GetCurrentProcessWindows( );

	CApplicationWindow( const std::string &strTitle, const Utilities::vector2_t &vecSize, HINSTANCE hModule, WNDPROC _WindowInputProcessor = DefaultWindowInputProcessor );
	CApplicationWindow( const HWND &hwWindow, WNDPROC _WindowInputProcessor = DefaultWindowInputProcessor );
	~CApplicationWindow( );

	bool PollInput( );
	HWND GetWindowHandle( );
	bool GetBounds( RECT& recOut );
	bool Move( int iHorizontalAmount, int iVerticalAmount );
	void Hide( );
	void Show( );
};
