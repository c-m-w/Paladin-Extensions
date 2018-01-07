#include "../../dllmain.h"

void CRadar::Radar( )
{
	for ( unsigned long ulEntity = 0; ulEntity < 64; ulEntity++ )
	{
		if ( !plrEntities[ ulEntity ].xValue._My_val.bDormant )
		{
			if ( plrLocalPlayer.xValue._My_val.ulTeamNum != plrEntities[ ulEntity ].xValue._My_val.ulTeamNum )
			{
				if ( plrEntities[ ulEntity ].xValue._My_val.bLifeState == LIFE_ALIVE )
				{
					CPlayer plrNewEntity = plrEntities[ ulEntity ].xValue;
					plrNewEntity.bSpotted = true;
					eng.SetEntity( ulEntity, plrNewEntity );
				}
			}
		}
	}
}

CRadar rad;
