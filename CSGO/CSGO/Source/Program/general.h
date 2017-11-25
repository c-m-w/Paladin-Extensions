#pragma once
#include "../includes.h"

class General {
	uint8 uiElevationState = -1;
public:
	bool GetElevationState();
	uint8 KillAnticheat(LPCSTR cstrAnticheatName, char cAnticheatExe);
};

extern General all;
