#include "main.h"

Debug *dbg = nullptr;

Debug::~Debug()
{
#ifndef m_DEBUG
	return;
#endif

	//Free console
	FreeConsole();
}

bool Debug::Init() 
{
#ifndef m_DEBUG
	initialized = true;
#endif

	if (initialized)
		return true;

	FILE *fp = nullptr;
	HANDLE lStdHandle = nullptr;
	HWND con = nullptr;
	HMENU conMenu = nullptr;
	long conLong = NULL;
	long conExLong = NULL;
	int conHandle = NULL;
	CONSOLE_FONT_INFOEX conFont = { NULL };
	CONSOLE_CURSOR_INFO conCursor = { NULL };

	//Create console
	if (!AllocConsole())
		return false;

	//Get handle
	lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Get console window
	con = GetConsoleWindow();

	if (!con)
		return false;

	//Get console menu
	conMenu = GetSystemMenu(con, false);

	if (!conMenu)
		return false;

	//Get window styles
	conLong = GetWindowLong(con, GWL_STYLE);

	if (!conLong)
		return false;

	conExLong = GetWindowLong(con, GWL_EXSTYLE);

	if (!conExLong)
		return false;

	//Redirect IO
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONERR$", "w", stderr);

	//Set console title
	if (!SetConsoleTitle("Paladin CSGO"))
		return false;

	//Set console window style
	if (EnableMenuItem(conMenu, SC_CLOSE, MF_GRAYED) == -1)
		return false;

	if (!SetWindowLong(con, GWL_STYLE, conLong & ~SC_CLOSE & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX))
		return false;

	if (!SetWindowLong(con, GWL_EXSTYLE, conExLong | WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE & ~WS_EX_APPWINDOW & ~WS_EX_CLIENTEDGE & ~WS_EX_ACCEPTFILES))
		return false;

	//Set console font
	conFont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	conFont.dwFontSize.X = 6;
	conFont.dwFontSize.Y = 8;

	if (wcscpy_s(conFont.FaceName, L"Terminal"))
		return false;

	if (!SetCurrentConsoleFontEx(lStdHandle, 0, &conFont))
		return false;

	//Set console cursor
	conCursor.dwSize = 25;
	conCursor.bVisible = false;

	if (!SetConsoleCursorInfo(lStdHandle, &conCursor))
		return false;

	//Sync IO
	//std::ios::sync_with_stdio();

	//Print start
	if (color == MONO)
		SetConsoleTextAttribute(lStdHandle, 7);
	else
		SetConsoleTextAttribute(lStdHandle, 11);

	printf("[BGN] ");

	if (color == DUAL)
		SetConsoleTextAttribute(lStdHandle, 7);

	printf("Paladin Debug Console Created\n");

	//Assume all is well at this point
	initialized = true;
	return true;
}

void Debug::LogDebugMsg(DebugMessage type, char *msg, ...) 
{
#ifndef m_DEBUG
	return;
#endif

	if (!initialized)
		return;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole == INVALID_HANDLE_VALUE)
		return;

	if (color == MONO)
		SetConsoleTextAttribute(hConsole, 7);

	//Set console color
	switch (type) 
	{
		case DBG:
			if (color != MONO)
				SetConsoleTextAttribute(hConsole, 15);
			printf("\n[DBG] ");
			break;
		case SCS:
			if (color != MONO)
				SetConsoleTextAttribute(hConsole, 10);
			printf("\n[SCS] ");
			break;
		case WRN:
			if (color != MONO)
				SetConsoleTextAttribute(hConsole, 14);
			printf("\n[WRN] ");
			break;
		case ERR:
			if (color != MONO)
				SetConsoleTextAttribute(hConsole, 12);
			printf("\n[ERR] ");
			break;
		case LER:
			if (color != MONO)
				SetConsoleTextAttribute(hConsole, 12);
			printf("\n[LER] ");
			break;
		default:
			if (color != MONO)
				SetConsoleTextAttribute(hConsole, 15);
			printf("\n[DBG] ");
	}

	if (color != FULL)
		SetConsoleTextAttribute(hConsole, 7);

	//Get arguments
	char cBuffer[2048] = { '\0' };

	va_list vaList;
	va_start(vaList, msg);
	vsnprintf(cBuffer, sizeof cBuffer, msg, vaList);
	va_end(vaList);

	//Output data
	printf(cBuffer);
}

// Look up errors here: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx
void Debug::LogLastErrorA() 
{
#ifndef m_DEBUG
	return;
#endif

	if (!initialized)
		return;

	DWORD error = GetLastError();
	LPSTR errorString = nullptr;

	if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&errorString), 0, nullptr))
		LogDebugMsg(LER, "[%lu] - Unable to retrieve error description", error);
	else
		LogDebugMsg(LER, "[%lu] - %s", error, errorString);

	LocalFree(errorString);
}

void Debug::LogLastErrorB()
{
#ifndef m_DEBUG
	return;
#endif

	DWORD error = GetLastError();
	LPSTR errorString = nullptr;
	char cBuffer[2048] = { '\0' };

	if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&errorString), 0, nullptr))
		_snprintf_s(cBuffer, sizeof cBuffer, "[%lu] - Unable to retrieve error description", error);
	else
		_snprintf_s(cBuffer, sizeof cBuffer, "[%lu] - %s", error, errorString);

	LocalFree(errorString);

	MessageBox(NULL, cBuffer, "Last Error", MB_OK);
}