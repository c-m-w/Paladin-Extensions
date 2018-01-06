#include "../../dllmain.h"

void CSonar::Sonar( )
{
	for (auto & plrEntity : plrEntities)
	{
		if ( !plrEntity._My_val.xValue.bDormant )
		{
			if ( plrLocalPlayer._My_val.xValue.ulTeamNum != plrEntity._My_val.xValue.ulTeamNum )
			{
				if ( plrEntity._My_val.xValue.bLifeState == LIFE_ALIVE )
				{
					vector_t vecEntityDistance( plrEntity._My_val.xValue.corOrigin, plrLocalPlayer._My_val.xValue.corOrigin );

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
