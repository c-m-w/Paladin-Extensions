/// Utilities.cpp

#include "../PX Framework.hpp"

namespace PX
{
    namespace Utilities
    {
		std::wstring GetDirectory( unsigned uUpLevels )
		{
			auto wchTemp = new wchar_t[ MAX_PATH ];
			GetModuleFileNameW( nullptr, wchTemp, MAX_PATH );

			auto str = std::wstring( wchTemp );
			delete[ ] wchTemp;

			for ( auto i = 0u; i <= uUpLevels; i++ )
				str = str.substr( 0, str.find_last_of( L'\\' ) );

			return str;
		}
    }
}
