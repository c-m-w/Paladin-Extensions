#pragma once
#include "../includes.h"

class General {
public:
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
