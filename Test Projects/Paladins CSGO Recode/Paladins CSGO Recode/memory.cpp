#include "main.h"

Memory::Memory()
{
	this->hGame = nullptr;

	this->clientDll = NULL;
	this->engineDll = NULL;

	this->clientOffs = 0x5A765C;
	this->client = NULL;

	this->clientStateOffs = 0x108;
	this->clientState = NULL;
}

bool Memory::Attach()
{
	DWORD dwProcessId = NULL;

	while (!GetWindowThreadProcessId(FindWindowA(nullptr, "Counter-Strike: Global Offensive"), &dwProcessId)) 
	{
		DEBUG(DBG, 2, "Searching for CSGO\n");
		wait(2000);
	}

	DEBUG(DBG, 2, "Opening process\n");

	this->hGame = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, dwProcessId);

	if (!this->hGame) {
		DEBUG(ERR, 2, "Invalid game handle\n");
		LASTERR(2);
		return false;
	}

	DEBUG(SCS, 2, "Attached to game\n");

	HANDLE hSnapshot = INVALID_HANDLE_VALUE;

	DEBUG(DBG, 2, "Creating module snapshot\n");

	for (unsigned int i = 0; i < 5; i++, wait(2000)) 
	{
		do 
		{
			SetLastError(0);
			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
			wait(100);
		} while (hSnapshot == INVALID_HANDLE_VALUE || GetLastError() == ERROR_BAD_LENGTH);

		if (hSnapshot == INVALID_HANDLE_VALUE) 
		{
			DEBUG(ERR, 2, "Invalid module snapshot\n");
			LASTERR(2);
			return false;
		}

		DEBUG(SCS, 2, "Module snapshot created\n");

		MODULEENTRY32 me = {};
		me.dwSize = sizeof(MODULEENTRY32);

		DEBUG(DBG, 2, "Searching for modules\n");

		if (Module32First(hSnapshot, &me)) 
		{
			do 
			{
				if (!_stricmp(me.szModule, "client.dll"))
					this->clientDll = (DWORD)me.modBaseAddr;
				else if (!_stricmp(me.szModule, "engine.dll"))
					this->engineDll = (DWORD)me.modBaseAddr;

			} while (Module32Next(hSnapshot, &me));
			CloseHandle(hSnapshot);
		}

		//0x%08lu
		if (this->clientDll && this->engineDll) 
		{
			DEBUG(SCS, 2, "Modules found\n");
			DEBUG(SCS, 3, "Client.dll: 0x%08lu\n", this->clientDll);
			DEBUG(SCS, 3, "Engine.dll: 0x%08lu\n", this->engineDll);
			return true;
		}

		DEBUG(WRN, 2, "Modules not found, retrying");
		DEBUG(WRN, 3, "Client.dll: 0x%08lu\n", this->clientDll);
		DEBUG(WRN, 3, "Engine.dll: 0x%08lu\n", this->engineDll);
	}

	DEBUG(ERR, 2, "Unable to get modules\n");

	return false;
}

bool Memory::Init()
{
	this->client = rpm<DWORD>(this->engineDll + this->clientOffs);

	DEBUG(SCS, 2, "Client: 0x%08lu\n", this->client);

	return true;
}