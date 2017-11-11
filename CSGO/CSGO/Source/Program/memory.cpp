#include "../main.h"

MemoryManager::MemoryManager() 
{

}

MemoryManager::~MemoryManager() 
{
	if (hGame != nullptr || hGame != INVALID_HANDLE_VALUE) 
		CloseHandle(hGame);
}

bool MemoryManager::AttachToGame() 
{
	while (!GetWindowThreadProcessId(FindWindowA(nullptr, "Counter-Strike: Global Offensive"), &(this->dwProcessId))) 
	{
		LogDebugMsg(DBG, "Searching for CSGO\n");
		Wait(1000);
	}

	this->hGame = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, this->dwProcessId);

	if (!this->hGame) 
	{
		LogDebugMsg(ERR, "Invalid game handle\n");
		return false;
	}

	LogDebugMsg(SCS, "Attached to game\n");

	HANDLE hSnapshot = INVALID_HANDLE_VALUE;

	for (int i = 0; i < 5; i++, Wait(2000)) 
	{
		do 
		{
			SetLastError(0);
			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
			Wait(10);
		} while (hSnapshot == INVALID_HANDLE_VALUE || GetLastError() == ERROR_BAD_LENGTH);

		if (hSnapshot == INVALID_HANDLE_VALUE) 
		{
			LogDebugMsg(ERR, "Invalid module snapshot\n");
			return false;
		}

		LogDebugMsg(SCS, "Module snapshot created\n");

		MODULEENTRY32 me = {};
		me.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(hSnapshot, &me)) 
		{
			do 
			{
				if (!_stricmp(me.szModule, "client.dll"))
					this->dwClientBase = (DWORD)me.modBaseAddr;
				else if (!_stricmp(me.szModule, "engine.dll"))
					this->dwEngineBase = (DWORD)me.modBaseAddr;
			} while (Module32Next(hSnapshot, &me));
			CloseHandle(hSnapshot);
		}

		if (this->dwClientBase && this->dwEngineBase)
		{
			LogDebugMsg(SCS, "Modules found\n");
			LogDebugMsg(SCS, "Client.dll: 0x%p\n", this->dwClientBase);
			LogDebugMsg(SCS, "Engine.dll: 0x%p\n", this->dwEngineBase);
			return true;
		}

		LogDebugMsg(DBG, "Modules not found, retrying");
		LogDebugMsg(DBG, "Client.dll: 0x%p\n", this->dwClientBase);
		LogDebugMsg(DBG, "Engine.dll: 0x%p\n", this->dwEngineBase);
	}

	LogDebugMsg(ERR, "Unable to get modules\n");

	return false;
}

void MemoryManager::InitializeAddresses() 
{
	iForceJump += dwClientBase;
	dwLocalPlayer += dwClientBase;
	Read(dwLocalPlayer);
	lp_iFlags += dwLocalPlayer.loc;
}