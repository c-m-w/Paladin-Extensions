/// PX Middleman.cpp

#include "PX Middleman.hpp"

void PX_API OnAttach( )
{
	HANDLE hBuffer = sys::FindInternalHandle( sys::GetProcessID( PX_XOR( L"ConsoleApplication1.exe" ) ) );
	if ( hBuffer != nullptr )
		dbg::out PX_SCS << PX_XOR( L"Handle found: " ) << hBuffer << dbg::newl;
	else
		dbg::out PX_ERR << PX_XOR( L"Getting handle failure!" ) << dbg::newl;
	dbg::PutLastError( );
}

void PX_API OnDetach( )
{
	dbg::out << "Detaching!";
}
