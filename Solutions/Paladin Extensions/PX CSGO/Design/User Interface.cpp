/// User Interface.cpp

#include "PX Precompiled.hpp"
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
		void PX_API ChangeVisibility( )
		{
			static HWND* pOldWindowHandle = nullptr;
			static HCURSOR hOldCursor;
			
			Render::bShouldRender = !Render::bShouldRender;
			static const auto ptrOffset = *reinterpret_cast< ptr_t* >( ptr_t( ( *reinterpret_cast< void*** >( pInputSystem ) )[ 10 ] ) + 0x5 );
			std::swap( pOldWindowHandle, *reinterpret_cast< HWND** >( reinterpret_cast< byte_t* >( pInputSystem ) + ptrOffset ) );

			if ( Render::bShouldRender )
				hOldCursor = SetCursor( nullptr );
			else
			{
				SetCursor( hOldCursor );
				while ( ShowCursor( TRUE ) <= 0 );
			}
		}

		bool PX_API Initialize( )
		{
			int iDimensions[ 2 ];
			unsigned uDimensions[ 2 ];

			pEngineClient->GetScreenSize( iDimensions[ 0 ], iDimensions[ 1 ] );
			memcpy( uDimensions, iDimensions, sizeof( int ) * 2 );
			Render::bShouldRender = false;

			PX_INPUT.AddGlobalCallback( [ = ]( unsigned uKey, bool bIsPressed )
			{
				PX_DEF uKeyPressSequenceSize = 11u;
				const static unsigned uKeyPresses[ uKeyPressSequenceSize ] { VK_UP, VK_UP, VK_DOWN, VK_DOWN, VK_LEFT, VK_RIGHT, VK_LEFT, VK_RIGHT, 'B', 'A', VK_RETURN };
				static std::deque< unsigned > dqKeyPresses;
				if ( bIsPressed )
				{
					if ( uKey == VK_HOME )
					{
						ChangeVisibility( );
						return;
					}

					dqKeyPresses.emplace_back( uKey );
					if ( dqKeyPresses.size( ) > uKeyPressSequenceSize )
						dqKeyPresses.pop_front( );
					if ( dqKeyPresses.size( ) == uKeyPressSequenceSize )
					{
						auto bCorrectSequence = true;
						for ( auto u = 0u; u < uKeyPressSequenceSize; u++ )
							if ( uKeyPresses[ u ] != dqKeyPresses[ u ] )
								bCorrectSequence = false;
						if ( bCorrectSequence )
							ChangeVisibility( );
					}
				}
			} );

			return Render::InitializeRenderTarget( pDevice, uDimensions )
				&& InitializeUI( PX_XOR( "CSGO" ), 720u, 600u );
		}

		void PX_API OnEndScene( )
		{
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
	constexpr auto COLOR_BUTTON_VERTICAL_PADDING = 7.5f;

	static const auto fnSetValue = [ ]( int& iCurrentValue, const int iNewValue )
	{
		iCurrentValue = iNewValue >= 0 ? iNewValue : iCurrentValue;
	};

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
				"Extra Sensory Drawing 1",
				"Extra Sensory Drawing 2",
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


		static auto iCurrentTab = 0;
		static int iCurrentSubTab[ iTabCount ] { };
		const static std::function< void( PX_API )( int ) > fnTabCallbacks[ iTabCount ] { LayoutAwareness, LayoutCombat, LayoutMiscellaneous, LayoutSettings };

		Header( PX_XOR( "Paladin Extensions" ), szNuklearWindowTitle, 102, CSGO::ChangeVisibility, [](){exit( -1 );} );
		fnSetValue( iCurrentTab, Tabs( 10, 0, dqPrimaryTabs, iCurrentTab ) );
		Separator( 61, 65, 72, 100 );
		SetFont( FNT_ROBOTO_SMALL );
		fnSetValue( iCurrentSubTab[ iCurrentTab ], SubTabs( 10, 60, 175, 30, dqSubTabs[ iCurrentTab ], iCurrentSubTab[ iCurrentTab ] ) );
		fnTabCallbacks[ iCurrentTab ]( iCurrentSubTab[ iCurrentTab ] );
	}

	void PX_API LayoutAwareness( int iSubtab )
	{
		enum
		{
			EXTRA_SENSORY_DRAWING_1,
			EXTRA_SENSORY_DRAWING_2,
			GLOW,
			MATERIALS
		};

		switch ( iSubtab )
		{
			case EXTRA_SENSORY_DRAWING_2:
			case EXTRA_SENSORY_DRAWING_1:
			{
				auto iEntity = iSubtab == EXTRA_SENSORY_DRAWING_2 ? SETTING_ENEMY : SETTING_TEAM;
				auto& esdConfig = _Settings._Awareness._ExtraSensoryDrawing;

				if ( BeginGroupbox( 200, 150, 500, 420, iEntity == SETTING_TEAM ? PX_XOR( "Teammates" ) : PX_XOR( "Enemies" ) ) )
				{
					{
						BeginRow( 30, 3, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Enabled" ), &esdConfig._Players[ iEntity ].bEnabled, PX_XOR( "Enable teammate extra sensory drawing." ) );

						EndRow( );
					}

					{
						std::deque< cstr_t > dqBoxModes
						{
							PX_XOR( "None" ),
							PX_XOR( "Dynamic" ),
							PX_XOR( "Static" )
						};

						BeginRow( 30, 15, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						//Checkbox( PX_XOR( "Box" ), &esdConfig._Players[ iEntity ].bBox, PX_XOR( "Enable drawing a box overtop of your teammates." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - COLOR_BUTTON_PADDING * 7 - COLOR_BUTTON_WIDTH * 3 );
						fnSetValue( esdConfig._Players[ iEntity ].iBoxMode, Combobox( 25, PX_XOR( "Box" ), dqBoxModes, esdConfig._Players[ iEntity ].iBoxMode ) );
						SetRowWidth( 1 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Box Visible" ), &esdConfig._Players[ iEntity ].seqBox[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Box Invisible" ), &esdConfig._Players[ iEntity ].seqBox[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Box Dormant" ), &esdConfig._Players[ iEntity ].seqBox[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Three Dimensional" ), &esdConfig._Players[ iEntity ].bThreeDimensional, PX_XOR( "Render a three dimensional prism overtop of your teammates." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Three Dimensional" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Fill" ), &esdConfig._Players[ iEntity ].bFill, PX_XOR( "Enable filling in the box drawn overtop of your temmates." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Fill" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Box Fill Visible" ), &esdConfig._Players[ iEntity ].seqFill[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Box Fill Invisible" ), &esdConfig._Players[ iEntity ].seqFill[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Box Fill Dormant" ), &esdConfig._Players[ iEntity ].seqFill[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						BeginRow( 30, 12, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Health-Based Fill" ), &esdConfig._Players[ iEntity ].bHealthBasedFillColor, PX_XOR( "Use your teammate's health to color the box fill." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH * 2 - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Health-Based Fill" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 6 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Box Fill Health Bottom Visible" ), &esdConfig._Players[ iEntity ].seqHealthFill[ 0 ][ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Box Fill Health Bottom Invisible" ), &esdConfig._Players[ iEntity ].seqHealthFill[ 0 ][ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Box Fill Health Bottom Dormant" ), &esdConfig._Players[ iEntity ].seqHealthFill[ 0 ][ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Box Fill Health Top Visible" ), &esdConfig._Players[ iEntity ].seqHealthFill[ 1 ][ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Box Fill Health Top Invisible" ), &esdConfig._Players[ iEntity ].seqHealthFill[ 1 ][ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Box Fill Health Top Dormant" ), &esdConfig._Players[ iEntity ].seqHealthFill[ 1 ][ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Solid" ), &esdConfig._Players[ iEntity ].bSolidHealthFill, PX_XOR( "Don't apply a transparent gradient to the health fill." ) );

						EndRow( );
					}

					{
						BeginRow( 30, 19, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Snaplines" ), &esdConfig._Players[ iEntity ].bSnaplines, PX_XOR( "Draw a line from the bottom of your screen to your teammates." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Snaplines" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Snapline Visible" ), &esdConfig._Players[ iEntity ].seqSnaplines[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Snapline Invisible" ), &esdConfig._Players[ iEntity ].seqSnaplines[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Snapline Dormant" ), &esdConfig._Players[ iEntity ].seqSnaplines[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Viewlines" ), &esdConfig._Players[ iEntity ].bViewLines, PX_XOR( "Draw a line from where your teammate is looking until it hits a surface." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Viewlines" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Viewline Visible" ), &esdConfig._Players[ iEntity ].seqViewLines[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Viewline Invisible" ), &esdConfig._Players[ iEntity ].seqViewLines[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Viewline Dormant" ), &esdConfig._Players[ iEntity ].seqViewLines[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Skeleton" ), &esdConfig._Players[ iEntity ].bSkeleton, PX_XOR( "Draw a skeleton overtop of your teammates." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Skeleton" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Skeleton Visible" ), &esdConfig._Players[ iEntity ].seqSkeleton[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Skeleton Invisible" ), &esdConfig._Players[ iEntity ].seqSkeleton[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Skeleton Dormant" ), &esdConfig._Players[ iEntity ].seqSkeleton[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						std::deque< bool* > dqInformationOptions
						{
							&esdConfig._Players[ iEntity ].bShowHealth.Get( ),
							&esdConfig._Players[ iEntity ].bShowName.Get( ),
							&esdConfig._Players[ iEntity ].bShowRank.Get( ),
							&esdConfig._Players[ iEntity ].bShowWeapon.Get( )
						};

						static std::deque< cstr_t > dqInformationText
						{
							PX_XOR( "Health" ),
							PX_XOR( "Name" ),
							PX_XOR( "Rank" ),
							PX_XOR( "Weapon" )
						};

						static std::deque< cstr_t > dqAlignment
						{
							PX_XOR( "Left" ),
							PX_XOR( "Top" ),
							PX_XOR( "Right" ),
							PX_XOR( "Bottom" ),
							PX_XOR( "Smart" )
						};

						BeginRow( 30, 11, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Information" ), &esdConfig._Players[ iEntity ].bShowInformation, PX_XOR( "Draw informational text/icons around your teammates." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Information" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Information Visible" ), &esdConfig._Players[ iEntity ].seqInformation[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Information Invisible" ), &esdConfig._Players[ iEntity ].seqInformation[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Information Dormant" ), &esdConfig._Players[ iEntity ].seqInformation[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						SetRowWidth( 3 );
						Spacing( );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						ComboboxMulti( 25, PX_XOR( "Information" ), dqInformationText, dqInformationOptions );

						SetRowWidth( 3 );
						Spacing( );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( esdConfig._Players[ iEntity ].iInformationAlignment, Combobox( 25, PX_XOR( "Alignment" ), dqAlignment, esdConfig._Players[ iEntity ].iInformationAlignment ) );

						EndRow( );
					}

					{
						BeginRow( 30, 16, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Health Bar" ), &esdConfig._Players[ iEntity ].bHealthBar, PX_XOR( "Draw a health bar rather than text for your teammates." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH * 2 - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Health Bar" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 6 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Healthbar Bottom Visible" ), &esdConfig._Players[ iEntity ].seqHealthBar[ 0 ][ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Healthbar Bottom Invisible" ), &esdConfig._Players[ iEntity ].seqHealthBar[ 0 ][ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Healthbar Bottom Dormant" ), &esdConfig._Players[ iEntity ].seqHealthBar[ 0 ][ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Healthbar Top Visible" ), &esdConfig._Players[ iEntity ].seqHealthBar[ 1 ][ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Healthbar Top Invisible" ), &esdConfig._Players[ iEntity ].seqHealthBar[ 1 ][ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Healthbar Top Dormant" ), &esdConfig._Players[ iEntity ].seqHealthBar[ 1 ][ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Outline Info" ), &esdConfig._Players[ iEntity ].bInformationOutline, PX_XOR( "Draw an outline over information for your teammates." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Outline Info" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Info. Outline Visible" ), &esdConfig._Players[ iEntity ].seqInformationOutline[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Info. Outline Invisible" ), &esdConfig._Players[ iEntity ].seqInformationOutline[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Info. Outline Dormant" ), &esdConfig._Players[ iEntity ].seqInformationOutline[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						static char szSnaplineWidth[ 64 ] { }, szViewlineWidth[ 64 ] { }, szSkeletonWidth[ 64 ] { }, szInformationOutlineWidth[ 64 ] { };

						BeginRow( 30, 9, ROW_CUSTOM );

						esdConfig._Players[ iEntity ].flSnaplineWidth = Slider( PX_XOR( "Snapline Width" ), szSnaplineWidth, 1.f, 5.f, esdConfig._Players[ iEntity ].flSnaplineWidth, 15, 0, GROUPBOX_COLUMN_WIDTH, 30, 1 );
						esdConfig._Players[ iEntity ].flViewLineWidth = Slider( PX_XOR( "Viewline Width" ), szViewlineWidth, 1.f, 5.f, esdConfig._Players[ iEntity ].flViewLineWidth, GROUPBOX_COLUMN_WIDTH + 30, 0, GROUPBOX_COLUMN_WIDTH, 30, 1 );
						esdConfig._Players[ iEntity ].flSkeletonWidth = Slider( PX_XOR( "Skeleton Width" ), szSkeletonWidth, 1.f, 5.f, esdConfig._Players[ iEntity ].flSkeletonWidth, GROUPBOX_COLUMN_WIDTH * 2 + 40, 0, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						EndRow( );
					}

					EndGroupbox( );
				}
			}
			break;

			case GLOW:
			{
				auto& esdConfig = _Settings._Awareness._Glow;
				std::deque< cstr_t > dqGlowStyles
				{
					PX_XOR( "Default" ),
					PX_XOR( "Pulsate" ),
					PX_XOR( "Thin" ),
					PX_XOR( "Thin Pulsate" )
				};

				if ( BeginGroupbox( 200, 150, 500, 220, PX_XOR( "Players" ) ) )
				{
					static auto iEntity = 0;
					{
						std::deque< cstr_t > dqEntities
						{
							PX_XOR( "Teammates" ),
							PX_XOR( "Enemies" )
						};

						VerticalSpacing( );

						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH );

						fnSetValue( iEntity, Combobox( 30, PX_XOR( "Settings" ), dqEntities, iEntity ) );
						EndRow( );
					}

					{
						BeginRow( 30, 7, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Enabled" ), &esdConfig._Players[ iEntity ].bEnabled, PX_XOR( "Enable glow." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Enabled" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Glow Visible" ), &esdConfig._Players[ iEntity ].seqColor[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Glow Invisible" ), &esdConfig._Players[ iEntity ].seqColor[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Glow Dormant" ), &esdConfig._Players[ iEntity ].seqColor[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						BeginRow( 30, 9, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Health Based Color" ), &esdConfig._Players[ iEntity ].bHealthBasedColor, PX_XOR( "Use health to calculate the color." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Health Based Color" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Full Bloom" ), &esdConfig._Players[ iEntity ].bFullBloom, PX_XOR( "Apply full bloom to the entity." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Full Bloom" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Smoke Check" ), &esdConfig._Players[ iEntity ].bMindSmoke, PX_XOR( "Check to see if the entity is behind a smoke grenade. " ) );

						EndRow( );
					}

					{
						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( esdConfig._Players[ iEntity ].iGlowStyle, Combobox( 30, PX_XOR( "Glow Style" ), dqGlowStyles, esdConfig._Players[ iEntity ].iGlowStyle ) );

						EndRow( );
					}

					{
						static char szFullbloomAmount[ 64 ] { };

						BeginRow( 30, 3, ROW_CUSTOM );

						esdConfig._Players[ iEntity ].flFullBloomAmount = Slider( PX_XOR( "Fullbloom Amount" ), szFullbloomAmount, 0.f, 1.f, esdConfig._Players[ iEntity ].flFullBloomAmount, 15, 0, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						EndRow( );
					}
					EndGroupbox( );
				}

				if ( BeginGroupbox( 400, 285, 500, 220, PX_XOR( "Entities" ) ) )
				{
					static auto uEntity = 0u;
					{
						std::deque< cstr_t > dqTabs
						{
							PX_XOR( "Entities" ),
							PX_XOR( "Grenades" ),
							PX_XOR( "Projectiles" )
						};

						std::deque< cstr_t > dqItems[ ]
						{
							{
								PX_XOR( "Weapons" ),
								PX_XOR( "C4" ),
								PX_XOR( "Planted C4" ),
								PX_XOR( "Defuse Kit" )
							},
							{
								PX_XOR( "HE" ),
								PX_XOR( "Flash" ),
								PX_XOR( "Smoke" ),
								PX_XOR( "Decoy" ),
								PX_XOR( "Incendiary" )
							},
							{
								PX_XOR( "Thrown HE" ),
								PX_XOR( "Thrown Flash" ),
								PX_XOR( "Thrown Smoke" ),
								PX_XOR( "Thrown Decoy" ),
								PX_XOR( "Thrown Incendiary" )
							}
						};

						VerticalSpacing( );

						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH * 2 );

						TabbedCombobox( 30, PX_XOR( "Settings" ), dqTabs, dqItems, uEntity );
						EndRow( );
					}

					{
						BeginRow( 30, 6, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Enabled" ), &esdConfig._Entities[ uEntity ].bEnabled, PX_XOR( "Enable glow." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Enabled" ), 30 ).x - COLOR_BUTTON_PADDING * 4 - COLOR_BUTTON_WIDTH * 2 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Glow Visible" ), &esdConfig._Entities[ uEntity ].seqColor[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Glow Invisible" ), &esdConfig._Entities[ uEntity ].seqColor[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						BeginRow( 30, 8, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Full Bloom" ), &esdConfig._Entities[ uEntity ].bFullBloom, PX_XOR( "Apply full bloom to the entity." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Full Bloom" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Smoke Check" ), &esdConfig._Entities[ uEntity ].bMindSmoke, PX_XOR( "Check if the entity is behind a smoke grenade." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Smoke Check" ), 30 ).x );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( esdConfig._Entities[ uEntity ].iGlowStyle, Combobox( 30, PX_XOR( "Glow Style" ), dqGlowStyles, esdConfig._Entities[ uEntity ].iGlowStyle ) );

						EndRow( );
					}

					{
						static char szFullbloomAmount[ 64 ] { };

						BeginRow( 30, 3, ROW_CUSTOM );

						esdConfig._Entities[ uEntity ].flFullBloomAmount = Slider( PX_XOR( "Fullbloom Amount" ), szFullbloomAmount, 0.f, 1.f, esdConfig._Entities[ uEntity ].flFullBloomAmount, 15, 0, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						EndRow( );
					}

					EndGroupbox( );
				}
			}
			break;

			case MATERIALS:
			{
				auto& esdConfig = _Settings._Awareness._Materials;

				if ( BeginGroupbox( 200, 150, 500, 220, PX_XOR( "Players" ) ) )
				{
					static auto uEntity = 0u;
					{
						std::deque< cstr_t > dqTabs
						{
							PX_XOR( "Players" ),
							PX_XOR( "Entities" ),
							PX_XOR( "Grenades" ),
							PX_XOR( "Projectiles" )
						};

						std::deque< cstr_t > dqItems[ ]
						{
							{
								PX_XOR( "Self" ),
								PX_XOR( "Teammates" ),
								PX_XOR( "Enemies" )
							},
							{
								PX_XOR( "Weapons" ),
								PX_XOR( "Held Weapons" ),
								PX_XOR( "Players' Weapons" ),
								PX_XOR( "C4" ),
								PX_XOR( "Planted C4" ),
								PX_XOR( "Defuse Kit" )
							},
							{
								PX_XOR( "HE" ),
								PX_XOR( "Flash" ),
								PX_XOR( "Smoke" ),
								PX_XOR( "Decoy" ),
								PX_XOR( "Incendiary" )
							},
							{
								PX_XOR( "Thrown HE" ),
								PX_XOR( "Thrown Flash" ),
								PX_XOR( "Thrown Smoke" ),
								PX_XOR( "Thrown Decoy" ),
								PX_XOR( "Thrown Incendiary" )
							}
						};

						VerticalSpacing( );

						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH * 2 );

						TabbedCombobox( 30, PX_XOR( "Settings" ), dqTabs, dqItems, uEntity );
						EndRow( );
					}

					{
						BeginRow( 30, 7, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Enabled" ), &esdConfig._Entities[ uEntity ].bEnabled, PX_XOR( "Enable materials." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Enabled" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Material Visible" ), &esdConfig._Entities[ uEntity ].seqColor[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Material Invisible" ), &esdConfig._Entities[ uEntity ].seqColor[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Material Dormant" ), &esdConfig._Entities[ uEntity ].seqColor[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						BeginRow( 30, 9, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Flat" ), &esdConfig._Entities[ uEntity ].bFlat, PX_XOR( "Make materials flat." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Flat" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Draw Above All" ), &esdConfig._Entities[ uEntity ].bDrawAboveAll, PX_XOR( "Draw the material above all others." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Draw Above All" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Wireframe" ), &esdConfig._Entities[ uEntity ].bWireFrame, PX_XOR( "Render the material with a wireframe texture." ) );

						EndRow( );
					}

					EndGroupbox( );
				}
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
