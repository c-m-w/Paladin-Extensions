/// User Interface.cpp

#include "PX Precompiled.hpp"
#include "../PX CSGO.hpp"

using namespace PX::Information;
using namespace Pointers;
using namespace Modules;
using namespace PX::UI;
using namespace Widgets;
using namespace PX::Features;

constexpr int ITEM_DEFINITION_INDICIES[ ]
{
	ITEM_WEAPON_DEAGLE,
	ITEM_WEAPON_ELITE,
	ITEM_WEAPON_FIVESEVEN,
	ITEM_WEAPON_GLOCK,
	ITEM_WEAPON_P250,
	ITEM_WEAPON_TEC9,
	ITEM_WEAPON_CZ75AUTO,
	ITEM_WEAPON_R8REVOLVER,
	ITEM_WEAPON_P2000,
	ITEM_WEAPON_USPS,
	ITEM_WEAPON_MAC10,
	ITEM_WEAPON_MP7,
	ITEM_WEAPON_MP5SD,
	ITEM_WEAPON_UMP45,
	ITEM_WEAPON_PPBIZON,
	ITEM_WEAPON_P90,
	ITEM_WEAPON_MP9,
	ITEM_WEAPON_GALILAR,
	ITEM_WEAPON_AK47,
	ITEM_WEAPON_SG553,
	ITEM_WEAPON_FAMAS,
	ITEM_WEAPON_M4A1,
	ITEM_WEAPON_M4A1S,
	ITEM_WEAPON_AUG,
	ITEM_WEAPON_NOVA,
	ITEM_WEAPON_XM1014,
	ITEM_WEAPON_SAWEDOFF,
	ITEM_WEAPON_MAG7,
	ITEM_WEAPON_SSG08,
	ITEM_WEAPON_AWP,
	ITEM_WEAPON_SCAR20,
	ITEM_WEAPON_G3SG1,
	ITEM_WEAPON_NEGEV,
	ITEM_WEAPON_M249,
	ITEM_WEAPON_KNIFE_BAYONET,
	ITEM_WEAPON_KNIFE_FLIP,
	ITEM_WEAPON_KNIFE_GUT,
	ITEM_WEAPON_KNIFE_KARAMBIT,
	ITEM_WEAPON_KNIFE_M9_BAYONET,
	ITEM_WEAPON_KNIFE_TACTICAL,
	ITEM_WEAPON_KNIFE_FALCHION,
	ITEM_WEAPON_KNIFE_SURVIVAL_BOWIE,
	ITEM_WEAPON_KNIFE_BUTTERFLY,
	ITEM_WEAPON_KNIFE_SHADOW_DAGGERS,
	ITEM_WEAPON_KNIFE_URSUS,
	ITEM_WEAPON_KNIFE_NAVAJA,
	ITEM_WEAPON_KNIFE_STILLETTO,
	ITEM_WEAPON_KNIFE_TALON,
	ITEM_GLOVE_BLOODHOUND,
	ITEM_GLOVE_SPORTY,
	ITEM_GLOVE_DRIVER,
	ITEM_GLOVE_HAND_WRAP,
	ITEM_GLOVE_MOTO,
	ITEM_GLOVE_SPECIALIST,
	ITEM_GLOVE_HYDRA
};

namespace PX::UI::Manager
{
	namespace CSGO
	{
		PX_DEF uWindowWidth = 720u, uWindowHeight = 600u;

		void PX_API ChangeVisibility( )
		{
			static HWND *pOldWindowHandle = nullptr;
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
					&& InitializeUI( PX_XOR( "CSGO" ), false, uWindowWidth, uWindowHeight );
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

	static const auto fnSetValue = [ ]( int &iCurrentValue, const int iNewValue )
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
				"Statistics",
				"Glow",
				"Materials"
			},
			{
				"Trigger",
				"Aim",
				"Recoil Compensation"
			},
			{
				"Movement",
				"Visuals",
				"Inventory",
				"Other"
			},
			{
				"Global Configuration",
				"Other Configurations"
			}
		};

		static auto iCurrentTab = 0;
		static int iCurrentSubTab[ iTabCount ] { };
		const static std::function< void( PX_API)( int ) > fnTabCallbacks[ iTabCount ] { LayoutAwareness, LayoutCombat, LayoutMiscellaneous, LayoutSettings };

