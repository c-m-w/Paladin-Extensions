#include "../../dllmain.h"

void CSonar::Sonar( )
{
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	address_t< CPlayer > aplrEntitiesCopy[64];
	for (int i = 0; i < 64; i++)
	{
		aplrEntitiesCopy[i] = aplrEntities[i];
	}
	for ( unsigned long ulEntity = 0; ulEntity <= 64; ulEntity++ )
	{
		if ( !aplrEntitiesCopy[ulEntity].xValue.bDormant )
		{
			if ( aplrLocalPlayerCopy.xValue.ulTeamNum != aplrEntitiesCopy[ulEntity].xValue.ulTeamNum )
			{
				vector_t vecEntityDistance( aplrEntitiesCopy[ulEntity].xValue.corOrigin, aplrLocalPlayerCopy.xValue.corOrigin );

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
