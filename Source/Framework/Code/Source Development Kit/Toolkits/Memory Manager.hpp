/// Memory Manager.hpp

#pragma once

#if defined _DEBUG

inline void __declspec( naked ) ThreadEnvironment( bool *bExit )
{
	__asm
	{
		pushad
		pushfd

		Check:

			mov		edx,		dword ptr[ esp + 0x28 ]
			cmp		[ edx ],	FALSE
			je		Check

		popfd
		popad
		ret 4
	}
}

inline void __declspec( naked ) LoadLibraryExWrapper( const char *szLibraryName, void *pLoadLibrary )
{
	__asm
	{
		pushfd

		mov		ecx,	[ esp + 0xC ]
		push	[ esp + 0x8 ]
		call	ecx

		popfd
		ret		8
	}
}

inline void __stdcall RelocateImageBase( void *pImage )
{
	const auto pOperatingSystemHeaders = reinterpret_cast< IMAGE_DOS_HEADER * >( pImage );
	const auto pNewTechnologyHeaders = reinterpret_cast< IMAGE_NT_HEADERS * >( std::uintptr_t( pImage ) + pOperatingSystemHeaders->e_lfanew );
	const auto zRelocationDifference = std::uintptr_t( pImage ) - pNewTechnologyHeaders->OptionalHeader.ImageBase;
	
	for ( auto p = reinterpret_cast< IMAGE_BASE_RELOCATION * >( std::uintptr_t( pImage ) + pNewTechnologyHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].VirtualAddress );
		p->VirtualAddress != NULL;
		p = reinterpret_cast< IMAGE_BASE_RELOCATION * >( std::uintptr_t( p ) + p->SizeOfBlock ) )
	{
		const auto zBlockCount = ( p->SizeOfBlock - sizeof( IMAGE_BASE_RELOCATION ) ) / sizeof( WORD );
		if ( zBlockCount == 0 )
			continue;
	
		const auto pBlocks = reinterpret_cast< unsigned __int16 * >( std::uintptr_t( p ) + sizeof( IMAGE_BASE_RELOCATION ) );
		for ( auto z = 0u; z < zBlockCount; z++ )
			if ( pBlocks[ z ] != NULL )
				*reinterpret_cast< std::uintptr_t * >( std::uintptr_t( pImage ) + p->VirtualAddress + ( pBlocks[ z ] & 0xFFF ) ) += zRelocationDifference;
	}
}

inline BOOL __stdcall LoadDependencies( void *pImage, void *pGetProcAddress, void *pLoadLibrary )
{
	const auto pOperatingSystemHeaders = reinterpret_cast< IMAGE_DOS_HEADER * >( pImage );
	const auto pNewTechnologyHeaders = reinterpret_cast< IMAGE_NT_HEADERS * >( std::uintptr_t( pImage ) + pOperatingSystemHeaders->e_lfanew );

	for ( auto p = reinterpret_cast< IMAGE_IMPORT_DESCRIPTOR * >( std::uintptr_t( pImage ) + pNewTechnologyHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].VirtualAddress );
		  p->Characteristics != NULL;
		  p = reinterpret_cast< IMAGE_IMPORT_DESCRIPTOR * >( std::uintptr_t( p ) + sizeof( IMAGE_IMPORT_DESCRIPTOR ) ) )
	{
		const auto hCurrent = reinterpret_cast< HMODULE( __stdcall * )( const char * ) >( pLoadLibrary )( reinterpret_cast< const char * >( std::uintptr_t( pImage ) + p->Name ) );
		if ( hCurrent == nullptr )
			return FALSE;

		for ( auto pOriginal = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( pImage ) + p->OriginalFirstThunk ),
			  pNew = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( pImage ) + p->FirstThunk );
			  pOriginal->u1.AddressOfData != NULL; 
			  pOriginal = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( pOriginal ) + sizeof( IMAGE_THUNK_DATA ) ),
			  pNew = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( pNew ) + sizeof( IMAGE_THUNK_DATA ) ) )
		{
			const auto szImport = reinterpret_cast< const char * >( ( pOriginal->u1.Ordinal & IMAGE_ORDINAL_FLAG ) > 0 ? reinterpret_cast< void * >( pOriginal->u1.Ordinal & 0xFFFF )
															  : reinterpret_cast< IMAGE_IMPORT_BY_NAME * >( std::uintptr_t( pImage ) + pOriginal->u1.AddressOfData )->Name );
			const auto pImport = reinterpret_cast< FARPROC( __stdcall * )( HMODULE, const char * ) >( pGetProcAddress )( hCurrent, szImport );
			if ( pImport == nullptr )
				return FALSE;

			pNew->u1.Function = std::uintptr_t( pImport );
		}
	}

	return TRUE;
}

