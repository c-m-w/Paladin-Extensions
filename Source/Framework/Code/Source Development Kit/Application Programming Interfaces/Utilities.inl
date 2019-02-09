/// Utilities.inl

#pragma once

namespace Utilities
{
	template< typename _t /*= std::chrono::milliseconds*/ > moment_t GetMoment( )
	{
		return std::chrono::duration_cast< _t >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
	}

	template< typename _t /*= std::chrono::milliseconds*/ > void Pause( moment_t mmtPauseLength )
	{
		std::this_thread::sleep_for( _t( mmtPauseLength ) );
	}
}
