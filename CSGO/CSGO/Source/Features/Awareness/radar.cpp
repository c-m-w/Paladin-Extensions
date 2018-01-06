#include "../../dllmain.h"

void CRadar::Radar( )
{
	address_t< CPlayer > aplrLocalPlayerCopy = plrLocalPlayer;
	address_t< CPlayer > aplrEntitiesCopy[64];
	for ( int i = 0; i < 64; i++ )
	{
		aplrEntitiesCopy[ i ] = plrEntities[ i ];
	}
	for ( unsigned long ulEntity = 0; ulEntity < 64; ulEntity++ )
	{
		if ( !aplrEntitiesCopy[ ulEntity ].xValue.bDormant )
		{
			if ( aplrLocalPlayerCopy.xValue.ulTeamNum != aplrEntitiesCopy[ ulEntity ].xValue.ulTeamNum )
			{
				CPlayer plrNewEntity = aplrEntitiesCopy[ ulEntity ].xValue;
				plrNewEntity.bSpotted = true;
				eng.SetEntity( ulEntity, plrNewEntity );
			}
		}
	}
}

CRadar rad;
