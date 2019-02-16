/// Memory Manager.hpp

#pragma once

#pragma optimize( "", off )

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

inline void __declspec( naked ) ThreadEnvironmentEnd( )
{ }

#pragma optimize( "", on )

#define DONE_LOADING_LIBRARY ( 0xDEADBEEF )

#pragma optimize( "", off )

inline void __declspec( naked ) LoadLibraryExWrapper( )
{
	__asm
	{
		pushfd

		call	Prepare

		Prepare:

			pop		eax
			sub		eax,	0x12
			push	dword ptr[ eax ]
			add		eax,	4
			call	[ eax ]

		popfd
		mov		ecx, DONE_LOADING_LIBRARY
		ret
	}
}

inline void __declspec( naked ) LoadLibraryExWrapperEnd( )
{ }

#pragma optimize( "", on )

#pragma optimize( "", off )

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

inline void RelocateImageBaseEnd( )
{ }

#pragma optimize( "", on )

#pragma optimize( "", off )

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

inline void LoadDependenciesEnd( )
{ }

#pragma optimize( "", on )

#if defined _DEBUG
inline unsigned char RELOCATE_IMAGE_BASE[ ] { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x1C, 0x56, 0x8B, 0x45, 0x08, 0x89, 0x45, 0xE8, 0x8B, 0x4D, 0xE8, 0x8B, 0x55, 0x08, 0x03, 0x51, 0x3C, 0x89, 0x55, 0xF0, 0x8B, 0x45, 0xF0, 0x8B, 0x4D, 0x08, 0x2B, 0x48, 0x34, 0x89, 0x4D, 0xE4, 0xBA, 0x08, 0x00, 0x00, 0x00, 0x6B, 0xC2, 0x05, 0x8B, 0x4D, 0xF0, 0x8B, 0x55, 0x08, 0x03, 0x54, 0x01, 0x78, 0x89, 0x55, 0xFC, 0xEB, 0x0C, 0x8B, 0x45, 0xFC, 0x8B, 0x4D, 0xFC, 0x03, 0x48, 0x04, 0x89, 0x4D, 0xFC, 0x8B, 0x55, 0xFC, 0x83, 0x3A, 0x00, 0x0F, 0x84, 0x82, 0x00, 0x00, 0x00, 0x8B, 0x45, 0xFC, 0x8B, 0x48, 0x04, 0x83, 0xE9, 0x08, 0xD1, 0xE9, 0x89, 0x4D, 0xEC, 0x75, 0x02, 0xEB, 0xD6, 0x8B, 0x55, 0xFC, 0x83, 0xC2, 0x08, 0x89, 0x55, 0xF4, 0xC7, 0x45, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x09, 0x8B, 0x45, 0xF8, 0x83, 0xC0, 0x01, 0x89, 0x45, 0xF8, 0x8B, 0x4D, 0xF8, 0x3B, 0x4D, 0xEC, 0x73, 0x48, 0x8B, 0x55, 0xF8, 0x8B, 0x45, 0xF4, 0x0F, 0xB7, 0x0C, 0x50, 0x85, 0xC9, 0x74, 0x38, 0x8B, 0x55, 0xFC, 0x8B, 0x45, 0x08, 0x03, 0x02, 0x8B, 0x4D, 0xF8, 0x8B, 0x55, 0xF4, 0x0F, 0xB7, 0x0C, 0x4A, 0x81, 0xE1, 0xFF, 0x0F, 0x00, 0x00, 0x8B, 0x14, 0x08, 0x03, 0x55, 0xE4, 0x8B, 0x45, 0xF8, 0x8B, 0x4D, 0xF4, 0x0F, 0xB7, 0x04, 0x41, 0x25, 0xFF, 0x0F, 0x00, 0x00, 0x8B, 0x4D, 0xFC, 0x8B, 0x75, 0x08, 0x03, 0x31, 0x89, 0x14, 0x06, 0xEB, 0xA7, 0xE9, 0x66, 0xFF, 0xFF, 0xFF, 0x5E, 0x8B, 0xE5, 0x5D, 0xC2, 0x04, 0x00, 0xCC, 0xCC, 0xCC, 0xCC };
inline unsigned char LOAD_DEPENDENCIES[ ] { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x24, 0x8B, 0x45, 0x08, 0x89, 0x45, 0xE4, 0x8B, 0x4D, 0xE4, 0x8B, 0x55, 0x08, 0x03, 0x51, 0x3C, 0x89, 0x55, 0xE0, 0xB8, 0x08, 0x00, 0x00, 0x00, 0xC1, 0xE0, 0x00, 0x8B, 0x4D, 0xE0, 0x8B, 0x55, 0x08, 0x03, 0x54, 0x01, 0x78, 0x89, 0x55, 0xFC, 0xEB, 0x09, 0x8B, 0x45, 0xFC, 0x83, 0xC0, 0x14, 0x89, 0x45, 0xFC, 0x8B, 0x4D, 0xFC, 0x83, 0x39, 0x00, 0x0F, 0x84, 0xA8, 0x00, 0x00, 0x00, 0x8B, 0x55, 0xFC, 0x8B, 0x45, 0x08, 0x03, 0x42, 0x0C, 0x50, 0xFF, 0x55, 0x10, 0x89, 0x45, 0xEC, 0x83, 0x7D, 0xEC, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x90, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0xFC, 0x8B, 0x55, 0x08, 0x03, 0x11, 0x89, 0x55, 0xF8, 0x8B, 0x45, 0xFC, 0x8B, 0x4D, 0x08, 0x03, 0x48, 0x10, 0x89, 0x4D, 0xF4, 0xEB, 0x12, 0x8B, 0x55, 0xF8, 0x83, 0xC2, 0x04, 0x89, 0x55, 0xF8, 0x8B, 0x45, 0xF4, 0x83, 0xC0, 0x04, 0x89, 0x45, 0xF4, 0x8B, 0x4D, 0xF8, 0x83, 0x39, 0x00, 0x74, 0x53, 0x8B, 0x55, 0xF8, 0x8B, 0x02, 0x25, 0x00, 0x00, 0x00, 0x80, 0x76, 0x10, 0x8B, 0x4D, 0xF8, 0x8B, 0x11, 0x81, 0xE2, 0xFF, 0xFF, 0x00, 0x00, 0x89, 0x55, 0xF0, 0xEB, 0x0F, 0x8B, 0x45, 0xF8, 0x8B, 0x08, 0x8B, 0x55, 0x08, 0x8D, 0x44, 0x0A, 0x02, 0x89, 0x45, 0xF0, 0x8B, 0x4D, 0xF0, 0x89, 0x4D, 0xDC, 0x8B, 0x55, 0xDC, 0x52, 0x8B, 0x45, 0xEC, 0x50, 0xFF, 0x55, 0x0C, 0x89, 0x45, 0xE8, 0x83, 0x7D, 0xE8, 0x00, 0x75, 0x04, 0x33, 0xC0, 0xEB, 0x14, 0x8B, 0x4D, 0xF4, 0x8B, 0x55, 0xE8, 0x89, 0x11, 0xEB, 0x93, 0xE9, 0x43, 0xFF, 0xFF, 0xFF, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x8B, 0xE5, 0x5D, 0xC2, 0x0C, 0x00, 0xCC, 0xCC, 0xCC, 0xCC };
#else
inline unsigned char *RELOCATE_IMAGE_BASE = decltype( RELOCATE_IMAGE_BASE )( RelocateImageBase );
inline unsigned char *LOAD_DEPENDENCIES = decltype( LOAD_DEPENDENCIES )( LoadDependencies );
#endif

