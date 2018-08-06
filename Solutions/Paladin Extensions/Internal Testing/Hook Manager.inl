/// Hook Manager.inl

#pragma once

namespace PX::Tools
{
	template< typename _fn > void hook_t::HookIndex( unsigned uIndex, _fn fnNewFunction )
	{
		if ( dbg::Assert( uIndex >= 0 && uIndex <= sTableLength ) )
			pNewTable[ uIndex ] = reinterpret_cast< Types::ptr_t >( fnNewFunction );
	}

	template< typename _fn > _fn hook_t::GetOriginalFunction( unsigned uIndex )
	{
		if ( dbg::Assert( uIndex >= 0 && uIndex <= sTableLength ) )
			return reinterpret_cast< _fn >( pOldTable[ uIndex ] );
	}
}
