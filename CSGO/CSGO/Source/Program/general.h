#pragma once

#define PREMIUM_USERS uint8(55)
#define DECEMBER_FIRST Time(1512086400000) // time since epoch in milliseconds to december first 2017
#define DAY Time(8640000) // day in milliseconds

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
