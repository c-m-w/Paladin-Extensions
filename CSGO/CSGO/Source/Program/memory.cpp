#include "../dllmain.h"

namespace Addresses {
	// global CEngine addresses
	// CEngine pointer addresses
	Address<GlobalVars> dwGlobalVars;
	Address<DWORD> dwClientState;
	Address<ESignOnState> cs_soSignOnState;
	Address<angle> cs_aViewAngle;
	// global Client addresses
	Address<float> flSensitivity;
	Address<frame> fForceAttack;
	Address<frame> fForceJump;
	// Client pointer addresses
	Address<DWORD> dwEntityList;
	Address<ETeam> el_tTeamNum;
	Address<bool> el_bSpotted;

	Address<DWORD> dwLocalPlayer;

	Address<ETeam> lp_tTeamNum;
	Address<frame> lp_fFlags;
	Address<EMoveType> lp_mMoveType;
	Address<angle> lp_aAimPunch;
	Address<int> lp_iFOV;
	Address<total> lp_totalHitsOnServer;
	Address<float> lp_flFlashMaxAlpha;

	Address<handle> lp_hActiveWeapon;
	Address<float> aw_flNextPrimaryAttack;
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
	if (!all.GetElevationState() && all.GetElevationState() != all.GetElevationState(hGame)) {
		LogDebugMsg(ERR, "No permissions");
		return false;
	}
	hGame = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, dwProcessID);
	if (!hGame || hGame == INVALID_HANDLE_VALUE) {
		LogDebugMsg(ERR, "Invalid game handle");
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

DWORD CMemoryManager::FindPattern(BYTE * bMask, char * cMask, DWORD dwAddress, DWORD dwLength) {
	DWORD dwDataLength = strlen(cMask);
	BYTE * bData = new BYTE[dwDataLength + 1];
	SIZE_T sRead;
	for (DWORD i = 0; i < dwLength; i++) {
		auto dwCurrentAddress = dwAddress + i;
		bool bSuccess = ReadProcessMemory(hGame, LPVOID(dwCurrentAddress), bData, dwDataLength, &sRead);
		if (!bSuccess || sRead == 0) {
			continue;
		}
		while (*cMask) {
			++cMask;
			++bData;
			++bMask;
			if (*cMask == 'x' && *bData != *bMask) {
				break;
			}
			delete[] bData;
			return dwAddress + i;
		}
	}
	delete[] bData;
	return 0;
}

void CMemoryManager::InitializeAddresses() {
	LogDebugMsg(DBG, "Initializing addresses");
	// global Engine addresses
	dwGlobalVars = {0x57D550};
	// Engine pointer addresses
	dwClientState = {0x57D84C};
	cs_soSignOnState = {0x108};
	cs_aViewAngle = {0x4D10};
	// global Client addresses
	flSensitivity = { 0xAA04EC, 0xAA04C0 };
	fForceAttack = {0x2EB9EAC};
	fForceJump = {0x4F0ED64};
	// Client pointer addresses
	dwEntityList = {0x4A77AFC};
	el_tTeamNum = {0xF0};
	el_bSpotted = {0x939};
	dwLocalPlayer = {0xA9ADEC};
	lp_tTeamNum = {0xF0};
	lp_fFlags = {0x100};
	lp_mMoveType = {0x258};
	lp_aAimPunch = {0x301C};
	lp_iFOV = {0x330C};
	lp_totalHitsOnServer = {0xA2C8};
	lp_flFlashMaxAlpha = {0xA2F4};
	lp_hActiveWeapon = {0x2EE8};
	aw_flNextPrimaryAttack = {0x31D8};
	LogDebugMsg(SCS, "Initialized bases");
	// engine
	dwGlobalVars.loc += dwEngineBase + dwGlobalVars.off;
	dwClientState.loc += dwEngineBase + dwClientState.off;
	// client
	fForceJump.loc += dwClientBase + fForceJump.off;
	fForceAttack.loc += dwClientBase + fForceAttack.off;
	flSensitivity.loc += dwClientBase + flSensitivity.off;
	dwEntityList.loc += dwClientBase + dwEntityList.off;
	dwLocalPlayer.loc += dwClientBase + dwLocalPlayer.off;
	LogDebugMsg(SCS, "Initialized addresses");
}

CMemoryManager mem;
