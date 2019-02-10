/// Memory Manager.hpp

#pragma once

class CMemoryManager
{
private:

	HANDLE hProcess = nullptr;
	DWORD dwCurrentAccess = 0;

public:

	bool SetProcess( const std::string &strExecutable, DWORD dwAccess );

	bool Read( void* pAddress, void* pOut, std::size_t zSize );
	template< typename _t > bool Read( void* pAddress, _t& _Out );
	bool Write( void* pAddress, void* pValue, std::size_t zSize );
	template< typename _t > bool Write( void* pAddress, _t& _Value );
};

#include "Memory Manager.inl"
