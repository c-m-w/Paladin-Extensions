#pragma once
#include "../includes.h"
#define PREMIUM_USERS 55
#define OCTOBER_FIRST 15068160000
#define DAY 864000

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
	bool CompareName(User uPremiumUser, User uCurrentUser);
public:
	EPremium CheckPremiumStatus();
private:
	EElevation eElevationState = EElevation::UNTESTED;
public:
	bool GetElevationState();
	bool GetElevationState(HANDLE hTarget);
	EAnticheatStatus KillAnticheat(LPCSTR cstrAnticheatName, char cAnticheatExe);
};

extern General all;
