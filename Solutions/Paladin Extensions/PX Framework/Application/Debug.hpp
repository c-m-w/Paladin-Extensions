/// Debug.hpp

#pragma once

namespace PX::dbg
{
	// INFO: Asserts parameter to empty initialization version of parameter
	template< typename _t > bool PX_API Assert( _t );

	PX_DEF newl = '\n';

	// INFO: Used to change console print color of debug output
	struct out_clr_t
	{
		WORD m_wDesiredAttributes;
		explicit out_clr_t( const WORD );
	};

	// INFO: Managed debug output; used like std::cout
	class out_t
	{
	public:
		out_t& PX_API operator<<( const out_clr_t& );
		template< typename _t > out_t& PX_API operator<<( const _t& );
	} PX_SDK out;

	void PX_API PutLastError( );
}

#include "Debug.inl"
