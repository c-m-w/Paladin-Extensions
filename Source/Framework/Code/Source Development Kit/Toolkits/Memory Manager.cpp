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
	_Out.ContextFlags = CONTEXT_FULL;
	if ( !( dwCurrentAccess & THREAD_GET_CONTEXT ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to get context of thread with insufficient handle privileges." ) );

	return GetThreadContext( hThread, &_Out ) == FALSE ?
			   ( _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get context of thread." ) ), false ) :
			   true;
}

bool worker_t::SetContext( CONTEXT &_New )
{
	_New.ContextFlags = CONTEXT_FULL;
	if ( !( dwCurrentAccess & THREAD_GET_CONTEXT ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to set context of thread with insufficient handle privileges." ) );

	return SetThreadContext( hThread, &_New ) == FALSE ?
			   ( _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to set context of thread." ) ), false ) :
			   true;
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
			   _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Failed to close thread handle %08X." ), hThread ), false :
			   hThread = nullptr, true;
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
			   _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to resume thread." ) ), false :
			   bSuspended = false, true;
}

bool worker_t::Terminate( DWORD dwExitCode /*= EXIT_SUCCESS*/ )
{
	if ( !( dwCurrentAccess & THREAD_TERMINATE ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to terminate a thread without sufficient handle privileges." ) );

	return TerminateThread( hThread, dwExitCode ) == FALSE ? _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to terminate thread." ) ), false : Close( ), true;
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
			&& _ThreadContext.Eip < std::uintptr_t( pFunction ) + zFunctionSize;
}

bool worker_t::WaitForExecutionFinish( DWORD dwTime )
{
	return WaitForSingleObject( hThread, dwTime ) == WAIT_OBJECT_0 ? true : _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Waiting for thread signal state failed." ) ), false;
}

image_info_t::image_info_t( void *pData ): pData( pData )
{ }

image_info_t::operator HMODULE( ) const
{
	return HMODULE( pData );
}

image_info_t::operator bool( ) const
{
	return pData != nullptr && ValidImage( );
}

bool image_info_t::ValidImage( ) const
{
	return GetOperatingSystemHeader( )->e_magic == IMAGE_DOS_SIGNATURE
			&& GetNewTechnologyHeaders( )->Signature == IMAGE_NT_SIGNATURE;
}

std::size_t image_info_t::GetImageSize( ) const
{
	return GetNewTechnologyHeaders( )->OptionalHeader.SizeOfImage;
}

std::size_t image_info_t::GetHeaderSize( ) const
{
	return GetNewTechnologyHeaders( )->OptionalHeader.SizeOfHeaders;
}

std::size_t image_info_t::GetSectionCount( ) const
{
	return GetNewTechnologyHeaders( )->FileHeader.NumberOfSections;
}

IMAGE_DOS_HEADER *image_info_t::GetOperatingSystemHeader( ) const
{
	return const_cast< IMAGE_DOS_HEADER * >( reinterpret_cast< const IMAGE_DOS_HEADER * >( pData ) );
}

IMAGE_NT_HEADERS *image_info_t::GetNewTechnologyHeaders( ) const
{
	return reinterpret_cast< IMAGE_NT_HEADERS * >( std::uintptr_t( pData ) + GetOperatingSystemHeader( )->e_lfanew );
}

IMAGE_SECTION_HEADER *image_info_t::GetSectionHeader( std::size_t zSection ) const
{
	if ( zSection >= GetSectionCount( ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Invalid section header index." ) ), zSection = GetSectionCount( ) - 1;

	return &reinterpret_cast< IMAGE_SECTION_HEADER * >( std::uintptr_t( GetNewTechnologyHeaders( ) ) + sizeof( IMAGE_NT_HEADERS ) )[ zSection ];
}

IMAGE_IMPORT_DESCRIPTOR *image_info_t::GetFirstImport( ) const
{
	return reinterpret_cast< IMAGE_IMPORT_DESCRIPTOR * >( std::uintptr_t( pData ) + GetNewTechnologyHeaders( )->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].VirtualAddress );
}

IMAGE_IMPORT_DESCRIPTOR *image_info_t::GetNextImport( IMAGE_IMPORT_DESCRIPTOR *pCurrent ) const
{
	const auto pReturn = reinterpret_cast< IMAGE_IMPORT_DESCRIPTOR * >( std::uintptr_t( pCurrent ) + sizeof( IMAGE_IMPORT_DESCRIPTOR ) );
	return pReturn->Characteristics == NULL ? nullptr : pReturn;
}

IMAGE_IMPORT_DESCRIPTOR *image_info_t::GetImportDescriptor( HMODULE hExporter ) const
{
	for ( auto p = GetFirstImport( ); p != nullptr; p = GetNextImport( p ) )
		if ( GetModuleHandle( reinterpret_cast< const char * >( std::uintptr_t( pData ) + p->Name ) ) == hExporter )
			return p;

	return nullptr;
}

IMAGE_EXPORT_DIRECTORY *image_info_t::GetExports( ) const
{
	return reinterpret_cast< IMAGE_EXPORT_DIRECTORY * >( std::uintptr_t( pData ) + GetNewTechnologyHeaders( )->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress );
}

bool image_info_t::GetImportName( IMAGE_THUNK_DATA *pImportData, std::string &strOut ) const
{
	const auto szImport = reinterpret_cast< const char * >( ( pImportData->u1.Ordinal & IMAGE_ORDINAL_FLAG ) > 0 ? reinterpret_cast< void * >( pImportData->u1.Ordinal & 0xFFFF ) : reinterpret_cast< IMAGE_IMPORT_BY_NAME * >( std::uintptr_t( pData ) + pImportData->u1.AddressOfData )->Name );
	if ( std::uintptr_t( szImport ) >= std::uintptr_t( pData )
		&& std::uintptr_t( szImport ) <= std::uintptr_t( pData ) + GetImageSize( ) )
		return strOut = szImport, true;

	return false;
}

IMAGE_THUNK_DATA *image_info_t::FindImport( HMODULE hExporter, void *pImport ) const
{
	const auto pDescriptor = GetImportDescriptor( hExporter );
	if ( pDescriptor == nullptr )
		return nullptr;

	for ( auto p = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( pData ) + pDescriptor->FirstThunk );
		  p != nullptr && p->u1.AddressOfData != NULL;
		  p = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( p ) + sizeof( IMAGE_THUNK_DATA ) ) )
		if ( p->u1.Function == std::uintptr_t( pImport ) )
			return p;

	return nullptr;
}

IMAGE_THUNK_DATA *image_info_t::FindImport( HMODULE hExporter, const std::string &strImport ) const
{
	const auto pDescriptor = GetImportDescriptor( hExporter );
	if ( pDescriptor == nullptr )
		return nullptr;

	for ( auto p = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( pData ) + pDescriptor->FirstThunk ),
			   _p = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( pData ) + pDescriptor->OriginalFirstThunk );
		  p != nullptr && p->u1.AddressOfData != NULL && _p != nullptr && _p->u1.AddressOfData != NULL;
		  p = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( p ) + sizeof( IMAGE_THUNK_DATA ) ),
		  _p = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( _p ) + sizeof( IMAGE_THUNK_DATA ) ) )
	{
		std::string strCurrentImport;
		if ( !GetImportName( _p, strCurrentImport ) )
			continue;

		if ( strCurrentImport == strImport )
			return p;
	}

	return nullptr;
}

std::string image_info_t::GenerateUniqueHash( ) const
{
	const auto zSections = GetSectionCount( );
	const auto pNewTechnologyHeaders = GetNewTechnologyHeaders( );
	nlohmann::json _Information { };

	_Information[ ENC( "Header Size" ) ] = GetHeaderSize( );
	_Information[ ENC( "Section Count" ) ] = zSections;
	_Information[ ENC( "Symbol Count" ) ] = pNewTechnologyHeaders->FileHeader.NumberOfSymbols;
	_Information[ ENC( "PE Offset" ) ] = GetOperatingSystemHeader( )->e_lfanew;
	_Information[ ENC( "Magic" ) ] = pNewTechnologyHeaders->OptionalHeader.Magic;
	_Information[ ENC( "Major Linker Version" ) ] = pNewTechnologyHeaders->OptionalHeader.MajorLinkerVersion;
	_Information[ ENC( "Minor Linker Version" ) ] = pNewTechnologyHeaders->OptionalHeader.MinorLinkerVersion;
	_Information[ ENC( "Entry Point RVA" ) ] = pNewTechnologyHeaders->OptionalHeader.AddressOfEntryPoint;
	_Information[ ENC( "Code RVA" ) ] = pNewTechnologyHeaders->OptionalHeader.BaseOfCode;
	_Information[ ENC( "Data RVA" ) ] = pNewTechnologyHeaders->OptionalHeader.BaseOfData;
	_Information[ ENC( "Major OS Version" ) ] = pNewTechnologyHeaders->OptionalHeader.MajorOperatingSystemVersion;
	_Information[ ENC( "Minor OS Version" ) ] = pNewTechnologyHeaders->OptionalHeader.MinorOperatingSystemVersion;
	_Information[ ENC( "Subsystem" ) ] = pNewTechnologyHeaders->OptionalHeader.Subsystem;

	for ( auto z = 0u; z < zSections; z++ )
	{
		const auto pSectionHeader = GetSectionHeader( z );
		const auto strName = std::string( reinterpret_cast< const char * >( pSectionHeader->Name ) ).substr( 0, IMAGE_SIZEOF_SHORT_NAME );

		_Information[ strName ][ ENC( "RVA" ) ] = pSectionHeader->VirtualAddress;
		_Information[ strName ][ ENC( "Characteristics" ) ] = pSectionHeader->Characteristics;
	}

	for ( auto p = GetFirstImport( ); p != nullptr; p = GetNextImport( p ) )
	{
		const auto strModule = std::string( reinterpret_cast< const char * >( std::uintptr_t( pData ) + p->Name ) );

		auto i = 0;
		for ( auto q = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( pData ) + p->OriginalFirstThunk );
			  q != nullptr && q->u1.AddressOfData != NULL;
			  q = reinterpret_cast< IMAGE_THUNK_DATA * >( std::uintptr_t( q ) + sizeof( IMAGE_THUNK_DATA ) ), i++ )
		{
			std::string strImport;
			if ( !GetImportName( q, strImport ) )
				continue;

			_Information[ ENC( "Imports" ) ][ strModule ][ i ] = strImport;
		}
	}

	return CRYPTO.GenerateHash( _Information.dump( ) );
}

std::vector< __int16 > CMemoryManager::pattern_t::ParsePattern( const std::string &strPattern )
{
	const auto pLast = &strPattern.back( ) + 1;
	auto pEnd = const_cast< char * >( &strPattern.front( ) );
	std::vector< __int16 > vecReturn { };

	do
	{
		auto &_Byte = vecReturn.emplace_back( );

		if ( *pEnd == ' ' )
			pEnd++;

		if ( *pEnd == '?' )
			_Byte = UNKNOWN_BYTE, pEnd++;
		else
			_Byte = strtoul( pEnd, &pEnd, 16 );
	}
	while ( pEnd != pLast );

	return vecReturn;
}

CMemoryManager::pattern_t::pattern_t( const nlohmann::json &_Data, void **pOutput, std::function< void( ) > fnOnFound /*= nullptr*/ ):
	pOutput( pOutput ), fnOnFound( fnOnFound )
{
	try
	{
		vecPattern = ParsePattern( _Data[ ENC( "Pattern" ) ].get< std::string >( ) );
		ptrOffset = _Data[ ENC( "Offset" ) ].get< std::ptrdiff_t >( );
	}
	catch ( nlohmann::json::type_error &e )
	{
		LOG( ERROR, MEMORY_MANAGER, "Unable to parse pattern data. Message: %s.", e.what( ) );
	}
}

bool CMemoryManager::pattern_t::Valid( ) const
{
	return !vecPattern.empty( ) && pOutput != nullptr;
}

bool CMemoryManager::Initialize( )
{
	return true;
}

void CMemoryManager::Uninitialize( )
{
#if !defined _DEBUG

	if ( bThreadEnvironment != nullptr )
		delete[ ] bThreadEnvironment;

	if ( bLoadLibraryExWrapper != nullptr )
		delete[ ] bLoadLibraryExWrapper;

	if ( bRelocateImageBase != nullptr )
		delete[ ] bRelocateImageBase;

	if ( bLoadDependencies != nullptr )
		delete[ ] bLoadDependencies;

#endif
}

bool CMemoryManager::EnsureDataValidity( )
{
	if ( pInsertInvertedFunctionTable != nullptr
		&& pInvertedFunctionTable != nullptr )
		return true;

	if ( strNewestInsertInvertedFunctionTable.empty( )
		|| ptrNewestInsertInvertedFunctionTable == 0
		|| strNewestInvertedFunctionTable.empty( )
		|| ptrNewestInvertedFunctionTable == 0
		|| strBackupInsertInvertedFunctionTable.empty( )
		|| ptrBackupInsertInvertedFunctionTable == 0
		|| ptrBackupInvertedFunctionTable == 0
		|| strResortInsertInvertedFunctionTable.empty( )
		|| ptrResortInsertInvertedFunctionTable == 0
		|| ptrResortWindows10InvertedFunctionTable == 0
		|| ptrResortPreviousWindowsInvertedFunctionTable == 0 )
		if ( !AUTH.RequestData( &strNewestInsertInvertedFunctionTable, &ptrNewestInsertInvertedFunctionTable, &strNewestInvertedFunctionTable, &ptrNewestInvertedFunctionTable,
								&strBackupInsertInvertedFunctionTable, &ptrBackupInsertInvertedFunctionTable, &ptrBackupInvertedFunctionTable, &strResortInsertInvertedFunctionTable,
								&ptrResortInsertInvertedFunctionTable, &ptrResortWindows10InvertedFunctionTable, &ptrResortPreviousWindowsInvertedFunctionTable ) )
			return false;

	const auto hNewTechnologyModule = GetModuleHandle( ENC( "ntdll.dll" ) );
	if ( hNewTechnologyModule == nullptr )
		return false;

	const auto _Version = SI.GetOperatingSystemVersion( );
	auto bInitializedData = false;

	if ( _Version == ESystemVersion::W10_PREVIEW
		|| _Version == ESystemVersion::W10_REDSTONE_CREATORS_OCTOBER_1809
		|| _Version == ESystemVersion::W10_REDSTONE_CREATORS_APRIL_1803
		|| _Version == ESystemVersion::W10_REDSTONE_CREATORS_FALL_1709 )
		bInitializedData = AddPattern( hNewTechnologyModule, pattern_t( strNewestInsertInvertedFunctionTable, &pInsertInvertedFunctionTable, ptrNewestInsertInvertedFunctionTable ) )
				&& AddPattern( hNewTechnologyModule, pattern_t( strNewestInvertedFunctionTable, &pInvertedFunctionTable, ptrNewestInvertedFunctionTable, [ ]( )
				{
					pInvertedFunctionTable = *reinterpret_cast< void ** >( pInvertedFunctionTable );
				} ) )
				&& FindPatterns( );
	else if ( _Version == ESystemVersion::W10_REDSTONE_CREATORS_1703 )
		bInitializedData = AddPattern( hNewTechnologyModule, pattern_t( strBackupInsertInvertedFunctionTable, &pInsertInvertedFunctionTable, ptrBackupInsertInvertedFunctionTable, [ ]( )
				{
					pInvertedFunctionTable = *reinterpret_cast< void ** >( std::uintptr_t( pInsertInvertedFunctionTable ) + ptrBackupInvertedFunctionTable );
				} ) )
				&& FindPatterns( );
	else
		bInitializedData = AddPattern( hNewTechnologyModule, pattern_t( strResortInsertInvertedFunctionTable, &pInsertInvertedFunctionTable, ptrResortInsertInvertedFunctionTable, [ _Version ]( )
				{
					pInvertedFunctionTable = *reinterpret_cast< void ** >( std::uintptr_t( pInsertInvertedFunctionTable ) +
						( _Version == ESystemVersion::W10_INITIAL_1507
						  || _Version == ESystemVersion::W10_REDSTONE_NOVEMBER_1511
						  || _Version == ESystemVersion::W10_REDSTONE_ANNIVERSARY_1607 ?
							  ptrResortWindows10InvertedFunctionTable :
							  ptrResortPreviousWindowsInvertedFunctionTable ) );
				} ) )
				&& FindPatterns( );

	if ( !bInitializedData )
		_Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to find patterns required." ) );

	// clear all this garbage from memory
	strNewestInsertInvertedFunctionTable.clear( );
	ptrNewestInsertInvertedFunctionTable = 0;
	strNewestInvertedFunctionTable.clear( );
	ptrNewestInvertedFunctionTable = 0;
	strBackupInsertInvertedFunctionTable.clear( );
	ptrBackupInsertInvertedFunctionTable = 0;
	ptrBackupInvertedFunctionTable = 0;
	strResortInsertInvertedFunctionTable.clear( );
	ptrResortInsertInvertedFunctionTable = 0;
	ptrResortWindows10InvertedFunctionTable = 0;
	ptrResortPreviousWindowsInvertedFunctionTable = 0;

	return bInitializedData;
}

bool CMemoryManager::EnsureShellcodeValidity( )
{
	if ( bThreadEnvironment == nullptr
		|| bLoadLibraryExWrapper == nullptr
		|| bRelocateImageBase == nullptr
		|| bLoadDependencies == nullptr )
		if ( !AUTH.RequestShellcode( reinterpret_cast< unsigned char ** >( &bThreadEnvironment ), reinterpret_cast< unsigned char ** >( &bLoadLibraryExWrapper ),
									 reinterpret_cast< unsigned char ** >( &bRelocateImageBase ), reinterpret_cast< unsigned char ** >( &bLoadDependencies ),
									 &zThreadEnvironment, &zLoadLibraryExWrapper, &zRelocateImageBase, &zLoadDependencies ) )
			return false;

	return true;
}

bool CMemoryManager::EnsureShellcodePresence( )
{
	if ( pShellcode == nullptr )
		if ( !AllocateMemory( pShellcode, zThreadEnvironment + zLoadLibraryExWrapper + zRelocateImageBase + zLoadDependencies, PAGE_EXECUTE_READWRITE )
			|| !Write( pThreadEnvironment, bThreadEnvironment, zThreadEnvironment )
			|| !Write( pLoadLibraryExWrapper, bLoadLibraryExWrapper, zLoadLibraryExWrapper )
			|| !Write( pRelocateImageBase, bRelocateImageBase, zRelocateImageBase )
			|| !Write( pLoadDependencies, bLoadDependencies, zLoadDependencies ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Failed to allocate and write shellcode to memory." ) ), false;

	return true;
}

void *CMemoryManager::GetShellcodeLocation( EShellcode _Shellcode )
{
	if ( pShellcode == nullptr )
		return _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to get shellcode location of %i without initializing it." ), _Shellcode ), nullptr;

	switch ( _Shellcode )
	{
		case THREAD_ENVIRONMENT:
			return pShellcode;

		case LOAD_LIBRARY_EX_WRAPPER:
			return reinterpret_cast< void * >( std::uintptr_t( pShellcode ) + zThreadEnvironment );

		case RELOCATE_IMAGE_BASE:
			return reinterpret_cast< void * >( std::uintptr_t( pShellcode ) + zThreadEnvironment + zLoadLibraryExWrapper );

		case LOAD_DEPENDENCIES:
			return reinterpret_cast< void * >( std::uintptr_t( pShellcode ) + zThreadEnvironment + zLoadLibraryExWrapper + zRelocateImageBase );

		default:
			return nullptr;
	}
}

bool CMemoryManager::SetProcess( DWORD dwNewProcessID, DWORD dwAccess )
{
	if ( !EnsureDataValidity( ) )
		return false;

	if ( dwNewProcessID == NULL )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid process ID passed to SetProcess." ) ), false;

	if ( !bElevated && !( bElevated = SI.ElevateProcess( ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Cannot elevate current process." ) ), false;

	if ( hProcess != nullptr )
		if ( CloseHandle( hProcess ) == FALSE )
			_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Unable to close old process handle." ) );

	if ( pShellcode != nullptr )
		if ( !FreeMemory( pShellcode ) )
			_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Unable to free shellcode memory." ) );

	hProcess = nullptr;
	pShellcode = nullptr;
	dwProcessID = dwNewProcessID;

	if ( dwAccess == NULL )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Access to open executable process is invalid." ) ), false;

	hProcess = OpenProcess( dwAccess, FALSE, dwProcessID );
	if ( hProcess == nullptr
		|| hProcess == INVALID_HANDLE_VALUE )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to open process handle of executable." ) ), false;

	dwCurrentAccess = dwAccess;
	return true;
}

bool CMemoryManager::SetProcess( const std::string &strExecutable, DWORD dwAccess )
{
	DWORD dwNewProcessID;
	if ( !SI.GetProcessID( strExecutable, dwNewProcessID ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get process id of executable %s." ), strExecutable.c_str( ) ), false;

	return SetProcess( dwNewProcessID, dwAccess );
}

bool CMemoryManager::CreateWorker( worker_t &_Worker, void *&pExit )
{
	if ( !EnsureShellcodeValidity( )
		|| !EnsureShellcodePresence( ) )
		return false;

	if ( !( dwCurrentAccess & PROCESS_CREATE_THREAD ) )
		_Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Insufficient privileges to create a thread." ) );

	DWORD dwThreadID;
	_Worker = worker_t( CreateRemoteThread( hProcess, nullptr, NULL, LPTHREAD_START_ROUTINE( pThreadEnvironment ), pExit, NULL, &dwThreadID ), THREAD_ALL_ACCESS );
	if ( !_Worker.Valid( ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to create a worker." ) ), false;

	while ( !_Worker.ExecutingFunction( pThreadEnvironment, zThreadEnvironment ) )
		Pause( 10ui64 );

	return true;
}

bool CMemoryManager::FindWorker( worker_t &_Worker, DWORD dwHandleAccess, void *&pExit )
{
	if ( !EnsureShellcodeValidity( )
		|| !EnsureShellcodePresence( ) )
		return false;

	CSystemInformation::thread_list_t _Threads { };
	if ( !SI.GetProcessThreads( dwProcessID, _Threads ) )
		return false;

	auto dwThreadID = _Threads.front( ).first, dwPriority = _Threads.front( ).second;
	for ( auto &_Thread: _Threads )
		if ( _Thread.second > dwPriority )
			dwThreadID = _Thread.first, dwPriority = _Thread.second;

	_Worker = worker_t( dwThreadID, dwHandleAccess );
	return _Worker.Valid( ) && _Worker.Suspend( ) && _Worker.Push( pExit ) && _Worker.SimulateFunctionCall( pThreadEnvironment ) && _Worker.Resume( );
}

bool CMemoryManager::Read( void *pAddress, void *pOut, std::size_t zSize )
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

bool CMemoryManager::Write( void *pAddress, void *pValue, std::size_t zSize )
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
	if ( !EnsureShellcodeValidity( )
		|| !EnsureShellcodePresence( ) )
		return false;

	worker_t _Worker;
	void *pExit = nullptr;
	void *pLibraryName = nullptr;

	if ( !AllocateMemory( pExit, sizeof( bool ), PAGE_READWRITE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for exiting." ) ), false;

	if ( !AllocateMemory( pLibraryName, strPath.length( ) * sizeof( char ), PAGE_READWRITE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for library name." ) ), FreeMemory( pExit ), false;

	if ( !( bUseExistingThread ? FindWorker( _Worker, THREAD_ALL_ACCESS, pExit ) : CreateWorker( _Worker, pExit ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get worker thread to load library." ) ), FreeMemory( pExit ), FreeMemory( pLibraryName ), false;

	if ( !Write( pLibraryName, const_cast< char * >( &strPath[ 0 ] ), strPath.length( ) ) )
		return FreeMemory( pExit ), false;

	if ( !_Worker.Suspend( )
		|| !_Worker.Push( LoadLibraryA )
		|| !_Worker.Push( pLibraryName )
		|| !_Worker.SimulateFunctionCall( pLoadLibraryExWrapper ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to call the LoadLibraryExWrapper shellcode." ) ), FreeMemory( pExit ), FreeMemory( pLibraryName ), false;

	while ( !_Worker.ExecutingFunction( pThreadEnvironment, zThreadEnvironment ) )
		Pause( 50ui64 );

	CONTEXT _ThreadContext;
	if ( !_Worker.GetContext( _ThreadContext ) )
		return FreeMemory( pExit ), FreeMemory( pLibraryName ), false;

	if ( pModuleHandle != nullptr )
		*pModuleHandle = HMODULE( _ThreadContext.Eax );

	auto bSuccess = _ThreadContext.Eax != NULL;
	bSuccess &= Write( pExit, true );

	if ( bUseExistingThread )
	{
		while ( _Worker.ExecutingFunction( pThreadEnvironment, zThreadEnvironment ) )
			Pause( 50ui64 );

		bSuccess &= _Worker.Close( );
	}
	else
		_Worker.WaitForExecutionFinish( INFINITE );

	return FreeMemory( pExit ) && FreeMemory( pLibraryName ) && bSuccess;
}

bool CMemoryManager::IsExecutableCode( void *pAddress )
{
	if ( pAddress == nullptr )
		return false;

	MEMORY_BASIC_INFORMATION _Memory;
	return VirtualQuery( pAddress, &_Memory, sizeof( MEMORY_BASIC_INFORMATION ) ) > 0
			&& _Memory.RegionSize > 0
			&& ( _Memory.Protect & PAGE_EXECUTE_READ ) > 0
			&& ( _Memory.Protect & ( PAGE_GUARD | PAGE_NOACCESS ) ) == 0;
}

void *CMemoryManager::FindFreeMemory( HMODULE hModule, std::size_t zMinimumSize, DWORD dwAccess, void *pStart /*= nullptr*/ )
{
	auto _Image = image_info_t( hModule );

	if ( !_Image.ValidImage( ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid module passed to FindFreeMemory." ) ), nullptr;

	if ( pStart != nullptr )
		if ( std::uintptr_t( pStart ) > std::uintptr_t( hModule ) + _Image.GetImageSize( ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid start address passed to FindFreeMemory." ) ), nullptr;

	std::size_t zRegionSize = 0, zCurrentSize = 0;
	for ( auto p = reinterpret_cast< unsigned char * >( pStart == nullptr ? std::uintptr_t( hModule ) + _Image.GetHeaderSize( ) : std::uintptr_t( pStart ) );
		  std::uintptr_t( p ) < std::uintptr_t( hModule ) + _Image.GetImageSize( ); p++, zRegionSize-- )
	{
		if ( zRegionSize == 0 )
		{
			MEMORY_BASIC_INFORMATION _Region;

			do
			{
				if ( VirtualQuery( p, &_Region, sizeof( MEMORY_BASIC_INFORMATION ) ) == 0
					|| _Region.RegionSize < zMinimumSize
					|| ( _Region.Protect & dwAccess ) == 0
					|| ( _Region.Protect & ~dwAccess ) != 0 )
					p += _Region.RegionSize, zCurrentSize = 0;
				else
					zRegionSize = _Region.RegionSize;
			}
			while ( zRegionSize == 0 );
		}

		if ( *p == NULL )
			zCurrentSize++;
		else
			zCurrentSize = 0;

		if ( zCurrentSize >= zMinimumSize )
			return p - zMinimumSize + 1;
	}

	return nullptr;
}

HMODULE CMemoryManager::GetOrigin( void *pAddress )
{
	std::vector< HMODULE > vecModules { };

	if ( !SI.GetModules( GetCurrentProcessId( ), vecModules ) )
		return nullptr;

	for ( auto &hModule: vecModules )
	{
		auto _Info = image_info_t( hModule );

		if ( std::uintptr_t( pAddress ) >= std::uintptr_t( hModule )
			&& std::uintptr_t( pAddress ) <= std::uintptr_t( hModule ) + _Info.GetImageSize( ) )
			return hModule;
	}

	return nullptr;
}

std::size_t CMemoryManager::GetPageSize( )
{
	static std::size_t zPage = 0;

	if ( zPage == 0 )
	{
		SYSTEM_INFO _Info;
		GetSystemInfo( &_Info );
		zPage = _Info.dwPageSize;
	}

	return zPage;
}

bool CMemoryManager::AddPattern( const std::string &strModule, const pattern_t &_Pattern )
{
	const auto hModule = GetModuleHandle( strModule.c_str( ) );
	if ( hModule == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get handle of module %s." ), strModule.c_str( ) ), false;

	return AddPattern( hModule, _Pattern );
}

bool CMemoryManager::AddPattern( HMODULE hModule, const pattern_t &_Pattern )
{
	if ( hModule == nullptr
		|| !image_info_t( hModule ).ValidImage( )
		|| !_Pattern.Valid( ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Invalid module passed to AddPattern." ) ), false;

	const auto pInstance = _PatternsToFind.find( hModule );
	if ( pInstance == _PatternsToFind.end( ) )
		return _PatternsToFind.insert( std::pair< HMODULE, std::vector< pattern_t > >( hModule, { } ) ), AddPattern( hModule, _Pattern );

	pInstance->second.emplace_back( _Pattern );
	return true;
}

bool CMemoryManager::FindPatterns( )
{
	for ( auto &_Patterns: _PatternsToFind )
	{
		auto _Module = image_info_t( _Patterns.first );
		std::vector< std::pair< unsigned char *, std::size_t > > vecSectionsToScan { };

		for ( auto i = 0; i < _Module.GetSectionCount( ); i++ )
		{
			const auto _Header = _Module.GetSectionHeader( i );
			if ( ( _Header->Characteristics & ( IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ ) ) > 0
				&& ( _Header->Characteristics & IMAGE_SCN_MEM_WRITE ) == 0 )
				vecSectionsToScan.emplace_back( std::pair< unsigned char*, std::size_t >( reinterpret_cast< unsigned char* >( std::uintptr_t( _Patterns.first ) + _Header->VirtualAddress ),
																						  _Header->SizeOfRawData ) );
		}

		if ( vecSectionsToScan.empty( ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to find sections to pattern scan." ) ), false;

		for ( auto &_Section: vecSectionsToScan )
			for ( auto p = _Section.first, f = decltype( p )( std::uintptr_t( _Section.first ) + _Section.second );
				  p < f && !_Patterns.second.empty( ); p++ )
			{
				for ( auto u = 0u; u < _Patterns.second.size( ); u++ )
				{
					auto &_Current = _Patterns.second[ u ];
					do
					{
						if ( _Current.vecPattern[ _Current.uProgress ] == pattern_t::UNKNOWN_BYTE
							|| _Current.vecPattern[ _Current.uProgress ] == *( p + _Current.iRelative ) )
						{
							if ( ++_Current.uProgress > 1
								&& _Current.ptrFirstByte == 0
								&& *( p + _Current.iRelative ) == _Current.vecPattern.front( ) )
								_Current.ptrFirstByte = decltype( _Current.ptrFirstByte )( p );
							else if ( _Current.ptrFirstByte != 0
								&& _Current.vecPattern[ std::uintptr_t( p ) - _Current.ptrFirstByte ] != *( p + _Current.iRelative ) )
								_Current.ptrFirstByte = 0;
						}
						else
						{
							if ( _Current.ptrFirstByte != 0 )
								_Current.iRelative -= decltype( _Current.ptrFirstByte )( p ) - _Current.ptrFirstByte;

							_Current.uProgress = _Current.ptrFirstByte = 0;
						}

						if ( _Current.uProgress == _Current.vecPattern.size( ) )
						{
							*_Current.pOutput = reinterpret_cast< void * >( p + _Current.iRelative - _Current.uProgress + _Current.ptrOffset + 1 );
							if ( _Current.fnOnFound )
								_Current.fnOnFound( );

							_Patterns.second.erase( _Patterns.second.begin( ) + u );
							u--;
						}

						if ( _Current.iRelative < 0 )
							_Current.iRelative++;
					}
					while ( p == f - 1 && _Current.iRelative < 0 );
				}
			}

		if ( !_Patterns.second.empty( ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to find all patterns." ) ), false;
	}

	return true;
}

bool CMemoryManager::FindPattern( HMODULE hLocation, const std::string &strPattern, std::ptrdiff_t ptrOffset, void *&pOutput )
{
	auto _Pattern = pattern_t::ParsePattern( strPattern );
	auto _Image = image_info_t( hLocation );

	if ( !_Image.ValidImage( ) )
		return false;

	for ( auto u = std::uintptr_t( hLocation ), uSequence = 0u; u < std::uintptr_t( hLocation ) + _Image.GetImageSize( ); u++ )
	{
		if ( uSequence == _Pattern.size( ) )
			return pOutput = reinterpret_cast< void * >( u - uSequence + ptrOffset ), true;

		if ( _Pattern[ uSequence ] == pattern_t::UNKNOWN_BYTE
			|| _Pattern[ uSequence ] == *reinterpret_cast< unsigned char * >( u ) )
			uSequence++;
		else
			u -= uSequence, uSequence = 0;
	}

	return false;
}

bool CMemoryManager::ManuallyLoadLibraryEx( const std::string &strData, bool bUseExistingThread, bool bEnableExceptions, bool bEraseHeaders, bool bEraseDiscardableSections, HMODULE *pModuleHandle /*= nullptr*/ )
{
	if ( !EnsureShellcodeValidity( )
		|| !EnsureShellcodePresence( ) )
		return false;

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

	if ( !AllocateMemory( pExit, sizeof( bool ), PAGE_READWRITE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for exiting." ) ), false;

	if ( !AllocateMemory( pImage, _Image.GetImageSize( ), PAGE_EXECUTE_READWRITE ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to allocate memory for image." ) ), fnCleanup( ), false;

	if ( !Write( pImage, _Image.pData, _Image.GetHeaderSize( ) ) )
		return fnCleanup( ), false;

	for ( auto i = 0; i < _Image.GetSectionCount( ); i++ )
	{
		auto pSectionHeader = _Image.GetSectionHeader( i );
		if ( pSectionHeader->SizeOfRawData != 0
			&& !Write( reinterpret_cast< void * >( std::uintptr_t( pImage ) + pSectionHeader->VirtualAddress ),
					   reinterpret_cast< void * >( std::uintptr_t( _Image.pData ) + pSectionHeader->PointerToRawData ), pSectionHeader->SizeOfRawData ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to write section %i into memory." ), i ), fnCleanup( ), false;
	}

	if ( !( bUseExistingThread ? FindWorker( _Worker, THREAD_ALL_ACCESS, pExit ) : CreateWorker( _Worker, pExit ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get worker thread to load library." ) ), fnCleanup( ), false;

	if ( !_Worker.Suspend( )
		|| !_Worker.Push( pImage )
		|| !_Worker.SimulateFunctionCall( pRelocateImageBase ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to call RelocateImageBase." ) ), fnCleanup( ), false;

	while ( !_Worker.ExecutingFunction( pThreadEnvironment, zThreadEnvironment ) )
		Pause( 50ui64 );

	if ( !_Worker.Suspend( )
		|| !_Worker.Push( LoadLibraryA )
		|| !_Worker.Push( GetProcAddress )
		|| !_Worker.Push( pImage )
		|| !_Worker.SimulateFunctionCall( pLoadDependencies ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to call LoadDependencies." ) ), fnCleanup( ), false;

	while ( _Worker.ExecutingFunction( pLoadDependencies, zLoadDependencies ) )
		Pause( 50ui64 );

	CONTEXT _ThreadContext;
	if ( !_Worker.GetContext( _ThreadContext )
		|| _ThreadContext.Eax != TRUE )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Failed to load dependencies." ) ), fnCleanup( ), false;

	if ( bEnableExceptions )
	{
		CONTEXT _Context;
		auto _Table = _RTL_INVERTED_FUNCTION_TABLE< DWORD >( );
		auto bFoundHandler = false;
		auto bCustomHandler = true;

		if ( !Read( pInvertedFunctionTable, _Table ) )
			return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to read function table." ) ), fnCleanup( ), false;

		for ( auto i = 0; i < _Table.Count && bCustomHandler; i++ )
			if ( _Table.Entries[ i ].ImageBase == std::uintptr_t( pImage )
				&& _Table.Entries[ i ].SizeOfTable > 0 )
				bFoundHandler = true;

		if ( !bFoundHandler )
		{
			if ( !_Worker.Suspend( )
				|| !_Worker.GetContext( _Context ) )
				return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Failed to suspend thread and get context." ) ), fnCleanup( ), false;

			_Context.Ecx = std::uintptr_t( pImage );
			_Context.Edx = _Image.GetImageSize( );

			if ( !_Worker.SetContext( _Context )
				|| !_Worker.SimulateFunctionCall( pInsertInvertedFunctionTable ) )
				return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Failed to call RtlInsertInvertedFunctionTable." ) ), fnCleanup( ), false;

			while ( !_Worker.ExecutingFunction( pThreadEnvironment, zThreadEnvironment ) )
				Pause( 50ui64 );

			if ( !Read( pInvertedFunctionTable, _Table ) )
				return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to read function table." ) ), fnCleanup( ), false;

			for ( auto i = 0; i < _Table.Count && bCustomHandler; i++ )
				if ( _Table.Entries[ i ].ImageBase == std::uintptr_t( pImage )
					&& _Table.Entries[ i ].SizeOfTable > 0 )
					bCustomHandler = false;

			if ( bCustomHandler )
				return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "SafeSEH is not enabled for this image, cannot load." ) ), fnCleanup( ), false;
		}
	}

	if ( !_Worker.Suspend( )
		|| !_Worker.Push( nullptr )
		|| !_Worker.Push( DLL_PROCESS_ATTACH )
		|| !_Worker.Push( pImage )
		|| !_Worker.SimulateFunctionCall( reinterpret_cast< void * >( std::uintptr_t( pImage ) + _Image.GetNewTechnologyHeaders( )->OptionalHeader.AddressOfEntryPoint ) ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to call entry point with message DLL_PROCESS_ATTACH." ) ), fnCleanup( ), false;

	while ( !_Worker.ExecutingFunction( pThreadEnvironment, zThreadEnvironment ) )
		Pause( 50ui64 );

	if ( !_Worker.GetContext( _ThreadContext ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Failed to get thread context to see if image loaded successfully." ) ), fnCleanup( ), false;

	const auto bReturn = _ThreadContext.Eax == TRUE;

	if ( !Write( pExit, true ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to signal thread to exit." ) ), fnCleanup( ), false;

	if ( bUseExistingThread )
	{
		while ( _Worker.ExecutingFunction( pThreadEnvironment, zThreadEnvironment ) )
			Pause( 50ui64 );

		if ( bUseExistingThread )
			if ( !_Worker.Close( ) )
				_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Failed to close worker." ) );
	}
	else if ( !_Worker.WaitForExecutionFinish( INFINITE ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Failed to wait for worker to close." ) );

	if ( bReturn )
	{
		if ( bEraseHeaders && !WipeMemory( pImage, _Image.GetHeaderSize( ) ) )
			_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Failed to erase headers." ) );

		if ( bEraseDiscardableSections )
			for ( auto i = 0; i < _Image.GetSectionCount( ); i++ )
			{
				const auto pSectionHeader = _Image.GetSectionHeader( i );
				if ( ( pSectionHeader->Characteristics & IMAGE_SCN_MEM_DISCARDABLE ) != NULL )
					if ( !WipeMemory( reinterpret_cast< void * >( std::uintptr_t( pImage ) + pSectionHeader->VirtualAddress ), pSectionHeader->SizeOfRawData ) )
						_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Failed to wipe section %i." ), i );
			}
	}
	else if ( !WipeMemory( pImage, _Image.GetImageSize( ) ) )
		_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Unable to wipe image from memory after entry point returned false." ) );

	fnCleanup( );
	return bReturn;
}

CMemoryManager _MemoryManager;
