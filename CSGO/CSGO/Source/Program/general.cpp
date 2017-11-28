#include "general.h"

General all;

bool General::CompareName(User uOwner, User uCurrentUser) {
	for (int n = 0; n < 256; n++) {
		if (uOwner.cUsername[n] && uOwner.cUsername[n] != uCurrentUser.cUsername[n]) {
			return false;
		}
		if (!uOwner.cUsername[n]) {
			break;
		}
	}
	return true;
}

void General::GetOwners() {
	uOwners[0].cUsername = "bhopfu1";
	uOwners[0].iHardwareID = 12 * 4095;
	uOwners[0].tExpiration = OCTOBER_FIRST + 365 * DAY;
	uOwners[0].bValid = true;

	uOwners[1].cUsername = ""; // TODO MIKE
	uOwners[1].iHardwareID = 0;
	uOwners[1].tExpiration = OCTOBER_FIRST + 365 * DAY;
	uOwners[1].bValid = true;

	uOwners[2].cUsername = ""; // TODO SKEL
	uOwners[2].iHardwareID = 0;
	uOwners[2].tExpiration = OCTOBER_FIRST + 365 * DAY;
	uOwners[2].bValid = true;

	uOwners[3].cUsername = "Cole White";
	uOwners[3].iHardwareID = 0;
	uOwners[3].tExpiration = OCTOBER_FIRST + 365 * DAY;
	uOwners[3].bValid = true;

	uOwners[4].cUsername = ""; // TODO BEAN
	uOwners[4].iHardwareID = 0;
	uOwners[4].tExpiration = OCTOBER_FIRST + 365 * DAY;
	uOwners[4].bValid = true;
}

uint8 General::CheckOwnershipStatus() {
	if (OCTOBER_FIRST > GetTime() && OCTOBER_FIRST - GetTime() > DAY) { // TODO REPLACE OCTOBER_FIRST WITH TIME OF SERVER IN THIS LINE ONLY
		return false;
	}
	DWORD dwSize = 257;
	User uCurrentUser;
	GetUserName(uCurrentUser.cUsername, &dwSize);
	GetOwners();
	int n = 0;
	for (; n <= 51; n++) {
		if (uOwners[n].bValid) {
			if (uOwners[n].cUsername && CompareName(uOwners[n], uCurrentUser)) {
				break;
			}
		}
		else {
			return 0;
		}
	}
	SYSTEM_INFO siCurrentUser;
	GetSystemInfo(&siCurrentUser);
	uCurrentUser.iHardwareID = siCurrentUser.dwActiveProcessorMask * siCurrentUser.dwNumberOfProcessors;
	if (uCurrentUser.iHardwareID != uOwners[n].iHardwareID) {
		return 0;
	}
	uCurrentUser.tExpiration = uOwners[n].tExpiration;
	if (uCurrentUser.tExpiration < GetTime()) {
		return -1;
	}
	return 1;
}

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
