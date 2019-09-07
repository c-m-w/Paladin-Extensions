/// Hook.hpp

#pragma once

// interface, index
inline std::vector< std::pair< void *, std::size_t > > vecBeginHook[ FUNCTION_MAX ] { };
// interface, index
inline std::vector< std::pair< void *, std::size_t > > vecEndHook[ FUNCTION_MAX ] { };

// nothing that inherits an interface should be a feature directly.
// it should inherit an abstract class first

// note: most important features
//     - psilent
//     obs proof backtrack
//     obs proof enemy + item chams
//     - bhop
//     stamina bug
//     edge jump
//     X auto pistol
//     skin changer

template < EFunctions enumHook, typename _tContext >
class IFeatureBase
{
public:
	enum
	{
		ACTIVE,
		TOGGLE_ACTIVATION,
		HOLD_TO_ACTIVATE,
		HOLD_TO_DEACTIVATE,
		SET_TO_ACTIVE,
		SET_TO_INACTIVE
	};
protected:
	using keybind_t = std::pair< key_t, decltype( ACTIVE ) >;
	using keybinds_t = std::vector< keybind_t >;
public:
	keybinds_t _Keys; // todo: this should be feature-based. not all features need a keybind.
protected:
	virtual void __cdecl Begin( _tContext* _Context ) = 0;
	virtual void __cdecl End( _tContext* _Context ) = 0;
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
					if ( _Input.GetKeyState( _Key.first ) )
						bLastActivationState = !bLastActivationState;
					if ( bLastActivationState )
						bKeyActive = true;
					break;
				}
				case HOLD_TO_ACTIVATE:
				{
					if (  _Input.GetKeyState( _Key.first ) )
						bKeyActive = true;
					else
						bKeyActive = false;
					break;
				}
				case HOLD_TO_DEACTIVATE:
				{
					if (  _Input.GetKeyState( _Key.first ) )
						bKeyActive = false;
					else
						bKeyActive = true;
					break;
				}
				case SET_TO_ACTIVE:
				{
					if (  _Input.GetKeyState( _Key.first ) )
						bKeyActive = true;
					break;
				}
				case SET_TO_INACTIVE:
				{
					if (  _Input.GetKeyState( _Key.first ) )
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
	static bool AddKeybind( const keybind_t _NewKey, keybinds_t& _Keys )
	{
		for ( auto& _Key: _Keys )
		{
			if ( _Key.first != key_t( 0ui8 )
				 && _Key.first == _NewKey.first )
				return false;
		}
		return _Keys.emplace_back( _NewKey ), true;
	}
protected:
	IFeatureBase( )
	{
		vecBeginHook[ enumHook ].emplace_back( this, 0 );
		vecEndHook[ enumHook ].emplace_back( this, 1 );
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
	virtual int BezierStuff( int time ) { return 0; }; // virtual because some features may want to change how a function works (not this function specifically because im sure it wont change)
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
	virtual bool MeetsActivationRequirements( SCreateMoveContext &_Context, CBaseEntity& _Entity ) = 0;
	virtual int GetPriorityEntityID( SCreateMoveContext &_Context, decltype( PRIORITY_MAX ) enumPriorityType = FIRST_IN_LIST ) // maybe they wanna do it based on real distance and not crosshair or smth
	{
		std::vector< int > vecPossibleEntities;
		for ( int i = 0; i < pGlobalVariables->m_iMaxClients; i++ )
			if ( MeetsActivationRequirements( _Context, *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( i ) ) ) )
				vecPossibleEntities.emplace_back( i );

		if ( vecPossibleEntities.size( ) == 0 )
			return 0;
		
		switch( enumPriorityType )
		{
			case FIRST_IN_LIST:
				return MeetsActivationRequirements( _Context,  *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( vecPossibleEntities[ 0 ] ) ) ), vecPossibleEntities[ 0 ];
			case NEAREST_TO_CROSSHAIR:
			{
				auto pLocalPlayer = GetLocalPlayer( );
				if ( nullptr == pLocalPlayer )
				return MeetsActivationRequirements( _Context,  *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( vecPossibleEntities[ 0 ] ) ) ), vecPossibleEntities[ 0 ];
				auto& _LocalPlayer = *pLocalPlayer;
				
				auto flNearest = FLT_MAX;
				// todo need VectorAngle
				throw 1;
			}
			case NEAREST_BY_DISTANCE:
			{
				auto pLocalPlayer = GetLocalPlayer( );
				if ( nullptr == pLocalPlayer )
				return MeetsActivationRequirements( _Context,  *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( vecPossibleEntities[ 0 ] ) ) ), vecPossibleEntities[ 0 ];
				auto& _LocalPlayer = *pLocalPlayer;
				
				std::pair< int, float > flNearest { 0, FLT_MAX };
				for ( auto& i: vecPossibleEntities )
				{
					auto& _Entity = *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( i ) );
					auto flDelta = _LocalPlayer.m_vecOrigin( ).DistTo( _Entity.m_vecOrigin( ) );
					if ( flNearest.second > flDelta )
						flNearest = { i, flDelta };
				}
				return MeetsActivationRequirements( _Context,  *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( flNearest.first ) ) ), flNearest.first;
			}
		}
	}
	virtual void CompensateRecoil( )
	{
		
	}
