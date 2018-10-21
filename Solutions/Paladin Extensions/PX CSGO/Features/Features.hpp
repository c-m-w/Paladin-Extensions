/// Features.hpp

#pragma once

namespace PX::Features
{
	extern nlohmann::json jsConfig;

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

	inline struct settings_t
	{
		struct awareness_t
		{
			struct extra_sensory_drawing_t
			{
				struct extra_sensory_drawing_base_t
				{
					toggle_t bEnabled = false;
					toggle_t bVisible = false;
					toggle_t bInvisible = false;

					toggle_t bMindSmoke = false;
					int iBoxMode = BOX_NONE; // only static
					color_sequence_t seqBox[ STATE_MAX ];
					toggle_t bFill = false;
					color_sequence_t seqFill[ STATE_MAX ];

					toggle_t bSnaplines = false;
					color_sequence_t seqSnaplines[ STATE_MAX ];
					float flSnaplineWidth = 1.f;

					toggle_t bShowInformation = false;
					color_sequence_t seqInformation[ STATE_MAX ];
					toggle_t bShowName = false;
					toggle_t bWeaponText = false;
					int iInformationAlignment = ALIGNMENT_BOTTOM;
					toggle_t bInformationOutline = false;
					color_sequence_t seqInformationOutline[ STATE_MAX ];
				} _Weapons[ 2 ];

				struct: extra_sensory_drawing_base_t
				{
					toggle_t bDormant = false;

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
				} _Players[ 2 ];
			} _ExtraSensoryDrawing;

			struct glow_t
			{
				struct player_t
				{
					toggle_t bEnabled = false;

					toggle_t bStates[ STATE_MAX ] { false, false, false };
					toggle_t bMindSmoke = false;

					color_sequence_t seqColor[ STATE_MAX ] { };

					toggle_t bHealthBasedColor = false;
					int iGlowStyle = 0;
					toggle_t bFullBloom = false;
					float flFullBloomAmount = 1.f;
				} _Players[ 2 ]; // team, enemy

				struct entity_t
				{
					toggle_t bEnabled = false;
					toggle_t bStates[ STATE_MAX ] { false, false, false };
					toggle_t bMindSmoke = false;

					color_sequence_t seqColor[ STATE_MAX ] { };

					int iGlowStyle = 0;
					toggle_t bFullBloom = false;
					float flFullBloomAmount = 1.f;
				} _Entities[ 4 ]; // weapons, c4, defuse kit, grenade
			} _Glow;
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
	} _Settings;

	bool PX_API InitializeFeatures( );

	enum
	{
		SETTING_TEAM,
		SETTING_ENEMY,
		SETTING_WEAPON = 0,
		SETTING_C4
	};
}
