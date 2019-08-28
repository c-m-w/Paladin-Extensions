/// Functionality.cpp

#include "Precompile.hpp"

#define USE_INTERNAL_NAMESPACES
#define USE_INTERNAL_DEFINITIONS
#include "Launcher.hpp"

bool CFunctionality::Initialize( )
{
	pApplicationWindow = new CApplicationWindow( ENC( "Launcher" ), InchesToPixels( { LAUNCHER_WIDTH, LAUNCHER_HEIGHT } ), GetModuleHandle( nullptr ) );
	pApplicationWindow->Show( );
	if ( !DRAW.ChangeTarget( pApplicationWindow ) )
		return false;

	_GUI.Setup( );
	pWindow = new CWindow( { 0, 0, LAUNCHER_WIDTH, LAUNCHER_HEIGHT } );
	pWindow->ShowIcon( );
	pWindow->SetTitle( TITLE );
	pWindow->SetSubtitle( SUBTITLE );
	pWindow->SetCloseCallback( [ & ]( )
	{
		bExit = true;
	} );
	pWindow->SetMinimizeCallback( [ & ]( )
	{
		pApplicationWindow->Minimize( );
	} );
	_GUI.AddWindow( pWindow );

	pWaitingContainer = new CContainer( );
	pWaitingContainer->SetSize( { LAUNCHER_WIDTH, LAUNCHER_HEIGHT - CWindowHeader::HEIGHT } );
	ChangeCurrentContainer( pWaitingContainer );

	pLoadingLogo = new CVectorGraphic( );
	pLoadingLogo->SetResourceName( ENC( "PX Logo.svg" ) );

	const auto dbMin = std::min( pWaitingContainer->GetSize( ).x, pWaitingContainer->GetSize( ).y );
	pLoadingLogo->SetSize( { dbMin, dbMin } );
	pWaitingContainer->AddObject( pLoadingLogo, { pWaitingContainer->GetSize( ).x / 2.0 - dbMin / 2.0, 0.0 } );
	_LogoAlphaTimer.Start( );

	for ( auto i = 0; i != ELoginCode::MAX_LOGIN_CODE; i++ )
		pLoginCodeContainers[ i ] = new CContainer( ), pLoginCodeContainers[ i ]->SetSize( { LAUNCHER_WIDTH, LAUNCHER_HEIGHT - CWindowHeader::HEIGHT } );

	pStaffLoginNotificationTop = new CText( );
	pStaffLoginNotificationTop->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pStaffLoginNotificationTop->SetText( ENC( "You have been successfully logged in as staff." ) );
	pStaffLoginNotificationTop->SetFont( FONT_ROBOTO );
	pStaffLoginNotificationTop->SetWeight( WEIGHT_MEDIUM );
	pStaffLoginNotificationTop->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::STAFF_SUCCESS ]->AddObject( pStaffLoginNotificationTop, { pLoginCodeContainers[ ELoginCode::STAFF_SUCCESS ]->GetSize( ).x / 2.0 - PixelsToInches( pStaffLoginNotificationTop->GetTextSize( ).x ) / 2.0, 1.0 } );

	pStaffLoginNotificationBottom = new CText( );
	pStaffLoginNotificationBottom->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pStaffLoginNotificationBottom->SetText( ENC( "Please wait shortly." ) );
	pStaffLoginNotificationBottom->SetFont( FONT_ROBOTO );
	pStaffLoginNotificationBottom->SetWeight( WEIGHT_LIGHT );
	pStaffLoginNotificationBottom->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::STAFF_SUCCESS ]->AddObject( pStaffLoginNotificationBottom, { pLoginCodeContainers[ ELoginCode::STAFF_SUCCESS ]->GetSize( ).x / 2.0 - PixelsToInches( pStaffLoginNotificationBottom->GetTextSize( ).x ) / 2.0, 1.0 + PixelsToInches( pStaffLoginNotificationTop->GetSize( ).y ) + 0.05208333333 } );

	return true;
}

void CFunctionality::Uninitialize( )
{
	pApplicationWindow->Destroy( );
	delete pApplicationWindow;
}

