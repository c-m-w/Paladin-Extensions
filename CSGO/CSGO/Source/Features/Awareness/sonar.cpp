#include "../../dllmain.h"

void CSonar::Sonar( )
{
	while ( plrEntities.val.size( ) != eng.GetGlobalVars( ).ulMaxClients )
	{
		Wait( 1 );
	}
	for ( unsigned long ulEntity = plrEntities.val.size( ); ulEntity > 0; ulEntity-- )
	{
		if ( !plrEntities.val.at( ulEntity ).bDormant )
		{
			if ( plrLocalPlayer.val.ulTeamNum != plrEntities.val.at( ulEntity ).ulTeamNum )
			{
				vector_t vecEntityDistance( plrEntities.val.at( ulEntity ).corOrigin, plrLocalPlayer.val.corOrigin );

				float flDistance = sqrt( pow( vecEntityDistance.dx, 2 ) + pow( vecEntityDistance.dy, 2 ) + pow( vecEntityDistance.dz, 2 ) );

				if ( flDistance < 1000.f )
				{
					Beep( DWORD( ( 1000.f - flDistance ) / 1000.f ), 50 );
					Wait( long( flDistance / 1000.f ) );
				}
			}
		}
	}
}

CSonar son;
