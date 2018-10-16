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

	// INFO: Deduces traits and uses matching casting function of trait
	template< typename > px_abstract_class AStringTraits;
	template< > px_abstract_class AStringTraits< Types::bstr_t >
	{
	public:
		typedef wchar_t char_trait_t;

		static int ByteConvert( const int iCodePage, LPVOID _szData, int iDataLength, LPVOID _szBuffer, int iBufferSize )
		{
			return MultiByteToWideChar( iCodePage, 0, (LPCSTR)_szData, iDataLength, (LPWSTR)_szBuffer, iBufferSize );
		}
	};
	template< > px_abstract_class AStringTraits< Types::wstr_t >
	{
	public:
		typedef wchar_t char_trait_t;

		static int ByteConvert( const int iCodePage, LPVOID _szData, int iDataLength, LPVOID _szBuffer, int iBufferSize )
		{
			return WideCharToMultiByte( iCodePage, 0, (LPCWSTR)_szData, iDataLength, (LPSTR)_szBuffer, iBufferSize, nullptr, nullptr );
		}
	};
	template< > px_abstract_class AStringTraits< Types::str32_t >
	{
		//todo
	public:
		typedef char32_t char_trait_t;

		static int ByteConvert( const int iCodePage, LPVOID _szData, int iDataLength, LPVOID _szBuffer, int iBufferSize )
		{
			return WideCharToMultiByte( iCodePage, 0, (LPCWSTR)_szData, iDataLength, (LPSTR)_szBuffer, iBufferSize, nullptr, nullptr );
		}
	};
	template< > px_abstract_class AStringTraits< Types::str16_t >
	{
		//todo
	public:
		typedef char16_t char_trait_t;

		static int ByteConvert( const int iCodePage, LPVOID _szData, int iDataLength, LPVOID _szBuffer, int iBufferSize )
		{
			return WideCharToMultiByte( iCodePage, 0, (LPCWSTR)_szData, iDataLength, (LPSTR)_szBuffer, iBufferSize, nullptr, nullptr );
		}
	};
	template< > px_abstract_class AStringTraits< Types::str_t >
	{
	public:
		typedef char char_trait_t;

		static int ByteConvert( const int iCodePage, LPVOID _szData, int iDataLength, LPVOID _szBuffer, int iBufferSize )
		{
			return MultiByteToWideChar( iCodePage, 0, (LPCSTR)_szData, iDataLength, (LPWSTR)_szBuffer, iBufferSize );
		}
	};

	// INFO: Differentiates casting from like or unlike string types
	template< typename _To, typename _From > px_abstract_class AStringCastImplementation
	{
	public:
		static _To Cast( const _From& _Source )
		{
			int iLength = AStringTraits< _From >::ByteConvert( CP_ACP, (LPVOID)_Source.data( ), _Source.length( ), nullptr, 0 );
			if ( !iLength )
				return _To( );

			std::vector< typename AStringTraits< _To >::char_trait_t > _strBuffer( iLength );
			AStringTraits< _From >::ByteConvert( CP_ACP, (LPVOID)_Source.data( ), _Source.length( ), (LPVOID)&_strBuffer[ 0 ], iLength );

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
		typedef Types::str_t wrap_t;
	};
	template< > px_abstract_class AStringTypeOfCharacter< Types::cstr16_t >
	{
	public:
		typedef Types::str16_t wrap_t;
	};
	template< > px_abstract_class AStringTypeOfCharacter< Types::cstr32_t >
	{
	public:
		typedef Types::str32_t wrap_t;
	};
	template< > px_abstract_class AStringTypeOfCharacter< Types::wcstr_t >
	{
	public:
		typedef Types::wstr_t wrap_t;
	};
	template< > px_abstract_class AStringTypeOfCharacter< Types::bcstr_t >
	{
	public:
		typedef Types::bstr_t wrap_t;
	};

	template< typename _fn > _fn CTrampolineHook::GetOriginalFunction( unsigned uIndex )
	{
		return reinterpret_cast< _fn >( pOldTable[ uIndex ] );
	}

	template< typename _To, typename _From > _To PX_API string_cast( const _From& _Source )
	{
		return AStringCastImplementation< _To, _From >::Cast( _Source );
	}
	template< typename _To, typename _From > _To PX_API string_cast( _From* _Source )
	{
		return AStringCastImplementation< _To, typename AStringTypeOfCharacter< const _From* >::wrap_t >::Cast( _Source );
	}
}
