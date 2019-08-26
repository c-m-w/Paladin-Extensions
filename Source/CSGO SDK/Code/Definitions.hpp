/// Definitions.hpp

#pragma once

#define MASK_VISIBLE ( MASK_SHOT | MASK_OPAQUE )

#define NETVAR_REFERENCE( type, name, table, netvar )									\
    type& name( ) const					        										\
	{																					\
        static auto ptrOffset = Memory::FindOffset( table, #name );						\
        return *reinterpret_cast< type* >( uintptr_t( this ) + ptrOffset );				\
    }

#define NETVAR_REFERENCE_OFFSET( type, name, table, netvar, offset )					\
    type& name() const																	\
	{																					\
        static auto ptrOffset = Memory::FindOffset( table, #name );						\
        return *reinterpret_cast< type* >( uintptr_t( this ) + ptrOffset + offset );	\
    }

#define NETVAR_POINTER( type, name, table, netvar )										\
    type* name() const																	\
	{																					\
        static auto ptrOffset = Memory::FindOffset( table, #name );						\
        return reinterpret_cast< type* >( uintptr_t( this ) + ptrOffset );				\
    }

#define NETVAR_POINTER_OFFSET( type, name, table, netvar, offset )						\
    type* name() const																	\
	{																					\
        static auto ptrOffset = Memory::FindOffset( table, #name );						\
        return reinterpret_cast< type* >( uintptr_t( this ) + ptrOffset + offset );		\
    }

#define REVOLUTION 360.f
#define MIN_PITCH -89.f
#define MAX_PITCH 89.f
#define MIN_YAW -180.f
#define MAX_YAW 180.f
#define MIN_ROLL -50.f
#define MAX_ROLL 50.f
#define MAX_ANGLE_DELTA 22.f
#define MAX_CLAN_LENGTH 15u
#define LEG_EXTEND 9.f
#define HEAD_EXTEND 9.f
#define CROUCH_EXTEND ( PX_HEAD_EXTEND + PX_LEG_EXTEND )

#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12

#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15

#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13

#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12

#define SEQUENCE_BOWIE_IDLE1 1
