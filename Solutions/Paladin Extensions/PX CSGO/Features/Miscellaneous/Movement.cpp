/// Movement.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

namespace PX::Features::Miscellaneous
{
	void PX_API AutoJump( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
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

	void PX_API CircleStrafe( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		constexpr auto flStrafeRadius = 500.f;
		volatile static auto bWasEnabled = false;
		volatile static auto flYaw = 0.f, flOldYaw = 0.f;
		const auto vecVelocity = pLocalPlayer->m_vecVelocity( );
		const auto flVelocity = D3DXToDegree( atan2f( vecVelocity.y, vecVelocity.x ) ),
			flNetVelocity = sqrtf( powf( vecVelocity.x, 2.f ) + powf( vecVelocity.y, 2.f ) );
		const auto flTicks = flStrafeRadius / flNetVelocity / pGlobalVariables->m_flIntervalPerTick;
		const auto flStep = 90.f / flTicks;


		std::cout << flVelocity << std::endl;
		if ( !_Settings._Miscellaneous._Movement.bCircleStrafe
			 && ( fabsf( flVelocity - pCmd->viewangles.yaw ) < flStep || !bWasEnabled ) )
		{
			bWasEnabled = false;
			return;
		}

		if ( !bWasEnabled )
			flYaw = flVelocity;
		else
			flYaw += flStep;

		flYaw -= pCmd->viewangles.yaw - flOldYaw;
		pCmd->forwardmove = sin( D3DXToRadian( flYaw ) ) * 450.f;
		pCmd->sidemove = cos( D3DXToRadian( flYaw ) ) * 450.f;

		bWasEnabled = true;
		flOldYaw = pCmd->viewangles.yaw;
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
