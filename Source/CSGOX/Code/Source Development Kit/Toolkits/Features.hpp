/// Hook.hpp

#pragma once

// interface, index
inline std::vector< std::pair< void *, std::size_t > > vecBeginHook[ FUNCTION_MAX ] { };
// interface, index
inline std::vector< std::pair< void *, std::size_t > > vecEndHook[ FUNCTION_MAX ] { };

// nothing that inherits an interface should be a feature directly.
// it should inherit an abstract class first

// todo note: most important features
//     + psilent
//     + stop trigger (sets sens to 0 on player kill with trigger for 3/4 second after kill)
//     _ obs proof backtrack
//     - obs proof enemy + item chams/glow
//     + bhop
//     * stamina bug
//     * edge jump
//     X auto pistol
//     _ skin changer

/* this code is based on my following pseudocode concept for a feature system. this code is not my desired implementation of the feature system, but this is just beta code :p

context< hook_fn >
struct context< fn_create_move >
    pointer local_player
    pointer cmd_stream

abstract class feature_base< fn_none >
    protected alias bind_t
    protected is_active( activation_keys )
    protected virtual thread_proc( ) = nullptr
    constructor( )
        create.new_thread( thread_proc )

abstract class feature_base< hook_fn >
    protected alias context< hook_fn > as context
    protected alias bind_t
    protected alias color_t
    protected is_active( activation_keys )
        for each key in activation_keys
            switch key.activation
                case ALWAYS
                    return true
                case ...
    protected virtual pre_hook_fn( context ) = nullptr
    protected virtual post_hook_fn( context ) = nullptr

interface config_base
    private byte[ ] convert_to_bytes< type >( type object )
        return ( &object )[ sizeof object ]
    private byte[ ] convert_to_bytes< color_t >( color_t colors )
        if colors.sequences == 0
            return "{ }"_b
        if colors.sequences == 1
            return ( &colors[ 0 ].rgba )[ 4 bytes ]
        return { for each { ( &colors[ each ].rgba )[ 4 bytes ], ( &colors[ each ].length ) } }
    private byte[ ] convert_to_bytes< bind_t >( bind_t binds )
        for each bind in binds
            if bind.type == active
                return "{ true }"
            else
                byte return[ for each counter ] = bind.type
                byte return[ for each max + for each counter ] = bind.vkey
    public dump( )
        dump = begin_feature_marker
        dump += colors_marker + convert_to_bytes( get_colors( ) )
        dump += binds_marker + convert_to_bytes( get_binds( ) )
        dump += members_marker + members_to_save_as_bytes( )
    protected pure virtual color_t[ ] get_colors( )
    protected pure virtual bind_t[ ] get_binds( )
    protected pure virtual byte[ ] members_to_save_as_bytes( )

// first member of config must be an array of two bools which describes if activation_keys and color_stream exists
// member after config_struct of config class must always be activation_keys if the feature can be activated by a key
// member after activation_keys (or color_struct if activation_keys isn’t a member) of config class must always be color_stream if the feature uses colors
class config_data< config >
    data data
    process_keys( activation_keys )
        data << &activation_keys // shrinks data into a less large format
    process_colors( color_stream )
        data << &color_stream // shrinks data into a less large format
    constructor( cfg )
        diffptr offset = 0
        if cfg.config_struct[ 0 ]
            process_keys( cfg.activation_keys )
            offset += sizeof bool + sizeof bind_t
        if cfg.config_struct[ 1 ]
            process_keys( cfg.color_stream )
            offset += sizeof bool + sizeof color_t
        data << &cfg + offset

interface event_base
    public struct config
        vector< pair< function pointer ( returns bool ), event_call_stack_trigger_signature > > event_should_trigger
        vector< function pointer > ( void )( event_callback )
    event( call_stack, event_should_trigger, event_callback )
        if event_should_trigger.event_call_stack_trigger_signature.signature_matches( call_stack )
            event_callback( )

class bhop inherits feature_base< fn_create_move >
    public struct config cfg
        const bool[ 2 ] config_struct = true, false
        bind_t activation_keys
        bool activate_with_jump_buttons
        bool add_early_jumps
        bool add_late_jumps
        percent miss
    can_jump( player )
    will_be_on_ground( ticks )
    pre_hook_fn( context ) override
        if will_be_on_ground( 0 )
            static tick last_tick_on_ground = globalvars.tick_count
        if not is_active( cfg.activation_keys ) or not context.cmd_stream.buttons & IN_JUMP
            return
        if can_jump( context.local_player ) and random( 100% ) > cfg.miss
            return void context.cmd_stream.buttons |= IN_JUMP
        if add_early_jumps and will_be_on_ground( ticks_per_second / 4 ) and globalvars.tick_count % 2
            return void context.cmd_stream.buttons |= IN_JUMP
        else if add_early_jumps
            return void context.cmd_stream.buttons &= ~IN_JUMP
        if add_late_jumps and last_ground_tick < ticks_per_second / 4 and globalvars.tick_count % 2
            return void context.cmd_stream.buttons |= IN_JUMP
        else if add_late_jumps
            return void context.cmd_stream.buttons &= ~IN_JUMP
bhop friend stamina_bug

class stamina_bug inherits feature_base< fn_create_move >
    public struct config cfg
        const bool[ 2 ] config_struct = true, false
        bind_t activation_keys
        bool only_if_already_crouched
    pre_hook_fn( context ) override
        if will_be_on_ground( 0 )
            static tick last_tick_on_ground = globalvars.tick_count
        if only_if_already_crouched and not context.cmd_stream.buttons & IN_DUCK
            return
        if not is_active( cfg.activation_keys )
            return
        if will_be_on_ground( 1 )
            return void context.cmd_stream.buttons &= ~IN_DUCK
        if not only_if_already_crouched and not context.cmd_stream.buttons & IN_DUCK and will_be_on_ground( 2 )
            return void context.cmd_stream.buttons |= IN_DUCK
*/

