/// PX Installer.cpp

#include "PX Precompiled.hpp"

#define PX_INSTANCE_ID L"Installer"
#include "PX Installer.hpp"

const wstr_t wstrApplicationExecutableNames[ ] { { }, PX_XOR( L"Steam.exe" ), PX_XOR( L"csgo.exe" ), PX_XOR( L"pubg.exe" ), PX_XOR( L"rsix.exe" ) };

void PX_API MonitorDetectionVectors( )
{
#if defined NDEBUG
	DWORD dwBuffer;
	while ( !Functionality::bTerminating )
	{
		for each ( auto wstrExecutable in wstrApplicationExecutableNames )
		{
			if ( !CheckForAnalysis( ) )
				Destroy( );
			else if ( !wstrExecutable.empty( ) && ( dwBuffer = GetProcessID( wstrExecutable ) ) )
				TerminateProcess( dwBuffer );
		}
		Pause( 1500ull );
	}
#endif
}

void PX_API Manager::SetLayout( )
{
	const auto fnClose = [ ]( )
	{
		if ( !Popup( EMBType::QUERY,						 PX_XOR( L"Cancelling the installation will require a rollback of currently started changes."
						 "You can restart the installation at a later time.\n\n"
						 "Are you sure you would like to cancel the installation?" ) ) )
			return;

		Functionality::Rollback( );
		Functionality::bTerminating = true;
		ExitProcess( 0u );
	};

	auto uWindowDimensions = GetCurrentWindowDimensions( );

	Header( PX_XOR( "Paladin Extensions" ), PX_XOR( "Installer" ), 600u, nullptr, fnClose );
	if ( !Functionality::bLoggedIn && Functionality::iLoginStatus == -1 ) // Connecting to server.
	{
		const auto strLoading = PX_XOR( "Loading" );

		SetFont( FNT_ROBOTO_SMALL );
		BeginRow( 30u, 1u, ROW_CUSTOM );
		auto vecTextSize = CalculateTextBounds( strLoading, 30u );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - vecTextSize.x / 2.f ), unsigned( float( uWindowDimensions[ 1 ] / 3.f ) ), unsigned( vecTextSize.x ), 30u );
		Text( strLoading, { 220, 190, 5, 255 } );
		EndRow( );

		BeginRow( 30u, 3u, ROW_CUSTOM );
		constexpr auto uButtonWidth = 150u;
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - uButtonWidth * 3.f / 2.f - 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::LEFT, PX_XOR( "FORUM" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin-extensions.com/" ) );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - uButtonWidth / 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::CENTER, PX_XOR( "SUPPORT" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin-extensions.com/support/" ) );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f + uButtonWidth / 2.f + 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::RIGHT, PX_XOR( "EXTENSIONS" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin-extensions.com/extensions/" ) );
		EndRow( );
	}
	else if ( !Functionality::bLoggedIn && Functionality::iLoginStatus > -1 ) // Error message
	{
		const static str_t strErrorMessages[ ]
		{
			{ },
			PX_XOR( "Communication with the server has failed. Please try again later." ),
			PX_XOR( "The manager is outdated. Please download and reinstall the updated version." ),
			PX_XOR( "You are banned and may not access any extensions." ),
			PX_XOR( "Your hardware does not match previous records. Please submit a support ticket." ),
			PX_XOR( "You currently do not have any active subscriptions to any extensions." )
		};

		const static color_t clrErrorMessages[ ]
		{
			{ },
			{ 255, 0, 0, 255 },
			{ 190, 220, 5, 255 },
			{ 255, 0, 0, 255 },
			{ 190, 220, 5, 255 },
			{ 190, 220, 5, 255 }
		};

		SetFont( FNT_ROBOTO_SMALL );
		BeginRow( 30u, 1u, ROW_CUSTOM );
		auto vecTextSize = CalculateTextBounds( strErrorMessages[ Functionality::iLoginStatus ].c_str( ), 30u );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - vecTextSize.x / 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), unsigned( vecTextSize.x ), 30u );
		Text( strErrorMessages[ Functionality::iLoginStatus ].c_str( ), clrErrorMessages[ Functionality::iLoginStatus ] );
		EndRow( );

		BeginRow( 30u, 3u, ROW_CUSTOM );
		constexpr auto uButtonWidth = 150u;
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - uButtonWidth * 3.f / 2.f - 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::LEFT, PX_XOR( "FORUM" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin-extensions.com/" ) );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - uButtonWidth / 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::CENTER, PX_XOR( "SUPPORT" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin-extensions.com/support/" ) );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f + uButtonWidth / 2.f + 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::RIGHT, PX_XOR( "EXTENSIONS" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin-extensions.com/extensions/" ) );
		EndRow( );
	}
	else
	{
		static int iScreen = 1;
		switch ( iScreen )
		{
			case 1: // WARNING + EULA
			{
				static const cstr_t szWarningAndEULA[ 2 ][ 23 ] = {
					{
						PX_XOR( "* Warning *" ),
						PX_XOR( "\nThis computer program is protected by copyright law and international treaties. Unauthorized" ),
						PX_XOR( "\nduplication or distribution of this program, or any portion of it or its installation products, may" ),
						PX_XOR( "\nresult in severe civil or criminal penalties, and will be prosecuted to the maximum extent possible" ),
						PX_XOR( "\nunder the law.\n" ),
						PX_XOR( "\n* End-User License Agreement (EULA) of PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX *" ),
						PX_XOR( "\nThis End-User License Agreement (\"EULA\") is a legal agreement between you and Paladin Extensions." ),
						PX_XOR( "\nThis EULA governs your acquisition and use of our PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX" ),
						PX_XOR( "\nsoftware (\"Software\") directly from Paladin Extensions or indirectly through a Paladin Extensions" ),
						PX_XOR( "\nauthorized reseller or distributor (a \"Reseller\"). Please read this EULA carefully before completing the" ),
						PX_XOR( "\ninstallation process and using the PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX software. It" ),
						PX_XOR( "\nprovides a license to use the PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX software and contains" ),
						PX_XOR( "\nwarranty information and liability disclaimers.\n" ),
						PX_XOR( "\n* Acknowledgement and Agreement *" ),
						PX_XOR( "\nBy clicking \"accept\" or installing and/or using the PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX" ),
						PX_XOR( "\nsoftware, you are confirming your acceptance of the Software and agreeing to become bound by the terms" ),
						PX_XOR( "\nof this EULA. If you are entering into this EULA on behalf of a company or other legal entity, you" ),
						PX_XOR( "\nrepresent that you have the authority to bind such entity and its affiliates to these terms and" ),
						PX_XOR( "\nconditions. If you do not have such authority or if you do not agree with the terms and conditions of" ),
						PX_XOR( "\nthis EULA, do not install or use the Software, and you must not accept this EULA. This EULA shall apply" ),
						PX_XOR( "\nonly to the Software supplied by Paladin Extensions herewith regardless of whether other software is" ),
						PX_XOR( "\nreferred to or described herein. The terms also apply to any Paladin Extensions updates, supplements," ),
						PX_XOR( "\nInternet-based services, and support services for the Software, unless otherwise specified." )
					},
					{
						PX_XOR( "* License Grant *" ),
						PX_XOR( "\nPaladin Extensions hereby grants you a personal, non-transferable, non-exclusive licence to use the PX" ),
						PX_XOR( "\nInstaller, PX Manager, PX CSGO, PX PUBG, PX RSIX software on your device in accordance with the terms of" ),
						PX_XOR( "\nthis EULA. You are permitted to load the PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX software" ),
						PX_XOR( "\n(for example a PC, laptop, mobile or tablet) under your control. You are responsible for ensuring your" ),
						PX_XOR( "\ndevice meets the minimum requirements of the PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX software." ),
						PX_XOR( "\nYou are not permitted to:" ),
						PX_XOR( "\n- Edit, alter, modify, adapt, translate or otherwise change the whole or any part of the Software nor" ),
						PX_XOR( "\n  permit the whole or any part of the Software to be combined with or become incorporated in any other" ),
						PX_XOR( "\n  software, nor decompile, disassemble or reverse engineer the Software or attempt to do any such things" ),
						PX_XOR( "\n- Reproduce, copy, distribute, resell or otherwise use the Software for any purpose, commercial or personal" ),
						PX_XOR( "\n- Allow any third party to use the Software on behalf of or for the benefit of any third party" ),
						PX_XOR( "\n- Use the Software for any purpose that Paladin Extensions considers is a breach of this EULA\n" ),
						PX_XOR( "\n* Intellectual Property and Ownership *" ),
						PX_XOR( "\nPaladin Extensions shall at all times retain ownership of the Software as originally downloaded by you" ),
						PX_XOR( "\nand all subsequent downloads of the Software by you. The Software (and the copyright, and other" ),
						PX_XOR( "\nintellectual property rights of whatever nature in the Software, including any modifications made" ),
						PX_XOR( "\nthereto) are and shall remain the property of Paladin Extensions.\n" ),
						PX_XOR( "\n* Termination *" ),
						PX_XOR( "\nThis EULA will terminate immediately if you fail to comply with any term of this EULA. Upon such" ),
						PX_XOR( "\ntermination, the licenses granted by this EULA will immediately terminate and you agree to stop all" ),
						PX_XOR( "\naccess and use of the Software. The provisions that by their nature continue and survive will survive" ),
						PX_XOR( "\nany termination of this EULA.)" )
					}
				};
				SetFont( FNT_ENVY );
				static auto bShowNextPage = false;
				BeginRow( 30u, 1u, ROW_CUSTOM );
				PushCustomRow( 10, -7, uWindowDimensions[ 0 ] - 20u, uWindowDimensions[ 1 ] - 95 );
				if ( !bShowNextPage )
				{
					str_t str = "";
					for each ( auto cstr in szWarningAndEULA[ 0 ] )
						str += cstr;
					DisplayBox( str.c_str( ), str.length( ) );
					EndRow( );
					BeginRow( 25u, 2u, ROW_CUSTOM );
					PushCustomRow( 259u, 325u, 100u, 25u );
					Button( EPosition::LEFT, PX_XOR( "Previous Page" ), false, true, PX_XOR( "Return to the previous page of the EULA.") );
					PushCustomRow( 361u, 325u, 100u, 25u );
					if ( Button( EPosition::RIGHT, PX_XOR( "Next Page" ), false, false, PX_XOR( "Continue to the next page of the EULA." ) ) )
						bShowNextPage = true;
				}
				else
				{
					str_t str = "";
					for each ( auto cstr in szWarningAndEULA[ 1 ] )
						str += cstr;
					DisplayBox( str.c_str( ), str.length( ) );
					EndRow( );
					BeginRow( 25u, 2u, ROW_CUSTOM );
					PushCustomRow( 259u, 325u, 100u, 25u );
					if ( Button( EPosition::LEFT, PX_XOR( "Previous Page" ), false, false, PX_XOR( "Return to the previous page of the EULA." ) ) )
						bShowNextPage = false;
					PushCustomRow( 361u, 325u, 100u, 25u );
					Button( EPosition::RIGHT, PX_XOR( "Next Page" ), false, true, PX_XOR( "Continue to the next page of the EULA." ) );
				}
				EndRow( );

				BeginRow( 25u, 1u, ROW_CUSTOM );
				PushCustomRow( 611u, 295u, 100u, 25u );
				if ( Button( EPosition::NONE, PX_XOR( "Accept" ), false, !bShowNextPage, PX_XOR( "Accept the EULA." ) ) )
					iScreen = 2;
				break;
			}
			case 2:
			{
				if ( PathFileExists( ( PX_APPDATA + PX_XOR( LR"(\PX\data.px)" ) ).c_str( ) ) )
				{
					// check hash to our hash
					// if hash mismatch
					//		Something is already installed and an update is available!
					//		Functionality::strInstallDirectory = px\data.px
					//		update or uninstall?
					//		install()
					// else
					//		Something is already installed and at the latest version!
					//		Functionality::strInstallDirectory = px\data.px
					//		uninstall or reinstall?
					//		uninstall()  install()
					//
					// uninstall/update complete? restart. 
				}

				// * GET INSTALL DIRECTORY & DESIRED PRODUCTS
				Functionality::strInstallDirectory = "a";
				// You may only install this on type FAT drives!
				// * Opens the windows select directory garbage.
				// * Ensure that the direction has USN Journal disabled.

				// if everything checks out and is entered, iScreen = 3;
				break;
			}
			case 3:
			{
				// Please ensure that these selected preferences match!
				// - *Display directory
				Functionality::strInstallDirectory;
				// - Display size going to be taken
				// - Fonts to be installed
				// - Products to be installed

				// if they're okay with it, iScreen = 4;
				break;
			}
			case 4:
			{
				// PROGRESS BAR (uProgress)
				// You can cancel the installation by clicking the X button at the top left corner!

				// * install()
				break;
			}
			case 5:
			{
				// COMPLETE
				// The Manager is now fully installed.
				// restart 
				// * Checkbox to run manager.
				// * Checkbox to open website for first run support.
				break;
			}
		}
	}
}

