/// Memory Manager.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

bool CMemoryManager::SetProcess( const std::string &strExecutable, DWORD dwAccess )
{
	if ( hProcess != nullptr )
		if ( CloseHandle( hProcess ) == FALSE )
			_Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Unable to close old process handle." ) );

	hProcess = nullptr;

	if ( dwAccess == NULL )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Access to open executable %s is invalid." ), strExecutable.c_str( ) ), false;

	DWORD dwProcessID;
	if ( !SI.GetProcessID( strExecutable, dwProcessID ) )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to get process id of executable %s." ), strExecutable.c_str( ) ), false;

	hProcess = OpenProcess( dwAccess, FALSE, dwProcessID );
	if ( hProcess == nullptr
		 || hProcess == INVALID_HANDLE_VALUE )
		return _Log.Log( EPrefix::ERROR, ELocation::MEMORY_MANAGER, ENC( "Unable to open process handle of executable %s." ), strExecutable.c_str( ) ), false;

	dwCurrentAccess = dwAccess;
	return true;
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
