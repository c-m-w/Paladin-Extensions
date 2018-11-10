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

		const auto pConfig = GetWeaponConfig< recoil_config_t >( hActiveWeapon, _Settings._Combat._RecoilCompensation );
		if ( !pConfig->bStandalone || pConfig->bOnlyWhileShooting.Get( ) && !( pCmd->buttons & IN_ATTACK ) )
			return;

		const auto qCurrentRecoil = pLocalPlayer->m_viewPunchAngle( ) * GetRecoilScale( ) * pConfig->flCompensationAmount;
		auto qNewRecoil = qCurrentRecoil - qOldRecoil;
		qOldRecoil = qCurrentRecoil;
		ClampAngles( qNewRecoil );

		pClientState->viewangles += Vector( qNewRecoil.pitch, qNewRecoil.yaw, qNewRecoil.roll );
	}
}
