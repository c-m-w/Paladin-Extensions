#include "main.h"

MemoryManager *mem = nullptr;

MemoryManager::~MemoryManager() 
{
	if (hGame != nullptr || hGame != INVALID_HANDLE_VALUE)
		CloseHandle(hGame);
}

bool MemoryManager::AttachToGame() 
{
	while (!GetWindowThreadProcessId(FindWindowA(nullptr, "Counter-Strike: Global Offensive"), &dwProcessId)) 
	{
		dbg->LogDebugMsg(DBG, "Searching for CSGO");
		Wait(1000);
	}

	hGame = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, dwProcessId);

	if (!hGame) 
	{
		dbg->LogDebugMsg(ERR, "Invalid game handle");
		return false;
	}

	dbg->LogDebugMsg(SCS, "Attached to game");

	HANDLE hSnapshot;
	for (uint8_t ui = 0; ui < 5; ui++, Wait(2000)) 
	{
		do 
		{
			SetLastError(0);
			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
			Wait(10);
		} while (hSnapshot == INVALID_HANDLE_VALUE || GetLastError() == ERROR_BAD_LENGTH);

		if (hSnapshot == INVALID_HANDLE_VALUE) 
		{
			dbg->LogDebugMsg(ERR, "Invalid module snapshot");
			return false;
		}

		dbg->LogDebugMsg(SCS, "Module snapshot created");

		MODULEENTRY32 me = {};
		me.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(hSnapshot, &me)) 
		{
			do 
			{
				if (!_stricmp(me.szModule, "client.dll"))
					dwClientBase = DWORD(me.modBaseAddr);
				else if (!_stricmp(me.szModule, "engine.dll"))
					dwEngineBase = DWORD(me.modBaseAddr);
			} while (Module32Next(hSnapshot, &me));

			CloseHandle(hSnapshot);
		}

		if (dwClientBase && dwEngineBase) 
		{
			dbg->LogDebugMsg(SCS, "Modules found");
			dbg->LogDebugMsg(SCS, "Client.dll: 0x%p", dwClientBase);
			dbg->LogDebugMsg(SCS, "Engine.dll: 0x%p", dwEngineBase);
			return true;
		}

		dbg->LogDebugMsg(DBG, "Modules not found, retrying");
		dbg->LogDebugMsg(DBG, "Client.dll: 0x%p", dwClientBase);
		dbg->LogDebugMsg(DBG, "Engine.dll: 0x%p", dwEngineBase);
	}

	dbg->LogDebugMsg(ERR, "Unable to get modules");
	return false;
}

void MemoryManager::InitializeAddresses() 
{
	dbg->LogDebugMsg(DBG, "Initializing addresses");

	Addresses::dwClientState += dwEngineBase;

	Read(Addresses::dwClientState);

	Addresses::cs_soState += Addresses::dwClientState.loc;
	Addresses::ksForceJump += dwClientBase;
	Addresses::ksForceAttack += dwClientBase;
	Addresses::flSensitivity += dwClientBase;

	dbg->LogDebugMsg(DBG, "Waiting for server connection to complete address initialization");

	do 
	{
		Read(Addresses::cs_soState);
		Wait(100);
	} while (Addresses::cs_soState != SignOnState::FULL);

	Addresses::dwLocalPlayer += dwClientBase;

	Read(Addresses::dwLocalPlayer);

	Addresses::lp_fFlags += Addresses::dwLocalPlayer.loc;
	Addresses::lp_totalHitsOnServer += Addresses::dwLocalPlayer.loc;

	dbg->LogDebugMsg(DBG, "Client Base: %p", dwClientBase);

	dbg->LogDebugMsg(SCS, "Initialized addresses");
}
