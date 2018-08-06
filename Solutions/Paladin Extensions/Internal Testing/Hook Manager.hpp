/// Hook Manager.hpp

#pragma once

namespace PX::Tools
{
	std::size_t PX_API EstimateTableLength( Types::ptr_t* pVirtualTable );

	struct hook_t
	{
	private:
		DWORD dwOldProtection;
		std::size_t sTableLength, sTableSize;
		void* pClassBase;
		Types::ptr_t* pOldTable,* pNewTable;
		HMODULE hAllocationModule;
		bool bSetNewTable;

	public:
		hook_t( void* pVirtualTable, const wchar_t* wszAllocationModule );
		~hook_t( );

		template< typename _fn > void HookIndex( unsigned uIndex, _fn fnNewFunction );
		void UnhookIndex( unsigned uIndex );
		void ResetTable( );
		template< typename _fn > _fn GetOriginalFunction( unsigned uIndex );

		void Cleanup( );
	};
}

#include "Hook Manager.inl"
