/// PX Loader.cpp

#include "PX Manager.hpp"

using namespace PX;

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

void PX_API UI::Manager::SetLayout( )
{

}

void f2( int one, int two )
{
	dbg::out << one << " | " << two << dbg::newl;
}

void f1( int one, int two )
{
	f2( one, two );
}

void OnLaunch( )
{
    //TestDebug( );
    //
    //unsigned piDimes[ 2 ] { 500, 500 };
    //Render::InitializeRenderTarget( piDimes, L"Paladin" );
    //UI::Manager::Initialize( "Men" );
    //while ( UI::Manager::Render( ) )
    //{
    //    
    //    TestInput( );
    //}
	system( "pause" );
}
