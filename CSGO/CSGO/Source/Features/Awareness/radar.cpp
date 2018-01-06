#include "../../dllmain.h"

void CRadar::Radar( )
{
	address_t< CPlayer > plrEntitiesCopy[64];
	for ( long i = 0; i < 64; i++ )
	{
		plrEntitiesCopy[ i ] = plrEntities[ i ];
	}
	for ( unsigned long ulEntity = 0; ulEntity < 64; ulEntity++ )
	{
		if ( !plrEntitiesCopy[ ulEntity ].xValue.bDormant )
		{
			if ( plrLocalPlayer._My_val.xValue.ulTeamNum != plrEntitiesCopy[ ulEntity ].xValue.ulTeamNum )
			{
				CPlayer plrNewEntity = plrEntitiesCopy[ ulEntity ].xValue;
				plrNewEntity.bSpotted = true;
				eng.SetEntity( ulEntity, plrNewEntity );
			}
		}
	}
}

CRadar rad;
