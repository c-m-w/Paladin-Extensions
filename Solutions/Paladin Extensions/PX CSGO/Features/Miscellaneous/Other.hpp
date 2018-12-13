/// Other.hpp

#pragma once

namespace PX::Features::Miscellaneous
{
	bool PX_API CopyHitsoundFiles( );
	void PX_API RemoveHitsoundFiles( );
	void PX_API Hitsound( IGameEvent* pEvent );

	void PX_API NoTeamDamage( player_ptr_t pLocalPlayer, CUserCmd* pCmd );
	void PX_API LastMomentDefuse( player_ptr_t pLocalPlayer, CUserCmd* pCmd );

	// also fakelag. max lag is 15 choke, 1 send
	void PX_API ChokeStream( );

	void PX_API AutomaticFire( player_ptr_t pLocalPlayer, CUserCmd *pCmd );

	void PX_API StaminaBug( player_ptr_t pLocalPlayer, int32_t fFlagsUnpredicted, CUserCmd *pCmd );
}