public:
	float flFieldOfView; // in degrees
	decltype( PRIORITY_MAX ) enumPriorities[ PRIORITY_MAX ] { NEAREST_TO_CROSSHAIR, NEAREST_BY_DISTANCE, FIRST_IN_LIST }; // targeting priority
	std::vector< int > vecHitboxes; // allowed hitboxes, in order of targeting preference if all in activation
};

class CAutonomousTrigger final: public AAimAssistanceBase // todo: autonomous trigger should really be merged with Aimbot and just have an auto-shoot option
{
	bool MeetsActivationRequirements( CBaseEntity& _Entity ) override
	{
		auto &_Player = reinterpret_cast< CBasePlayer& >( _Entity );
		volatile auto sz = _Player.GetPlayerInformation(  ).szName;
		if ( !_Player.IsPlayer( )
			|| !_Player.IsAlive( ) )
			return false;
		//	for ( auto &iHitbox: vecHitboxes )
		//		if ( iHitbox == _Entity.GetHitboxPosition(  ))
		//&& VecAngle( _Entity.GetHitboxPosition( each vecHitboxes ) ) // we want our crosshair position to overlap a hitbox
		return true;
	}
	
	void __cdecl Begin( SCreateMoveContext* _Context ) override
	{
		auto& pLocalPlayer = _Context->pLocalPlayer;
		auto& pCommand = _Context->pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;

		if ( pCommand->buttons & IN_ATTACK
			 || !KeybindActiveState( _Keys ) )
			return;
		
		auto &_Trace = pLocalPlayer->TraceRayFromView( _Context->pCommand ); // todo, add reocil to current view angle
		if ( !_Trace.DidHit( )
			 || _Trace.hit_entity == nullptr )
			return;
		
		if ( !MeetsActivationRequirements( *reinterpret_cast< CBaseEntity* >( _Trace.hit_entity ) ) )
			return;

		if ( pLocalPlayer->m_hActiveWeapon( )->CanFire( ) )
			pCommand->buttons |= IN_ATTACK;
	}
	void __cdecl End( SCreateMoveContext* _Context ) override
	{
		
	}
public:
	std::vector< int > vecHitboxes; // allowed hitboxes, in order of targeting preference if all in activation
};

class CAimAssistance final: public AAimAssistanceBase
{
	int iTargetHitbox = 0;
	bool MeetsActivationRequirements( SCreateMoveContext& _Context, CBaseEntity& _Entity ) override
	{
		auto &_Player = reinterpret_cast< CBasePlayer& >( _Entity );
		volatile auto sz = _Player.GetPlayerInformation(  ).szName;
		if ( !_Player.IsPlayer( )
			|| !_Player.IsAlive( ) )
			return false;

		float flSmallestDelta = FLT_MAX;
		for_enum( EHitbox, enumHitbox, EHitbox( 0 ), HITBOX_MAX ) // we can add priority hitboxes to this, but i figure the order of the enum is already pretty good.
		{
			auto flFOVDelta = ( _Context.pCommand->viewangles - CalculateAngle( _Context.pLocalPlayer, &_Player, iTargetHitbox, _Context.pCommand, nullptr ) ).Length( );
			if ( flSmallestDelta > flFOVDelta && flFOVDelta < flFOV )
				return iTargetHitbox = enumHitbox, flSmallestDelta = flFOVDelta, true;
		}
		
		return true;
	}
	void __cdecl Begin( SCreateMoveContext* _Context ) override
	{
		auto& pLocalPlayer = _Context->pLocalPlayer;
		auto& pCommand = _Context->pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return ( void )( iTargetHitbox = 0 );

		static QAngle old_viewangles { 0.f, 0.f, 0.f };
		if ( !old_viewangles.IsZero( .1f ) )
			pCommand->viewangles = old_viewangles;
		
		if ( !KeybindActiveState( _Keys ) )
			return iTargetHitbox = 0, old_viewangles.Init( 0.f, 0.f, 0.f );

		int iEntityID = 0;
		for ( int i = 0; iEntityID == 0 && i < PRIORITY_MAX; i++ )
			iEntityID = GetPriorityEntityID( *_Context, enumPriorities[ i ] );
		if ( iEntityID == 0 )
			return iTargetHitbox = 0, old_viewangles.Init( 0.f, 0.f, 0.f );
		
		auto& _Target = *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( iEntityID ) );

