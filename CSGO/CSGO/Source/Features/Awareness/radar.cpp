#include "../../dllmain.h"

void CRadar::Radar( )
{
	for ( int iEntity { }; iEntity <= 64; iEntity++ )
	{
		if ( !plrEntities[ iEntity ].xValue.bDormant )
		{
			if ( plrLocalPlayer.xValue.iTeamNum != plrEntities[ iEntity ].xValue.iTeamNum )
			{
				if ( plrEntities[ iEntity ].xValue.bLifeState == LIFE_ALIVE )
				{
					CPlayer plrNewEntity = plrEntities[ iEntity ].xValue;
					plrNewEntity.bSpotted = true;
					eng.SetEntity( iEntity, plrNewEntity );
				}
			}
		}
	}
}

CRadar rad;
