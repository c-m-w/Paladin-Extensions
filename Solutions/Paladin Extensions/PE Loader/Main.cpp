/// Main.cpp

#include "Main.hpp"

void Button1Callback( )
{
	std::cout << "I've been called because Button 1 was clicked!" << std::endl;
}
void Button2Callback( )
{
	std::cout << "I've been called because Button 2 was clicked!" << std::endl;
}

void OnLaunch( )
{
	std::cout << "Started User Interface Creation" << dbg::endl;

	unsigned u[ ]
	{
		500, 500
	};
	ui = new CUserInterface( "men", u, L"MEN_ASS" );
	std::cout << "Created User Interface" << dbg::endl;

	std::cout << "Initializing User Interface" << dbg::endl;
	ui->InitializeUserInterface( );
	std::cout << "Initialized User Interface Successfully" << dbg::endl;

	std::cout << "Drawing User Interface" << dbg::endl;

	ui->dqWidgets.emplace_back( CUserInterface::SWidget( "MENASS", "NOT UR DAD TOOL TIP", Button1Callback ) );
	int bob = 0;
	ui->dqWidgets.emplace_back( CUserInterface::SWidget( "MENASSCHECJ", "NOT UR DAD TOOL TIP3", &bob ) );
	ui->dqWidgets.emplace_back( CUserInterface::SWidget( "MENASS2", "NOT UR DAD TOOL TIP2", Button2Callback ) );

	while ( ui->DrawUserInterface( ) )
		if ( !ui->DrawUserInterface( ) )
			break;

	std::cout << "Finished Drawing User Interface; cleaning up" << dbg::endl;
	ui->Shutdown( );

	std::cout << "Finished Drawing User Interface; cleaning up" << dbg::endl;
}
