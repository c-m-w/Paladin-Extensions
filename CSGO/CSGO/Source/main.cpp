#include "main.h"

void Feature(bool, std::function<void()>, unsigned int);
void Feature(bool, std::function<void()>, unsigned int, int);
void CleanUp();
void Panic();
void Cheat();

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hInstDll);
			hInst = hInstDll;
			CreateThread(nullptr, NULL, LPTHREAD_START_ROUTINE(Cheat), nullptr, NULL, nullptr);
			break;
		case DLL_PROCESS_DETACH:
			CleanUp();
			break;
		default:
			return BOOL(EQuitReasons::BLACKLISTED_CALL);
	}
	return BOOL(EQuitReasons::SUCCESS);
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
	SetCurrentConsoleFontEx(hConsole, NULL, &cfiEx);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cci);
	Wait(1);
	SetConsoleTextAttribute(hConsole, 15);
	printf("[DBG] ");
	strLog.append("\n[DBG] ");
	SetConsoleTextAttribute(hConsole, 7);
	printf("Paladin Debug Interface Setup\n");
	strLog.append("Paladin Debug Interface Setup\n");
#endif
	EPremium uCurrentUserPremiumStatus = all.CheckPremiumStatus();
	if (uCurrentUserPremiumStatus == EPremium::BANNED) {
		//TODO BANNED: DELETE FILE
		return;
	}
	if (uCurrentUserPremiumStatus == EPremium::NOT_PREMIUM) {
		return;
	}
	if (uCurrentUserPremiumStatus == EPremium::EXPIRED) {
		MessageBox(nullptr, "Notice 1: Premium Time Expired -> No access\nDid you renew your premium?", "Paladin CSGO", MB_ICONHAND | MB_OK);
	}
	if (uCurrentUserPremiumStatus == EPremium::PREMIUM) {
		LogDebugMsg(SCS, "Authenticated!");
	}
	if (!all.GetElevationState()) {
		MessageBox(nullptr, "Warning 1: Elevation Token State -> No access\nDid you run the middleman as admin?", "Paladin CSGO", MB_ICONWARNING | MB_OK);
	}
	if (cfg.bCheckForAnticheat) {
		EAnticheatStatus kacCSGO = all.KillAnticheat("Counter-Strike: Global Offensive", *"csgo.exe");
		if (kacCSGO != EAnticheatStatus::FAILED) {
			if (kacCSGO == EAnticheatStatus::KILLED) {
				MessageBox(nullptr, "Warning 2: Anticheat -> Terminated\nDid you leave CSGO open during injection?", "Paladin CSGO", MB_ICONWARNING | MB_OK);
			}
			if (all.KillAnticheat("Steam", *"steam.exe") == EAnticheatStatus::KILLED) {
				MessageBox(nullptr, "Warning 2: Anticheat -> Terminated\nDid you leave Steam open during injection?", "Paladin CSGO", MB_ICONWARNING | MB_OK);
			}
		} else {
			MessageBox(nullptr, "Fatal Error 1: Elevation Token State -> No anticheat termination access\nDid you run the middleman as admin?", "Paladin CSGO", MB_ICONERROR | MB_OK);
			CleanUp();
		}
	}
	if (!cfg.LoadConfig()) {
		MessageBox(nullptr, "Warning 3: Config File -> Using Defaults\nIs there a config file?", "Paladin CSGO", MB_ICONWARNING | MB_OK);
	}
	if (!cfg.ReadConfig()) {
		MessageBox(nullptr, "Warning 4: Config File -> Using Defaults\nIs the config file formatted for this version?", "Paladin CSGO", MB_ICONWARNING | MB_OK);
	}
	// Todo call Menu here
	if (!mem.AttachToGame()) {
		MessageBox(nullptr, "Fatal Error 2: Game Attach\nAre you running the cheat as admin?", "Paladin CSGO", MB_ICONERROR | MB_OK);
		CleanUp();
	}
	mem.InitializeAddresses();
	// General format for cheat threads:
	if (cfg.bAutoJumpState) {
		std::function<void()> fnAutoJump = [&] {
			aut.AutoJump();
		};
		std::thread tAutoJump([&]() {
			Feature(cfg.bAutoJumpState, fnAutoJump, 1, cfg.iAutoJumpKey);
		});
		tThreads.push_back(move(tAutoJump));
	}
}

void Panic() {
	CleanUp();
	cfg.iQuitReason = int(EQuitReasons::PANIC);
	FreeLibraryAndExitThread(hInst, cfg.iQuitReason);
}

void CleanUp() {
	bExitState = true;
	for (auto &t : tThreads) {
		if (t.joinable()) {
			t.join();
		}
	}
#ifdef _DEBUG
	FreeConsole();
#endif
}

void Feature(bool bFeatureState, std::function<void()> fnFeature, unsigned int uiWait, int iFeatureKey) {
	while (!bExitState) {
		while (bFeatureState) {
			if (GetAsyncKeyState(iFeatureKey)) {
				fnFeature();
			} else {
				if (uiWait) {
					Wait(uiWait);
				}
			}
			if (bExitState) {
				return;
			}
		}
	}
}

void Feature(bool bFeatureState, std::function<void()> fnFeature, unsigned int uiWait) {
	while (!bExitState) {
		while (bFeatureState) {
			fnFeature();
			if (uiWait) {
				Wait(uiWait);
			}
			if (bExitState) {
				return;
			}
		}
	}
}
