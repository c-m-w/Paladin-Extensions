/// Definitions.hpp

#pragma once

#define PX_MASK_VISIBLE ( MASK_SHOT | MASK_OPAQUE )

#define PX_NETVAR_REFERENCE( type, name, table, netvar )													\
    PX_INL type& name( ) const					        													\
	{																										\
        static int ptrOffset = PX::Information::NetworkedVariableManager::FindOffset( table, netvar );		\
        return *reinterpret_cast< type* >( PX::Types::ptr_t( this ) + ptrOffset );							\
    }

#define PX_NETVAR_REFERENCE_OFFSET( type, name, table, netvar, offset )										\
    PX_INL type& name() const																				\
	{																										\
        static int ptrOffset = PX::Information::NetworkedVariableManager::FindOffset( table, netvar );		\
        return *reinterpret_cast< type* >( PX::Types::ptr_t( this ) + ptrOffset + offset );					\
    }

#define PX_NETVAR_POINTER( type, name, table, netvar )														\
    PX_INL type* name() const																				\
	{																										\
        static int ptrOffset = PX::Information::NetworkedVariableManager::FindOffset( table, netvar );		\
        return reinterpret_cast< type* >( PX::Types::ptr_t( this ) + ptrOffset );							\
    }

#define PX_NETVAR_POINTER_OFFSET( type, name, table, netvar, offset )										\
    PX_INL type* name() const																				\
	{																										\
        static int ptrOffset = PX::Information::NetworkedVariableManager::FindOffset( table, netvar );		\
        return reinterpret_cast< type* >( PX::Types::ptr_t( this ) + ptrOffset + offset );					\
    }

#define PX_REVOLUTION 360.f
#define PX_MIN_PITCH -89.f
#define PX_MAX_PITCH 89.f
#define PX_MIN_YAW -180.f
#define PX_MAX_YAW 180.f
#define PX_MIN_ROLL -50.f
#define PX_MAX_ROLL 50.f

