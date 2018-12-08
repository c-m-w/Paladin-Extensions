/// Recoil Compensation.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Features;
using namespace Information;
using namespace Pointers;
using namespace Tools;

bool operator!=( const QAngle& lhs, const QAngle& rhs )
{
	return lhs.pitch != rhs.pitch ||
		lhs.yaw != rhs.yaw ||
		lhs.roll != rhs.roll;
}

namespace PX::Features::Combat
{
	void PX_API CompensateRecoil( const player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hActiveWeapon || !hActiveWeapon.IsValid( ) )
			return;

		recoil_config_t* _Config;
		PX_GET_WEAPON_CONFIG( hActiveWeapon, _Config, _Settings._Combat._RecoilCompensation );

		if ( !_Config->bEnabled )
			return;

		static QAngle angPunch { };
		static QAngle angPunchOld { };
		if ( pCmd->buttons & IN_ATTACK )
		{
			static bool bCompOnce = false;

			if ( hActiveWeapon->CanFire( ) )
			{
				angPunch = pLocalPlayer->m_aimPunchAngle( );
				bCompOnce = true;
			}
			else if ( bCompOnce )
			{
				QAngle angCompensation { pClientState->viewangles.x, pClientState->viewangles.y ,0.f };

				auto buffer = ( angPunch - angPunchOld ) * GetRecoilScale( ) * _Config->flCompensationAmount;
				buffer.pitch *= 1;
				buffer.yaw *= .6;
				angCompensation -= buffer;
				angPunchOld = angPunch;
				bCompOnce = false;

				ClampAngles( angCompensation );
				HumanizeAngles( angCompensation, pLocalPlayer );
				pClientState->viewangles = Vector( angCompensation.pitch, angCompensation.yaw, pClientState->viewangles.z );
			}

		}
		else
			angPunchOld = angPunch = { };
	}

	void PX_API CompensateRecoilz( const player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		// information we want persistent across ticks
		/*static QAngle angPunchCompensated { };*/
		static QAngle angPunchLastFireable { };
		static QAngle angPunchLastFireableCompensated { };
		static float flMaxYAW = 0.f;
		static float flMaxPITCH = 0.f;
		/*static auto bResetRefractoryCompensation = false;*/

		// safety and other basic checks
		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hActiveWeapon || !hActiveWeapon.IsValid( ) )
			return;

		recoil_config_t* _Config;
		PX_GET_WEAPON_CONFIG( hActiveWeapon, _Config, _Settings._Combat._RecoilCompensation );

		if ( !_Config->bEnabled )
			return;

		// aim punch is only a delta to current angle, so we default our value with our current angles
		QAngle angCompensation; angCompensation.Init( pClientState->viewangles.x, pClientState->viewangles.y );

		if ( pCmd->buttons & IN_ATTACK ) // we should only compensate recoil while the player is firing
		{
			// check if we haven't finished resetting crosshair position from the last recoil control session
			/*if ( bResetRefractoryCompensation )
				angPunchCompensated = { 0.f, 0.f, 0.f };*/

			static bool bCompen = false;

			// if we can fire, we have our recoil amount to compensate for
			if ( hActiveWeapon->m_flNextPrimaryAttack( ) - pGlobalVariables->m_flCurrentTime <= pGlobalVariables->m_flIntervalPerTick * 2 )
			{
				//bCompen = true;
				angPunchLastFireableCompensated = angPunchLastFireable;
				angPunchLastFireable = pLocalPlayer->m_aimPunchAngle( );
			}
			else if ( hActiveWeapon->HasBullets( ) )
			{
				//if ( bCompen )
				//	angCompensation -= ( angPunchLastFireable - angPunchLastFireableCompensated ) * 2.f * _Config->flCompensationAmount;
				//bCompen = false;
				
				// we ideally only want to compensate over the length of the shot. this is as smooth as recoil control can be without lagging behind
				// drawback: we're always 1 shot behind in our recoil control
				const auto flTicksPerShot = hActiveWeapon->GetCSWeaponData( )->flCycleTimeAlt / pGlobalVariables->m_flIntervalPerTick;
				const auto angCompensationAmount = ( angPunchLastFireable - angPunchLastFireableCompensated ) * GetRecoilScale( ) * _Config->flCompensationAmount / flTicksPerShot;

				if ( flMaxYAW < angCompensationAmount.yaw )
					flMaxYAW = angCompensationAmount.yaw;

				if ( flMaxPITCH < angCompensationAmount.pitch )
					flMaxPITCH = angCompensationAmount.pitch;

				//angCompensation -= angCompensationAmount;
				//angPunchCompensated += angCompensationAmount;
			}
			else
			{
				pCmd->buttons &= ~IN_ATTACK;
			}
		}
		else // if we aren't firing, we need to clear our static vars
		{
			/*if ( !!_Config->bNoRefractoryCompensation ) // we should also reset the crosshair position to it's original spot from before controlling the recoil
			{
				static auto iTickRecovery = 0;
				if ( angPunchCompensated.pitch || angPunchCompensated.yaw )
					if ( iTickRecovery < 1.f / ( pGlobalVariables->m_flIntervalPerTick * 2.f ) ) // review we should probably replace 2.f with a config val to say how quick to reset
					{
						// we've been storing all the punch compensated, so let's invert it and assign it based on the tick
						angCompensation -= angPunchCompensated * pGlobalVariables->m_flIntervalPerTick;
						iTickRecovery++;
						bResetRefractoryCompensation = true; // if they start shooting again, we want to reset the angCompensation so it doesn't just get infinitely bigger
					}
					else // we've fully reset crosshair position, clear static vars
					{
						angPunchCompensated = { };
						iTickRecovery = 0;
						bResetRefractoryCompensation = false;
					}
			}
			else
			{
				angPunchCompensated = { };
			}*/

			angPunchLastFireable = { };
			angPunchLastFireableCompensated = { };
		}

		// safety and assignment
		if ( angCompensation.pitch != pClientState->viewangles.x
			 || angCompensation.yaw != pClientState->viewangles.y )
		{
			//ClampAngles( angCompensation );
			//HumanizeAngles( angCompensation, pLocalPlayer );
			//pClientState->viewangles = Vector( angCompensation.pitch, angCompensation.yaw, pClientState->viewangles.z );
		}
	}
}
