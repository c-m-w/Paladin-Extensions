#include "general.h"
General all;
bool General::GetElevationState() {
	HANDLE hSelf = nullptr;
	TOKEN_ELEVATION teSelf;
	DWORD dwReturnLength = sizeof(TOKEN_ELEVATION);

	OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hSelf);

	if (GetTokenInformation(hSelf, TokenElevation, &teSelf, dwReturnLength, &dwReturnLength)) {
		uiElevationState = bool(teSelf.TokenIsElevated);
	} else {
		uiElevationState = 0;
	}
	CloseHandle(hSelf);
	return uiElevationState;
}

uint8 General::KillAnticheat(LPCSTR cstrAnticheatName, char cAnticheatExe) {
	if (uiElevationState == -1) {
		GetElevationState();
	}
	if(FindWindowA(nullptr, cstrAnticheatName)) {
		if (uiElevationState == 1) {
			system("taskkill /F /T /IM " + cAnticheatExe);
			return 1; // Anticheat Killed
		}
		return 0; // Anticheat unkillable
	}
	return -1; // No anticheat found
}