// done
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

struct SDrawContext
{
	
};

struct STargetEntityFilter
{
	
	enum // filter
	{
		unfiltered = -1,
		player,
		creature, // chicken
		weapon,
		projectile
	} entity_type = unfiltered;
	int get_entity_type( CBaseEntity& entity )
	{
		if ( entity.IsPlayer( ) )
			return player;
		if ( false )
			return creature;
		if ( entity.IsWeapon( ) )
			return weapon;
		if ( false )
			return projectile;
		return unfiltered;
	}
	
	enum // player filter
	{
		teamless = -1,
		terrorists,
		counter_terrorists,
		other
	} team;
	int get_team( CBasePlayer& entity )
	{
		if ( get_entity_type( entity ) != player )
			return teamless;
		switch ( entity.m_iTeamNum( ) )
		{
			case 2:
				return terrorists;
			case 3:
				return counter_terrorists;
			default:
				return other;
		}
	}

	enum // weapon filter
	{
		groupless = -1,
		knife,
		pistol,
		smg,
		shotgun,
		lmg,
		rifle,
		sniper,
		autosniper,
		gear
	} weapon_group = groupless;
	int get_weapon_group( CBasePlayer& entity )
	{
		if ( get_entity_type( entity ) != weapon )
			return groupless;
		/* todo */
	}
	
	enum // guns + players
	{
		uncounted = -1,
		minority, // < 50
		majority // > 50
	} ammo = uncounted, armor = uncounted;
	int get_ammo( CBaseEntity& entity )
	{
		switch ( get_entity_type( entity ) )
		{
			case player:
			{
				auto& wep = reinterpret_cast< CBasePlayer* >( &entity )->m_hActiveWeapon( );
				if ( wep == nullptr )
					return uncounted;
				return wep->m_iClip1( );
			}
			case weapon:
			{
				//todo add imaxclip1
				//return reinterpret_cast< CBaseCombatWeapon* >( &entity )->m_iMaxClip1( );
			}
			default:
				return uncounted;
		}
	}
	int get_armor( CBasePlayer& entity )
	{
		if ( get_entity_type( entity ) != player )
			return uncounted;
		return entity.m_ArmorValue( );
	}

	enum // players
	{
		unknown = -1,
		no_armor,
		half_armor,
		head_plus_armor
	} armor_type;
	int get_armor_type( CBasePlayer& entity )
	{
		if ( get_entity_type( entity ) != player )
			return unknown;
		//??? todo
	}
	
	enum // players
	{
		every = -1,
		away, // we're at least 90 degrees away
		toward // we're at most 90 degrees away
	} direction = every;
	int get_direction( CBasePlayer& local, CBasePlayer& entity )
	{
		if ( get_entity_type( entity ) != player )
			return every;
		return 90.f < ( CalculateAngle( local.GetViewPosition( ), entity.GetHitboxPosition( HITBOX_HEAD ) ) - entity.m_angEyeAngles( ) ).Length( )
			? away
			: toward;
	}
	
