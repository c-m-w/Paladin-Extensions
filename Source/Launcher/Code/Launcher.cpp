/// Launcher.cpp

#include "Precompile.hpp"

#define ENTRY_SOURCE
#include "Launcher.hpp"

void Draw( );
void CallRun( );
void CallDrawLoop( );

// todo check VMP debug checks and shit

void OnLaunch( )
{
	if ( !SetupFramework( )
		|| !_Functionality.Setup( ) )
		return;

	std::thread tRun( CallRun );
	tRun.detach( );

	_Functionality.DrawLoop( );

	while ( 1 )
		Pause( 1 );

	_Functionality.Shutdown( );
}

void Draw( )
{
	bool temp = false;
	_GUI.Setup( );
	auto button = new CButton( );
	button->SetText( "create super p popup" );

	auto left = new CGroupButton( );
	auto center = new CGroupButton( );
	auto right = new CGroupButton( );
	auto row = new CHorizontalRow( );

	left->SetText( "button" );
	left->SetType( BUTTON_LEFT );
	center->SetText( "button" );
	center->SetType( BUTTON_CENTER );
	right->SetText( "button" );
	right->SetType( BUTTON_RIGHT );
	row->SetAlignment( HALIGNMENT_LEFT );
	row->AddWidget( left );
	row->SetAlignment( HALIGNMENT_CENTER );
	row->AddWidget( center );
	row->SetAlignment( HALIGNMENT_RIGHT );
	row->AddWidget( right );
	row->Clamp( );
	row->SetAlignmentGap( 0.02083333333 );

	auto checkbox = new CCheckbox( );
	checkbox->SetSubject( "super p checkbox" );
	checkbox->SetVariable( &temp );
	checkbox->SetSize( checkbox->CalculateRequiredSpace( ) );
	auto window = new CWindow( { 0, 0, 15, 8 } );
	window->ShowIcon( );
	window->SetTitle( "Paladin Extensions" );
	window->SetSubtitle( "Launcher" );
	window->SetMinimizeCallback( [ & ]( )
								{ } );
	window->SetCloseCallback( [ & ]( )
							 { } );
	window->EnableScrollbars( );
	window->AddObject( button, { 10.0 / 96.0, 2.96875 } );
	window->AddObject( checkbox, { 50.0 / 96.0, 160.0 / 96.0 } );
	window->AddObject( row, { 250.0 / 96.0 + 1.5625, 90.0 / 96.0 } );
	_GUI.AddWindow( window );

	auto window2 = new CWindow( { 0, 0, 5, 5 } );
	window2->ShowIcon( );
	window2->SetTitle( "popupwindow420" );
	window2->SetSubtitle( "popupwindow420_subtitle" );

	button->GetCallbacks( ).AddCallback( [ & ]( CKeyState _State )
	{
		if ( !_State )
			return window->Popup( window2, true ), true;

		return false;
	}, VK_LBUTTON );

	//while ( !bExit )
	//{
	//	if ( pApplicationWindow->PollInput( ) )
	//		continue;
	//
	//	const auto mmtNow = GetMoment( );
	//
	//	DRAW.BeginFrame( );
	//	//first->Draw( );
	//	//second->Draw( );
	//	_GUI.Draw( );
	//	DRAW.EndFrame( );
	//
	//	const auto mmtDifference = GetMoment( ) - mmtNow;
	//	if ( mmtDifference > 1000.0 / 60.0 )
	//		continue;
	//
	//	Pause( 1000.0 / 60.0 - mmtDifference );
	//}
	//
	//pApplicationWindow->Destroy( );
}

void CallRun( )
{
	_Functionality.Run( );
}

void CallDrawLoop( )
{
	_Functionality.DrawLoop( );
}
