/// Memory Manager.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

load_library_ex_wrapper_t::load_library_ex_wrapper_t( )
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

	return ResumeThread( hThread ) == UINT_MAX ?
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

	if ( !bSuspended && !Suspend( )
		 || !GetInstructionPointer( pInstructionPointer )
		 || !Push( pInstructionPointer )
		 || !GetContext( _ThreadContext ) )
		return Resume( ), false;

	_ThreadContext.Eip = DWORD( pFunction );
	return SetContext( _ThreadContext ) && Resume( );
}

bool worker_t::ExecutingFunction( void *pFunction, std::size_t zFunctionSize )
{
	CONTEXT _ThreadContext;
	if ( !GetContext( _ThreadContext ) )
		return false;

	return _ThreadContext.Eip >= std::uintptr_t( pFunction )
		&& _ThreadContext.Eip <= std::uintptr_t( pFunction ) + zFunctionSize;
}

bool worker_t::WaitForExecutionFinish( DWORD dwTime )
{
	return WaitForSingleObject( hThread, dwTime ) == WAIT_OBJECT_0 ? true : _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Waiting for thread signal state failed." ) ), false;
}

image_info_t::image_info_t( void *pData ): pData( pData )
{ }

bool image_info_t::ValidImage( )
{
	return GetOperatingSystemHeader( )->e_magic == IMAGE_DOS_SIGNATURE
		&& GetNewTechnologyHeaders( )->Signature == IMAGE_NT_SIGNATURE
		&& ( GetNewTechnologyHeaders( )->FileHeader.Characteristics & IMAGE_FILE_DLL ) != NULL;
}

std::size_t image_info_t::GetImageSize( )
{
	return GetNewTechnologyHeaders( )->OptionalHeader.SizeOfImage;
}

std::size_t image_info_t::GetHeaderSize( )
{
	return GetNewTechnologyHeaders( )->OptionalHeader.SizeOfHeaders;
}

std::size_t image_info_t::GetSectionCount( )
{
	return GetNewTechnologyHeaders( )->FileHeader.NumberOfSections;
}

IMAGE_DOS_HEADER *image_info_t::GetOperatingSystemHeader( )
{
	return reinterpret_cast< IMAGE_DOS_HEADER * >( pData );
}

IMAGE_NT_HEADERS *image_info_t::GetNewTechnologyHeaders( void *pImageBase /*= nullptr*/ )
{
	return reinterpret_cast< IMAGE_NT_HEADERS * >( ( pImageBase == nullptr ? std::uintptr_t( pData ) : std::uintptr_t( pImageBase ) ) + GetOperatingSystemHeader( )->e_lfanew );
}

