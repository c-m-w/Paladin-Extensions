#include "../../dllmain.h"

void CSonar::Sonar( )
{
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	std::vector< address_t< CPlayer > > aplrEntitiesCopy;
	for ( size_t sizSize = aplrEntities.size(  ); sizSize > 0; sizSize --)
	{
		aplrEntitiesCopy.push_back( aplrEntities.at( sizSize )._My_val );
	}
	for ( unsigned long ulEntity = aplrEntitiesCopy.size( ); ulEntity > 0; ulEntity-- )
	{
		if ( !aplrEntitiesCopy.at( ulEntity ).xValue.bDormant )
		{
			if ( aplrLocalPlayerCopy.xValue.ulTeamNum != aplrEntitiesCopy.at( ulEntity ).xValue.ulTeamNum )
			{
				vector_t vecEntityDistance( aplrEntitiesCopy.at( ulEntity ).xValue.corOrigin, aplrLocalPlayerCopy.xValue.corOrigin );

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
