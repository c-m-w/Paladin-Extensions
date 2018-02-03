#include "../main.h"

bool Inject( LPWSTR dll, DWORD processId )
{
	if ( !processId )
		return false;

	HANDLE hProcess = INVALID_HANDLE_VALUE, hThread = INVALID_HANDLE_VALUE;
	LPVOID mRegion = nullptr;
	FARPROC loadLibrary = nullptr;

	hProcess = OpenProcess( PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processId );

	if ( !hProcess )
		return false;

	mRegion = VirtualAllocEx( hProcess, nullptr, wcslen( dll ), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );

	if ( !mRegion )
	{
		CloseHandle( hProcess );
		return false;
	}

	if ( !WriteProcessMemory( hProcess, mRegion, reinterpret_cast< LPCVOID >( dll ), wcslen( dll ), nullptr ) )
	{
		CloseHandle( hProcess );
		return false;
	}

	loadLibrary = GetProcAddress( GetModuleHandle( L"Kernel32" ), "LoadLibraryA" );

	if ( !loadLibrary )
	{
		CloseHandle( hProcess );
		return false;
	}

	hThread = CreateRemoteThread( hProcess, nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( loadLibrary ), mRegion, 0, nullptr );

	if ( !hThread )
	{
		CloseHandle( hProcess );
		return false;
	}

	WaitForSingleObject( hThread, INFINITE );

	VirtualFreeEx( hProcess, mRegion, wcslen( dll ), MEM_RELEASE );

	CloseHandle( hThread );
	CloseHandle( hProcess );

	return true;
}
