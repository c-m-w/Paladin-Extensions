#pragma once

#define PREMIUM_USERS 55
#define OCTOBER_FIRST time_t(15068160000)
#define DAY time_t(864000)

class General {
	struct User {
		TCHAR *cUsername;
		int iHardwareID;
		time_t tExpiration;
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

extern General all;