inline void __declspec( naked ) TrampolineStub( )
{
	__asm
	{
		mov	eax, 0xCCCCCCCC
		jmp eax
	}
}

inline unsigned char bThreadEnvironment[ ] { 0x60, 0x9C, 0x8B, 0x54, 0x24, 0x28, 0x80, 0x3A, 0x00, 0x74, 0xF7, 0x9D, 0x61, 0xC2, 0x04, 0x00, 0xCC, 0xCC, 0xCC, 0xCC };
inline unsigned char bLoadLibraryExWrapper[ ] { 0x9C, 0x8B, 0x4C, 0x24, 0x0C, 0xFF, 0x74, 0x24, 0x08, 0xFF, 0xD1, 0x9D, 0xC2, 0x08, 0x00, 0xCC, 0xCC, 0xCC, 0xCC };
inline unsigned char bRelocateImageBase[ ] { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x1C, 0x56, 0x8B, 0x45, 0x08, 0x89, 0x45, 0xE8, 0x8B, 0x4D, 0xE8, 0x8B, 0x55, 0x08, 0x03, 0x51, 0x3C, 0x89, 0x55, 0xF0, 0x8B, 0x45, 0xF0, 0x8B, 0x4D, 0x08, 0x2B, 0x48, 0x34, 0x89, 0x4D, 0xE4, 0xBA, 0x08, 0x00, 0x00, 0x00, 0x6B, 0xC2, 0x05, 0x8B, 0x4D, 0xF0, 0x8B, 0x55, 0x08, 0x03, 0x54, 0x01, 0x78, 0x89, 0x55, 0xFC, 0xEB, 0x0C, 0x8B, 0x45, 0xFC, 0x8B, 0x4D, 0xFC, 0x03, 0x48, 0x04, 0x89, 0x4D, 0xFC, 0x8B, 0x55, 0xFC, 0x83, 0x3A, 0x00, 0x0F, 0x84, 0x82, 0x00, 0x00, 0x00, 0x8B, 0x45, 0xFC, 0x8B, 0x48, 0x04, 0x83, 0xE9, 0x08, 0xD1, 0xE9, 0x89, 0x4D, 0xEC, 0x75, 0x02, 0xEB, 0xD6, 0x8B, 0x55, 0xFC, 0x83, 0xC2, 0x08, 0x89, 0x55, 0xF4, 0xC7, 0x45, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x09, 0x8B, 0x45, 0xF8, 0x83, 0xC0, 0x01, 0x89, 0x45, 0xF8, 0x8B, 0x4D, 0xF8, 0x3B, 0x4D, 0xEC, 0x73, 0x48, 0x8B, 0x55, 0xF8, 0x8B, 0x45, 0xF4, 0x0F, 0xB7, 0x0C, 0x50, 0x85, 0xC9, 0x74, 0x38, 0x8B, 0x55, 0xFC, 0x8B, 0x45, 0x08, 0x03, 0x02, 0x8B, 0x4D, 0xF8, 0x8B, 0x55, 0xF4, 0x0F, 0xB7, 0x0C, 0x4A, 0x81, 0xE1, 0xFF, 0x0F, 0x00, 0x00, 0x8B, 0x14, 0x08, 0x03, 0x55, 0xE4, 0x8B, 0x45, 0xF8, 0x8B, 0x4D, 0xF4, 0x0F, 0xB7, 0x04, 0x41, 0x25, 0xFF, 0x0F, 0x00, 0x00, 0x8B, 0x4D, 0xFC, 0x8B, 0x75, 0x08, 0x03, 0x31, 0x89, 0x14, 0x06, 0xEB, 0xA7, 0xE9, 0x66, 0xFF, 0xFF, 0xFF, 0x5E, 0x8B, 0xE5, 0x5D, 0xC2, 0x04, 0x00, 0xCC, 0xCC, 0xCC, 0xCC };
inline unsigned char bLoadDependencies[ ] { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x24, 0x8B, 0x45, 0x08, 0x89, 0x45, 0xE4, 0x8B, 0x4D, 0xE4, 0x8B, 0x55, 0x08, 0x03, 0x51, 0x3C, 0x89, 0x55, 0xE0, 0xB8, 0x08, 0x00, 0x00, 0x00, 0xC1, 0xE0, 0x00, 0x8B, 0x4D, 0xE0, 0x8B, 0x55, 0x08, 0x03, 0x54, 0x01, 0x78, 0x89, 0x55, 0xFC, 0xEB, 0x09, 0x8B, 0x45, 0xFC, 0x83, 0xC0, 0x14, 0x89, 0x45, 0xFC, 0x8B, 0x4D, 0xFC, 0x83, 0x39, 0x00, 0x0F, 0x84, 0xA8, 0x00, 0x00, 0x00, 0x8B, 0x55, 0xFC, 0x8B, 0x45, 0x08, 0x03, 0x42, 0x0C, 0x50, 0xFF, 0x55, 0x10, 0x89, 0x45, 0xEC, 0x83, 0x7D, 0xEC, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x90, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0xFC, 0x8B, 0x55, 0x08, 0x03, 0x11, 0x89, 0x55, 0xF8, 0x8B, 0x45, 0xFC, 0x8B, 0x4D, 0x08, 0x03, 0x48, 0x10, 0x89, 0x4D, 0xF4, 0xEB, 0x12, 0x8B, 0x55, 0xF8, 0x83, 0xC2, 0x04, 0x89, 0x55, 0xF8, 0x8B, 0x45, 0xF4, 0x83, 0xC0, 0x04, 0x89, 0x45, 0xF4, 0x8B, 0x4D, 0xF8, 0x83, 0x39, 0x00, 0x74, 0x53, 0x8B, 0x55, 0xF8, 0x8B, 0x02, 0x25, 0x00, 0x00, 0x00, 0x80, 0x76, 0x10, 0x8B, 0x4D, 0xF8, 0x8B, 0x11, 0x81, 0xE2, 0xFF, 0xFF, 0x00, 0x00, 0x89, 0x55, 0xF0, 0xEB, 0x0F, 0x8B, 0x45, 0xF8, 0x8B, 0x08, 0x8B, 0x55, 0x08, 0x8D, 0x44, 0x0A, 0x02, 0x89, 0x45, 0xF0, 0x8B, 0x4D, 0xF0, 0x89, 0x4D, 0xDC, 0x8B, 0x55, 0xDC, 0x52, 0x8B, 0x45, 0xEC, 0x50, 0xFF, 0x55, 0x0C, 0x89, 0x45, 0xE8, 0x83, 0x7D, 0xE8, 0x00, 0x75, 0x04, 0x33, 0xC0, 0xEB, 0x14, 0x8B, 0x4D, 0xF4, 0x8B, 0x55, 0xE8, 0x89, 0x11, 0xEB, 0x93, 0xE9, 0x43, 0xFF, 0xFF, 0xFF, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x8B, 0xE5, 0x5D, 0xC2, 0x0C, 0x00, 0xCC, 0xCC, 0xCC, 0xCC };
inline unsigned char bTrampolineStub[ ] { 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0xFF, 0xE0, 0xCC, 0xCC, 0xCC, 0xCC };

