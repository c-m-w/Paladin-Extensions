/// Utilities.cpp

#include "../PX Framework.hpp"

namespace PX
{
    namespace Tools
    {
		std::wstring PX_API GetDirectory( unsigned uEscapeLevels )
		{
            std::wstring wstr;
            GetModuleFileNameW( nullptr, &wstr[ 0 ], MAX_PATH );

			for ( auto i = 0u; i <= uEscapeLevels; i++ )
                wstr = wstr.substr( 0, wstr.find_last_of( L'\\' ) );

			return wstr;
		}
    }
}