	enum // players
	{
		indifferent = -1,
		invulnerable, // weapon out
		vulnerable, // reloading, weaponless, flashed
		unaware // fully flashed
	} vulnerability = indifferent;
	int get_vulnerability( CBasePlayer& entity )
	{
		if ( get_entity_type( entity ) != player )
			return indifferent;
		if ( entity.m_flFlashDuration( ) )
			return unaware; // todo something smart like CFlashUtility
		const auto &hActiveWeapon = entity.m_hActiveWeapon( );
		if ( hActiveWeapon )
		{
			if ( !hActiveWeapon->HasBullets( ) )
				return vulnerable;
			const auto iWeaponType = hActiveWeapon->GetCSWeaponData( )->WeaponType;
			if ( (iWeaponType == ITEM_WEAPON_SSG08
				 || iWeaponType == ITEM_WEAPON_AWP ) && !hActiveWeapon->CanFire( ))
				return vulnerable;
			if ( iWeaponType == ITEM_NONE // no weapon (tpose)
					|| iWeaponType > ITEM_WEAPON_SSG08 // useless weapon/nade
					&& iWeaponType < ITEM_WEAPON_M4A1S // useless weapon/nade
					|| iWeaponType > ITEM_WEAPON_TACTICALAWARENESSGRENADE ) // knife/glove/other
				return vulnerable;
		}
		return invulnerable;
	}
	
	enum // players
	{
		all = -1,
		soundless, // no sound
		sound, // any sound
		loud // shooting
	} noise = all;
	int get_noise( CBasePlayer& entity )
	{
		// todo no idea
	}

	enum // players
	{
		any = -1,
		full, // standing still
		quick_regain, // moving
		inaccurate // in air
	} accuracy = any;
	int get_accuracy( CBasePlayer& entity )
	{
		if ( get_entity_type( entity ) != player )
			return any;
		
		if ( !( entity.m_fFlags( ) & FL_ONGROUND ) )
			return inaccurate;

		if ( entity.m_vecVelocity( ).Length( ) > 40.f )
			return quick_regain;

		return full;
	}
};

// todo https://www.unknowncheats.me/forum/1960243-post4.html
class CChams final: public IFeatureBase< FUNCTION_DRAW_PRIMITIVE, SDrawContext >
{
	void __cdecl Begin( SDrawContext* _Context ) override
	{
		
	}
	void __cdecl End( SDrawContext* _Context ) override
	{ }
};

// todo https://www.unknowncheats.me/forum/2197432-post19.html
class CGlow final: public IFeatureBase< FUNCTION_DRAW_PRIMITIVE, SDrawContext >
{
	void __cdecl Begin( SDrawContext* _Context ) override
	{
		
	}
	void __cdecl End( SDrawContext* _Context ) override
	{ }
};

struct SPresentContext
{
	
};

class CDrawTextures final: public IFeatureBase< FUNCTION_PRESENT, SPresentContext >
{
	void __cdecl Begin( SPresentContext* _Context ) override
	{
		
	}
	void __cdecl End( SPresentContext* _Context ) override
	{ }
};

// done
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
			if ( MeetsActivationRequirements( _Context, *(CBaseEntity*)pEntityList->GetClientEntity( i ) ) )
				vecPossibleEntities.emplace_back( i );

		if ( vecPossibleEntities.size( ) == 0 )
			return 0;
		
		switch( enumPriorityType )
		{
			case FIRST_IN_LIST:
				return MeetsActivationRequirements( _Context,  *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( vecPossibleEntities[ 0 ] ) ) ), vecPossibleEntities[ 0 ];
			case NEAREST_TO_CROSSHAIR:
			{
				auto& _LocalPlayer = *_Context.pLocalPlayer;

				struct
				{ int first; EHitbox second; float third; }
				flFavoriteEntity { -1, HITBOX_MAX, FLT_MAX };
				for ( auto& i: vecPossibleEntities )
				{
					auto& _Entity = *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( i ) );
					for_enum( EHitbox, enumHitbox, EHitbox( 0 ), HITBOX_MAX )
					{
						auto fl=CalculateCrosshairDistance( _Context.pLocalPlayer, &_Entity, enumHitbox, _Context.pCommand, false );
						if ( fl < flFieldOfView && flFavoriteEntity.third > fl )
							flFavoriteEntity = { i, enumHitbox, fl };
					}
				}
				return MeetsActivationRequirements( _Context,  *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( flFavoriteEntity.first ) ) ), flFavoriteEntity.first;
			}
			case NEAREST_BY_DISTANCE:
			{
				auto& _LocalPlayer = *_Context.pLocalPlayer;
				
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
	decltype( PRIORITY_MAX ) enumPriorities[ PRIORITY_MAX ] { NEAREST_TO_CROSSHAIR, NEAREST_BY_DISTANCE, FIRST_IN_LIST }; //{ NEAREST_TO_CROSSHAIR, NEAREST_BY_DISTANCE, FIRST_IN_LIST }; // targeting priority
	std::vector< int > vecHitboxes; // allowed hitboxes, in order of targeting preference if all in activation
};

