/// Movement.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

namespace PX::Features::Miscellaneous
{
	void PX_API AutoJump( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		if ( !_Settings._Miscellaneous._Movement.bAutoJump
			 || !pLocalPlayer->IsAlive( ) )
			return;

		if ( pCmd->buttons & IN_JUMP )
			if ( !( pLocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
				if ( !( pGlobalVariables->m_iTickCount % ( int( _Settings._Miscellaneous._Movement.flMissChance / pGlobalVariables->m_flIntervalPerTick ) + 1 ) ) )
					pCmd->buttons &= ~IN_JUMP;
	}
}
