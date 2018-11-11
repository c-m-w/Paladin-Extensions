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
	void PX_API CompensateRecoil( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		static QAngle qProgressedRecoil { }, qOldRecoil { }, qVelocity { };
		static auto flLastTick = pGlobalVariables->m_flCurrentTime,
					flLastShotTime = flLastTick,
					flWaitTime = 0.f,
					flLastRefreshTime = pGlobalVariables->m_flCurrentTime;

		if ( !pLocalPlayer->IsAlive( ) )
			return;

		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hActiveWeapon )
			return;

		recoil_config_t* _Config;
		PX_GET_WEAPON_CONFIG( hActiveWeapon, _Config, _Settings._Combat._RecoilCompensation );

		if ( !_Config->bEnabled || !_Config->bStandalone || _Config->bOnlyWhileShooting.Get( ) && !( pCmd->buttons & IN_ATTACK ) )
		{
			qProgressedRecoil = qVelocity = QAngle( );
			return;
		}

		const auto qCurrentRecoil = pLocalPlayer->m_aimPunchAngle( ) * GetRecoilScale( ) * _Config->flCompensationAmount;
		if ( qCurrentRecoil.pitch == 0.f && qCurrentRecoil.yaw == 0.f && qCurrentRecoil.roll == 0.f )
			return;
		const auto flNextShotTime = hActiveWeapon->GetNextShotTime( );

		if( flNextShotTime != 0.f && ( flWaitTime > pGlobalVariables->m_flCurrentTime - flLastRefreshTime 
			|| flNextShotTime > flLastShotTime 
			|| flNextShotTime < 0.f 
			|| qCurrentRecoil != qOldRecoil ) )
		{
			qVelocity = ( qCurrentRecoil - qProgressedRecoil ) / fabsf( flNextShotTime );
			qOldRecoil = qCurrentRecoil;
			flLastShotTime = flWaitTime = flNextShotTime;
			flLastRefreshTime = pGlobalVariables->m_flCurrentTime;
		}

		auto qStep = qVelocity * ( pGlobalVariables->m_flCurrentTime - flLastTick );
		qProgressedRecoil += qStep;
		ClampAngles( qStep );
		pClientState->viewangles -= Vector( qStep.pitch, qStep.yaw, pClientState->viewangles.z );
		flLastTick = pGlobalVariables->m_flCurrentTime;
	}
}
