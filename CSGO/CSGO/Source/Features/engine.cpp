#include "../dllmain.h"

CGlobalVars CEngine::GetGlobalVars() {
	mem.Get(dwGlobalVars);
	return dwGlobalVars.val;
}

DWORD CEngine::GetClientState() {
	mem.Get(pdwClientState);
	return pdwClientState.val;
}

ESignOnState CEngine::GetSignOnState() {
	cs_soSignOnState.loc = GetClientState() + cs_soSignOnState.off;
	mem.Get(pdwClientState);
	return cs_soSignOnState.val;
}

angle_t CEngine::GetViewAngle() {
	cs_aViewAngle.loc = GetClientState() + cs_aViewAngle.off;
	mem.Get(cs_aViewAngle);
	return cs_aViewAngle.val;
}

void CEngine::SetViewAngle(angle_t cs_aNewViewAngle) {
	if (GetViewAngle() != cs_aNewViewAngle) {
		cs_aViewAngle.val = cs_aNewViewAngle;
		mem.Set(cs_aViewAngle);
	}
}

flag CEngine::GetForceAttack() {
	mem.Get(fForceAttack);
	return fForceAttack.val;
}

void CEngine::ForceAttack(flag ksType) {
	if (GetForceAttack() ^ ksType) {
		fForceAttack.val |= ksType;
		mem.Set(fForceAttack);
	}
}

flag CEngine::GetForceJump() {
	mem.Get(fForceJump);
	return fForceJump.val;
}

void CEngine::ForceJump(flag ksType) {
	if (GetForceJump() ^ ksType) {
		fForceJump.val |= ksType;
		mem.Set(fForceJump);
	}
}

float CEngine::GetSensitivity() {
	mem.Get(flSensitivity);
	return flSensitivity.val;
}

void CEngine::SetSensitivity(float flNewSensitivity) {
	if (GetSensitivity() != flNewSensitivity) {
		flSensitivity.val = flNewSensitivity;
		mem.Set(flSensitivity);
	}
}

DWORD CEngine::GetEntityBase(int iEntity) {
	DWORD dwOldEntityList = pdwEntityList.loc;
	pdwEntityList.loc += (iEntity - 1) * 0x10;
	mem.Get(pdwEntityList);
	pdwEntityList.loc = dwOldEntityList;
	return pdwEntityList.val;
}

ETeam CEngine::GetEntityTeam(int iEntity) {
	el_tTeamNum.loc = GetEntityBase(iEntity) + el_tTeamNum.off;
	mem.Get(el_tTeamNum);
	return el_tTeamNum.val;
}

bool CEngine::GetEntitySpotted(int iEntity) {
	el_bSpotted.loc = GetEntityBase(iEntity) + el_bSpotted.off;
	mem.Get(el_bSpotted);
	return el_bSpotted.val;
}

void CEngine::SetEntitySpotted(int iEntity, bool el_bNewSpotted) {
	if (GetEntitySpotted(iEntity) != el_bNewSpotted) {
		el_bSpotted.val = el_bNewSpotted;
		mem.Set(el_bSpotted);
	}
}

DWORD CEngine::GetLocalPlayer() {
	mem.Get(pdwLocalPlayer);
	return pdwLocalPlayer.val;
}

ETeam CEngine::GetTeam() {
	lp_tTeamNum.loc = GetLocalPlayer() + lp_tTeamNum.off;
	mem.Get(lp_tTeamNum);
	return lp_tTeamNum.val;
}

flag CEngine::GetFlags() {
	lp_fFlags.loc = GetLocalPlayer() + lp_fFlags.off;
	mem.Get(lp_fFlags);
	return lp_fFlags.val;
}

EMoveType CEngine::GetMoveType() {
	lp_mMoveType.loc = GetLocalPlayer() + lp_mMoveType.off;
	mem.Get(lp_mMoveType);
	return lp_mMoveType.val;
}