inline std::size_t zThreadEnvironment		= 20;
inline std::size_t zLoadLibraryExWrapper	= 19;
inline std::size_t zRelocateImageBase		= 225;
inline std::size_t zLoadDependencies		= 251;
inline std::size_t zTrampolineStub			= 11;

inline std::string strNewestInsertInvertedFunctionTable = ENC( "53 56 57 8D 45 F8 8B FA" );
inline std::ptrdiff_t ptrNewestInsertInvertedFunctionTable = -8;
inline std::string strNewestInvertedFunctionTable = ENC( "33 F6 46 3B C6" );
inline std::ptrdiff_t ptrNewestInvertedFunctionTable = -0x1B;
inline std::string strBackupInsertInvertedFunctionTable = ENC( "8D 45 F0 89 55 F8 50 8D 55 F4" );
inline std::ptrdiff_t ptrBackupInsertInvertedFunctionTable = -0xB,
						ptrBackupInvertedFunctionTable = 0x57;
inline std::string strResortInsertInvertedFunctionTable = ENC( "53 56 57 8B DA 8B F9 50" );
inline std::ptrdiff_t ptrResortInsertInvertedFunctionTable = -0xB;
inline std::ptrdiff_t ptrResortWindows10InvertedFunctionTable = 0xB5,
						ptrResortPreviousWindowsInvertedFunctionTable = 0xB6;

#else

inline unsigned char *bThreadEnvironment	= nullptr;
inline unsigned char *bLoadLibraryExWrapper = nullptr;
inline unsigned char *bRelocateImageBase	= nullptr;
inline unsigned char *bLoadDependencies		= nullptr;
inline unsigned char *bTrampolineStub		= nullptr;

