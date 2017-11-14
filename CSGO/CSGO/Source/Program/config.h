#pragma once

class Config {
	struct Version {
		unsigned short major;
		unsigned short minor;
		bool operator==(const Version &rvalue) const;
	};

	char cfgPath[255];
	// read from config
	template<class datatype> void Read(char *setting, char *subsetting, datatype &status);
	// write to config
	template<class datatype> void Write(char *setting, char *subsetting, datatype status);
public:
	Version vVersion = {1, 0};
	unsigned short uiQuitReason = -1;

#ifdef _DEBUG
	bool bCheckForAnticheat = false;
#else
	bool bCheckForAnticheat = true;
#endif

	// Keys
	int uiExitKey;
	int uiReloadKey;

	Config();
	// open config, return false & create if doesn't exist
	bool LoadConfig();
	// read loaded config, replace impossible values
	bool ReadConfig();
	// set quit reason
	~Config();
};
