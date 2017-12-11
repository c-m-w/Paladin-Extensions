#include "../dllmain.h"

void CGeneral::GetPremiumUsers() {
	uPremiumUsers[0].lpstrUsername = "bhopfu1";
	uPremiumUsers[0].iHardwareID = 12 * 4095;
	uPremiumUsers[0].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[0].bValid = true;
	uPremiumUsers[0].bBanned = false;
	uPremiumUsers[1].lpstrUsername = ""; // TODO MIKE
	uPremiumUsers[1].iHardwareID = 0;
	uPremiumUsers[1].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[1].bValid = true;
	uPremiumUsers[1].bBanned = false;
	uPremiumUsers[2].lpstrUsername = ""; // TODO SKEL
	uPremiumUsers[2].iHardwareID = 0;
	uPremiumUsers[2].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[2].bValid = true;
	uPremiumUsers[2].bBanned = false;
	uPremiumUsers[3].lpstrUsername = "Cole";
	uPremiumUsers[3].iHardwareID = 4 * 15;
	uPremiumUsers[3].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[3].bValid = true;
	uPremiumUsers[3].bBanned = false;
	uPremiumUsers[4].lpstrUsername = "Bean"; // TODO BEAN
	uPremiumUsers[4].iHardwareID = 0;
	uPremiumUsers[4].tExpiration = DECEMBER_FIRST + 365 * DAY;
	uPremiumUsers[4].bValid = true;
	uPremiumUsers[4].bBanned = false;
}

bool CGeneral::CompareName(User uPremiumUser, User uCurrentUser) {
	for (int n = 0; n < 256; n++) {
		if (uPremiumUser.lpstrUsername[n] && !uCurrentUser.lpstrUsername[n]) {
			return false;
		}
		if (!uPremiumUser.lpstrUsername[n] && uCurrentUser.lpstrUsername[n]) {
			return false;
		}
		if (!uPremiumUser.lpstrUsername[n] && !uCurrentUser.lpstrUsername[n]) {
			break;
		}
		if (uPremiumUser.lpstrUsername[n] != uCurrentUser.lpstrUsername[n]) {
			return false;
		}
	}
	return true;
}

EPremium CGeneral::CheckPremiumStatus() {
	if (DECEMBER_FIRST > GetTime()) {
		LogDebugMsg(ERR, "Date Mismatch: %i > %i", DECEMBER_FIRST, GetTime());
		return EPremium::NOT_PREMIUM;
	}
	GetPremiumUsers();
	User uCurrentUser;
	char cBuffer[257];
	DWORD dwBufferSize = 257;
	GetUserNameA(cBuffer, &dwBufferSize);
	uCurrentUser.lpstrUsername = cBuffer;
	LogDebugMsg(DBG, "Current User Username: %s", uCurrentUser.lpstrUsername);
	int n = 0;
	for (; n <= PREMIUM_USERS; n++) {
		if (uPremiumUsers[n].bValid) {
			if (uPremiumUsers[n].lpstrUsername && CompareName(uPremiumUsers[n], uCurrentUser)) {
				break;
			}
		} else {
			LogDebugMsg(ERR, "Username did not match any users in database");
			return EPremium::NOT_PREMIUM;
		}
	}
	LogDebugMsg(DBG, "Current User Database ID: %i", n);
	SYSTEM_INFO siCurrentUser;
	GetSystemInfo(&siCurrentUser);
	uCurrentUser.iHardwareID = siCurrentUser.dwActiveProcessorMask * siCurrentUser.dwNumberOfProcessors;
	LogDebugMsg(DBG, "Current User HWID: %i", uCurrentUser.iHardwareID);
	if (uCurrentUser.iHardwareID != uPremiumUsers[n].iHardwareID) {
		LogDebugMsg(ERR, "HWID did not match any users in database");
		return EPremium::NOT_PREMIUM;
	}
	uCurrentUser.tExpiration = uPremiumUsers[n].tExpiration;
	LogDebugMsg(DBG, "Current User Premium Time: %i", uCurrentUser.tExpiration);
	if (uCurrentUser.tExpiration < GetTime()) {
		LogDebugMsg(ERR, "%i < %i", uCurrentUser.tExpiration, GetTime());
		LogDebugMsg(ERR, "User is out of premium");
		return EPremium::EXPIRED;
	}
	uCurrentUser.bBanned = uPremiumUsers[n].bBanned;
	if (uCurrentUser.bBanned) {
		LogDebugMsg(SCS, "User is banned");
		return EPremium::BANNED;
	}
	LogDebugMsg(SCS, "User is premium!");
	return EPremium::PREMIUM;
}

bool CGeneral::GetElevationState() {
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

bool CGeneral::GetElevationState(HANDLE hTarget) {
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

EAnticheatStatus CGeneral::KillAnticheat(LPCSTR cstrAnticheatName, char cAnticheatExe) {
	if (eElevationState == EElevation::UNTESTED) {
		GetElevationState();
	}
	if (FindWindowA(nullptr, cstrAnticheatName)) {
		if (eElevationState == EElevation::ADMIN) {
			system("taskkill /F /T /IM " + cAnticheatExe);
			LogDebugMsg(WRN, "Found anticheat %s open and terminated it", cstrAnticheatName);
			return EAnticheatStatus::KILLED;
		}
		LogDebugMsg(WRN, "Found anticheat %s open", cstrAnticheatName);
		return EAnticheatStatus::FAILED;
	}
	LogDebugMsg(WRN, "Did not find anticheat %s open", cstrAnticheatName);
	return EAnticheatStatus::NOT_FOUND;
}

CGeneral all;
