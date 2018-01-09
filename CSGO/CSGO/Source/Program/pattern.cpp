#include "../dllmain.h"

CPatternScanner scan; // always declare object AFTER function definition (at bottom of file)

MODULEENTRY32 CPatternScanner::GetModule(char *module)
{
	HANDLE hSnapshot = INVALID_HANDLE_VALUE; // no need to initialize this

	DEBUG(DBG, "Creating snapshot");

	do
	{
		SetLastError(0);
		hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, mem.dwProcessID);
		Wait(1);
	} while (hSnapshot == INVALID_HANDLE_VALUE || GetLastError() == ERROR_BAD_LENGTH);

	if (hSnapshot == INVALID_HANDLE_VALUE || !hSnapshot)
	{
		DEBUG(DBG, "Snapshot failure"); // should be an ERR
		return MODULEENTRY32({});
	}

	DEBUG(DBG, "Snapshot created"); // should be an SCS
	DEBUG(DBG, "Searching for module");

	MODULEENTRY32 me = { NULL }; // never do `= { }`, do `{ }`. also, never initialize with `NULL` inside braces
	me.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &me))
	{
		do
		{
			//DEBUG(SCS, "%s", me.szModule);
			if (!_stricmp(me.szModule, module))
			{
				DEBUG(DBG, "Module found");
				CloseHandle(hSnapshot);
				return me;
			}
		} while (Module32Next(hSnapshot, &me));
		CloseHandle(hSnapshot);
	}

	DEBUG(DBG, "Module not found");

	return MODULEENTRY32({});
}

// dont use uintptr_t, use unsigned int
uintptr_t CPatternScanner::FindPattern(char* base, unsigned int size, char* pattern, char *mask) // pattern should be const as it's a pointer
{
	size_t patternLength = strlen(mask);

	for (uintptr_t i = 0; i < size - patternLength; i++)
	{
		bool found = true;
		for (uintptr_t j = 0; j < patternLength; j++)
		{
			if (mask[j] != '?' && pattern[j] != *(char*)(base + i + j)) // c-style cast is old news, use static cast
			{
				found = false;
				break; // yeah that's right, stop iterating when pattern is bad.  Looking at you fleep...
				// haha, fleep is dump
			}
		}

		if (found)
			return (uintptr_t)base + i; // reinterpret-style cast is best here
	}
	return 0;
}
uintptr_t CPatternScanner::FindPatternEx(HANDLE hProcess, char *module, char *pattern, char *mask)
{
	DEBUG(DBG, "Starting scan");

	//Grab module information from External Process
	MODULEENTRY32 modEntry = GetModule(module);
	DWORD start = (DWORD)modEntry.modBaseAddr; // function-style cast is best here
	DWORD end = start + modEntry.modBaseSize;

	DEBUG(DBG, "Start: 0x%p", start);
	DEBUG(DBG, "Size: 0x%p", end);

	uintptr_t currentChunk = start;
	SIZE_T bytesRead;

	while (currentChunk < end)
	{
		//make data accessible to ReadProcessMemory
		DWORD oldprotect;
		VirtualProtectEx(hProcess, (void*)currentChunk, 4096, PROCESS_VM_READ, &oldprotect);// reinterpret-style cast is best here

		//Copy chunk of external memory into local storage
		byte buffer[4096];
		ReadProcessMemory(hProcess, (void*)currentChunk, &buffer, 4096, &bytesRead);// reinterpret-style cast is best here

		//if readprocessmemory failed, return
		if (bytesRead == 0)
		{
			return 0;
		}

		//Find pattern in local buffer, if pattern is found return address of matching data
		uintptr_t InternalAddress = FindPattern((char*)&buffer, bytesRead, pattern, mask);// reinterpret-style cast is best here

		//if Find Pattern returned an address
		if (InternalAddress != 0)
		{
			//convert internal offset to external address and return
			uintptr_t offsetFromBuffer = InternalAddress - (uintptr_t)&buffer; // function-style cast is best here
			return currentChunk + offsetFromBuffer;
		}

		//pattern not found in this chunk, advance to next chunk
		currentChunk = currentChunk + bytesRead;
	}
	return 0;
}