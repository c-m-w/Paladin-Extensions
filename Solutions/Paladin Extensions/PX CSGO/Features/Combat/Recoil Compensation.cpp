/// Recoil Compensation.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Features;
using namespace Information;
using namespace Pointers;
using namespace Tools;

bool operator!=( const QAngle &lhs, const QAngle &rhs )
{
	return lhs.pitch != rhs.pitch ||
			lhs.yaw != rhs.yaw ||
			lhs.roll != rhs.roll;
}

namespace PX::Features::Combat
{
	void PX_API CompensateRecoil( player_ptr_t pLocalPlayer, CUserCmd *pCmd )
	{
		return;

		static QAngle angPreviousBulletRecoil;
		static QAngle angStartAimAngle;
		QAngle angRecoil;
		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hActiveWeapon )
			return;

		recoil_config_t *_Config;
		PX_GET_WEAPON_CONFIG( hActiveWeapon, _Config, _Settings._Combat._RecoilCompensation );
		if ( !_Config->bEnabled || _Config->bOnlyWhileShooting.Get( ) && !( pCmd->buttons & IN_ATTACK ) )
			return;
		if ( !_Config->bOnlyWhileShooting.Get( ) && !( pCmd->buttons & IN_ATTACK ) )
			angStartAimAngle = QAngle( pClientState->viewangles.x, pClientState->viewangles.y, pClientState->viewangles.z );

		if ( !hActiveWeapon.IsValid( ) )
			return;

		if ( hActiveWeapon->CanFire( ) )
		{
			angPreviousBulletRecoil = pLocalPlayer->m_aimPunchAngle( );
			if ( !_Config->bOnlyWhileShooting.Get( ) && !( pCmd->buttons & IN_ATTACK ) )
				angRecoil = ( angStartAimAngle - QAngle( pClientState->viewangles.x, pClientState->viewangles.y, pClientState->viewangles.z ) ) / settings_t::combat_t::SMOOTHING_MIN / _Config->flStandaloneSmoothing;
			else
				// review flIdleInterval or flCycleTime, not sure
				angRecoil = angPreviousBulletRecoil / ceilf( hActiveWeapon->GetCSWeaponData( )->flCycleTime / pGlobalVariables->m_flIntervalPerTick );
		}
		ClampAngles( angRecoil );
		HumanizeAngles( angRecoil, pLocalPlayer );
		pClientState->viewangles += Vector( angRecoil.pitch, angRecoil.yaw, 0.f );
	}
}
