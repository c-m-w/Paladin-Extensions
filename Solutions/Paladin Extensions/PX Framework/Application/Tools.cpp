/// Tools.cpp

#include "../PX Framework.hpp"

using namespace PX::Files;

namespace PX::Tools
{
	void PX_API EmitSound( wcstr_t szFileName )
	{
		const static auto strSoundDirectory = GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(Resources\Sound\)" );
		PlaySound( ( strSoundDirectory + szFileName ).c_str( ), nullptr, SND_ASYNC );
	}

	void PX_API OpenLink( cstr_t szLink )
	{
		ShellExecute( nullptr, PX_XOR( L"open" ), Tools::string_cast< std::wstring >( std::string( szLink ) ).c_str( ), nullptr, nullptr, SW_SHOWNORMAL );
	}

	std::string PX_API TimeToDate( moment_t mmtTime )
	{
		if ( mmtTime == 0ull )
			return PX_XOR( "Never" );

		static char szBuffer[ 32 ];
		time_t tmBuffer = mmtTime;

		time( &tmBuffer );
		const auto tmTime = localtime( &tmBuffer );

		const char* szDaySuffix;

		switch ( tmTime->tm_mday % 10 )
		{
			default:
				if ( tmTime->tm_mday / 10 == 1 || tmTime->tm_mday % 10 > 3 )
				{
					szDaySuffix = PX_XOR( "th" );
					break;
				}
			case 1:
				szDaySuffix = PX_XOR( "st" );
				break;
			case 2:
				szDaySuffix = PX_XOR( "nd" );
				break;
			case 3:
				szDaySuffix = PX_XOR( "rd" );
				break;
		}

		px_assert( szDaySuffix );

		strftime( szBuffer, 80, ( std::string( PX_XOR( "%B %e" ) ) + szDaySuffix + PX_XOR( ", 20%g" ) ).c_str( ), tmTime );
		return szBuffer;
	}

	std::string PX_API FormatShellcode( byte_t* bByteArray, unsigned uSize )
	{
		std::string strFormatted { };
		for ( auto u = 0u; u < uSize; u++ )
		{
			strFormatted += PX_XOR( R"(\x)" );
			strFormatted.resize( strFormatted.size( ) + 2 ); // +2 because max length of a byte in digits is 2.
			sprintf( &strFormatted[ 0 ], "%s%02X", strFormatted.c_str( ), bByteArray[ u ] );
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
