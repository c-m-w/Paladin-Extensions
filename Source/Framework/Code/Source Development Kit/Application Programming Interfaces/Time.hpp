/// Time.hpp

#pragma once

class CTime
{
	bool bCalibrationState = false;
	__int64 iFrequency = LLONG_MAX;
	__int64 iCountBase = LLONG_MAX;
	unsigned __int64 uTimeBase = ULLONG_MAX;

public:
	void CalibrateTime( );

	/** \brief Absolute value of difference between windows epoch and unix epoch. */
	const unsigned __int64 EPOCH_DELTA = 116444736000000000ui64;

	/** \brief Gets the current time since Unix epoch */
	/** \param bPrecise  */
	/** \return Current time in specified precision format */
	[ [ nodiscard ] ] unsigned __int64 GetTime( bool bPrecise = false );
	void Wait( unsigned __int64 uTime = 0ui64 );
	void Pause( unsigned __int64 uTime = ULLONG_MAX );
} inline _Time;

