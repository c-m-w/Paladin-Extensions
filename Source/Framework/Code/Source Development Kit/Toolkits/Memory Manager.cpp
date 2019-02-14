/// Memory Manager.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

load_library_ex_wrapper::load_library_ex_wrapper( )
{
	memcpy( bLoadLibraryExWrapper, LoadLibraryExWrapper, LOAD_LIBRARY_EX_WRAPPER_SIZE );
}

worker_t::worker_t( DWORD dwThreadID, DWORD dwNewAccess ): dwThreadID( dwThreadID ), dwCurrentAccess( dwNewAccess )
{
	if ( dwThreadID == 0 )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Invalid thread ID passed to worker_t constructor." ) );
	
	if ( dwNewAccess == 0 )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Invalid thread access passed to worker_t constructor." ) );

	hThread = OpenThread( dwNewAccess, FALSE, dwThreadID );
	if ( hThread == nullptr
		 || hThread == INVALID_HANDLE_VALUE )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Unable to open thread with id %08X and access %08X." ), dwThreadID, dwNewAccess );
	
}

worker_t::worker_t( HANDLE hThread, DWORD dwAccess ): hThread( hThread ), dwCurrentAccess( dwAccess )
{
	if ( hThread == nullptr
		 || hThread == INVALID_HANDLE_VALUE )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Invalid thread handle passed to worker_t constructor." ) );


	dwThreadID = GetThreadId( hThread );
	if ( dwThreadID == 0 )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Unable to get thread id from handle %08X." ), hThread );
}

