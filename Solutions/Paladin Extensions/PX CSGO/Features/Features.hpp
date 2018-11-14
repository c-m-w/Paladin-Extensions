/// Features.hpp

#pragma once

namespace PX::Features
{
	enum EBox
	{
		BOX_NONE,
		BOX_DYNAMIC,
		BOX_STATIC
	};

	enum EState
	{
		STATE_VISIBLE,
		STATE_INVISIBLE,
		STATE_DORMANT,
		STATE_MAX,
	//	STATE_PLAYER_VULNERABLE = STATE_MAX,
	//	STATE_PLAYER_SPOTTED,
	//	STATE_PLAYER_HEARD,
		STATE_PLAYER_MAX = STATE_MAX
	};

	enum EAlignment
	{
		ALIGNMENT_LEFT,
		ALIGNMENT_TOP,
		ALIGNMENT_RIGHT,
		ALIGNMENT_BOTTOM,
		ALIGNMENT_SMART,
		ALIGNMENT_MAX
	};

	enum
	{
		// Player
		SETTING_PLAYER_TEAM,
		SETTING_PLAYER_ENEMY,
		SETTING_PLAYER_MAX,
		// Entity
		// Entity Weapons
		SETTING_ENTITY_WEAPONS = 0,
	//	SETTING_ENTITY_WEAPONS_MATERIALS_HELD_WEAPONS,
	//	SETTING_ENTITY_WEAPONS_MATERIALS_PLAYER_WEAPONS,
	//	SETTING_ENTITY_WEAPONS_MATERIALS_MAX,
		SETTING_ENTITY_C4,
		SETTING_ENTITY_PLANTED_C4,
		SETTING_ENTITY_DEFUSER,
		SETTING_ENTITY_CHICKEN,
		SETTING_ENTITY_GRENADE_HE,
		SETTING_ENTITY_GRENADE_FLASH,
		SETTING_ENTITY_GRENADE_SMOKE,
		SETTING_ENTITY_GRENADE_DECOY,
		SETTING_ENTITY_GRENADE_INCENDIARY,
		SETTING_ENTITY_GRENADE_PROJECTILE_HE,
		SETTING_ENTITY_GRENADE_PROJECTILE_FLASH,
		SETTING_ENTITY_GRENADE_PROJECTILE_SMOKE,
		SETTING_ENTITY_GRENADE_PROJECTILE_DECOY,
		SETTING_ENTITY_GRENADE_PROJECTILE_INCENDIARY,
		SETTING_ENTITY_MAX,
		// Weapon
	//	SETTING_WEAPON_PISTOLS,
	//	SETTING_WEAPON_SHOTGUNS,
	//	SETTING_WEAPON_SMGS,
	//	SETTING_WEAPON_RIFLES,
	//	SETTING_WEAPON_LMGS,
	//	SETTING_WEAPON_BOLT_SNIPERS,
	//	SETTING_WEAPON_AUTO_SNIPERS,
	//	SETTING_WEAPON_OTHERS,
	//	SETTING_WEAPON_MAX,
	};

	enum
	{
		SETTING_MATERIALS_SELF,
		SETTING_MATERIALS_TEAM,
		SETTING_MATERIALS_ENEMY,
		SETTING_MATERIALS_CHICKEN,
		SETTING_MATERIALS_WEAPONS,
		SETTING_MATERIALS_HELD_WEAPONS,
		SETTING_MATERIALS_PLAYER_WEAPONS,
		SETTING_MATERIALS_C4,
		SETTING_MATERIALS_PLANTED_C4,
		SETTING_MATERIALS_DEFUSER,
		SETTING_MATERIALS_HE,
		SETTING_MATERIALS_FLASH,
		SETTING_MATERIALS_SMOKE,
		SETTING_MATERIALS_DECOY,
		SETTING_MATERIALS_INCENDIARY,
		SETTING_MATERIALS_PROJECTILE_HE,
		SETTING_MATERIALS_PROJECTILE_FLASH,
		SETTING_MATERIALS_PROJECTILE_SMOKE,
		SETTING_MATERIALS_PROJECTILE_DECOY,
		SETTING_MATERIALS_PROJECTILE_INCENDIARY,
		SETTING_MATERIALS_MAX,
		SETTING_MATERIALS_MATERIAL_DEFAULT = 0,
		SETTING_MATERIALS_MATERIAL_IGNOREZ,
		SETTING_MATERIALS_MATERIAL_FLAT,
		SETTING_MATERIALS_MATERIAL_FLAT_IGNOREZ,
		SETTING_MATERIALS_MATERIAL_REFLECTIVE,
		//SETTING_MATERIALS_MATERIAL_GLOW,
		SETTING_MATERIALS_MATERIAL_GLASS,
		SETTING_MATERIALS_MATERIAL_CRYSTAL,
		SETTING_MATERIALS_MATERIAL_GOLD,
		SETTING_MATERIALS_MATERIAL_MAX
	};

