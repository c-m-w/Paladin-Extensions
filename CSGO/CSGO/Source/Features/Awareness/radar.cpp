#include "../../dllmain.h"

void CRadar::Radar( )
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
				CPlayer plrNewEntity = aplrEntities.at( ulEntity ).xValue;
				plrNewEntity.bSpotted = true;
				eng.SetEntity( ulEntity, plrNewEntity );
			}
		}
	}
}

CRadar rad;
