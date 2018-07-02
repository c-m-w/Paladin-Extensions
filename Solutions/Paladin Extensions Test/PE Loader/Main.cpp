/// Main.cpp

#include "Main.hpp"

std::deque< const char * > dqTabs
{
	{
		ICON_FA_MONEY_BILL " Tab 1",
		ICON_FA_PHONE " Tab 2",
		ICON_FA_ADDRESS_BOOK " Tab 3",
		ICON_FA_CAR " Tab 4",
		ICON_FA_BOMB " Tab 5"
	}
};

std::deque< std::deque< const char * > > dqSidebarButtons
{
	{
		"Tab 1 Subtab 1",
		"Tab 1 Subtab 2",
		"Tab 1 Subtab 3",
		"Tab 1 Subtab 4"
	},
	{
		"Tab 2 Subtab 1",
		"Tab 2 Subtab 2",
		"Tab 2 Subtab 3",
		"Tab 2 Subtab 4"
	},
	{
		"Tab 3 Subtab 1",
		"Tab 3 Subtab 2",
		"Tab 3 Subtab 3",
		"Tab 3 Subtab 4"
	},
	{
		"Tab 4 Subtab 1",
		"Tab 4 Subtab 2",
		"Tab 4 Subtab 3",
		"Tab 4 Subtab 4"
	},
	{
		"Tab 5 Subtab 1",
		"Tab 5 Subtab 2",
		"Tab 5 Subtab 3",
		"Tab 5 Subtab 4"
	}
};

std::deque< std::deque< const char * > > dqGroupBoxes
{
	{
		"Tab 1 Subtab 1 Groupbox",
		"Tab 1 Subtab 2 Groupbox",
		"Tab 1 Subtab 3 Groupbox",
		"Tab 1 Subtab 4 Groupbox"
	},

	{
		"Tab 2 Subtab 1 Groupbox",
		"Tab 2 Subtab 2 Groupbox",
		"Tab 2 Subtab 3 Groupbox",
		"Tab 2 Subtab 4 Groupbox"
	},

	{
		"Tab 3 Subtab 1 Groupbox",
		"Tab 3 Subtab 2 Groupbox",
		"Tab 3 Subtab 3 Groupbox",
		"Tab 3 Subtab 4 Groupbox"
	},

	{
		"Tab 4 Subtab 1 Groupbox",
		"Tab 4 Subtab 2 Groupbox",
		"Tab 4 Subtab 3 Groupbox",
		"Tab 4 Subtab 4 Groupbox"
	},

	{
		"Tab 5 Subtab 1 Groupbox",
		"Tab 5 Subtab 2 Groupbox",
		"Tab 5 Subtab 3 Groupbox",
		"Tab 5 Subtab 4 Groupbox"
	},
};

void CUserInterface::SetLayout( )
{
	//wdg.menfuck( );
	static px_color_t clr( { 255, 0, 0, 255 } ), clr1( { 0, 255, 255, 255 } );
	static int iCurrentUpperTab { }, iCurrentSubTab { }, iCurrentLowerTab { };

	auto iTabResult = wdg.Tabs( 10, 0, 140, 45, dqTabs, iCurrentUpperTab );
	iCurrentUpperTab = iTabResult >= 0 ? iTabResult : iCurrentUpperTab;
	
	wdg.Separator( 61, 65, 72, 100, 5 );
	ui->SetFont( EFont::ROBOTOBOLDSMALL );
	wdg.NewRow( 25 );
	
	iCurrentLowerTab = wdg.SpecialButton( CWidgets::EPosition::LEFT, "LEFT ROUNDED", iCurrentLowerTab == 0 ) ? 0 : iCurrentLowerTab;
	iCurrentLowerTab = wdg.SpecialButton( CWidgets::EPosition::CENTER, "NO ROUNDING", iCurrentLowerTab == 1 ) ? 1 : iCurrentLowerTab;
	iCurrentLowerTab = wdg.SpecialButton( CWidgets::EPosition::RIGHT, "RIGHT ROUNDED", iCurrentLowerTab == 2 ) ? 2 : iCurrentLowerTab;
	
	auto iResult = wdg.Sidebar( 30, 190, 5, 10, dqSidebarButtons.at( iCurrentUpperTab ), iCurrentSubTab );
	iCurrentSubTab = iResult >= 0 ? iResult : iCurrentSubTab;

	wdg.BeginGroupbox( 240, 300, 205, 147, dqGroupBoxes.at( iCurrentUpperTab ).at( iCurrentSubTab ), 155 );
	wdg.EndGroupbox( );

	wdg.BeginGroupbox( 240, 300, 665, 35, dqGroupBoxes.at( iCurrentUpperTab ).at( iCurrentSubTab ), 155 );
	wdg.BeginRow( 17, 3 );
	static auto b = false;
	wdg.Checkbox( "Counter-Terrorist Visible", 170, &b );
	wdg.SetRowWidth( 30 );
	wdg.ColorButton( "Counter-Terrorist Glow Visible", &clr );
	wdg.EndRow( );

	wdg.BeginRow( 17, 3 );
	static auto b1 = false;
	wdg.Checkbox( "Counter-Terrorist Invisible", 170, &b1 );
	wdg.SetRowWidth( 30 );
	wdg.ColorButton( "Counter-Terrorist Glow Invisible", &clr1 );
	wdg.EndRow( );
	wdg.EndGroupbox( );

	if ( wdg.pActiveEditColor != nullptr )
		wdg.ColorPicker( );

	//wdg.BeginRow( );
	//static bool bCheckbox[ 3 ] { };
	//wdg.Checkbox( "Men", &bCheckbox[ 0 ] );
	//wdg.Checkbox( "Men1", &bCheckbox[ 1 ] );
	//wdg.Checkbox( "Men2", &bCheckbox[ 2 ] );
	//wdg.EndRow( );
}				    

void OnLaunch( )
{
	std::cout << "Started User Interface Creation" << dbg::endl;

	unsigned u[ ]
	{
		720, 600
	};

	ui = new CUserInterface( M_XOR( "Paladin Extensions" ), M_XOR( "Loader" ), u, M_WXOR( L"Paladin Extensions Loader" ) );
	std::cout << M_XOR( "Created User Interface" ) << dbg::endl;

	std::cout << M_XOR( "Initializing User Interface" ) << dbg::endl;
	ui->InitializeUserInterface( );
	std::cout << M_XOR( "Initialized User Interface Successfully" ) << dbg::endl;

	std::cout << M_XOR( "Drawing User Interface" ) << dbg::endl;

	while ( ui->DrawUserInterface( ) )
		Wait( 1 );

	std::cout << M_XOR( "Finished Drawing User Interface; cleaning up" ) << dbg::endl;
	ui->Shutdown( );

	std::cout << M_XOR( "Finished Drawing User Interface; cleaning up" ) << dbg::endl;
}
