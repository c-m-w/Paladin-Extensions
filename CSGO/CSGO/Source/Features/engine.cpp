#include "../dllmain.h"

CGlobalVars CEngine::GetGlobalVars( )
{
	mem.Get( gvGlobalVars );
	return gvGlobalVars.val;
}

void CEngine::SetGlobalVars( CGlobalVars gvNewGlobalVars )
{
	if ( GetGlobalVars( ) != gvNewGlobalVars )
	{
		gvGlobalVars.val = gvNewGlobalVars;
		mem.Set( gvGlobalVars );
	}
}

DWORD CEngine::GetClientState( )
{
	mem.Get( pdwClientState );
	return pdwClientState.val;
}

ESignOnState CEngine::GetSignOnState( )
{
	cs_soSignOnState.loc = GetClientState( ) + cs_soSignOnState.off;
	mem.Get( pdwClientState );
	return cs_soSignOnState.val;
}

angle_t CEngine::GetViewAngle( )
{
	cs_aViewAngle.loc = GetClientState( ) + cs_aViewAngle.off;
	mem.Get( cs_aViewAngle );
	return cs_aViewAngle.val;
}

void CEngine::SetViewAngle( angle_t angNewViewAngle )
{
	if ( GetViewAngle( ) != ClampAngle( NormalizeAngle( angNewViewAngle ) ) )
	{
		cs_aViewAngle.val = ClampAngle( NormalizeAngle( angNewViewAngle ) );
		mem.Set( cs_aViewAngle );
	}
}

flag CEngine::GetAttack( )
{
	mem.Get( fForceAttack );
	return fForceAttack.val;
}

void CEngine::SetAttack( flag ksType )
{
	if ( GetAttack( ) != ( FA_DEFAULT | ksType ) )
	{
		fForceAttack.val = FA_DEFAULT | ksType;
		mem.Set( fForceAttack );
	}
}

flag CEngine::GetJump( )
{
	mem.Get( fForceJump );
	return fForceJump.val;
}

void CEngine::SetJump( flag ksType )
{
	if ( GetJump( ) != ( FA_DEFAULT | ksType ) )
	{
		fForceJump.val = FA_DEFAULT | ksType;
		mem.Set( fForceJump );
	}
}

float CEngine::GetSensitivity( )
{
	mem.Get( flSensitivity );
	return flSensitivity.val;
}

void CEngine::SetSensitivity( float flNewSensitivity )
{
	Limit( flNewSensitivity, MIN_SENSITIVITY, MAX_SENSITIVITY );
	if ( GetSensitivity( ) != flNewSensitivity )
	{
		flSensitivity.val = flNewSensitivity;
		mem.Set( flSensitivity );
	}
}

DWORD CEngine::GetEntityBase( int iEntity )
{
	DWORD dwOldEntityList = pdwEntityList.loc;
	pdwEntityList.loc += ( iEntity - 1 ) * 0x10;
	mem.Get( pdwEntityList );
	pdwEntityList.loc = dwOldEntityList;
	return pdwEntityList.val;
}

ETeam CEngine::GetEntityTeam( int iEntity )
{
	el_tTeamNum.loc = GetEntityBase( iEntity ) + el_tTeamNum.off;
	mem.Get( el_tTeamNum );
	return el_tTeamNum.val;
}

bool CEngine::GetEntityDormancy( int iEntity )
{
	el_bDormant.loc = GetEntityBase( iEntity ) + el_bDormant.off;
	mem.Get( el_bDormant );
	return el_bDormant.val;
}

bool CEngine::GetEntitySpottedState( int iEntity )
{
	el_bSpottedState.loc = GetEntityBase( iEntity ) + el_bSpottedState.off;
	mem.Get( el_bSpottedState );
	return el_bSpottedState.val;
}

void CEngine::SetEntitySpottedState( int iEntity, bool bNewSpottedState )
{
	if ( GetEntitySpottedState( iEntity ) != bNewSpottedState )
	{
		el_bSpottedState.val = bNewSpottedState;
		mem.Set( el_bSpottedState );
	}
}

DWORD CEngine::GetLocalPlayer( )
{
	mem.Get( pdwLocalPlayer );
	return pdwLocalPlayer.val;
}

ETeam CEngine::GetTeam( )
{
	lp_tTeamNum.loc = GetLocalPlayer( ) + lp_tTeamNum.off;
	mem.Get( lp_tTeamNum );
	return lp_tTeamNum.val;
}

flag CEngine::GetFlags( )
{
	lp_fFlags.loc = GetLocalPlayer( ) + lp_fFlags.off;
	mem.Get( lp_fFlags );
	return lp_fFlags.val;
}

EMoveType CEngine::GetMoveType( )
{
	lp_mMoveType.loc = GetLocalPlayer( ) + lp_mMoveType.off;
	mem.Get( lp_mMoveType );
	return lp_mMoveType.val;
}

angle_t CEngine::GetAimPunch( )
{
	lp_aAimPunch.loc = GetLocalPlayer( ) + lp_aAimPunch.off;
	mem.Get( lp_aAimPunch );
	return lp_aAimPunch.val;
}

int CEngine::GetFieldOfView( )
{
	lp_iFOV.loc = GetLocalPlayer( ) + lp_iFOV.off;
	mem.Get( lp_iFOV );
	return lp_iFOV.val;
}

void CEngine::SetFieldOfView( int iNewFOV )
{
	Limit( iNewFOV, MIN_FIELDOFVIEW, MAX_FIELDOFVIEW );
	if ( GetFieldOfView( ) != iNewFOV )
	{
		lp_iFOV.val = iNewFOV;
		mem.Set( lp_iFOV );
	}
}

