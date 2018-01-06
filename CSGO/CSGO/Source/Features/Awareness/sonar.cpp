#include "../../dllmain.h"

void CSonar::Sonar( )
{
	address_t< CPlayer > plrEntitiesCopy[64];
	for ( long i = 0; i < 64; i++ )
	{
		plrEntitiesCopy[ i ] = plrEntities[ i ];
	}
	for ( auto &ulEntity: plrEntitiesCopy )
	{
		if ( !ulEntity.xValue.bDormant )
		{
			if ( plrLocalPlayer._My_val.xValue.ulTeamNum != ulEntity.xValue.ulTeamNum )
			{
				vector_t vecEntityDistance( ulEntity.xValue.corOrigin, plrLocalPlayer._My_val.xValue.corOrigin );

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
