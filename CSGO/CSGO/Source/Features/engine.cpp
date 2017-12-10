#include "../main.h"

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
	cs_soState.loc = dwClientState.val + cs_soState.off;
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
	lp_fFlags.loc = dwLocalPlayer.val + lp_fFlags.off;
	mem.Read(lp_fFlags);
	return lp_fFlags.val;
}

total CEngine::GetLocalPlayerHitsOnServer() {
	GetLocalPlayer();
	lp_totalHitsOnServer.loc = dwLocalPlayer.val + lp_totalHitsOnServer.off;
	mem.Read(lp_totalHitsOnServer);
	return lp_totalHitsOnServer.val;
}

float CEngine::GetFlashMaxAlpha() {
	GetLocalPlayer();
	lp_flFlashMaxAlpha.loc = dwLocalPlayer.val + lp_flFlashMaxAlpha.off;
	mem.Read(lp_flFlashMaxAlpha);
	return lp_flFlashMaxAlpha.val;
}

void CEngine::SetFlashMaxAlpha(float lp_flNewFlashMaxAlpha) {
	if (GetFlashMaxAlpha() != lp_flNewFlashMaxAlpha) {
		lp_flFlashMaxAlpha.val = lp_flNewFlashMaxAlpha;
		mem.Write(lp_flFlashMaxAlpha);
	}
}

int CEngine::GetFieldOfView() {
	GetLocalPlayer();
	lp_iFOV.loc = dwLocalPlayer.val + lp_iFOV.off;
	mem.Read(lp_iFOV);
	return lp_iFOV.val;
}

void CEngine::SetFieldOfView(int lp_iNewFOV) {
	if (GetFieldOfView() != lp_iNewFOV) {
		lp_iFOV.val = lp_iNewFOV;
		mem.Write(lp_iFOV);
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

handle CEngine::GetActiveWeaponHandle() {
	GetLocalPlayer();
	lp_hActiveWeapon.loc = dwLocalPlayer.val + lp_hActiveWeapon.off;
	mem.Read(lp_hActiveWeapon);
	return lp_hActiveWeapon.val;
}

DWORD CEngine::GetActiveWeaponEntity() {
	DWORD dwActiveWeaponEntityID = GetActiveWeaponHandle() & 0xFFF;
	Address<DWORD> dwWeaponEntity = {dwEntityList.loc + (dwActiveWeaponEntityID - 1) * 0x10};
	mem.Read(dwWeaponEntity);
	return dwWeaponEntity.val;
}

float CEngine::GetNextPrimaryAttack() {
	aw_flNextPrimaryAttack.loc = GetActiveWeaponEntity() + aw_flNextPrimaryAttack.off;
	mem.Read(aw_flNextPrimaryAttack);
	aw_flNextPrimaryAttack.val -= GetGlobalVars().curtime;
	return aw_flNextPrimaryAttack.val;
}

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

CEngine eng;
