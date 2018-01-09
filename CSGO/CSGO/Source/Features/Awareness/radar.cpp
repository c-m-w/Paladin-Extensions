#include "../../dllmain.h"

void CRadar::Radar( )
{
	for ( int iEntity = 0; iEntity < 64; iEntity++ )
	{
		if ( !plrEntities[ iEntity ].xValue._My_val.bDormant )
		{
			if ( plrLocalPlayer.xValue._My_val.iTeamNum != plrEntities[ iEntity ].xValue._My_val.iTeamNum )
			{
				if ( plrEntities[ iEntity ].xValue._My_val.bLifeState == LIFE_ALIVE )
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
