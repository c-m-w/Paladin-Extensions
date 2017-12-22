#include "../../dllmain.h"

void CRadar::Radar( )
{
	for ( unsigned long ulEntity = 1; ulEntity < eng.GetGlobalVars( ).maxClients; ulEntity++ )
	{
		if ( /*!plrEntities.val.at( ulEntity ).bDormant*/1 )
		{
			if ( plrLocalPlayer.val.ulTeamNum != plrEntities.val.at( ulEntity ).ulTeamNum )
			{
				plrEntities.val.at( ulEntity ).bSpotted = true;
				eng.SetEntity( ulEntity, plrEntities.val.at( ulEntity ) );
			}
		}
	}
}

CRadar rad;
