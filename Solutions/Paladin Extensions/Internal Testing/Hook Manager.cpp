/// Hook Manager.cpp

#include "Internal Testing.hpp"

namespace PX::Tools
{
	std::size_t PX_API EstimateTableLength( void* pVirtualTable )
	{
		auto pCastedTable = reinterpret_cast< void** >( pVirtualTable );
		auto uReturn = 0u;
		MEMORY_BASIC_INFORMATION mbiMemoryInformation { };
		for ( ; pCastedTable[ uReturn ] != nullptr && VirtualQuery( pCastedTable[ uReturn ], &mbiMemoryInformation, sizeof mbiMemoryInformation ) 
			  && ( mbiMemoryInformation.Protect == PAGE_EXECUTE_READ || mbiMemoryInformation.Protect == PAGE_EXECUTE_READWRITE ); uReturn++ ) { }
		return uReturn;
	}

	hook_t::hook_t( void * pVirtualTable ):
		uOldProtection( 0u ), pClassBase( pVirtualTable ), sTableLength( EstimateTableLength( pClassBase ) ), pOldTable( nullptr ), pNewTable( nullptr )
	{

		if ( !dbg::Assert( pClassBase != nullptr ) || !dbg::Assert( sTableLength > 0 ) )
			return;

		pOldTable = *reinterpret_cast< Types::ptr_t** >( pClassBase );
	}

	hook_t::~hook_t( )
	{
		
	}

	void hook_t::UnhookIndex( unsigned uIndex )
	{
		if ( uIndex >= 0 && uIndex < sTableLength )
			pNewTable[ uIndex ] = pOldTable[ uIndex ];
	}

	//template< typename _t, typename _p > _t static __forceinline CallVirtualFunction( _p pVirtualTable, unsigned uIndex )
	//{
	//	return _t( ( *reinterpret_cast< int** >( pVirtualTable ) )[ uIndex ] );
	//}
}
