/// Features.cpp

#include "../PX CSGO.hpp"

#define NOCOLOR 0x000000FFu

namespace PX::Features
{
	nlohmann::json jsConfig;

	bool PX_API InitializeFeatures( )
	{
		// Set up config file.
		jsConfig = nlohmann::json
		{
			{ PX_XOR( "Awareness" ), {
				{ PX_XOR( "Extra Sensory Drawing" ), {
					{ PX_XOR( "Players" ), {
							{
								{ PX_XOR( "Enabled" ), false },
								{ PX_XOR( "Mind Smoke" ), false },
								{ "Box", false },
								{ "Box Color",
									{
										NOCOLOR, NOCOLOR, NOCOLOR
									}
								},
								{ "Three Dimensional", false },
								{ "Fill", false },
								{ "Fill Color",
									{
										NOCOLOR, NOCOLOR, NOCOLOR
									}
								},
								{ "Health Based Fill", false },
								{ "Dotted Fill", false },
								{ "Snaplines", false },
								{
									"Snaplines Color",
									{
										NOCOLOR, NOCOLOR, NOCOLOR
									}
								}
							},
							{ // Enemy
								{ PX_XOR( "Enabled" ), false },
								{ PX_XOR( "Mind Smoke" ), false },
								{ "Box", false },
								{ "Box Color", {
										NOCOLOR, NOCOLOR, NOCOLOR
									}
								},
								{ "Three Dimensional", false },
								{ "Fill", false },
								{ "Fill Color",	{
										NOCOLOR, NOCOLOR, NOCOLOR
									}
								},
								{ "Health Based Fill", false },
								{ "Dotted Fill", false },
								{ "Snaplines", false },
								{ "Snaplines Color", {
										NOCOLOR, NOCOLOR, NOCOLOR
									}
								}
							}
						}
					}
				}
				},
				{ PX_XOR( "Glow" ),
				{

				} },
				{ PX_XOR( "Materials" ),
				{

				} }
					}
			},
			{ PX_XOR( "Combat" ),
			{
			} },
			{ PX_XOR( "Miscellaneous" ),
			{
			} },
			{ PX_XOR( "Settings" ),
			{
			} }
		};
		auto str = jsConfig.dump( 4 );
		return true;
	}
}
