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

class CImportHook
{
private:

	struct patched_import_t
	{
		std::string strImport { };
		void **pPatchedFunction = nullptr, *pOriginal = nullptr;
	};

	image_info_t _Importee { };
	std::map< HMODULE, std::vector< patched_import_t > > _Patches { };

	bool PatchAddress( void **pAddress, void *pValue );

public:

	bool Attach( HMODULE hImportee );
	bool Detach( );
	bool PatchImport( HMODULE hExporter, const std::string &strImportName, void *pPatch );
	void *GetOriginalImport( HMODULE hExporter, const std::string &strImportName );
	bool RevertPatch( HMODULE hExporter, const std::string &strImportName );
	bool RevertAllPatches( );
};
