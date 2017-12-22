#include "../../dllmain.h"

void CSonar::Sonar( )
{
	for ( unsigned long ulEntity = 1; ulEntity < eng.GetGlobalVars( ).maxClients; ulEntity++ )
	{
		if ( /*!plrEntities.val.at( ulEntity ).bDormant*/1 )
		{
			if ( plrLocalPlayer.val.ulTeamNum != plrEntities.val.at( ulEntity ).ulTeamNum )
			{
				vector_t vecPlayerToEntity( plrEntities.val.at( ulEntity ).corOrigin, plrLocalPlayer.val.corOrigin );

				float flDistance = sqrt( pow( vecPlayerToEntity.dx, 2 ) + pow( vecPlayerToEntity.dy, 2 ) + pow( vecPlayerToEntity.dz, 2 ) );

				std::cout << "Current Entity: " << ulEntity << "\n Distance from Local Player: " << flDistance << std::endl;
			}
		}
	}
}

CSonar son;
