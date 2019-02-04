/// PX Loader.cpp

#include "PX Precompiled.hpp"

#define PX_INSTANCE_ID L"Manager"
#include "PX Manager.hpp"

//void TestDebug( )
//{
//	auto print = string_cast< std::wstring >( "casted" );
//	dbg::out PX_DBG << PX_XOR( L"Hi" ) << dbg::newl;
//	dbg::out PX_ERR << PX_XOR( L"Mid-print" ) << dbg::newl;
//	dbg::out PX_WRN << PX_XOR( L"Mid-print 2" ) << dbg::newl;
//	dbg::out PX_SCS << PX_XOR( L"Bye" ) << dbg::newl;
//	dbg::out PX_LER << print << dbg::newl;
//}
//
//void TestInput( )
//{
//	dbg::out PX_DBG << PX_INPUT.GetKeyState( VK_LBUTTON );
//	Wait( 100 );
//}
//
//void Uncalled( )
//{
//	UI::Widgets::Inputbox< char* >( 20, new char[ 6 ] { "Hello" } );
//	UI::Widgets::Inputbox< int >( 20, new char[ 6 ] { "Hello" } );
//	UI::Widgets::Inputbox< float >( 20, new char[ 6 ] { "Hello" } );
//}
//
//void PX_API UI::Manager::SetLayout( )
//{
//	Example( );
//}
//
//void PX_API UIExample( )
//{
//	unsigned uDimensions[ 2 ] { 720, 600 };
//	Render::InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
//	UI::Manager::InitializeUI( PX_XOR( "Manager" ) );
//	while ( UI::Manager::Render( ) )
//		Wait( 1 );
//}
//
//void PX_API ConnectionExample( )
//{
//	Net::InitializeConnection( );
//	std::deque< Net::post_data_t > dqPostData;
//	
//	dqPostData.emplace_back( "test", R"()" );
//	const auto strResponse = Request( PX_XOR( "https://www.paladin-extensions.com:443/test.php/" ), dqPostData );
//	Net::CleanupConnection( );
//	dbg::out << strResponse.length( ) << dbg::newl;
//}
//
//void PX_API InjectionExample( )
//{
//	const auto pDLL = fopen( R"(C:\Users\Cole\Desktop\Messagebox.dll)", "rb" );
//
//	if ( !px_assert( pDLL != nullptr ) )
//		return;
//
//	fseek( pDLL, 0, SEEK_END );
//	const auto lSize = ftell( pDLL );
//	rewind( pDLL );
//	const auto pBuffer = VirtualAlloc( nullptr, lSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
//	fread( pBuffer, 1, lSize, pDLL );
//
//	if ( px_assert( lSize != 0 && pBuffer != nullptr ) )
//	{
//		sys::injection_info_t inj { };
//		Inject( pBuffer, L"ConsoleApplication1.exe", &inj );
//	}
//}

bool bLoggedIn = false, bShouldClose = false, bIsStaff = false, bPreferBeta = false;
int iSelectedExtension = -1, iLoginStatus = -1;
extensions_t extInfo;

const wstr_t wstrApplicationExecutableNames[ ] { { }, PX_XOR( L"Steam.exe" ), PX_XOR( L"csgo.exe" ), PX_XOR( L"pubg.exe" ), PX_XOR( L"rsix.exe" ) };
constexpr bool bExtensionDisabled[ PX_EXTENSION_MAX ] { true, true, false, true, true };
const str_t strExtensionNames[ PX_EXTENSION_MAX ] { { }, PX_XOR( "Manager" ), PX_XOR( "CSGO" ), PX_XOR( "PUBG" ), PX_XOR( "RSIX" ) },
		*strLastLaunchTimes;
bool bExtensionAccess[ PX_EXTENSION_MAX ] { false, false, false, false, false };
std::array< unsigned, 2 > uWindowDimensions;

