#include "../../dllmain.h"

void CSonar::Sonar( )
{
	for (auto & plrEntity : plrEntities)
	{
		if ( !plrEntity.xValue._My_val.bDormant )
		{
			if ( plrLocalPlayer.xValue._My_val.ulTeamNum != plrEntity.xValue._My_val.ulTeamNum )
			{
				if ( plrEntity.xValue._My_val.bLifeState == LIFE_ALIVE )
				{
					vector_t vecEntityDistance( plrEntity.xValue._My_val.corOrigin, plrLocalPlayer.xValue._My_val.corOrigin );

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
}

CSonar son;
