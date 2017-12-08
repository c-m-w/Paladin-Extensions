#include "../main.h"

CGlobalVars CEngine::GetGlobalVars() {
	mem.Read(dwGlobalVars);
	return dwGlobalVars.val;
}

float CEngine::GetCurTime() {
	return GetGlobalVars().curtime;
}

int CEngine::GetMaxClients() {
	return GetGlobalVars().maxClients;
}

int CEngine::GetTickCount() {
	return GetGlobalVars().tickcount;
}

float CEngine::GetIntervalPerTick() {
	return GetGlobalVars().interval_per_tick;
}

DWORD CEngine::GetClientState() {
	if (!dwClientState.val) {
		mem.Read(dwClientState);
	}
	return dwClientState.val;
}

ESignOnState CEngine::GetClientStateSignOnState() {
	GetClientState();
	if (cs_soState.loc < dwClientState.val) {
		cs_soState.loc += dwClientState.val;
	}
	mem.Read(dwClientState);
	return cs_soState.val;
}

EKeystroke CEngine::GetForceJump() {
	mem.Read(ksForceJump);
	return ksForceJump.val;
}

EKeystroke CEngine::GetForceAttack() {
	mem.Read(ksForceAttack);
	return ksForceAttack.val;
}

DWORD CEngine::GetLocalPlayer() {
	mem.Read(dwLocalPlayer);
	return dwLocalPlayer.val;
}

frame CEngine::GetLocalPlayerFlags() {
	GetLocalPlayer();
	if (lp_fFlags.loc < dwLocalPlayer.val) {
		lp_fFlags.loc += dwLocalPlayer.val;
	}
	mem.Read(lp_fFlags);
	return lp_fFlags.val;
}

total CEngine::GetLocalPlayerHitsOnServer() {
	GetLocalPlayer();
	if (lp_totalHitsOnServer.loc < dwLocalPlayer.val) {
		lp_totalHitsOnServer.loc += dwLocalPlayer.val;
	}
	mem.Read(lp_totalHitsOnServer);
	return lp_totalHitsOnServer.val;
}

float CEngine::GetFlashMaxAlpha() {
	GetLocalPlayer();
	if (lp_flFlashMaxAlpha.loc < dwLocalPlayer.val) {
		lp_flFlashMaxAlpha.loc += dwLocalPlayer.val;
	}
	mem.Read(lp_flFlashMaxAlpha);
	return lp_flFlashMaxAlpha.val;
}

void CEngine::SetFlashMaxAlpha(float lp_flNewFlashMaxAlpha) {
	if (GetFlashMaxAlpha() != lp_flNewFlashMaxAlpha) {
		lp_flFlashMaxAlpha.val = lp_flNewFlashMaxAlpha;
		mem.Write(lp_flFlashMaxAlpha);
	}
}

void CEngine::ForceJump(EKeystroke ksType) {
	if (GetForceJump() != ksType) {
		ksForceJump.val = ksType;
		mem.Write(ksForceJump);
	}
}

void CEngine::ForceAttack(EKeystroke ksType) {
	if (GetForceAttack() != ksType) {
		ksForceAttack.val = ksType;
		mem.Write(ksForceAttack);
	}
}

float CEngine::GetSensitivity() {
	mem.Read(flSensitivity);
	return flSensitivity.val;
}

void CEngine::SetSensitivity(float flNewSensitivity) {
	if (GetSensitivity() != flNewSensitivity) {
		flSensitivity.val = flNewSensitivity;
		mem.Write(flSensitivity);
	}
}

handle CEngine::GetActiveWeapon() {
	GetLocalPlayer();
	if (hActiveWeapon.loc < dwLocalPlayer.val) {
		hActiveWeapon.loc += dwLocalPlayer.val;
	}
	mem.Read(hActiveWeapon);
	return hActiveWeapon.val;
}

int CEngine::GetActiveWeaponID() {
	GetActiveWeapon();
	return hActiveWeapon.val & 0xFFF;
}

DWORD CEngine::GetActiveWeaponEntity() {
	Address<DWORD> dwWeaponEntity = {dwEntityList.loc + (GetActiveWeaponID() - 1) * 0x10};
	mem.Read(dwWeaponEntity);
	return dwWeaponEntity.val;
}

float CEngine::GetNextPrimaryAttack() {
	if (flNextPrimaryAttack.loc < GetActiveWeaponEntity()) {
		flNextPrimaryAttack.loc += GetActiveWeaponEntity();
	}
	mem.Read(flNextPrimaryAttack);
	flNextPrimaryAttack.val -= GetCurTime();
	return flNextPrimaryAttack.val;
}

void CEngine::WaitTick() {
	Wait(int(GetIntervalPerTick() * 1000.f));
}

void CEngine::WaitUntilNextTick() {
	int iStartTick = GetTickCount();
	while (iStartTick == GetTickCount()) {
		Wait(1);
	}
}

CEngine eng;
