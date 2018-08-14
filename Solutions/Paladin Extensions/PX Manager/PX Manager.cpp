/// PX Loader.cpp

#define PX_ENTRY_AS_DLL
#define PX_INSTANCE_ID L"Manager"
#include <Jeremia-h/Entry Manager.hpp>

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
//	UI::Manager::Initialize( PX_XOR( "Manager" ) );
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
//	const auto strResponse = Request( PX_XOR( "https://www.paladin.rip:443/test.php" ), dqPostData );
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

const std::wstring wstrApplicationExecutableNames[ ] { { }, PX_XOR( L"Steam.exe" ), PX_XOR( L"csgo.exe" ), PX_XOR( L"pubg.exe" ), PX_XOR( L"rsix.exe" ) };
constexpr bool bExtensionDisabled[ PX_EXTENSION_MAX ] { true, true, false, true, true };
const std::string strExtensionNames[ PX_EXTENSION_MAX ] { { }, PX_XOR( "Manager" ), PX_XOR( "CSGO" ), PX_XOR( "PUBG" ), PX_XOR( "RSIX" ) },
*strLastLaunchTimes;

using namespace UI::Widgets;

void PX_API UI::Manager::SetLayout( )
{
	const auto fnClose = [ ]( )
	{
		exit( -1 );
	};

	static byte_t bLogoAlpha = 0, bCSGOAlpha = 0, bPUBGAlpha = 0;
	static auto bReverseColor = false;
	auto uWindowDimensions = GetCurrentWindowDimensions( );

	if ( !bLoggedIn && iLoginStatus == -1 ) /// Connecting to server.
	{
		Header( PX_XOR( "Paladin Extensions" ), PX_XOR( "Manager" ), 600u, nullptr, fnClose );

		bLogoAlpha += bReverseColor ? -5 : 5;
		if ( bLogoAlpha == UCHAR_MAX || bLogoAlpha == 0 )
			bReverseColor = !bReverseColor;

		vecImageQueue.emplace_back( TEXTURE_LOGO_LOADING, D3DXVECTOR3( float( uWindowDimensions[ 0 ] ) / 2.f - float( vecTextures[ TEXTURE_LOGO_LOADING ].uWidth ) / 2.f,
																	   float( uWindowDimensions[ 1 ] ) / 2.f - float( vecTextures[ TEXTURE_LOGO_LOADING ].uHeight ) / 2.f, 0.f ),
									D3DCOLOR_ARGB( bLogoAlpha, bLogoAlpha, bLogoAlpha, bLogoAlpha ) );
	}
	else if ( !bLoggedIn && iLoginStatus > -1 ) /// Error message
	{
		Header( PX_XOR( "Paladin Extensions" ), PX_XOR( "Manager" ), 600u, nullptr, fnClose );

		if ( bLogoAlpha != 255 )
		{
			bLogoAlpha += 5;
		}
		else
		{
			const static std::string strErrorMessages[ ]
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
			auto vecTextSize = CalculateTextBounds( strErrorMessages[ iLoginStatus ].c_str( ), 30u );
			PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - vecTextSize.x / 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), unsigned( vecTextSize.x ), 30u );
			Text( strErrorMessages[ iLoginStatus ].c_str( ), clrErrorMessages[ iLoginStatus ] );
			EndRow( );

			BeginRow( 30u, 3u, ROW_CUSTOM );
			constexpr auto uButtonWidth = 150u;
			PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - uButtonWidth * 3.f / 2.f - 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
			if ( Button( EPosition::LEFT, PX_XOR( "FORUM" ), false ) )
				OpenLink( PX_XOR( "https://www.paladin.rip/" ) );
			PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f - uButtonWidth / 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
			if ( Button( EPosition::CENTER, PX_XOR( "SUPPORT" ), false ) )
				OpenLink( PX_XOR( "https://www.paladin.rip/support/" ) );
			PushCustomRow( unsigned( float( uWindowDimensions[ 0 ] ) / 2.f + uButtonWidth / 2.f + 2.f ), unsigned( float( uWindowDimensions[ 1 ] ) - 140.f ), uButtonWidth, 30u );
			if ( Button( EPosition::RIGHT, PX_XOR( "EXTENSIONS" ), false ) )
				OpenLink( PX_XOR( "https://www.paladin.rip/extensions/" ) );
			EndRow( );
		}
		vecImageQueue.emplace_back( TEXTURE_LOGO_LOADING, D3DXVECTOR3( float( uWindowDimensions[ 0 ] ) / 2.f - float( vecTextures[ TEXTURE_LOGO_LOADING ].uWidth ) / 2.f,
																	   float( uWindowDimensions[ 1 ] ) / 2.f - float( vecTextures[ TEXTURE_LOGO_LOADING ].uHeight ) / 2.f, 0.f ),
									D3DCOLOR_ARGB( bLogoAlpha, bLogoAlpha, bLogoAlpha, bLogoAlpha ) );
	}
	else
	{
		static const auto fnSetTabValue = [ ]( int& iCurrentValue, const int iNewValue )
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
			SLink( PX_XOR( "My Account" ), PX_XOR( "https://www.paladin.rip/account/" ) ),
			SLink( PX_XOR( "Support" ), PX_XOR( "https://www.paladin.rip/support/" ) ),
			SLink( PX_XOR( "Forum" ), PX_XOR( "https://www.paladin.rip/" ) )
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
				SetWidgetActive( Render::CURSOR_HAND );
				if ( PX_INPUT.GetKeyState( VK_LBUTTON ) && !bExtensionDisabled[ u ] )
				{
					uSelectedExtension = u;
					bWasClicking = true;
				}
			}

		constexpr auto uHoverColor = D3DCOLOR_ARGB( 255, 255, 255, 255 ),
			uDormantColor = D3DCOLOR_ARGB( 200, 200, 200, 200 );

		const static color_t clrText { 255, 255, 255, 255 },
			clrGold { 255, 192, 0, 255 },
			clrGreen { 32, 200, 32, 255 },
			clrPurple { 192, 0, 255, 255 };

		Header( PX_XOR( "Paladin Extensions" ), PX_XOR( "Manager" ), 102u, nullptr, fnClose );

		if ( bLogoAlpha > 0 )
		{
			bLogoAlpha -= 5;
			vecImageQueue.emplace_back( TEXTURE_LOGO_LOADING, D3DXVECTOR3( float( uWindowDimensions[ 0 ] ) / 2.f - float( vecTextures[ TEXTURE_LOGO_LOADING ].uWidth ) / 2.f,
																		   float( uWindowDimensions[ 1 ] ) / 2.f - float( vecTextures[ TEXTURE_LOGO_LOADING ].uHeight ) / 2.f, 0.f ),
										D3DCOLOR_ARGB( bLogoAlpha, bLogoAlpha, bLogoAlpha, bLogoAlpha ) );
			return;
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
		JustifiedText( PX_XOR( "Manager Version:" ), extInfo[ PX_EXTENSION_MANAGER ].strVersion.c_str( ), clrText, clrPurple, uColumnWidth - 5u );
		SetRowWidth( uColumnWidth - 5u );
		Spacing( );
		if ( bIsStaff )
			Checkbox( PX_XOR( "Prefer Beta" ), &bPreferBeta, PX_XOR( "If the beta is available, choose it over the regular build. Warning: The beta may be less stable." ) );
		EndRow( );

		SetFont( FONT_ROBOTOBOLDSMALL );
		BeginRow( 25u, 3, ROW_CUSTOM );

		auto flBaseButtonPosition = float( uWindowDimensions[ 0 ] ) / 2.f;

		PushCustomRow( unsigned( flBaseButtonPosition - uColumnWidth * 3.f / 2.f - 33.f ), 0, uColumnWidth, 25u );
		if ( Button( EPosition::LEFT, PX_XOR( "MANAGER CHANGELOG" ), false, PX_XOR( "View the changelog for the manager." ) ) )
			OpenLink( PX_XOR( "https://www.paladin.rip/extensions/1/updates/" ) );

		PushCustomRow( unsigned( flBaseButtonPosition - uColumnWidth / 2.f - 30.f ), 0, uColumnWidth, 25u );
		if ( Button( EPosition::CENTER, ( strExtensionNames[ uSelectedExtension ] + PX_XOR( " CHANGELOG" ) ).c_str( ), false, PX_XOR( "View the changelog for an extension." ) ) )
			OpenLink( ( PX_XOR( "https://www.paladin.rip/extensions/" ) + std::to_string( uSelectedExtension ) + PX_XOR( "/updates/" ) ).c_str( ) );

		PushCustomRow( unsigned( flBaseButtonPosition + uColumnWidth / 2.f - 27.f ), 0, uColumnWidth, 25u );
		if ( Button( EPosition::RIGHT, ( PX_XOR( "LOAD " ) + strExtensionNames[ uSelectedExtension ] ).c_str( ), false, PX_XOR( "Load an extension." ) ) )
			iSelectedExtension = uSelectedExtension;

		EndRow( );

		bWasClicking = PX_INPUT.GetKeyState( VK_LBUTTON );
	}
}

