#include "../main.h"

DWORD getFirstCSGO( )
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );

	if ( Process32First( snap, &entry ) )
	{
		do
		{
			if ( !wcscmp( entry.szExeFile, L"csgo.exe" ) )
			{
				CloseHandle( snap );
				return entry.th32ProcessID;
			}
		} while ( Process32Next( snap, &entry ) );
	}

	CloseHandle( snap );

	return 0;
}