void PX_API UI::Manager::SetLayout( )
{
	const auto fnClose = [ ]( )
	{
		ExitProcess( UINT_MAX );
	};

	const static D3DXVECTOR3 vecLogoPosition = { 0.f, 41.f, 0.f };
	static byte_t bLogoAlpha = 0, bCSGOAlpha = 0, bPUBGAlpha = 0;
	static auto bReverseColor = false;
	uWindowDimensions = GetCurrentWindowDimensions( );

	if ( !bLoggedIn && iLoginStatus == -1 ) // Connecting to server.
	{
		Header( PX_XOR( "Paladin Extensions" ), PX_XOR( "Manager" ), 600u, nullptr, fnClose );

		bLogoAlpha += bReverseColor ? -5 : 5;
		if ( bLogoAlpha == UCHAR_MAX || bLogoAlpha == 0 )
			bReverseColor = !bReverseColor;

		vecImageQueue.emplace_back( TEXTURE_LOGO_LOADING, vecLogoPosition, D3DCOLOR_ARGB( bLogoAlpha, bLogoAlpha, bLogoAlpha, bLogoAlpha ) );
	}
	else if ( !bLoggedIn && iLoginStatus > -1 ) // Error message
	{
		Header( PX_XOR( "Paladin Extensions" ), PX_XOR( "Manager" ), 600u, nullptr, fnClose );

		if ( bLogoAlpha != 255 )
		{
			bLogoAlpha += 5;
		}
		else
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
			auto vecTextSize = CalculateTextBounds( strErrorMessages[ iLoginStatus ].c_str( ), 30u );
			PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - vecTextSize.x / 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), unsigned( vecTextSize.x ), 30u );
			Text( strErrorMessages[ iLoginStatus ].c_str( ), clrErrorMessages[ iLoginStatus ] );
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
		vecImageQueue.emplace_back( TEXTURE_LOGO_LOADING, vecLogoPosition, D3DCOLOR_ARGB( bLogoAlpha, bLogoAlpha, bLogoAlpha, bLogoAlpha ) );
	}
	else
	{
		static const auto fnSetTabValue = [ ]( int &iCurrentValue, const int iNewValue )
		{
			iCurrentValue = iNewValue >= 0 ? iNewValue : iCurrentValue;
		};
		static auto bSetTabs = false;
		static auto iCurrentTab = 0;
		static std::deque< cstr_t > dqTabs;
		if ( !bSetTabs )
		{
			dqTabs.emplace_back( ICON_FA_SHARE_ALT_SQUARE "  EXTENSIONS" );
			if ( bIsStaff )
				dqTabs.emplace_back( ICON_FA_CODE_BRANCH "  DEVELOPER" ); // blank tab just to look COOL DXDXDXDXDXDXD
			bSetTabs = true;
		}

		const static links_t lnkSeparator
		{
			SLink( PX_XOR( "My Account" ), PX_XOR( "https://www.paladin-extensions.com/account/" ) ),
			SLink( PX_XOR( "Support" ), PX_XOR( "https://www.paladin-extensions.com/support/" ) ),
			SLink( PX_XOR( "Forum" ), PX_XOR( "https://www.paladin-extensions.com/" ) )
		};

		constexpr unsigned uImagePositions[ PX_EXTENSION_MAX ][ 2 ]
		{
			{ { }, { } },
			{ { }, { } },
			{ 47u, 190u },
			{ 162u, 190u },
			{ 277u, 190u }
		};

		bool bHoveringImage[ PX_EXTENSION_MAX ]
		{
			false,
			false,
			MouseHoveringRectangle( uImagePositions[ PX_EXTENSION_CSGO ][ 0 ], uImagePositions[ PX_EXTENSION_CSGO ][ 1 ], vecTextures[ TEXTURE_ICON_CSGO ].uWidth, vecTextures[ TEXTURE_ICON_CSGO ].uHeight ),
			MouseHoveringRectangle( uImagePositions[ PX_EXTENSION_PUBG ][ 0 ], uImagePositions[ PX_EXTENSION_PUBG ][ 1 ], vecTextures[ TEXTURE_ICON_PUBG ].uWidth, vecTextures[ TEXTURE_ICON_PUBG ].uHeight ),
			MouseHoveringRectangle( uImagePositions[ PX_EXTENSION_RSIX ][ 0 ], uImagePositions[ PX_EXTENSION_RSIX ][ 1 ], vecTextures[ TEXTURE_ICON_RSIX ].uWidth, vecTextures[ TEXTURE_ICON_RSIX ].uHeight )
		};

		static auto uSelectedExtension = PX_EXTENSION_CSGO;
		static auto bWasClicking = false;

		for ( auto u = 0u; u < PX_EXTENSION_MAX; u++ )
			if ( bHoveringImage[ u ] )
			{
				SetWidgetActive( CURSOR_HAND );
				if ( PX_INPUT.GetKeyState( VK_LBUTTON ) )
				{
					uSelectedExtension = u;
					bWasClicking = true;
				}
			}

		auto uHoverColor = D3DCOLOR_ARGB( 255 - bLogoAlpha, 255, 255, 255 ),
			 uDormantColor = D3DCOLOR_ARGB( 255 - bLogoAlpha, 200, 200, 200 );

		const static color_t clrText { 255, 255, 255, 255 },
							 clrGold { 255, 192, 0, 255 },
							 clrGreen { 32, 200, 32, 255 },
							 clrPurple { 192, 0, 255, 255 };

		Header( PX_XOR( "Paladin Extensions" ), PX_XOR( "Manager" ), 102u, nullptr, fnClose );

		if ( bLogoAlpha > 0u )
		{
			bLogoAlpha -= 5u;
			vecImageQueue.emplace_back( TEXTURE_LOGO_LOADING, vecLogoPosition, D3DCOLOR_ARGB( bLogoAlpha, bLogoAlpha, bLogoAlpha, bLogoAlpha ) );
		}

		fnSetTabValue( iCurrentTab, Tabs( 10, 0, dqTabs, iCurrentTab ) );
		Separator( 61, 65, 72, 100, &lnkSeparator );

		BeginGroupbox( 27, 153, 370, 160, PX_XOR( "Extensions" ) );
		{
			vecImageQueue.emplace_back( TEXTURE_ICON_CSGO, D3DXVECTOR3( float( uImagePositions[ PX_EXTENSION_CSGO ][ 0 ] ), float( uImagePositions[ PX_EXTENSION_CSGO ][ 1 ] ), 0.f ), bHoveringImage[ PX_EXTENSION_CSGO ] ? uHoverColor : uDormantColor );
			vecImageQueue.emplace_back( TEXTURE_ICON_PUBG, D3DXVECTOR3( float( uImagePositions[ PX_EXTENSION_PUBG ][ 0 ] ), float( uImagePositions[ PX_EXTENSION_PUBG ][ 1 ] ), 0.f ), bHoveringImage[ PX_EXTENSION_PUBG ] ? uHoverColor : uDormantColor );
			vecImageQueue.emplace_back( TEXTURE_ICON_RSIX, D3DXVECTOR3( float( uImagePositions[ PX_EXTENSION_RSIX ][ 0 ] ), float( uImagePositions[ PX_EXTENSION_RSIX ][ 1 ] ), 0.f ), bHoveringImage[ PX_EXTENSION_RSIX ] ? uHoverColor : uDormantColor );
		}
		EndGroupbox( );

		BeginGroupbox( 448, 180, 273, 160, ( strExtensionNames[ uSelectedExtension ] + PX_XOR( " Information" ) ).c_str( ) );
		{
			BeginRow( 15, 4, ROW_STATIC );
			SetRowWidth( 10 );
			Spacing( );
			JustifiedText( PX_XOR( "Status:" ), extInfo[ uSelectedExtension ].strStatus.c_str( ), clrText, clrGold, 240 );
			EndRow( );

			BeginRow( 15, 4, ROW_STATIC );
			SetRowWidth( 10 );
			Spacing( );
			JustifiedText( PX_XOR( "Next Update:" ), extInfo[ uSelectedExtension ].strEstimatedNextUpdate.c_str( ), clrText, clrGreen, 240 );
			EndRow( );

			BeginRow( 15, 4, ROW_STATIC );
			SetRowWidth( 10 );
			Spacing( );
			JustifiedText( PX_XOR( "Last Update:" ), extInfo[ uSelectedExtension ].strLastUpdate.c_str( ), clrText, clrGreen, 240 );
			EndRow( );

			BeginRow( 15, 4, ROW_STATIC );
			SetRowWidth( 10 );
			Spacing( );
			JustifiedText( PX_XOR( "Last Load:" ), strLastLaunchTimes[ uSelectedExtension ].c_str( ), clrText, clrGreen, 240 );
			EndRow( );

			BeginRow( 15, 4, ROW_STATIC );
			SetRowWidth( 10 );
			Spacing( );
			JustifiedText( PX_XOR( "Version:" ), extInfo[ uSelectedExtension ].strVersion.c_str( ), clrText, clrPurple, 240 );
			EndRow( );
		}
		EndGroupbox( );

		constexpr auto uColumnWidth = 217u;

		SetWidgetPosition( 30, 200 );

		BeginRow( 25, bIsStaff ? 6 : 4, ROW_STATIC );
		JustifiedText( PX_XOR( "Manager Version:" ), extInfo[ PX_EXTENSION_MANAGER ].strVersion.c_str( ), clrText, clrPurple, uColumnWidth - 8u );
		SetRowWidth( uColumnWidth );
		if ( Button( EPosition::CENTER, bExtensionAccess[ uSelectedExtension ] ? PX_XOR( "PURCHASED" ) : PX_XOR( "PURCHASE" ), false, bExtensionAccess[ uSelectedExtension ], bExtensionAccess[ uSelectedExtension ] ? PX_XOR( "You have purchased this extension." ) : PX_XOR( "Purchase this extension." ) ) )
			OpenLink( PX_XOR( "https://www.paladin-extensions.com/extensions/" ) );
		if ( bIsStaff )
			Checkbox( PX_XOR( "Prefer Beta" ), &bPreferBeta, PX_XOR( "If the beta is available, choose it over the regular build. Warning: The beta may be less stable." ) );
		EndRow( );

		SetFont( FNT_ROBOTO_BOLD_SMALL );
		BeginRow( 25u, 3, ROW_CUSTOM );

		const auto flBaseButtonPosition = float( uWindowDimensions[ 0 ] ) / 2.f;

		PushCustomRow( unsigned( flBaseButtonPosition - uColumnWidth * 3.f / 2.f - 33.f ), 0, uColumnWidth, 25u );
		if ( Button( EPosition::LEFT, PX_XOR( "MANAGER CHANGELOG" ), false, false, PX_XOR( "View the changelog for the manager." ) ) )
			OpenLink( PX_XOR( "https://www.paladin-extensions.com/extensions/1/updates/" ) );

		PushCustomRow( unsigned( flBaseButtonPosition - uColumnWidth / 2.f - 30.f ), 0, uColumnWidth, 25u );
		if ( Button( EPosition::CENTER, ( strExtensionNames[ uSelectedExtension ] + PX_XOR( " CHANGELOG" ) ).c_str( ), false, false, PX_XOR( "View the changelog for an extension." ) ) )
			OpenLink( ( PX_XOR( "https://www.paladin-extensions.com/extensions/" ) + std::to_string( uSelectedExtension ) + PX_XOR( "/updates/" ) ).c_str( ) );

		PushCustomRow( unsigned( flBaseButtonPosition + uColumnWidth / 2.f - 27.f ), 0, uColumnWidth, 25u );
		if ( Button( EPosition::RIGHT, ( PX_XOR( "LOAD " ) + strExtensionNames[ uSelectedExtension ] ).c_str( ), false,
					 !bExtensionAccess[ uSelectedExtension ] || bExtensionDisabled[ uSelectedExtension ], PX_XOR( "Load an extension." ) ) )
			iSelectedExtension = uSelectedExtension;

		EndRow( );

		bWasClicking = PX_INPUT.GetKeyState( VK_LBUTTON ) == true;
	}
}

