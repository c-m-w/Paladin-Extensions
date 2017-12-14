#include "../../dllmain.h"

void CRadar::Radar( )
{
	for ( int iEntity = 1; iEntity < eng.GetGlobalVars( ).maxClients; iEntity++ )
	{
		if ( !eng.GetEntityDormant( iEntity ) ) {
			if ( eng.GetTeam( ) != eng.GetEntityTeam( iEntity ) )
			{
				eng.SetEntitySpotted( iEntity, true );
			}
		}
	}
	eng.WaitTicks( 1 );
}

CRadar rad;
