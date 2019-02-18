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
CLabel *_InvalidPurchaseKeyTop, *_InvalidPurchaseKeyCenter, *_InvalidPurchaseKeyBottom;
CButton *_InvalidPurchaseKeyKeys, *_InvalidPurchaseKeyClose, *_InvalidPurchaseKeySupport;
CPanel *_ConnectionError, *_ServerError, *_Banned, *_InvalidKey, *_InvalidHardware, *_Success;
CLabel *_ConnectionErrorTop, *_ConnectionErrorCenter, *_ConnectionErrorLink;
CLabel *_ServerErrorTop, *_ServerErrorCenter;
CLabel *_BannedText;
CLabel *_InvalidKeyText, *_InvalidKeyLink;
CInputBox *_InvalidKeyPurchaseKey;
CButton *_InvalidKeySubmit;
CLabel *_InvalidHardwareTop, *_InvalidHardwareLink;
CLabel *_SuccessTop, *_SuccessBottom;

bool SetupInterface( );

void OnLaunch( )
{
	if ( !SetupFramework( ) )
		return;

	if ( MEM.SetProcess( "csgo.exe", PROCESS_ALL_ACCESS ) )
	{
		std::string strData { };

		_Filesystem.ReadAbsoluteFile( R"(C:\Users\Cole\Desktop\DLL.dll)", strData, false );
		//MEM.LoadLibraryEx( R"(C:\Users\Cole\Documents\Visual Studio 2017\Projects\Test1\Release\Test1.dll)", true );
		MEM.ManuallyLoadLibraryEx( strData, true, true, true, true );
		//MEM.ManuallyLoadLibrary( strData );
	}

	ShutdownFramework( );

	constexpr auto fnAttemptLogin = [ ]( ELoginCode& _Result ) -> void
	{
		static CPanel* pnlToSet = nullptr;
		_Result = AUTH.Login( );
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

			case ELoginCode::SERVER_ERROR:
			{
				pnlToSet = _ServerError;
			}
			break;

			case ELoginCode::BANNED:
			{
				pnlToSet = _Banned;
			}
			break;

			case ELoginCode::INVALID_KEY:
			{
				pnlToSet = _InvalidKey;
			}
			break;

			case ELoginCode::INVALID_HARDWARE:
			{
				pnlToSet = _InvalidHardware;
			}
			break;

			case ELoginCode::SUCCESS:
			case ELoginCode::STAFF_SUCCESS:
			{
				pnlToSet = _Success;
			}
			break;

			default:
			{
				bExit = true;
				_Log.Log( EPrefix::ERROR, ELocation::APPLICATION, ENC( "Invalid login code received." ) ), throw std::runtime_error( ENC( "There has been an invalid response from the server." ) );
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
	_ServerError = new CPanel( padding_t( ), BACKGROUND_DARK );
	_Banned = new CPanel( padding_t( ), BACKGROUND_DARK );
	_InvalidKey = new CPanel( padding_t( ), BACKGROUND_DARK );
	_InvalidHardware = new CPanel( padding_t( ), BACKGROUND_DARK );
	_Success = new CPanel( padding_t( ), BACKGROUND_DARK );

	{
		pInvalidPurchaseKeyPopup = new CWindow( CWindow::POPUP_FLAGS, rectangle_t( 0.f, 0.f, POPUP_WIDTH, POPUP_HEIGHT ), ENC( "Error" ), ENC( "Invalid Key" ) );
		_InvalidPurchaseKeyTop = new CLabel( padding_t( ), new text_t( ENC( "There was an issue validating your purchase key." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_InvalidPurchaseKeyCenter = new CLabel( padding_t( ), new text_t( ENC( "Ensure the key you entered is valid." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_InvalidPurchaseKeyBottom = new CLabel( padding_t( ), new text_t( ENC( "Contact support if this issue persists." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_InvalidPurchaseKeyKeys = new CButton( CButton::LEFT, ENC( "Purchases" ), [ & ]( )
		{
			_SystemInformation.OpenLink( ENC( "https://www.paladin-extensions.com/extensions/purchases" ) );
		} );
		_InvalidPurchaseKeyClose = new CButton( CButton::CENTER, ENC( "Close" ), [ & ]( )
		{
			pErrorWindow->ClosePopup( false );
		} );
		_InvalidPurchaseKeySupport = new CButton( CButton::RIGHT, ENC( "Support" ), [ & ]( )
		{
			_SystemInformation.OpenLink( ENC( "https://www.paladin-extensions.com/support/" ) );
		} );

		pInvalidPurchaseKeyPopup->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		pInvalidPurchaseKeyPopup->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		pInvalidPurchaseKeyPopup->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		pInvalidPurchaseKeyPopup->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 32.f ), 30.f ) );
		pInvalidPurchaseKeyPopup->AddWidgetToRow( _InvalidPurchaseKeyTop, POPUP_WIDTH, 1 );
		pInvalidPurchaseKeyPopup->AddWidgetToRow( _InvalidPurchaseKeyCenter, POPUP_WIDTH, 2 );
		pInvalidPurchaseKeyPopup->AddWidgetToRow( _InvalidPurchaseKeyBottom, POPUP_WIDTH, 3 );
		pInvalidPurchaseKeyPopup->AddWidgetToRow( _InvalidPurchaseKeyKeys, 90.f, 4 );
		pInvalidPurchaseKeyPopup->AddWidgetToRow( _InvalidPurchaseKeyClose, 90.f, 4 );
		pInvalidPurchaseKeyPopup->AddWidgetToRow( _InvalidPurchaseKeySupport, 90.f, 4 );
	}

	{
		_ConnectionErrorTop = new CLabel( padding_t( ), new text_t( ENC( "Connection to the Paladin Extensions website failed." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_ConnectionErrorCenter = new CLabel( padding_t( ), new text_t( ENC( "Ensure there are no programs interfering with the connection and try again." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_ConnectionErrorLink = new CLabel( padding_t( ), new text_t( ENC( "If this issue persists, click here for support." ), EFont::ROBOTO, SMALL_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, CLEAR, CLEAR, CLEAR, EFontFlags::NONE, [ & ]( )
		{
			_SystemInformation.OpenLink( ENC( "https://www.paladin-extensions.com/support/" ) );
		} );

		_ConnectionError->AddRow( row_t( padding_t( 73.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_ConnectionError->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_ConnectionError->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_ConnectionError->AddWidgetToRow( _ConnectionErrorTop, LAUNCHER_WIDTH, 0 );
		_ConnectionError->AddWidgetToRow( _ConnectionErrorCenter, LAUNCHER_WIDTH, 1 );
		_ConnectionError->AddWidgetToRow( _ConnectionErrorLink, LAUNCHER_WIDTH, 2 );
	}

	{
		_ServerErrorTop = new CLabel( padding_t( ), new text_t( ENC( "There has been an error with the Paladin Extensions website." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_ServerErrorCenter = new CLabel( padding_t( ), new text_t( ENC( "Please notify a staff member as soon as possible." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );

		_ServerError->AddRow( row_t( padding_t( 73.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_ServerError->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_ServerError->AddWidgetToRow( _ServerErrorTop, LAUNCHER_WIDTH, 0 );
		_ServerError->AddWidgetToRow( _ServerErrorCenter, LAUNCHER_WIDTH, 1 );
	}

	{
		_BannedText = new CLabel( padding_t( ), new text_t( ENC( "You are banned and may not use Paladin Extensions' software." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );

		_Banned->AddRow( row_t( padding_t( 73.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_Banned->AddWidgetToRow( _BannedText, LAUNCHER_WIDTH, 0 );
	}

	{
		_InvalidKeyText = new CLabel( padding_t( ), new text_t( ENC( "Please enter one of your purchase keys." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_InvalidKeyLink = new CLabel( padding_t( ), new text_t( ENC( "Click here to view your purchase keys." ), EFont::ROBOTO, SMALL_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, CLEAR, CLEAR, CLEAR, EFontFlags::NONE, [ & ]( )
		{
			_SystemInformation.OpenLink( ENC( "https://www.paladin-extensions.com/extensions/purchases" ) );
		} );
		_InvalidKeyPurchaseKey = new CInputBox( padding_t( ), padding_t( 0.f, 5.f, 0.f, 5.f ), EFont::ENVY, CInputBox::ALPHANUMERIC, "", [ & ]( )
		{
			if ( !AUTH.CreateLicenseFile( _InvalidKeyPurchaseKey->StringValue( ) ) )
				pErrorWindow->Popup( pInvalidPurchaseKeyPopup );
			else
				bRetryConnection = true;
		} );
		_InvalidKeySubmit = new CButton( CButton::STANDALONE, ENC( "Submit" ), [ & ]( )
		{
			if ( !AUTH.CreateLicenseFile( _InvalidKeyPurchaseKey->StringValue( ) ) )
				pErrorWindow->Popup( pInvalidPurchaseKeyPopup );
			else
				bRetryConnection = true;
		} );

		_InvalidKey->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_InvalidKey->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_InvalidKey->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, LAUNCHER_WIDTH / 2.f - INPUT_WIDTH / 2.f ), 30.f ) );
		_InvalidKey->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, LAUNCHER_WIDTH / 2.f - INPUT_WIDTH / 2.f ), 25.f ) );
		_InvalidKey->AddWidgetToRow( _InvalidKeyText, LAUNCHER_WIDTH, 0 );
		_InvalidKey->AddWidgetToRow( _InvalidKeyLink, LAUNCHER_WIDTH, 1 );
		_InvalidKey->AddWidgetToRow( _InvalidKeyPurchaseKey, INPUT_WIDTH, 2 );
		_InvalidKey->AddWidgetToRow( _InvalidKeySubmit, INPUT_WIDTH, 3 );
	}

	{
		_InvalidHardwareTop = new CLabel( padding_t( ), new text_t( ENC( "There was an issue validating your hardware identity with the server." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_InvalidHardwareLink = new CLabel( padding_t( ), new text_t( ENC( "Click here to request a hardware identification reset." ), EFont::ROBOTO, SMALL_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, CLEAR, CLEAR, CLEAR, EFontFlags::NONE, [ & ]( )
		{
			_SystemInformation.OpenLink( ENC( "https://www.paladin-extensions.com/support/" ) );
		} );

		_InvalidHardware->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_InvalidHardware->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_InvalidHardware->AddWidgetToRow( _InvalidHardwareTop, LAUNCHER_WIDTH, 0 );
		_InvalidHardware->AddWidgetToRow( _InvalidHardwareLink, LAUNCHER_WIDTH, 1 );
	}

	{
		_SuccessTop = new CLabel( padding_t( ), new text_t( ENC( "You have been logged in successfully." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
		_SuccessBottom = new CLabel( padding_t( ), new text_t( ENC( "Please wait momentarily." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );

		_Success->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_Success->AddRow( row_t( padding_t( 10.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
		_Success->AddWidgetToRow( _SuccessTop, LAUNCHER_WIDTH, 0 );
		_Success->AddWidgetToRow( _SuccessBottom, LAUNCHER_WIDTH, 1 );
	}

	return true;
}
