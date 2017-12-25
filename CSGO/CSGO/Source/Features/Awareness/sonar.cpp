#include "../../dllmain.h"

void CSonar::Sonar( )
{
	while ( plrEntities.size( ) != eng.GetGlobalVars( ).ulMaxClients )
	{
		Wait( 1 );
	}
	for ( unsigned long ulEntity = plrEntities.size( ); ulEntity > 0; ulEntity-- )
	{
		if ( !plrEntities.at( ulEntity ).xValue.bDormant )
		{
			if ( plrLocalPlayer.xValue.ulTeamNum != plrEntities.at( ulEntity ).xValue.ulTeamNum )
			{
				vector_t vecEntityDistance( plrEntities.at( ulEntity ).xValue.corOrigin, plrLocalPlayer.xValue.corOrigin );

				float flDistance = sqrt( pow( vecEntityDistance.flDeltaX, 2 ) + pow( vecEntityDistance.flDeltaY, 2 ) + pow( vecEntityDistance.flDeltaZ, 2 ) );

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
