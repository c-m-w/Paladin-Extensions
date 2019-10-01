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

	pConnectionErrorNotificationTop = new CText( );
	pConnectionErrorNotificationTop->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pConnectionErrorNotificationTop->SetText( ENC( "There was an error connecting to the server." ) );
	pConnectionErrorNotificationTop->SetFont( FONT_ROBOTO );
	pConnectionErrorNotificationTop->SetWeight( WEIGHT_MEDIUM );
	pConnectionErrorNotificationTop->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::CONNECTION_ERROR ]->AddObject( pConnectionErrorNotificationTop, { pLoginCodeContainers[ ELoginCode::CONNECTION_ERROR ]->GetSize( ).x / 2.0 - PixelsToInches( pConnectionErrorNotificationTop->GetTextSize( ).x ) / 2.0, 1.0 } );

	pConnectionErrorNotificationBottom = new CText( );
	pConnectionErrorNotificationBottom->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pConnectionErrorNotificationBottom->SetText( ENC( "Please try again later and contact support if this issue persists." ) );
	pConnectionErrorNotificationBottom->SetFont( FONT_ROBOTO );
	pConnectionErrorNotificationBottom->SetWeight( WEIGHT_LIGHT );
	pConnectionErrorNotificationBottom->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::CONNECTION_ERROR ]->AddObject( pConnectionErrorNotificationBottom, { pLoginCodeContainers[ ELoginCode::CONNECTION_ERROR ]->GetSize( ).x / 2.0 - PixelsToInches( pConnectionErrorNotificationBottom->GetTextSize( ).x ) / 2.0, 1.0 + pConnectionErrorNotificationTop->GetSize( ).y + 0.05208333333 } );
	
	pServerErrorNotificationTop = new CText( );
	pServerErrorNotificationTop->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pServerErrorNotificationTop->SetText( ENC( "There was an error with the server." ) );
	pServerErrorNotificationTop->SetFont( FONT_ROBOTO );
	pServerErrorNotificationTop->SetWeight( WEIGHT_MEDIUM );
	pServerErrorNotificationTop->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::SERVER_ERROR ]->AddObject( pServerErrorNotificationTop, { pLoginCodeContainers[ ELoginCode::SERVER_ERROR ]->GetSize( ).x / 2.0 - PixelsToInches( pServerErrorNotificationTop->GetTextSize( ).x ) / 2.0, 1.0 } );

	pServerErrorNotificationBottom = new CText( );
	pServerErrorNotificationBottom->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pServerErrorNotificationBottom->SetText( ENC( "Please try again later and contact support if this issue persists." ) );
	pServerErrorNotificationBottom->SetFont( FONT_ROBOTO );
	pServerErrorNotificationBottom->SetWeight( WEIGHT_LIGHT );
	pServerErrorNotificationBottom->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::SERVER_ERROR ]->AddObject( pServerErrorNotificationBottom, { pLoginCodeContainers[ ELoginCode::SERVER_ERROR ]->GetSize( ).x / 2.0 - PixelsToInches( pServerErrorNotificationBottom->GetTextSize( ).x ) / 2.0, 1.0 + pServerErrorNotificationTop->GetSize( ).y + 0.05208333333 } );
	
	pBannedNotificationTop = new CText( );
	pBannedNotificationTop->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pBannedNotificationTop->SetText( ENC( "You are currently banned from Paladin Extensions." ) );
	pBannedNotificationTop->SetFont( FONT_ROBOTO );
	pBannedNotificationTop->SetWeight( WEIGHT_MEDIUM );
	pBannedNotificationTop->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::BANNED ]->AddObject( pBannedNotificationTop, { pLoginCodeContainers[ ELoginCode::BANNED ]->GetSize( ).x / 2.0 - PixelsToInches( pBannedNotificationTop->GetTextSize( ).x ) / 2.0, 1.0 } );

	pBannedNotificationBottom = new CText( );
	pBannedNotificationBottom->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pBannedNotificationBottom->SetText( ENC( "Please contact staff if you believe there to be an issue." ) );
	pBannedNotificationBottom->SetFont( FONT_ROBOTO );
	pBannedNotificationBottom->SetWeight( WEIGHT_LIGHT );
	pBannedNotificationBottom->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::BANNED ]->AddObject( pBannedNotificationBottom, { pLoginCodeContainers[ ELoginCode::BANNED ]->GetSize( ).x / 2.0 - PixelsToInches( pBannedNotificationBottom->GetTextSize( ).x ) / 2.0, 1.0 + pBannedNotificationTop->GetSize( ).y + 0.05208333333 } );
	
	pInvalidKeyNotificationTop = new CText( );
	pInvalidKeyNotificationTop->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pInvalidKeyNotificationTop->SetText( ENC( "Your license appears to be invalid." ) );
	pInvalidKeyNotificationTop->SetFont( FONT_ROBOTO );
	pInvalidKeyNotificationTop->SetWeight( WEIGHT_MEDIUM );
	pInvalidKeyNotificationTop->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::INVALID_KEY ]->AddObject( pInvalidKeyNotificationTop, { pLoginCodeContainers[ ELoginCode::INVALID_KEY ]->GetSize( ).x / 2.0 - PixelsToInches( pInvalidKeyNotificationTop->GetTextSize( ).x ) / 2.0, 1.0 } );

	pInvalidKeyNotificationBottom = new CText( );
	pInvalidKeyNotificationBottom->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pInvalidKeyNotificationBottom->SetText( ENC( "Please enter a purchase key below." ) );
	pInvalidKeyNotificationBottom->SetFont( FONT_ROBOTO );
	pInvalidKeyNotificationBottom->SetWeight( WEIGHT_LIGHT );
	pInvalidKeyNotificationBottom->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::INVALID_KEY ]->AddObject( pInvalidKeyNotificationBottom, { pLoginCodeContainers[ ELoginCode::INVALID_KEY ]->GetSize( ).x / 2.0 - PixelsToInches( pInvalidKeyNotificationBottom->GetTextSize( ).x ) / 2.0, 1.0 + pInvalidKeyNotificationTop->GetSize( ).y + 0.05208333333 } );

	pInvalidKeyInput = new CInputBox( );
	pInvalidKeyInput->AddFilter( CInputBox::FILTER_LETTERS );
	pInvalidKeyInput->AddFilter( CInputBox::FILTER_NUMERIC );
	pInvalidKeyInput->SetMaxLength( AUTH.PURCHASE_KEY_LENGTH );
	pInvalidKeyInput->SetSize( { 2.0, 0.26041666666 } );
	pLoginCodeContainers[ ELoginCode::INVALID_KEY ]->AddObject( pInvalidKeyInput, { pLoginCodeContainers[ ELoginCode::INVALID_KEY ]->GetSize( ).x / 2.0 - pInvalidKeyInput->GetSize( ).x / 2.0, pInvalidKeyNotificationBottom->GetLocation( ).y + pInvalidKeyNotificationBottom->GetSize( ).y + 0.05208333333 } );

	pInvalidKeyEnterKey = new CButton( );
	pInvalidKeyEnterKey->SetText( "continue" );
	pInvalidKeyEnterKey->GetCallbacks( ).AddCallback( [ & ]( CKeyState _State )
	{
		if ( _State && AUTH.CreateLicenseFile( pInvalidKeyInput->GetBuffer( ) ) )
			exit( -1 );

		return false;
	}, VK_LBUTTON );
	pLoginCodeContainers[ ELoginCode::INVALID_KEY ]->AddObject( pInvalidKeyEnterKey, { pLoginCodeContainers[ ELoginCode::INVALID_KEY ]->GetSize( ).x / 2.0 - pInvalidKeyEnterKey->GetSize( ).x / 2.0, pInvalidKeyInput->GetLocation( ).y + pInvalidKeyInput->GetSize( ).y + 0.05208333333 } );
	
	pInvalidHardwareNotificationTop = new CText( );
	pInvalidHardwareNotificationTop->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pInvalidHardwareNotificationTop->SetText( ENC( "Your hardware seems to have changed." ) );
	pInvalidHardwareNotificationTop->SetFont( FONT_ROBOTO );
	pInvalidHardwareNotificationTop->SetWeight( WEIGHT_MEDIUM );
	pInvalidHardwareNotificationTop->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::INVALID_HARDWARE ]->AddObject( pInvalidHardwareNotificationTop, { pLoginCodeContainers[ ELoginCode::INVALID_HARDWARE ]->GetSize( ).x / 2.0 - PixelsToInches( pInvalidHardwareNotificationTop->GetTextSize( ).x ) / 2.0, 1.0 } );

	pInvalidHardwareNotificationBottom = new CText( );
	pInvalidHardwareNotificationBottom->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pInvalidHardwareNotificationBottom->SetText( ENC( "Please create a support ticket." ) );
	pInvalidHardwareNotificationBottom->SetFont( FONT_ROBOTO );
	pInvalidHardwareNotificationBottom->SetWeight( WEIGHT_LIGHT );
	pInvalidHardwareNotificationBottom->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::INVALID_HARDWARE ]->AddObject( pInvalidHardwareNotificationBottom, { pLoginCodeContainers[ ELoginCode::INVALID_HARDWARE ]->GetSize( ).x / 2.0 - PixelsToInches( pInvalidHardwareNotificationBottom->GetTextSize( ).x ) / 2.0, 1.0 + pInvalidHardwareNotificationTop->GetSize( ).y + 0.05208333333 } );
	
	pLoginNotificationTop = new CText( );
	pLoginNotificationTop->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pLoginNotificationTop->SetText( ENC( "You have been successfully logged in." ) );
	pLoginNotificationTop->SetFont( FONT_ROBOTO );
	pLoginNotificationTop->SetWeight( WEIGHT_MEDIUM );
	pLoginNotificationTop->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::SUCCESS ]->AddObject( pLoginNotificationTop, { pLoginCodeContainers[ ELoginCode::SUCCESS ]->GetSize( ).x / 2.0 - PixelsToInches( pLoginNotificationTop->GetTextSize( ).x ) / 2.0, 1.0 } );

	pLoginNotificationBottom = new CText( );
	pLoginNotificationBottom->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
	pLoginNotificationBottom->SetText( ENC( "Please wait shortly." ) );
	pLoginNotificationBottom->SetFont( FONT_ROBOTO );
	pLoginNotificationBottom->SetWeight( WEIGHT_LIGHT );
	pLoginNotificationBottom->SetHeight( 1.0 / 6.0 );
	pLoginCodeContainers[ ELoginCode::SUCCESS ]->AddObject( pLoginNotificationBottom, { pLoginCodeContainers[ ELoginCode::SUCCESS ]->GetSize( ).x / 2.0 - PixelsToInches( pLoginNotificationBottom->GetTextSize( ).x ) / 2.0, 1.0 + pLoginNotificationTop->GetSize( ).y + 0.05208333333 } );

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
	pLoginCodeContainers[ ELoginCode::STAFF_SUCCESS ]->AddObject( pStaffLoginNotificationBottom, { pLoginCodeContainers[ ELoginCode::STAFF_SUCCESS ]->GetSize( ).x / 2.0 - PixelsToInches( pStaffLoginNotificationBottom->GetTextSize( ).x ) / 2.0, 1.0 + pStaffLoginNotificationTop->GetSize( ).y + 0.05208333333 } );

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
		pLastContainerLocation->IgnoreStateChanges( true );
		pLastContainerLocation->SetAnimationTime( ANIMATION_TIME );
		pLastContainerLocation->SetEaseType( ANIMATION_EASE_OUT );
		pLastContainerLocation->AnimateValue( { -LAUNCHER_WIDTH, 0.0 }, { } );
		( *pLastContainer )->AddAnimatedValue( pLastContainerLocation );

		pNextContainerLocation = new animated_value_t< vector2_t >( &( *pCurrentContainer )->GetRelativeLocation( ) );
		pNextContainerLocation->IgnoreStateChanges( true );
		pNextContainerLocation->SetAnimationTime( ANIMATION_TIME );
		pNextContainerLocation->SetEaseType( ANIMATION_EASE_IN );
		pNextContainerLocation->AnimateValue( { }, { LAUNCHER_WIDTH, 0.0 } );
		( *pCurrentContainer )->AddAnimatedValue( pNextContainerLocation );

		pNextContainerAlphaFade = new animated_value_t< double >( &( *pCurrentContainer )->GetAlphaRatio( ) );
		pNextContainerAlphaFade->IgnoreStateChanges( true );
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
	auto test = new CDrawable();
	test->Rectangle( { 0, 0, InchesToPixels( LAUNCHER_WIDTH ), InchesToPixels( LAUNCHER_HEIGHT ) }, 0xFF0000FF );
	
	while ( !bExit )
	{
		if ( pApplicationWindow->PollInput( ) )
			continue;
		
		const auto mmtNow = GetMoment( );

		if ( &pWaitingContainer == pCurrentContainer )
		{
			if ( bConnected 
			 && _LogoAlphaTimer.GetRatio( ) <= 1.0 / FPS )
				ChangeCurrentContainer( pLoginCodeContainers[ _LoginCode ] ), bLogoFaded = true, pWaitingContainer->GetAlphaRatio( ) = 0.0;
			else if ( !bLogoFaded )
				pWaitingContainer->GetAlphaRatio( ) = _LogoAlphaTimer.GetRatio( ), IInteractable::UpdateContainerContents( pWaitingContainer );
		}
		
		CheckContainerAnimation( );
		
		DRAW.BeginFrame( );
		_GUI.Draw( );
		//test->Draw();
		DRAW.EndFrame( );
		
		
		const auto mmtDifference = GetMoment( ) - mmtNow;
		if ( mmtDifference > 1000.0 / FPS )
			continue;

		Pause( 1000.0 / 60.0 - mmtDifference );
	}

	delete test;
}
