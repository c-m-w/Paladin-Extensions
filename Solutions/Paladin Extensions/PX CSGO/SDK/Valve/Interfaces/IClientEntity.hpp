#pragma once

#include "IClientNetworkable.hpp"
#include "IClientRenderable.hpp"
#include "IClientUnknown.hpp"
#include "IClientThinkable.hpp"

struct SpatializationInfo_t;

class IClientEntity: public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void Release( void ) = 0;

	QAngle &GetABSAngles( )
	{
		return reinterpret_cast< QAngle&( __thiscall*)( void * ) >( ( *reinterpret_cast< void*** >( this ) )[ 11 ] )( this );
	}
};
