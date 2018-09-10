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

	void PX_API LogLastError( )
	{
#if defined _DEBUG
		auto dwLastError = GetLastError( );

		std::wstring wstrLastErrorMessage;
		wstrLastErrorMessage.resize( 1024 );
		if ( 0 == FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, dwLastError,
								 MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), &wstrLastErrorMessage[ 0 ], 0, nullptr ) )
			out PX_LER << "[0x" << std::hex << dwLastError << "] - Unable to retrieve error description due to 0x" << GetLastError( ) << std::dec;
		else
			out PX_LER << "[0x" << std::hex << dwLastError << "] - " << wstrLastErrorMessage << std::dec;
#endif
	}
}