class CAutonomousTrigger final: public AAimAssistanceBase // todo: autonomous trigger should really be merged with Aimbot and just have an auto-shoot option
// todo hitboxes activation
{
	bool MeetsActivationRequirements( SCreateMoveContext& _Context, CBaseEntity& _Entity ) override
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

		const auto old_angles = _Context->pCommand->viewangles;
		_Context->pCommand->viewangles -= pLocalPlayer->m_aimPunchAngle( ) * GetRecoilScale( );
		auto &_Trace = pLocalPlayer->TraceRayFromView( _Context->pCommand );
		_Context->pCommand->viewangles = old_angles;
		
		if ( !_Trace.DidHit( )
			 || _Trace.hit_entity == nullptr )
			return;
		
		if ( !MeetsActivationRequirements( *_Context, *reinterpret_cast< CBaseEntity* >( _Trace.hit_entity ) ) )
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
		if ( nullptr == &_Entity )
			return false;
		if ( _Context.pLocalPlayer == &_Player )
			return false;
		if ( !_Player.IsPlayer( )
			|| !_Player.IsAlive( ) )
			return false;

		/*float flSmallestDelta = FLT_MAX;*/
		for_enum( EHitbox, enumHitbox, EHitbox( 0 ), HITBOX_MAX ) // we can add priority hitboxes to this, but i figure the order of the enum is already pretty good.
		{
			auto flFOVDelta = CalculateCrosshairDistance( _Context.pLocalPlayer, &_Player, enumHitbox, _Context.pCommand, nullptr );
			if ( /*flSmallestDelta > flFOVDelta &&*/ flFOVDelta < flFieldOfView )
				return iTargetHitbox = enumHitbox, /*flSmallestDelta = flFOVDelta,*/ true; // if we want hitbox priorities, DO NOT RETURN HERE
		}
		
		return iTargetHitbox = -1, false;
	}
	void __cdecl Begin( SCreateMoveContext* _Context ) override // psilent
	{
		// shorten reference to context variables
		auto& pLocalPlayer = _Context->pLocalPlayer;
		auto& pCommand = _Context->pCommand;

		// check setup
		if ( nullptr == pLocalPlayer || nullptr == pCommand )
			return;

		// if we already moved angles last tick, we need to move back
		static QAngle old_viewangles { 0.f, 0.f, 0.f };
		if ( !old_viewangles.IsZero( .1f ) )
			return pCommand->viewangles = old_viewangles, old_viewangles.Init( 0.f, 0.f, 0.f );

		// check for aimbot key
		if ( !KeybindActiveState( _Keys ) )
			return;

		{
			// validate weapon can fire this tick so we aren't just randomly snapping
			auto& wep = pLocalPlayer->m_hActiveWeapon( );
			if ( nullptr == wep )
				return;
			// todo remove check for IN_ATTACK and just assign it if they want it to automatically shoot like some psilent trigger
			if ( !wep->CanFire( ) || !( pCommand->buttons & IN_ATTACK ) ) // todo revolver check
				return;
		}

		// iterate through entities, find highest priority and their target hitbox.
		int iEntityID = 0;
		for ( int i = 0; iEntityID == 0 && i < PRIORITY_MAX; i++ )
			iEntityID = GetPriorityEntityID( *_Context, enumPriorities[ i ] );
		if ( iEntityID == 0 )
			return;
		
		auto& _Target = *reinterpret_cast< CBasePlayer * >( pEntityList->GetClientEntity( iEntityID ) );

		// compensate for recoil because calculate angle doesn't consider it
		// this is intentional in case we want to change recoil control based on user settings
		static int iShouldShoot;
		static QAngle angAtHitbox;
		if ( iShouldShoot == 0 )
		{
			angAtHitbox = CalculateAngle( pLocalPlayer, &_Target, iTargetHitbox, pCommand, nullptr ) - pLocalPlayer->m_aimPunchAngle( ) * GetRecoilScale( ); // note: pcmd is not used. dunno why its a param
			ClampAngles( angAtHitbox ); // safety
			iShouldShoot++;
		}
		else
		{
			old_viewangles = pCommand->viewangles; // save for restore
			pCommand->viewangles = angAtHitbox;
			if ( iShouldShoot == 2 )
				iShouldShoot = 0;
			else
				iShouldShoot++;
		}
	}
	void __cdecl End( SCreateMoveContext* _Context ) override
	{
		
	}
