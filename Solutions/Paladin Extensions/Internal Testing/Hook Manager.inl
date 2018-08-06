/// Hook Manager.inl

#pragma once

namespace PX::Tools
{
	template< typename _fn > void hook_t::HookIndex( unsigned uIndex, _fn fnNewFunction )
	{
		if ( dbg::Assert( uIndex >= 0 && uIndex <= sTableLength ) )
			pNewTable[ uIndex ] = fnNewFunction;
	}
}
