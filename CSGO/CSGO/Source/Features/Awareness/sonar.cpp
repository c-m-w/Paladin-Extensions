#include "../../dllmain.h"

void CSonar::Sonar( )
{
	for ( int iEntity = 1; iEntity < eng.GetGlobalVars( ).maxClients; iEntity++ )
	{
		if ( !eng.GetEntityDormancy( iEntity ) )
		{
			if ( eng.GetTeam( ) != eng.GetEntityTeam( iEntity ) )
			{
				vector_t vecPlayerToEntity( eng.GetEntityOrigin( iEntity ), eng.GetEntityOrigin( 1 ) );

				float flDistance = sqrt( pow( vecPlayerToEntity.dx, 2 ) + pow( vecPlayerToEntity.dy, 2 ) + pow( vecPlayerToEntity.dz, 2 ) );

				std::cout << "Current Entity: " << iEntity << "\n Distance from Local Player: " << flDistance << std::endl;
			}
		}
	}
}

CSonar son;
