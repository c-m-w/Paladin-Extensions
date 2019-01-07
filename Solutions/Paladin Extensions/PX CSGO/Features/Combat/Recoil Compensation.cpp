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
	void PX_API CompensateRecoil( const player_ptr_t pLocalPlayer, CUserCmd *pCmd )
	{
		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hActiveWeapon || !hActiveWeapon.IsValid( ) )
			return;

		recoil_config_t *_Config;
		PX_GET_WEAPON_CONFIG( hActiveWeapon, _Config, _Settings._Combat._RecoilCompensation );

		if ( !_Config->bEnabled )
			return;

		static QAngle angPunchOld { };
		QAngle angPunchCompensated { pClientState->viewangles.x, pClientState->viewangles.y, pClientState->viewangles.z };
		if ( !_Config->bNoRefractoryCompensation || ( pCmd->buttons & IN_ATTACK || _Settings._Miscellaneous._Other.bAutomaticFire.Get( ) ) )
		{
			if ( !_Config->bNoRefractoryCompensation && !( pCmd->buttons & IN_ATTACK || _Settings._Miscellaneous._Other.bAutomaticFire.Get( ) ) || _Config->iStartBullet < pLocalPlayer->m_iShotsFired( ) )
			{
				QAngle angPunch = pLocalPlayer->m_aimPunchAngle( );
				auto buffer = ( angPunch - angPunchOld ) * GetRecoilScale( ) * _Config->flCompensationAmount * ( 1.f - _Config->flSmoothness );
				angDeltaCompensation += buffer;
				angPunchCompensated -= buffer;
				angPunchOld = angPunch - ( angPunch - angPunchOld ) * _Config->flSmoothness;
			}
		}
		else
		{
			// angPunchOld = angPunch
			// angPunchDeltaCompensation += pLocalPlayer->m_aimPunchAngle( );
			angDeltaCompensation = angPunchOld = { 0.f, 0.f, 0.f };
		}

		ClampAngles( angPunchCompensated );
		HumanizeAngles( angPunchCompensated, pLocalPlayer );
		pClientState->viewangles = { angPunchCompensated.pitch, angPunchCompensated.yaw, angPunchCompensated.roll };
	}
}
