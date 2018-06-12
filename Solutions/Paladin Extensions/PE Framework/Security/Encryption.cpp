/// Encryption.cpp

#include "../Framework.hpp"

namespace Paladin
{
	namespace xors
	{
		template < typename _char, typename _IndexList > class CXorString;

		template< typename _char, int... iIndex > const _char *CXorString< _char, SIndexList< iIndex... > >::Decrypt( )
		{
			for ( int i = 0; i < sizeof...( iIndex ); i++ )
			{
				_chValue[ i ] = _chValue[ i ] ^ ( _chXorKey + i );
			}

			_chValue[ sizeof...( iIndex ) ] = static_cast< _char >( 0 );

			return _chValue;
		}

		template< typename _char, int... iIndex > const _char *CXorString< _char, SIndexList< iIndex... > >::Get( )
		{
			return _chValue;
		}

		template< typename _char, int... iIndex > constexpr _char CXorString< _char, SIndexList< iIndex... > >::EncryptCharacter( const _char _chCharacter )
		{
			return _chCharacter ^ ( _chXorKey + iIndex );
		}

		template< typename _char, int... iIndex > constexpr CXorString< _char, SIndexList< iIndex... > >::CXorString( const _char * const String ): _chValue { EncryptCharacter( String[ iIndex ] ) }
		{ }
	}
}
