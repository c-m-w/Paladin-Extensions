#pragma once
#include "../main.h"

struct version {
	uint8_t lower;
	uint8_t upper;
};

class Config {
	char cfgPath[255];
	// read from config
	void Read(char *setting, char *subsetting, bool &status);
	void Read(char *setting, char *subsetting, int &status);
	void Read(char *setting, char *subsetting, float &status);
	void Read(char *setting, char *subsetting, double &status);
	void Read(char *setting, char *subsetting, std::string &status);
	// write to config
	void Write(char *setting, char *subsetting, bool status);
	void Write(char *setting, char *subsetting, int status);
	void Write(char *setting, char *subsetting, float status);
	void Write(char *setting, char *subsetting, double status);
	void Write(char *setting, char *subsetting, std::string status);

public:
	std::string sVersion;
	unsigned short uiQuitReason;

#ifdef _DEBUG
	bool bCheckForAnticheat = false;
#else
	bool bCheckForAnticheat = true;
#endif

	// Keys
	int uiExitKey;
	int uiReloadKey;
	int uiAutoJumpKey;

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
