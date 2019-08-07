/// Movement.hpp

#pragma once

inline void Bhop( SCreateMoveContext _Context )
{
	if ( nullptr == _Context.pLocalPlayer )
		return;
	if ( !( ( Cfg::Bhop::bUseJumpButton && _Context.pCommand->buttons & IN_JUMP )
			|| ( Cfg::Bhop::bUseKeybind && GetKeyState( Cfg::Bhop::_Key ) ) ) )
		return;

	{
		const auto &movetype = _Context.pLocalPlayer->movetype( );
		if ( movetype != MOVETYPE_NOCLIP && movetype != MOVETYPE_LADDER ) // don't change anything in these states
			return; // do not unset +jump because they may want to jump off a ladder or smth.
	}

	if ( _Context.pLocalPlayer->m_fFlags( ) & FL_ONGROUND )
		return ( void )( _Context.pCommand->buttons |= IN_JUMP );

	const auto &zvel = _Context.pLocalPlayer->m_vecVelocity( ).z;
	if ( ( zvel < 0.f && Cfg::Bhop::bJumpBeforeHopping )
		 || ( zvel > 0.f && Cfg::Bhop::bJumpAfterHopping ) )
	{
		Ray_t rRay;
		const auto vecOrigin = _Context.pLocalPlayer->m_vecOrigin( );
		rRay.Init( vecOrigin, vecOrigin + Vector( 0, 0, -( abs( zvel ) * pGlobalVariables->m_flIntervalPerTick * 16 ) ) ); // 16 indicates number of ticks to check for scroll before landing

		CTraceFilter tfFilter;
		tfFilter.pSkip = _Context.pLocalPlayer;

		CGameTrace gtRay;
		pEngineTrace->TraceRay( rRay, MASK_PLAYERSOLID, &tfFilter, &gtRay );

		if ( gtRay.fraction > ( 2.f / 16.f ) && gtRay.fraction < 1.f )
			return ( void )( _Context.pCommand->buttons |= IN_JUMP );
	}
	_Context.pCommand->buttons &= ~IN_JUMP;
}
