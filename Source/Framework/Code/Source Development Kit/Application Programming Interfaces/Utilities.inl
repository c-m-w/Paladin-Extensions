/// Utilities.inl

#pragma once

namespace Utilities
{
	template< typename _t /*= std::chrono::milliseconds*/ > moment_t GetMoment( )
	{
		return std::chrono::duration_cast< _t >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
	}

	template< typename _t /*= std::chrono::milliseconds*/ > void Pause( moment_t mmtPauseLength )
	{
		std::this_thread::sleep_for( _t( mmtPauseLength ) );
	}

	template< typename _t > struct AStringTraits;
	template< > struct AStringTraits< std::string >
	{
		using char_trait_t = char;

		static int ConvertStringBytes( const char* szFromString, const int iFromStringLength, wchar_t* wszToString, const int iToStringLength )
		{
			return MultiByteToWideChar( 0, 0, szFromString, iFromStringLength, wszToString, iToStringLength );
		}
	};
	template< > struct AStringTraits< std::wstring >
	{
		using char_trait_t = wchar_t;

		static int ConvertStringBytes( const wchar_t* wszFromString, const int iFromStringLength, char* szToString, const int iToStringLength )
		{
			return WideCharToMultiByte( 0, 0, wszFromString, iFromStringLength, szToString, iToStringLength, nullptr, nullptr );
		}
	};

	template< typename _To, typename _From > struct AStringCastImplementation
	{
		static _To Cast( const _From &_strSource )
		{
			int iLength = AStringTraits< _From >::ConvertStringBytes( _strSource.data( ), _strSource.length( ), nullptr, 0 );
			if ( iLength == 0 )
				return _To( );

			std::vector< typename AStringTraits< _To >::char_trait_t > iCastBuffer( iLength );

			AStringTraits< _From >::ConvertStringBytes( _strSource.data( ), _strSource.length( ), &iCastBuffer[ 0 ], iLength );

			return _To( iCastBuffer.begin( ), iCastBuffer.end( ) );
		}
	};

	template< typename _t > struct AStringCastImplementation< _t, _t >
	{
		static _t Cast( const _t &_strSource )
		{
			return _strSource;
		}
	};

	template< typename _t > struct ACharacterTraits;
	template< > struct ACharacterTraits< const char * >
	{
		using string_trait_t = std::string;
	};
	template< > struct ACharacterTraits< const wchar_t * >
	{
		using string_trait_t = std::string;
	};

	template< typename _To, typename _From > _To string_cast( const _From &_strSource )
	{
		return AStringCastImplementation< _To, _From >::Cast( _strSource );
	}
	template< typename _To, typename _From > _To string_cast( _From *_szSource )
	{
		return AStringCastImplementation< _To, typename ACharacterTraits< const _From* >::string_trait_t >::Cast( _szSource );
	}

#define BYTE_STRING( _ch )                                          \
	extern inline unsigned char operator""_b( const _ch _chSource ) \
	{                                                               \
		return static_cast< unsigned char >( _chSource );           \
	}
	BYTE_STRING( char )
	BYTE_STRING( char16_t )
	BYTE_STRING( char32_t )
	BYTE_STRING( wchar_t )
#undef BYTE_STRING
#define BYTE_STRING( _ch )\
	extern inline const unsigned char *operator""_b( const _ch *_szSource, const std::size_t zSize ) \
	{                                                                                                \
		auto b = new unsigned char[ zSize + 1 ];                                                     \
		for ( auto z = 0u; z < zSize; z++ )                                                          \
			b[ z ] = static_cast< unsigned char >( _szSource[ z ] );                                 \
		b[ zSize ] = '\0';                                                                           \
		return const_cast< const unsigned char* >( b );                                              \
	}
	BYTE_STRING( char )
	BYTE_STRING( char16_t )
	BYTE_STRING( char32_t )
	BYTE_STRING( wchar_t )
#undef BYTE_STRING
}
