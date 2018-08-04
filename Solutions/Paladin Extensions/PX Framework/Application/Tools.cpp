/// Tools.cpp

#include "../PX Framework.hpp"

namespace PX::Tools
{
	void PX_API EmitSound( Types::wcstr_t szFileName )
	{
		const static auto strSoundDirectory = Files::GetDirectory( 1 ) + PX_XOR( LR"(\Resources\Sound\)" );
		PlaySound( ( strSoundDirectory + szFileName ).c_str( ), nullptr, SND_ASYNC );
	}

	std::string PX_API FormatShellcode( Types::byte_t* bByteArray )
	{
		std::string strFormatted { };
		for ( int i { }; i < sizeof bByteArray; i++ )
		{
			strFormatted += PX_XOR( R"(\x)" );
			strFormatted.resize( strFormatted.size( ) + 2 ); // +2 because max length of a byte in digits is 2.
			sprintf( &strFormatted[ 0 ], "%s%02X", strFormatted.c_str( ), bByteArray[ i ] );
		}
		return strFormatted;
	}

	unsigned* GetScreenDimensions( )
	{
		static unsigned uScreenDimensions[ 2 ];
		uScreenDimensions[ 0 ] = GetSystemMetrics( SM_CXSCREEN );
		uScreenDimensions[ 1 ] = GetSystemMetrics( SM_CYSCREEN );
		return uScreenDimensions;
	}
}