IMAGE_SECTION_HEADER *image_info_t::GetSectionHeader( std::size_t zSection )
{
	if ( zSection >= GetSectionCount( ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Invalid section header index." ) ), zSection = GetSectionCount( ) - 1;

	return &reinterpret_cast< IMAGE_SECTION_HEADER * >( std::uintptr_t( GetNewTechnologyHeaders( ) ) + sizeof( IMAGE_NT_HEADERS ) )[ zSection ];
}

IMAGE_IMPORT_DESCRIPTOR *image_info_t::GetImportDescriptor( void *pImageBase /*= nullptr*/ )
{
	return reinterpret_cast< IMAGE_IMPORT_DESCRIPTOR * >( ( pImageBase == nullptr ? std::uintptr_t( pData ) : std::uintptr_t( pImageBase ) ) +
														GetNewTechnologyHeaders( pImageBase )->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].VirtualAddress );
}

CMemoryManager::pattern_t CMemoryManager::ParsePattern( const std::string &strPattern )
{
	auto strModifiable = strPattern;
	pattern_t _Return;

	do
	{
		auto &_Byte = _Return.emplace_back( );
		while ( strModifiable.front( ) == ' ' )
			strModifiable.erase( strModifiable.begin( ) );

		if ( strModifiable.front( ) == '?' )
			_Byte = UNKNOWN_BYTE;
		else
			_Byte = strtoul( strModifiable.substr( 0, 2 ).c_str( ), nullptr, 16 );

		while ( !strModifiable.empty( )
				&& strModifiable.front( ) != ' ' )
			strModifiable.erase( strModifiable.begin( ) );
	} while ( !strModifiable.empty( ) );

	return _Return;
}

bool CMemoryManager::Initialize( )
{
	const auto hNewTechnologyModule = GetModuleHandle( ENC( "ntdll.dll" ) );
	if ( hNewTechnologyModule == nullptr )
		return false;

	const auto _Version = SI.GetOperatingSystemVersion( );
	auto bCouldRetry = false;
	std::string strPattern { };

	if ( _Version == ESystemVersion::W10_PREVIEW
		 || _Version == ESystemVersion::W10_REDSTONE_CREATORS_OCTOBER_1809
		 || _Version == ESystemVersion::W10_REDSTONE_CREATORS_APRIL_1803
		 || _Version == ESystemVersion::W10_REDSTONE_CREATORS_FALL_1709 )
		strPattern = ENC( "53 56 57 8D 45 F8 8B FA" );
	else if ( _Version == ESystemVersion::W10_REDSTONE_CREATORS_1703 )
		strPattern = ENC( "8D 45 F0 89 55 F8 50 8D 55 F4" );
	else
		bCouldRetry = true, strPattern = ENC( "53 56 57 8B DA 8B F9 50" );

	if ( ( pInsertInvertedFunctionTable = FindPattern( hNewTechnologyModule, strPattern ) ) == nullptr
		 && bCouldRetry 
		 && ( pInsertInvertedFunctionTable = FindPattern( hNewTechnologyModule, ENC( "8D 45 F4 89 55 F8 50 8D 55 FC" ) ) ) == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Failed to find RtlInsertInvertedFunctionTable." ) ), false;

	return true;
}

void CMemoryManager::Uninitialize( )
{ }

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
	if ( !_Worker.Valid( ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to create a worker." ) ), false;

	while ( !_Worker.ExecutingFunction( pThreadEnvironment, THREAD_ENVIRONMENT_SIZE ) )
		Pause( 10ui64 );

	return true;
}

bool CMemoryManager::FindWorker( worker_t &_Worker, DWORD dwHandleAccess, void *&pExit )
{
	CSystemInformation::thread_list_t _Threads { };
	if ( !SI.GetProcessThreads( dwProcessID, _Threads ) )
		return false;

	auto dwThreadID = _Threads.front( ).first, dwPriority = _Threads.front( ).second;
	for ( auto &_Thread : _Threads )
		if ( _Thread.second > dwPriority )
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
		if ( !AllocateMemory( pLoadLibraryExWrapper, sizeof ( load_library_ex_wrapper_t ), PAGE_EXECUTE_READWRITE ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for LoadLibraryExWrapper." ) ), false;

	if ( !AllocateMemory( pExit, sizeof( bool ), PAGE_READWRITE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for exiting." ) ), false;

	if( !( bUseExistingThread ? FindWorker( _Worker, THREAD_ALL_ACCESS, pExit ) : CreateWorker( _Worker, pExit ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get worker thread to load library." ) ), FreeMemory( pExit ), false;

	load_library_ex_wrapper_t _WrapperData;

	_WrapperData.szLibraryPath = reinterpret_cast< const char * >( std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( void * ) * 3 + LOAD_LIBRARY_EX_WRAPPER_SIZE );
	if ( !Write( pLoadLibraryExWrapper, _WrapperData.szLibraryPath )
		 || !Write( reinterpret_cast< void * >( const_cast< char * >( _WrapperData.szLibraryPath ) ),
					reinterpret_cast< void * >( const_cast< char * >( &strPath[ 0 ] ) ), strPath.length( ) * sizeof( char ) ) )
		return FreeMemory( pExit ), false;

	_WrapperData.pLoadLibrary = reinterpret_cast< decltype( _WrapperData.pLoadLibrary ) >( LoadLibraryA );
	if ( !Write( reinterpret_cast< void * >( std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( void * ) ), _WrapperData.pLoadLibrary )
		 || !Write( reinterpret_cast< void * >( std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( void * ) * 2 ), _WrapperData.BUFFER )
		 || !Write( reinterpret_cast< void * >( std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( void * ) * 3 ),
					reinterpret_cast< void * >( _WrapperData.bLoadLibraryExWrapper ), LOAD_LIBRARY_EX_WRAPPER_SIZE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to write load library wrapper data to memory." ) ), FreeMemory( pExit ), false;

	if ( !_Worker.SimulateFunctionCall( reinterpret_cast< void * >( std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( void * ) * 3 ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to call the LoadLibraryExWrapper shellcode." ) ), FreeMemory( pExit ), false;

	auto mmtWaitStart = GetMoment( );
	CONTEXT _ThreadContext;
	do
	{
		if ( !_Worker.GetContext( _ThreadContext ) )
			return FreeMemory( pExit ), false;

		if ( GetMoment( ) - mmtWaitStart >= MAX_LIBRARY_LOAD_TIME )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Waiting for ECX signal timed out while loading library." ) ), FreeMemory( pExit ), false;

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
				return FreeMemory( pExit ), false;

			if ( GetMoment( ) - mmtWaitStart >= MAX_LIBRARY_LOAD_TIME )
				return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Waiting for thread execution to resume timed out." ) ), FreeMemory( pExit ), false;

			Pause( 50ui64 );
		} while ( _ThreadContext.Eip >= std::uintptr_t( pThreadEnvironment )
				  && _ThreadContext.Eip <= std::uintptr_t( pThreadEnvironment ) + THREAD_ENVIRONMENT_SIZE
				  || _ThreadContext.Eip >= std::uintptr_t( pLoadLibraryExWrapper )
				  && _ThreadContext.Eip <= std::uintptr_t( pLoadLibraryExWrapper ) + sizeof( load_library_ex_wrapper_t ) );

		bSuccess &= _Worker.Close( );
	}
	else
		_Worker.WaitForExecutionFinish( INFINITE );

	return FreeMemory( pExit ) && bSuccess;
}

bool CMemoryManager::ManuallyLoadLibrary( const std::string &strData, HMODULE *pModuleHandle /*= nullptr*/ )
{
	image_info_t _Image( reinterpret_cast< void * >( const_cast< char * >( &strData[ 0 ] ) ) );
	const auto zImage = _Image.GetImageSize( );
	DWORD dwBuffer;
	unsigned char *pImage = nullptr;

	if ( !_Image.ValidImage( ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid image passed to ManuallyLoadLibrary." ) ), delete[ ] pImage, false;

	pImage = new unsigned char[ zImage ];
	VirtualProtect( pImage, zImage, PAGE_EXECUTE_READWRITE, &dwBuffer );
	memcpy( pImage, _Image.pData, _Image.GetHeaderSize( ) );

	for ( auto i = 0; i < _Image.GetSectionCount( ); i++ )
	{
		auto pSectionHeader = _Image.GetSectionHeader( i );
		memcpy( reinterpret_cast< void * >( std::uintptr_t( pImage ) + pSectionHeader->VirtualAddress ),
				reinterpret_cast< void * >( std::uintptr_t( _Image.pData ) + pSectionHeader->PointerToRawData ), pSectionHeader->SizeOfRawData );
	}

	RelocateImageBase( pImage );
	if ( !LoadDependencies( pImage, GetProcAddress, LoadLibraryA ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to load image dependencies." ) ), delete[ ] pImage, false;

	const auto pEntryPoint = reinterpret_cast< BOOL( WINAPI * )( HMODULE, DWORD, void * ) >( std::uintptr_t( pImage ) + _Image.GetNewTechnologyHeaders( )->OptionalHeader.AddressOfEntryPoint );
	const auto bSuccess = pEntryPoint( HMODULE( pImage ), DLL_PROCESS_ATTACH, nullptr ) == TRUE;

	if ( bSuccess && pModuleHandle != nullptr )
		*pModuleHandle = HMODULE( pImage );

	return bSuccess;
}

void *CMemoryManager::FindPattern( HMODULE hLocation, const std::string &strPattern )
{
	const auto _Pattern = ParsePattern( strPattern );
	auto _Image = image_info_t( hLocation );

	if ( !_Image.ValidImage( ) )
		return nullptr;

	for ( auto u = std::uintptr_t( hLocation ), uSequence = 0u; u < std::uintptr_t( hLocation ) + _Image.GetImageSize( ); u++ )
	{
		if ( _Pattern[ uSequence ] == UNKNOWN_BYTE
			 || _Pattern[ uSequence ] == *reinterpret_cast< unsigned char * >( u ) )
			uSequence++;
		else
			u -= uSequence, uSequence = 0;

		if ( uSequence == _Pattern.size( ) )
			return reinterpret_cast< void * >( u - uSequence );
	}

	return nullptr;
}

bool CMemoryManager::ManuallyLoadLibraryEx( const std::string &strData, bool bUseExistingThread, bool bEraseHeaders, bool bEraseDiscardableSections, HMODULE *pModuleHandle /*= nullptr*/  )
{
	image_info_t _Image( reinterpret_cast< void * >( const_cast< char * >( &strData[ 0 ] ) ) );
	worker_t _Worker;
	void *pExit = nullptr, *pImage = nullptr;

	const auto fnCleanup = [ & ]( ) -> void
	{
		if ( pExit )
			FreeMemory( pExit );

		if ( pImage )
			FreeMemory( pImage );

		pExit = pImage = nullptr;

		if ( _Worker.Valid( ) )
			_Worker.Close( );
	};

	if ( !_Image.ValidImage( ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid image passed to ManuallyLoadLibraryEx." ) ), false;

	if ( !pManualMapFunctions )
		if ( !AllocateMemory( pManualMapFunctions, LOAD_DEPENDENCIES_SIZE + RELOCATE_IMAGE_BASE_SIZE, PAGE_EXECUTE_READWRITE ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to create memory for functions to manually map image." ) ), false;

	if ( !Write( pManualMapFunctions, reinterpret_cast< void * >( RELOCATE_IMAGE_BASE ), RELOCATE_IMAGE_BASE_SIZE )
		 || !Write( reinterpret_cast< void * >( std::uintptr_t( pManualMapFunctions ) + RELOCATE_IMAGE_BASE_SIZE ), reinterpret_cast< void * >( LOAD_DEPENDENCIES ), LOAD_DEPENDENCIES_SIZE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to write functions for manually mapping image into memory." ) ), false;

	if ( !AllocateMemory( pExit, sizeof( bool ), PAGE_READWRITE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for exiting." ) ), false;

	if ( !AllocateMemory( pImage, _Image.GetImageSize( ), PAGE_EXECUTE_READWRITE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for image." ) ), fnCleanup( ), false;

	if ( !Write( pImage, _Image.pData, _Image.GetHeaderSize( ) ) )
		return fnCleanup( ), false;

	for ( auto i = 0; i < _Image.GetSectionCount( ); i++ )
	{
		auto pSectionHeader = _Image.GetSectionHeader( i );
		if ( !Write( reinterpret_cast< void * >( std::uintptr_t( pImage ) + pSectionHeader->VirtualAddress ), 
					 reinterpret_cast< void * >( std::uintptr_t( _Image.pData ) + pSectionHeader->PointerToRawData ), pSectionHeader->SizeOfRawData ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to write section %i into memory." ), i ), fnCleanup( ), false;
	}

	if ( !( bUseExistingThread ? FindWorker( _Worker, THREAD_ALL_ACCESS, pExit ) : CreateWorker( _Worker, pExit ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get worker thread to load library." ) ), fnCleanup( ), false;

	if ( !_Worker.Suspend( )
		 || !_Worker.Push( pImage )
		 || !_Worker.SimulateFunctionCall( pManualMapFunctions ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to call RelocateImageBase." ) ), fnCleanup( ), false;

	while ( !_Worker.ExecutingFunction( pThreadEnvironment, THREAD_ENVIRONMENT_SIZE ) )
		Pause( 50ui64 );

	if ( !_Worker.Suspend( )
		 || !_Worker.Push( LoadLibraryA )
		 || !_Worker.Push( GetProcAddress )
		 || !_Worker.Push( pImage )
		 || !_Worker.SimulateFunctionCall( reinterpret_cast< void * >( std::uintptr_t( pManualMapFunctions ) + RELOCATE_IMAGE_BASE_SIZE ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to call LoadDependencies." ) ), fnCleanup( ), false;

	while ( _Worker.ExecutingFunction( reinterpret_cast< void * >( std::uintptr_t( pManualMapFunctions ) + RELOCATE_IMAGE_BASE_SIZE ), LOAD_DEPENDENCIES_SIZE ) )
		Pause( 50ui64 );

	CONTEXT _ThreadContext;
	if ( !_Worker.GetContext( _ThreadContext )
		 || _ThreadContext.Eax != TRUE )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Failed to load dependencies." ) ), fnCleanup( ), false;

	if ( !_Worker.Suspend( )
		 || !_Worker.Push( nullptr )
		 || !_Worker.Push( DLL_PROCESS_ATTACH )
		 || !_Worker.Push( pImage )
		 || !_Worker.SimulateFunctionCall( reinterpret_cast< void * >( std::uintptr_t( pImage ) + _Image.GetNewTechnologyHeaders( )->OptionalHeader.AddressOfEntryPoint ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to call entry point." ) ), fnCleanup( ), false;

	while ( !_Worker.ExecutingFunction( pThreadEnvironment, THREAD_ENVIRONMENT_SIZE ) )
		Pause( 50ui64 );

	if ( !_Worker.GetContext( _ThreadContext ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Failed to get thread context to see if image loaded successfully." ) ), fnCleanup( ), false;

	const auto bReturn = _ThreadContext.Eax == TRUE;
	if ( !Write( pExit, true ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to signal thread to exit." ) ), fnCleanup( ), false;

	while ( _Worker.ExecutingFunction( pThreadEnvironment, THREAD_ENVIRONMENT_SIZE ) )
		Pause( 50ui64 );

	if ( !bReturn )
		_Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "DLLMain didn't return true." ) );

	if ( bEraseHeaders && !WipeMemory( pImage, _Image.GetHeaderSize( ) ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Failed to erase headers." ) );

	if ( bEraseDiscardableSections )
		for ( auto i = 0; i < _Image.GetSectionCount( ); i++ )
		{
			auto pSectionHeader = _Image.GetSectionHeader( i );
			if ( ( pSectionHeader->Characteristics & IMAGE_SCN_MEM_DISCARDABLE ) != NULL )
				if ( !WipeMemory( reinterpret_cast< void * >( std::uintptr_t( pImage ) + pSectionHeader->VirtualAddress ), pSectionHeader->SizeOfRawData ) )
					_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Failed to wipe section %i." ), i );
		}

	fnCleanup( );
	return bReturn;
}
