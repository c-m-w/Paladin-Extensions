/// Main.cpp

#include "Main.hpp"

void OnLaunch( )
{
	dbg::out M_DBG << "This is output only visible if compiled in debug" << dbg::endl;
	dbg::out M_ERR << "This is error output" << dbg::endl;

	dbg::out << string_cast< std::string >( L"This is a wide string, printed through casting means" ) << dbg::endl;
	dbg::out << std::wstring( L"This is a wide string, still printable through normal means" ) << dbg::endl;
	dbg::out << L"This is a wide string, still printable through normal means" << dbg::endl;
	const wchar_t *wsz = L"This is a wide string, still printable through normal means";
	dbg::out << wsz << dbg::endl;
	dbg::out << M_XOR( "This is an encrypted string, still readable on runtime" ) << dbg::endl;

	system( "pause" );
}
