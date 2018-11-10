/// Recoil Compensation.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Features;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Features::Combat
{
	void PX_API CompensateRecoil( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		static auto qOldRecoil = QAngle( );

		if ( !pLocalPlayer->IsAlive( ) )
			return;

		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hActiveWeapon )
			return;

		recoil_config_t* _Config;
		PX_GET_WEAPON_CONFIG( hActiveWeapon, _Config, _Settings._Combat._RecoilCompensation );

		if ( !_Config->bStandalone || _Config->bOnlyWhileShooting.Get( ) && !( pCmd->buttons & IN_ATTACK ) )
			return;

		const auto qCurrentRecoil = pLocalPlayer->m_viewPunchAngle( ) * GetRecoilScale( ) * _Config->flCompensationAmount;
		auto qNewRecoil = qCurrentRecoil - qOldRecoil;
		qOldRecoil = qCurrentRecoil;
		ClampAngles( qNewRecoil );

		pClientState->viewangles += Vector( qNewRecoil.pitch, qNewRecoil.yaw, qNewRecoil.roll );
	}
}
