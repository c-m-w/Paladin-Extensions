/// Debug.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::dbg
{

	out_clr_t::out_clr_t( const WORD wDesiredAttributes ): wDesiredAttributes( wDesiredAttributes )
	{ }

	out_t& PX_API out_t::operator<<( const out_clr_t& rhs )
	{
#if defined _DEBUG
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), rhs.wDesiredAttributes );
#endif
		return *this;
	}

	void PX_API PrintLastError( )
	{
#if defined _DEBUG
		auto dwError = GetLastError( );
		if ( !dwError )
		{
			out PX_LER << "[0x0] - No errors";
			return;
		}

		LPWSTR lpwstrError { };
		if ( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
							 nullptr, dwError, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), lpwstrError, 0, nullptr ) )
			out PX_LER << "[0x" << std::hex << dwError << "] - Unable to retrieve error description";
		else
			out PX_LER << "[0x" << std::hex << dwError << "] - " << *lpwstrError;
		LocalFree( lpwstrError );
#endif
	}
}
