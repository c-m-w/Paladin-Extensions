#include "memory.h"

MemoryManager mem;

MemoryManager::~MemoryManager() {
	if (hGame != nullptr || hGame != INVALID_HANDLE_VALUE) {
		CloseHandle(hGame);
	}
}

bool MemoryManager::AttachToGame() {
	while (!GetWindowThreadProcessId(FindWindowA(nullptr, "Counter-Strike: Global Offensive"), &dwProcessId)) {
		LogDebugMsg(DBG, "Searching for CSGO");
		Wait(1000);
	}
	hGame = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, dwProcessId);
	if (!hGame) {
		LogDebugMsg(ERR, "Invalid game handle");
		return false;
	}
	LogDebugMsg(SCS, "Attached to game");
	HANDLE hSnapshot;
	for (int ui = 0; ui < 5; ui++, Wait(2000)) {
		do {
			SetLastError(0);
			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
			Wait(10);
		} while (hSnapshot == INVALID_HANDLE_VALUE || GetLastError() == ERROR_BAD_LENGTH);
		if (hSnapshot == INVALID_HANDLE_VALUE) {
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

void MemoryManager::InitializeAddresses() {
	ksForceJump += dwClientBase;
	ksForceAttack += dwClientBase;
	dwLocalPlayer += dwClientBase;
	Read(dwLocalPlayer);
	lp_iFlags += dwLocalPlayer.loc;
}
