#include "../main.h"

void CEngine::WaitTicks(int iTicksToWait) {
	iTicksToWait += GetGlobalVars().tickcount;
	while (iTicksToWait > GetGlobalVars().tickcount) {
		Wait(1);
	}
}

Angle ClampAngle(Angle aToClamp) {
	if (aToClamp.pitch > 89) {
		aToClamp.pitch = 89;
	} else if (aToClamp.pitch < -89) {
		aToClamp.pitch = -89;
	}
	while (aToClamp.yaw < -180) {
		aToClamp.yaw += 360;
	}
	while (aToClamp.yaw > 180) {
		aToClamp.yaw -= 360;
	}
	if (aToClamp.roll > 50) {
		aToClamp.roll = 50;
	} else if (aToClamp.roll < -50) {
		aToClamp.roll = -50;
	}
	return aToClamp;
}

CGlobalVars CEngine::GetGlobalVars() {
	mem.Read(dwGlobalVars);
	return dwGlobalVars.val;
}

DWORD CEngine::GetClientState() {
	mem.Read(dwClientState);
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
	if (lp_hActiveWeapon.loc < dwLocalPlayer.val) {
		lp_hActiveWeapon.loc += dwLocalPlayer.val;
	}
	mem.Read(lp_hActiveWeapon);
	return lp_hActiveWeapon.val;
}

int CEngine::GetActiveWeaponID() {
	GetActiveWeapon();
	return lp_hActiveWeapon.val & 0xFFF;
}

DWORD CEngine::GetActiveWeaponEntity() {
	Address<DWORD> dwWeaponEntity = {dwEntityList.loc + (GetActiveWeaponID() - 1) * 0x10};
	mem.Read(dwWeaponEntity);
	return dwWeaponEntity.val;
}

float CEngine::GetNextPrimaryAttack() {
	if (aw_flNextPrimaryAttack.loc < GetActiveWeaponEntity()) {
		aw_flNextPrimaryAttack.loc += GetActiveWeaponEntity();
	}
	mem.Read(aw_flNextPrimaryAttack);
	aw_flNextPrimaryAttack.val -= GetGlobalVars().curtime;
	return aw_flNextPrimaryAttack.val;
}

CEngine eng;
