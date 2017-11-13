#include "main.h"

/* Key:
 * 0 -> successfully exited
 * 1 -> initial library loading failed
 * 2 -> called for blacklisted reason
 */

void CleanUp() {
	bExitState = true;
	for (auto & t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}
}

void Panic() {
	CleanUp();
#ifdef _DEBUG
	FreeConsole();
#endif
	FreeLibraryAndExitThread(hInst, 0);
}

void Cheat() {
#ifdef _DEBUG
	AllocConsole();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWndConsole = GetConsoleWindow();
	SetConsoleTitle("Paladin CSGO");
	MoveWindow(hWndConsole, 300, 300, 339, 279, false);
	
	EnableMenuItem(GetSystemMenu(hWndConsole, false), SC_CLOSE, MF_GRAYED);
	SetWindowLong(hWndConsole, GWL_STYLE, GetWindowLong(hWndConsole, GWL_STYLE) & ~SC_CLOSE & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	CONSOLE_FONT_INFOEX cfiEx;
	cfiEx.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfiEx.dwFontSize.X = 6;
	cfiEx.dwFontSize.Y = 8;
	wcscpy_s(cfiEx.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(hConsole, 0, &cfiEx);

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cci);

	Wait(1);

	SetConsoleTextAttribute(hConsole, 15);
	printf("[DBG] ");
	SetConsoleTextAttribute(hConsole, 7);
	printf("Paladin Debug Interface Setup\n");
#endif
}

BOOL WINAPI DllMain(const HINSTANCE hinstDll, const DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hinstDll);
			hInst = hinstDll;
			CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(Cheat), nullptr, 0, nullptr);
			break;
		case DLL_PROCESS_DETACH:
			CleanUp();
			break;
		default:
			return false;
	}
	return true;
}