int CEngine::GetShotsFired( )
{
	lp_iShotsFired.loc = GetLocalPlayer( ) + lp_iShotsFired.off;
	mem.Get( lp_iShotsFired );
	return lp_iShotsFired.val;
}

total CEngine::GetHitsOnServer( )
{
	lp_totalHitsOnServer.loc = GetLocalPlayer( ) + lp_totalHitsOnServer.off;
	mem.Get( lp_totalHitsOnServer );
	return lp_totalHitsOnServer.val;
}

float CEngine::GetFlashMaxAlpha( )
{
	lp_flFlashMaxAlpha.loc = GetLocalPlayer( ) + lp_flFlashMaxAlpha.off;
	mem.Get( lp_flFlashMaxAlpha );
	return lp_flFlashMaxAlpha.val;
}

void CEngine::SetFlashMaxAlpha( float flNewFlashMaxAlpha )
{
	Limit( flNewFlashMaxAlpha, MIN_FLASHALPHA, MAX_FLASHALPHA );
	if ( GetFlashMaxAlpha( ) != flNewFlashMaxAlpha )
	{
		lp_flFlashMaxAlpha.val = flNewFlashMaxAlpha;
		mem.Set( lp_flFlashMaxAlpha );
	}
}

handle CEngine::GetActiveWeaponHandle( )
{
	lp_hActiveWeapon.loc = GetLocalPlayer( ) + lp_hActiveWeapon.off;
	mem.Get( lp_hActiveWeapon );
	lp_hActiveWeapon.val = GetEntityBase( lp_hActiveWeapon.val & 0xFFF );
	return lp_hActiveWeapon.val;
}

int CEngine::GetActiveWeaponZoomLevel( )
{
	aw_iZoomLevel.loc = GetActiveWeaponHandle( ) + aw_iZoomLevel.off;
	mem.Get( aw_iZoomLevel );
	return aw_iZoomLevel.val;
}

EWeapon CEngine::GetActiveWeaponIndex( )
{
	aw_wpnPlayerWeaponIndex.loc = GetActiveWeaponHandle( ) + aw_wpnPlayerWeaponIndex.off;
	mem.Get( aw_wpnPlayerWeaponIndex );
	return aw_wpnPlayerWeaponIndex.val;
}

float CEngine::GetNextPrimaryAttack( )
{
	aw_flNextPrimaryAttack.loc = GetActiveWeaponHandle( ) + aw_flNextPrimaryAttack.off;
	mem.Get( aw_flNextPrimaryAttack );
	aw_flNextPrimaryAttack.val -= GetGlobalVars( ).curtime;
	return aw_flNextPrimaryAttack.val;
}

float CEngine::GetPixelToAngleYAW( )
{
	return 0.022f * GetSensitivity( ) * all.GetWindowsSensitivity( ); // * ZOOM SENS IF ZOOMED
}

float CEngine::GetPixelToAnglePITCH( )
{
	return 0.022f * GetSensitivity( ) * all.GetWindowsSensitivity( ); // * ZOOM SENS IF ZOOMED
}

angle_t CEngine::ClampAngle( angle_t angToClamp )
{
	Limit( angToClamp.pitch, MIN_PITCH, MAX_PITCH );

	while ( angToClamp.yaw < MIN_YAW )
	{
		angToClamp.yaw += 360.f;
	}
	while ( angToClamp.yaw > MAX_YAW )
	{
		angToClamp.yaw -= 360.f;
	}

	Limit( angToClamp.roll, MIN_ROLL, MAX_ROLL );

	return angToClamp;
}

angle_t CEngine::NormalizeAngle( angle_t angDestination )
{
	angle_t angReturn = angDestination - eng.GetViewAngle( );

	float flAngleChange = sqrt( angReturn.pitch * angReturn.pitch + angReturn.yaw * angReturn.yaw );

	if ( fabs( flAngleChange ) > MAX_ANGLE_DELTA )
	{
		float flAngleScaleFactor = MAX_ANGLE_DELTA / fabs( flAngleChange );
		angReturn.pitch *= flAngleScaleFactor;
		angReturn.yaw *= flAngleScaleFactor;
	}

	int i = int( angReturn.yaw / GetPixelToAngleYAW( ) );
	angReturn.yaw = GetPixelToAngleYAW( ) * i;

	i = int( angReturn.pitch / GetPixelToAnglePITCH( ) );
	angReturn.pitch = GetPixelToAnglePITCH( ) * i;

	angReturn += eng.GetViewAngle( );
	angReturn.roll = eng.GetViewAngle( ).roll;

	return angReturn;
}

angle_t CEngine::VectorToAngle( coordinate_t corOrigin, coordinate_t corDestination )
{
	angle_t angReturn = { 0, 0, 0 };
	vector_t vDelta( corOrigin, corDestination );
	if ( !vDelta.dy && !vDelta.dx )
	{
		angReturn.yaw = 0;
		if ( vDelta.dz > 0 )
		{
			angReturn.pitch = 90;
		}
		else if ( vDelta.dz < 0 )
		{
			angReturn.pitch = -90;
		}
		else
		{
			angReturn.pitch = 0;
		}
	}
	else
	{
		angReturn.yaw = atan2( vDelta.dy, vDelta.dx ) * 180 / PI;
		if ( angReturn.yaw < 0 )
		{
			angReturn.yaw += 360;
		}

		float flTemp = sqrt( vDelta.dx * vDelta.dx + vDelta.dy * vDelta.dy );
		angReturn.pitch = atan2( -vDelta.dz, flTemp ) * 180 / PI;
		if ( angReturn.pitch < 0 )
		{
			angReturn.pitch += 360;
		}
	}
	ClampAngle( angReturn );
	return angReturn;
}

CEngine eng;
