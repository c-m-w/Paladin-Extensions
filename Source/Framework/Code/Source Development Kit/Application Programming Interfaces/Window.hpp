/// Window.hpp

#pragma once

LRESULT CALLBACK DefaultWindowInputProcessor( HWND, UINT, WPARAM, LPARAM );

class CApplicationWindow
{
private:

	WNDCLASSEX _WindowInformation { };
	HWND hwHandle;
	void *pOldWindowInputProcessor;
	static inline std::map< HWND, void* > _HookedWindowProcessors { };

public:

	CApplicationWindow( const std::string &strTitle, const Utilities::vector2_t &vecSize, HINSTANCE hModule, WNDPROC _WindowInputProcessor = DefaultWindowInputProcessor );
	CApplicationWindow( const HWND &hwWindow, WNDPROC _WindowInputProcessor = DefaultWindowInputProcessor );
	~CApplicationWindow( );

	bool PollInput( );
	HWND GetWindowHandle( );
	bool GetBounds( RECT &recOut );
	bool Move( int iHorizontalAmount, int iVerticalAmount );
	bool Resize( int iWidth, int iHeight );
	bool SetTitle( const std::string &strTitle );
	void Hide( );
	void Show( );
	void Destroy( );
	bool CursorOnWindow( );
	void Minimize( );

	friend LRESULT CALLBACK DefaultWindowInputProcessor( HWND, UINT, WPARAM, LPARAM );
};
