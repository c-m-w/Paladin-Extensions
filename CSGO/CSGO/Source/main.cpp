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
	FreeLibraryAndExitThread(hInst, 0);
}

void Cheat() {
#ifdef _DEBUG
	AllocConsole();
	SetConsoleTitle("Paladin CSGO");
	system("Color 0B"); // console color + text color
	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), false), SC_CLOSE, MF_GRAYED);
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~SC_CLOSE & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	CONSOLE_FONT_INFOEX cfiEx;
	cfiEx.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfiEx.dwFontSize.X = 6;
	cfiEx.dwFontSize.Y = 8;
	wcscpy_s(cfiEx.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cfiEx);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25; // v console cursor length to invisible
	cci.bVisible = false; // v console cursor to invisible
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	MoveWindow(GetConsoleWindow(), 300, 300, 339, 279, false); // window size -> 30x50
	Wait(5);
	printf("[DBG] Paladin Debug Interface Setup\n");
#endif
	Wait(5000);
	//Make threads, add them to threads vector, return this function (close if error)
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
