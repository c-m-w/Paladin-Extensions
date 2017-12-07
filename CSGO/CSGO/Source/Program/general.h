#pragma once

#define PREMIUM_USERS uint8(55)
#define OCTOBER_FIRST Time(15068160000)
#define DAY Time(8640000)

class CGeneral {
	struct User {
		LPSTR lpstrUsername = nullptr;
		int iHardwareID = 0;
		Time tExpiration = 0;
		bool bValid = false;
		bool bBanned = false;
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
