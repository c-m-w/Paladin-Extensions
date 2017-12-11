#include "../dllmain.h"

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

void CEngine::ForceJump(EKeystroke ksType) {
	if (GetForceJump() != ksType) {
		ksForceJump.val = ksType;
		mem.Write(ksForceJump);
	}
}

EKeystroke CEngine::GetForceAttack() {
	mem.Read(ksForceAttack);
	return ksForceAttack.val;
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

DWORD CEngine::GetEntityBase(int iEntity) {
	DWORD dwOldEntityList = dwEntityList.loc;
	dwEntityList.loc += (iEntity - 1) * 0x10;
	mem.Read(dwEntityList);
	dwEntityList.loc = dwOldEntityList;
	return dwEntityList.val;
}

ETeam CEngine::GetEntityTeam(int iEntity) {
	el_tTeamNum.loc = GetEntityBase(iEntity) + el_tTeamNum.off;
	mem.Read(el_tTeamNum);
	return el_tTeamNum.val;
}

bool CEngine::GetEntitySpotted(int iEntity) {
	el_bSpotted.loc = GetEntityBase(iEntity) + el_bSpotted.off;
	mem.Read(el_bSpotted);
	return el_bSpotted.val;
}

void CEngine::SetEntitySpotted(int iEntity, bool el_bNewSpotted) {
	if (GetEntitySpotted(iEntity) != el_bNewSpotted) {
		el_bSpotted.val = el_bNewSpotted;
		mem.Write(el_bSpotted);
	}
}

DWORD CEngine::GetLocalPlayer() {
	mem.Read(dwLocalPlayer);
	return dwLocalPlayer.val;
}

ETeam CEngine::GetTeam() {
	GetLocalPlayer();
	lp_tTeamNum.loc = dwLocalPlayer.val + lp_tTeamNum.off;
	mem.Read(lp_tTeamNum);
	return lp_tTeamNum.val;
}

EMoveType CEngine::GetMoveType() {
	GetLocalPlayer();
	lp_mMoveType.loc = dwLocalPlayer.val + lp_mMoveType.off;
	mem.Read(lp_mMoveType);
	return lp_mMoveType.val;
}

frame CEngine::GetFlags() {
	GetLocalPlayer();
	lp_fFlags.loc = dwLocalPlayer.val + lp_fFlags.off;
	mem.Read(lp_fFlags);
	return lp_fFlags.val;
}

total CEngine::GetHitsOnServer() {
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

Angle CEngine::ClampAngle(Angle aToClamp) {
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

Angle CEngine::VectorToAngle(Coordinate cOrigin, Coordinate cEndPoint) {
	Angle aReturn = {0,0,0};
	Vector vDelta(cOrigin, cEndPoint);
	if (vDelta.dy == 0 && vDelta.dx == 0) {
		aReturn.yaw = 0;
		if (vDelta.dz > 0) {
			aReturn.pitch = 89;
		} else if (vDelta.dz > 0) {
			aReturn.pitch = -89;
		} else {
			aReturn.pitch = 0;
		}
	} else {
		aReturn.yaw = atan2(vDelta.dy, vDelta.dx) * 180 / PI;
		if (aReturn.yaw < 0) {
			aReturn.yaw += 360;
		}
		float flTemp = sqrt(vDelta.dx * vDelta.dx + vDelta.dy * vDelta.dy);
		aReturn.pitch = atan2(-vDelta.dz, flTemp) * 180 / PI;
		if (aReturn.pitch < 0) {
			aReturn.pitch += 360;
		}
	}
	ClampAngle(aReturn);
	return aReturn;
}

CEngine eng;
