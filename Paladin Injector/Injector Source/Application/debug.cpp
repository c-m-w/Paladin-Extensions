#include "../main.h"

Debug *dbg = nullptr;

Debug::~Debug( )
{
#ifndef _DEBUG
	return;
#endif

	//Free console
	FreeConsole( );

	//Restore handles
	SetStdHandle( STD_INPUT_HANDLE, hIn );
	SetStdHandle( STD_OUTPUT_HANDLE, hOut );
	//SetStdHandle(STD_ERROR_HANDLE	, hErr);
}

bool Debug::Init( )
{
#ifndef _DEBUG
	initialized = true;
#endif

	if ( initialized )
		return true;

	HWND con = nullptr;
	HMENU conMenu = nullptr;
	long conLong = NULL;
	long conExLong = NULL;
	CONSOLE_FONT_INFOEX conFont = { NULL };
	CONSOLE_CURSOR_INFO conCursor = { NULL };

	//Create console
	if ( !AllocConsole( ) )
		return false;

	//Get handles
	hIn = GetStdHandle( STD_INPUT_HANDLE );
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	//hErr = GetStdHandle(STD_ERROR_HANDLE);

	//Get console window
	con = GetConsoleWindow( );

	if ( !con )
		return false;

	//Get console menu
	conMenu = GetSystemMenu( con, false );

	if ( !conMenu )
		return false;

	//Get window styles
	conLong = GetWindowLong( con, GWL_STYLE );

	if ( !conLong )
		return false;

	conExLong = GetWindowLong( con, GWL_EXSTYLE );

	if ( !conExLong )
		return false;

	//Redirect IO
	errIn = _wfreopen_s( &chIn, L"CONIN$", L"r", stdin );
	errOut = _wfreopen_s( &chOut, L"CONOUT$", L"w", stdout );
	//errErr	= _wfreopen_s(&chErr,	L"CONERR$",		L"w", stderr);

	if ( errIn || errOut /*|| errErr*/ )
		return false;

	//Set console title
	if ( !SetConsoleTitle( L"Paladin CSGO" ) )
		return false;

	//Set console window style
	if ( EnableMenuItem( conMenu, SC_CLOSE, MF_GRAYED ) == -1 )
		return false;

	if ( !SetWindowLong( con, GWL_STYLE, conLong & ~SC_CLOSE & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX ) )
		return false;

	if ( !SetWindowLong( con, GWL_EXSTYLE, conExLong | WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE & ~WS_EX_APPWINDOW & ~WS_EX_CLIENTEDGE & ~WS_EX_ACCEPTFILES ) )
		return false;

	//Set console font
	conFont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	conFont.dwFontSize.X = 6;
	conFont.dwFontSize.Y = 8;

	if ( wcscpy_s( conFont.FaceName, L"Terminal" ) )
		return false;

	if ( !SetCurrentConsoleFontEx( hOut, 0, &conFont ) )
		return false;

	//Set console cursor
	conCursor.dwSize = 25;
	conCursor.bVisible = false;

	if ( !SetConsoleCursorInfo( hOut, &conCursor ) )
		return false;

	//Sync IO
	//std::ios::sync_with_stdio();

	//Print start
	if ( color == MONO )
		SetConsoleTextAttribute( hOut, 7 );
	else
		SetConsoleTextAttribute( hOut, 11 );

	wprintf_s( L"[BGN] " );

	if ( color == DUAL )
		SetConsoleTextAttribute( hOut, 7 );

	wprintf_s( L"Paladin Debug Console Created\n" );

	//Assume all is well at this point
	initialized = true;
	return true;
}

void Debug::LogDebugMsg( DebugMessage type, wchar_t *msg, ... )
{
#ifndef _DEBUG
	return;
#endif

	if ( !initialized )
		return;

	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	if ( hConsole == INVALID_HANDLE_VALUE )
		return;

	if ( color == MONO )
		SetConsoleTextAttribute( hConsole, 7 );

	//Set console color
	switch ( type )
	{
		case DBG:
			if ( color != MONO )
				SetConsoleTextAttribute( hConsole, 15 );
			wprintf_s( L"\n[DBG] " );
			break;
		case SCS:
			if ( color != MONO )
				SetConsoleTextAttribute( hConsole, 10 );
			wprintf_s( L"\n[SCS] " );
			break;
		case WRN:
			if ( color != MONO )
				SetConsoleTextAttribute( hConsole, 14 );
			wprintf_s( L"\n[WRN] " );
			break;
		case ERR:
			if ( color != MONO )
				SetConsoleTextAttribute( hConsole, 12 );
			wprintf_s( L"\n[ERR] " );
			break;
		case LER:
			if ( color != MONO )
				SetConsoleTextAttribute( hConsole, 12 );
			wprintf_s( L"\n[LER] " );
			break;
		default:
			if ( color != MONO )
				SetConsoleTextAttribute( hConsole, 15 );
			wprintf_s( L"\n[DBG] " );
	}

	if ( color != FULL )
		SetConsoleTextAttribute( hConsole, 7 );

	//Get arguments
	wchar_t cBuffer[2048] = { '\0' };

	va_list vaList;
	va_start(vaList, msg);
	_vsnwprintf_s( cBuffer, sizeof cBuffer, msg, vaList );
	va_end(vaList);

	//Output data
	wprintf_s( cBuffer );
}

// Look up errors here: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx
void Debug::LogLastErrorA( )
{
#ifndef _DEBUG
	return;
#endif

	if ( !initialized )
	{
		if ( allowSecondaryReporting )
			LogLastErrorB( );
		return;
	}

	DWORD error = GetLastError( );
	LPWSTR errorString = nullptr;

	if ( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast< LPWSTR >( &errorString ), 0, nullptr ) )
		LogDebugMsg( LER, L"[%lu] - Unable to retrieve error description", error );
	else
		LogDebugMsg( LER, L"[%lu] - %s", error, errorString );

	LocalFree( errorString );
}

void Debug::LogLastErrorB( )
{
#ifndef _DEBUG
	return;
#endif

	DWORD error = GetLastError( );
	LPWSTR errorString = nullptr;
	wchar_t cBuffer[2048] = { '\0' };

	if ( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast< LPWSTR >( &errorString ), 0, nullptr ) )
		wsprintf( cBuffer, L"[%lu] - Unable to retrieve error description", error );
	else
		wsprintf( cBuffer, L"[%lu] - %sn", error, errorString );

	LocalFree( errorString );

	MessageBox( nullptr, cBuffer, L"Last Error", MB_OK );
}
