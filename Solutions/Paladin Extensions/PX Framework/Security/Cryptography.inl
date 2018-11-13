/// Encryption.hpp

#pragma once

namespace PX
{
	namespace Cryptography
	{
		template< typename _t > Types::str_t PX_API Base64( const Types::str_t &strSubject )
		{
			px_assert( !strSubject.empty( ) );
			_t _Coder;
			_Coder.Put( reinterpret_cast< Types::byte_t * >( const_cast< char * >( strSubject.c_str( ) ) ), strSubject.size( ) );
			_Coder.MessageEnd( );

			const auto uSize = unsigned( _Coder.MaxRetrievable( ) );
			px_assert( uSize > 0 );
			Types::str_t strProcessedText;
			strProcessedText.resize( uSize );
			_Coder.Get( reinterpret_cast< Types::byte_t * >( &strProcessedText[ 0 ] ), uSize );
			return strProcessedText;
		}

		template< typename _t > Types::str_t PX_API AES256CBC( const Types::str_t &strPlainText )
		{
			px_assert( !strEncryptionKey.empty( ) && !strInitializationVector.empty( ) );
			Types::str_t strOutput;
			_t _Cryption( reinterpret_cast< Types::byte_t * >( const_cast< char * >( Tools::string_cast< Types::str_t >( strEncryptionKey ).c_str( ) ) ),
						  strEncryptionKey.length( ), reinterpret_cast< Types::byte_t * >( const_cast< char * >( strInitializationVector.c_str( ) ) ) );
			CryptoPP::StringSource( Tools::string_cast< Types::str_t >( strPlainText ), true, new
									CryptoPP::StreamTransformationFilter( _Cryption, new CryptoPP::StringSink( strOutput ) ) ); // review should we store this var somewhere?
			// should we be declaring an object of StringSource type??
			return strOutput;
		}
	}

	namespace XOR
	{
		template< int iValueToEnsure > px_abstract_class AEnsureCompileTime
		{
		public:
			enum: int
			{
				VALUE = iValueToEnsure
			};
		};

		template< typename > px_abstract_class ACStringTraits;

		template< std::size_t i > px_abstract_class ACStringTraits< char const( &)[ i ] >
		{
		public:
			static PX_DEF int_trait_t = 1;
			typedef char char_trait_t;
		};

		template< std::size_t i > px_abstract_class ACStringTraits< wchar_t const( &)[ i ] >
		{
		public:
			static PX_DEF int_trait_t = 2;
			typedef wchar_t char_trait_t;
		};

		template< > px_abstract_class ACStringTraits< const char * >
		{
		public:
			static PX_DEF int_trait_t = 1;
			typedef char char_trait_t;
		};

		template< > px_abstract_class ACStringTraits< const wchar_t * >
		{
		public:
			static PX_DEF int_trait_t = 2;
			typedef wchar_t char_trait_t;
		};

		template< int... > px_abstract_class AIndexList;

		template< typename, int > px_abstract_class AAppend;

		template< int... iLeft, int iRight > px_abstract_class AAppend< AIndexList< iLeft... >, iRight >
		{
		public:
			typedef AIndexList< iLeft..., iRight > result_t;
		};

		template< int i > px_abstract_class AConstructIndexList
		{
		public:
			typedef typename AAppend< typename AConstructIndexList< i - 1 >::result_t, i - 1 >::result_t result_t;
		};

		template< > px_abstract_class AConstructIndexList< 0 >
		{
		public:
			typedef AIndexList< > result_t;
		};

		template< typename, typename > px_abstract_class AXorString;

		template< typename _char, int... iIndex > px_abstract_class AXorString< _char, AIndexList< iIndex... > >
		{
			_char _chValue[ sizeof...( iIndex ) + 1 ];

			static const _char _chXorKey = static_cast< _char >( AEnsureCompileTime< LinearCongruentialGenerator( 10 ) >::VALUE % 0x10000 );

			constexpr _char PX_API EncryptCharacter( const _char _chCharacter, int iIndexParam )
			{
				return _char( _chCharacter ^ ( _chXorKey + iIndexParam ) );
			}

		public:
			explicit constexpr AXorString( const _char * const _String ): _chValue { EncryptCharacter( _String[ iIndex ], iIndex )... }
			{ }

			const _char * PX_API Decrypt( )
			{
				for ( auto u = 0u; u < sizeof...( iIndex ); u++ )
				{
					_chValue[ u ] ^= ( _chXorKey + u );
				}

				_chValue[ sizeof...( iIndex ) ] = static_cast< _char >( 0 );

				return _chValue;
			}

			const _char * PX_API Get( )
			{
				return _chValue;
			}
		};
	}
}
