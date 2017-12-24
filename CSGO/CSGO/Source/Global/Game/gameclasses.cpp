#include "../../dllmain.h"

bool CGlobalVars::operator==( CGlobalVars rhs )
{
	return flRealTime == rhs.flRealTime && ulFrameCount == rhs.ulFrameCount && flAbsoluteFrameTime == rhs.flAbsoluteFrameTime
			&& flAbsoluteFrameStartTimeStdDev == rhs.flAbsoluteFrameStartTimeStdDev && flCurrentTime == rhs.flCurrentTime
			&& flFrameTime == rhs.flFrameTime && ulMaxClients == rhs.ulMaxClients && ulTickCount == rhs.ulTickCount
			&& flIntervalPerTick == rhs.flIntervalPerTick && flInterpolationAmount == rhs.flInterpolationAmount;
}

bool CGlobalVars::operator!=( CGlobalVars rhs )
{
	return !( *this == rhs );
}
