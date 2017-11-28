#include "config.h"

Config cfg;

Config::Config() {
	strVersion = {1, 0};
	iQuitReason = -1;
	iExitKey = VK_F4;
	iReloadKey = VK_F5;
	iAutoJumpKey = VK_XBUTTON1;
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
		Write("Info", "Version", strVersion);
		Write("Info", "Quit Reason", iQuitReason);
		Write("Key Binds", "Terminate", iExitKey);
		Write("Key Binds", "Reload Config", iReloadKey);
		Write("Key Binds", "Auto Jump", iAutoJumpKey);
		Write("Auto Jump", "Enabled", bAutoJumpState);
		return false;
	}
	return true;
}

bool Config::ReadConfig() {
	version sConfig;
	Read("Info", "Version", sConfig);
	if (strVersion == sConfig) {
		Read("Key Binds", "Terminate", iExitKey);
		Read("Key Binds", "Reload Config", iReloadKey);
		Read("Key Binds", "Auto Jump", iAutoJumpKey);
		Read("Auto Jump", "Enabled", bAutoJumpState);
	} else {
		// set defaults
		iExitKey = VK_F4;
		iReloadKey = VK_F5;
		iAutoJumpKey = VK_XBUTTON1;
		bAutoJumpState = true;
		return false;
	}
	Limit(iExitKey, VK_F4, MAXINT);
	Limit(iReloadKey, VK_F5, MAXINT);
	Limit(iAutoJumpKey, VK_XBUTTON1, MAXINT);
	return true;
}

Config::~Config() {
	Write("Info", "Quit Reason", iQuitReason);
}
