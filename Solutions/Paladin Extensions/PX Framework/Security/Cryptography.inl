/// Encryption.hpp

#pragma once

namespace PX
{
	namespace Cryptography
	{
		template< typename _t > std::string PX_API Base64( const std::string& strSubject )
		{
			dbg::Assert( !strSubject.empty( ) );
			_t _Coder;
			_Coder.Put( reinterpret_cast< Types::byte_t* >( const_cast< char* >( strSubject.c_str( ) ) ), strSubject.size( ) );
			_Coder.MessageEnd( );

			const auto uSize = unsigned( _Coder.MaxRetrievable( ) );
			dbg::Assert( uSize > 0 );
			std::string strProcessedText;
			strProcessedText.resize( uSize );
			_Coder.Get( reinterpret_cast< Types::byte_t* >( &strProcessedText[ 0 ] ), uSize );
			return strProcessedText;
		}

		template< typename _t > std::string PX_API AES256CBC( const std::string& strPlainText )
		{
			dbg::Assert( !strEncryptionKey.empty( ) && !strInitializationVector.empty( ) );
			std::string strOutput;
			_t _Cryption( reinterpret_cast< Types::byte_t* >( const_cast< char* >( Tools::string_cast< std::string >( strEncryptionKey ).c_str( ) ) ),
						  strEncryptionKey.length( ), reinterpret_cast< Types::byte_t* >( const_cast< char* >( strInitializationVector.c_str( ) ) ) );
			CryptoPP::StringSource( Tools::string_cast< std::string >( strPlainText ), true, new
									CryptoPP::StreamTransformationFilter( _Cryption, new CryptoPP::StringSink( strOutput ) ) );
			return strOutput;
		}
	}

	namespace XOR
	{
		template< int iValueToEnsure > PX_ABSTRACT_STRUCT SEnsureCompileTime
		{
			enum: int
			{
				VALUE = iValueToEnsure
			};
		};

		template< typename > PX_ABSTRACT_STRUCT SCStringTraits;
		template< std::size_t i > PX_ABSTRACT_STRUCT SCStringTraits< char const( &)[ i ] >
		{
			static PX_DEF int_trait_t = 1;
			typedef char char_trait_t;
		};
		template< std::size_t i > PX_ABSTRACT_STRUCT SCStringTraits< wchar_t const( &)[ i ] >
		{
			static PX_DEF int_trait_t = 2;
			typedef wchar_t char_trait_t;
		};

		template< > PX_ABSTRACT_STRUCT SCStringTraits< const char* >
		{
			static PX_DEF int_trait_t = 1;
			typedef char char_trait_t;
		};
		template< > PX_ABSTRACT_STRUCT SCStringTraits< const wchar_t* >
		{
			static PX_DEF int_trait_t = 2;
			typedef wchar_t char_trait_t;
		};

		template< int... > PX_ABSTRACT_STRUCT SIndexList;

		template< typename, int > PX_ABSTRACT_STRUCT SAppend;
		template< int... iLeft, int iRight > struct SAppend< SIndexList< iLeft... >, iRight >
		{
			typedef SIndexList< iLeft..., iRight > result_t;
		};

		template< int i > struct SConstructIndexList
		{
			typedef typename SAppend< typename SConstructIndexList< i - 1 >::result_t, i - 1 >::result_t result_t;
		};
		template< > struct SConstructIndexList< 0 >
		{
			typedef SIndexList< > result_t;
		};

		template< typename, typename > PX_ABSTRACT_CLASS CXorString;
		template< typename _char, int... iIndex > PX_ABSTRACT_CLASS CXorString< _char, SIndexList< iIndex... > >
		{
			_char _chValue[ sizeof... ( iIndex ) + 1 ];

			static const _char _chXorKey = static_cast< _char >( SEnsureCompileTime< LinearCongruentialGenerator( 10 ) >::VALUE % 0x10000 );

			constexpr _char PX_API EncryptCharacter( const _char _chCharacter, int iIndexParam )
			{
				return _chCharacter ^ ( _chXorKey + iIndexParam );
			}

		public:
			explicit constexpr CXorString( const _char* const _String ): _chValue { EncryptCharacter( _String[ iIndex ], iIndex )... }
			{ }

			const _char* PX_API Decrypt( )
			{
				for ( int i = 0; i < sizeof... ( iIndex ); i++ )
				{
					_chValue[ i ] = _chValue[ i ] ^ ( _chXorKey + i );
				}

				_chValue[ sizeof... ( iIndex ) ] = static_cast< _char >( 0 );

				return _chValue;
			}

			const _char* PX_API Get( )
			{
				return _chValue;
			}
		};
	}
}
