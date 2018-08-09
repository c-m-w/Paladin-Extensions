/// PX Loader.cpp

#define PX_ENTRY_AS_WIN
#define PX_INSTANCE_ID L"Manager"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX Manager.hpp"

using namespace Tools;

//void TestDebug( )
//{
//	auto print = Tools::string_cast< std::wstring >( "casted" );
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
void PX_API InjectionExample( )
{
	const auto pDLL = fopen( R"(C:\Users\Cole\Desktop\Messagebox.dll)", "rb" );

	if ( !dbg::Assert( pDLL != nullptr ) )
		return;

	fseek( pDLL, 0, SEEK_END );
	const auto lSize = ftell( pDLL );
	rewind( pDLL );
	const auto pBuffer = VirtualAlloc( nullptr, lSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	fread( pBuffer, 1, lSize, pDLL );

	if ( dbg::Assert( lSize != 0 && pBuffer != nullptr ) )
	{
		sys::injection_info_t inj { };
		Inject( pBuffer, L"ConsoleApplication1.exe", &inj );
	}
}

void PX_API OnLaunch( )
{
	const auto lResult = Manager::Login( );
	const auto strDLL = Manager::AssembleCheat( PX_GAME_CSGO );

	auto pBuffer = VirtualAlloc( nullptr, strDLL.length( ) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	memcpy( pBuffer, strDLL.c_str( ), strDLL.length( ) );
	
	sys::injection_info_t inj { };
	Inject( pBuffer, L"ConsoleApplication1.exe", &inj );

	system( "pause" );
}
