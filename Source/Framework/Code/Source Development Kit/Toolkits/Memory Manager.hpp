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

			cmp byte ptr [ esp - 4 ], TRUE
			jne Check

		popad
		popfd
		ret 4
	}
}

inline void __declspec( naked ) ThreadEnvironmentEnd( )
{ }

#pragma optimize( "", on )

#pragma optimize( "", off )
/// LoadLibraryExWrapper - 8h = szLibraryPath
/// LoadLibraryExWrapper - 4h = LoadLibraryA
inline void __declspec( naked ) LoadLibraryExWrapper( )
{
	__asm
	{
		pushad
		pushfd

		call Prepare

		Prepare:

			mov		eax, [ esp ]
			sub		eax, 0xE
			push	eax
			add		eax, 4
			call	eax

		popad
		popfd
		ret
	}
}

inline void __declspec( naked ) LoadLibraryExWrapperEnd( )
{ }

#pragma optimize( "", on )

#define THREAD_ENVIRONMENT_SIZE ( 16 )
#define THREAD_ENVIRONMENT_SIZE_ ( std::uintptr_t( ThreadEnvironmentEnd ) - std::uintptr_t( ThreadEnvironment ) )
#define LOAD_LIBRARY_EX_WRAPPER_SIZE ( 32 )
#define LOAD_LIBRARY_EX_WRAPPER_SIZE_ ( std::uintptr_t( LoadLibraryExWrapperEnd ) - std::uintptr_t( LoadLibraryExWrapper ) )

struct load_library_ex_wrapper
{
	const char *szLibraryPath = nullptr;
	void *pLoadLibrary = nullptr;
	unsigned char bLoadLibraryExWrapper[ LOAD_LIBRARY_EX_WRAPPER_SIZE ];

	load_library_ex_wrapper( );
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
	~worker_t( );

	bool GetContext( CONTEXT &_Out );
	bool SetContext( CONTEXT &_New );
	bool Valid( );
	bool Close( );
	bool Suspend( );
	bool Resume( );
	bool Terminate( DWORD dwExitCode = EXIT_SUCCESS );
	bool GetInstructionPointer( void *&pOut );
	bool SetInstructionPointer( void *pNew );
	bool SimulateFunctionCall( void *pFunction, void *pParameter );
	bool WaitForExecutionFinish( DWORD dwTime = INFINITE );
};

class CMemoryManager
{
private:

	inline static bool bElevated = false;

	HANDLE hProcess = nullptr;
	DWORD dwProcessID = 0;
	DWORD dwCurrentAccess = 0;
	void *pThreadEnvironment = nullptr;
	void *pLoadLibraryExWrapper = nullptr;

public:

	bool SetProcess( const std::string &strExecutable, DWORD dwAccess );
	bool CreateWorker( worker_t &_Worker, void *&pExit );
	bool FindWorker( worker_t &_Worker, DWORD dwHandleAccess, void *&pExit );

	bool Read( void* pAddress, void* pOut, std::size_t zSize );
	template< typename _t > bool Read( void* pAddress, _t& _Out );
	bool Write( void* pAddress, void* pValue, std::size_t zSize );
	template< typename _t > bool Write( void* pAddress, _t& _Value );
	bool AllocateMemory( void *&pAddress, std::size_t zSize, DWORD dwAccess );
	bool WipeMemory( void *pAddress, std::size_t zSize );
	bool FreeMemory( void *pAddress );
	bool LoadLibraryEx( const std::string &strPath, bool bUseExistingThread );
} inline _MemoryManager;

#include "Memory Manager.inl"
