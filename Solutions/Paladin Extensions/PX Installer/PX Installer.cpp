/// PX Installer.cpp

#include "PX Precompiled.hpp"

#define PX_ENTRY_AS_WIN
#define PX_INSTANCE_ID L"Installer"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX Installer.hpp"

const wstr_t wstrApplicationExecutableNames[ ] { { }, PX_XOR( L"Steam.exe" ), PX_XOR( L"csgo.exe" ), PX_XOR( L"pubg.exe" ), PX_XOR( L"rsix.exe" ) };

void PX_API MonitorDetectionVectors( )
{
#if defined NDEBUG
	DWORD dwBuffer;
	while ( !bTerminating )
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
		if ( !Popup( EMBType::QUERY, PX_XOR( L"Cancelling the installation will require a rollback of currently started changes."
											 "You can restart the installation at a later time.\n\n"
											 "Are you sure you would like to cancel the installation?" ) ) )
			return;

		Functionality::Rollback( );
		ExitProcess( 0u );
	};

	auto uWindowDimensions = GetCurrentWindowDimensions( );

	Header( PX_XOR( "Paladin Extensions" ), PX_XOR( "Installer" ), 600u, nullptr, fnClose );
	if ( !Functionality::bLoggedIn && Functionality::iLoginStatus == -1 ) // Connecting to server.
	{
		const str_t strLoading = PX_XOR( "Loading" );

		SetFont( FONT_ROBOTOSMALL );
		BeginRow( 30u, 1u, ROW_CUSTOM );
		auto vecTextSize = CalculateTextBounds( strLoading.c_str( ), 30u );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - vecTextSize.x / 2.f ), unsigned( float( uWindowDimensions[ 1 ] / 3.f ) ), unsigned( vecTextSize.x ), 30u );
		Text( strLoading.c_str( ), { 190, 220, 5, 255 } );
		EndRow( );

		BeginRow( 30u, 3u, ROW_CUSTOM );
		constexpr auto uButtonWidth = 150u;
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - uButtonWidth * 3.f / 2.f - 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::LEFT, PX_XOR( "FORUM" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin.rip/" ) );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - uButtonWidth / 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::CENTER, PX_XOR( "SUPPORT" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin.rip/support/" ) );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f + uButtonWidth / 2.f + 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::RIGHT, PX_XOR( "EXTENSIONS" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin.rip/extensions/" ) );
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

		SetFont( FONT_ROBOTOSMALL );
		BeginRow( 30u, 1u, ROW_CUSTOM );
		auto vecTextSize = CalculateTextBounds( strErrorMessages[ Functionality::iLoginStatus ].c_str( ), 30u );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - vecTextSize.x / 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), unsigned( vecTextSize.x ), 30u );
		Text( strErrorMessages[ Functionality::iLoginStatus ].c_str( ), clrErrorMessages[ Functionality::iLoginStatus ] );
		EndRow( );

		BeginRow( 30u, 3u, ROW_CUSTOM );
		constexpr auto uButtonWidth = 150u;
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - uButtonWidth * 3.f / 2.f - 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::LEFT, PX_XOR( "FORUM" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin.rip/" ) );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - uButtonWidth / 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::CENTER, PX_XOR( "SUPPORT" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin.rip/support/" ) );
		PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f + uButtonWidth / 2.f + 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
		if ( Button( EPosition::RIGHT, PX_XOR( "EXTENSIONS" ), false, false ) )
			OpenLink( PX_XOR( "https://www.paladin.rip/extensions/" ) );
		EndRow( );
	}
	else
	{
		static int iScreen = 1;
		switch ( iScreen )
		{
			case 1: // WARNING + EULA
			{
				cstr_t szWarningAndEULA[ ] = { PX_XOR(
R"(WARNING: This computer program is protected by copyright law and international treaties. Unauthorized
duplication or distribution of this program, or any portion of it or its installation products, may
result in severe civil or criminal penalties, and will be prosecuted to the maximum extent possible
under the law.

* End-User License Agreement (EULA) of PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX *
This End-User License Agreement ("EULA") is a legal agreement between you and Paladin Extensions.
This EULA governs your acquisition and use of our PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX
software ("Software") directly from Paladin Extensions or indirectly through a Paladin Extensions
authorized reseller or distributor (a "Reseller"). Please read this EULA carefully before completing the
installation process and using the PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX software. It
provides a license to use the PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX software and contains
warranty information and liability disclaimers.

By clicking "accept" or installing and/or using the PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX
software, you are confirming your acceptance of the Software and agreeing to become bound by the terms
of this EULA. If you are entering into this EULA on behalf of a company or other legal entity, you
represent that you have the authority to bind such entity and its affiliates to these terms and
conditions. If you do not have such authority or if you do not agree with the terms and conditions of
this EULA, do not install or use the Software, and you must not accept this EULA. This EULA shall apply
only to the Software supplied by Paladin Extensions herewith regardless of whether other software is
referred to or described herein. The terms also apply to any Paladin Extensions updates, supplements,
Internet-based services, and support services for the Software, unless other terms accompany those
items on delivery. If so, those terms apply.)" ),
PX_XOR( R"(* License Grant *
Paladin Extensions hereby grants you a personal, non-transferable, non-exclusive licence to use the PX
Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX software on your device in accordance with the terms of this EULA.
You are permitted to load the PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX software (for example a PC, laptop, mobile or tablet) under your control. You are responsible for ensuring your device meets the minimum requirements of the PX Installer, PX Manager, PX CSGO, PX PUBG, PX RSIX software.
You are not permitted to:
- Edit, alter, modify, adapt, translate or otherwise change the whole or any part of the Software nor permit the whole or any part of the Software to be combined with or become incorporated in any other software, nor decompile, disassemble or reverse engineer the Software or attempt to do any such things
- Reproduce, copy, distribute, resell or otherwise use the Software for any purpose, commercial or personal
- Allow any third party to use the Software on behalf of or for the benefit of any third party
- Use the Software in any way which breaches any applicable local, national or international law
- Use the Software for any purpose that Paladin Extensions considers is a breach of this EULA

* Intellectual Property and Ownership *
Paladin Extensions shall at all times retain ownership of the Software as originally downloaded by you and all subsequent downloads of the Software by you. The Software (and the copyright, and other intellectual property rights of whatever nature in the Software, including any modifications made thereto) are and shall remain the property of Paladin Extensions.
Paladin Extensions reserves the right to grant licences to use the Software to third parties.

* Termination *
This EULA is effective from the date you first use the Software and shall continue until terminated. You may terminate it at any time upon written notice to Paladin Extensions.
It will also terminate immediately if you fail to comply with any term of this EULA. Upon such termination, the licenses granted by this EULA will immediately terminate and you agree to stop all access and use of the Software. The provisions that by their nature continue and survive will survive any termination of this EULA.

* Governing Law *
This EULA, and any dispute arising out of or in connection with this EULA, shall be governed by and construed in accordance with the laws of the United States of America.)" ) };
				auto uLength = strlen( szWarningAndEULA[ 0 ] );
				auto uLength2 = strlen( szWarningAndEULA[ 1 ] );
				SetFont( FONT_ENVY );
				static bool bShowNextPage = false;
				BeginRow( 30u, 1u, ROW_CUSTOM );
				PushCustomRow( 10u, 0u, uWindowDimensions[ 0 ] - 20u, uWindowDimensions[ 1 ] - 95 );
				if ( !bShowNextPage )
				{
					DisplayBox( szWarningAndEULA[ 0 ], uLength );
					EndRow( );
					BeginRow( 30u, 2u, ROW_CUSTOM );
					PushCustomRow( 10u, 100u, 100u, uWindowDimensions[ 1 ] - 90 );
					Button( EPosition::LEFT, PX_XOR( "Previous Page" ), false, true, PX_XOR( "Return to the previous page of the EULA.") );
					PushCustomRow( 110u, 100u, 10u, uWindowDimensions[ 1 ] - 90 );
					if ( Button( EPosition::LEFT, PX_XOR( "Next Page" ), false, false, PX_XOR( "Return to the previous page of the EULA." ) ) )
						bShowNextPage = true;
				}
				else
				{
					DisplayBox( szWarningAndEULA[ 1 ], uLength2 );
					EndRow( );
					BeginRow( 30u, 2u, ROW_CUSTOM );
					PushCustomRow( 10u, 100u, 100u, uWindowDimensions[ 1 ] - 90 );
					if ( Button( EPosition::LEFT, PX_XOR( "Previous Page" ), false, false, PX_XOR( "Return to the previous page of the EULA." ) ) )
						bShowNextPage = true;
					PushCustomRow( 110u, 100u, 10u, uWindowDimensions[ 1 ] - 90 );
					Button( EPosition::LEFT, PX_XOR( "Next Page" ), false, true, PX_XOR( "Return to the previous page of the EULA." ) );
				}
				EndRow( );

			// if button pressed, iScreen = 2;
				break;
			}
			case 2:
			{
				if ( PathFileExists( ( PX_APPDATA + PX_XOR( LR"(\PX\data.px)" ) ).c_str( ) ) )
				{
					// Something is already installed!
					// uninstall?
				}

				// * GET INSTALL DIRECTORY & DESIRED PRODUCTS
				// You may only install this on type FAT drives!
				// * Opens the windows select directory garbage.
				// * Ensure that the direction has USN Journal disabled.

				// if everything checks out and is entered, iScreen = 3;
			}
			case 3:
			{
				// Please ensure that these selected preferences match!
				// - *Display directory
				// - Display size going to be taken
				// - Fonts to be installed
				// - Products to be installed
			
				// if they're okay with it, iScreen = 4;
			}
			case 4:
			{
				// PROGRESS BAR
				// You can cancel the installation by clicking the X button at the top left corner!
				
				// * install()
			}
			case 5:
			{
				// COMPLETE
				// The Manager is now fully installed.
				// * Checkbox to run manager.
				// * Checkbox to open website for first run support.
			}
		}
	}
}

