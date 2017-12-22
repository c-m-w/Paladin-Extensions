#include "../../dllmain.h"

void CSonar::Sonar( )
{
	for ( int iEntity = 1; iEntity < eng.GetGlobalVars( ).maxClients; iEntity++ )
	{
		if ( /*!plrEntities.val.at( iEntity ).bDormant*/1 )
		{
			if ( plrLocalPlayer.val.iTeamNum != plrEntities.val.at( iEntity ).iTeamNum )
			{
				vector_t vecPlayerToEntity( plrEntities.val.at( iEntity ).corOrigin, plrLocalPlayer.val.corOrigin );

				float flDistance = sqrt( pow( vecPlayerToEntity.dx, 2 ) + pow( vecPlayerToEntity.dy, 2 ) + pow( vecPlayerToEntity.dz, 2 ) );

				std::cout << "Current Entity: " << iEntity << "\n Distance from Local Player: " << flDistance << std::endl;
			}
		}
	}
}

CSonar son;
