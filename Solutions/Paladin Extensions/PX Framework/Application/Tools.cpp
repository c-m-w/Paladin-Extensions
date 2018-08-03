/// Tools.cpp

#include "../PX Framework.hpp"

namespace PX::Tools
{
	void PX_API EmitSound( Types::wcstr_t szFileName )
	{
		const static auto strSoundDirectory = Files::GetDirectory( 1 ) + LR"(\Resources\Sound\)";
		PlaySound( ( strSoundDirectory + szFileName ).c_str( ), nullptr, SND_ASYNC );
	}

	unsigned* GetScreenDimensions( )
	{
		static unsigned uScreenDimensions[ 2 ];
		uScreenDimensions[ 0 ] = GetSystemMetrics( SM_CXSCREEN );
		uScreenDimensions[ 1 ] = GetSystemMetrics( SM_CYSCREEN );
		return uScreenDimensions;
	}
}
