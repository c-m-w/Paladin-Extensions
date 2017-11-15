#pragma once
#include "../main.h"
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
	std::string sVersion = "1.0";
	unsigned short uiQuitReason = 0;

#ifdef _DEBUG
	bool bCheckForAnticheat = false;
#else
	bool bCheckForAnticheat = true;
#endif

	// Keys
	int uiExitKey;
	int uiReloadKey;

	Config();
	// open config, create if doesn't exist
	bool LoadConfig();
	// read loaded config, replace impossible values
	bool ReadConfig();
	// set quit reason
	~Config();
};
