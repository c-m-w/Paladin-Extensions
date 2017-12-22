#include "../../dllmain.h"

void CRadar::Radar( )
{
	while ( plrEntities.val.size( ) != eng.GetGlobalVars( ).ulMaxClients )
	{
		Wait( 1 );
	}
	unsigned short us = 0;
	for ( auto &plrEntity: plrEntities.val )
	{
		//if ( !plrEntities.val.at( ulEntity ).bDormant )
		//{
		if ( plrLocalPlayer.val.ulTeamNum != plrEntity.ulTeamNum )
		{
			plrEntity.bSpotted = true;
			eng.SetEntity( us, plrEntity );
		}
		//}
		us++;
	}
}

CRadar rad;
