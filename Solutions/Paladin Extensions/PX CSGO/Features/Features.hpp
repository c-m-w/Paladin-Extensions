/// Features.hpp

#pragma once

namespace PX::Features
{
	extern nlohmann::json jsConfig;

	enum EState
	{
		STATE_VISIBLE,
		STATE_INVISIBLE,
		STATE_DORMANT,
		STATE_MAX
	};

	inline struct settings_t
	{
		struct awareness_t
		{
			struct extra_sensory_drawing_t
			{
				struct
				{
					bool bEnabled = false;
					bool bVisible = false;
					bool bInvisible = false;
					bool bDormant = false;

					bool bMindSmoke = false;
					bool bBox = false;
					color_sequence_t seqBox[ STATE_MAX ];
					bool bThreeDimensional = false;

					bool bFill = false;
					color_sequence_t seqFill[ STATE_MAX ];
					bool bHealthBasedFillColor = false; // player only
					color_sequence_t seqHealthFill[ 2 ][ STATE_MAX ]; // player only
					bool bSolidHealthFill = false; // player only

					bool bSnaplines = false; 
					color_sequence_t seqSnaplines[ STATE_MAX ];
					float flSnaplineWidth = 1.f;

					bool bViewLines = false; // player only
					color_sequence_t seqViewLines[ STATE_MAX ]; // player only
					float flViewLineWidth = 1.f; // player only

					bool bSkeleton = false; // player only
					color_sequence_t seqSkeleton[ STATE_MAX ]; // player only
					float flSkeletonWidth = 1.f; // player only

					bool bShowHealth = false; // player only
					bool bHealthText = false; // player only
				} _Players[ 2 ];
			} _ExtraSensoryDrawing;
		} _Awareness;
	} _Settings;

	bool PX_API InitializeFeatures( );

	enum
	{
		TEAM,
		ENEMY
	};
}
