/// Hook.hpp

#pragma once

// function, this
inline std::vector< std::pair< void *, void * > > vecBeginHook[ FUNCTION_MAX ] { };
// function, this
inline std::vector< std::pair< void *, void * > > vecEndHook[ FUNCTION_MAX ] { };

// nothing that inherits an interface should be a feature directly.
// it should inherit an abstract class first

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
public:
	keybinds_t _Keys;
protected:
	virtual void __cdecl Begin( _tContext& _Context ) = 0;
	virtual void __cdecl End( _tContext& _Context ) = 0;
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
		vecBeginHook[ enumHook ].emplace_back( **reinterpret_cast< void *** >( this ), this );
		vecEndHook[ enumHook ].emplace_back( **reinterpret_cast< void *** >( reinterpret_cast< std::uintptr_t* >( this ) + 1 ), this );
	}
	~IFeatureBase( )
	{		
		for ( std::size_t z = 0u; z < vecBeginHook[ enumHook ].size( ); z++ )
		{			
			if ( **reinterpret_cast< void*** >( this ) == vecBeginHook[ enumHook ][ z ].first )
			{
				vecBeginHook[ enumHook ].erase( vecBeginHook[ enumHook ].begin( ) + z );
				z--;
			}
		}
		
		for ( std::size_t z = 0u; z < vecEndHook[ enumHook ].size( ); z++ )
		{
			if ( **reinterpret_cast< void *** >( reinterpret_cast< std::uintptr_t* >( this ) + 1 ) == vecEndHook[ enumHook ][ z ].first )
			{
				vecEndHook[ enumHook ].erase( vecEndHook[ enumHook ].begin( ) + z );
				z--;
			}
		}
	}
};

struct SCreateMoveContext
{
	/*CCSPlayer*/CBasePlayer* pLocalPlayer;
	CUserCmd* pCommand;
};

class ICombatFeatureBase: public IFeatureBase< FUNCTION_CREATE_MOVE, SCreateMoveContext >
{
protected:
	virtual int BezierStuff( int time ); // virtual because some features may want to change how a function works (not this function specifically because im sure it wont change)
	// here we put the context for shit that'll go between each instance of a combat feature. maybe even some functions
};

class AAimAssistanceBase: public ICombatFeatureBase
{
protected:
	enum
	{
		FIRST_IN_LIST,
		NEAREST_TO_CROSSHAIR,
		NEAREST_BY_DISTANCE,
		PRIORITY_MAX
	};
	virtual bool MeetsActivationRequirements( int iEntityID ) = 0;
	virtual int GetPriorityEntityID( decltype( PRIORITY_MAX ) enumPriorityType = FIRST_IN_LIST ) // maybe they wanna do it based on real distance and not crosshair or smth
	{
		
	}
	virtual void CompensateRecoil( )
	{
		
	}
public:
	float flFieldOfView; // in degrees
	decltype( PRIORITY_MAX ) enumPriorities[ PRIORITY_MAX ] { NEAREST_TO_CROSSHAIR, NEAREST_BY_DISTANCE, FIRST_IN_LIST }; // targeting priority
	std::vector< int > vecHitboxes; // allowed hitboxes, in order of targeting preference if all in activation
};

class CAutonomousTrigger final: public AAimAssistanceBase
{
	bool MeetsActivationRequirements( int iEntityID ) override
	{
		auto &_Entity = *reinterpret_cast< CBasePlayer* >( pEntityList->GetClientEntity( iEntityID ) );
		if ( _Entity.IsPlayer( )
		&& _Entity.IsAlive( ) )
			return false;
		//	for ( auto &iHitbox: vecHitboxes )
		//		if ( iHitbox == _Entity.GetHitboxPosition(  ))
		//&& VecAngle( _Entity.GetHitboxPosition( each vecHitboxes ) ) // we want our crosshair position to overlap a hitbox 
	}
	
	void __cdecl Begin( SCreateMoveContext& _Context ) override
	{
		auto& pLocalPlayer = _Context.pLocalPlayer;
		auto& pCommand = _Context.pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;

		if ( pCommand->buttons & IN_ATTACK
			 || !KeybindActiveState( _Keys ) )
			return;

		auto &_Trace = pLocalPlayer->TraceRayFromView( );
		if ( !_Trace.DidHit( ) )
			return;

		if ( !MeetsActivationRequirements( _Trace.GetEntityIndex( ) ))
			return;
		
		pCommand->buttons |= IN_ATTACK;
	}
	void __cdecl End( SCreateMoveContext& _Context ) override
	{
		
	}
public:
	std::vector< int > vecHitboxes; // allowed hitboxes, in order of targeting preference if all in activation
};

class CAimAssistance final: public AAimAssistanceBase
{
	bool MeetsActivationRequirements( int iEntityID ) override
	{
		auto &_Entity = *reinterpret_cast< CBasePlayer* >( pEntityList->GetClientEntity( iEntityID ) );
		return _Entity.IsPlayer( )
		&& _Entity.IsAlive( );
		//&& VecAngle( _Entity.GetHitboxPosition( each vecHitboxes ) ) < flFOVadfsfadfasdfasdfasdf
	}
	void __cdecl Begin( SCreateMoveContext& _Context ) override
	{
		auto& pLocalPlayer = _Context.pLocalPlayer;
		auto& pCommand = _Context.pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;

		if ( !KeybindActiveState( _Keys ) )
			return;

		int iEntityID = 0;
		for ( int i = 0; iEntityID == 0 && i < PRIORITY_MAX; i++ )
			iEntityID = GetPriorityEntityID( enumPriorities[ i ] );
		if ( iEntityID == 0 )
			return;
	}
	void __cdecl End( SCreateMoveContext& _Context ) override
	{
		
	}
};