bool worker_t::GetContext( CONTEXT &_Out )
{
	_Out.ContextFlags = CONTEXT_FULL;
	if ( !( dwCurrentAccess & THREAD_GET_CONTEXT ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to get context of thread with insufficient handle privileges." ) );

	return GetThreadContext( hThread, &_Out ) == FALSE ?
		( _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get context of thread." ) ), false ) : true;
}

bool worker_t::SetContext( CONTEXT &_New )
{
	_New.ContextFlags = CONTEXT_FULL;
	if ( !( dwCurrentAccess & THREAD_GET_CONTEXT ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to set context of thread with insufficient handle privileges." ) );

	return SetThreadContext( hThread, &_New ) == FALSE ?
		( _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to set context of thread." ) ), false ) : true;
}

bool worker_t::Valid( )
{
	return dwThreadID != 0
		&& hThread != nullptr
		&& hThread != INVALID_HANDLE_VALUE
		&& dwCurrentAccess != 0;
}

bool worker_t::Close( )
{
	if ( hThread == nullptr
		 || hThread == INVALID_HANDLE_VALUE )
		return _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to close an invalid thread handle." ) ), false;

	return CloseHandle( hThread ) == FALSE ?
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Failed to close thread handle %08X." ), hThread ), false : hThread = nullptr, true;
}

bool worker_t::Suspend( )
{
	if ( bSuspended )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to suspend a thread which is already suspended." ) );

	if ( !( dwCurrentAccess & THREAD_SUSPEND_RESUME ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to suspend a thread without sufficient handle privileges." ) );

	return SuspendThread( hThread ) == UINT_MAX ? ( _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to suspend thread." ) ), false ) : ( bSuspended = true, true );
}

bool worker_t::Resume( )
{
	if ( !bSuspended )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to resume a thread which is not suspended." ) );

	if ( !( dwCurrentAccess & THREAD_SUSPEND_RESUME ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to resume a thread without sufficient handle privileges." ) );

	return ResumeThread( hThread ) == DWORD( -1 ) ?
		_Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to resume thread." ) ), false : bSuspended = false, true;
}

bool worker_t::Terminate( DWORD dwExitCode /*= EXIT_SUCCESS*/ )
{
	if ( !( dwCurrentAccess & THREAD_TERMINATE ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to terminate a thread without sufficient handle privileges." ) );

	return TerminateThread( hThread, dwExitCode ) == FALSE ? _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to terminate thread." ) ), false
		: Close( ), true;
}

bool worker_t::GetInstructionPointer( void *&pOut )
{
	CONTEXT _Thread;
	return GetContext( _Thread ) ? pOut = reinterpret_cast< void * >( _Thread.Eip ), true : false;
}

bool worker_t::SetInstructionPointer( void *pNew )
{
	CONTEXT _Thread;
	return GetContext( _Thread ) ? ( _Thread.Eip = DWORD( pNew ), SetContext( _Thread ) ? true : false ) : false;
}

bool worker_t::SimulateFunctionCall( void *pFunction )
{
	void *pInstructionPointer;
	CONTEXT _ThreadContext;

	if ( !Suspend( )
		 || !GetInstructionPointer( pInstructionPointer )
		 || !Push( pInstructionPointer )
		 || !GetContext( _ThreadContext ) )
		return Resume( ), false;

	_ThreadContext.Eip = DWORD( pFunction );
	return SetContext( _ThreadContext ) && Resume( );
}

bool worker_t::WaitForExecutionFinish( DWORD dwTime )
{
	return WaitForSingleObject( hThread, dwTime ) == WAIT_OBJECT_0 ? true : _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Waiting for thread signal state failed." ) ), false;
}

bool CMemoryManager::SetProcess( const std::string &strExecutable, DWORD dwAccess )
{
	if ( !bElevated && !( bElevated = SI.ElevateProcess( ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Cannot elevate current process." ) ), false;

	if ( hProcess != nullptr )
		if ( CloseHandle( hProcess ) == FALSE )
			_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Unable to close old process handle." ) );

	if ( pThreadEnvironment != nullptr )
		if ( !FreeMemory( pThreadEnvironment ) )
			_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Unable to free ThreadEnvironment memory." ) );

	if ( pLoadLibraryExWrapper != nullptr )
		if ( !FreeMemory( pLoadLibraryExWrapper ) )
			_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Unable to free LoadLibraryExWrapper memory." ) );

	hProcess = nullptr;
	pThreadEnvironment = nullptr;
	pLoadLibraryExWrapper = nullptr;

	if ( dwAccess == NULL )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Access to open executable %s is invalid." ), strExecutable.c_str( ) ), false;

	if ( !SI.GetProcessID( strExecutable, dwProcessID ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get process id of executable %s." ), strExecutable.c_str( ) ), false;

	hProcess = OpenProcess( dwAccess, FALSE, dwProcessID );
	if ( hProcess == nullptr
		 || hProcess == INVALID_HANDLE_VALUE )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to open process handle of executable %s." ), strExecutable.c_str( ) ), false;

	dwCurrentAccess = dwAccess;
	return true;
}

bool CMemoryManager::CreateWorker( worker_t &_Worker, void *&pExit )
{	
	if ( !( dwCurrentAccess & PROCESS_CREATE_THREAD ) )
		_Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Insufficient privileges to create a thread." ) );

	if ( !pThreadEnvironment )
		if ( !AllocateMemory( pThreadEnvironment, THREAD_ENVIRONMENT_SIZE, PAGE_EXECUTE_READWRITE )
			 || !Write( pThreadEnvironment, ThreadEnvironment, THREAD_ENVIRONMENT_SIZE ) )
			 return false;

	DWORD dwThreadID;
	_Worker = worker_t( CreateRemoteThread( hProcess, nullptr, NULL, LPTHREAD_START_ROUTINE( pThreadEnvironment ), pExit, NULL, &dwThreadID ), THREAD_ALL_ACCESS );
	return _Worker.Valid( ) ? true : ( _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to create a worker." ) ), false );
}

bool CMemoryManager::FindWorker( worker_t &_Worker, DWORD dwHandleAccess, void *&pExit )
{
	CSystemInformation::thread_list_t _Threads { };
	if ( !SI.GetProcessThreads( dwProcessID, _Threads ) )
		return false;

	auto dwThreadID = _Threads.front( ).first, dwPriority = _Threads.front( ).second;
	for ( auto &_Thread : _Threads )
		if ( _Thread.second < dwPriority )
			dwThreadID = _Thread.first, dwPriority = _Thread.second;

	if ( !pThreadEnvironment )
		if ( !AllocateMemory( pThreadEnvironment, THREAD_ENVIRONMENT_SIZE, PAGE_EXECUTE_READWRITE )
			 || !Write( pThreadEnvironment, ThreadEnvironment, THREAD_ENVIRONMENT_SIZE ) )
			return false;

	_Worker = worker_t( dwThreadID, dwHandleAccess );
	return _Worker.Valid( ) && _Worker.Suspend( ) && _Worker.Push( pExit ) && _Worker.SimulateFunctionCall( pThreadEnvironment ) && _Worker.Resume( );
}

bool CMemoryManager::Read( void* pAddress, void* pOut, std::size_t zSize )
{
	if ( hProcess == nullptr
		 || hProcess == INVALID_HANDLE_VALUE )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Handle for process is invalid, unable to read memory." ) ), false;

	if ( pAddress == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid address passed to Read( )." ) ), false;

	if ( pOut == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid output address passed to Read( )." ) ), false;

	if ( zSize == 0 )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid size passed to Read( )." ) ), false;

	std::size_t zBytesRead;
	if ( ReadProcessMemory( hProcess, pAddress, pOut, zSize, PSIZE_T( &zBytesRead ) ) == FALSE )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to read memory." ) ), false;

	return zBytesRead != zSize ? _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Number of bytes read was not equal to the size passed." ) ), false : true;
}

bool CMemoryManager::Write( void* pAddress, void* pValue, std::size_t zSize )
{
	if ( hProcess == nullptr
		 || hProcess == INVALID_HANDLE_VALUE )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Handle for process is invalid, unable to write memory." ) ), false;

	if ( pAddress == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid address passed to Write( )." ) ), false;

	if ( pValue == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid input address passed to Write( )." ) ), false;

	if ( zSize == 0 )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid size passed to Write( )." ) ), false;

	std::size_t zBytesWritten;
	if ( WriteProcessMemory( hProcess, pAddress, pValue, zSize, PSIZE_T( &zBytesWritten ) ) == FALSE )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to write memory." ) ), false;

	return zBytesWritten != zSize ? _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Number of bytes written was not equal to the size passed." ) ), false : true;
}

bool CMemoryManager::AllocateMemory( void *&pAddress, std::size_t zSize, DWORD dwAccess )
{
	if ( !( dwCurrentAccess & PROCESS_VM_OPERATION ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Insufficient handle privileges to allocate memory." ) ), false;

	if ( ( pAddress = VirtualAllocEx( hProcess, nullptr, zSize, MEM_COMMIT | MEM_RESERVE, dwAccess ) ) == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Allocating memory failed." ) ), false;

	return true;
}

bool CMemoryManager::WipeMemory( void *pAddress, std::size_t zSize )
{
	const auto pMemory = new unsigned char[ zSize ];
	memset( pMemory, 0, zSize );
	const auto bReturn = Write( pAddress, pMemory, zSize );
	delete[ ] pMemory;
	return bReturn;
}

bool CMemoryManager::FreeMemory( void *pAddress )
{
	if ( !( dwCurrentAccess & PROCESS_VM_OPERATION ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Insufficient handle privileges to free memory." ) ), false;

	return VirtualFreeEx( hProcess, pAddress, 0, MEM_RELEASE ) == FALSE ? _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Unable to release memory." ) ), false : true;
}

bool CMemoryManager::LoadLibraryEx( const std::string &strPath, bool bUseExistingThread, HMODULE *pModuleHandle /*= nullptr*/ )
{
	worker_t _Worker;
	void *pExit = nullptr;

	if ( LOAD_LIBRARY_EX_WRAPPER_SIZE_ != LOAD_LIBRARY_EX_WRAPPER_SIZE )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "LOAD_LIBRARY_EX_WRAPPER_SIZE needs to be updated." ) ), false;

	if ( !pLoadLibraryExWrapper )
		if ( !AllocateMemory( pLoadLibraryExWrapper, sizeof ( load_library_ex_wrapper ), PAGE_EXECUTE_READWRITE ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for LoadLibraryExWrapper." ) ), false;

	if ( !AllocateMemory( pExit, sizeof( bool ), PAGE_READWRITE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for exiting." ) ), false;

	if( !( bUseExistingThread ? FindWorker( _Worker, THREAD_ALL_ACCESS, pExit ) : CreateWorker( _Worker, pExit ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get worker thread to load library." ) ), false;

	load_library_ex_wrapper _WrapperData;

	_WrapperData.szLibraryPath = reinterpret_cast< const char * >( std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( void * ) * 3 + LOAD_LIBRARY_EX_WRAPPER_SIZE );
	if ( !Write( pLoadLibraryExWrapper, _WrapperData.szLibraryPath )
		 || !Write( reinterpret_cast< void * >( const_cast< char * >( _WrapperData.szLibraryPath ) ),
					reinterpret_cast< void * >( const_cast< char * >( &strPath[ 0 ] ) ), strPath.length( ) * sizeof( char ) ) )
		return false;

	_WrapperData.pLoadLibrary = reinterpret_cast< decltype( _WrapperData.pLoadLibrary ) >( LoadLibraryA );
	if ( !Write( reinterpret_cast< void * >( std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( void * ) ), _WrapperData.pLoadLibrary )
		 || !Write( reinterpret_cast< void * >( std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( void * ) * 2 ), _WrapperData.BUFFER )
		 || !Write( reinterpret_cast< void * >( std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( void * ) * 3 ),
					reinterpret_cast< void * >( _WrapperData.bLoadLibraryExWrapper ), LOAD_LIBRARY_EX_WRAPPER_SIZE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to write load library wrapper data to memory." ) ), false;

	if ( !_Worker.SimulateFunctionCall( reinterpret_cast< void * >( std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( void * ) * 3 ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to call the LoadLibraryExWrapper shellcode." ) ), false;

	auto mmtWaitStart = GetMoment( );
	CONTEXT _ThreadContext;
	do
	{
		if ( !_Worker.GetContext( _ThreadContext ) )
			return false;

		if ( GetMoment( ) - mmtWaitStart >= MAX_LIBRARY_LOAD_TIME )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Waiting for ECX signal timed out while loading library." ) ), false;

		Pause( 50ui64 );
	} while ( _ThreadContext.Ecx != DONE_LOADING_LIBRARY );

	if ( pModuleHandle != nullptr )
		*pModuleHandle = HMODULE( _ThreadContext.Eax );

	auto bSuccess = _ThreadContext.Eax != NULL;
	bSuccess &= Write( pExit, true );

	if ( bUseExistingThread )
	{
		mmtWaitStart = GetMoment( );
		do
		{
			if ( !_Worker.GetContext( _ThreadContext ) )
				return false;

			if ( GetMoment( ) - mmtWaitStart >= MAX_LIBRARY_LOAD_TIME )
				return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Waiting for thread execution to resume timed out." ) ), false;

			Pause( 50ui64 );
		} while ( _ThreadContext.Eip >= std::uintptr_t( pThreadEnvironment )
				  && _ThreadContext.Eip <= std::uintptr_t( pThreadEnvironment ) + THREAD_ENVIRONMENT_SIZE
				  || _ThreadContext.Eip >= std::uintptr_t( pLoadLibraryExWrapper )
				  && _ThreadContext.Eip <= std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( load_library_ex_wrapper ) );
	}
	else
		_Worker.WaitForExecutionFinish( INFINITE );

	return FreeMemory( pExit ) && bSuccess;
}
