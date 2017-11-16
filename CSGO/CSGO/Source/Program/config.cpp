#include "config.h"

Config cfg;

void Config::Read(char *setting, char *subsetting, bool &status) {
	double temp = status;
	Read(setting, subsetting, temp);
	status = bool(temp);
}

void Config::Read(char *setting, char *subsetting, int &status) {
	double temp = status;
	Read(setting, subsetting, temp);
	status = int(temp);
}

void Config::Read(char *setting, char *subsetting, float &status) {
	double temp = status;
	Read(setting, subsetting, temp);
	status = float(temp);
}

void Config::Read(char *setting, char *subsetting, double &status) {
	char *temp = nullptr;
	if (!WritePrivateProfileStringA(setting, subsetting, temp, cfgPath)) {
		LogDebugMsg(WRN, "Failed to write %s, %s to config!", setting, subsetting);
	}
	status = atof(temp);
}

void Config::Read(char *setting, char *subsetting, std::string &status) {
	char *temp = nullptr;
	if (!WritePrivateProfileStringA(setting, subsetting, temp, cfgPath)) {
		LogDebugMsg(WRN, "Failed to write %s, %s to config!", setting, subsetting);
	}
	status = temp;
}

void Config::Write(char *setting, char *subsetting, bool status) {
	int temp = (int)status;
	Write(setting, subsetting, temp);
}

void Config::Write(char *setting, char *subsetting, int status) {
	char *temp = nullptr;
	sprintf_s(temp, 255, "%d", status);
	if (!WritePrivateProfileStringA(setting, subsetting, temp, cfgPath)) {
		LogDebugMsg(WRN, "Failed to write %s, %s to config!", setting, subsetting);
	}
}

void Config::Write(char *setting, char *subsetting, float status) {
	double temp = double(status);
	Write(setting, subsetting, temp);
}

void Config::Write(char *setting, char *subsetting, double status) {
	char *temp = nullptr;
	sprintf_s(temp, 255, "%2f", status);
	if (!WritePrivateProfileStringA(setting, subsetting, temp, cfgPath)) {
		LogDebugMsg(WRN, "Failed to write %s, %s to config!", setting, subsetting);
	}
}

void Config::Write(char *setting, char *subsetting, std::string status) {
	if (!WritePrivateProfileStringA(setting, subsetting, status.c_str(), cfgPath)) {
		LogDebugMsg(WRN, "Failed to write %s, %s to config!", setting, subsetting);
	}
}

Config::Config() {
	sVersion = "1.0";
	uiQuitReason = -1;
	uiExitKey = VK_F4;
	uiReloadKey = VK_F5;
	uiAutoJumpKey = VK_XBUTTON1;
	bAutoJumpState = true;
}

bool Config::LoadConfig() {
	char tempChar[MAX_PATH];
	GetModuleFileName(nullptr, tempChar, MAX_PATH);
	memset(cfgPath, 0, MAX_PATH);
	strcpy_s(cfgPath, std::string(tempChar).substr(NULL, std::string(tempChar).find_last_of("/\\") + 1).c_str());
	strcat_s(cfgPath, "config.txt");
	struct stat buffer;
	if (stat(cfgPath, &buffer)) {
		Write("Info", "Version", sVersion);
		Write("Info", "Quit Reason", uiQuitReason);
		Write("Key Binds", "Terminate", uiExitKey);
		Write("Key Binds", "Reload Config", uiReloadKey);
		Write("Key Binds", "Auto Jump", uiAutoJumpKey);
		Write("Auto Jump", "Enabled", bAutoJumpState);
		return false;
	}
	return true;
}

bool Config::ReadConfig() {
	std::string sConfig;
	Read("Info", "Version", sConfig);
	if (sVersion == sConfig) {
		Read("Key Binds", "Terminate", uiExitKey);
		Read("Key Binds", "Reload Config", uiReloadKey);
		Read("Key Binds", "Auto Jump", uiAutoJumpKey);
		Read("Auto Jump", "Enabled", bAutoJumpState);
	} else {
		// set defaults
		uiExitKey = VK_F4;
		uiReloadKey = VK_F5;
		uiAutoJumpKey = VK_XBUTTON1;
		bAutoJumpState = true;
		return false;
	}
	if (!uiExitKey) {
		uiExitKey = VK_F4;
		return false;
	}
	if (!uiReloadKey) {
		uiReloadKey = VK_F5;
		return false;
	}
	if (!uiAutoJumpKey) {
		uiAutoJumpKey = VK_XBUTTON1;
		return false;
	}
	return true;
}

Config::~Config() {
	Write("Info", "Quit Reason", uiQuitReason);
}
