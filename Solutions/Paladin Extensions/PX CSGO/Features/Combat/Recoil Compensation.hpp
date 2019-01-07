/// Recoil Compensation.hpp

#pragma once

namespace PX::Features::Combat
{
	PX_SDK QAngle angDeltaCompensation;
	void PX_API CompensateRecoil( player_ptr_t pLocalPlayer, CUserCmd *pCmd );
}
