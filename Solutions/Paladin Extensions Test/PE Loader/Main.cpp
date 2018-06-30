/// Main.cpp

#include "Main.hpp"

void CUserInterface::SetLayout( )
{
	static int iCurrentTab { }, iCurrentLowerTab { };

	wdg.NewRow( );
	iCurrentTab = wdg.RegularButton( ICON_FA_FILE " File Manager", iCurrentTab == 0 ) ? 0 : iCurrentTab;

	wdg.NewRow( );
	iCurrentTab = wdg.RegularButton( ICON_FA_CALCULATOR " Calculator", iCurrentTab == 1 ) ? 1 : iCurrentTab;
	
	wdg.NewRow( );
	iCurrentTab = wdg.RegularButton( ICON_FA_MONEY_BILL " Finance", iCurrentTab == 2 ) ? 2 : iCurrentTab;

	wdg.NewRow( );
	iCurrentTab = wdg.RegularButton( ICON_FA_BOMB " Bomb Syria", iCurrentTab == 3 ) ? 3 : iCurrentTab;

	wdg.NewRow( 25 );

	iCurrentLowerTab = wdg.SpecialButton( CWidgets::EPosition::LEFT, "LEFT ROUNDED", iCurrentLowerTab == 0 ) ? 0 : iCurrentLowerTab;
	iCurrentLowerTab = wdg.SpecialButton( CWidgets::EPosition::CENTER, "NO ROUNDING", iCurrentLowerTab == 1 ) ? 1 : iCurrentLowerTab;
	iCurrentLowerTab = wdg.SpecialButton( CWidgets::EPosition::RIGHT, "RIGHT ROUNDED", iCurrentLowerTab == 2 ) ? 2 : iCurrentLowerTab;

	wdg.NewRow( 25, 4 );

	static bool bWasPressed[ 4 ];
	bWasPressed[ 0 ] = wdg.SpecialButton( CWidgets::EPosition::LEFT, ICON_FA_PLUS, bWasPressed[ 0 ] );
	bWasPressed[ 1 ] = wdg.SpecialButton( CWidgets::EPosition::CENTER, ICON_FA_SAVE, bWasPressed[ 1 ] );
	bWasPressed[ 2 ] = wdg.SpecialButton( CWidgets::EPosition::CENTER, ICON_FA_UNDO, bWasPressed[ 2 ] );
	bWasPressed[ 3 ] = wdg.SpecialButton( CWidgets::EPosition::RIGHT, ICON_FA_TIMES_CIRCLE, bWasPressed[ 3 ] );
}				    

void OnLaunch( )
{
	std::cout << "Started User Interface Creation" << dbg::endl;

	unsigned u[ ]
	{
		600, 600
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
