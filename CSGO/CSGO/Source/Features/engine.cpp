#include "../dllmain.h"

CGlobalVars CEngine::GetGlobalVars( )
{
	mem.Get( dwGlobalVars );
	return dwGlobalVars.val;
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

void CEngine::SetViewAngle( angle_t cs_aNewViewAngle )
{
	if ( GetViewAngle( ) != cs_aNewViewAngle )
	{
		cs_aViewAngle.val = ClampAngle( NormalizeAngle( cs_aNewViewAngle ) );
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
	if ( GetAttack( ) != KS_DEFAULT | ksType )
	{
		fForceAttack.val = KS_DEFAULT | ksType;
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
	if ( GetJump( ) != KS_DEFAULT | ksType )
	{
		fForceJump.val = KS_DEFAULT | ksType;
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

bool CEngine::GetEntityDormant( int iEntity )
{
	el_bDormant.loc = GetEntityBase( iEntity ) + el_bDormant.off;
	mem.Get( el_bDormant );
	return el_bDormant.val;
}

bool CEngine::GetEntitySpotted( int iEntity )
{
	el_bSpotted.loc = GetEntityBase( iEntity ) + el_bSpotted.off;
	mem.Get( el_bSpotted );
	return el_bSpotted.val;
}

void CEngine::SetEntitySpotted( int iEntity, bool el_bNewSpotted )
{
	if ( GetEntitySpotted( iEntity ) != el_bNewSpotted )
	{
		el_bSpotted.val = el_bNewSpotted;
		mem.Set( el_bSpotted );
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

void CEngine::SetFieldOfView( int lp_iNewFOV )
{
	if ( GetFieldOfView( ) != lp_iNewFOV )
	{
		lp_iFOV.val = lp_iNewFOV;
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

void CEngine::SetFlashMaxAlpha( float lp_flNewFlashMaxAlpha )
{
	if ( GetFlashMaxAlpha( ) != lp_flNewFlashMaxAlpha )
	{
		lp_flFlashMaxAlpha.val = lp_flNewFlashMaxAlpha;
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

void CEngine::WaitTicks( int iTicksToWait )
{
	iTicksToWait += GetGlobalVars( ).tickcount;
	while ( iTicksToWait > GetGlobalVars( ).tickcount )
	{
		Wait( 1 );
	}
}

float CEngine::GetPixelToAngleYAW( )
{
	return 0.022f * GetSensitivity( ) * all.GetWindowsSensitivity( ); // * ZOOM SENS IF ZOOMED
}

float CEngine::GetPixelToAnglePITCH( )
{
	return 0.022f * GetSensitivity( ) * all.GetWindowsSensitivity( ); // * ZOOM SENS IF ZOOMED
}

angle_t CEngine::ClampAngle( angle_t aToClamp )
{
	if ( aToClamp.pitch > 89 )
	{
		aToClamp.pitch = 89;
	}
	else if ( aToClamp.pitch < -89 )
	{
		aToClamp.pitch = -89;
	}
	while ( aToClamp.yaw < -180 )
	{
		aToClamp.yaw += 360;
	}
	while ( aToClamp.yaw > 180 )
	{
		aToClamp.yaw -= 360;
	}
	if ( aToClamp.roll > 50 )
	{
		aToClamp.roll = 50;
	}
	else if ( aToClamp.roll < -50 )
	{
		aToClamp.roll = -50;
	}
	return aToClamp;
}

angle_t CEngine::NormalizeAngle( angle_t aDestination )
{
	angle_t aNewAngle = aDestination - eng.GetViewAngle( );

	// if aNewAngle.pitch > 22(?), aNewAngle.pitch = 22(?) TODO
	float flAngleChange = sqrt( aNewAngle.pitch * aNewAngle.pitch + aNewAngle.yaw * aNewAngle.yaw );
	if ( fabs( flAngleChange ) > MAX_ANGLE_DELTA )
	{
		float flAngleScaleFactor = MAX_ANGLE_DELTA / fabs( flAngleChange );
		aNewAngle.pitch *= flAngleScaleFactor;
		aNewAngle.yaw *= flAngleScaleFactor;
	}
	if ( aNewAngle.yaw / GetPixelToAngleYAW( ) > GetPixelToAngleYAW( ) / 2 )
	{
		int i = int( aNewAngle.yaw / GetPixelToAngleYAW( ) + GetPixelToAngleYAW( ) );
		aNewAngle.yaw = GetPixelToAngleYAW( ) * i;
	}
	else
	{
		int i = int( aNewAngle.yaw / GetPixelToAngleYAW( ) );
		aNewAngle.yaw = GetPixelToAngleYAW( ) * i;
	}
	if ( aNewAngle.pitch / GetPixelToAnglePITCH( ) > GetPixelToAnglePITCH( ) / 2 )
	{
		int i = int( aNewAngle.pitch / GetPixelToAnglePITCH( ) + GetPixelToAnglePITCH( ) );
		aNewAngle.pitch = GetPixelToAnglePITCH( ) * i;
	}
	else
	{
		int i = int( aNewAngle.pitch / GetPixelToAnglePITCH( ) );
		aNewAngle.pitch = GetPixelToAnglePITCH( ) * i;
	}
	return aNewAngle + eng.GetViewAngle( );
}

angle_t CEngine::VectorToAngle( coordinate_t cOrigin, coordinate_t cDestination )
{
	angle_t aReturn = { 0, 0, 0 };
	vector_t vDelta( cOrigin, cDestination );
	if ( vDelta.dy == 0 && vDelta.dx == 0 )
	{
		aReturn.yaw = 0;
		if ( vDelta.dz > 0 )
		{
			aReturn.pitch = 90;
		}
		else if ( vDelta.dz < 0 )
		{
			aReturn.pitch = -90;
		}
		else
		{
			aReturn.pitch = 0;
		}
	}
	else
	{
		aReturn.yaw = atan2( vDelta.dy, vDelta.dx ) * 180 / PI;
		if ( aReturn.yaw < 0 )
		{
			aReturn.yaw += 360;
		}
		float flTemp = sqrt( vDelta.dx * vDelta.dx + vDelta.dy * vDelta.dy );
		aReturn.pitch = atan2( -vDelta.dz, flTemp ) * 180 / PI;
		if ( aReturn.pitch < 0 )
		{
			aReturn.pitch += 360;
		}
	}
	ClampAngle( aReturn );
	return aReturn;
}

CEngine eng;
