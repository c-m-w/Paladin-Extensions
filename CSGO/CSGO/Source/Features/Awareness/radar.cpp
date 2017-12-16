#include "../../dllmain.h"

void CRadar::Radar( )
{
	for ( int iEntity = 1; iEntity < eng.GetGlobalVars( ).maxClients; iEntity++ )
	{
		if ( !eng.GetEntityDormancy( iEntity ) )
		{
			if ( eng.GetTeam( ) != eng.GetEntityTeam( iEntity ) )
			{
				eng.SetEntitySpottedState( iEntity, true );
			}
		}
	}
}

CRadar rad;
