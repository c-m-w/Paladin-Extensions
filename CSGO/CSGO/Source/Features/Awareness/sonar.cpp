#include "../../dllmain.h"

void CSonar::Sonar( )
{
	for ( int iEntity = 1; iEntity < eng.GetGlobalVars( ).maxClients; iEntity++ )
	{
		if ( !eng.GetEntityDormancy( iEntity ) )
		{
			if ( eng.GetTeam( ) != eng.GetEntityTeam( iEntity ) )
			{
				float flDelta[3];
				flDelta[0] = eng.GetEntityOrigin( iEntity ).x - eng.GetEntityOrigin( 1 ).x;
				flDelta[1] = eng.GetEntityOrigin( iEntity ).y - eng.GetEntityOrigin( 1 ).y;
				flDelta[2] = eng.GetEntityOrigin( iEntity ).z - eng.GetEntityOrigin( 1 ).z;

				float flDistance = sqrt( pow( flDelta[0], 2 ) + pow( flDelta[1], 2 ) + pow( flDelta[2], 2 ) );

				std::cout << "Current Entity: " << iEntity << "\n    Distance from Local Player: " << flDistance << std::endl;
			}
		}
	}
}

CSonar son;
