#include "main.h"

enum QuitReasons {
	QUIT_REASON_UNKNOWN = -1,
	QUIT_REASON_SUCCESS,
	QUIT_REASON_LOADLIBRARY_ERROR,
	QUIT_REASON_BLACKLISTED_CALL,
	QUIT_REASON_PANIC
};

void Feature(bool bFeatureState, int uiFeatureKey, void (*Feature)()) {
	while (bFeatureState) {
		if (bExitState) {
			return;
		}
		if (GetAsyncKeyState(uiFeatureKey)) {
			Feature();
		}
		Wait(10);
	}
}

void CleanUp() {
	bExitState = true;
	for (auto &t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}
#ifdef _DEBUG
	FreeConsole();
#endif
}

void Panic() {
	CleanUp();
	cfg.uiQuitReason = QUIT_REASON_PANIC;
	FreeLibraryAndExitThread(hInst, cfg.uiQuitReason);
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
	if (!cfg.LoadConfig()) {
		MessageBox(nullptr, "Warning 3: Config File -> Using Defaults\nIs there a config file?", "Paladin CSGO", MB_ICONWARNING | MB_OK);
	}
	if (!cfg.ReadConfig()) {
		MessageBox(nullptr, "Warning 4: Config File -> Using Defaults\nIs the config file formatted for this version?", "Paladin CSGO", MB_ICONWARNING | MB_OK);
	}
	// Todo call Menu here
	if (!mem.AttachToGame()) {
		MessageBox(nullptr, "Fatal Error 1: Game Attach\nAre you running the cheat as admin?", "Paladin CSGO", MB_ICONERROR | MB_OK);
		return;
	}
	mem.InitializeAddresses();
	// Todo make our threads here
	// General format for cheat threads:
	threads.push_back(std::thread(Feature(cfg.bAutoJumpState, cfg.uiAutoJumpKey, &aut.AutoJump)));
}

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hInstDll);
			hInst = hInstDll;
			CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(Cheat), nullptr, 0, nullptr);
			break;
		case DLL_PROCESS_DETACH:
			CleanUp();
			break;
		default:
			return QUIT_REASON_BLACKLISTED_CALL;
	}
	return QUIT_REASON_SUCCESS;
}