		if ( pCommand->buttons & IN_ATTACK )
		{
			auto& wep = pLocalPlayer->m_hActiveWeapon( );
			if ( nullptr == wep )
				return iTargetHitbox = 0, old_viewangles.Init( 0.f, 0.f, 0.f );
			
			if ( !wep->CanFire( ) )
				return iTargetHitbox = 0, pCommand->buttons &= ~IN_ATTACK, old_viewangles.Init( 0.f, 0.f, 0.f );

			auto angAtHitbox = CalculateAngle( pLocalPlayer, &_Target, iTargetHitbox, pCommand, nullptr ); // note: pcmd is not used. dunno why its a param
			ClampAngles( angAtHitbox );
			old_viewangles = pCommand->viewangles;
			pCommand->viewangles = angAtHitbox;
			
			iTargetHitbox = 0;
		}
	}
	void __cdecl End( SCreateMoveContext* _Context ) override
	{
		
	}
public:
	float flFOV = 1.f;
};

class IMiscellaneousFeatureBase: public IFeatureBase< FUNCTION_CREATE_MOVE, SCreateMoveContext >
{
	
};

class AEnvironmentFeatureBase: public IMiscellaneousFeatureBase
{

};

class CFlashUtility final: public AEnvironmentFeatureBase
{
	void __cdecl Begin( SCreateMoveContext* _Context ) override
	{
		auto& pLocalPlayer = _Context->pLocalPlayer;
		auto& pCommand = _Context->pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;

		if ( !KeybindActiveState( _Keys ) )
			return;
		
		auto &flFlashDuration = pLocalPlayer->m_flFlashDuration( );

		static auto flFullFlashTime = 0.f, flFlashTime = 0.f;
		if ( flFlashDuration <= 0.f )
			return ( void )( pLocalPlayer->m_flFlashMaxAlpha( ) = 255.f, flFullFlashTime = flFlashTime = 0.f );
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
	void __cdecl End( SCreateMoveContext* _Context ) override
	{
		
	}
public:
	float flFullFlashMaximum = 0.8f;
	float flPartialFlashMaximum = 0.25f;
};

class AMovementFeatureBase: public IMiscellaneousFeatureBase
{

};

class CTriggerAutomation final: public AMovementFeatureBase
{
	void __cdecl Begin( SCreateMoveContext* _Context ) override
	{
		auto& pLocalPlayer = _Context->pLocalPlayer;
		auto& pCommand = _Context->pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;

		if ( !KeybindActiveState( _Keys ) )
			return;

		auto& hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( nullptr == &hActiveWeapon )
			return;
		
		pCommand->buttons = hActiveWeapon->CanFire( ) ? ( pCommand->buttons | IN_ATTACK ) : ( pCommand->buttons & ~IN_ATTACK );
	}
	void __cdecl End( SCreateMoveContext* _Context ) override
	{
		
	}
};

class CJumpAutomation final: public AMovementFeatureBase
{
public:
	bool bUseJumpButton = true;
	unsigned __int8 u8JumpChance = 100ui8;
	unsigned __int8 u8MaximumExtraJumps = 7ui8;
	float flExtraJumpWindow = 0.25f;
	bool bJumpBeforeHopping = true;
	bool bJumpAfterHopping = true;
private:
	void __cdecl Begin( SCreateMoveContext* _Context ) override
	{
		auto& pLocalPlayer = _Context->pLocalPlayer;
		auto& pCommand = _Context->pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;
		
		if ( !( ( bUseJumpButton && pCommand->buttons & IN_JUMP )
				|| ( KeybindActiveState( _Keys ) ) ) )
			return;

		{
			const auto& movetype = pLocalPlayer->movetype( );
			if ( movetype == MOVETYPE_NOCLIP || movetype == MOVETYPE_LADDER ) // don't change anything in these states
				return; // do not unset +jump because they may want to jump off a ladder or smth.
		}

		if ( pLocalPlayer->m_fFlags( ) & FL_ONGROUND )
			return ( void )( pCommand->buttons = 
				( pGlobalVariables->m_iTickCount % 100 < u8JumpChance ) 
					? ( pCommand->buttons | IN_JUMP ) 
					: ( pCommand->buttons & ~IN_JUMP ) );

		static auto u8ExtraJumps = 0ui8;
		const auto& zvel = pLocalPlayer->m_vecVelocity( ).z;
		
		// it would be better to see if the ground is getting closer with a trace ray rather than checking zvelocity
		// this way we can still do a bhop before jumping if the user is bhopping up hill
		if ( ( ( zvel < 0.f && bJumpBeforeHopping ) && u8ExtraJumps < u8MaximumExtraJumps / 2 ) // we want to split the number of extra jumps to before and after the jump for extra legit
			 || ( ( zvel > 0.f && bJumpAfterHopping ) && u8ExtraJumps <= u8MaximumExtraJumps ) )
		{
			Ray_t rRay;
			const auto vecOrigin = pLocalPlayer->m_vecOrigin( );
			rRay.Init( vecOrigin, vecOrigin + Vector( 0, 0, -( abs( zvel ) * ( ( 1.f / flExtraJumpWindow ) / pGlobalVariables->m_flIntervalPerTick ) ) ) );

			CTraceFilter tfFilter;
			tfFilter.pSkip = pLocalPlayer;

			CGameTrace gtRay;
			pEngineTrace->TraceRay( rRay, MASK_PLAYERSOLID, &tfFilter, &gtRay );

			if ( zvel > 0.f && !( gtRay.fraction < 1.f ) )
				return ( void )( u8ExtraJumps = 0ui8, pCommand->buttons &= ~IN_JUMP );

			if ( gtRay.fraction < 1.f && gtRay.fraction > pGlobalVariables->m_flIntervalPerTick )
				return ( void )( u8ExtraJumps++, _Log.Log( EPrefix::INFO, ELocation::APPLICATION, "Extra Jump" ), pCommand->buttons |= IN_JUMP );
		}
		else if ( zvel >= 0.f && !bJumpAfterHopping )
			u8ExtraJumps = 0ui8;
		pCommand->buttons &= ~IN_JUMP;
	}
	void __cdecl End( SCreateMoveContext* _Context ) override
	{
		
	}
};

class CStaminaBugAutomation final: public AMovementFeatureBase
{
	void __cdecl Begin( SCreateMoveContext* _Context ) override
	{
		
	}
	void __cdecl End( SCreateMoveContext* _Context ) override
	{
		auto& pLocalPlayer = _Context->pLocalPlayer;
		auto& pCommand = _Context->pCommand;

		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;

		if ( bDisableWhenManuallyDucking && pCommand->buttons & IN_DUCK )
			return;
		
		if ( !( ( bUseDuckButton && pCommand->buttons & IN_DUCK )
				|| ( KeybindActiveState( _Keys ) ) ) )
			return;

		//Prediction::Start( pLocalPlayer, pCommand );
		//if ( _Context.pLocalPlayer->m_fFlags( ) & w )
		//	return ( void )( Prediction::End( pLocalPlayer ), pCommand->buttons &= ~IN_DUCK );
		//Prediction::Start( pLocalPlayer, pCommand );
		//if ( _Context.pLocalPlayer->m_fFlags( ) & FL_ONGROUND )
		//	return ( void )( Prediction::End( pLocalPlayer ), Prediction::End( pLocalPlayer ), pCommand->buttons |= IN_DUCK );
		//Prediction::End( pLocalPlayer );
		//Prediction::End( pLocalPlayer );
	}
public:
	bool bUseDuckButton = true;
	bool bDisableWhenManuallyDucking = true;
};
