/// Features.hpp

#pragma once

namespace PX::Features
{
	extern nlohmann::json jsConfig;

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
					color_sequence_t seqBox[ 3 ];
					bool bThreeDimensional = false;

					bool bFill = false;
					color_sequence_t seqFill[ 3 ];
					bool bHealthBasedFillColor = false;
					bool bDottedFill = false;

					bool bSnaplines = false;
					color_sequence_t seqSnapline[ 3 ];
				} _Players[ 2 ];
			} _ExtraSensoryDrawing;
		} _Awareness;
	} _Settings;

	bool PX_API InitializeFeatures( );

	enum
	{
		VISIBLE,
		INVISIBLE,
		DORMANT
	};

	enum
	{
		TEAM,
		ENEMY
	};
}