#define THREAD_ENVIRONMENT_SIZE ( 16 )
#define THREAD_ENVIRONMENT_SIZE_ ( std::uintptr_t( ThreadEnvironmentEnd ) - std::uintptr_t( ThreadEnvironment ) )
#define LOAD_LIBRARY_EX_WRAPPER_SIZE ( 32 )
#define LOAD_LIBRARY_EX_WRAPPER_SIZE_ ( std::uintptr_t( LoadLibraryExWrapperEnd ) - std::uintptr_t( LoadLibraryExWrapper ) )
#define RELOCATE_IMAGE_BASE_SIZE ( 225 )
#define RELOCATE_IMAGE_BASE_SIZE_ ( std::uintptr_t( RelocateImageBaseEnd ) - std::uintptr_t( RelocateImageBase ) )
#define LOAD_DEPENDENCIES_SIZE ( 251 )
#define LOAD_DEPENDENCIES_SIZE_ ( std::uintptr_t( LoadDependenciesEnd ) - std::uintptr_t( LoadDependencies ) )

struct load_library_ex_wrapper_t
{
	const char *szLibraryPath = nullptr;
	void *pLoadLibrary = nullptr;
	constexpr static DWORD BUFFER = 0xCCCCCCCC;
	unsigned char bLoadLibraryExWrapper[ LOAD_LIBRARY_EX_WRAPPER_SIZE ];

	load_library_ex_wrapper_t( );
};

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
};

struct image_info_t
{
	void *pData;

	image_info_t( void *pData );

	bool ValidImage( );
	std::size_t GetImageSize( );
	std::size_t GetHeaderSize( );
	std::size_t GetSectionCount( );
	IMAGE_DOS_HEADER *GetOperatingSystemHeader( );
	IMAGE_NT_HEADERS *GetNewTechnologyHeaders( void *pImageBase = nullptr );
	IMAGE_SECTION_HEADER *GetSectionHeader( std::size_t zSection );
	IMAGE_IMPORT_DESCRIPTOR *GetImportDescriptor( void *pImageBase = nullptr );
};

class CMemoryManager
{
private:

	constexpr static auto MAX_LIBRARY_LOAD_TIME = 10000ui64;
	constexpr static auto UNKNOWN_BYTE = -1i16;

	using pattern_t = std::vector< __int16 >;

	static pattern_t ParsePattern( const std::string &strPattern );

	inline static bool bElevated = false;

	HANDLE hProcess = nullptr;
	DWORD dwProcessID = 0;
	DWORD dwCurrentAccess = 0;
	void *pThreadEnvironment = nullptr;
	void *pLoadLibraryExWrapper = nullptr;
	void *pManualMapFunctions = nullptr;

public:

	static bool ManuallyLoadLibrary( const std::string &strData, HMODULE *pModuleHandle = nullptr );
	static void *FindPattern( HMODULE hLocation, const std::string &strPattern );

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
	bool ManuallyLoadLibraryEx( const std::string &strData, bool bUseExistingThread, bool bEraseHeaders, bool bEraseDiscardableSections, HMODULE *pModuleHandle = nullptr );
} inline _MemoryManager;

#include "Memory Manager.inl"
