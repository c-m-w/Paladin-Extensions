#include "main.h"

void Feature(bool, std::function<void()>, unsigned int);
void FeatureKeybound(bool, std::function<void()>, unsigned int, int);
void CleanUp();
void Panic();
void Cheat();

HANDLE hCheat;

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			hInst = hInstDll;
			DisableThreadLibraryCalls(hInstDll);
			hCheat = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(Cheat), nullptr, 0, nullptr);
			if (!hCheat || hCheat == INVALID_HANDLE_VALUE) {
				cfg.iQuitReason = EQuitReasons::LOAD_LIBRARY_ERROR;
			} else {
				cfg.iQuitReason = EQuitReasons::SUCCESS;
			}
			break;
		case DLL_PROCESS_DETACH:
			CleanUp();
			break;
		default:
			cfg.iQuitReason = EQuitReasons::BLACKLISTED_CALL;
			break;
	}
	return BOOL(cfg.iQuitReason);
}

void Cheat() {
#ifdef _DEBUG
	AllocConsole();
	FILE *fTemp;
	freopen_s(&fTemp, "CONOUT$", "w", stdout);
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
		return CleanUp();
	}
	if (uCurrentUserPremiumStatus == EPremium::NOT_PREMIUM) {
		return CleanUp();
	}
	if (uCurrentUserPremiumStatus == EPremium::EXPIRED) {
		MessageBox(nullptr, "Notice 1: Premium Time Expired -> No access\nDid you renew your premium?", "Paladin CSGO", MB_ICONHAND | MB_OK);
		return;
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
			return CleanUp();
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
		return CleanUp();
	}
	mem.InitializeAddresses();
	LogDebugMsg(DBG, "Initializing threads...");
	// general
	std::function<void()> fnPanic = [&] {
		Panic();
	};
	std::thread tPanic(FeatureKeybound, true, fnPanic, 1, VK_F4);
	tThreads.push_back(move(tPanic));
	// awareness
	std::function<void()> fnHitSound = [&] {
		hit.PlaySoundOnHit();
	};
	std::thread tHitSound(FeatureKeybound, true, fnHitSound, 1, VK_F4);
	tThreads.push_back(move(tHitSound));
	std::function<void()> fnNoFlash = [&] {
		nof.NoFlash();
	};
	std::thread tNoFlash(FeatureKeybound, true, fnNoFlash, 1, VK_F4);
	tThreads.push_back(move(tNoFlash));
	// combat
	// miscellaneous
	std::function<void()> fnAutoJump = [&] {
		aut.AutoJump();
	};
	std::thread tAutoJump(FeatureKeybound, true, fnAutoJump, 1, VK_F4);
	tThreads.push_back(move(tAutoJump));
	LogDebugMsg(SCS, "Created threads");
}

void Panic() {
	LogDebugMsg(WRN, "Panic called");
	CleanUp();
	cfg.iQuitReason = EQuitReasons::PANIC;
	FreeLibraryAndExitThread(hInst, DWORD(cfg.iQuitReason));
}

void CleanUp() {
	LogDebugMsg(DBG, "Cleaning up");
	bExitState = true;
	for (auto &tThread : tThreads) {
		if (tThread.joinable()) {
			tThread.join();
		}
	}
#ifdef _DEBUG
	FreeConsole();
#endif
}

void FeatureKeybound(bool bFeatureState, std::function<void()> fnFeature, unsigned int uiWait, int iFeatureKey) {
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
		if (uiWait) {
			Wait(uiWait);
		} else {
			Wait(1);
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
		if (uiWait) {
			Wait(uiWait);
		} else {
			Wait(1);
		}
	}
}
