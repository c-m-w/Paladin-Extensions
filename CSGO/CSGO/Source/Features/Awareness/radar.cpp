#include "../../dllmain.h"

void CRadar::Radar( )
{
	for ( unsigned long ulEntity = 0; ulEntity < 64; ulEntity++ )
	{
		if ( !plrEntities[ ulEntity ]._My_val.xValue.bDormant )
		{
			if ( plrLocalPlayer._My_val.xValue.ulTeamNum != plrEntities[ ulEntity ]._My_val.xValue.ulTeamNum )
			{
				CPlayer plrNewEntity = plrEntities[ ulEntity ]._My_val.xValue;
				plrNewEntity.bSpotted = true;
				eng.SetEntity( ulEntity, plrNewEntity );
			}
		}
	}
}

CRadar rad;
