/// Launcher.cpp

#include "Precompile.hpp"

#define WIN_ENTRY
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

constexpr auto LAUNCHER_WIDTH = 560.f,
LAUNCHER_HEIGHT = 260.f,
POPUP_WIDTH = 340.f,
POPUP_HEIGHT = 160.f,
INPUT_WIDTH = 200.f;
auto bExit = false, bRetryConnection = false;

CApplicationWindow *pApplicationWindow;
CWindow *pErrorWindow, *pInvalidPurchaseKeyPopup;
CLabel *_InvalidPurchaseKey;
CButton *_InvalidPurchaseKeyKeys, *_InvalidPurchaseKeyClose, *_InvalidPurchaseKeySupport;
CPanel *_ConnectionError, *_InvalidLicense, *_InvalidHardware;
CLabel *_ConnectionErrorTop, *_ConnectionErrorCenter, *_ConnectionErrorLink;
CLabel *_InvalidLicenseTop, *_InvalidLicenseCenter, *_InvalidLicenseLink;
CInputBox *_InvalidLicensePurchaseKey;
CButton *_InvalidLicenseSubmit;
CLabel *_InvalidHardwareTop, *_InvalidHardwareLink;

bool SetupInterface( );

void OnLaunch( )
{
	if ( !SetupFramework( ) )
		return;

	constexpr auto fnAttemptLogin = [ ]( ELoginCode& _Result ) -> void
	{
		static CPanel* pnlToSet = nullptr;
		_Result = /*AUTH.Login( )*/ ELoginCode::INVALID_LICENSE;
		bRetryConnection = false;

		if ( pnlToSet != nullptr )
		{
			pErrorWindow->ClearRow( 1 );
		}

		switch( _Result )
		{
			case ELoginCode::CONNECTION_ERROR:
			{
				pnlToSet = _ConnectionError;
			}
			break;

			case ELoginCode::INVALID_LICENSE:
			{
				pnlToSet = _InvalidLicense;
			}
			break;

			case ELoginCode::INVALID_HARDWARE:
			{
				pnlToSet = _InvalidHardware;
			}
			break;

			case ELoginCode::LOGIN_SUCCESS:
			case ELoginCode::LOGIN_STAFF_SUCCESS:
				return;

			default:
			{
				bExit = true;
				_Log.Log( EPrefix::ERROR, ELocation::APPLICATION, ENC( "Invalid login code received." ) );
			}
		}

		pErrorWindow->AddWidgetToRow( pnlToSet, LAUNCHER_WIDTH, 1 );
		pApplicationWindow->Show( );

		while ( !bExit && !bRetryConnection )
		{
			if ( pApplicationWindow->PollInput( ) )
				continue;

			if ( DRAW.BeginFrame( ) )
			{
				DrawWindows( );
				DRAW.EndFrame( );
			}

			Pause( );
		}
	};

	ELoginCode _Result;
	
	SetupInterface( );
	
	do
	{
		fnAttemptLogin( _Result );
	} while ( !bExit && bRetryConnection );

	ShutdownFramework( );
}