inline std::size_t zThreadEnvironment		= 0;
inline std::size_t zLoadLibraryExWrapper	= 0;
inline std::size_t zRelocateImageBase		= 0;
inline std::size_t zLoadDependencies		= 0;
inline std::size_t zTrampolineStub			= 0;

inline std::string strNewestInsertInvertedFunctionTable;
inline std::ptrdiff_t ptrNewestInsertInvertedFunctionTable = 0;
inline std::string strNewestInvertedFunctionTable;
inline std::ptrdiff_t ptrNewestInvertedFunctionTable = 0;
inline std::string strBackupInsertInvertedFunctionTable;
inline std::ptrdiff_t ptrBackupInsertInvertedFunctionTable = 0,
						ptrBackupInvertedFunctionTable = 0;
inline std::string strResortInsertInvertedFunctionTable;
inline std::ptrdiff_t ptrResortInsertInvertedFunctionTable = 0;
inline std::ptrdiff_t ptrResortWindows10InvertedFunctionTable = 0,
						ptrResortPreviousWindowsInvertedFunctionTable = 0;

#endif


#define GET_SHELLCODE_LOCATION( _Name, _Shellcode )					\
	inline void *_Name( ) { return GetShellcodeLocation( _Shellcode ); }

struct worker_t
{
private:

	bool bSuspended = false;

public:

	DWORD dwThreadID = 0;
	HANDLE hThread = nullptr;
	DWORD dwCurrentAccess = 0;

	worker_t( ) = default;
	explicit worker_t( DWORD dwThreadID, DWORD dwNewAccess );
	explicit worker_t( HANDLE hThread, DWORD dwAccess );

	bool GetContext( CONTEXT &_Out );
	bool SetContext( CONTEXT &_New );
	bool Valid( );
	bool Close( );
	bool Suspend( );
	bool Resume( );
	bool Terminate( DWORD dwExitCode = EXIT_SUCCESS );
	bool GetInstructionPointer( void *&pOut );
	bool SetInstructionPointer( void *pNew );
	bool SimulateFunctionCall( void *pFunction );
	bool ExecutingFunction( void *pFunction, std::size_t zFunctionSize );
	bool WaitForExecutionFinish( DWORD dwTime = INFINITE );
	template< typename _t > bool Push( _t _Value );
	template< typename _t > bool Pop( _t &_Out );

	friend class CMemoryManager;
};

struct image_info_t
{
private:

	void *pData = nullptr;

public:

	image_info_t( ) = default;
	image_info_t( void *pData );

	operator HMODULE( ) const;
	operator bool( ) const;

	bool ValidImage( ) const;
	std::size_t GetImageSize( ) const;
	std::size_t GetHeaderSize( ) const;
	std::size_t GetSectionCount( ) const;
	IMAGE_DOS_HEADER *GetOperatingSystemHeader( ) const;
	IMAGE_NT_HEADERS *GetNewTechnologyHeaders( ) const;
	IMAGE_SECTION_HEADER *GetSectionHeader( std::size_t zSection ) const;
	IMAGE_IMPORT_DESCRIPTOR *GetFirstImport( ) const;
	IMAGE_IMPORT_DESCRIPTOR *GetNextImport( IMAGE_IMPORT_DESCRIPTOR *pCurrent ) const;
	IMAGE_IMPORT_DESCRIPTOR *GetImportDescriptor( HMODULE hExporter ) const;
	IMAGE_EXPORT_DIRECTORY *GetExports( ) const;
	bool GetImportName( IMAGE_THUNK_DATA *pImportData, std::string &strOut ) const;
	IMAGE_THUNK_DATA *FindImport( HMODULE hExporter, void *pImport ) const;
	IMAGE_THUNK_DATA *FindImport( HMODULE hExporter, const std::string &strImport ) const;
	std::string GenerateUniqueHash( ) const;

	friend class CMemoryManager;
};

template< typename T >
struct _RTL_INVERTED_FUNCTION_TABLE_ENTRY
{
	T     ExceptionDirectory;
	T     ImageBase;
	uint32_t ImageSize;
	uint32_t SizeOfTable;
};

template< typename T >
struct _RTL_INVERTED_FUNCTION_TABLE
{
	ULONG Count;
	ULONG MaxCount;
	ULONG Epoch;
	UCHAR Overflow;
	_RTL_INVERTED_FUNCTION_TABLE_ENTRY< T > Entries[ 0x200 ];
};

class CMemoryManager: public IBase
{
private:

	constexpr static auto MAX_LIBRARY_LOAD_TIME = 10000ui64;

