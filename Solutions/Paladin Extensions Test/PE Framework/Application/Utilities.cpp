/// Utilities.cpp

#include "../Framework.hpp"

namespace Paladin
{
    moment_t GetMoment( )
    {
        return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
    }

	void Wait( moment_t mWaitLength )
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( mWaitLength ) );
    }

	std::wstring GetDirectory( unsigned uUpLevels /*= 0*/ )
	{
		auto wchTemp = new wchar_t[ MAX_PATH ];
		GetModuleFileName( nullptr, wchTemp, MAX_PATH );
		auto str = std::wstring( wchTemp );
		for( auto i = 0u; i <= uUpLevels; i ++ )
			str = str.substr( 0, str.find_last_of( L'\\' ) );
		delete[ ] wchTemp;
		return str;
	}
}
