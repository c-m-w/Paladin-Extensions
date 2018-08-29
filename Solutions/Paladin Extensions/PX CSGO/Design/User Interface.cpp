/// User Interface.cpp

#include "../PX CSGO.hpp"

using namespace PX::Information;
using namespace Pointers;
using namespace Modules;
using namespace PX::UI;
using namespace Widgets;
using namespace PX::Features;

namespace PX::UI::Manager
{
	namespace CSGO
	{
		bool PX_API Initialize( )
		{
			int iDimensions[ 2 ];
			unsigned uDimensions[ 2 ];

			pEngineClient->GetScreenSize( iDimensions[ 0 ], iDimensions[ 1 ] );
			memcpy( uDimensions, iDimensions, sizeof( int ) * 2 );
			Render::bShouldRender = false;

			PX_INPUT.AddKeyCallback( VK_HOME, [ = ]( bool bIsPressed )
			{
				if( bIsPressed )
					Render::bShouldRender = !Render::bShouldRender;
				while( ShowCursor( true ) <= 0 );
			} );

			return Render::InitializeRenderTarget( pDevice, uDimensions )
				&& InitializeUI( PX_XOR( "CSGO" ), 720u, 600u );
		}

		void PX_API OnEndScene( Types::ptr_t ptrReturnAddress )
		{
			static auto ptrDesiredReturnAddress = 0u;
			static auto bPrintedStates = false;
			auto bPrintStates = bool( PX_INPUT.GetKeyState( VK_RETURN ) ) && !bPrintedStates;

			if ( !ptrDesiredReturnAddress )
			{
				if ( Tools::FindAddressOrigin( ptrReturnAddress ) == mOverlay.hModule )
					ptrDesiredReturnAddress = ptrReturnAddress;
			}

			if ( ptrDesiredReturnAddress == ptrReturnAddress )
				if ( Render::bShouldRender && bCreatedTextures )
					Render( );
		}

		void PX_API OnReset( )
		{
			Render::bShouldRender = false;
			bCreatedTextures = false;
		}

		void PX_API OnSuccessfulReset( unsigned uWidth, unsigned uHeight )
		{
			bCreatedTextures = true;
		}
	}

	void PX_API LayoutAwareness( int iSubtab );
	void PX_API LayoutCombat( int iSubtab );
	void PX_API LayoutMiscellaneous( int iSubtab );
	void PX_API LayoutSettings( int iSubtab );

	void PX_API SetLayout( )
	{
		constexpr auto iTabCount = 4;
		static const std::deque< cstr_t > dqPrimaryTabs
		{
			ICON_FA_EYE " AWARENESS",
			ICON_FA_CROSSHAIRS " COMBAT",
			ICON_FA_QUESTION_CIRCLE " MISCELLANEOUS",
			ICON_FA_COG " SETTINGS"
		};

		static const std::deque< std::deque< cstr_t > > dqSubTabs
		{
			
			{
				"Extra Sensory Drawing",
				"Glow",
				"Materials"
			},
			{
				"Tab"
			},
			{
				"Tab"
			},
			{
				"Tab"
			}
		};

		static const auto fnSetTabValue = [ ]( int& iCurrentValue, const int iNewValue )
		{
			iCurrentValue = iNewValue >= 0 ? iNewValue : iCurrentValue;
		};

		static auto iCurrentTab = 0;
		static int iCurrentSubTab[ iTabCount ] { };
		const static std::function< void( PX_API )( int ) > fnTabCallbacks[ iTabCount ] { LayoutAwareness, LayoutCombat, LayoutMiscellaneous, LayoutSettings };

		Header( PX_XOR( "Paladin Extensions" ), szNuklearWindowTitle );
		fnSetTabValue( iCurrentTab, Tabs( 10, 0, dqPrimaryTabs, iCurrentTab ) );
		Separator( 61, 65, 72, 100 );
		SetFont( FONT_ROBOTOSMALL );
		fnSetTabValue( iCurrentSubTab[ iCurrentTab ], SubTabs( 10, 60, 175, 30, dqSubTabs[ iCurrentTab ], iCurrentSubTab[ iCurrentTab ] ) );
		fnTabCallbacks[ iCurrentTab ]( iCurrentSubTab[ iCurrentTab ] );
	}

	void PX_API LayoutAwareness( int iSubtab )
	{
		enum
		{
			EXTRA_SENSORY_DRAWING,
			GLOW,
			MATERIALS
		};

		switch ( iSubtab )
		{
			case EXTRA_SENSORY_DRAWING:
			{
				auto& esdConfig = _Settings._Awareness._ExtraSensoryDrawing;

				if ( BeginGroupbox( 200, 150, 500, 420, PX_XOR( "Teammates" ) ) )
				{
					VerticalSpacing( );

					BeginRow( 15, 3, ROW_STATIC );
					SetRowWidth( 5 );
					Spacing( );

					Checkbox( PX_XOR( "Enabled" ), &esdConfig._Players[ TEAM ].bEnabled, PX_XOR( "Enable teammate extra sensory drawing." ) );

					EndRow( );

					VerticalSpacing( );

					BeginRow( 15, 15, ROW_STATIC );
					SetRowWidth( 5 );
					Spacing( );

					Checkbox( PX_XOR( "Box" ), &esdConfig._Players[ TEAM ].bBox, PX_XOR( "Enable drawing a box overtop of your teammates." ) );
					SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( "Box", 15 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
					Spacing( );
					SetRowWidth( COLOR_BUTTON_WIDTH );
					ColorButton( PX_XOR( "Teammate Box Visible" ), &esdConfig._Players[ TEAM ].seqBox[ VISIBLE ] );
					ColorButton( PX_XOR( "Teammate Box Invisible" ), &esdConfig._Players[ TEAM ].seqBox[ INVISIBLE ] );
					ColorButton( PX_XOR( "Teammate Box Dormant" ), &esdConfig._Players[ TEAM ].seqBox[ DORMANT ] );

					Checkbox( PX_XOR( "Fill" ), &esdConfig._Players[ TEAM ].bFill, PX_XOR( "Enable filling in the box drawn overtop of your temmates." ) );
					SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Fill" ), 15 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
					Spacing( );
					SetRowWidth( COLOR_BUTTON_WIDTH );
					ColorButton( PX_XOR( "Teammate Box Fill Visible" ), &esdConfig._Players[ TEAM ].seqFill[ VISIBLE ] );
					ColorButton( PX_XOR( "Teammate Box Fill Invisible" ), &esdConfig._Players[ TEAM ].seqFill[ INVISIBLE ] );
					ColorButton( PX_XOR( "Teammate Box Fill Dormant" ), &esdConfig._Players[ TEAM ].seqFill[ DORMANT ] );

					Checkbox( PX_XOR( "Health-Based Fill" ), &esdConfig._Players[ TEAM ].bHealthBasedFillColor, PX_XOR( "Use your teammate's health to color the box fill." ) );

					EndRow( );

					VerticalSpacing( );

					EndGroupbox( );
				}
			}
				break;

			case GLOW:
			{

			}
			break;

			case MATERIALS:
			{

			}
			break;

			default:
				break;
		}
	}

	void PX_API LayoutCombat( int iSubtab )
	{
		enum
		{

		};

		switch ( iSubtab )
		{
			default:
				break;
		}
	}

	void PX_API LayoutMiscellaneous( int iSubtab )
	{
		enum
		{

		};

		switch ( iSubtab )
		{
			default:
				break;
		}
	}

	void PX_API LayoutSettings( int iSubtab )
	{
		enum
		{

		};

		switch ( iSubtab )
		{
			default:
				break;
		}
	}
}
