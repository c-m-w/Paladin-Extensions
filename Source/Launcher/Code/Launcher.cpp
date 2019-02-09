/// Launcher.cpp

#include "Precompile.hpp"

#define WIN_ENTRY
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

constexpr auto LAUNCHER_WIDTH = 560.f,
LAUNCHER_HEIGHT = 260.f,
INPUT_WIDTH = 200.f;

void OnLaunch( )
{
	if ( !SetupFramework( ) )
		return;

	const auto _Code = /*AUTH.Login( )*/ ELoginCode::INVALID_LICENSE;
	if ( _Code != ELoginCode::LOGIN_SUCCESS
		 && _Code != ELoginCode::LOGIN_STAFF_SUCCESS )
	{
		auto pWindow = std::make_unique< CApplicationWindow >( CApplicationWindow( XOR( "Launcher" ), { LAUNCHER_WIDTH, LAUNCHER_HEIGHT }, GetModuleHandle( nullptr ) ) );
		DRAW.SetTarget( pWindow.get( ) );
		if ( !DRAW.Setup( ) )
			return;

		InitializeInterface( );

		auto bExit = false;
		auto wndCurrent = CWindow( CWindow::FLAG_WINDOW_MOVE_APPLICATION_WINDOW, rectangle_t( -1.f, -1.f, LAUNCHER_WIDTH + 1.f, LAUNCHER_HEIGHT + 1.f ), XOR( "Paladin Extensions" ), XOR( "Launcher" ), [ & ]( )
		{ }, [ & ]( )
		{
			bExit = true;
		}, pWindow.get( ) );

		AddWindow( &wndCurrent );

		switch( _Code )
		{
			case ELoginCode::INVALID_LICENSE:
			{
				constexpr auto fnTestKey = [ & ]( const std::string &strKey )
				{
					
				};
				static auto _Top = CLabel( padding_t( ), new text_t( XOR( "Your license does not exist locally or cannot be located." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
				static auto _Bottom = CLabel( padding_t( ), new text_t( XOR( "Please enter one of your purchase keys." ), EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE );
				static auto _Link = CLabel( padding_t( ), new text_t( XOR( "Click here to view your purchase keys." ), EFont::ROBOTO, SMALL_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, CLEAR, CLEAR, CLEAR, EFontFlags::NONE, [ & ]( )
				{
					OpenLink( XOR( "https://www.paladin-extensions.com/extensions/purchases" ) );
				} );
				static CInputBox _PurchaseKey;
				_PurchaseKey = CInputBox( padding_t( ), padding_t( 0.f, 5.f, 0.f, 5.f ), EFont::ENVY, CInputBox::ALPHANUMERIC, "", [ & ]( )
				{
					fnTestKey( _PurchaseKey.StringValue( ) );
				} );
				static auto _Submit = CButton( CButton::STANDALONE, XOR( "Submit" ), [ & ]( )
				{
					fnTestKey( _PurchaseKey.StringValue( ) );
				} );

				wndCurrent.AddRow( row_t( padding_t( 5.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
				wndCurrent.AddRow( row_t( padding_t( 5.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
				wndCurrent.AddRow( row_t( padding_t( 5.f, 0.f, 0.f, 0.f ), STANDARD_HEIGHT ) );
				wndCurrent.AddRow( row_t( padding_t( 5.f, 0.f, 0.f, LAUNCHER_WIDTH / 2.f - INPUT_WIDTH / 2.f ), 30.f ) );
				wndCurrent.AddRow( row_t( padding_t( 5.f, 0.f, 0.f, LAUNCHER_WIDTH / 2.f - INPUT_WIDTH / 2.f ), 25.f ) );
				wndCurrent.AddWidgetToRow( &_Top, LAUNCHER_WIDTH, 1 );
				wndCurrent.AddWidgetToRow( &_Bottom, LAUNCHER_WIDTH, 2 );
				wndCurrent.AddWidgetToRow( &_Link, LAUNCHER_WIDTH, 3 );
				wndCurrent.AddWidgetToRow( &_PurchaseKey, INPUT_WIDTH, 4 );
				wndCurrent.AddWidgetToRow( &_Submit, INPUT_WIDTH, 5 );
			}
			break;

			default:
				throw std::runtime_error( XOR( "This shouldn't have happened." ) );
		}

		while ( !bExit )
		{
			if ( pWindow->PollInput( ) )
				continue;

			if ( DRAW.BeginFrame( ) )
			{
				DrawWindows( );
				DRAW.EndFrame( );
			}

			Pause( );
		}

		pWindow.release( );
	}

	ShutdownFramework( );
}
