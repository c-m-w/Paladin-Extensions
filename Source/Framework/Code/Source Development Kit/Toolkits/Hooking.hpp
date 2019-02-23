/// Hooking.hpp

#pragma once

class CVirtualTableHook
{
private:

	bool bAttached = false;
	void *pInterface = nullptr,
		**pTableAddress = nullptr,
		**pOldTable = nullptr,
		**pCurrentTable = nullptr;
	HMODULE hOrigin = nullptr;
	std::size_t zLength, zSize;

#if !defined _DEBUG

	void *pLastStubLocation = nullptr;

#endif

public:

	static std::size_t GetTableSize( void **pTable );

	bool Attach( void *pInterface );
	void Detach( );
	bool Replace( std::size_t zIndex, void *pReplacement );
	bool Replace( void *pReplacee, void *pReplacement );
	void *GetOriginalFunction( std::size_t zIndex );
};
