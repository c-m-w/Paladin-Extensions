/// Time.cpp

#include "Precompile.hpp"

#include "../../Framework.hpp"

void CTime::CalibrateTime( )
{
	if ( QueryPerformanceFrequency( reinterpret_cast< PLARGE_INTEGER >( &iFrequency ) ) == 0 )
		return ( void )( uTimeBase = iCountBase = iFrequency = -1i64, bCalibrationState = false ); // todo log, failed to get performance frequency. GetLastError()

	__int64 iFileTimes[ 2 ];
	if ( timeBeginPeriod( 1 ) != TIMERR_NOERROR )
		return ( void )( uTimeBase = iCountBase = iFrequency = -1i64, bCalibrationState = false ); // todo log

	GetSystemTimePreciseAsFileTime( reinterpret_cast< LPFILETIME >( &iFileTimes[ 0 ] ) );
	do
	{
		GetSystemTimePreciseAsFileTime( reinterpret_cast< LPFILETIME >( &iFileTimes[ 1 ] ) );
	}
	while ( iFileTimes[ 0 ] == iFileTimes[ 1 ] );

	if ( timeEndPeriod( 1 ) != TIMERR_NOERROR )
		return ( void )( uTimeBase = iCountBase = iFrequency = -1i64, bCalibrationState = false ); // todo log

	if ( QueryPerformanceCounter( reinterpret_cast< PLARGE_INTEGER >( &iCountBase ) ) == 0 )
		return ( void )( uTimeBase = iCountBase = iFrequency = -1i64, bCalibrationState = false ); // todo log

	uTimeBase = iFileTimes[ 1 ];

	bCalibrationState = true;
}

unsigned __int64 CTime::GetTime( bool bPrecise /*= false*/ )
{
	for ( auto u = 0; u < 4; u++ )
	{
		if ( !bCalibrationState && ( CalibrateTime( ), !bCalibrationState ) )
			break; // todo log

		auto iFileTime = 0i64, iCount = 0i64;
		GetSystemTimePreciseAsFileTime( reinterpret_cast< LPFILETIME >( &iFileTime ) );
		QueryPerformanceCounter( reinterpret_cast< PLARGE_INTEGER >( &iCount ) );

		auto iCurrentTime = uTimeBase + ( iCount - iCountBase ) * 10000000 / iFrequency;
		static auto iPreviousTime = 0ui64;
		iCurrentTime = iCurrentTime < iPreviousTime ? iPreviousTime : iCurrentTime;
		iPreviousTime = iCurrentTime;

		DWORD dwTimeAdjustment, dwTimeIncrement;
		BOOL bTimeAdjustmentDisableState;
		if ( GetSystemTimeAdjustment( &dwTimeAdjustment, &dwTimeIncrement, &bTimeAdjustmentDisableState ) == 0 )
			break; // todo log

		if ( _abs64( iFileTime - iCurrentTime ) > 2 * ( bTimeAdjustmentDisableState ? dwTimeAdjustment : dwTimeIncrement ) )
			bCalibrationState = false, iPreviousTime = 0;

		if ( bCalibrationState )
			return ( iCurrentTime - EPOCH_DELTA ) / ( bPrecise ? 1 : 10000 );
	}

	auto iFileTime = 0i64;
	GetSystemTimePreciseAsFileTime( reinterpret_cast< LPFILETIME >( &iFileTime ) );
	return ( iFileTime - EPOCH_DELTA ) / ( bPrecise ? 1 : 10000 );
}

void CTime::Wait( unsigned __int64 iTime /*= 0ui64*/ )
{
	
}

void CTime::Pause( unsigned __int64 iTime /*= -1ui64*/ )
{
	
}