bool SetupInterface( )
{
	pApplicationWindow = new CApplicationWindow( ENC( "Launcher" ), { LAUNCHER_WIDTH, LAUNCHER_HEIGHT }, GetModuleHandle( nullptr ) );
	pApplicationWindow->Hide( );
	DRAW.SetTarget( pApplicationWindow );
	if ( !_Drawing.Setup( ) )
		return false;

	InitializeInterface( );

	pErrorWindow = new CWindow( CWindow::FLAG_WINDOW_ANCHOR, rectangle_t( -1.f, -1.f, LAUNCHER_WIDTH + 1.f, LAUNCHER_HEIGHT + 1.f ), ENC( "Paladin Extensions" ), ENC( "Launcher" ), [ & ]( )
	{ }, [ & ]( )
	{
		bExit = true;
	}, pApplicationWindow );

	AddWindow( pErrorWindow );

	pErrorWindow->AddRow( row_t( padding_t( ), LAUNCHER_HEIGHT ) );

	_ConnectionError = new CPanel( padding_t( ), BACKGROUND_DARK );
	_InvalidLicense = new CPanel( padding_t( ), BACKGROUND_DARK );
	_InvalidHardware = new CPanel( padding_t( ), BACKGROUND_DARK );

	{
		pInvalidPurchaseKeyPopup = new CWindow( CWindow::POPUP_FLAGS, rectangle_t( 0.f, 0.f, POPUP_WIDTH, POPUP_HEIGHT ), ENC( "Error" ), ENC( "Invalid Key" ) );
		_InvalidPurchaseKey = new CLabel( padding_t( ), new text_t( ENC( "You have entered an invalid purchase key." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_InvalidPurchaseKeyKeys = new CButton( CButton::LEFT, ENC( "Purchases" ), [ & ]( )
		{
			OpenLink( ENC( "https://www.paladin-extensions.com/extensions/purchases" ) );
		} );
		_InvalidPurchaseKeyClose = new CButton( CButton::CENTER, ENC( "Close" ), [ & ]( )
		{
			pErrorWindow->ClosePopup( false );
		} );
		_InvalidPurchaseKeySupport = new CButton( CButton::RIGHT, ENC( "Support" ), [ & ]( )
		{
			OpenLink( ENC( "https://www.paladin-extensions.com/support/" ) );
		} );

		pInvalidPurchaseKeyPopup->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		pInvalidPurchaseKeyPopup->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 32.f ), 30.f ) );
		pInvalidPurchaseKeyPopup->AddWidgetToRow( _InvalidPurchaseKey, POPUP_WIDTH, 1 );
		pInvalidPurchaseKeyPopup->AddWidgetToRow( _InvalidPurchaseKeyKeys, 90.f, 2 );
		pInvalidPurchaseKeyPopup->AddWidgetToRow( _InvalidPurchaseKeyClose, 90.f, 2 );
		pInvalidPurchaseKeyPopup->AddWidgetToRow( _InvalidPurchaseKeySupport, 90.f, 2 );
	}

	{
		_ConnectionErrorTop = new CLabel( padding_t( ), new text_t( ENC( "Connection to the Paladin Extensions website failed." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_ConnectionErrorCenter = new CLabel( padding_t( ), new text_t( ENC( "Ensure there is no program interfering with the connection and try again." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_ConnectionErrorLink = new CLabel( padding_t( ), new text_t( ENC( "If this issue persists, click here for support." ), EFont::ROBOTO, SMALL_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, CLEAR, CLEAR, CLEAR, EFontFlags::NONE, [ & ]( )
		{
			OpenLink( ENC( "https://www.paladin-extensions.com/support/" ) );
		} );

		_ConnectionError->AddRow( row_t( padding_t( 73.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_ConnectionError->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_ConnectionError->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_ConnectionError->AddWidgetToRow( _ConnectionErrorTop, LAUNCHER_WIDTH, 0 );
		_ConnectionError->AddWidgetToRow( _ConnectionErrorCenter, LAUNCHER_WIDTH, 1 );
		_ConnectionError->AddWidgetToRow( _ConnectionErrorLink, LAUNCHER_WIDTH, 2 );
	}

	{
		_InvalidLicenseTop = new CLabel( padding_t( ), new text_t( ENC( "Your license does not exist locally or cannot be located." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_InvalidLicenseCenter = new CLabel( padding_t( ), new text_t( ENC( "Please enter one of your purchase keys." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_InvalidLicenseLink = new CLabel( padding_t( ), new text_t( ENC( "Click here to view your purchase keys." ), EFont::ROBOTO, SMALL_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, CLEAR, CLEAR, CLEAR, EFontFlags::NONE, [ & ]( )
		{
			OpenLink( ENC( "https://www.paladin-extensions.com/extensions/purchases" ) );
		} );
		_InvalidLicensePurchaseKey = new CInputBox( padding_t( ), padding_t( 0.f, 5.f, 0.f, 5.f ), EFont::ENVY, CInputBox::ALPHANUMERIC, "", [ & ]( )
		{
			if ( !AUTH.CreateLicenseFile( _InvalidLicensePurchaseKey->StringValue( ) ) )
				pErrorWindow->Popup( pInvalidPurchaseKeyPopup );

			bRetryConnection = true;
		} );
		_InvalidLicenseSubmit = new CButton( CButton::STANDALONE, ENC( "Submit" ), [ & ]( )
		{
			if ( !AUTH.CreateLicenseFile( _InvalidLicensePurchaseKey->StringValue( ) ) )
				pErrorWindow->Popup( pInvalidPurchaseKeyPopup );

			bRetryConnection = true;
		} );

		_InvalidLicense->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_InvalidLicense->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_InvalidLicense->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_InvalidLicense->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, LAUNCHER_WIDTH / 2.f - INPUT_WIDTH / 2.f ), 30.f ) );
		_InvalidLicense->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, LAUNCHER_WIDTH / 2.f - INPUT_WIDTH / 2.f ), 25.f ) );
		_InvalidLicense->AddWidgetToRow( _InvalidLicenseTop, LAUNCHER_WIDTH, 0 );
		_InvalidLicense->AddWidgetToRow( _InvalidLicenseCenter, LAUNCHER_WIDTH, 1 );
		_InvalidLicense->AddWidgetToRow( _InvalidLicenseLink, LAUNCHER_WIDTH, 2 );
		_InvalidLicense->AddWidgetToRow( _InvalidLicensePurchaseKey, INPUT_WIDTH, 3 );
		_InvalidLicense->AddWidgetToRow( _InvalidLicenseSubmit, INPUT_WIDTH, 4 );
	}

	{
		_InvalidHardwareTop = new CLabel( padding_t( ), new text_t( ENC( "There was an issue validating your hardware identity with the server." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_InvalidHardwareLink = new CLabel( padding_t( ), new text_t( ENC( "Click here to request a hardware identification reset." ), EFont::ROBOTO, SMALL_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, CLEAR, CLEAR, CLEAR, EFontFlags::NONE, [ & ]( )
		{
			OpenLink( ENC( "https://www.paladin-extensions.com/support/" ) );
		} );

		_InvalidHardware->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_InvalidHardware->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_InvalidHardware->AddWidgetToRow( _InvalidHardwareTop, LAUNCHER_WIDTH, 0 );
		_InvalidHardware->AddWidgetToRow( _InvalidHardwareLink, LAUNCHER_WIDTH, 1 );
	}

	return true;
}
