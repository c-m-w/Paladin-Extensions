/// Movement.hpp

#pragma once

namespace PX::Features::Miscellaneous
{
	void PX_API AutoJump( player_ptr_t pLocalPlayer, CUserCmd* pCmd );
	void PX_API CircleStrafe( player_ptr_t pLocalPlayer, CUserCmd* pCmd );
	void PX_API AutoEdgeJump( player_ptr_t pLocalPlayer, CUserCmd *pCmd, int32_t fFlagsPredicted );
	void PX_API AutoStrafe( player_ptr_t pLocalPlayer, CUserCmd* pCmd );
	void PX_API StaminaBug( player_ptr_t pLocalPlayer, CUserCmd *pCmd, int32_t fFlagsUnpredicted );
}
