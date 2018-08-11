/// Tools.cpp

#include "../PX Framework.hpp"

namespace PX::Tools
{
	void PX_API EmitSound( wcstr_t szFileName )
	{
		const static auto strSoundDirectory = Files::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Resources\Sound\)" );
		PlaySound( ( strSoundDirectory + szFileName ).c_str( ), nullptr, SND_ASYNC );
	}

	void PX_API OpenLink( cstr_t szLink )
	{
		ShellExecute( nullptr, PX_XOR( L"open" ), Tools::string_cast< std::wstring >( std::string( szLink ) ).c_str( ), nullptr, nullptr, SW_SHOWNORMAL );
	}

	std::string PX_API TimeToDate( moment_t mmtTime )
	{
		constexpr char* szDateSuffixes[ ]
		{
			"", "st", "nd", "rd", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th", "th", "th"
		};

		if ( mmtTime == 0ull )
			return "Never";

		static char szBuffer[ 32 ];
		time_t tmBuffer = mmtTime;

		time( &tmBuffer );
		const auto tmTime = localtime( &tmBuffer );

		strftime( szBuffer, 80, ( std::string( "%B %e" ) + szDateSuffixes[ tmTime->tm_mday ] + ", 20%g" ).c_str( ), tmTime );
		return szBuffer;
	}

	std::string PX_API FormatShellcode( byte_t* bByteArray, unsigned uSize )
	{
		std::string strFormatted { };
		for ( auto u = 0u; u < uSize; u++ )
		{
			strFormatted += R"(\x)";
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
