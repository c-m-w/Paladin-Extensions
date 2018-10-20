/// Trigger.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX::Information;

namespace PX::Features::Combat
{
	void PX_API Trigger( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		Vector vecEnd;
		CTraceFilter tfFilter;
		Ray_t rRay;
		CGameTrace gtRay;

		Tools::TransformAngle( pCmd->viewangles, vecEnd );
		vecEnd *= 8192;
		vecEnd += pLocalPlayer->GetViewPosition( );
		tfFilter.pSkip = pLocalPlayer;
		rRay.Init( pLocalPlayer->GetViewPosition( ), vecEnd );
		Pointers::pEngineTrace->TraceRay( rRay, PX_MASK_VISIBLE, &tfFilter, &gtRay );

		if ( gtRay.hit_entity && player_ptr_t( gtRay.hit_entity )->IsPlayer( ) )
			pCmd->buttons |= IN_ATTACK;
	}
}
