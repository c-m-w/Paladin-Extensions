#include "../../dllmain.h"

void CSonar::Sonar( )
{
	for ( unsigned long ulEntity = 0; ulEntity < 64; ulEntity++ )
	{
		if ( !plrEntities[ulEntity]._My_val.xValue.bDormant )
		{
			if ( plrLocalPlayer._My_val.xValue.ulTeamNum != plrEntities[ulEntity]._My_val.xValue.ulTeamNum )
			{
				vector_t vecEntityDistance( plrEntities[ulEntity]._My_val.xValue.corOrigin, plrLocalPlayer._My_val.xValue.corOrigin );

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