	enum
	{
		AIMTYPE_DEFAULT,
		AIMTYPE_SMOOTH,
		AIMTYPE_SILENT
	};

	enum
	{
		SMOOTH_LINEAR,
		SMOOTH_PARABOLIC,
		SMOOTH_RADICAL,
		SMOOTH_SINUSOIDAL,
		SMOOTH_BEZIER,
		SMOOTH_RANDOMIZE
	};

	enum
	{
		TARGETING_DISTANCE,
		TARGETING_CROSSHAIR_DISTANCE,
		TARGETING_LOWEST_HEALTH
	};

	struct settings_t
	{
		struct awareness_t
		{
			struct statistics_t
			{
				struct a_statistics_base
				{
					toggle_t bEnabled = false;
					toggle_t bSmokeCheck = false;

					toggle_t bSnapline = false;
					toggle_t bSnaplineOutline = false;
					float flSnaplineThickness = 1.f;
					float flSnaplineOutlineThickness = 1.f;
					color_sequence_t seqSnaplineOutline { };
					toggle_t bSnaplineOrigin = false; // false is bottom, true is top
					toggle_t bSnaplineDestination = false; // false is bottom, true is top

					toggle_t bBox = false;
					toggle_t bBoxOutline = false;
					float flBoxOutlineThickness = 1.f;
					color_sequence_t seqBoxOutline { };
					toggle_t bDimesMode = false; // false is two, true is three
					toggle_t bDisplayMode = false; // false is screen, true is world
					float flBoxThickness = 1.f;
					float flBoxCornerLength = 1.f; // odd input only allowed

					toggle_t bInformation = false;
					color_sequence_t seqInformationOutline { };
					enum
					{
						LEFT,
						RIGHT,
						TOP,
						BOTTOM,
						SMART
					};
					flags_t fAlignment = SMART;
					toggle_t bIdentifier = false;
					toggle_t bDistance = false;
				};

				struct player_t: a_statistics_base
				{
					color_t clrHighestHealth = { 0x00, 0xFF, 0x00, 0xFF };
					color_t clrLowestHealth = { 0xFF, 0x00, 0x00, 0xFF };

					color_sequence_t seqSnapline[ STATE_PLAYER_MAX ] { };
					color_sequence_t seqBox[ STATE_PLAYER_MAX ] { };

					toggle_t bWeapon = false;
					toggle_t bWeaponIcon = false;
					color_sequence_t seqWeapon[ STATE_PLAYER_MAX ] { };
					toggle_t bAmmo = false;
					color_sequence_t seqAmmo[ STATE_PLAYER_MAX ] { };
					toggle_t bHealth = false;
					toggle_t bHealthColoredByHealth = false;
					color_sequence_t seqHealth[ STATE_PLAYER_MAX ] { };
					toggle_t bArmor = false;
					toggle_t bArmorIcon = false;
					toggle_t bArmorColoredByArmor = false;
					color_sequence_t seqArmor[ STATE_PLAYER_MAX ] { };

					toggle_t bDamageIndication = false;
					toggle_t bDamageIndicationColoredByDamage = false;
					color_sequence_t seqDamageIndication[ STATE_PLAYER_MAX ] { };

					toggle_t bBone = false;
					toggle_t bBoneOutline = false;
					float flBoneThickness = 1.f;
					float flBoneOutlineThickness = 1.f;
					toggle_t bBoneColoredByHealth = false;
					color_sequence_t seqBone[ STATE_PLAYER_MAX ] { };
					color_sequence_t seqBoneOutline { };

					toggle_t bOrientation = false;
					toggle_t bOrientationOutline = false;
					float flOrientationThickness = 1.f;
					float flOrientationOutlineThickness = 1.f;
					color_sequence_t seqOrientation[ STATE_PLAYER_MAX ] { };
					color_sequence_t seqOrientationOutline { };
				} _Players[ SETTING_PLAYER_MAX ];

