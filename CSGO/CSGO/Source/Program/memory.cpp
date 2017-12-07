#include "../main.h"

namespace Addresses {
	// global CEngine addresses
	// CEngine pointer addresses
	Address<DWORD> dwClientState = {0x5A783C};
	Address<ESignOnState> cs_soState = {0x108};
	// global Client addresses
	Address<EKeystroke> ksForceJump = {0x4F2419C};
	Address<EKeystroke> ksForceAttack = {0x2ECF46C};
	Address<float> flSensitivity = {0xAB547C, 0xAB5450};
	// Client pointer addresses
	Address<DWORD> dwLocalPlayer = {0xAAFD7C};

	Address<frame> lp_fFlags = {0x100};
	Address<total> lp_totalHitsOnServer = {0xA2C8};

	Address<handle> hActiveWeapon = {0x2EE8};
	Address<float> flNextPrimaryAttack = {0x31D8};
}

CMemoryManager::~CMemoryManager() {
	if (hGame || hGame != INVALID_HANDLE_VALUE) {
		CloseHandle(hGame);
	}
}

bool CMemoryManager::AttachToGame() {
	while (!GetWindowThreadProcessId(FindWindowA(nullptr, "Counter-Strike: Global Offensive"), &dwProcessID)) {
		LogDebugMsg(DBG, "Searching for CSGO");
		Wait(1000);
	}
	hGame = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, dwProcessID);
	if (!hGame || hGame == INVALID_HANDLE_VALUE) {
		LogDebugMsg(ERR, "Invalid game handle");
		return false;
	}
	if (!all.GetElevationState() && all.GetElevationState() != all.GetElevationState(hGame)) {
		LogDebugMsg(ERR, "No permissions");
		return false;
	}
	LogDebugMsg(SCS, "Attached to game");
	HANDLE hSnapshot;
	for (int n = 0; n < 5; n++, Wait(2000)) {
		do {
			SetLastError(0);
			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessID);
			Wait(1);
		} while (hSnapshot == INVALID_HANDLE_VALUE || GetLastError() == ERROR_BAD_LENGTH);
		if (hSnapshot == INVALID_HANDLE_VALUE || !hSnapshot) {
			LogDebugMsg(ERR, "Invalid module snapshot");
			return false;
		}
		LogDebugMsg(SCS, "Module snapshot created");
		MODULEENTRY32 me = {};
		me.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &me)) {
			do {
				if (!_stricmp(me.szModule, "client.dll")) {
					dwClientBase = DWORD(me.modBaseAddr);
				} else if (!_stricmp(me.szModule, "engine.dll")) {
					dwEngineBase = DWORD(me.modBaseAddr);
				}
			} while (Module32Next(hSnapshot, &me));
			CloseHandle(hSnapshot);
		}
		if (dwClientBase && dwEngineBase) {
			LogDebugMsg(SCS, "Modules found");
			LogDebugMsg(SCS, "Client.dll: 0x%p", dwClientBase);
			LogDebugMsg(SCS, "Engine.dll: 0x%p", dwEngineBase);
			return true;
		}
		LogDebugMsg(DBG, "Modules not found, retrying");
		LogDebugMsg(DBG, "Client.dll: 0x%p", dwClientBase);
		LogDebugMsg(DBG, "Engine.dll: 0x%p", dwEngineBase);
	}
	LogDebugMsg(ERR, "Unable to get modules");
	return false;
}

void CMemoryManager::InitializeAddresses() {
	LogDebugMsg(DBG, "Initializing addresses");
	// engine
	dwClientState.loc += dwEngineBase;
	// client
	ksForceJump.loc += dwClientBase;
	ksForceAttack.loc += dwClientBase;
	flSensitivity.loc += dwClientBase;
	dwLocalPlayer.loc += dwClientBase;
	LogDebugMsg(SCS, "Initialized addresses");
}

CMemoryManager mem;
