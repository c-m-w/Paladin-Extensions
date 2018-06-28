/// Utilities.cpp

#include "../Framework.hpp"

namespace Paladin
{
    moment_t GetMoment( )
    {
        return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
    }
}
