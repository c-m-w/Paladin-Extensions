/// Debug.inl

#pragma once

namespace PX
{
	namespace dbg
	{
		template< typename _t > out_t& PX_API out_t::operator<<( const _t& rhs )
		{
#if defined _DEBUG
			static std::wofstream wofLogFile;
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