void PX_API DrawWindow( )
{
	unsigned uDimensions[ 2 ] { 720, 435 };
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

	if ( !FileWrite( PX_APPDATA + PX_XOR( L"data.px" ), GetExecutableDirectory( ), false ) )
		return;

	std::thread tDraw( DrawWindow );
	tDraw.detach( );

	// review MAKE SURE TO UNCOMMENT _NDEBUG THIS BEFORE RELEASING
#if defined _NDEBUG
	if ( !CheckForAllAnalysis( ) )
		Request( PX_XOR( "https://www.paladin.rip/ban.php" ), { } ),
		Destroy( );
	std::thread( [ ]( )
	{
		if ( !CheckForAllAnalysis( ) )
			Request( PX_XOR( "https://www.paladin.rip/ban.php" ), { } ),
			Destroy( );

		while ( !CheckForAnalysis( ) )
			Pause( 1 );
		Request( PX_XOR( "https://www.paladin.rip/ban.php" ), { } );
		Destroy( );
	} ).detach( );

	std::thread tMonitorDetectionVectors( MonitorDetectionVectors );
	tMonitorDetectionVectors.detach( );
#endif

	Functionality::iLoginStatus = Login( Functionality::bExtensionAccess );

	if ( Functionality::iLoginStatus == LOGIN_SUCCESS || Functionality::iLoginStatus == LOGIN_STAFF_SUCCESS )
		Functionality::bLoggedIn = true;

	while( !Functionality::bTerminating )
		Pause( 100 );
	ExitProcess( 0 );
}
