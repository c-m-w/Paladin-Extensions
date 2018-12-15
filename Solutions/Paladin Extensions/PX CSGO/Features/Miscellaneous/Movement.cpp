/// Movement.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

namespace PX::Features::Miscellaneous
{
	void PX_API AutoJump( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		if ( !_Settings._Miscellaneous._Movement.bAutomaticJump )
			return;

		const auto movetype = pLocalPlayer->movetype( );
		if ( movetype != MOVETYPE_NOCLIP && movetype != MOVETYPE_LADDER ) // don't change anything in these states
			if ( !( pLocalPlayer->m_fFlags( ) & FL_ONGROUND )
				 || pGlobalVariables->m_iTickCount % ( _Settings._Miscellaneous._Movement.iMissTicks + 1 ) ) // if they aren't on the ground or if they missed, stop jumping
				pCmd->buttons &= ~IN_JUMP;
			else
				pCmd->buttons |= IN_JUMP;
	}

	void PX_API CircleStrafe( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		constexpr auto flAcceleration = 30.f;
		volatile static auto bWasEnabled = false;
		volatile static auto flYaw = 0.f, flOldYaw = 0.f, flLastVelocity = 0.f;
		const auto vecVelocity = pLocalPlayer->m_vecVelocity( );
		const auto flNetVelocity = sqrtf( powf( vecVelocity.x, 2.f ) + powf( vecVelocity.y, 2.f ) );
		const auto flStrafeRadius = powf( powf( ( flAcceleration + 0.2769974f ) / 479.8696974f, 0.52318110855f ) * 19.23914f / 62.1f, 2.f ); // max vel = 62.1 * sqrtf(x)
		//const auto flMaxVelocity = 6.21f * sqrtf( flStrafeRadius ); // acceleration = -0.2769974 + (479.5927 - -0.2769974)/(1 + (max vel/19.23914)^1.911384)
		const auto flTicks = flStrafeRadius * .5f * D3DX_PI / flNetVelocity / pGlobalVariables->m_flIntervalPerTick;
		const auto flStep = 90.f / flTicks;
		auto flVelocity = D3DXToDegree( atan2f( vecVelocity.y, vecVelocity.x ) );

		if ( !_Settings._Miscellaneous._Movement.bCircleStrafe
			 && ( fabsf( flVelocity - pCmd->viewangles.yaw ) < flStep || !bWasEnabled )
			 || !( pCmd->buttons & IN_JUMP ) )
		{
			bWasEnabled = false;
			return;
		}
		if ( vecVelocity.x < 0.f && vecVelocity.y < 0.f ) // q3
			flVelocity += 180.f;

		if ( !bWasEnabled )
			flYaw = flVelocity + pCmd->viewangles.yaw < 0.f ? 180.f : 0.f;
		else
			flYaw -= flStep + pCmd->viewangles.yaw - flOldYaw;

		pCmd->forwardmove = sin( D3DXToRadian( flYaw ) ) * 450.f;
		pCmd->sidemove = cos( D3DXToRadian( flYaw ) ) * 450.f;

		bWasEnabled = true;
		flOldYaw = pCmd->viewangles.yaw;
	}

	void PX_API AutoEdgeJump( player_ptr_t pLocalPlayer, CUserCmd *pCmd, int32_t fFlagsUnpredicted )
	{
		if ( !_Settings._Miscellaneous._Movement.bEdgeJump )
			return;

		if ( fFlagsUnpredicted & FL_ONGROUND && !( pLocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
			pCmd->buttons |= IN_JUMP;
		else
			pCmd->buttons &= ~IN_JUMP;
	}

	void PX_API StaminaBug( player_ptr_t pLocalPlayer, CUserCmd *pCmd, int32_t fFlagsUnpredicted )
	{
		if ( fFlagsUnpredicted & FL_ONGROUND || !( pCmd->buttons & IN_DUCK ) )
			return;

		const auto flVelocityZ = pLocalPlayer->m_vecVelocity( ).z;
		if ( flVelocityZ >= 0.f )
			return;

		Ray_t rRay;
		const auto vecOrigin = pLocalPlayer->m_vecOrigin( );
		rRay.Init( vecOrigin, vecOrigin + Vector( 0, 0, -100.f ) );

		CTraceFilter tfFilter;
		tfFilter.pSkip = pLocalPlayer;

		CGameTrace gtRay;
		pEngineTrace->TraceRay( rRay, MASK_PLAYERSOLID, &tfFilter, &gtRay );

		if ( gtRay.fraction >= 100.f )
			return;

		static auto flDeltaPrevious = 0.f;
		const auto flDelta = gtRay.fraction * 100.f + flVelocityZ * pGlobalVariables->m_flIntervalPerTick;

		rRay.Init( vecOrigin, vecOrigin + Vector( 0, 0, -8.f ) );
		pEngineTrace->TraceRay( rRay, MASK_PLAYERSOLID, &tfFilter, &gtRay );
		if ( gtRay.fraction < 1.f )//( gtRay.fraction * 100 < 8.f )//( flDelta < flDeltaPrevious - flDelta )
			std::cout << "Unducking: ", pCmd->buttons &= ~IN_DUCK;
		std::cout << "V" << flDelta << ", \tW" << flDeltaPrevious << ", \t" << gtRay.fraction * 100 << "%\n";
		flDeltaPrevious = flDelta;
	}

	void PX_API AutoStrafe( player_ptr_t pLocalPlayer, CUserCmd *pCmd )
	{
		if ( !_Settings._Miscellaneous._Movement.bAutomaticStrafe && !_Settings._Miscellaneous._Movement.bAutonomousStrafe )
			return;

		// humanized
		// todo sideways, backwards based on velocity direction
		if ( !!_Settings._Miscellaneous._Movement.bAutomaticStrafe )
		{
			static int iLastMotionlessTick;
			static auto cl_sidespeed = pConVar->FindVar( PX_XOR( "cl_sidespeed" ) );
			if ( !( pLocalPlayer->m_fFlags( ) & FL_ONGROUND )
				 && abs( pCmd->mousedx ) > 0
				 && 100.f - _Settings._Miscellaneous._Movement.flSync < ( pGlobalVariables->m_iTickCount - iLastMotionlessTick ) * 100 / 16 + 1 )
				return ( void )( pCmd->sidemove = cl_sidespeed->GetFloat( ) * ( ( pCmd->mousedx > 0 ) - ( pCmd->mousedx < 0 ) ), pCmd->forwardmove = 0.f );

			iLastMotionlessTick = pGlobalVariables->m_iTickCount;
		}
		else
		{
			// b1g method of doing it silently based on airaccel. it's broken bad, though...
			// https://www.unknowncheats.me/forum/1394519-post1.html
		}
	}

	// https://www.unknowncheats.me/forum/counterstrike-1-5-1-6-and-mods/208650-autostrafe.html
	// some more kz stuff
}
