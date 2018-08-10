/// PX Loader.cpp

#define PX_ENTRY_AS_WIN
#define PX_INSTANCE_ID L"Manager"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX Manager.hpp"

using namespace Tools;

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

bool bLoggedIn = false, bShouldClose = false;
int iSelectedCheat = -1, iLoginStatus = -1;

using namespace UI::Widgets;

void PX_API UI::Manager::SetLayout( )
{
	//Example( );

	if ( !bLoggedIn && iLoginStatus == -1 )
	{
		static auto bReverseColor = false;
		static byte_t bAlpha = 0;
		bAlpha += bReverseColor ? -5 : 5;
		if ( bAlpha == UCHAR_MAX || bAlpha == 0 )
			bReverseColor = !bReverseColor;

		Header( "Paladin Extensions", "Manager", 600u, nullptr, [ ]( )
		{
			bShouldClose = true;
		} );

		auto uWindowDimensions = GetCurrentWindowDimensions( );
		vecImageQueue.emplace_back( TEXTURE_LOGO_LOADING, D3DXVECTOR3( float( uWindowDimensions[ 0 ] / 2 - vecTextures[ TEXTURE_LOGO_LOADING ].uWidth / 2 ), float( uWindowDimensions[ 1 ] / 2 - vecTextures[ TEXTURE_LOGO_LOADING ].uHeight / 2 ), 0.f ), D3DCOLOR_ARGB( bAlpha, bAlpha, bAlpha, bAlpha ) );
	}
	else if ( !bLoggedIn && iLoginStatus > -1 )
	{

	}
}

void PX_API Draw( )
{
	unsigned uDimensions[ 2 ] { 720, 600 };
	Render::InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
	UI::Manager::Initialize( PX_XOR( "Manager" ) );

	DEVMODE pDevMode;
	EnumDisplaySettings( nullptr, ENUM_CURRENT_SETTINGS, &pDevMode );
	while ( !bShouldClose )
	{
		auto mmtStart = GetMoment( );

		if ( !UI::Manager::Render( ) )
			break;

		Wait( 1000 / pDevMode.dmDisplayFrequency - ( GetMoment( ) - mmtStart ) );
	}
}

void PX_API MonitorSteam( )
{
	while ( iSelectedCheat == -1 )
	{
		if ( sys::GetProcessID( PX_XOR( L"Steam.exe" ) ) != 0u )
			exit( -1 );
		Wait( 250 );
	}
}

void PX_API OnLaunch( )
{
	if ( sys::GetProcessID( PX_XOR( L"Steam.exe" ) ) != 0u )
		return;

	// We need the resources loaded for textures in the ui
	Files::Resources::LoadResources( { } );

	std::thread tDraw( Draw );
	tDraw.detach( );

	std::thread tSentinal( MonitorSteam );
	tSentinal.detach( );

	iLoginStatus = Manager::Login( );
	switch ( iLoginStatus )
	{
		case Manager::LOGIN_HARDWARE_MISMATCH:
			MessageBox( nullptr, L"Unique ID Mismatch", L"Your Unique ID does not match the one in the database. Please create a ticket to change your unique ID.", MB_OK );
			break;
		case Manager::LOGIN_STAFF_SUCCESS:
		// staff shit
		case Manager::LOGIN_SUCCESS:
		//while ( iSelectedCheat == -1 )
		//	Wait( 5 );
		const auto strDLL = Manager::AssembleCheat( 2 /*iSelectedCheat*/ );
		auto pBuffer = VirtualAlloc( nullptr, strDLL.length( ) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
		memcpy( pBuffer, strDLL.c_str( ), strDLL.length( ) );

		sys::injection_info_t inj { };
		Inject( pBuffer, L"ConsoleApplication1.exe", &inj );
		break;
	}

	while ( !bShouldClose )
		Wait( 10 );
}
