/// Tools.cpp

#include "../PX Framework.hpp"

namespace PX::Tools
{
	unsigned* GetScreenDimensions( )
	{
		static unsigned uScreenDimensions[ 2 ];
		uScreenDimensions[ 0 ] = GetSystemMetrics( SM_CXSCREEN );
		uScreenDimensions[ 1 ] = GetSystemMetrics( SM_CYSCREEN );
		return uScreenDimensions;
	}
}
