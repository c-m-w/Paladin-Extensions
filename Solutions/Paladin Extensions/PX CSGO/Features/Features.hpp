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
		STATE_MAX
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
		SETTING_MATERIALS_MAX
	};

	struct settings_t
	{
		struct awareness_t
		{
			struct information_t
			{
				struct player_t
				{
					toggle_t bEnabled = false;
					toggle_t bOutline = false;
					float flOutlineThickness = 1.f;

					toggle_t bBox = false;
					toggle_t bDimesMode = false; // false is two, true is three
					toggle_t bDisplayMode = false; // false is screen, true is world
					float flBoxThickness = 1.f;
					float flBoxCornerLength = 1.f; // odd input only allowed

					toggle_t bStatistics = false;
					enum
					{
						LEFT,
						RIGHT,
						TOP,
						BOTTOM,
						SMART
					};
					flags_t fAlignment = SMART;
					toggle_t bName = false;
					toggle_t bDistance = false;
					toggle_t bWeapon = false;
					toggle_t bAmmo = false;
					toggle_t bHealth = false;
					toggle_t bArmor = false;

					toggle_t bBones = false;
					toggle_t bOrientation = false;

					toggle_t bDamageIndication = false;
				} _Players[ 2 ];

				struct entity_t
				{
					toggle_t bEnabled = false;
					toggle_t bOutline = false;
					float flOutlineThickness = 1.f;

					toggle_t bBox = false;
					toggle_t bDimesMode = false; // false is two, true is three
					toggle_t bDisplayMode = false; // false is screen, true is world
					float flBoxThickness = 1.f;
					float flBoxCornerLength = 1.f; // odd input only allowed

					toggle_t bStatistics = false;
					enum
					{
						LEFT,
						RIGHT,
						TOP,
						BOTTOM,
						SMART
					};
					flags_t fAlignment = SMART;
					toggle_t bWeaponName = false;
					toggle_t bDistance = false;
				} _Entity [ SETTING_ENTITY_MAX ];
			} _Information;
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
				} _Players[ 2 ] { };
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
					toggle_t bFlat = false;
					toggle_t bDrawAboveAll = false;
					toggle_t bWireFrame = false;
					toggle_t bWireFrameOverlay = false;
					toggle_t bWireFrameUnderlay = false;

					color_sequence_t seqColor[ STATE_MAX ] { }; 
					color_sequence_t seqWireFrameOverlay[ STATE_MAX ] { };
					color_sequence_t seqWireFrameUnderlay[ STATE_MAX ] { };
				} _Entities[ SETTING_MATERIALS_MAX ] { };
			} _Materials;
		} _Awareness;

		struct miscellaneous_t
		{
			struct movement_t
			{
				toggle_t bAutoJump = false;
				key_t kAutoJumpKey = VK_SPACE;
				toggle_t bEdgeJump = false;
				key_t kEdgeJumpKey = 0;

			} _Movement;
		} _Miscellaneous;
	} PX_SDK _Settings;

	bool PX_API InitializeFeatures( );
	void PX_API ShutdownFeatures( );

	enum
	{
		SETTING_TEAM,
		SETTING_ENEMY,
		SETTING_WEAPON = 0,
		SETTING_C4
	};
}
