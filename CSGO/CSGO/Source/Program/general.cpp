#include "general.h"

General all;

bool General::GetElevationState() {
	HANDLE hTokenSelf;
	TOKEN_ELEVATION teSelf;
	DWORD dwReturnLength = sizeof(TOKEN_ELEVATION);

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hTokenSelf) &&
		GetTokenInformation(hTokenSelf, TokenElevation, &teSelf, dwReturnLength, &dwReturnLength)) {
			uiElevationState = Elevation(bool(teSelf.TokenIsElevated));
	} else {
		uiElevationState = NOT_ADMIN;
	}

	CloseHandle(hTokenSelf);
	return uiElevationState;
}

bool General::GetElevationState(HANDLE hTarget) {
	HANDLE hTokenTarget;
	TOKEN_ELEVATION teTarget;
	DWORD dwReturnLength = sizeof(TOKEN_ELEVATION);

	if (OpenProcessToken(hTarget, TOKEN_QUERY, &hTokenTarget) &&
		GetTokenInformation(hTokenTarget, TokenElevation, &teTarget, dwReturnLength, &dwReturnLength)) {
		CloseHandle(hTokenTarget);
		return bool(teTarget.TokenIsElevated);
	}
	CloseHandle(hTokenTarget);
	return NOT_ADMIN;
}

uint8 General::KillAnticheat(LPCSTR cstrAnticheatName, char cAnticheatExe) {
	if (uiElevationState == UNTESTED) {
		GetElevationState();
	}
	if (FindWindowA(nullptr, cstrAnticheatName)) {
		if (uiElevationState == ADMIN) {
			system("taskkill /F /T /IM " + cAnticheatExe);
			return KILLED;
		}
		return FAILED;
	}
	return NOT_FOUND;
}
