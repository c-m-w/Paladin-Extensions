/// Hook.hpp

#pragma once

inline std::vector< std::function< void( void * ) > > vecBeginHook[ FUNCTION_MAX ] { };
inline std::vector< std::function< void( void * ) > > vecEndHook[ FUNCTION_MAX ] { };

template < EFunctions enumHook, typename _tContext >
class IFeatureBase
{
protected:
	enum
	{
		ACTIVE,
		TOGGLE_ACTIVATION,
		HOLD_TO_ACTIVATE,
		HOLD_TO_DEACTIVATE,
		SET_TO_ACTIVE,
		SET_TO_INACTIVE
	};
	using keybind_t = std::pair< key_t, decltype( ACTIVE ) >;
	using keybinds_t = std::vector< keybind_t >;
	virtual void Begin( _tContext& _Context ) = 0;
	virtual void End( _tContext& _Context ) = 0;
public:
	static bool KeybindActiveState( const keybinds_t& _Keys )
	{
		bool bKeyActive = false;
		for ( auto& _Key: _Keys )
		{
			switch ( _Key.second )
			{
				case ACTIVE:
				{
					bKeyActive = true;
					break;
				}
				case TOGGLE_ACTIVATION:
				{
					static bool bLastActivationState = false;
					if ( GetKeyState( _Key.first ) )
						bLastActivationState = !bLastActivationState;
					if ( bLastActivationState )
						bKeyActive = true;
					break;
				}
				case HOLD_TO_ACTIVATE:
				{
					if ( GetKeyState( _Key.first ) )
						bKeyActive = true;
					else
						bKeyActive = false;
					break;
				}
				case HOLD_TO_DEACTIVATE:
				{
					if ( GetKeyState( _Key.first ) )
						bKeyActive = false;
					else
						bKeyActive = true;
					break;
				}
				case SET_TO_ACTIVE:
				{
					if ( GetKeyState( _Key.first ) )
						bKeyActive = true;
					break;
				}
				case SET_TO_INACTIVE:
				{
					if ( GetKeyState( _Key.first ) )
						bKeyActive = false;
					break;
				}
				default:
				{
				}
			}
		}
		return bKeyActive;
	}
	static bool AddKeybind( const keybind_t _NewKey, const keybinds_t& _Keys )
	{
		for ( auto& _Key : _Keys )
		{
			if ( _Key.first == _NewKey.first )
				return false;
		}
		return _Keys.emplace_back( _NewKey ), true;
	}
protected:
	IFeatureBase( )
	{		
		if ( nullptr != Begin )
			vecBeginHook[ enumHook ].emplace_back( Begin );
		if ( nullptr != End )
			vecBeginHook[ enumHook ].emplace_back( End );
	}
	~IFeatureBase( )
	{
		int i;
		if ( i = 0, Begin )
			for ( auto &fnHook: vecBeginHook[ enumHook ] )
				if ( Begin == fnHook )
					vecBeginHook[ enumHook ].erase( vecBeginHook[ enumHook ].begin( ) + i );
				else
					i++;
		if ( i = 0, End )
			for ( auto& fnHook : vecEndHook[ enumHook ] )
				if ( End == fnHook )
					vecEndHook[ enumHook ].erase( vecEndHook[ enumHook ].begin( ) + i );
				else
					i++;
	}
};

struct SCreateMoveContext
{
	/*CCSPlayer*/CBasePlayer* pLocalPlayer;
	CUserCmd* pCommand;
};

class ACombatFeatureBase: public IFeatureBase< FUNCTION_CREATE_MOVE, SCreateMoveContext >
{
public:
	keybinds_t _Keys;
protected:
	virtual int BezierStuff( int time ); // virtual because some features may want to change how a function works (not this function specifically because im sure it wont change)
	// here we put the context for shit that'll go between each instance of a combat feature. maybe even some functions
};

class AAimAssistanceBase: public ACombatFeatureBase
{
protected:
	virtual int GetNearestEntityID( ); // maybe they wanna do it based on real distance and not crosshair or smth
};

class CAimAssistance final: public AAimAssistanceBase
{

};

class AMovementFeatureBase: public IFeatureBase< FUNCTION_CREATE_MOVE, SCreateMoveContext >
{
public:
	keybinds_t _Keys;
};

class CJumpAutomation final: public AMovementFeatureBase
{
public:
	bool bUseJumpButton = true;
	unsigned __int8 u8MaximumExtraJumps = 7ui8;
	bool bJumpBeforeHopping = true;
	bool bJumpAfterHopping = true;
private:
	void Begin( SCreateMoveContext& _Context ) override
	{
		auto& pLocalPlayer = _Context.pLocalPlayer;
		auto& pCommand = _Context.pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;
		
		if ( !( ( bUseJumpButton && pCommand->buttons & IN_JUMP )
				|| ( KeybindActiveState( _Keys ) ) ) )
			return;

		{
			const auto& movetype = pLocalPlayer->movetype( );
			if ( movetype != MOVETYPE_NOCLIP && movetype != MOVETYPE_LADDER ) // don't change anything in these states
				return; // do not unset +jump because they may want to jump off a ladder or smth.
		}

		if ( pLocalPlayer->m_fFlags( ) & FL_ONGROUND )
			return ( void )( pCommand->buttons |= IN_JUMP );

		static unsigned __int8 uExtraJumps = 0ui8;
		const auto& zvel = pLocalPlayer->m_vecVelocity( ).z;
		if ( ( ( zvel < 0.f && bJumpBeforeHopping ) && uExtraJumps < u8MaximumExtraJumps / 2 ) // we want to split the number of extra jumps to before and after the jump for extra legit
			 || ( ( zvel > 0.f && bJumpAfterHopping ) && uExtraJumps < u8MaximumExtraJumps ) )
		{
			Ray_t rRay;
			const auto vecOrigin = pLocalPlayer->m_vecOrigin( );
			rRay.Init( vecOrigin, vecOrigin + Vector( 0, 0, -( abs( zvel ) * pGlobalVariables->m_flIntervalPerTick * 16 ) ) ); // 16 indicates number of ticks to check for scroll before landing

			CTraceFilter tfFilter;
			tfFilter.pSkip = pLocalPlayer;

			CGameTrace gtRay;
			pEngineTrace->TraceRay( rRay, MASK_PLAYERSOLID, &tfFilter, &gtRay );

			if ( gtRay.fraction > ( 2.f / 16.f ) && gtRay.fraction < 1.f )
				return ( void )( uExtraJumps++, pCommand->buttons |= IN_JUMP );
		}
		pCommand->buttons &= ~IN_JUMP;
	}
};

class CStaminaBugAutomation final: public AMovementFeatureBase
{
private:
	void End( SCreateMoveContext& _Context ) override
	{
		auto& pLocalPlayer = _Context.pLocalPlayer;
		auto& pCommand = _Context.pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;

		if ( !KeybindActiveState( _Keys ) )
			return;

		//Prediction::Start( pLocalPlayer, pCommand );
		//if ( _Context.pLocalPlayer->m_fFlags( ) & FL_ONGROUND )
		//	return ( void )( Prediction::End( pLocalPlayer ), pCommand->buttons &= ~IN_DUCK );
		//Prediction::Start( pLocalPlayer, pCommand );
		//if ( _Context.pLocalPlayer->m_fFlags( ) & FL_ONGROUND )
		//	return ( void )( Prediction::End( pLocalPlayer ), Prediction::End( pLocalPlayer ), pCommand->buttons |= IN_DUCK );
		//Prediction::End( pLocalPlayer );
		//Prediction::End( pLocalPlayer );
	}
};