public:
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
	float flFullFlashMaximum;
	float flPartialFlashMaximum;
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
	bool bUseJumpButton;
	unsigned __int8 u8JumpChance;
	unsigned __int8 u8MaximumExtraJumps;
	float flExtraJumpWindow;
	bool bJumpBeforeHopping;
	bool bJumpAfterHopping;
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
	bool bUseDuckButton;
	bool bDisableWhenManuallyDucking;
};

struct SFrameStageNotifyContext
{
	/*CCSPlayer*/CBasePlayer* pLocalPlayer;
	CUserCmd* pCommand;
	ClientFrameStage_t _FrameStage;
};

// todo https://www.unknowncheats.me/forum/counterstrike-global-offensive/225472-instant-weapon-paintkit-update-fullupdate.html
// todo force update
class CInventoryManager final: public IFeatureBase< FUNCTION_FRAME_STAGE_NOTIFY, SFrameStageNotifyContext >
{
	int kills_to_save = 0;
	
	void __cdecl Begin( SFrameStageNotifyContext* _Context ) override
	{
		if ( !bEquipped )
			return;

		if ( _Context->_FrameStage != FRAME_NET_UPDATE_POSTDATAUPDATE_START )
			return;
		
		// todo
		//kills_to_save = _Context->pLocalPlayer->m_iKills( );
		
		if ( !_Context->pLocalPlayer->IsAlive( ) )
			return;
			
		auto weps = _Context->pLocalPlayer->m_hMyWeapons( );
		if ( nullptr == weps )
			return;

		for ( int i = 0; auto &wep = weps[ i ]; i++ )
		{
			if ( wep->m_nFallbackPaintKit( ) == iSkin )
				continue;
				
			if ( enumWeapon != wep->m_Item( )->m_iItemDefinitionIndex( ) )
				switch ( wep->m_Item( )->m_iItemDefinitionIndex( ) )
				{
					case ITEM_WEAPON_KNIFE_BAYONET:
					case ITEM_WEAPON_KNIFE_FLIP:
					case ITEM_WEAPON_KNIFE_GUT:
					case ITEM_WEAPON_KNIFE_KARAMBIT:
					case ITEM_WEAPON_KNIFE_M9_BAYONET:
					case ITEM_WEAPON_KNIFE_TACTICAL:
					case ITEM_WEAPON_KNIFE_FALCHION:
					case ITEM_WEAPON_KNIFE_SURVIVAL_BOWIE:
					case ITEM_WEAPON_KNIFE_BUTTERFLY:
					case ITEM_WEAPON_KNIFE_SHADOW_DAGGERS:
					case ITEM_WEAPON_KNIFE_URSUS:
					case ITEM_WEAPON_KNIFE_NAVAJA:
					case ITEM_WEAPON_KNIFE_STILLETTO:
					case ITEM_WEAPON_KNIFE_TALON:
						wep->m_Item(  )->m_iItemDefinitionIndex(  ) = enumWeapon;
					default:
						continue;
				}

			wep->m_OriginalOwnerXuidHigh( ) = _Context->pLocalPlayer->GetPlayerInformation( ).xuid_high;
			wep->m_OriginalOwnerXuidLow( ) = _Context->pLocalPlayer->GetPlayerInformation( ).xuid_low;
				
			wep->m_nFallbackPaintKit( ) = iSkin;
			wep->m_flFallbackWear( ) = flExterior;
			wep->m_nFallbackSeed( ) = iSeed;
			if ( iStatTrak.second > -1 )
				wep->m_nFallbackStatTrak( ) = /*iStatTrak.first ? iStatTrak.second + _Context->pLocalPlayer->m_iKills :*/ iStatTrak.second;

			wep->m_Item(  )->m_iEntityQuality(  ) = enumItemQuality;
				
			if ( !strNametag.empty( ) )
				wep->m_szCustomName( ) = &strNametag[ 0 ];

			// todo stickers
		}
	}
	void __cdecl End( SFrameStageNotifyContext* _Context ) override
	{ }
	~CInventoryManager( )
	{
		if ( iStatTrak.first )
			iStatTrak.second += kills_to_save;
	}
public:
	bool bEquipped;
	int iSkin;
	float flExterior;
	int iSeed;
	EItemDefinitionIndex enumWeapon;
	EItemQuality enumItemQuality;
	std::string strNametag; // empty string indicates disabled
	std::pair< bool /*bLiveTracking*/, int /*iStatTrakCount*/ > iStatTrak; // -1 indicates disabled
	std::vector< int > vecStickers;
};
