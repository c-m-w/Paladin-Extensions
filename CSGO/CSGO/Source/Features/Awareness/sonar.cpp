#include "../../dllmain.h"

void CSonar::Sonar( )
{
	int iEntity = eng.GetClosestEnemyToPosition( );

	if ( !plrEntities[ iEntity ].xValue._My_val.bDormant )
	{
		if ( plrEntities[ iEntity ].xValue._My_val.bLifeState == LIFE_ALIVE )
		{
		if ( plrLocalPlayer.xValue._My_val.iTeamNum != plrEntities[ iEntity ].xValue._My_val.iTeamNum )
		{
				vector_t vecEntityDistance( plrEntities[ iEntity ].xValue._My_val.corOrigin, plrLocalPlayer.xValue._My_val.corOrigin );

				float flDistance = sqrt( pow( vecEntityDistance.flDeltaX, 2 ) + pow( vecEntityDistance.flDeltaY, 2 ) + pow( vecEntityDistance.flDeltaZ, 2 ) );

				if ( flDistance < 1000.f )
				{
					Beep( DWORD( ( 1000.f - flDistance ) / 1000.f ), 50 );
					Wait( int( flDistance / 1000.f ) );
				}
			}
		}
	}
}

CSonar son;
