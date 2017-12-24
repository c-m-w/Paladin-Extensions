#include "../dllmain.h"

void Wait( unsigned long ulSleepTime )
{
	std::this_thread::sleep_for( std::chrono::milliseconds( ulSleepTime ) );
}

moment GetMoment( )
{
	return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
}
