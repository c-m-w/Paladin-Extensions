/// Movement.hpp

#pragma once

namespace PX::Features::Miscellaneous
{
	void PX_API AutoJump( player_ptr_t pLocalPlayer, CUserCmd* pCmd );
	void PX_API EdgeJump( CUserCmd* pCmd );
	void PX_API AutoStrafe( CUserCmd* pCmd );
}