void PX_API UI::Manager::DrawOther( )
{
	std::deque< vertex_t > vtxVertices;
	PX_DEF dwColor = D3DCOLOR_ARGB( 255, 255, 255, 255 );
	vtxVertices.emplace_back( 0, 0, dwColor );
	vtxVertices.emplace_back( 100, 0, dwColor );
	vtxVertices.emplace_back( 0, 100, dwColor );
	vtxVertices.emplace_back( 100, 100, dwColor );
	Drawing::Polygon( vtxVertices );
}

void PX_API Draw( )
{
	unsigned uDimensions[ 2 ] { 720, 435 };
	Render::InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
	UI::Manager::Initialize( PX_XOR( "Manager" ) );

	DEVMODE pDevMode;
	EnumDisplaySettings( nullptr, ENUM_CURRENT_SETTINGS, &pDevMode );
	while ( !bShouldClose )
	{
		const auto mmtStart = GetMoment( );
		if ( !UI::Manager::Render( ) )
			break;

		Wait( 1000ull / pDevMode.dmDisplayFrequency - ( GetMoment( ) - mmtStart ) ); // Refresh the application at the speed of the monitor's refresh rate.
	}
}

void PX_API MonitorDetectionVectors( )
{
	while ( iSelectedExtension == PX_EXTENSION_NONE && !bShouldClose )
	{
		for each ( auto wstrExecutable in wstrApplicationExecutableNames )
			if ( !wstrExecutable.empty( ) )
				sys::TerminateProcess( sys::GetProcessID( wstrExecutable ) );
		Wait( 1500ull );
	}
}

