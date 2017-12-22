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
	soSignOnState.loc = GetClientState( ) + soSignOnState.off;
	mem.Get( soSignOnState );
	return soSignOnState.val;
}

angle_t CEngine::GetViewAngle( )
{
	angViewAngle.loc = GetClientState( ) + angViewAngle.off;
	mem.Get( angViewAngle );
	return angViewAngle.val;
}

void CEngine::SetViewAngle( angle_t angNewViewAngle )
{
	if ( GetViewAngle( ) != ClampAngle( NormalizeAngle( angNewViewAngle ) ) )
	{
		angViewAngle.val = ClampAngle( NormalizeAngle( angNewViewAngle ) );
		mem.Set( angViewAngle );
	}
}

FLAG CEngine::GetAttack( )
{
	mem.Get( fForceAttack );
	return fForceAttack.val;
}

void CEngine::SetAttack( FLAG ksType )
{
	if ( GetAttack( ) != ( FA_DEFAULT | ksType ) )
	{
		fForceAttack.val = FA_DEFAULT | ksType;
		mem.Set( fForceAttack );
	}
}

FLAG CEngine::GetJump( )
{
	mem.Get( fForceJump );
	return fForceJump.val;
}

void CEngine::SetJump( FLAG ksType )
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

DWORD CEngine::GetEntityBase( unsigned long ulEntity )
{
	DWORD dwOldEntityList = pdwEntityList.loc;
	pdwEntityList.loc += ( ulEntity - 1 ) * ENTITY_DISTANCE;
	mem.Get( pdwEntityList );
	pdwEntityList.loc = dwOldEntityList;
	return pdwEntityList.val;
}

CPlayer CEngine::GetEntity( unsigned long ulEntity )
{
	address_t<CPlayer> plrEntity = { 0, 0, GetEntityBase( ulEntity ) };
	mem.Get( plrEntity );
	return plrEntity.val;
}

void CEngine::GetEntities( )
{
	plrEntities.val.clear( );
	for ( unsigned long ul = GetGlobalVars( ).maxClients; ul > 0; ul-- )
	{
		plrEntities.val.push_back( GetEntity( ul ) );
	}
};

void CEngine::SetEntity( unsigned long ulEntity, CPlayer plrNewEntity )
{
	address_t< CPlayer > aplrEntity = { 0, 0, GetEntityBase( ulEntity ), plrNewEntity };
	mem.Set( aplrEntity );
};

DWORD CEngine::GetLocalPlayerBase( )
{
	mem.Get( pdwLocalPlayer );
	return pdwLocalPlayer.val;
}

CPlayer CEngine::GetLocalPlayer( )
{
	plrLocalPlayer = { 0, 0, GetLocalPlayerBase( ) };
	mem.Get( plrLocalPlayer );
	return plrLocalPlayer.val;
}

void CEngine::SetLocalPlayer( )
{ 
	mem.Set( plrLocalPlayer );
};

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

	unsigned short us = unsigned short( angReturn.yaw / GetPixelToAngleYAW( ) );
	angReturn.yaw = GetPixelToAngleYAW( ) * us;

	us = unsigned short( angReturn.pitch / GetPixelToAnglePITCH( ) );
	angReturn.pitch = GetPixelToAnglePITCH( ) * us;

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
