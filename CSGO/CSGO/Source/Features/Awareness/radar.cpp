#include "../../dllmain.h"

void CRadar::Radar( )
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
				CPlayer plrNewEntity = aplrEntitiesCopy.at( ulEntity ).xValue;
				plrNewEntity.bSpotted = true;
				eng.SetEntity( ulEntity, plrNewEntity );
			}
		}
	}
}

CRadar rad;
