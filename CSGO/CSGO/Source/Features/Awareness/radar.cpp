#include "../../dllmain.h"

void CRadar::Radar( )
{
	while ( plrEntities.val.size() != eng.GetGlobalVars( ).maxClients )
	{
		Wait( 1 );
	}
	int i = 0;
	for ( auto &plrEntity : plrEntities.val )
	{
		if ( /*!plrEntities.val.at( ulEntity ).bDormant*/1 )
		{
			if ( plrLocalPlayer.val.ulTeamNum != plrEntity.ulTeamNum )
			{
				plrEntity.bSpotted = true;
				eng.SetEntity( i, plrEntity );
			}
		}
		i++;
	}
}

CRadar rad;
