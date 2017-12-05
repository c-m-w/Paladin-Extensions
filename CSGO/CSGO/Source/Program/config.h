#pragma once

struct version {
	uint8 upper, lower;

	bool operator==(const version &rhs) {
		if (upper == rhs.upper && lower == rhs.lower) {
			return true;
		}
		return false;
	}
};

class CConfig {
	char cfgPath[255];
	// read from config
	template<typename datatype> void Read(char *cSetting, char *cSubSetting, datatype &Status) {
	}

	// write to config
	template<typename datatype> void Write(char *cSetting, char *cSubSetting, datatype Status) {
	}

public:
	version verVersion;
	EQuitReasons iQuitReason;

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
	bool bHitSound;
	bool bAutoJumpState;

	// Feature Settings
	std::string strHitSoundLocation;

	CConfig();
	// open config, create if doesn't exist
	bool LoadConfig();
	// read loaded config, replace impossible values
	bool ReadConfig();
	// set quit reason
	~CConfig();
};

extern CConfig cfg;
