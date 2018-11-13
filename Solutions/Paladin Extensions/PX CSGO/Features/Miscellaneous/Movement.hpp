/// Movement.hpp

#pragma once

namespace PX::Features::Miscellaneous
{
	void PX_API AutoJump( player_ptr_t pLocalPlayer, CUserCmd *pCmd );
	void PX_API AutoEdgeJump( CUserCmd *pCmd );
	void PX_API AutoStrafe( player_ptr_t pLocalPlayer, CUserCmd *pCmd );
}
