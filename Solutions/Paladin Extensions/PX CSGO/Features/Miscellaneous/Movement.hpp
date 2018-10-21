/// Movement.hpp

#pragma once

namespace PX::Features::Miscellaneous
{
	void AutoJump( player_ptr_t pLocalPlayer, CUserCmd* pCmd );
	void EdgeJump( CUserCmd* pCmd );
	void AutoStrafe( CUserCmd* pCmd );
}
