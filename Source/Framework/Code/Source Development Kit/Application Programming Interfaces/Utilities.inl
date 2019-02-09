/// Utilities.inl

#pragma once

namespace Utilities
{
	template< typename _t > moment_t GetMoment( )
	{
		return std::chrono::duration_cast< _t >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
	}
}