void CFunctionality::ChangeCurrentContainer( CContainer*& pNew )
{
	if ( mmtContainerChangeTime != 0ull ) // not done animating out
		return;

	if ( pLastContainerLocation )
	{
		( *pLastContainer )->RemoveAnimatedValue( pLastContainerLocation );
		( *pCurrentContainer )->RemoveAnimatedValue( pNextContainerLocation );
		( *pCurrentContainer )->RemoveAnimatedValue( pNextContainerAlphaFade );

		delete pLastContainerLocation;
		pLastContainerLocation = nullptr;
		delete pNextContainerLocation;
		pNextContainerLocation = nullptr;
	}

	if ( pCurrentContainer )
		pLastContainer = pCurrentContainer;

	pCurrentContainer = &pNew;
	pWindow->AddObject( pNew, { 0.0, CWindowHeader::HEIGHT } );
	mmtContainerChangeTime = GetMoment( );

	if ( pLastContainer )
	{
		pLastContainerLocation = new animated_value_t< vector2_t >( &( *pLastContainer )->GetRelativeLocation( ) );
		pLastContainerLocation->SetAnimationTime( ANIMATION_TIME );
		pLastContainerLocation->SetEaseType( ANIMATION_EASE_OUT );
		pLastContainerLocation->AnimateValue( { -LAUNCHER_WIDTH, 0.0 }, { } );
		( *pLastContainer )->AddAnimatedValue( pLastContainerLocation );

		pNextContainerLocation = new animated_value_t< vector2_t >( &( *pCurrentContainer )->GetRelativeLocation( ) );
		pNextContainerLocation->SetAnimationTime( ANIMATION_TIME );
		pNextContainerLocation->SetEaseType( ANIMATION_EASE_IN );
		pNextContainerLocation->AnimateValue( { }, { LAUNCHER_WIDTH, 0.0 } );
		( *pCurrentContainer )->AddAnimatedValue( pNextContainerLocation );

		pNextContainerAlphaFade = new animated_value_t< double >( &( *pCurrentContainer )->GetAlphaRatio( ) );
		pNextContainerAlphaFade->SetAnimationTime( ANIMATION_TIME );
		pNextContainerAlphaFade->SetEaseType( ANIMATION_EASE_IN );
		pNextContainerAlphaFade->AnimateValue( 1.0, 0.0 );
		( *pCurrentContainer )->AddAnimatedValue( pNextContainerAlphaFade );
	}
}

void CFunctionality::CheckContainerAnimation( )
{
	if ( GetMoment( ) - mmtContainerChangeTime >= ANIMATION_TIME )
	{
		if ( pLastContainer != nullptr )
			pWindow->RemoveObject( *pLastContainer ), pLastContainer = nullptr;

		mmtContainerChangeTime = 0;
	}
}

void CFunctionality::Run( )
{
	Pause( 2500ull );

	_LoginCode = AUTH.Login( );
	bConnected = true;
}

void CFunctionality::DrawLoop( )
{
	while ( !bExit )
	{
		if ( pApplicationWindow->PollInput( ) )
			continue;
		
		const auto mmtNow = GetMoment( );
		
		if ( bConnected 
			 && &pWaitingContainer == pCurrentContainer 
			 && _LogoAlphaTimer.GetRatio( ) <= 1.0 / FPS )
			ChangeCurrentContainer( pLoginCodeContainers[ _LoginCode ] ), bLogoFaded = true, pWaitingContainer->GetAlphaRatio( ) = 0.0;
		else if ( !bLogoFaded )
			pWaitingContainer->GetAlphaRatio( ) = _LogoAlphaTimer.GetRatio( ), IInteractable::UpdateContainerContents( pWaitingContainer );

		CheckContainerAnimation( );

		DRAW.BeginFrame( );
		_GUI.Draw( );
		DRAW.EndFrame( );

		const auto mmtDifference = GetMoment( ) - mmtNow;
		if ( mmtDifference > 1000.0 / FPS )
			continue;

		Pause( 1000.0 / 60.0 - mmtDifference );
	}
}