				struct entity_t: a_statistics_base
				{
					toggle_t bIdentifierIcon = false;
					color_sequence_t seqInformation[ STATE_MAX ] { };
					color_sequence_t seqSnapline[ STATE_MAX ] { };
					color_sequence_t seqBox[ STATE_MAX ] { };
				} _Entities [ SETTING_ENTITY_MAX ];
			} _Statistics;
			struct extra_sensory_drawing_t
			{
				struct extra_sensory_drawing_base_t
				{
					toggle_t bEnabled = false;

					toggle_t bMindSmoke = false;
					int iBoxMode = BOX_NONE; // only static
					color_sequence_t seqBox[ STATE_MAX ] { };
					toggle_t bFill = false;
					color_sequence_t seqFill[ STATE_MAX ] { };

					toggle_t bSnaplines = false;
					color_sequence_t seqSnaplines[ STATE_MAX ] { };
					float flSnaplineWidth = 1.f;

					toggle_t bShowInformation = false;
					color_sequence_t seqInformation[ STATE_MAX ] { };
					toggle_t bShowName = false;
					toggle_t bWeaponText = false;
					int iInformationAlignment = ALIGNMENT_BOTTOM;
					toggle_t bInformationOutline = false;
					color_sequence_t seqInformationOutline[ STATE_MAX ] { };
				} _Weapons[ 2 ];

				struct: extra_sensory_drawing_base_t
				{
					toggle_t bThreeDimensional = false;

					toggle_t bHealthBasedFillColor = false; // player only
					color_sequence_t seqHealthFill[ 2 ][ STATE_MAX ]; // player only
					toggle_t bSolidHealthFill = false; // player only

					toggle_t bViewLines = false; // player only
					color_sequence_t seqViewLines[ STATE_MAX ]; // player only
					float flViewLineWidth = 1.f; // player only

					toggle_t bSkeleton = false; // player only
					color_sequence_t seqSkeleton[ STATE_MAX ]; // player only
					float flSkeletonWidth = 1.f; // player only

					toggle_t bShowHealth = false; // player only
					toggle_t bHealthBar = false; // player only
					color_sequence_t seqHealthBar[ 2 ][ STATE_MAX ]; // player only
					toggle_t bShowRank = false; // player only
					toggle_t bShowWeapon = false; // player only
				} _Players[ SETTING_PLAYER_MAX ] { };
			} _ExtraSensoryDrawing;

			struct glow_t
			{
				struct player_t
				{
					toggle_t bEnabled = false;
					toggle_t bMindSmoke = false;

					color_sequence_t seqColor[ STATE_MAX ] { };

					toggle_t bHealthBasedColor = false;
					int iGlowStyle = 0;
					toggle_t bFullBloom = false;
					float flFullBloomAmount = 1.f;
				} _Players[ SETTING_PLAYER_MAX ] { }; // team, enemy

				struct entity_t
				{
					toggle_t bEnabled = false;
					toggle_t bMindSmoke = false;

					color_sequence_t seqColor[ STATE_MAX ] { };

					int iGlowStyle = 0;
					toggle_t bFullBloom = false;
					float flFullBloomAmount = 1.f;
				} _Entities[ SETTING_ENTITY_MAX ] { }; // weapons, c4, defuse kit, grenade
			} _Glow { };

			struct materials_t
			{
				struct entity_t
				{
					toggle_t bEnabled = false;
					toggle_t bWireFrame = false;
					toggle_t bWireFrameOverlay = false;
					toggle_t bWireFrameUnderlay = false;
					int iMaterial = SETTING_MATERIALS_MATERIAL_DEFAULT;

					color_sequence_t seqColor[ STATE_MAX ] { }; 
					color_sequence_t seqWireFrameOverlay[ STATE_MAX ] { };
					color_sequence_t seqWireFrameUnderlay[ STATE_MAX ] { };
				} _Entities[ SETTING_MATERIALS_MAX ] { };
			} _Materials;
		} _Awareness;

		struct combat_t
		{
			constexpr static float SMOOTHING_MIN = 1.f;
			constexpr static float SMOOTHING_MAX = 100.f;
			struct trigger_t
			{
				struct weapon_t
				{
					toggle_t bTeammates = false;
					toggle_t bEnemies = false;
					toggle_t bHitGroups[ HITGROUP_MAX ] { };
					toggle_t bMindSmoke = false;
					toggle_t bUseSeparate = false; // only for _WeaponTypes and _IndividualWeapons to use separate from the rest
					float flHitChance = 0.f;
					int iRays = 100; // 100 to 255
				} _All, _WeaponTypes[ WEAPONTYPE_MACHINEGUN + 1 ] { }, _IndividualWeapons[ ITEM_MAX ] { };
			} _Trigger;

