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

	template< typename _To, typename _From > struct AStringCastImplementation
	{
		static _To Cast( const _From& _Source )
		{
			return _To( _Source.begin( ), _Source.end( ) );
		}
	};

	template< typename _From > struct AStringCastImplementation< _From, _From >
	{
		static const _From& Cast( const _From& _Source )
		{
			return _Source;
		}
	};

	template< typename > struct AStringTypeOfCharacter;
#define IMPLEMENT_STRING_TYPE_OF_CHARACTER( _t )                                              \
	template< > struct AStringTypeOfCharacter< _t >                                           \
	{                                                                                         \
		typedef std::basic_string< _t, std::char_traits< _t >, std::allocator< _t > > wrap_t; \
	}
	IMPLEMENT_STRING_TYPE_OF_CHARACTER( const char* );
	IMPLEMENT_STRING_TYPE_OF_CHARACTER( const char16_t* );
	IMPLEMENT_STRING_TYPE_OF_CHARACTER( const char32_t* );
	IMPLEMENT_STRING_TYPE_OF_CHARACTER( const wchar_t* );
	IMPLEMENT_STRING_TYPE_OF_CHARACTER( const unsigned char* );
#undef IMPLEMENT_STRING_TYPE_OF_CHARACTER

	template< typename _To, typename _From > _To string_cast( const _From& _Source )
	{
		return AStringCastImplementation< _To, _From >::Cast( _Source );
	}

	template< typename _To, typename _From > _To string_cast( _From* _Source )
	{
		return string_cast< _To >( _Source );
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
