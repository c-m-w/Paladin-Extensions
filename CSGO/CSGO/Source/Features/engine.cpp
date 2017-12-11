#include "../dllmain.h"

GlobalVars CEngine::GetGlobalVars() {
	mem.Get(dwGlobalVars);
	return dwGlobalVars.val;
}

DWORD CEngine::GetClientState() {
	mem.Get(dwClientState);
	return dwClientState.val;
}

ESignOnState CEngine::GetSignOnState() {
	GetClientState();
	cs_soSignOnState.loc = dwClientState.val + cs_soSignOnState.off;
	mem.Get(dwClientState);
	return cs_soSignOnState.val;
}

angle CEngine::GetViewAngle() {
	GetClientState();
	cs_aViewAngle.loc = dwClientState.val + cs_aViewAngle.off;
	mem.Get(cs_aViewAngle);
	return cs_aViewAngle.val;
}

void CEngine::SetViewAngle(angle cs_aNewViewAngle) {
	if (GetViewAngle() != cs_aNewViewAngle) {
		cs_aViewAngle.val = cs_aNewViewAngle;
		mem.Set(cs_aViewAngle);
	}
}

frame CEngine::GetForceAttack() {
	mem.Get(fForceAttack);
	return fForceAttack.val;
}

void CEngine::ForceAttack(frame ksType) {
	if (GetForceAttack() ^ ksType) {
		fForceAttack.val |= ksType;
		mem.Set(fForceAttack);
	}
}

frame CEngine::GetForceJump() {
	mem.Get(fForceJump);
	return fForceJump.val;
}

void CEngine::ForceJump(frame ksType) {
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
	DWORD dwOldEntityList = dwEntityList.loc;
	dwEntityList.loc += (iEntity - 1) * 0x10;
	mem.Get(dwEntityList);
	dwEntityList.loc = dwOldEntityList;
	return dwEntityList.val;
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
	mem.Get(dwLocalPlayer);
	return dwLocalPlayer.val;
}

ETeam CEngine::GetTeam() {
	GetLocalPlayer();
	lp_tTeamNum.loc = dwLocalPlayer.val + lp_tTeamNum.off;
	mem.Get(lp_tTeamNum);
	return lp_tTeamNum.val;
}

frame CEngine::GetFlags() {
	GetLocalPlayer();
	lp_fFlags.loc = dwLocalPlayer.val + lp_fFlags.off;
	mem.Get(lp_fFlags);
	return lp_fFlags.val;
}

EMoveType CEngine::GetMoveType() {
	GetLocalPlayer();
	lp_mMoveType.loc = dwLocalPlayer.val + lp_mMoveType.off;
	mem.Get(lp_mMoveType);
	return lp_mMoveType.val;
}

angle CEngine::GetAimPunch() {
	GetLocalPlayer();
	lp_aAimPunch.loc = dwLocalPlayer.val + lp_aAimPunch.off;
	mem.Get(lp_aAimPunch);
	return lp_aAimPunch.val;
}

int CEngine::GetFieldOfView() {
	GetLocalPlayer();
	lp_iFOV.loc = dwLocalPlayer.val + lp_iFOV.off;
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
	GetLocalPlayer();
	lp_totalHitsOnServer.loc = dwLocalPlayer.val + lp_totalHitsOnServer.off;
	mem.Get(lp_totalHitsOnServer);
	return lp_totalHitsOnServer.val;
}

float CEngine::GetFlashMaxAlpha() {
	GetLocalPlayer();
	lp_flFlashMaxAlpha.loc = dwLocalPlayer.val + lp_flFlashMaxAlpha.off;
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
	GetLocalPlayer();
	lp_hActiveWeapon.loc = dwLocalPlayer.val + lp_hActiveWeapon.off;
	mem.Get(lp_hActiveWeapon);
	return lp_hActiveWeapon.val;
}

DWORD CEngine::GetActiveWeaponEntity() {
	DWORD dwActiveWeaponEntityID = GetActiveWeaponHandle() & 0xFFF;
	Address<DWORD> dwWeaponEntity = {dwEntityList.loc + (dwActiveWeaponEntityID - 1) * 0x10};
	mem.Get(dwWeaponEntity);
	return dwWeaponEntity.val;
}

float CEngine::GetNextPrimaryAttack() {
	aw_flNextPrimaryAttack.loc = GetActiveWeaponEntity() + aw_flNextPrimaryAttack.off;
	mem.Get(aw_flNextPrimaryAttack);
	aw_flNextPrimaryAttack.val -= GetGlobalVars().curtime;
	return aw_flNextPrimaryAttack.val;
}

void CEngine::WaitTicks(int iTicksToWait) {
	iTicksToWait += GetGlobalVars().tickcount;
	while (iTicksToWait > GetGlobalVars().tickcount) {
		Wait(1);
	}
}

angle CEngine::ClampAngle(angle aToClamp) {
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

angle CEngine::NormalizeAngle(angle aToNormalize) {
	angle aNewAngle;
	// TODO cap 31 degrees per tick
	return aNewAngle;
}

angle CEngine::VectorToAngle(coordinate cOrigin, coordinate cEndPoint) {
	angle aReturn = {0,0,0};
	vector vDelta(cOrigin, cEndPoint);
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
