/// Movement.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

namespace PX::Features::Miscellaneous
{
	void PX_API AutoJump( player_ptr_t pLocalPlayer, CUserCmd *pCmd )
	{
		return;
		if ( !_Settings._Miscellaneous._Movement.bAutomaticJump
			|| !pLocalPlayer->IsAlive( ) )
			return;

		// need movetype...

		if ( pCmd->buttons & IN_JUMP )
			if ( !( pLocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
				if ( !( pGlobalVariables->m_iTickCount % ( int( _Settings._Miscellaneous._Movement.flMissChance / pGlobalVariables->m_flIntervalPerTick ) + 1 ) ) )
					pCmd->buttons &= ~IN_JUMP;
	}

	void AutoEdgeJump( CUserCmd *pCmd )
	{
		return;
		// engine prediction
		// https://www.unknowncheats.me/forum/1338060-post2.html
		// ray trace downward is also an option, but it's ghetto
	}

	void AutoStrafe( player_ptr_t pLocalPlayer, CUserCmd *pCmd )
	{
		return;
		if ( !_Settings._Miscellaneous._Movement.bAutomaticStrafe && !_Settings._Miscellaneous._Movement.bAutonomousStrafe )
			return;

		// humanized
		// todo sideways, backwards based on velocity direction
		if ( !!_Settings._Miscellaneous._Movement.bAutomaticStrafe )
		{
			static int iLastMotionlessTick;
			static auto cl_sidespeed = pConVar->FindVar( PX_XOR( "cl_sidespeed" ) );
			if ( !( pLocalPlayer->m_fFlags( ) & FL_ONGROUND )
				&& ( abs( pCmd->mousedx ) > 0
					&& iLastMotionlessTick - pGlobalVariables->m_iTickCount > 100.f - _Settings._Miscellaneous._Movement.flSync ) )
				return ( void )( pCmd->sidemove = float( abs( pCmd->mousedx ) / pCmd->mousedx ) * cl_sidespeed->GetFloat( ), pCmd->forwardmove = 0.f );

			iLastMotionlessTick = pGlobalVariables->m_iTickCount;
		}
		else
		{
			// b1g method of doing it silently based on airaccel. it's broken bad, though...
			// https://www.unknowncheats.me/forum/1394519-post1.html
			//if ( autonomous_strafe_key )
		}
	}

	// https://www.unknowncheats.me/forum/counterstrike-1-5-1-6-and-mods/208650-autostrafe.html
	// some more kz stuff
}
