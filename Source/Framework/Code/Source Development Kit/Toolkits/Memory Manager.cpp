/// Memory Manager.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

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
	if ( !( dwCurrentAccess & THREAD_GET_CONTEXT ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to get context of thread with insufficient handle privileges." ) );

	return GetThreadContext( hThread, &_Out ) == FALSE ?
		_Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get context of thread." ) ), false : true;
}

bool worker_t::SetContext( CONTEXT &_New )
{
	if ( !( dwCurrentAccess & THREAD_GET_CONTEXT ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to set context of thread with insufficient handle privileges." ) );

	return SetThreadContext( hThread, &_New ) == FALSE ?
		_Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to set context of thread." ) ), false : true;
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

	return SuspendThread( hThread ) == DWORD( -1 ) ? 
		_Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to suspend thread." ) ), false : bSuspended = true, true;
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

bool worker_t::WaitForExecutionFinish( DWORD dwTime )
{
	return WaitForSingleObject( hThread, dwTime ) == WAIT_OBJECT_0 ? true : _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Waiting for thread signal state failed." ) ), false;
}

bool CMemoryManager::SetProcess( const std::string &strExecutable, DWORD dwAccess )
{
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
		if ( !AllocateMemory( pThreadEnvironment, THREAD_ENVIRONMENT_SIZE, PAGE_EXECUTE_READWRITE ) )
			 return false;

	DWORD dwThreadID;
	_Worker = worker_t( CreateRemoteThread( hProcess, nullptr, NULL, LPTHREAD_START_ROUTINE( pThreadEnvironment ), pExit, NULL, &dwThreadID ), THREAD_ALL_ACCESS );
	return _Worker.Valid( ) ? true : _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to create a worker." ) ), false;
}

bool CMemoryManager::FindWorker( worker_t &_Worker, DWORD dwHandleAccess, void *&pExit )
{
	std::vector< DWORD > vecThreads { };
	if ( !SI.GetProcessThreads( dwProcessID, vecThreads ) )
		return false;

	_Worker = worker_t( vecThreads[ 0 ], dwHandleAccess );
	if ( !_Worker.Valid( )
		 || !_Worker.Suspend( ) )
		return false;

	CONTEXT _ThreadContext;
	if ( !_Worker.GetContext( _ThreadContext ) )
		return false;

	_ThreadContext.Esp -= sizeof( bool * );
	if ( !Write< void * >( reinterpret_cast< void* >( _ThreadContext.Esp ), pExit ) )
		return false;

	_ThreadContext.Esp -= sizeof( void * );
	if ( !Write< DWORD >( reinterpret_cast< void* >( _ThreadContext.Esp ), _ThreadContext.Eip ) )
		return false;

	_ThreadContext.Esp = DWORD( pThreadEnvironment );
	return _Worker.SetContext( _ThreadContext ) && _Worker.Resume( );
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

bool CMemoryManager::LoadLibraryEx( const std::string &strPath, bool bUseExistingThread )
{
	worker_t _Worker;
	void *pExit = nullptr;

	if ( !pLoadLibraryExWrapper )
		if ( !AllocateMemory( pLoadLibraryExWrapper, LOAD_LIBRARY_EX_WRAPPER_SIZE, PAGE_EXECUTE_READWRITE ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for LoadLibraryExWrapper." ) ), false;

	if ( !AllocateMemory( pExit, sizeof( bool ), PAGE_READWRITE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for exiting." ) ), false;

	if( !( bUseExistingThread ? FindWorker( _Worker, THREAD_ALL_ACCESS, pExit ) : CreateWorker( _Worker, pExit ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get worker thread to load library." ) ), false;

	return false;
}
