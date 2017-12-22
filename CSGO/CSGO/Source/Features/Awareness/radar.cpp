#include "../../dllmain.h"

void CRadar::Radar( )
{
	for ( int iEntity = 1; iEntity < eng.GetGlobalVars( ).maxClients; iEntity++ )
	{
		if ( /*!plrEntities.val.at( iEntity ).bDormant*/1 )
		{
			if ( plrLocalPlayer.val.iTeamNum != plrEntities.val.at( iEntity ).iTeamNum )
			{
				plrEntities.val.at( iEntity ).bSpotted = true;
				eng.SetEntity( iEntity, plrEntities.val.at( iEntity ) );
			}
		}
	}
}

CRadar rad;
