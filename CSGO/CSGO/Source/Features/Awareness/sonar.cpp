#include "../../dllmain.h"

void CSonar::Sonar( )
{
	while ( plrEntities.val.size() != eng.GetGlobalVars( ).ulMaxClients )
	{
		Wait( 1 );
	}
	int i = 0;
	for ( auto &plrEntity : plrEntities.val )
	{
		//if ( !plrEntities.val.at( ulEntity ).bDormant )
		//{
			if ( plrLocalPlayer.val.ulTeamNum != plrEntity.ulTeamNum )
			{
				vector_t vecPlayerToEntity( plrEntity.corOrigin, plrLocalPlayer.val.corOrigin );

				float flDistance = sqrt( pow( vecPlayerToEntity.dx, 2 ) + pow( vecPlayerToEntity.dy, 2 ) + pow( vecPlayerToEntity.dz, 2 ) );

				std::cout << "Current Entity: " << i << "\n Distance from Local Player: " << flDistance << std::endl;
			}
		//}
		i++;
	}
}

CSonar son;
