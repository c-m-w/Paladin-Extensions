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

void PX_API UI::Manager::SetLayout( )
{
	using namespace Widgets;
	Header( Tools::string_cast< std::string >( Render::wszWindowTitle ).c_str( ), szNuklearWindowTitle, Minimize, Exit );
}

void OnLaunch( )
{
	//unsigned uDimensions[ 2 ] { 500, 500 };
	//Render::InitializeRenderTarget( uDimensions, hinstWin, PX_XOR( L"Paladin Extensions" ) );
	//UI::Manager::Initialize( PX_XOR( "Manager" ) );
	//while ( UI::Manager::Render( ) && !bShutdown )
	//	Tools::Wait( 1 );
	Cryptography::Initialize( );

	std::string strPlainText = "Men",
				strEncryptedText = Cryptography::Encrypt( strPlainText ),
				strDecryptedText = Cryptography::Decrypt( strEncryptedText );
	dbg::out << "Original: "	<< Tools::string_cast< std::wstring >( strPlainText		) << dbg::newl;
	dbg::out << "Encrypted: "	<< Tools::string_cast< std::wstring >( strEncryptedText ) << dbg::newl;
	dbg::out << "Decrypted: "	<< Tools::string_cast< std::wstring >( strDecryptedText ) << dbg::newl;
	system( "pause" );
}
