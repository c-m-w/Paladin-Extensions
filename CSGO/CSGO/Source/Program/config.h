#pragma once
#include "../includes.h"

struct version {
	uint8 upper, lower;

	bool operator==(const version &rhs) {
		if (upper == rhs.upper && lower == rhs.lower) {
			return true;
		}
		return false;
	}
};

class Config {
	char cfgPath[255];
	// read from config
	template<typename datatype> void Read(char *cSetting, char *cSubSetting, datatype &Status) {
	}

	// write to config
	template<typename datatype> void Write(char *cSetting, char *cSubSetting, datatype Status) {
	}

public:
	version verVersion;
	int iQuitReason;

#ifdef _DEBUG
	bool bCheckForAnticheat = false;
#else
	bool bCheckForAnticheat = true;
#endif

	// Keys
	int iExitKey;
	int iReloadKey;
	int iAutoJumpKey;

	// Feature Toggles
	bool bAutoJumpState;

	Config();
	// open config, create if doesn't exist
	bool LoadConfig();
	// read loaded config, replace impossible values
	bool ReadConfig();
	// set quit reason
	~Config();
};

extern Config cfg;