void PX_API DrawWindow( )
{
	unsigned uDimensions[ 2 ] { 720, 450 };
	InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
	InitializeUI( PX_XOR( "Installer" ) );

	DEVMODE pDevMode { };
	EnumDisplaySettings( nullptr, ENUM_CURRENT_SETTINGS, &pDevMode );
	while ( !Functionality::bTerminating )
	{
		const auto mmtStart = GetMoment( );
		if ( !UI::Manager::Render( ) )
			break;

		// todo vsync 1000ull / pDevMode.dmDisplayFrequency - ( GetMoment( ) - mmtStart )
		Pause( 1ull ); // Refresh the application at the speed of the monitor's refresh rate.
	}
}

void PX_API OnLaunch( )
{
	// todo check hash to that of the servers.

	if ( !EnsureElevation( ) )
		Popup( EMBType::FATAL_ERROR, PX_XOR( L"You must run the program as administrator." ) );

	// do not uncomment, we use this for the previous install check
	//if ( !FileWrite( PX_APPDATA + PX_XOR( L"data.px" ), GetExecutableDirectory( ), false ) )
	//	return;

	std::thread tDraw( DrawWindow );
	tDraw.detach( );

#if defined NDEBUG
	if ( !CheckForAllAnalysis( ) )
		Request( PX_XOR( "https://www.paladin-extensions.com/ban.php" ), { } ),
		Destroy( );
	std::thread( [ ]( )
	{
		if ( !CheckForAllAnalysis( ) )
			Request( PX_XOR( "https://www.paladin-extensions.com/ban.php" ), { } ),
			Destroy( );

		while ( !CheckForAnalysis( ) )
			Pause( 1 );
		Request( PX_XOR( "https://www.paladin-extensions.com/ban.php" ), { } );
		Destroy( );
	} ).detach( );

	std::thread tMonitorDetectionVectors( MonitorDetectionVectors );
	tMonitorDetectionVectors.detach( );
#endif

	Functionality::iLoginStatus = Login( Functionality::bExtensionAccess );

	if ( Functionality::iLoginStatus == LOGIN_SUCCESS || Functionality::iLoginStatus == LOGIN_STAFF_SUCCESS )
		Functionality::bLoggedIn = true;

	while ( !Functionality::bTerminating )
		Pause( 100 );
	ExitProcess( 0 );
}
