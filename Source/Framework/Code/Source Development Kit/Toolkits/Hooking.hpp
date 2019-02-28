/// Hooking.hpp

#pragma once

/** \brief Tool for modifying virtual table functions to detour them. */
class CVirtualTableHook
{
private:

	/** \brief Whether or not it is currently attached\n 
				to a virtual function table. */
	bool bAttached = false;
	/** \brief The interface that is being detoured. */
	void *pInterface = nullptr;
	/** \brief Address of the original virtual function table. */
	void **pTableAddress = nullptr;
	/** \brief Address of the current virtual function table. */
	void **pCurrentTable = nullptr;
	HMODULE hOrigin = nullptr;
	std::size_t zLength, zSize;

#if !defined _DEBUG

	/** \brief Address of the last stub that was found. */
	void *pLastStubLocation = nullptr;

#endif

public:

	/** \brief Gets the size of a virtual function table. */
	/** \param pTable Address of the table to be analyzed. */
	/** \return How many functions are contained in the table. */
	static std::size_t GetTableSize( void **pTable );

	/** \brief Attaches to an interface to prepare for detouring functions. */
	/** \param pInterface The interface that is to be attached to. */
	/** \return Whether or not attaching was successful. */
	bool Attach( void *pInterface );
	/** \brief Detaches from an interface and no longer detours functions. */
	void Detach( );
	/** \brief Replaces a function at a specified index with another. */
	/** \param zIndex Index of the function to be replaced. */
	/** \param pReplacement The new function that should be detoured to. */
	/** \return Whether or not detouring the function was successful. */
	bool Replace( std::size_t zIndex, void *pReplacement );
	/** \brief Replaces a function with a specified address in the table with another.\n 
				The table will be searched until the index of the function is determined, at\n 
				which point it is detoured. */
	/** \param pReplacee The function address that is to be replaced. */
	/** \param pReplacement The function address that is to replace the other. */
	/** \return Whether or not detouring the function was successful. */
	bool Replace( void *pReplacee, void *pReplacement );
	/** \brief Obtains the address of the original function at a specified index\n 
				so that it is able to be called after it is detoured. */
	/** \param zIndex The index of the function. */
	/** \return The address of the original function. */
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

	bool bAttached = false;
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

class CExportHook
{
private:

	bool bAttached = false;
	std::vector< void * > vecOldExports { };
	image_info_t _Exporter { };

public:

	bool Attach( HMODULE hExporter );
	bool Detach( );
	bool PatchExport( void *pFunction, void *pPatch );
	bool PatchExport( const std::string &strExportName, void *pPatch );
	void *GetOriginalExport( const std::string &strExportName );
	bool RevertPatch( void *pOriginal );
	bool RevertPatch( const std::string &strExportName );
	bool RevertAllPatches( );
};

class CExceptionHook
{
private:

	static constexpr auto PROTECTION = PAGE_EXECUTE | PAGE_GUARD;
	static constexpr auto STEP_OVER = 0x100;

	static inline std::vector< std::pair< void *, void * > > vecHooks { };
	static inline void *pHandlerHandle = nullptr;

	bool bAttached = false;
	DWORD dwOldProtection = PAGE_NOACCESS;
	void *pProtectedArea = nullptr, *pHook = nullptr;

public:

	static bool AddHandler( );
	static bool RemoveHandler( );

	bool Attach( void *pFunction, void *pCallback );
	bool Detach( );

	friend DWORD ExceptionHandler( EXCEPTION_POINTERS *pRecord );
};

class CPatchHook
{
private:

	static constexpr unsigned char CALL_OPCODE = 0xE8;
	static constexpr auto CALL_SIZE = 5;

	static inline std::map< void *, void * > _PatchedFunctions { };
	bool bPatched = false;
	std::vector< unsigned char > vecOldBytes { };
	void *pPatchedData = nullptr;

public:

	bool Patch( void *pFunction, void *pHook );
	bool Unpatch( );

	friend void *__stdcall FindHook( void *pFunction );
};
