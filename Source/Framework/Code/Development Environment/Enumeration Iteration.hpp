/// Enumeration Iteration.hpp

#pragma once

#define for_enum( EEnum, enumName, enumMin, enumMax ) \
	for ( EEnum enumName = enumMin; ( enumName ) < ( enumMax ); *reinterpret_cast< int* >( &( enumName ) ) += 1 )

#define do_then_return( action ) \
	return ( void )( action )

#define do_then_return_value( action, ret ) \
	return ( action ), ret
