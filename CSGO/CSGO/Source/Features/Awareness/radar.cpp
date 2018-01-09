#include "../../dllmain.h"

void CRadar::Radar( )
{
	for ( unsigned int uiEntity = 0; uiEntity < 64; uiEntity++ )
	{
		if ( !plrEntities[ uiEntity ].xValue._My_val.bDormant )
		{
			if ( plrLocalPlayer.xValue._My_val.uiTeamNum != plrEntities[ uiEntity ].xValue._My_val.uiTeamNum )
			{
				if ( plrEntities[ uiEntity ].xValue._My_val.bLifeState == LIFE_ALIVE )
				{
					CPlayer plrNewEntity = plrEntities[ uiEntity ].xValue;
					plrNewEntity.bSpotted = true;
					eng.SetEntity( uiEntity, plrNewEntity );
				}
			}
		}
	}
}

CRadar rad;