	enum EShellcode
	{
		THREAD_ENVIRONMENT,
		LOAD_LIBRARY_EX_WRAPPER,
		RELOCATE_IMAGE_BASE,
		LOAD_DEPENDENCIES
	};

public:

	struct pattern_t
	{
	private:

		constexpr static auto UNKNOWN_BYTE = -1i16;

		std::vector< __int16 > vecPattern { };
		void **pOutput = nullptr;
		std::ptrdiff_t ptrOffset = 0;
		std::function< void( ) > fnOnFound = nullptr;
		unsigned uProgress = 0u;
		int iRelative = 0;

	public:

		static std::vector< __int16 > ParsePattern( const std::string &strPattern );

		pattern_t( ) = default;
		pattern_t( const std::string &strPattern, void **pOutput, std::ptrdiff_t ptrOffset, std::function< void( ) > fnOnFound = nullptr );
		pattern_t( const nlohmann::json &_Data, void **pOutput, std::function< void( ) > fnOnFound = nullptr );

		bool Valid( ) const;

		friend class CMemoryManager;
	};

private:

	bool Initialize( ) override;
	void Uninitialize( ) override;

	bool EnsureDataValidity( );
	bool EnsureShellcodeValidity( );
	bool EnsureShellcodePresence( );
	void *GetShellcodeLocation( EShellcode _Shellcode );
	GET_SHELLCODE_LOCATION( GetThreadEnvironmentLocation, THREAD_ENVIRONMENT )
	GET_SHELLCODE_LOCATION( GetLoadLibraryExWrapperLocation, LOAD_LIBRARY_EX_WRAPPER )
	GET_SHELLCODE_LOCATION( GetRelocateImageBaseLocation, RELOCATE_IMAGE_BASE )
	GET_SHELLCODE_LOCATION( GetLoadDependenciesLocation, LOAD_DEPENDENCIES )

	inline static bool bElevated = false;
	inline static void *pInsertInvertedFunctionTable = nullptr, *pInvertedFunctionTable = nullptr;

	__declspec( property( get = GetThreadEnvironmentLocation ) )	void *pThreadEnvironment;
	__declspec( property( get = GetLoadLibraryExWrapperLocation ) ) void *pLoadLibraryExWrapper;
	__declspec( property( get = GetRelocateImageBaseLocation ) )	void *pRelocateImageBase;
	__declspec( property( get = GetLoadDependenciesLocation ) )		void *pLoadDependencies;

	HANDLE hProcess = nullptr;
	DWORD dwProcessID = 0;
	DWORD dwCurrentAccess = 0;
	void *pShellcode = nullptr;
	std::map< HMODULE, std::vector< pattern_t > > _PatternsToFind;

public:

	static bool IsExecutableCode( void *pAddress );
	static void *FindFreeMemory( HMODULE hModule, std::size_t zMinimumSize, DWORD dwAccess, void *pStart = nullptr );
	static HMODULE GetOrigin( void *pAddress );
	static std::size_t GetPageSize( );

	bool AddPattern( const std::string &strModule, const pattern_t &_Pattern );
	bool AddPattern( HMODULE hModule, const pattern_t &_Pattern );
	bool FindPatterns( );

	bool SetProcess( DWORD dwProcessID, DWORD dwAccess );
	bool SetProcess( const std::string &strExecutable, DWORD dwAccess );
	bool CreateWorker( worker_t &_Worker, void *&pExit );
	bool FindWorker( worker_t &_Worker, DWORD dwHandleAccess, void *&pExit );

	bool Read( void* pAddress, void* pOut, std::size_t zSize );
	template< typename _t > bool Read( void* pAddress, _t &_Out );
	bool Write( void* pAddress, void* pValue, std::size_t zSize );
	template< typename _t > bool Write( void* pAddress, _t _Value );
	bool AllocateMemory( void *&pAddress, std::size_t zSize, DWORD dwAccess );
	bool WipeMemory( void *pAddress, std::size_t zSize );
	bool FreeMemory( void *pAddress );
	bool LoadLibraryEx( const std::string &strPath, bool bUseExistingThread, HMODULE *pModuleHandle = nullptr );
	bool ManuallyLoadLibraryEx( const std::string &strData, bool bUseExistingThread, bool bEnableExceptions, bool bEraseHeaders, bool bEraseDiscardableSections, HMODULE *pModuleHandle = nullptr );

	friend class CVirtualTableHook;
} inline _MemoryManager;

using pattern_t = CMemoryManager::pattern_t;

#include "Memory Manager.inl"
