/// PX Loader.cpp

#include "PX Manager.hpp"

using namespace PX;

PX_SDK auto bShutdown = false;

void TestDebug( )
{
	auto print = Tools::string_cast< std::wstring >( "casted" );
	dbg::out PX_DBG << PX_XOR( L"Hi" ) << dbg::newl;
	dbg::out PX_ERR << PX_XOR( L"Mid-print" ) << dbg::newl;
	dbg::out PX_WRN << PX_XOR( L"Mid-print 2" ) << dbg::newl;
	dbg::out PX_SCS << PX_XOR( L"Bye" ) << dbg::newl;
	dbg::out PX_LER << print << dbg::newl;
}

void TestInput( )
{
	dbg::out << PX_INPUT.GetKeyState( VK_LBUTTON );
	Tools::Wait( 100 );
}

void Uncalled( )
{
	UI::Widgets::Inputbox< char* >( 20, new char[ 6 ] { "Hello" } );
	UI::Widgets::Inputbox< int >( 20, new char[ 6 ] { "Hello" } );
	UI::Widgets::Inputbox< float >( 20, new char[ 6 ] { "Hello" } );
}

void Minimize( )
{

}

void Exit( )
{
    bShutdown = true;
}

void PX_API UI::Manager::Example( )
{
	static const std::deque< Types::cstr_t > dqPrimaryTabs
	{
		"Tab One",
		"Super Wide Tab That Is Dynamically Sized Depending On Text",
		"Tab three!!!" ICON_FA_KEY,
		"Tab Four"
	};

	static const std::deque< Types::cstr_t > dqSubTabs
	{
		"Subtab One",
		"Subtab Two",
		"Subtab Three",
		"Subtab Four"
	};

	using namespace Widgets;

	static const auto fnSetTabValue = [ ]( int& iCurrentValue, const int iNewValue ) { iCurrentValue = iNewValue >= 0 ? iNewValue : iCurrentValue; };

	/// Declare variables for widgets to use.

	// Tabs
	static auto iPrimaryTab = 0, iSubTab = 0;
	// Checkboxes
	static auto bFirst = false, bSecond = false;
	// Color pickers
	static Types::color_t clrFirst( 255, 0, 0, 255 ), clrSecond( 0, 255, 0 );

	/// 

	// Create a header with the window title and subtitle, with minimize and close functionality.
	Header( Tools::string_cast< std::string >( Render::wszWindowTitle ).c_str( ), szNuklearWindowTitle, Minimize, Exit );

	// Create primary tabs.
	fnSetTabValue( iPrimaryTab, Tabs( 10, 0, dqPrimaryTabs, iPrimaryTab ) );

	// Separate the primary tabs from the rest of the application.
	Separator( 61, 65, 72, 100 );
	// Set the font for Nuklear to render in.
	SetFont( FONT_ROBOTOSMALL );

	// Create subtabs.
	fnSetTabValue( iSubTab, SubTabs( 10, 60, 30, 190, dqSubTabs, iSubTab ) );
}

void PX_API UI::Manager::SetLayout( )
{
	Example( );
}

void OnLaunch( )
{
	unsigned uDimensions[ 2 ] { 720, 600 };
	Render::InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
	UI::Manager::Initialize( PX_XOR( "Manager" ) );
	while ( UI::Manager::Render( ) && !bShutdown )
		Tools::Wait( 1 );

	Net::InitializeConnection( );
	std::deque< Types::post_data_t > dqPostData;
	dqPostData.emplace_back( "test", "post" );
	const auto strResponse = Net::Request( PX_XOR( "https://www.paladin.rip:443/test.php" ), dqPostData );
	Net::CleanupConnection( );
	dbg::out << strResponse.c_str( ) << dbg::newl;
	system( "pause" );
}
