/// Main.cpp

#include "Main.hpp"



void CUserInterface::SetLayout( )
{
	//wdg.urmom( );
	static int iCurrentUpperTab { }, iCurrentSubTab { }, iCurrentLowerTab { };
	
	wdg.NewRow( 48, 5 );
	ui->SetFont( EFont::ROBOTOBOLDSMALL );
	iCurrentUpperTab = wdg.TopButton( ICON_FA_MONEY_BILL " Finance", iCurrentUpperTab == 0 ) ? 0 : iCurrentUpperTab;
	iCurrentUpperTab = wdg.TopButton( ICON_FA_PHONE " Phone", iCurrentUpperTab == 1 ) ? 1 : iCurrentUpperTab;
	iCurrentUpperTab = wdg.TopButton( ICON_FA_ADDRESS_BOOK " Addresses", iCurrentUpperTab == 2 ) ? 2 : iCurrentUpperTab;
	iCurrentUpperTab = wdg.TopButton( ICON_FA_CAR " Cars", iCurrentUpperTab == 3 ) ? 3 : iCurrentUpperTab;
	iCurrentUpperTab = wdg.TopButton( ICON_FA_BOMB " Bomb Syria", iCurrentUpperTab == 4 ) ? 4 : iCurrentUpperTab;
	
	wdg.Separator( 61, 65, 72, 100, 5 );
	ui->SetFont( EFont::ROBOTOBOLDSMALL );
	wdg.NewRow( 25 );
	
	iCurrentLowerTab = wdg.SpecialButton( CWidgets::EPosition::LEFT, "LEFT ROUNDED", iCurrentLowerTab == 0 ) ? 0 : iCurrentLowerTab;
	iCurrentLowerTab = wdg.SpecialButton( CWidgets::EPosition::CENTER, "NO ROUNDING", iCurrentLowerTab == 1 ) ? 1 : iCurrentLowerTab;
	iCurrentLowerTab = wdg.SpecialButton( CWidgets::EPosition::RIGHT, "RIGHT ROUNDED", iCurrentLowerTab == 2 ) ? 2 : iCurrentLowerTab;
	
	wdg.NewRow( 25, 0 );
	wdg.NewRow( 30 );
	ui->SetFont( EFont::TAHOMA );
	iCurrentSubTab = wdg.RegularButton( "Men are Hot!", iCurrentSubTab == 0 ) ? 0 : iCurrentSubTab;
	iCurrentSubTab = wdg.RegularButton( "Men are Hot!", iCurrentSubTab == 1 ) ? 1 : iCurrentSubTab;
	iCurrentSubTab = wdg.RegularButton( "Men are Hot!", iCurrentSubTab == 2 ) ? 2 : iCurrentSubTab;
	
	wdg.NewRow( 25, 4 );
	
	static bool bWasPressed[ 4 ] { };
	bWasPressed[ 0 ] = wdg.SpecialButton( CWidgets::EPosition::LEFT, ICON_FA_PLUS, bWasPressed[ 0 ] );
	bWasPressed[ 1 ] = wdg.SpecialButton( CWidgets::EPosition::CENTER, ICON_FA_SAVE, bWasPressed[ 1 ] );
	bWasPressed[ 2 ] = wdg.SpecialButton( CWidgets::EPosition::CENTER, ICON_FA_UNDO, bWasPressed[ 2 ] );
	bWasPressed[ 3 ] = wdg.SpecialButton( CWidgets::EPosition::RIGHT, ICON_FA_TIMES_CIRCLE, bWasPressed[ 3 ] );

	wdg.BeginRow( );
	static bool bCheckbox[ 3 ] { };
	wdg.Checkbox( "Men", &bCheckbox[ 0 ] );
	wdg.Checkbox( "Men1", &bCheckbox[ 1 ] );
	wdg.Checkbox( "Men2", &bCheckbox[ 2 ] );
	wdg.EndRow( );
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
