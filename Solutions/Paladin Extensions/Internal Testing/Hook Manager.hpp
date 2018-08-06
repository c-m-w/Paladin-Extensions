/// Hook Manager.hpp

#pragma once

namespace PX::Tools
{
	std::size_t PX_API EstimateTableLength( void* pVirtualTable );

	struct hook_t
	{
	private:
		unsigned uOldProtection;
		std::size_t sTableLength;
		void* pClassBase;
		Types::ptr_t* pOldTable,* pNewTable;

	public:
		hook_t( void* pVirtualTable );
		~hook_t( );

		template< typename _fn > void HookIndex( unsigned uIndex, _fn fnNewFunction );
		void UnhookIndex( unsigned uIndex );
	};
}

#include "Hook Manager.inl"
