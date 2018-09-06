/// Debug.inl

#pragma once

namespace PX
{
	namespace dbg
	{
		namespace
		{
			std::wofstream wofLogFile; // var cannot be static as each fn is compiled as an independent fn due to templating
		}

		template< typename _t > out_t& PX_API out_t::operator<<( const _t& rhs )
		{
#if defined _DEBUG
			if ( !wofLogFile.is_open( ) )
			{
				wofLogFile.open( "C:/debug.log", std::ofstream::trunc );
				px_assert( wofLogFile.good( ) );

				out PX_OPN;
			}

			wofLogFile << rhs;
			std::wcout << rhs;
#endif
			return *this;
		}
	}
}
