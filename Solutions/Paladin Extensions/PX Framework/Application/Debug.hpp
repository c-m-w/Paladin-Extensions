/// Debug.hpp

#pragma once

#if defined _DEBUG
namespace PX::dbg
{
	struct SDebugStream: PX::Tools::ASingleton< SDebugStream >
	{
		template< typename _t > SDebugStream & PX_API operator<<( const _t &_Log );
	};
}

#include "Debug.inl"

#if defined PX_USE_NAMESPACES
using namespace PX::dbg;
#endif
#endif
