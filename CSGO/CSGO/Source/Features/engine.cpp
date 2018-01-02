#include "../dllmain.h"

CGlobalVars CEngine::GetGlobalVars( )
{
	mem.Get( gvGlobalVars );
	return gvGlobalVars.xValue;
}

void CEngine::SetGlobalVars( CGlobalVars gvNewGlobalVars )
{
	gvGlobalVars.xValue = gvNewGlobalVars;
	mem.Set( gvGlobalVars );
}

bool CEngine::GetSendPackets( )
{
	mem.Get( bSendPackets );
	return bSendPackets.xValue;
}

void CEngine::SetSendPackets( bool bNewSendPackets )
{
	if ( GetSendPackets( ) != bNewSendPackets )
	{
		bSendPackets.xValue = bNewSendPackets;
		mem.Set( bSendPackets );
	}
}

DWORD CEngine::GetClientState( )
{
	mem.Get( pdwClientState );
	return pdwClientState.xValue;
}

ESignOnState CEngine::GetSignOnState( )
{
	soSignOnState.dwLocation = GetClientState( ) + soSignOnState.dwOffset;
	mem.Get( soSignOnState );
	return soSignOnState.xValue;
}

angle_t CEngine::GetViewAngle( )
{
	angViewAngle.dwLocation = GetClientState( ) + angViewAngle.dwOffset;
	mem.Get( angViewAngle );
	return angViewAngle.xValue;
}

void CEngine::SetViewAngle( angle_t angNewViewAngle )
{
	if ( GetViewAngle( ) != ClampAngle( NormalizeAngle( angNewViewAngle ) ) )
	{
		angViewAngle.xValue = ClampAngle( NormalizeAngle( angNewViewAngle ) );
		mem.Set( angViewAngle );
	}
}

FLAG CEngine::GetAttack( )
{
	mem.Get( fForceAttack );
	return fForceAttack.xValue;
}

void CEngine::SetAttack( FLAG ksType )
{
	if ( GetAttack( ) != ( ACTION_DEFAULT | ksType ) )
	{
		fForceAttack.xValue = ACTION_DEFAULT | ksType;
		mem.Set( fForceAttack );
	}
}

FLAG CEngine::GetJump( )
{
	mem.Get( fForceJump );
	return fForceJump.xValue;
}

void CEngine::SetJump( FLAG ksType )
{
	if ( GetJump( ) != ( ACTION_DEFAULT | ksType ) )
	{
		fForceJump.xValue = ACTION_DEFAULT | ksType;
		mem.Set( fForceJump );
	}
}

float CEngine::GetSensitivity( )
{
	mem.Get( flSensitivity );
	return flSensitivity.xValue;
}

void CEngine::SetSensitivity( float flNewSensitivity )
{
	Limit( flNewSensitivity, MIN_SENSITIVITY, MAX_SENSITIVITY );
	if ( GetSensitivity( ) != flNewSensitivity )
	{
		flSensitivity.xValue = flNewSensitivity;
		mem.Set( flSensitivity );
	}
}

DWORD CEngine::GetEntityBase( unsigned long ulEntity )
{
	DWORD dwOldEntityList = pdwEntityList.dwLocation;
	pdwEntityList.dwLocation += ulEntity * ENTITY_DISTANCE;
	mem.Get( pdwEntityList );
	pdwEntityList.dwLocation = dwOldEntityList;
	return pdwEntityList.xValue;
}

CPlayer CEngine::GetEntity( unsigned long ulEntity )
{
	address_t< CPlayer > aplrEntityTemp = { 0, 0, GetEntityBase( ulEntity ) };
	mem.Get( aplrEntityTemp );
	aplrEntities[ulEntity] = aplrEntityTemp;
	return aplrEntityTemp.xValue;
}

void CEngine::GetEntities( )
{
	for ( unsigned long ulEntity = 0; ulEntity < 64; ulEntity++ )
	{
		address_t< CPlayer > plrEntity = { 0, 0, GetEntityBase( ulEntity ) };
		mem.Get( plrEntity );
		aplrEntities[ulEntity] = plrEntity;
	}
}

void CEngine::SetEntity( unsigned long ulEntity, CPlayer plrNewEntity )
{
	address_t< CPlayer > aplrNewEntity = { 0, 0, GetEntityBase( ulEntity ), plrNewEntity };
	mem.Set( aplrNewEntity );
}