class IMiscellaneousFeatureBase: public IFeatureBase< FUNCTION_CREATE_MOVE, SCreateMoveContext >
{
	
};

class AEnvironmentFeatureBase: public IMiscellaneousFeatureBase
{

};

class CFlashUtility: public AEnvironmentFeatureBase
{
	void __cdecl Begin( SCreateMoveContext& _Context ) override
	{
		auto& pLocalPlayer = _Context.pLocalPlayer;
		auto& pCommand = _Context.pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;

		if ( !KeybindActiveState( _Keys ) )
			return;
		
		auto &flFlashDuration = pLocalPlayer->m_flFlashDuration( );

		static auto flFullFlashTime = 0.f, flFlashTime = 0.f;
		if ( flFlashDuration <= 0.f )
			return ( void )( flFullFlashTime = flFlashTime = 0.f );
		if ( flFullFlashTime == 0.f || flFlashTime == 0.f )
			return;
		if ( flFlashDuration < 1.f )
			flFullFlashTime = 0.09f, flFlashTime = 0.95f;
		else if ( flFlashDuration < 2.f )
			flFullFlashTime = 0.09f, flFlashTime = 1.96f;
		else if ( flFlashDuration < 3.5f )
			flFullFlashTime = 0.46f, flFlashTime = 3.41f;
		else
			flFullFlashTime = 1.89f, flFlashTime = 4.88f;

		pLocalPlayer->m_flFlashMaxAlpha( ) = 255.f * ( flFlashDuration - ( flFlashTime - flFullFlashTime ) > 0.f ? flFullFlashMaximum : flPartialFlashMaximum );
	}
	void __cdecl End( SCreateMoveContext& _Context ) override
	{
		
	}
public:
	float flFullFlashMaximum = 1.f;
	float flPartialFlashMaximum = 1.f;
};

class AMovementFeatureBase: public IMiscellaneousFeatureBase
{

};

class CTriggerAutomation final: public AMovementFeatureBase
{
	void __cdecl Begin( SCreateMoveContext& _Context ) override
	{
		auto& pLocalPlayer = _Context.pLocalPlayer;
		auto& pCommand = _Context.pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;

		if ( !KeybindActiveState( _Keys ) )
			return;
		
		pCommand->buttons = pLocalPlayer->m_hActiveWeapon( )->CanFire( ) ? ( pCommand->buttons | IN_ATTACK ) : ( pCommand->buttons & ~IN_ATTACK );
	}
	void __cdecl End( SCreateMoveContext& _Context ) override
	{
		
	}
};

class CJumpAutomation final: public AMovementFeatureBase
{
public:
	bool bUseJumpButton = true;
	unsigned __int8 u8JumpChance = 100ui8;
	unsigned __int8 u8MaximumExtraJumps = 7ui8;
	bool bJumpBeforeHopping = true;
	bool bJumpAfterHopping = true;
private:
	void __cdecl Begin( SCreateMoveContext& _Context ) override
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
		{
			if ( pGlobalVariables->m_iTickCount % 100 < u8JumpChance )
				pCommand->buttons |= IN_JUMP;
			return;
		}
		
		static auto u8ExtraJumps = 0ui8;
		const auto& zvel = pLocalPlayer->m_vecVelocity( ).z;
		if ( ( ( zvel < 0.f && bJumpBeforeHopping ) && u8ExtraJumps < u8MaximumExtraJumps / 2 ) // we want to split the number of extra jumps to before and after the jump for extra legit
			 || ( ( zvel > 0.f && bJumpAfterHopping ) && u8ExtraJumps <= u8MaximumExtraJumps ) )
		{
			Ray_t rRay;
			const auto vecOrigin = pLocalPlayer->m_vecOrigin( );
			rRay.Init( vecOrigin, vecOrigin + Vector( 0, 0, -( abs( zvel ) * pGlobalVariables->m_flIntervalPerTick * 16 ) ) ); // 16 indicates number of ticks to check for scroll before landing

			CTraceFilter tfFilter;
			tfFilter.pSkip = pLocalPlayer;

			CGameTrace gtRay;
			pEngineTrace->TraceRay( rRay, MASK_PLAYERSOLID, &tfFilter, &gtRay );

			if ( zvel > 0.f && !( gtRay.fraction < 1.f ) )
				return ( void )( u8ExtraJumps = 0ui8, pCommand->buttons &= ~IN_JUMP );

			if ( gtRay.fraction > ( 2.f / 16.f ) )
				return ( void )( u8ExtraJumps++, pCommand->buttons |= IN_JUMP );
		}
		else if ( zvel >= 0.f && !bJumpAfterHopping )
			u8ExtraJumps = 0ui8;

		pCommand->buttons &= ~IN_JUMP;
	}
	void __cdecl End( SCreateMoveContext& _Context ) override
	{
		
	}
};

class CStaminaBugAutomation final: public AMovementFeatureBase
{
	void __cdecl Begin( SCreateMoveContext& _Context ) override
	{
		
	}
	void __cdecl End( SCreateMoveContext& _Context ) override
	{
		auto& pLocalPlayer = _Context.pLocalPlayer;
		auto& pCommand = _Context.pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;
		
		if ( !( ( bUseJumpButton && pCommand->buttons & IN_DUCK )
				|| ( KeybindActiveState( _Keys ) ) ) )
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
public:
	bool bUseJumpButton = true;
};