			struct aim_t
			{
				struct weapon_t
				{
					toggle_t bTeammates = false;
					toggle_t bEnemies = false;
					toggle_t bHitboxes[ HITBOX_MAX ] { };
					toggle_t bMindSmoke = false;
					toggle_t bUseSeparate = false;
					toggle_t bWorldlyCrosshairDistance = false;
					toggle_t bStaticTarget = false;
					toggle_t bValidateTarget = false;
					int iReferenceHitbox = HITBOX_HEAD; // hitbox to use as reference for seeing which players are within crosshair distance.
					int iPriorityHitbox = HITBOX_HEAD;
					int iAimType = AIMTYPE_DEFAULT;
					float flOverCompensation = 0.f; // +- xyz
					float flMaxCrosshairDistance = 1.f;
					float flMaxWorldCrosshairDistance = 1.f;
					float flSmoothFactor = SMOOTHING_MIN;
					Tools::bezier_order_t _BezierOrders[ 7 ];
					int iCurrentOrders = 0;
					int iSmoothMode = SMOOTH_LINEAR;
					int iTargeting = TARGETING_DISTANCE;
				} _All, _WeaponTypes[ WEAPONTYPE_MACHINEGUN + 1 ] { }, _IndividualWeapons[ ITEM_MAX ] { };
			} _Aim;

			struct recoil_compensation_t
			{
				struct weapon_t
				{
					toggle_t bEnabled = false;
					toggle_t bStandalone = false;
					toggle_t bOnlyWhileShooting = false;
					toggle_t bUseSeparate = false;
					float flCompensationAmount = 1.f; // 0.f to 2.f
					float flStandaloneSmoothing = SMOOTHING_MIN;
				} _All, _WeaponTypes[ WEAPONTYPE_MACHINEGUN + 1 ] { }, _IndividualWeapons[ ITEM_MAX ] { };
			} _RecoilCompensation;
		} _Combat;

		struct miscellaneous_t
		{
			struct movement_t
			{
				toggle_t bAutomaticJump = false;
				float flMissChance = 0.f; // 0.f -> 1.f
				toggle_t bEdgeJump = false;
				toggle_t bAutomaticStrafe = false;
				float flSync = 0.f; // 0.f -> 100.f
				toggle_t bAutonomousStrafe = false; // one or the other
			} _Movement;

			struct visuals_t
			{
				toggle_t bDarkenWorld = false;
				toggle_t bDrawAimFOV = false;
				color_sequence_t seqAimFOV[ 2 ] { }; // inner, outer
				toggle_t bVisualizeSpread = false;
				color_sequence_t seqSpread[ 2 ] { }; // inner, outer
			} _Visuals;

			struct inventory_t
			{
				struct team_t
				{
					toggle_t bModifyInventory = false;
					toggle_t bModifyKnifeModel = false;
					toggle_t bModifyGloveModel = false;

					struct
					{
						int iPaintKitID = 0;
						toggle_t bSouvenier = false;
						toggle_t bStatTrak = false;
						toggle_t bUseCustomName = false;
						char szName[ 32 ] { };
						wchar_t wszName[ 32 ] { };
						float flWear = 0.f;
						int iSeed = 0;
						int iStatTrakCounter = -1;
					} _PaintKits[ ITEM_MAX ];

					struct
					{
						int iKnifeModel = 0, iGloveModel = 0;
					} _Models;
				} _Terrorist, _CounterTerrorist;
			} _Inventory;
		} _Miscellaneous;
	} PX_SDK _Settings;

	bool PX_API InitializeFeatures( );
	void PX_API ShutdownFeatures( );

	using trigger_config_t = settings_t::combat_t::trigger_t::weapon_t;
	using aim_config_t = settings_t::combat_t::aim_t::weapon_t;
	using recoil_config_t = settings_t::combat_t::recoil_compensation_t::weapon_t;

	enum
	{
		SETTING_TEAM,
		SETTING_ENEMY,
		SETTING_WEAPON = 0,
		SETTING_C4
	};
}
