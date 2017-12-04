#include "../main.h"

void General::GetPremiumUsers() {
	uPremiumUsers[0].cUsername = "bhopfu1";
	uPremiumUsers[0].iHardwareID = 12 * 4095;
	uPremiumUsers[0].tExpiration = OCTOBER_FIRST + 365 * DAY;
	uPremiumUsers[0].bValid = true;
	uPremiumUsers[0].bBanned = false;
	uPremiumUsers[1].cUsername = ""; // TODO MIKE
	uPremiumUsers[1].iHardwareID = 0;
	uPremiumUsers[1].tExpiration = OCTOBER_FIRST + 365 * DAY;
	uPremiumUsers[1].bValid = true;
	uPremiumUsers[1].bBanned = false;
	uPremiumUsers[2].cUsername = ""; // TODO SKEL
	uPremiumUsers[2].iHardwareID = 0;
	uPremiumUsers[2].tExpiration = OCTOBER_FIRST + 365 * DAY;
	uPremiumUsers[2].bValid = true;
	uPremiumUsers[2].bBanned = false;
	uPremiumUsers[3].cUsername = ""; // TODO COLE
	uPremiumUsers[3].iHardwareID = 0;
	uPremiumUsers[3].tExpiration = OCTOBER_FIRST + 365 * DAY;
	uPremiumUsers[3].bValid = true;
	uPremiumUsers[3].bBanned = false;
	uPremiumUsers[4].cUsername = ""; // TODO BEAN
	uPremiumUsers[4].iHardwareID = 0;
	uPremiumUsers[4].tExpiration = OCTOBER_FIRST + 365 * DAY;
	uPremiumUsers[4].bValid = true;
	uPremiumUsers[4].bBanned = false;
}

bool General::CompareName(User uPremiumUser, User uCurrentUser) {
	for (int n = 0; n < 256; n++) {
		if (uPremiumUser.cUsername[n] && uPremiumUser.cUsername[n] != uCurrentUser.cUsername[n]) {
			return false;
		}
		if (!uPremiumUser.cUsername[n]) {
			break;
		}
	}
	return true;
}

EPremium General::CheckPremiumStatus() {
	if (OCTOBER_FIRST > GetTime() && OCTOBER_FIRST - GetTime() > DAY) {
		return EPremium::NOT_PREMIUM;
	}
	DWORD dwSize = 257;
	User uCurrentUser = {};
	GetUserName(uCurrentUser.cUsername, &dwSize);
	GetPremiumUsers();
	int n = 0;
	for (; n <= PREMIUM_USERS; n++) {
		if (uPremiumUsers[n].bValid) {
			if (uPremiumUsers[n].cUsername && CompareName(uPremiumUsers[n], uCurrentUser)) {
				break;
			}
		} else {
			return EPremium::NOT_PREMIUM;
		}
	}
	SYSTEM_INFO siCurrentUser;
	GetSystemInfo(&siCurrentUser);
	uCurrentUser.iHardwareID = siCurrentUser.dwActiveProcessorMask * siCurrentUser.dwNumberOfProcessors;
	if (uCurrentUser.iHardwareID != uPremiumUsers[n].iHardwareID) {
		return EPremium::NOT_PREMIUM;
	}
	uCurrentUser.tExpiration = uPremiumUsers[n].tExpiration;
	if (uCurrentUser.tExpiration < GetTime()) {
		return EPremium::EXPIRED;
	}
	uCurrentUser.bBanned = uPremiumUsers[n].bBanned;
	if (uCurrentUser.bBanned) {
		return EPremium::BANNED;
	}
	return EPremium::PREMIUM;
}

bool General::GetElevationState() {
	HANDLE hTokenSelf;
	TOKEN_ELEVATION teSelf;
	DWORD dwReturnLength = sizeof(TOKEN_ELEVATION);
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hTokenSelf) &&
		GetTokenInformation(hTokenSelf, TokenElevation, &teSelf, dwReturnLength, &dwReturnLength)) {
		eElevationState = EElevation(bool(teSelf.TokenIsElevated));
	} else {
		eElevationState = EElevation::NOT_ADMIN;
	}
	CloseHandle(hTokenSelf);
	return bool(eElevationState);
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
	return bool(EElevation::NOT_ADMIN);
}

EAnticheatStatus General::KillAnticheat(LPCSTR cstrAnticheatName, char cAnticheatExe) {
	if (eElevationState == EElevation::UNTESTED) {
		GetElevationState();
	}
	if (FindWindowA(nullptr, cstrAnticheatName)) {
		if (eElevationState == EElevation::ADMIN) {
			system("taskkill /F /T /IM " + cAnticheatExe);
			return EAnticheatStatus::KILLED;
		}
		return EAnticheatStatus::FAILED;
	}
	return EAnticheatStatus::NOT_FOUND;
}

General all;
