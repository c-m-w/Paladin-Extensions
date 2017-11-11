#include "main.h"

bool StandardInject(char *dll, DWORD processId) 
{
	HANDLE hProcess, hThread;
	LPVOID mRegion;
	FARPROC loadLibrary;

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

	if (!hProcess) 
		return false;

	mRegion = VirtualAllocEx(hProcess, NULL, strlen(dll), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (!mRegion)
	{
		CloseHandle(hProcess);
		return false;
	}

	if (!WriteProcessMemory(hProcess, mRegion, (LPCVOID)dll, strlen(dll), NULL))
	{
		CloseHandle(hProcess);
		return false;
	}

	loadLibrary = GetProcAddress(GetModuleHandle("Kernel32"), "LoadLibraryA");

	if (!loadLibrary) 
	{
		CloseHandle(hProcess);
		return false;
	}

	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibrary, mRegion, 0, NULL);

	if (!hThread) 
	{
		CloseHandle(hProcess);
		return false;
	}

	WaitForSingleObject(hThread, INFINITE);

	VirtualFreeEx(hProcess, mRegion, strlen(dll), MEM_RELEASE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return true;
}