/// Enumeration Iteration.hpp

#pragma once

#define for_enum( EEnum, enumName, enumMin, enumMax ) \
	for ( EEnum enumName = enumMin; ( enumName ) < ( enumMax ); *reinterpret_cast< int* >( &( enumName ) ) += 1 )
