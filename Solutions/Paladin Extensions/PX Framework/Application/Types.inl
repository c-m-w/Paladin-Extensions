///Types.inl

#pragma once

namespace PX::Types
{
	PX_EXT PX_INL byte_t operator""_b( char chSource )
	{
		return static_cast< byte_t >( chSource );
	}

	PX_EXT PX_INL byte_t operator""_b( char16_t ch16Source )
	{
		return static_cast< byte_t >( ch16Source );
	}

	PX_EXT PX_INL byte_t operator""_b( char32_t ch32Source )
	{
		return static_cast< byte_t >( ch32Source );
	}

	PX_EXT PX_INL byte_t operator""_b( wchar_t wchSource )
	{
		return static_cast< byte_t >( wchSource );
	}

	PX_EXT PX_INL const byte_t *operator""_b( cstr_t szSource, const std::size_t zSize )
	{
		byte_t *b = new byte_t[ zSize + 1 ];
		for ( std::size_t z = 0u; z < zSize; z++ )
		{
			b[ z ] = static_cast< byte_t >( szSource[ z ] );
		}
		b[ zSize ] = '\0';
		return const_cast< const byte_t* >( b );
	}

	PX_EXT PX_INL const byte_t *operator""_b( cstr16_t sz16Source, const std::size_t zSize )
	{
		byte_t *b = new byte_t[ zSize ];
		for ( std::size_t z = 0u; z < zSize; z++ )
		{
			b[ z ] = static_cast< byte_t >( sz16Source[ z ] );
		}
		b[ zSize ] = '\0';
		return const_cast< const byte_t* >( b );
	}

	PX_EXT PX_INL const byte_t *operator""_b( cstr32_t sz32Source, const std::size_t zSize )
	{
		byte_t *b = new byte_t[ zSize ];
		for ( std::size_t z = 0u; z < zSize; z++ )
		{
			b[ z ] = static_cast< byte_t >( sz32Source[ z ] );
		}
		b[ zSize ] = '\0';
		return const_cast< const byte_t* >( b );
	}

	PX_EXT PX_INL const byte_t *operator""_b( wcstr_t wszSource, const std::size_t zSize )
	{
		byte_t *b = new byte_t[ zSize ];
		for ( std::size_t z = 0u; z < zSize; z++ )
		{
			b[ z ] = static_cast< byte_t >( wszSource[ z ] );
		}
		b[ zSize ] = '\0';
		return const_cast< const byte_t* >( b );
	}
}
