#include "../dllmain.h"

namespace Addresses {
	// global CEngine addresses
	// CEngine pointer addresses
	address_t<CGlobalVars> dwGlobalVars;
	address_t<DWORD> pdwClientState;
	address_t<ESignOnState> cs_soSignOnState;
	address_t<angle_t> cs_aViewAngle;
	// global Client addresses
	address_t<float> flSensitivity;
	address_t<flag> fForceAttack;
	address_t<flag> fForceJump;
	// Client pointer addresses
	address_t<DWORD> pdwEntityList;
	address_t<ETeam> el_tTeamNum;
	address_t<bool> el_bSpotted;

	address_t<DWORD> pdwLocalPlayer;

	address_t<ETeam> lp_tTeamNum;
	address_t<flag> lp_fFlags;
	address_t<EMoveType> lp_mMoveType;
	address_t<angle_t> lp_aAimPunch;
	address_t<int> lp_iFOV;
	address_t<total> lp_totalHitsOnServer;
	address_t<float> lp_flFlashMaxAlpha;

	address_t<int> lp_iPlayerWeaponIndex;
	address_t<handle> lp_hActiveWeapon;
	address_t<float> aw_flNextPrimaryAttack;
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
	if (all.GetElevationState() != all.GetElevationState(hGame) && all.GetElevationState() != EElevation::ADMIN) {
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
	for (int i = 0; i < 5; i++, Wait(2000)) {
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

DWORD CMemoryManager::FindPattern(BYTE * bMask, char * szMask, DWORD dwAddress, DWORD dwLength) {
	DWORD dwDataLength = strlen(szMask);
	BYTE * bData = new BYTE[dwDataLength + 1];
	SIZE_T sRead;
	for (DWORD dw = 0; dw < dwLength; dw++) {
		auto dwCurrentAddress = dwAddress + dw;
		bool bSuccess = ReadProcessMemory(hGame, LPVOID(dwCurrentAddress), bData, dwDataLength, &sRead);
		if (!bSuccess || sRead == 0) {
			continue;
		}
		while (*szMask) {
			++szMask;
			++bData;
			++bMask;
			if (*szMask == 'x' && *bData != *bMask) {
				break;
			}
			delete[] bData;
			return dwAddress + dw;
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
	pdwClientState = {0x57D84C};
	cs_soSignOnState = {0x108};
	cs_aViewAngle = {0x4D10};
	// global Client addresses
	flSensitivity = { 0xAA04EC, 0xAA04C0 };
	fForceAttack = {0x2EB9EAC};
	fForceJump = {0x4F0ED64};
	// Client pointer addresses
	pdwEntityList = {0x4A77AFC};
	el_tTeamNum = {0xF0};
	el_bSpotted = {0x939};
	pdwLocalPlayer = {0xA9ADEC};
	lp_tTeamNum = {0xF0};
	lp_fFlags = {0x100};
	lp_mMoveType = {0x258};
	lp_aAimPunch = {0x301C};
	lp_iFOV = {0x330C};
	lp_totalHitsOnServer = {0xA2C8};
	lp_flFlashMaxAlpha = {0xA2F4};
	lp_iPlayerWeaponIndex = {0x5D38};
	lp_hActiveWeapon = {0x2EE8};
	aw_flNextPrimaryAttack = {0x31D8};
	LogDebugMsg(SCS, "Initialized bases");
	// engine
	dwGlobalVars.loc += dwEngineBase + dwGlobalVars.off;
	pdwClientState.loc += dwEngineBase + pdwClientState.off;
	// client
	fForceJump.loc += dwClientBase + fForceJump.off;
	fForceAttack.loc += dwClientBase + fForceAttack.off;
	flSensitivity.loc += dwClientBase + flSensitivity.off;
	pdwEntityList.loc += dwClientBase + pdwEntityList.off;
	pdwLocalPlayer.loc += dwClientBase + pdwLocalPlayer.off;
	LogDebugMsg(SCS, "Initialized addresses");
}

CMemoryManager mem;
