/// Aim Assistance.cpp

#include "Precompile.hpp"

#include "../../../../CSGOX.hpp"

EXTENDED_SDK_CLASS( CNetChannel ) *test2;

void CAimAssistance::flee( )
{
	test2->OurCustomNetChannelFunction( );

	if ( !pLocalPlayer )
		return;

	if ( !pLocalPlayer->IsVulnerable( ) )
		return;
}

void CAimAssistance::AimAtTarget( )
{

}