		SetMainWindowWidth( CSGO::uWindowWidth );
		SetMainWindowHeight( CSGO::uWindowHeight );
		Header( PX_XOR( "Paladin Extensions" ), szNuklearWindowTitle, 102, CSGO::ChangeVisibility, [ ]( )
		{
			exit( 0 );
		} );
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
			STATISTICS,
			GLOW,
			MATERIALS
		};

		switch ( iSubtab )
		{
			case STATISTICS:
			{
				SetMainWindowHeight( 750 );
				if ( BeginGroupbox( 200, 150, 500, 750, PX_XOR( "Team" ) ) )
				{
					auto &_Config = _Settings._Awareness._Statistics._Players[ SETTING_PLAYER_TEAM ];

					{
						VerticalSpacing( );

						BeginRow( 30, 13, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Enabled" ), &_Config.bEnabled );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Enabled" ), 30 ).x );
						Spacing( );
						Checkbox( PX_XOR( "Smoke Check" ), &_Config.bSmokeCheck );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Smoke Check" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Snaplines" ), &_Config.bSnapline );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Snaplines" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Snapline Visible" ), &_Config.seqSnapline[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Snapline Invisible" ), &_Config.seqSnapline[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Snapline Dormant" ), &_Config.seqSnapline[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						BeginRow( 30, 10, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Snapline Outline" ), &_Config.bSnaplineOutline );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Snapline Outline" ), 30 ).x - COLOR_BUTTON_PADDING * 2 - COLOR_BUTTON_WIDTH );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Snapline Outline" ), &_Config.seqSnaplineOutline, COLOR_BUTTON_VERTICAL_PADDING );


						Checkbox( PX_XOR( "Begin at Screen Top" ), &_Config.bSnaplineOrigin );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Begin at Screen Top" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "End at Box Top" ), &_Config.bSnaplineDestination );

						EndRow( );
					}

					{
						BeginRow( 30, 13, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Box" ), &_Config.bBox );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Box" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Bounding Box Visible" ), &_Config.seqBox[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Bounding Box Invisible" ), &_Config.seqBox[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Bounding Box Dormant" ), &_Config.seqBox[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Box Outline" ), &_Config.bBoxOutline );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Box Outline" ), 30 ).x - COLOR_BUTTON_PADDING * 2 - COLOR_BUTTON_WIDTH );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Bounding Box Outline" ), &_Config.seqBoxOutline, COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Three-Dimensional Box" ), &_Config.bDimesMode );

						EndRow( );
					}

					{
						BeginRow( 30, 13, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Worldly 2D Box" ), &_Config.bDisplayMode );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Worldly 2D Box" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Information" ), &_Config.bInformation );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Information" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Weapon" ), &_Config.bWeapon );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Weapon" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Weapon Information Visible" ), &_Config.seqWeapon[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Weapon Information Invisible" ), &_Config.seqWeapon[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Weapon Information Dormant" ), &_Config.seqWeapon[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						BeginRow( 30, 16, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Weapon Icon" ), &_Config.bWeaponIcon );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Weapon Icon" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Ammo" ), &_Config.bAmmo );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Ammo" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Ammo Information Visible" ), &_Config.seqAmmo[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Ammo Information Invisible" ), &_Config.seqAmmo[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Ammo Information Dormant" ), &_Config.seqAmmo[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Health" ), &_Config.bHealth );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Health" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Health Information Visible" ), &_Config.seqHealth[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Health Information Invisible" ), &_Config.seqHealth[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Health Information Dormant" ), &_Config.seqHealth[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						BeginRow( 30, 12, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Health-Based Health Color" ), &_Config.bHealthColoredByHealth );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Health-Based Health Color" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Armor" ), &_Config.bArmor );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Armor" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Armor Information Visible" ), &_Config.seqArmor[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Armor Information Invisible" ), &_Config.seqArmor[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Armor Information Dormant" ), &_Config.seqArmor[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Armor Icon" ), &_Config.bArmorIcon );

						EndRow( );
					}

					{
						BeginRow( 30, 12, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Armor-Based Armor Color" ), &_Config.bArmorColoredByArmor );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Armor-Based Armor Color" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Damage Indication" ), &_Config.bDamageIndication );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Damage Indication"), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Damage Indication Visible" ), &_Config.seqDamageIndication[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Damage Indication Invisible" ), &_Config.seqDamageIndication[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Damage Indication Dormant" ), &_Config.seqDamageIndication[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Damage-Based Damage Indication Color" ), &_Config.bDamageIndicationColoredByDamage );

						EndRow( );
					}

					{
						BeginRow( 30, 13, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Bone" ), &_Config.bDamageIndication );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Bone" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Bone Visible" ), &_Config.seqBone[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Bone Invisible" ), &_Config.seqBone[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Bone Dormant" ), &_Config.seqBone[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Bone Outline" ), &_Config.bBoneOutline );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Bone Outline" ), 30 ).x - COLOR_BUTTON_PADDING * 2 - COLOR_BUTTON_WIDTH );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Bone Outline" ), &_Config.seqBoneOutline, COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Health-Based Bone Color" ), &_Config.bBoneColoredByHealth );

						EndRow( );
					}

					{
						std::deque< const char* > dqAlignment
						{
							PX_XOR( "Left" ),
							PX_XOR( "Right" ),
							PX_XOR( "Top" ),
							PX_XOR( "Bottom" ),
							PX_XOR( "Smart" )
						};

						BeginRow( 30, 12, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Orientation" ), &_Config.bOrientation );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Orientation" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Orientation Visible" ), &_Config.seqOrientation[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Orientation Invisible" ), &_Config.seqOrientation[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Orientation Dormant" ), &_Config.seqOrientation[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Orientation Outline" ), &_Config.bOrientationOutline );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Orientation Outline" ), 30 ).x - COLOR_BUTTON_PADDING * 2 - COLOR_BUTTON_WIDTH );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Orientation Outline" ), &_Config.seqOrientationOutline, COLOR_BUTTON_VERTICAL_PADDING );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						const auto iReturn = Combobox( 30, PX_XOR( "Alignment" ), dqAlignment, _Config.fAlignment );
						if ( iReturn >= 0 )
							_Config.fAlignment = iReturn;

						EndRow( );
					}

					{
						BeginRow( 30, 6, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Identifier" ), &_Config.bIdentifier );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Identifier" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Distance" ), &_Config.bDistance );

						EndRow( );
					}

					{
						static char szSnaplineThickness[ 32 ] { },
							szSnaplineOutlineThickness[ 32 ] { },
							szBoxThickness[ 32 ] { };

						BeginRow( 30, 9, ROW_CUSTOM );

						_Config.flSnaplineThickness = Slider( PX_XOR( "Snapline Thickness" ), szSnaplineThickness, 1.f, 5.f, _Config.flSnaplineThickness, 10, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						_Config.flSnaplineOutlineThickness = Slider( PX_XOR( "Snapline Outline Thickness" ), szSnaplineOutlineThickness, 1.f, 5.f, _Config.flSnaplineOutlineThickness, GROUPBOX_COLUMN_WIDTH + 30, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						_Config.flBoxThickness = Slider( PX_XOR( "Box Thickness" ), szBoxThickness, 1.f, 5.f, _Config.flBoxThickness, GROUPBOX_COLUMN_WIDTH * 2 + 40, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						EndRow( );
					}

					{
						static char szBoxOutlineThickness[ 32 ] { },
							szBoxCornerLength[ 32 ] { },
							szBoneThickness[ 32 ] { };

						BeginRow( 30, 9, ROW_CUSTOM );

						_Config.flBoxOutlineThickness = Slider( PX_XOR( "Box Outline Thickness" ), szBoxOutlineThickness, 1.f, 5.f, _Config.flBoxOutlineThickness, 10, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						_Config.flBoxCornerLength = Slider( PX_XOR( "Box Corner Length" ), szBoxCornerLength, 1.f, 5.f, _Config.flBoxCornerLength, GROUPBOX_COLUMN_WIDTH + 30, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						_Config.flBoneThickness = Slider( PX_XOR( "Bone Thickness" ), szBoneThickness, 1.f, 5.f, _Config.flBoneThickness, GROUPBOX_COLUMN_WIDTH * 2 + 40, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						EndRow( );
					}

					{
						static char szBoneOutlineThickness[ 32 ] { },
							szOrientationThickness[ 32 ] { },
							szOrientationOutlineThickness[ 32 ] { };

						BeginRow( 30, 9, ROW_CUSTOM );

						_Config.flBoneOutlineThickness = Slider( PX_XOR( "Bone Outline Thickness" ), szBoneOutlineThickness, 1.f, 5.f, _Config.flBoneOutlineThickness, 10, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						_Config.flOrientationThickness = Slider( PX_XOR( "Orientation Thickness" ), szOrientationThickness, 1.f, 5.f, _Config.flOrientationThickness, GROUPBOX_COLUMN_WIDTH + 30, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						_Config.flOrientationOutlineThickness = Slider( PX_XOR( "Orientation Outline Thickness" ), szOrientationOutlineThickness, 1.f, 5.f, _Config.flOrientationOutlineThickness, GROUPBOX_COLUMN_WIDTH * 2 + 40, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						EndRow( );
					}

					EndGroupbox( );
				}
			}
			break;

			case GLOW:
			{
				auto &esdConfig = _Settings._Awareness._Glow;
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

				if ( BeginGroupbox( 400, 315, 500, 220, PX_XOR( "Entities" ) ) )
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
								PX_XOR( "Defuse Kit" ),
								PX_XOR( "Chicken" )
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
				auto &esdConfig = _Settings._Awareness._Materials;

				if ( BeginGroupbox( 200, 150, 500, 220, PX_XOR( "Entities" ) ) )
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
								PX_XOR( "Enemies" ),
								PX_XOR( "Team Corpse" ),
								PX_XOR( "Enemy Corpse" ),
								PX_XOR( "Chicken" )
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
						BeginRow( 30, 3, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Wireframe" ), &esdConfig._Entities[ uEntity ].bWireFrame, PX_XOR( "Render the material with a wireframe texture." ) );

						EndRow( );
					}

					{
						BeginRow( 30, 13, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Wireframe Overlay" ), &esdConfig._Entities[ uEntity ].bWireFrameOverlay, PX_XOR( "Render a wireframe material overtop of the entity." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH * 3.f / 2.f - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Wireframe Overlay" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Wireframe Overlay Visible" ), &esdConfig._Entities[ uEntity ].seqWireFrameOverlay[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Wireframe Overlay Invisible" ), &esdConfig._Entities[ uEntity ].seqWireFrameOverlay[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Wireframe Overlay Dormant" ), &esdConfig._Entities[ uEntity ].seqWireFrameOverlay[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Wireframe Underlay" ), &esdConfig._Entities[ uEntity ].bWireFrameUnderlay, PX_XOR( "Render a wireframe material under the entity, creating an outline effect." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH * 3.f / 2.f - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Wireframe Underlay" ), 30 ).x - COLOR_BUTTON_PADDING * 6 - COLOR_BUTTON_WIDTH * 3 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Wireframe Overlay Visible" ), &esdConfig._Entities[ uEntity ].seqWireFrameUnderlay[ STATE_VISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Wireframe Overlay Invisible" ), &esdConfig._Entities[ uEntity ].seqWireFrameUnderlay[ STATE_INVISIBLE ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Wireframe Overlay Dormant" ), &esdConfig._Entities[ uEntity ].seqWireFrameUnderlay[ STATE_DORMANT ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						std::deque< cstr_t > dqMaterials
						{
							PX_XOR( "Default" ),
							PX_XOR( "Ignore Walls" ),
							PX_XOR( "Flat" ),
							PX_XOR( "Flat Ignore Walls" ),
							PX_XOR( "Reflective" ),
							PX_XOR( "Glow" ),
							PX_XOR( "Glass" ),
							PX_XOR( "Crystal" ),
							PX_XOR( "Gold" )
						};

						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( esdConfig._Entities[ uEntity ].iMaterial, Combobox( 30, PX_XOR( "Material" ), dqMaterials, esdConfig._Entities[ uEntity ].iMaterial ) );

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
			TRIGGER,
			AIM,
			RECOIL
		};

		std::deque< cstr_t > dqWeapons[ WEAPONTYPE_MACHINEGUN + 1 ]
		{
			{ // WEAPONTYPE_PISTOL
				PX_XOR( "Deagle" ),
				PX_XOR( "Elites" ),
				PX_XOR( "FiveSeveN" ),
				PX_XOR( "Glock" ),
				PX_XOR( "P250" ),
				PX_XOR( "Tec-9" ),
				PX_XOR( "CZ75-Auto" ),
				PX_XOR( "R8 Revolver" ),
				PX_XOR( "P2000" ),
				PX_XOR( "USP-S" )
			},
			{ // WEAPONTYPE_SUBMACHINEGUN
				PX_XOR( "MAC-10" ),
				PX_XOR( "MP7" ),
				PX_XOR( "MP5-SD" ),
				PX_XOR( "UMP-45" ),
				PX_XOR( "PP-Bizon" ),
				PX_XOR( "P90" ),
				PX_XOR( "MP9" )
			},
			{ // WEAPONTYPE_RIFLE
				PX_XOR( "Galil AR" ),
				PX_XOR( "AK47" ),
				PX_XOR( "SG 553" ),
				PX_XOR( "FAMAS" ),
				PX_XOR( "M4A4" ),
				PX_XOR( "M4A1-S" ),
				PX_XOR( "AUG" )
			},
			{ // WEAPONTYPE_SHOTGUN
				PX_XOR( "Nova" ),
				PX_XOR( "XM1014" ),
				PX_XOR( "Sawed-Off" ),
				PX_XOR( "MAG-7" )
			},
			{ // WEAPONTYPE_SNIPER_RIFLE
				PX_XOR( "SSG-08" ),
				PX_XOR( "AWP" ),
				PX_XOR( "SCAR-20" ),
				PX_XOR( "G3SG1" )
			},
			{ // WEAPONTYPE_MACHINEGUN
				PX_XOR( "Negev" ),
				PX_XOR( "M249" )
			}
		};

		std::deque< cstr_t > dqTypes
		{
			nullptr,
			PX_XOR( "Pistols" ),
			PX_XOR( "SMGs" ),
			PX_XOR( "Rifles" ),
			PX_XOR( "Shotguns" ),
			PX_XOR( "Snipers" ),
			PX_XOR( "Heavy" )
		};

		std::deque< cstr_t > dqComboboxHeaderTypes
		{
			PX_XOR( "Pistols" ),
			PX_XOR( "SMGs" ),
			PX_XOR( "Rifles" ),
			PX_XOR( "Shotguns" ),
			PX_XOR( "Snipers" ),
			PX_XOR( "Heavy" )
		};

		switch ( iSubtab )
		{
			case TRIGGER:
			{
				const auto fnDrawTriggerOptions = [ ]( settings_t::combat_t::trigger_t::weapon_t *pConfig, char *szHitchance, char *szRays )
				{
					{
						BeginRow( 30, 9, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Teammates" ), &pConfig->bTeammates, PX_XOR( "Fire at teammates." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Teammates" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Enemies" ), &pConfig->bEnemies, PX_XOR( "Fire at enemies." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Enemies" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Mind Smoke" ), &pConfig->bMindSmoke, PX_XOR( "Don't shoot through the smoke." ) );

						EndRow( );
					}

					{
						std::deque< cstr_t > dqHitgroupText
						{
							nullptr,
							PX_XOR( "Head" ),
							PX_XOR( "Upper Body" ),
							PX_XOR( "Lower Body" ),
							PX_XOR( "Left Arm" ),
							PX_XOR( "Right Arm" ),
							PX_XOR( "Left Leg" ),
							PX_XOR( "Right Leg" )
						};
						std::deque< bool* > dqHitgroups;

						for ( auto &hitgroup: pConfig->bHitGroups )
							dqHitgroups.emplace_back( &hitgroup.Get( ) );

						BeginRow( 30, 7, ROW_CUSTOM );

						PushCustomRow( 10, 0, GROUPBOX_COLUMN_WIDTH, 30 );
						ComboboxMulti( 30, PX_XOR( "Hitgroups" ), dqHitgroupText, dqHitgroups );

						pConfig->flHitChance = Slider( PX_XOR( "Hitchance" ), szHitchance, 0.00f, 1.00f, pConfig->flHitChance, GROUPBOX_COLUMN_WIDTH + 30, 10, GROUPBOX_COLUMN_WIDTH, 30, 2 );

						pConfig->iRays = Slider( PX_XOR( "Rays" ), szRays, 100, 255, pConfig->iRays, GROUPBOX_COLUMN_WIDTH * 2 + 40, 10, GROUPBOX_COLUMN_WIDTH, 30 );

						EndRow( );
					}
				};

				if ( BeginGroupbox( 200, 150, 500, 113, PX_XOR( "Global Configuration" ) ) )
				{
					static char szHitchance[ 32 ] { }, szRays[ 32 ] { };
					{
						fnDrawTriggerOptions( &_Settings._Combat._Trigger._All, szHitchance, szRays );
					}

					EndGroupbox( );
				}

				if ( BeginGroupbox( 400, 206, 500, 158, PX_XOR( "Group Configurations" ) ) )
				{
					static char szHitchance[ 32 ] { }, szRays[ 32 ] { };
					static int iWeaponGroup = WEAPONTYPE_PISTOL;
					{
						VerticalSpacing( );

						BeginRow( 30, 5, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( iWeaponGroup, Combobox( 30, PX_XOR( "Group" ), dqTypes, iWeaponGroup ) );

						SetRowWidth( -1.f );
						Spacing( );

						Checkbox( PX_XOR( "Use Group Configuration" ), &_Settings._Combat._Trigger._WeaponTypes[ iWeaponGroup ].bUseSeparate, PX_XOR( "Use the weapon group rather than the global setting." ) );

						EndRow( );
					}

					{
						fnDrawTriggerOptions( &_Settings._Combat._Trigger._WeaponTypes[ iWeaponGroup ], szHitchance, szRays );
					}

					EndGroupbox( );
				}

				if ( BeginGroupbox( 400, 350, 500, 190, PX_XOR( "Weapon Configurations" ) ) )
				{
					static char szHitchance[ 32 ] { }, szRays[ 32 ] { };
					static auto uCurrentWeapon = 0u;

					{
						VerticalSpacing( );

						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH * 3.f + 29.f );
						TabbedCombobox( 30, PX_XOR( "Weapons" ), dqComboboxHeaderTypes, dqWeapons, uCurrentWeapon );

						EndRow( );
					}

					{
						BeginRow( 30, 3, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Use Weapon Configuration" ), &_Settings._Combat._Trigger._IndividualWeapons[ ITEM_DEFINITION_INDICIES[ uCurrentWeapon ] ].bUseSeparate, PX_XOR( "Use the weapon's configuration rather than the group or global configuration." ) );

						EndRow( );
					}

					{
						fnDrawTriggerOptions( &_Settings._Combat._Trigger._IndividualWeapons[ ITEM_DEFINITION_INDICIES[ uCurrentWeapon ] ], szHitchance, szRays );
					}

					EndGroupbox( );
				}
			}
			break;

			case AIM:
			{
				SetMainWindowHeight( 687u );
				SetMainWindowWidth( 1231u );
				const auto fnDrawAimOptions = [ ]( settings_t::combat_t::aim_t::weapon_t *pConfig, char *szSmoothFactor, char *szCrosshairDistance, char *szBisection, char *szDistance, char *szOverCompensation )
				{
					{
						BeginRow( 30, 9, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Teammates" ), &pConfig->bTeammates, PX_XOR( "Fire at teammates." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Teammates" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Enemies" ), &pConfig->bEnemies, PX_XOR( "Fire at enemies." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Enemies" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Mind Smoke" ), &pConfig->bMindSmoke, PX_XOR( "Don't aim through the smoke." ) );

						EndRow( );
					}

					{
						static auto uCurrentTab = 0u;
						std::deque< cstr_t > dqHitboxTabs
						{
							PX_XOR( "Torso" ),
							PX_XOR( "Legs" ),
							PX_XOR( "Arms" )
						};
						std::deque< cstr_t > dqHitboxText[ ]
						{
							{
								PX_XOR( "Head" ),
								PX_XOR( "Neck" ),
								PX_XOR( "Pelvis" ),
								PX_XOR( "Stomach" ),
								PX_XOR( "Lower Chest" ),
								PX_XOR( "Chest" ),
								PX_XOR( "Upper Chest" )
							},
							{
								PX_XOR( "Right Thigh" ),
								PX_XOR( "Left Thigh" ),
								PX_XOR( "Right Calf" ),
								PX_XOR( "Left Calf" ),
								PX_XOR( "Right Foot" ),
								PX_XOR( "Left Foot" )
							},
							{
								PX_XOR( "Right Hand" ),
								PX_XOR( "Left Hand" ),
								PX_XOR( "Right Upper Arm" ),
								PX_XOR( "Right Forearm" ),
								PX_XOR( "Left Upper Arm" ),
								PX_XOR( "Left Forearm" )
							}
						};
						std::deque< bool* > dqHitboxes;

						for ( auto &hitgroup: pConfig->bHitboxes )
							dqHitboxes.emplace_back( &hitgroup.Get( ) );

						std::deque< cstr_t > dqAimTypes
						{
							PX_XOR( "Default" ),
							PX_XOR( "Smooth" ),
							PX_XOR( "Silent" )
						};

						std::deque< cstr_t > dqSmoothType
						{
							PX_XOR( "Linear" ),
							PX_XOR( "Parabolic" ),
							PX_XOR( "Radical" ),
							PX_XOR( "Sinusoidal" ),
							PX_XOR( "Bezier" ),
							PX_XOR( "Randomize" )
						};

						BeginRow( 30, 6, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						TabbedComboboxMulti( 30, PX_XOR( "Hitboxes" ), dqHitboxTabs, dqHitboxText, dqHitboxes, uCurrentTab );

						SetRowWidth( 5 );
						Spacing( );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( pConfig->iAimType, Combobox( 30, PX_XOR( "Aim Type" ), dqAimTypes, pConfig->iAimType ) );

						SetRowWidth( 5 );
						Spacing( );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( pConfig->iSmoothMode, Combobox( 30, PX_XOR( "Smooth Mode" ), dqSmoothType, pConfig->iSmoothMode ) );

						EndRow( );
					}

					{
						std::deque< cstr_t > dqTargetingModes
						{
							PX_XOR( "Distance" ),
							PX_XOR( "Crosshair Distance" ),
							PX_XOR( "Health" )
						};

						BeginRow( 30, 8, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( pConfig->iTargeting, Combobox( 30, PX_XOR( "Targeting" ), dqTargetingModes, pConfig->iTargeting ) );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Static Target" ), &pConfig->bStaticTarget, PX_XOR( "Keep the same target until aimbot is re-activated." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CalculateTextBounds( PX_XOR( "Static Target" ), 30 ).x - CHECKBOX_ICON_WIDTH );
						Spacing( );

						Checkbox( PX_XOR( "Validate Target" ), &pConfig->bValidateTarget, PX_XOR( "Ensure the target is within valid activation parameters after selection. Only applies when Static Target is enabled." ) );
					}

					{
						BeginRow( 30, 9, ROW_CUSTOM );

						pConfig->flAimTime = Slider( PX_XOR( "Aim Time" ), szSmoothFactor, 0.01f, 1.50f, pConfig->flAimTime, 10, 10, GROUPBOX_COLUMN_WIDTH, 30, 2 );

						pConfig->flAimAcceleration = Slider( PX_XOR( "Acceleration Factor" ), szSmoothFactor, -0.99f, 0.99f, pConfig->flAimAcceleration, GROUPBOX_COLUMN_WIDTH + 30, 10, GROUPBOX_COLUMN_WIDTH, 30, 2 );

						pConfig->flMaxCrosshairDistance = Slider( PX_XOR( "Max Distance" ), szCrosshairDistance, 0.f, 254.558441227f, pConfig->flMaxCrosshairDistance, GROUPBOX_COLUMN_WIDTH * 2 + 40, 10, GROUPBOX_COLUMN_WIDTH, 30, 2 );

						EndRow( );
					}

					{
						BeginRow( 30, 3, ROW_CUSTOM );

						pConfig->flOverCompensation = Slider( PX_XOR( "Over Compensation" ), szOverCompensation, 0.f, 5.f, pConfig->flOverCompensation, 10, 10, GROUPBOX_COLUMN_WIDTH, 30, 2 );

						EndRow( );
					}

					{
						cstr_t pStrings[ 7 ] { "1", "2", "3", "4", "5", "6", "7" };

						static auto iSelectedOrder = 0;
						std::deque< cstr_t > dqOrders;
						for ( auto i = 0; i <= pConfig->iCurrentOrders; i++ )
							dqOrders.emplace_back( pStrings[ i ] );

						BeginRow( 30, 7, ROW_CUSTOM );

						PushCustomRow( 10, 5, GROUPBOX_COLUMN_WIDTH, 30 );
						fnSetValue( iSelectedOrder, IncrementalCombobox( 30, PX_XOR( "Bezier Orders" ), dqOrders, pConfig->iCurrentOrders, 7, iSelectedOrder ) );
						auto &pCurrentOrder = pConfig->_BezierOrders[ iSelectedOrder ];

						pCurrentOrder.flBisectionPoint = Slider( PX_XOR( "Bisection Point" ), szBisection, 0.01f, 1.50f, pCurrentOrder.flBisectionPoint, GROUPBOX_COLUMN_WIDTH + 30, 5, GROUPBOX_COLUMN_WIDTH, 30, 2 );

						pCurrentOrder.flDistance = Slider( PX_XOR( "Distance" ), szDistance, -1.50f, 1.50f, pCurrentOrder.flDistance, GROUPBOX_COLUMN_WIDTH * 2 + 40, 5, GROUPBOX_COLUMN_WIDTH, 30, 2 );

						EndRow( );
					}
				};

				static auto uCurrentWeapon = 0u;
				static int iWeaponGroup = WEAPONTYPE_PISTOL;

				if ( BeginGroupbox( 200, 150, 500, 250, PX_XOR( "Global Configuration" ) ) )
				{
					static char szSmooth[ 32 ] { }, szCrosshairDistance[ 32 ] { }, szBisect[ 32 ] { }, szDistance[ 32 ] { }, szOverCompensation[ 32 ] { };
					{
						fnDrawAimOptions( &_Settings._Combat._Aim._All, szSmooth, szCrosshairDistance, szBisect, szDistance, szOverCompensation );
					}

					EndGroupbox( );
				}

				if ( BeginGroupbox( 400, 343, 500, 290, PX_XOR( "Group Configurations" ) ) )
				{
					static char szSmooth[ 32 ] { }, szCrosshairDistance[ 32 ] { }, szBisect[ 32 ] { }, szDistance[ 32 ] { }, szOverCompensation[ 32 ] { };
					{
						VerticalSpacing( );

						BeginRow( 30, 5, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( iWeaponGroup, Combobox( 30, PX_XOR( "Group" ), dqTypes, iWeaponGroup ) );

						SetRowWidth( -1.f );
						Spacing( );

						Checkbox( PX_XOR( "Use Group Configuration" ), &_Settings._Combat._Aim._WeaponTypes[ iWeaponGroup ].bUseSeparate, PX_XOR( "Use the weapon group rather than the global setting." ) );

						EndRow( );
					}

					{
						fnDrawAimOptions( &_Settings._Combat._Aim._WeaponTypes[ iWeaponGroup ], szSmooth, szCrosshairDistance, szBisect, szDistance, szOverCompensation );
					}

					EndGroupbox( );
				}

				if ( BeginGroupbox( 914, 88, 500, 320, PX_XOR( "Weapon Configurations" ) ) )
				{
					static char szSmooth[ 32 ] { }, szCrosshairDistance[ 32 ] { }, szBisect[ 32 ] { }, szDistance[ 32 ] { }, szOverCompensation[ 32 ] { };
					{
						VerticalSpacing( );

						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH * 3.f + 29.f );
						TabbedCombobox( 30, PX_XOR( "Weapons" ), dqComboboxHeaderTypes, dqWeapons, uCurrentWeapon );

						EndRow( );
					}

					{
						BeginRow( 30, 3, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Use Weapon Configuration" ), &_Settings._Combat._Aim._IndividualWeapons[ ITEM_DEFINITION_INDICIES[ uCurrentWeapon ] ].bUseSeparate, PX_XOR( "Use the weapon's configuration rather than the group or global configuration." ) );

						EndRow( );
					}

					{
						fnDrawAimOptions( &_Settings._Combat._Aim._IndividualWeapons[ ITEM_DEFINITION_INDICIES[ uCurrentWeapon ] ], szSmooth, szCrosshairDistance, szBisect, szDistance, szOverCompensation );
					}

					EndGroupbox( );
				}

				if ( BeginGroupbox( 1427, -137, 500, 192, PX_XOR( "Aim Path Preview" ) ) )
				{
					static auto iConfig = 0;
					{
						std::deque< cstr_t > dqConfigs
						{
							PX_XOR( "Global" ),
							PX_XOR( "Selected Group" ),
							PX_XOR( "Selected Weapon" )
						};

						VerticalSpacing( );

						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( iConfig, Combobox( 30, PX_XOR( "Configuration" ), dqConfigs, iConfig ) );

						EndRow( );
					}

					{
						const auto pConfig = iConfig == 0 ? &_Settings._Combat._Aim._All : iConfig == 1 ? &_Settings._Combat._Aim._WeaponTypes[ iWeaponGroup ] : &_Settings._Combat._Aim._IndividualWeapons[ ITEM_DEFINITION_INDICIES[ uCurrentWeapon ] ];
						static struct nk_vec2 vecDots[ ] { { 0.f, 0.f }, { 200.f, 130.f } };
						static auto flRatio = 0.f, flWaitTime = 0.f;
						static auto bDoneWaiting = false;
						static auto i = -1;
						static std::vector< struct nk_vec2 > vecLinePoints { };
						struct nk_vec2 vecDistance = { vecDots[ 0 ].x - vecDots[ 1 ].x, vecDots[ 0 ].y - vecDots[ 1 ].y };

						if ( pConfig->iAimType == AIMTYPE_DEFAULT || pConfig->iAimType == AIMTYPE_SILENT )
						{
							vecLinePoints.clear( );
							vecLinePoints.emplace_back( vecDots[ 0 ] );
							vecLinePoints.emplace_back( vecDots[ 1 ] );
						}
						else
						{
							if ( flRatio == 1.f )
							{
								if ( bDoneWaiting )
								{
									bDoneWaiting = false;
									flWaitTime = pGlobalVariables->m_flCurrentTime + 1.f;
								}
								else if ( pGlobalVariables->m_flCurrentTime > flWaitTime )
								{
									bDoneWaiting = true;
									flRatio = 0.f;
									vecLinePoints.clear( );
								}
							}
							else
							{
								//flRatio += fabsf( pConfig->flSmoothFactor -
								//	( settings_t::combat_t::SMOOTHING_MAX + settings_t::combat_t::SMOOTHING_MIN ) ) / ( settings_t::combat_t::SMOOTHING_MAX * 5.f );
								flRatio = std::clamp( flRatio, 0.f, 1.f );
							}

							const struct nk_vec2 vecDefaultSmoothed { vecDots[ 0 ].x - vecDistance.x * flRatio, vecDots[ 0 ].y - vecDistance.y * flRatio };

							switch ( pConfig->iSmoothMode )
							{
								case SMOOTH_LINEAR:
								{
									vecLinePoints.emplace_back( vecDefaultSmoothed );
								}
								break;

								case SMOOTH_PARABOLIC:
								{
									const auto flTemp = ( vecDots[ 1 ].y - vecDots[ 0 ].y ) / pow( vecDots[ 1 ].x - vecDots[ 0 ].x, 2.f );
									const struct nk_vec2 vecNew = { vecDefaultSmoothed.x, flTemp * pow( vecDefaultSmoothed.x - vecDots[ 0 ].x, 2.f ) + vecDots[ 0 ].y };
									vecLinePoints.emplace_back( vecNew );
								}
								break;

								case SMOOTH_RADICAL:
								{
									const auto flTemp = ( vecDots[ 1 ].y - vecDots[ 0 ].y ) / cbrtf( vecDots[ 1 ].x - vecDots[ 0 ].x );
									const struct nk_vec2 vecNew = { vecDefaultSmoothed.x, flTemp * cbrtf( vecDefaultSmoothed.x - vecDots[ 0 ].x ) + vecDots[ 0 ].y };
									vecLinePoints.emplace_back( vecNew );
								}
								break;

								case SMOOTH_SINUSOIDAL:
								{
									const auto fl = D3DX_PI / 2.f / ( vecDots[ 0 ].x - vecDots[ 1 ].x );
									const auto flTemp = ( vecDots[ 1 ].y - vecDots[ 0 ].y ) / sinf( fl * ( vecDots[ 1 ].x - vecDots[ 0 ].x ) );
									const struct nk_vec2 vecNew = { vecDefaultSmoothed.x, flTemp * sinf( fl * ( vecDefaultSmoothed.x - vecDots[ 0 ].x ) ) + vecDots[ 0 ].y };
									vecLinePoints.emplace_back( vecNew );
								}
								break;

								case SMOOTH_BEZIER:
								{
									const auto vecBezierPoints = Tools::GetBezierPoints( D3DXVECTOR2( vecDots[ 0 ].x, vecDots[ 0 ].y ), D3DXVECTOR2( vecDots[ 1 ].x, vecDots[ 1 ].y ), pConfig->_BezierOrders, pConfig->iCurrentOrders + 1 );
									const auto vecPoint = Tools::GetBezierPoint( vecBezierPoints, flRatio );
									const struct nk_vec2 vecNew = { vecPoint.x, vecPoint.y };
									vecLinePoints.emplace_back( vecNew );
								}
								break;

								default:
									break;
							}
						}

						const auto recMainWindow = GetActiveWindowBounds( );
						Graph( recMainWindow.x + 900.f, recMainWindow.y + 490.f, 300.f, 150, 10, 5, &vecLinePoints[ 0 ], vecLinePoints.size( ), vecDots, 2u, i );
					}
					EndGroupbox( );
				}
			}
			break;

			case RECOIL:
			{
				const auto fnDrawRecoilOption = [ ]( settings_t::combat_t::recoil_compensation_t::weapon_t *pConfig, char *szCompensationAmount, char *szSmoothness, char *szStartBullet )
				{
					{
						BeginRow( 30, 9, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Enabled" ), &pConfig->bEnabled, PX_XOR( "Enable compensating for recoil." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CalculateTextBounds( PX_XOR( "Enabled" ), 30 ).x - CHECKBOX_ICON_WIDTH );
						Spacing( );

						Checkbox( PX_XOR( "Standalone" ), &pConfig->bStandalone, PX_XOR( "Compensate for recoil without aimbot. Disable if aimbot is enabled or they will conflict." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CalculateTextBounds( PX_XOR( "Standalone" ), 30 ).x - CHECKBOX_ICON_WIDTH );
						Spacing( );

						Checkbox( PX_XOR( "Only When Shooting" ), &pConfig->bNoRefractoryCompensation, PX_XOR( "Only compensate for recoil while shooting. This will not bring your cursor back to the original position after compensating for recoil has finished." ) );

						EndRow( );
					}

					{
						BeginRow( 30, 9, ROW_CUSTOM );

						pConfig->flCompensationAmount = Slider( PX_XOR( "Compensation Amount" ), szCompensationAmount, 0.f, 1.5f, pConfig->flCompensationAmount, 10, 10, GROUPBOX_COLUMN_WIDTH, 30, 2 );

						pConfig->flSmoothness = Slider( PX_XOR( "Smoothness" ), szCompensationAmount, 0.f, 1.f, pConfig->flSmoothness, 175, 10, GROUPBOX_COLUMN_WIDTH, 30, 3 );

						pConfig->iStartBullet = Slider( PX_XOR( "Start Compensation at Shot" ), szCompensationAmount, 0, 150, pConfig->iStartBullet, 350, 10, GROUPBOX_COLUMN_WIDTH, 30 );

						EndRow( );
					}
				};

				if ( BeginGroupbox( 200, 150, 500, 220, PX_XOR( "Global Configuration" ) ) )
				{
					static char szCompensationAmount[ 32 ] { }, szSmoothness[ 32 ] { }, szStartBullet[ 32 ] { };
					{
						fnDrawRecoilOption( &_Settings._Combat._RecoilCompensation._All, szCompensationAmount, szSmoothness, szStartBullet );
					}
					EndGroupbox( );
				}
			}
			break;

			default:
				break;
		}
	}

	void PX_API LayoutMiscellaneous( int iSubtab )
	{
		enum
		{
			MOVEMENT,
			VISUALS,
			INVENTORY,
			OTHER
		};

		std::deque< cstr_t > dqCategories
		{
			PX_XOR( "Pistols" ),
			PX_XOR( "SMG" ),
			PX_XOR( "Rifle" ),
			PX_XOR( "Shotty" ),
			PX_XOR( "Sniper" ),
			PX_XOR( "Heavy" ),
			PX_XOR( "Knives" ),
			PX_XOR( "Knives [2]" ),
			PX_XOR( "Gloves" )
		};

		std::deque< cstr_t > dqWeapons[ ]
		{
			{ // WEAPONTYPE_PISTOL
				PX_XOR( "Deagle" ),
				PX_XOR( "Elites" ),
				PX_XOR( "FiveSeveN" ),
				PX_XOR( "Glock" ),
				PX_XOR( "P250" ),
				PX_XOR( "Tec-9" ),
				PX_XOR( "CZ75-Auto" ),
				PX_XOR( "R8 Revolver" ),
				PX_XOR( "P2000" ),
				PX_XOR( "USP-S" )
			},
			{ // WEAPONTYPE_SUBMACHINEGUN
				PX_XOR( "MAC-10" ),
				PX_XOR( "MP7" ),
				PX_XOR( "MP5-SD" ),
				PX_XOR( "UMP-45" ),
				PX_XOR( "PP-Bizon" ),
				PX_XOR( "P90" ),
				PX_XOR( "MP9" )
			},
			{ // WEAPONTYPE_RIFLE
				PX_XOR( "Galil AR" ),
				PX_XOR( "AK47" ),
				PX_XOR( "SG 553" ),
				PX_XOR( "FAMAS" ),
				PX_XOR( "M4A4" ),
				PX_XOR( "M4A1-S" ),
				PX_XOR( "AUG" )
			},
			{ // WEAPONTYPE_SHOTGUN
				PX_XOR( "Nova" ),
				PX_XOR( "XM1014" ),
				PX_XOR( "Sawed-Off" ),
				PX_XOR( "MAG-7" )
			},
			{ // WEAPONTYPE_SNIPER_RIFLE
				PX_XOR( "SSG-08" ),
				PX_XOR( "AWP" ),
				PX_XOR( "SCAR-20" ),
				PX_XOR( "G3SG1" )
			},
			{ // WEAPONTYPE_MACHINEGUN
				PX_XOR( "Negev" ),
				PX_XOR( "M249" )
			},
			{ // knives 
				PX_XOR( "Bayonet" ),
				PX_XOR( "Flip" ),
				PX_XOR( "Gut" ),
				PX_XOR( "Karambit" ),
				PX_XOR( "M9 Bayonet" ),
				PX_XOR( "Huntsman" ),
				PX_XOR( "Falchion" ),
				PX_XOR( "Bowie" ),
				PX_XOR( "Butterfly" ),
				PX_XOR( "Shadow Daggers" )
			},
			{ // knives cont'd
				PX_XOR( "Ursus" ),
				PX_XOR( "Navaja" ),
				PX_XOR( "Stilletto" ),
				PX_XOR( "Talon" )
			},
			{ // gloves
				PX_XOR( "Bloodhound" ),
				PX_XOR( "Sport" ),
				PX_XOR( "Driver" ),
				PX_XOR( "Hand Wrap" ),
				PX_XOR( "Moto" ),
				PX_XOR( "Specialist" ),
				PX_XOR( "Hydra" )
			}
		};

		switch ( iSubtab )
		{
			case MOVEMENT:
			{
				if ( BeginGroupbox( 200, 150, 500, 220, PX_XOR( "Movement" ) ) )
				{
					static char szMissChance[ 32 ] { };

					{
						BeginRow( 30, 9, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Auto Jump" ), &_Settings._Miscellaneous._Movement.bAutomaticJump, PX_XOR( "Automatically jump." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Auto Jump" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Edge Jump" ), &_Settings._Miscellaneous._Movement.bEdgeJump, PX_XOR( "Automatically jump when at the edge of a platform." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Edge Jump" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Circle Strafe" ), &_Settings._Miscellaneous._Movement.bCircleStrafe );

						EndRow( );
					}

					{
						BeginRow( 30, 3, ROW_CUSTOM );

						_Settings._Miscellaneous._Movement.iMissTicks = Slider( PX_XOR( "Jump Miss Chance" ), szMissChance, 0, 15, _Settings._Miscellaneous._Movement.iMissTicks, 10, 10, GROUPBOX_COLUMN_WIDTH, 30 );

						EndRow( );
					}

					EndGroupbox( );
				}
			}
			break;

			case VISUALS:
			{
				if ( BeginGroupbox( 200, 150, 500, 250, PX_XOR( "Visuals" ) ) )
				{
					{
						BeginRow( 30, 13, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Draw Aim FOV" ), &_Settings._Miscellaneous._Visuals.bDrawAimFOV, PX_XOR( "Draw a circle to indicate what the boundaries of your aimbot FOV are.") );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Draw Aim FOV" ), 30 ).x - COLOR_BUTTON_PADDING * 4 - COLOR_BUTTON_WIDTH * 2 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Inner Circle" ), &_Settings._Miscellaneous._Visuals.seqAimFOV[ 0 ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Outer Circle" ), &_Settings._Miscellaneous._Visuals.seqAimFOV[ 1 ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Visualize Spread" ), &_Settings._Miscellaneous._Visuals.bVisualizeSpread, PX_XOR( "Draw a circle to visualize spread." ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Visualize Spread" ), 30 ).x - COLOR_BUTTON_PADDING * 4 - COLOR_BUTTON_WIDTH * 2 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Inner Circle" ), &_Settings._Miscellaneous._Visuals.seqSpread[ 0 ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Outer Circle" ), &_Settings._Miscellaneous._Visuals.seqSpread[ 1 ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Darken World" ), &_Settings._Miscellaneous._Visuals.bDarkenWorld, PX_XOR( "Darken the world." ) );

						EndRow( );
					}

					{
						BeginRow( 30, 14, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Modify FOV" ), &_Settings._Miscellaneous._Visuals.bModifyFOV );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Modify FOV" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Bullet Beams" ), &_Settings._Miscellaneous._Visuals.bBulletBeams );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Bullet Beams" ), 30 ).x - COLOR_BUTTON_WIDTH * 2 - COLOR_BUTTON_PADDING * 4 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Bullet Beam Miss" ), &_Settings._Miscellaneous._Visuals.seqBulletBeams[ 0 ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Bullet Beam Hit" ), &_Settings._Miscellaneous._Visuals.seqBulletBeams[ 1 ], COLOR_BUTTON_VERTICAL_PADDING );

						Checkbox( PX_XOR( "Hitmarkers" ), &_Settings._Miscellaneous._Visuals.bHitmarkers );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Hitmarkers" ), 30 ).x - COLOR_BUTTON_WIDTH * 2 - COLOR_BUTTON_PADDING * 4 );
						Spacing( );
						SetRowWidth( COLOR_BUTTON_WIDTH );
						ColorButton( PX_XOR( "Hitmarker Team" ), &_Settings._Miscellaneous._Visuals.seqHitmarkers[ 0 ], COLOR_BUTTON_VERTICAL_PADDING );
						ColorButton( PX_XOR( "Hitmarker Enemy" ), &_Settings._Miscellaneous._Visuals.seqHitmarkers[ 1 ], COLOR_BUTTON_VERTICAL_PADDING );

						EndRow( );
					}

					{
						BeginRow( 30, 4, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Fade Hitmarkers" ), &_Settings._Miscellaneous._Visuals.bHitmarkerFade );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Fade Hitmarkers" ), 30 ).x );
						Spacing( );

						EndRow( );
					}

					{
						static char szViewmodelFOV[ 32 ] { }, szRenderFOV[ 32 ] { }, szHitmarkerLength[32] { };

						BeginRow( 30, 9, ROW_CUSTOM );

						_Settings._Miscellaneous._Visuals.flViewmodelFOV = Slider( PX_XOR( "Viewmodel FOV" ), szViewmodelFOV, 0.f, 180.f, _Settings._Miscellaneous._Visuals.flViewmodelFOV, 10, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						_Settings._Miscellaneous._Visuals.flRenderFOV = Slider( PX_XOR( "Render FOV" ), szRenderFOV, 0.f, 180.f, _Settings._Miscellaneous._Visuals.flRenderFOV, GROUPBOX_COLUMN_WIDTH + 30, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						_Settings._Miscellaneous._Visuals.flHitmarkerLifetime = Slider( PX_XOR( "Hitmarker Length" ), szHitmarkerLength, 0.1f, 10.f, _Settings._Miscellaneous._Visuals.flHitmarkerLifetime, GROUPBOX_COLUMN_WIDTH * 2 + 40, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						EndRow( );
					}

					{
						static char szHitmarkerFade[ 32 ] { };

						BeginRow( 30, 3, ROW_CUSTOM );

						_Settings._Miscellaneous._Visuals.flHitmarkerFadeTime = Slider( PX_XOR( "Hitmarker Fade" ), szHitmarkerFade, 0.f, _Settings._Miscellaneous._Visuals.flHitmarkerLifetime, _Settings._Miscellaneous._Visuals.flHitmarkerFadeTime, 10, 10, GROUPBOX_COLUMN_WIDTH, 30, 1 );

						EndRow( );
					}

					EndGroupbox( );
				}
			}
			break;

			case INVENTORY:
			{
				SetMainWindowHeight( 603 );
				static settings_t::miscellaneous_t::inventory_t::team_t *pConfig = nullptr;
				static unsigned iSelectedWeapon = 0;
				static auto iSelectedPaintKit = 0;
				static auto uSelectedKnife = 0u;
				static auto uSelectedWeaponPaintKit = 0u;
				static auto iSelectedGlove = 0;

				const auto fnSetSelectedPaintKit = [ & ]( int iKitID )
				{
					for ( auto z = 0u; z < Other::vecPaintKits.size( ); z++ )
						if ( Other::vecPaintKits[ z ].iIdentifier == iKitID )
							iSelectedPaintKit = z;
					uSelectedWeaponPaintKit = 0u;
				};

				const auto fnSetModels = [ & ]( int iGlove, int iKnife )
				{
					switch ( iGlove )
					{
						case ITEM_GLOVE_BLOODHOUND:
						{
							iSelectedGlove = 0;
						}
						break;

						case ITEM_GLOVE_SPORTY:
						{
							iSelectedGlove = 1;
						}
						break;

						case ITEM_GLOVE_DRIVER:
						{
							iSelectedGlove = 2;
						}
						break;

						case ITEM_GLOVE_HAND_WRAP:
						{
							iSelectedGlove = 3;
						}
						break;

						case ITEM_GLOVE_MOTO:
						{
							iSelectedGlove = 4;
						}
						break;

						case ITEM_GLOVE_SPECIALIST:
						{
							iSelectedGlove = 5;
						}
						break;

						case ITEM_GLOVE_HYDRA:
						{
							iSelectedGlove = 6;
						}
						break;

						default:
							break;
					}

					switch ( iKnife )
					{
						case ITEM_WEAPON_KNIFE_BAYONET:
						{
							uSelectedKnife = 0;
						}
						break;

						case ITEM_WEAPON_KNIFE_FLIP:
						{
							uSelectedKnife = 1;
						}
						break;

						case ITEM_WEAPON_KNIFE_GUT:
						{
							uSelectedKnife = 2;
						}
						break;

						case ITEM_WEAPON_KNIFE_KARAMBIT:
						{
							uSelectedKnife = 3;
						}
						break;

						case ITEM_WEAPON_KNIFE_M9_BAYONET:
						{
							uSelectedKnife = 4;
						}
						break;

						case ITEM_WEAPON_KNIFE_TACTICAL:
						{
							uSelectedKnife = 5;
						}
						break;

						case ITEM_WEAPON_KNIFE_FALCHION:
						{
							uSelectedKnife = 6;
						}
						break;

						case ITEM_WEAPON_KNIFE_SURVIVAL_BOWIE:
						{
							uSelectedKnife = 7;
						}
						break;

						case ITEM_WEAPON_KNIFE_BUTTERFLY:
						{
							uSelectedKnife = 8;
						}
						break;

						case ITEM_WEAPON_KNIFE_SHADOW_DAGGERS:
						{
							uSelectedKnife = 9;
						}
						break;

						case ITEM_WEAPON_KNIFE_URSUS:
						{
							uSelectedKnife = 10;
						}
						break;

						case ITEM_WEAPON_KNIFE_NAVAJA:
						{
							uSelectedKnife = 11;
						}
						break;

						case ITEM_WEAPON_KNIFE_STILLETTO:
						{
							uSelectedKnife = 12;
						}
						break;

						case ITEM_WEAPON_KNIFE_TALON:
						{
							uSelectedKnife = 13;
						}
						break;

						default:
							break;
					}
				};

				if ( BeginGroupbox( 200, 150, 500, 112, PX_XOR( "Configuration" ) ) )
				{
					static auto iTeam = 0;
					{
						std::deque< cstr_t > dqTeams
						{
							PX_XOR( "Terrorist" ),
							PX_XOR( "Counter-Terrorist" )
						};

						VerticalSpacing( );

						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						const auto iOldTeam = iTeam;
						fnSetValue( iTeam, Combobox( 30, PX_XOR( "Team" ), dqTeams, iTeam ) );

						EndRow( );

						pConfig = iTeam == 0 ? &_Settings._Miscellaneous._Inventory._Terrorist : &_Settings._Miscellaneous._Inventory._CounterTerrorist;
						if ( iOldTeam != iTeam )
						{
							fnSetSelectedPaintKit( pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].iPaintKitID );
							fnSetModels( pConfig->_Models.iGloveModel, pConfig->_Models.iKnifeModel );
						}
					}

					{
						BeginRow( 30, 10, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Modify Inventory" ), &pConfig->bModifyInventory );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Modify Inventory" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Modify Knife Model" ), &pConfig->bModifyKnifeModel );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Modify Knife Model" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Modify Glove Model" ), &pConfig->bModifyGloveModel );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Modify Glove Model" ), 30 ).x );
						Spacing( );

						EndRow( );
					}

					EndGroupbox( );
				}

				if ( BeginGroupbox( 401, 175, 500, 220, PX_XOR( "Paint Kits" ) ) )
				{
					{
						VerticalSpacing( );

						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH * 3.f + 29.f );
						const auto buf = iSelectedWeapon;
						TabbedCombobox( 30, PX_XOR( "Weapons" ), dqCategories, dqWeapons, iSelectedWeapon );
						if ( buf != iSelectedWeapon )
							fnSetSelectedPaintKit( pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].iPaintKitID );

						EndRow( );
					}

					{
						constexpr struct nk_color clrText[ GRADE_CONTRABAND + 1]
						{
							{ },
							{ 0xB0, 0xC3, 0xD9, 0xFF },
							{ 0x5E, 0x98, 0xD9, 0xFF },
							{ 0x4B, 0x69, 0xFF, 0xFF },
							{ 0x88, 0x47, 0xFF, 0xFF },
							{ 0xD3, 0x2E, 0xE6, 0xFF },
							{ 0xEB, 0x4B, 0x4B, 0xFF },
							{ 0xEB, 0x4B, 0x4B, 0xFF },
							{ 0xFF, 0xAE, 0x39, 0xFF },
						};
						constexpr char *szPageNumbers[ ] { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
						constexpr auto flWidth = ( GROUPBOX_COLUMN_WIDTH * 3.f + 29.f ) / 2.f - 1.f;
						static std::deque< cstr_t > dqPaintKits;
						static char szSearch[ 32 ] { };
						if ( dqPaintKits.empty( ) )
							for ( const auto &kit: Other::vecPaintKits )
								dqPaintKits.emplace_back( kit.strName.c_str( ) );

						const auto vecWeaponKits = Other::GetWeaponKits( ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] );
						const auto iPages = int( ceil( vecWeaponKits.size( ) / 7.f ) );
						std::deque< cstr_t > dqPages;
						for ( auto i = 0; i < iPages; i++ )
							dqPages.emplace_back( szPageNumbers[ i ] );

						const auto dqItems = new std::deque< colored_text_t >[ iPages ];
						for ( auto i = 0; i < iPages; i++ )
							for ( auto j = i * 7; j < i * 7 + 7 && j < vecWeaponKits.size( ); j++ )
								dqItems[ i ].emplace_back( colored_text_t( vecWeaponKits[ j ].strName.c_str( ), clrText[ vecWeaponKits[ j ].iGrade ] ) );

						BeginRow( 30, 3, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( flWidth );
						const auto iResult = FilteredCombobox( 30, PX_XOR( "All Paintkits" ), dqPaintKits, iSelectedPaintKit, 10, szSearch );
						if ( iResult >= 0 )
						{
							iSelectedPaintKit = iResult;
							pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].iPaintKitID = Other::vecPaintKits[ iSelectedPaintKit ].iIdentifier;
							Miscellaneous::ForceUpdate( );
						}

						if ( TabbedCombobox( 30, PX_XOR( "Weapon Paintkits" ), dqPages, dqItems, uSelectedWeaponPaintKit ) )
						{
							Miscellaneous::ForceUpdate( );
							pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].iPaintKitID = vecWeaponKits[ uSelectedWeaponPaintKit ].iIdentifier;
						}

						EndRow( );

						delete[ ] dqItems;
					}

					{
						BeginRow( 30, 9, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Souvenir" ), &pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].bSouvenier );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Souvenir" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "StatTrak" ), &pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].bStatTrak );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CHECKBOX_ICON_WIDTH - CalculateTextBounds( PX_XOR( "Souvenir" ), 30 ).x );
						Spacing( );

						Checkbox( PX_XOR( "Use Custom Name" ), &pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].bUseCustomName );

						EndRow( );
					}

					{
						BeginRow( 30, 3, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( CalculateTextBounds( PX_XOR( "Name: " ), 30 ).x );
						Text( PX_XOR( "Name: " ), color_t( { 255, 255, 255, 255 } ) );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH - CalculateTextBounds( PX_XOR( "Name: " ), 30 ).x );
						Inputbox( 32, pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].szName );
						mbstowcs( pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].wszName, pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].szName, 32 );

						EndRow( );
					}

					{
						static char szStatTrak[ 32 ], szSeed[ 32 ], szWear[ 32 ];

						BeginRow( 30, 9, ROW_CUSTOM );

						pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].iStatTrakCounter = Slider( PX_XOR( "StatTrak" ), szStatTrak, 0, 999999, pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].iStatTrakCounter, 10, 10, GROUPBOX_COLUMN_WIDTH, 30 );

						pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].flWear = Slider( PX_XOR( "Wear" ), szWear, 0.01f, 1.f, pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].flWear, GROUPBOX_COLUMN_WIDTH + 30, 10, GROUPBOX_COLUMN_WIDTH, 30, 2 );

						pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].iSeed = Slider( PX_XOR( "Seed" ), szSeed, 0, 1000, pConfig->_PaintKits[ ITEM_DEFINITION_INDICIES[ iSelectedWeapon ] ].iSeed, GROUPBOX_COLUMN_WIDTH * 2 + 40, 10, GROUPBOX_COLUMN_WIDTH, 30 );

						EndRow( );
					}

					EndGroupbox( );
				}

				if ( BeginGroupbox( 401, 379, 500, 120, PX_XOR( "Models" ) ) )
				{
					{
						std::deque< cstr_t > dqPages
						{
							PX_XOR( "Page 1" ),
							PX_XOR( "Page 2" )
						};

						cstr_t szKnives[ ]
						{
							PX_XOR( "Bayonet" ),
							PX_XOR( "Flip" ),
							PX_XOR( "Gut" ),
							PX_XOR( "Karambit" ),
							PX_XOR( "M9 Bayonet" ),
							PX_XOR( "Huntsman" ),
							PX_XOR( "Falchion" ),
							PX_XOR( "Bowie" ),
							PX_XOR( "Butterfly" ),
							PX_XOR( "Shadow Daggers" ),
							PX_XOR( "Ursus" ),
							PX_XOR( "Navaja" ),
							PX_XOR( "Stilletto" ),
							PX_XOR( "Talon" )
						};

						std::deque< cstr_t > dqKnives[ ]
						{
							{
								PX_XOR( "Bayonet" ),
								PX_XOR( "Flip" ),
								PX_XOR( "Gut" ),
								PX_XOR( "Karambit" ),
								PX_XOR( "M9 Bayonet" ),
								PX_XOR( "Huntsman" ),
								PX_XOR( "Falchion" ),
								PX_XOR( "Bowie" ),
								PX_XOR( "Butterfly" ),
								PX_XOR( "Shadow Daggers" )
							},
							{
								PX_XOR( "Ursus" ),
								PX_XOR( "Navaja" ),
								PX_XOR( "Stilletto" ),
								PX_XOR( "Talon" )
							}
						};

						std::deque< cstr_t > dqGloves
						{
							PX_XOR( "Bloodhound" ),
							PX_XOR( "Sport" ),
							PX_XOR( "Driver" ),
							PX_XOR( "Hand Wrap" ),
							PX_XOR( "Moto" ),
							PX_XOR( "Specialist" ),
							PX_XOR( "Hydra" )
						};

						BeginRow( 30, 3, ROW_STATIC );
						SetRowWidth( 10 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						TabbedCombobox( 30, PX_XOR( "Knife Model" ), dqPages, dqKnives, uSelectedKnife );
						pConfig->_Models.iKnifeModel = Other::GetItemDefinitionIndex( szKnives[ uSelectedKnife ] );

						fnSetValue( iSelectedGlove, Combobox( 30, PX_XOR( "Glove Model" ), dqGloves, iSelectedGlove ) );
						pConfig->_Models.iGloveModel = Other::GetItemDefinitionIndex( dqGloves[ iSelectedGlove ] );

						EndRow( );
					}
					EndGroupbox( );
				}
			}
			break;

			case OTHER:
			{
				if ( BeginGroupbox( 200, 150, 500, 112, PX_XOR( "Other" ) ) )
				{
					{
						BeginRow( 30, 3, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						Checkbox( PX_XOR( "Hitsound" ), &_Settings._Miscellaneous._Other.bHitSound );

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

	void PX_API LayoutSettings( int iSubtab )
	{
		enum
		{
			GLOBAL,
			OTHER
		};

		switch ( iSubtab )
		{
			case GLOBAL:
			{
				if ( BeginGroupbox( 200, 150, 500, 112, PX_XOR( "Global Configuration" ) ) )
				{
					VerticalSpacing( );

					{
						static std::string strConfig { };
						if ( strConfig.empty( ) )
							strConfig.resize( 32u );

						BeginRow( 30, 4, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						SetFont( FNT_ROBOTO_SMALL );
						SetRowWidth( CalculateTextBounds( PX_XOR( "Default Configuration:" ), 30 ).x );
						Text( PX_XOR( "Default Configuration:" ), color_t( { 255, 255, 255, 255 } ) );
						SetRowWidth( 5 );
						Spacing( );
						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						Inputbox( 32u, &strConfig[ 0 ] );

						EndRow( );

						PX_CONFIG.SetDefaultConfiguration( strConfig );
					}
					EndGroupbox( );
				}
			}
			break;

			default:
			{
				if ( BeginGroupbox( 200, 150, 500, 112, PX_XOR( "Other Configurations" ) ) )
				{
					static auto iSelectedConfig = 0;
					const auto vecConfigs = PX_CONFIG.GetConfigs( );
					std::deque< const char* > vecMen { };
					for ( auto& config : vecConfigs )
						vecMen.emplace_back( config.c_str( ) );

					if ( iSelectedConfig >= int( vecConfigs.size( ) ) )
						iSelectedConfig = 0;

					{
						VerticalSpacing( );

						BeginRow( 30, 2, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH );
						fnSetValue( iSelectedConfig, Combobox( 30, PX_XOR( "Configs" ), vecMen, iSelectedConfig ) );

						EndRow( );
					}

					{
						VerticalSpacing( );

						BeginRow( 30, 4, ROW_STATIC );
						SetRowWidth( 5 );
						Spacing( );

						SetRowWidth( GROUPBOX_COLUMN_WIDTH / 2.f );

						if ( Button( EPosition::LEFT, PX_XOR( "Save" ), false, false ) )
							PX_CONFIG.SaveConfiguration( Tools::string_cast< std::wstring >( vecConfigs[ iSelectedConfig ] ).c_str( ) );
						if ( Button( EPosition::CENTER, PX_XOR( "Load" ), false, false ) )
							PX_CONFIG.LoadConfiguration( Tools::string_cast< std::wstring >( vecConfigs[ iSelectedConfig ] ).c_str( ) );
						if ( Button( EPosition::RIGHT, PX_XOR( "Remove" ), false, false ) )
							PX_CONFIG.RemoveConfiguration( Tools::string_cast< std::wstring >( vecConfigs[ iSelectedConfig ] ).c_str( ) );

						EndRow( );
					}
					EndGroupbox( );
				}
			}
			break;
		}
	}
}
