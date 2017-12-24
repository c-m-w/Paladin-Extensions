#include "main.h"

void Wait(uint32_t z) 
{
	std::this_thread::sleep_for(std::chrono::milliseconds(z));
}

unsigned int GetTime()
{
	return static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

bool IsElevated() 
{
	bool ret = false;
	HANDLE hToken = NULL;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		TOKEN_ELEVATION elev;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);

		if (GetTokenInformation(hToken, TokenElevation, &elev, sizeof(elev), &cbSize))
			ret = elev.TokenIsElevated;
	}

	if (hToken)
		CloseHandle(hToken);

	return ret;
}

uint8_t KillAntiCheat(LPCSTR cstrAntiCheatName, char cAntiCheatExe) 
{
	dbg->LogDebugMsg(DBG, "Attempting to kill %s [%s]", cstrAntiCheatName, cAntiCheatExe);

	if (!IsElevated()) 
	{
		dbg->LogDebugMsg(ERR, "Not running with admin permissions");
		return -2;
	}

	if (FindWindowA(nullptr, cstrAntiCheatName)) 
	{
		dbg->LogDebugMsg(DBG, "Found %s", cstrAntiCheatName);

		system("taskkill /F /T /IM " + cAntiCheatExe);

		/*
		//Check if process is still runnig, return 1 on running
		dbg->LogDebugMsg(ERR, "Unable to kill %s", cstrAntiCheatName);
		return 1;
		*/

		dbg->LogDebugMsg(SCS, "Successfully killed %s", cstrAntiCheatName);

		return 0;
	}

	dbg->LogDebugMsg(DBG, "Unable to find %s [%s]", cstrAntiCheatName, cAntiCheatExe);

	return -1; // No AntiCheat found
}
