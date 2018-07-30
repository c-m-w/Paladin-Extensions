/// PX Loader.cpp

#include "PX Loader.hpp"

using namespace PX;

void TestDebug( )
{
    auto print = Utilities::string_cast< std::wstring >( "casted" );
    dbg::out PX_DBG << L"Hi" << dbg::endl;
    dbg::out PX_ERR << L"Mid-print" << dbg::endl;
    dbg::out PX_WRN << L"Mid-print 2" << dbg::endl;
    dbg::out PX_SCS << L"Bye" << dbg::endl;
    dbg::out PX_LER << print << dbg::endl;
}

void TestInput( )
{
    while ( true )
    {
        dbg::out << IInputManager::Get( ).GetKeyState( VK_LBUTTON );
        Utilities::Wait( 100 );
    }
}

void Uncalled( )
{
    UI::Widgets::Inputbox< char* >( 20, new char[ 6 ] { "Hello" } );
    UI::Widgets::Inputbox< int >( 20, new char[ 6 ] { "Hello" } );
    UI::Widgets::Inputbox< float >( 20, new char[ 6 ] { "Hello" } );
}

void OnLaunch( )
{
    TestDebug( );
    TestInput( );
}
