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
		{ "Int", 0 },
		{ "Float", 0.f }
	};

	// Color pickers
	static Tools::color_sequence_t clrFirst( Tools::color_t( 255, 0, 0 ), 1000 );
	static Tools::color_sequence_t clrSecond( Tools::color_t( 0, 255, 0 ), 1000 );
	static Tools::color_sequence_t clrThird( Tools::color_t( 0, 0, 255 ), 1000 );

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

void PX_API OnLaunch( )
{
	using namespace Tools;

	dbg::out << color_sequence_t::GetGradient( color_t( 255, 0, 0 ), color_t( 0, 0, 255 ), 0.f ).r << dbg::newl;
	dbg::out << color_sequence_t::GetGradient( color_t( 255, 0, 0 ), color_t( 0, 0, 255 ), 0.25f ).r << dbg::newl;
	dbg::out << color_sequence_t::GetGradient( color_t( 255, 0, 0 ), color_t( 0, 0, 255 ), 0.5f ).r << dbg::newl;
	dbg::out << color_sequence_t::GetGradient( color_t( 255, 0, 0 ), color_t( 0, 0, 255 ), 0.75f ).r << dbg::newl;
	dbg::out << color_sequence_t::GetGradient( color_t( 255, 0, 0 ), Tools::color_t( 0, 0, 255 ), 1.f ).r << dbg::newl; 	//dbg::out << color_sequence_t::GetGradient( color_t( 255, 0, 0 ), Tools::color_t( 0, 0, 255 ), 1.25f ).r << dbg::newl;


	unsigned uDimensions[ 2 ] { 720, 600 };
	Render::InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
	UI::Manager::Initialize( PX_XOR( "Manager" ) );
	while ( UI::Manager::Render( ) && !bShutdown )
		Tools::Wait( 1 );

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
		sys::DLLManualMap( pBuffer, L"ConsoleApplication1.exe", &inj );
	}
	system( "pause" );
}
