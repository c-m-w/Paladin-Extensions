#include "../../dllmain.h"

void CSonar::Sonar( )
{
	while ( aplrEntities.size( ) != eng.GetGlobalVars( ).ulMaxClients )
	{
		Wait( 1 );
	}
	for ( unsigned long ulEntity = aplrEntities.size( ); ulEntity > 0; ulEntity-- )
	{
		if ( !aplrEntities.at( ulEntity ).xValue.bDormant )
		{
			if ( aplrLocalPlayer.xValue.ulTeamNum != aplrEntities.at( ulEntity ).xValue.ulTeamNum )
			{
				vector_t vecEntityDistance( aplrEntities.at( ulEntity ).xValue.corOrigin, aplrLocalPlayer.xValue.corOrigin );

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
