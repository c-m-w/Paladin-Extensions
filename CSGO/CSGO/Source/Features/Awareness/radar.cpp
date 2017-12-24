#include "../../dllmain.h"

void CRadar::Radar( )
{
	while ( plrEntities.val.size( ) != eng.GetGlobalVars( ).ulMaxClients )
	{
		Wait( 1 );
	}
	for ( unsigned long ulEntity = plrEntities.val.size( ); ulEntity > 0; ulEntity-- )
	{
		if ( !plrEntities.val.at( ulEntity ).bDormant )
		{
			if ( plrLocalPlayer.val.ulTeamNum != plrEntities.val.at( ulEntity ).ulTeamNum )
			{
				plrEntities.val.at( ulEntity ).bSpotted = true;
				eng.SetEntity( ulEntity );
			}
		}
	}
}

CRadar rad;
