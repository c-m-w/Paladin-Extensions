#include "../main.h"

DWORD CEngine::GetClientState() {
	if (!dwClientState.val) {
		mem.Read(dwClientState);
	}
	return dwClientState.val;
}

ESignOnState CEngine::GetClientStateSignOnState() {
	GetClientState();
	if (cs_soState.loc - dwClientState.val == 0) {
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
	if (lp_fFlags.loc - dwLocalPlayer.val == 0) {
		lp_fFlags.loc += dwLocalPlayer.val;
	}
	mem.Read(lp_fFlags);
	return lp_fFlags.val;
}

total CEngine::GetLocalPlayerHitsOnServer() {
	GetLocalPlayer();
	if (lp_totalHitsOnServer.loc - dwLocalPlayer.val == 0) {
		lp_totalHitsOnServer.loc += dwLocalPlayer.val;
	}
	mem.Read(lp_totalHitsOnServer);
	return lp_totalHitsOnServer.val;
}

float CEngine::GetFlashMaxAlpha() {
	GetLocalPlayer();
	if (lp_flFlashMaxAlpha.loc - dwLocalPlayer.val == 0) {
		lp_flFlashMaxAlpha.loc += dwLocalPlayer.val;
	}
	mem.Read(lp_flFlashMaxAlpha);
	return lp_flFlashMaxAlpha.val;
}

void CEngine::SetFlashMaxAlpha(float lp_flNewFlashMaxAlpha) {
	GetLocalPlayer();
	if (lp_flFlashMaxAlpha.loc - dwLocalPlayer.val == 0) {
		lp_flFlashMaxAlpha.loc += dwLocalPlayer.val;
	}
	lp_flFlashMaxAlpha.val = lp_flNewFlashMaxAlpha;
	mem.Write(lp_flFlashMaxAlpha);
}

void CEngine::ForceJump(EKeystroke ksType) {
	GetForceJump();
	ksForceJump.val = ksType;
	mem.Write(ksForceJump);
}

void CEngine::ForceAttack(EKeystroke ksType) {
	GetForceAttack();
	ksForceAttack.val = ksType;
	mem.Write(ksForceAttack);
}

float CEngine::GetSensitivity() {
	mem.Read(flSensitivity);
	return flSensitivity.val;
}

void CEngine::SetSensitivity(float flNewSensitivity) {
	flSensitivity.val = flNewSensitivity;
	mem.Write(flSensitivity);
}

handle CEngine::GetActiveWeapon() {
	GetLocalPlayer();
	if (hActiveWeapon.loc - dwLocalPlayer.val == 0) {
		hActiveWeapon.loc += dwLocalPlayer.val;
	}
	mem.Read(hActiveWeapon);
	return hActiveWeapon.val;
}

float CEngine::GetNextPrimaryAttack() {
	GetActiveWeapon();
	if (flNextPrimaryAttack.loc - hActiveWeapon.val == 0) {
		flNextPrimaryAttack.loc += hActiveWeapon.val;
	}
	mem.Read(flNextPrimaryAttack);
	return flNextPrimaryAttack.val;
}

CEngine eng;