void PX_API OnAttach( )
{
	for each ( auto wstrExecutable in wstrApplicationExecutableNames )
		if ( !wstrExecutable.empty( ) )
			sys::TerminateProcess( sys::GetProcessID( wstrExecutable ) );

	// We need the resources loaded for textures in the ui
	Files::Resources::LoadResources( { } );

	std::thread tDraw( Draw );
	tDraw.detach( );

	std::thread tSentinal( MonitorDetectionVectors );
	tSentinal.detach( );

	// wait 1 sec so that our cool loading animation has some time to play :D
	Wait( rand( ) % 1900 + 100 );

	iLoginStatus = Net::Login( );
	switch ( iLoginStatus )
	{
		case Net::LOGIN_STAFF_SUCCESS:
			bIsStaff = true;

		case Net::LOGIN_SUCCESS:
		{
			extInfo = Manager::RetrieveExtensionInformation( );
			strLastLaunchTimes = Manager::RetrieveLaunchInformation( );

			if ( extInfo.empty( ) )
			{
				iLoginStatus = Net::LOGIN_CONNECTION_FAILURE;
				break;
			}

			for ( const auto& ext : extInfo )
				if ( !ext.bInitialized ) // issue getting info, connection error or someone has messed with the loader to get here and the php session hasnt started
				{
					iLoginStatus = Net::LOGIN_CONNECTION_FAILURE;
					break;
				}
			if ( strLastLaunchTimes == nullptr )
			{
				iLoginStatus = Net::LOGIN_CONNECTION_FAILURE;
				break;
			}

			bLoggedIn = true;
			while ( iSelectedExtension == PX_EXTENSION_NONE )
				Wait( 100 );

			bShouldClose = true;

			DWORD dwProcessID { };
			do
			{
				dwProcessID = sys::GetProcessID( wstrApplicationExecutableNames[ iSelectedExtension ] );
				Wait( 10 );
			} while ( dwProcessID == 0u
					  || !sys::IsProcessThreadRunning( dwProcessID )
					  || !sys::NecessaryModulesLoaded( dwProcessID ) );

			const auto strDLL = Manager::RequestExtensionInformation( iSelectedExtension );
			auto pBuffer = VirtualAlloc( nullptr, strDLL.length( ) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
			memcpy( pBuffer, strDLL.c_str( ), strDLL.length( ) );

			Inject( pBuffer, wstrApplicationExecutableNames[ iSelectedExtension ], new sys::injection_info_t );
			bShouldClose = true;
		}
		break;

		default:
			break;
	}

	while ( !bShouldClose )
		Wait( 10 );
}

void PX_API OnDetach( )
{
	
}
