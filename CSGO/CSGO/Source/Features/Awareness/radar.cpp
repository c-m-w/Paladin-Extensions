#include "../../dllmain.h"

void CRadar::Radar( )
{
	while ( plrEntities.size( ) != eng.GetGlobalVars( ).ulMaxClients )
	{
		Wait( 1 );
	}
	for ( unsigned long ulEntity = plrEntities.size( ); ulEntity > 0; ulEntity-- )
	{
		if ( !plrEntities.at( ulEntity ).xValue.bDormant )
		{
			if ( plrLocalPlayer.xValue.ulTeamNum != plrEntities.at( ulEntity ).xValue.ulTeamNum )
			{
				plrEntities.at( ulEntity ).xValue.bSpotted = true;
				eng.SetEntity( ulEntity );
			}
		}
	}
}

CRadar rad;