angle_t CEngine::GetAimPunch() {
	lp_aAimPunch.loc = GetLocalPlayer() + lp_aAimPunch.off;
	mem.Get(lp_aAimPunch);
	return lp_aAimPunch.val;
}

int CEngine::GetFieldOfView() {
	lp_iFOV.loc = GetLocalPlayer() + lp_iFOV.off;
	mem.Get(lp_iFOV);
	return lp_iFOV.val;
}

void CEngine::SetFieldOfView(int lp_iNewFOV) {
	if (GetFieldOfView() != lp_iNewFOV) {
		lp_iFOV.val = lp_iNewFOV;
		mem.Set(lp_iFOV);
	}
}

total CEngine::GetHitsOnServer() {
	lp_totalHitsOnServer.loc = GetLocalPlayer() + lp_totalHitsOnServer.off;
	mem.Get(lp_totalHitsOnServer);
	return lp_totalHitsOnServer.val;
}

float CEngine::GetFlashMaxAlpha() {
	lp_flFlashMaxAlpha.loc = GetLocalPlayer() + lp_flFlashMaxAlpha.off;
	mem.Get(lp_flFlashMaxAlpha);
	return lp_flFlashMaxAlpha.val;
}

void CEngine::SetFlashMaxAlpha(float lp_flNewFlashMaxAlpha) {
	if (GetFlashMaxAlpha() != lp_flNewFlashMaxAlpha) {
		lp_flFlashMaxAlpha.val = lp_flNewFlashMaxAlpha;
		mem.Set(lp_flFlashMaxAlpha);
	}
}

handle CEngine::GetActiveWeaponHandle() {
	lp_hActiveWeapon.loc = GetLocalPlayer() + lp_hActiveWeapon.off;
	mem.Get(lp_hActiveWeapon);
	return lp_hActiveWeapon.val;
}

int CEngine::GetActiveWeaponIndex() {
	lp_iPlayerWeaponIndex.loc = lp_iPlayerWeaponIndex.off + GetActiveWeaponEntity();
	mem.Get(lp_iPlayerWeaponIndex);
	return lp_iPlayerWeaponIndex.val;
}

DWORD CEngine::GetActiveWeaponEntity() {
	DWORD dwActiveWeaponEntityID = GetActiveWeaponHandle() & 0xFFF;
	return GetEntityBase(dwActiveWeaponEntityID);
}

float CEngine::GetNextPrimaryAttack() {
	aw_flNextPrimaryAttack.loc = GetActiveWeaponEntity() + aw_flNextPrimaryAttack.off;
	mem.Get(aw_flNextPrimaryAttack);
	aw_flNextPrimaryAttack.val -= GetGlobalVars().curtime;
	if (aw_flNextPrimaryAttack.val < 0.f) {
		aw_flNextPrimaryAttack.val = 0.f;
	}
	return aw_flNextPrimaryAttack.val;
}

void CEngine::WaitTicks(int iTicksToWait) {
	iTicksToWait += GetGlobalVars().tickcount;
	while (iTicksToWait > GetGlobalVars().tickcount) {
		Wait(1);
	}
}

angle_t CEngine::ClampAngle(angle_t aToClamp) {
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

angle_t CEngine::NormalizeAngle(angle_t aToNormalize) {
	angle_t aNewAngle = {};
	// TODO cap 31 degrees per tick
	return aNewAngle;
}

angle_t CEngine::VectorToAngle(coordinate_t cOrigin, coordinate_t cEndPoint) {
	angle_t aReturn = {0,0,0};
	vector_t vDelta(cOrigin, cEndPoint);
	if (vDelta.dy == 0 && vDelta.dx == 0) {
		aReturn.yaw = 0;
		if (vDelta.dz > 0) {
			aReturn.pitch = 90;
		} else if (vDelta.dz < 0) {
			aReturn.pitch = -90;
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