DWORD CEngine::GetLocalPlayerBase( )
{
	mem.Get( pdwLocalPlayer );
	return pdwLocalPlayer.xValue;
}

CPlayer CEngine::GetLocalPlayer( )
{
	address_t< CPlayer > aplrLocalPlayerTemp = { 0, 0, GetLocalPlayerBase( ) };
	mem.Get( aplrLocalPlayerTemp );
	aplrLocalPlayer = aplrLocalPlayerTemp;
	return aplrLocalPlayerTemp.xValue;
}

void CEngine::SetLocalPlayer( CPlayer plrNewLocalPlayer )
{
	address_t<CPlayer> aplrNewLocalPlayer = aplrLocalPlayer;
	aplrNewLocalPlayer.xValue = plrNewLocalPlayer;
	mem.Set( aplrNewLocalPlayer );
}

float CEngine::GetPixelToAngleYaw( )
{
	return 0.022f * GetSensitivity( ) * all.GetWindowsSensitivity( ); // * ZOOM SENS IF ZOOMED
}

float CEngine::GetPixelToAnglePitch( )
{
	return 0.022f * GetSensitivity( ) * all.GetWindowsSensitivity( ); // * ZOOM SENS IF ZOOMED
}

angle_t CEngine::ClampAngle( angle_t angToClamp )
{
	Limit( angToClamp.flPitch, MIN_PITCH, MAX_PITCH );

	while ( angToClamp.flYaw < MIN_YAW )
	{
		angToClamp.flYaw += 360.f;
	}
	while ( angToClamp.flYaw > MAX_YAW )
	{
		angToClamp.flYaw -= 360.f;
	}

	Limit( angToClamp.flRoll, MIN_ROLL, MAX_ROLL );

	return angToClamp;
}

angle_t CEngine::NormalizeAngle( angle_t angDestination )
{
	angle_t angReturn = angDestination - eng.GetViewAngle( );

	float flAngleChange = sqrt( angReturn.flPitch * angReturn.flPitch + angReturn.flYaw * angReturn.flYaw );

	if ( fabs( flAngleChange ) > MAX_ANGLE_DELTA )
	{
		float flAngleScaleFactor = MAX_ANGLE_DELTA / fabs( flAngleChange );
		angReturn.flPitch *= flAngleScaleFactor;
		angReturn.flYaw *= flAngleScaleFactor;
	}

	unsigned short us = unsigned short( angReturn.flYaw / GetPixelToAngleYaw( ) );
	angReturn.flYaw = GetPixelToAngleYaw( ) * us;

	us = unsigned short( angReturn.flPitch / GetPixelToAnglePitch( ) );
	angReturn.flPitch = GetPixelToAnglePitch( ) * us;

	angReturn += eng.GetViewAngle( );
	angReturn.flRoll = eng.GetViewAngle( ).flRoll;

	return angReturn;
}

angle_t CEngine::VectorToAngle( coordinate_t corOrigin, coordinate_t corDestination )
{
	angle_t angReturn = { 0, 0, 0 };
	vector_t vecDelta( corOrigin, corDestination );
	if ( !vecDelta.flDeltaY && !vecDelta.flDeltaX )
	{
		angReturn.flYaw = 0;
		if ( vecDelta.flDeltaZ > 0 )
		{
			angReturn.flPitch = 90;
		}
		else if ( vecDelta.flDeltaZ < 0 )
		{
			angReturn.flPitch = -90;
		}
		else
		{
			angReturn.flPitch = 0;
		}
	}
	else
	{
		angReturn.flYaw = atan2( vecDelta.flDeltaY, vecDelta.flDeltaX ) * 180/PI;
		if ( angReturn.flYaw < 0 )
		{
			angReturn.flYaw += 360;
		}

		float flTemp = sqrt( vecDelta.flDeltaX * vecDelta.flDeltaX + vecDelta.flDeltaY * vecDelta.flDeltaY );
		angReturn.flPitch = atan2( -vecDelta.flDeltaZ, flTemp ) * 180 / PI;
		if ( angReturn.flPitch < 0 )
		{
			angReturn.flPitch += 360;
		}
	}
	return ClampAngle( angReturn );
}

CEngine eng;
