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
	dbg::out PX_DBG << PX_INPUT.GetKeyState( VK_LBUTTON );
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
	PX_DEF GROUPBOX_COLUMN_WIDTH = 150;
	PX_DEF CHECKBOX_ICON_WIDTH = 25;
	PX_DEF COLOR_BUTTON_WIDTH = 15;
	PX_DEF COLOR_BUTTON_PADDING = 2;
	PX_DEF KEYBIND_BUTTON_WIDTH = 60;
	PX_DEF KEYBIND_BUTTON_PADDING = 2;

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

	/// Create a JSON object to hold our variables for widgets to use.
	static nlohmann::json jsWidgets
	{
		{ "PrimaryTab", 0 },
		{ "SubTab", 0 },
		{ "First", false },
		{ "Second", false },
		{ "Third", false },
		{ "Color One", 0xFF0000FFu },
		{ "Color Two", 0xFEBA4E10u },
		{ "Color Three", 0x00FF00FFu },
		{ "Int", 0 },
		{ "Float", 0.f }
	};

	// Color pickers
	static Types::color_t clrFirst( jsWidgets[ "Color One" ].get_ptr< unsigned* >( ) );
	static Types::color_t clrSecond( jsWidgets[ "Color Two" ].get_ptr< unsigned* >( ) );
	static Types::color_t clrThird( jsWidgets[ "Color Three" ].get_ptr< unsigned* >( ) );

	// Create a header with the window title and subtitle, with minimize and close functionality.
	Header( Tools::string_cast< std::string >( Render::wszWindowTitle ).c_str( ), szNuklearWindowTitle, Minimize, Exit );

	// Create primary tabs.
	fnSetTabValue( jsWidgets[ "PrimaryTab" ].get_ref< int& >( ), Tabs( 10, 0, dqPrimaryTabs, jsWidgets[ "PrimaryTab" ] ) );

	// Separate the primary tabs from the rest of the application.
	Separator( 61, 65, 72, 100 );
	// Set the font for Nuklear to render in.
	SetFont( FONT_ROBOTOSMALL );

	// Create subtabs.
	fnSetTabValue( jsWidgets[ "SubTab" ].get_ref< int& >( ), SubTabs( 10, 60, 190, 30, dqSubTabs, jsWidgets[ "SubTab" ] ) );

	// Begin a groupbox for all of our widgets to be inside of.
	BeginGroupbox( 200, 150, 500, 420, dqSubTabs.at( jsWidgets[ "SubTab" ] ) );
	{
		const static auto iCheckboxTextWidth = CalculateTextBounds( "Checkbox", 30 ).x;
		static char szIntBuffer[ 32 ], szFloatBuffer[ 32 ], buf[ 32 ];
		auto bInitializedBuffers = false;

		if ( !bInitializedBuffers )
		{
			bInitializedBuffers = true;
			strcpy( szIntBuffer, std::to_string( jsWidgets[ "Int" ].get< int >( ) ).c_str( ) );
			strcpy( szFloatBuffer, std::to_string( jsWidgets[ "Float" ].get< int >( ) ).c_str( ) );
			strcpy( buf, "5.0" );
		}

		VerticalSpacing( );

		BeginRow( 15, 12, ROW_STATIC );
		SetRowWidth( 5 );
		Spacing( );
		SetRowWidth( CHECKBOX_ICON_WIDTH + CalculateTextBounds( "Checkbox", 30 ).x );
		Checkbox( "Checkbox", jsWidgets[ "First" ].get_ptr< bool* >( ) );
		SetRowWidth( GROUPBOX_COLUMN_WIDTH - iCheckboxTextWidth - CHECKBOX_ICON_WIDTH - COLOR_BUTTON_WIDTH - COLOR_BUTTON_PADDING * 2 );
		Spacing( );
		SetRowWidth( COLOR_BUTTON_WIDTH );
		ColorButton( "Color 1", &clrFirst );
		SetRowWidth( CHECKBOX_ICON_WIDTH + CalculateTextBounds( "Checkbox", 30 ).x );
		Checkbox( "Checkbox", jsWidgets[ "Second" ].get_ptr< bool* >( ) );
		SetRowWidth( GROUPBOX_COLUMN_WIDTH - iCheckboxTextWidth - CHECKBOX_ICON_WIDTH - ( COLOR_BUTTON_WIDTH * 2 ) - ( COLOR_BUTTON_PADDING * 4 ) );
		Spacing( );
		SetRowWidth( COLOR_BUTTON_WIDTH );
		ColorButton( "Color 2", &clrSecond );
		ColorButton( "Color 3", &clrThird );
		Checkbox( "Checkbox", jsWidgets[ "Third" ].get_ptr< bool* >( ) );
		EndRow( );

		VerticalSpacing( );

		BeginRow( 30, 6, ROW_CUSTOM );
		jsWidgets[ "Int" ] = Slider( "Int Slider", szIntBuffer, -50, 50, jsWidgets[ "Int" ], 15, 0, GROUPBOX_COLUMN_WIDTH, 30 );
		jsWidgets[ "Float" ] = Slider( "Float Slider", szFloatBuffer, -50.f, 50.f, jsWidgets[ "Float" ], GROUPBOX_COLUMN_WIDTH + 25, 0, GROUPBOX_COLUMN_WIDTH, 30, 1 );
		EndRow( );
	}
	EndGroupbox( );
}

void PX_API UI::Manager::SetLayout( )
{
	Example( );
}

void OnLaunch( )
{
	//unsigned uDimensions[ 2 ] { 720, 600 };
	//Render::InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
	//UI::Manager::Initialize( PX_XOR( "Manager" ) );
	//while ( UI::Manager::Render( ) && !bShutdown )
	//	Tools::Wait( 1 );

	//Net::InitializeConnection( );
	//std::deque< Net::post_data_t > dqPostData;
	//
	//nlohmann::json jsDLL
	//{
	//	{ "Order", "7341562" },
	//	{ "DLL", 
	//		{
	//			"Part7"
	//		},
	//		{
	//			"Part3"
	//		}
	//	}
	//};
	//
	//dqPostData.emplace_back( "test", R"()" );
	//const auto strResponse = Net::Request( PX_XOR( "https://www.paladin.rip:443/test.php" ), dqPostData );
	//Net::CleanupConnection( );
	//dbg::out << strResponse.length( ) << dbg::newl;
	//system( "pause" );

	auto pDLL = fopen( R"(C:\Users\Cole\Desktop\Messagebox.dll)", "rb" );
	fseek( pDLL, 0, SEEK_END );
	long lSize = ftell( pDLL );
	rewind( pDLL );
	auto pBuffer = VirtualAlloc( NULL, lSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	fread( pBuffer, 1, lSize, pDLL );

	sys::SInjectionInfo inj;
	DLLManualMap( pBuffer, L"ConsoleApplication1.exe", &inj );
}
