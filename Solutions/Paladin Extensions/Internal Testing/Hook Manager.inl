/// Hook Manager.inl

#pragma once

namespace PX::Tools
{
	template< typename _fn > void hook_t::HookIndex( unsigned uIndex, _fn fnNewFunction )
	{
		if ( px_assert( uIndex >= 0 && uIndex <= sTableLength ) )
			pNewTable[ uIndex ] = reinterpret_cast< ptr_t >( fnNewFunction );
	}

	template< typename _fn > _fn hook_t::GetOriginalFunction( unsigned uIndex )
	{
		if ( px_assert( uIndex >= 0 && uIndex <= sTableLength ) )
			return reinterpret_cast< _fn >( pOldTable[ uIndex ] );
	}
}
