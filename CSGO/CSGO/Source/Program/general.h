#pragma once
#include "../includes.h"


class General {
private:
	const int OCTOBER_FIRST = 1506816000;
	const int DAY = 86400;
	struct User {
		TCHAR *cUsername;
		int iHardwareID;
		time_t tExpiration;
		bool bValid;
	};
	User uOwners[55];
	bool CompareName(User uOwner, User uCurrentUser);
	void GetOwners();
public:
	uint8 CheckOwnershipStatus();
	enum Elevation {
		UNTESTED = -1,
		NOT_ADMIN,
		ADMIN
	};
private:
	enum AnticheatStatus {
		NOT_FOUND = -1,
		FAILED,
		KILLED
	};
	Elevation uiElevationState = UNTESTED;
public:
	bool GetElevationState();
	bool GetElevationState(HANDLE hTarget);
	uint8 KillAnticheat(LPCSTR cstrAnticheatName, char cAnticheatExe);
};

extern General all;
