/// Tools.inl

#pragma once

namespace PX::Tools
{
	template< class _Child > _Child& PX_API ASingleton< _Child >::Get( )
	{
		static _Child _ChildClassObject { };
		return _ChildClassObject;
	}

	template< typename _fn > _fn CHook::GetOriginalFunction( unsigned uIndex )
	{
		px_assert( uIndex >= 0 && uIndex <= zTableLength );
		return reinterpret_cast< _fn >( pOldTable[ uIndex ] );
	}

	template< typename _t > Types::moment_t PX_API GetMoment( )
	{
		return std::chrono::duration_cast< _t >( std::chrono::high_resolution_clock::now( ).time_since_epoch( ) ).count( );
	}
	template< typename _t > void PX_API Wait( Types::moment_t mmtWaitLength = ULLONG_MAX )
	{
		std::this_thread::sleep_for( _t( mmtWaitLength ) );
	}

	// INFO: Deduces traits and uses matching casting function of trait
	template< typename > px_abstract_class AStringTraits;
	template< > px_abstract_class AStringTraits< std::wstring >
	{
	public:
		typedef wchar_t char_trait_t;

		static int ByteConvert( const int iCodePage, LPCWSTR wszData, int iDataLength, LPSTR szBuffer, int iBufferSize )
		{
			return WideCharToMultiByte( iCodePage, 0, wszData, iDataLength, szBuffer, iBufferSize, nullptr, nullptr );
		}
	};
	template< > px_abstract_class AStringTraits< std::string >
	{
	public:
		typedef char char_trait_t;

		static int ByteConvert( const int iCodePage, LPCSTR szData, int iDataLength, LPWSTR wszBuffer, int iBufferSize )
		{
			return MultiByteToWideChar( iCodePage, 0, szData, iDataLength, wszBuffer, iBufferSize );
		}
	};

	// INFO: Differentiates casting from like or unlike string types
	template< typename _To, typename _From > px_abstract_class AStringCastImplementation
	{
	public:
		static _To Cast( const _From& _Source )
		{
			int iLength = AStringTraits< _From >::ByteConvert( CP_ACP, _Source.data( ), _Source.length( ), nullptr, 0 );
			if ( !iLength )
				return _To( );

			std::vector< typename AStringTraits< _To >::char_trait_t > _strBuffer( iLength );
			AStringTraits< _From >::ByteConvert( CP_ACP, _Source.data( ), _Source.length( ), &_strBuffer[ 0 ], iLength );

			return _To( _strBuffer.begin( ), _strBuffer.end( ) );
		}
	};
	template< typename _From > px_abstract_class AStringCastImplementation< _From, _From >
	{
	public:
		static const _From& Cast( const _From& _Source )
		{
			return _Source;
		}
	};

	// INFO: Interface for C-Style string casting
	template< typename > px_abstract_class AStringTypeOfCharacter;
	template< > px_abstract_class AStringTypeOfCharacter< Types::cstr_t >
	{
	public:
		typedef std::string wrap_t;
	};
	template< > px_abstract_class AStringTypeOfCharacter< Types::wcstr_t >
	{
	public:
		typedef std::wstring wrap_t;
	};

	template< typename _To, typename _From > _To PX_API string_cast( const _From& _Source )
	{
		return AStringCastImplementation< _To, _From >::Cast( _Source );
	}
	template< typename _To, typename _From > _To PX_API string_cast( _From* _Source )
	{
		return AStringCastImplementation< _To, typename AStringTypeOfCharacter< const _From* >::wrap_t >::Cast( _Source );
	}
}