void PX_API DrawWindow( )
{
	unsigned uDimensions[ 2 ] { 720, 435 };
	InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
	InitializeUI( PX_XOR( "Manager" ), false );

	while ( !bShouldClose )
	{
		const auto mmtStart = GetMoment( );
		if ( !UI::Manager::Render( ) )
			break;

		// todo vsync 1000ull / pDevMode.dmDisplayFrequency - ( GetMoment( ) - mmtStart )
		Wait( 1ull ); // Refresh the application at the speed of the monitor's refresh rate.
	}
}

void PX_API MonitorDetectionVectors( )
{
#if defined NDEBUG
	while ( iSelectedExtension == PX_EXTENSION_NONE && !bShouldClose )
	{
		for each ( auto wstrExecutable in wstrApplicationExecutableNames )
		{
			/*if ( !CheckForAnalysis( ) )
				Destroy( );
			else*/ if ( !wstrExecutable.empty( ) )
				TerminateProcess( GetProcessID( wstrExecutable ) );
		}
		Pause( 1500ull );
	}
#endif
}

HANDLE hStartThread;
HANDLE hStartProcess;

void PX_API OnDetach( )
{
	//Destroy( );
	// ideally, should never be called
}

void PX_API OnAttach( )
{
	// todo check hash to that of the servers.


	if( !EnsureElevation( ) )
		Popup( EMBType::FATAL_ERROR, PX_XOR( L"You must run the program as administrator." ) );
#if defined NDEBUG
	for each ( auto wstrExecutable in wstrApplicationExecutableNames )
		if ( !wstrExecutable.empty( ) )
			TerminateProcess( GetProcessID( wstrExecutable ) );
// review MAKE SURE TO UNCOMMENT THIS BEFORE RELEASING
	//if ( !CheckForAnalysis( ) )
	//	Destroy( );
#endif

	// We need the resources loaded for textures in the ui
	LoadResources( { } );

	std::thread tDraw( DrawWindow );
	tDraw.detach( );

#if defined NDEBUG
	/*std::thread( [ ]( )
	{
		while ( CheckForAnalysis( )
				&& ( ( iSelectedExtension == PX_EXTENSION_NONE && hStartProcess && hStartThread )
					 ? true : CheckForAnalysisEx( hStartProcess, &hStartThread, 1 ) ) )
			Pause( 1 );
		Request( PX_XOR( "https://www.paladin-extensions.com/ban.php" ), { } );
		if ( hStartProcess )
			CloseHandle( hStartProcess );
		if ( hStartThread )
			CloseHandle( hStartThread );
		Destroy( );
	} ).detach( );*/

	/*std::thread tMonitorDetectionVectors( MonitorDetectionVectors );
	tMonitorDetectionVectors.detach( );*/
#endif

	iLoginStatus = Login( bExtensionAccess );
	switch ( iLoginStatus )
	{
		case LOGIN_STAFF_SUCCESS:
			bIsStaff = true;

		case LOGIN_SUCCESS:
		{
			extInfo = ::Manager::RetrieveExtensionInformation( );
			strLastLaunchTimes = ::Manager::RetrieveLaunchInformation( );

			if ( extInfo.empty( ) )
			{
				iLoginStatus = LOGIN_CONNECTION_FAILURE;
				break;
			}

			for ( const auto &ext: extInfo )
				if ( !ext.bInitialized ) // issue getting info, connection error or someone has messed with the loader to get here and the php session hasn't started
				{
					iLoginStatus = LOGIN_CONNECTION_FAILURE;
					break;
				}
			if ( strLastLaunchTimes == nullptr )
			{
				iLoginStatus = LOGIN_CONNECTION_FAILURE;
				break;
			}

			bLoggedIn = true;
			while ( iSelectedExtension == PX_EXTENSION_NONE )
				Pause( 100 );

			bShouldClose = true;
			auto strEncryptedDLL = RequestExtension( iSelectedExtension, false );
			CleanupConnection( );

			DWORD dwProcessID { };
			do
			{
				if ( dwProcessID == 0ul )
					dwProcessID = GetProcessID( wstrApplicationExecutableNames[ iSelectedExtension ] );
				Pause( 10 );
			}
			while ( dwProcessID == 0ul
				|| !IsProcessThreadRunning( dwProcessID )
				|| !NecessaryModulesLoaded( dwProcessID ) );

			Wait( 15000i64 );
			auto strDLL = AssembleExtensionInformation( strEncryptedDLL );
			const auto sDLL = strDLL.size( );
			auto pBuffer = VirtualAlloc( nullptr, sDLL + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
			px_assert( pBuffer );
			memcpy( pBuffer, strDLL.c_str( ), sDLL );
			strEncryptedDLL.clear( );
			strDLL.clear( );

			// todo put safety here, check that everything is loading properly/return is success
			LoadRawLibraryEx( pBuffer, wstrApplicationExecutableNames[ iSelectedExtension ], new injection_info_t, &hStartProcess, &hStartThread );
			WipeMemory( pBuffer, sDLL );
			bShouldClose = true;
		}
		break;

		default:
			break;
	}

	while ( !bShouldClose )
		Pause( 10 );
	if ( hStartProcess )
		CloseHandle( hStartProcess );
	if ( hStartThread )
		CloseHandle( hStartThread );
}
