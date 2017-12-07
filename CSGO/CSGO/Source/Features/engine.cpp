#include "../main.h"

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

float CEngine::GetNextPrimaryAttack() {
	GetActiveWeapon();
	if (flNextPrimaryAttack.loc < hActiveWeapon.val) {
		flNextPrimaryAttack.loc += hActiveWeapon.val;
	}
	mem.Read(flNextPrimaryAttack);
	return flNextPrimaryAttack.val;
}

CEngine eng;
