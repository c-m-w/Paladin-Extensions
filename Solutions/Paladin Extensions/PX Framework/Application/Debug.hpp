/// Debug.hpp

#pragma once

namespace PX::dbg
{
	PX_DEF newl = '\n';

	// INFO: Used to change console print color of debug output
	struct out_clr_t
	{
		WORD wDesiredAttributes;
		explicit out_clr_t( WORD );
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

#if defined PX_USE_NAMESPACES
using namespace PX::dbg;
#endif
