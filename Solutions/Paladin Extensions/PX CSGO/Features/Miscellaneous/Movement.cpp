/// Movement.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

namespace PX::Features::Miscellaneous
{
	void AutoJump( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		if ( !_Settings._Miscellaneous._Movement.bAutoJump ||
			 PX_INPUT.GetKeyState( _Settings._Miscellaneous._Movement.kAutoJumpKey ) == false
			 || !pLocalPlayer->IsAlive( ) )
			return;

		static auto bShouldJump = false, bJumped = false;

		if( !bJumped && bShouldJump )
		{
			bShouldJump = false;
			pCmd->buttons |= IN_JUMP;
		}
		else if( pCmd->buttons & IN_JUMP )
		{
			if( pLocalPlayer->m_fFlags(  ) & FL_ONGROUND )
			{
				bShouldJump = true;
				bJumped = true;
			}
			else
			{
				pCmd->buttons &= ~IN_JUMP;
				bJumped = false;
			}
		}
		else
		{
			bShouldJump = false;
			bJumped = false;
		}
	}
}
