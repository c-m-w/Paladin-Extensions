/// Utilities.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

namespace Utilities
{
	moment_t GetMoment( )
	{
		timespec _Time { };
		timespec_get( &_Time, TIME_UTC );
		return _Time.tv_nsec / 100ui64;
	}

	void Pause( moment_t mmtPauseLength )
	{
		if ( 0ui64 == mmtPauseLength )
			return;

		//static const auto NtDelayExecution = static_cast< SWindowsAPI::fnNtDelayExecution >( GetFunctionPointer( SWindowsAPI::NtDelayExecution ) );
		//if ( nullptr == NtDelayExecution ) // their system must be really messed up if it can't find delay execution
		//	return Sleep( DWORD( mmtPauseLength ) );
		//
		//const auto mmtEndTarget = GetMoment( ) + mmtPauseLength * 10000ull - 5000ull; // 10,000 is milliseconds to 100 nanoseconds conversion
		//
		//LARGE_INTEGER liDelayInterval;
		//liDelayInterval.QuadPart = -1ll;
		//
		//while ( GetMoment( ) < mmtEndTarget )
		//	NtDelayExecution( FALSE, &liDelayInterval );
	}
}
