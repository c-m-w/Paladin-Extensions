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
					bool bEnabled = false;
					bool bVisible = false;
					bool bInvisible = false;

					bool bMindSmoke = false;
					int iBoxMode = BOX_NONE; // only static
					color_sequence_t seqBox[ STATE_MAX ];
					bool bFill = false;
					color_sequence_t seqFill[ STATE_MAX ];

					bool bSnaplines = false;
					color_sequence_t seqSnaplines[ STATE_MAX ];
					float flSnaplineWidth = 1.f;

					bool bShowInformation = false;
					color_sequence_t seqInformation[ STATE_MAX ];
					bool bShowName = false;
					bool bWeaponText = false;
					int iInformationAlignment = ALIGNMENT_BOTTOM;
					bool bInformationOutline = false;
					color_sequence_t seqInformationOutline[ STATE_MAX ];
				} _Weapons[ 2 ];

				struct: extra_sensory_drawing_base_t
				{
					bool bDormant = false;

					bool bThreeDimensional = false;

					bool bHealthBasedFillColor = false; // player only
					color_sequence_t seqHealthFill[ 2 ][ STATE_MAX ]; // player only
					bool bSolidHealthFill = false; // player only

					bool bViewLines = false; // player only
					color_sequence_t seqViewLines[ STATE_MAX ]; // player only
					float flViewLineWidth = 1.f; // player only

					bool bSkeleton = false; // player only
					color_sequence_t seqSkeleton[ STATE_MAX ]; // player only
					float flSkeletonWidth = 1.f; // player only

					bool bShowHealth = false; // player only
					bool bHealthBar = false; // player only
					color_sequence_t seqHealthBar[ 2 ][ STATE_MAX ]; // player only
					bool bShowRank = false; // player only
					bool bShowWeapon = false; // player only
				} _Players[ 2 ];
			} _ExtraSensoryDrawing;
		} _Awareness;

		struct miscellaneous_t
		{
			struct movement_t
			{
				bool bAutoJump = false;
				key_t kAutoJumpKey = VK_SPACE;
				bool bEdgeJump = false;
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
