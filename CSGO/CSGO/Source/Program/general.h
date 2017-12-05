#pragma once

#define PREMIUM_USERS uint8(55)
#define OCTOBER_FIRST std::chrono::duration_cast<std::chrono::milliseconds>(15068160000)
#define DAY std::chrono::duration_cast<std::chrono::milliseconds>(8640000)

class CGeneral {
	struct User {
		LPSTR lpstrUsername;
		int iHardwareID;
		std::chrono::milliseconds tExpiration;
		bool bValid;
		bool bBanned;
	};

	User uPremiumUsers[PREMIUM_USERS];
	void GetPremiumUsers();
	bool CompareName(User, User);
public:
	EPremium CheckPremiumStatus();
private:
	EElevation eElevationState = EElevation::UNTESTED;
public:
	bool GetElevationState();
	bool GetElevationState(HANDLE);
	EAnticheatStatus KillAnticheat(LPCSTR, char);
};

extern CGeneral all;
