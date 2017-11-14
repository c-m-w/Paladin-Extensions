#include "../main.h"

bool Config::Version::operator==(const Version &rvalue) const {
	if (major == rvalue.major && minor == rvalue.minor) {
		return true;
	}
	return false;
}

Config::Config() {
	uiExitKey = VK_F4;
	uiReloadKey = VK_F5;
}

template<class datatype> void Config::Read(char *setting, char *subsetting, datatype &status) {
	char temp[255];
	if (!GetPrivateProfileStringA(setting, subsetting, nullptr, temp, 255, cfgPath)) {
		LogDebugMsg(WRN, "Failed to read %s, %s from config!", setting, subsetting);
	}
	if (typeid(datatype) == typeid(Version)) {
		sprintf_s(status, "%f", temp);
		return;
	}
	status = datatype(atof(temp));
}

template<class datatype> void Config::Write(char *setting, char *subsetting, datatype status) {
	char temp[255];
	if (typeid(datatype) == typeid(bool) || typeid(datatype) == typeid(int)) {
		sprintf_s(temp, "%i", status);
	} else if (typeid(datatype) == typeid(float) || typeid(datatype) == typeid(double)) {
		sprintf_s(temp, "%2f", status);
	} else if (typeid(datatype) == typeid(Version)) {
		Version x = { status };
		sprintf_s(temp, "%i.%i", x.major, x.minor);
	} else {
		LogDebugMsg(WRN, "Failed to write %s, %s to config! Unexpected datatype!", setting, subsetting);
		return;
	}
	WritePrivateProfileStringA(setting, subsetting, temp, cfgPath);
}

bool Config::LoadConfig() {
	char tempChar[MAX_PATH];
	GetModuleFileName(nullptr, tempChar, MAX_PATH);
	memset(cfgPath, 0, 255);
	strcpy_s(cfgPath, std::string(tempChar).substr(NULL, std::string(tempChar).find_last_of("/\\") + 1).c_str());
	strcat_s(cfgPath, "config.txt");
	struct stat buffer;
	if (stat(cfgPath, &buffer)) {
		Write<Version>("Info", "Version", vVersion);
		Write<int>("Key Binds", "Terminate", uiExitKey);
		Write<int>("Key Binds", "Reload Config", uiReloadKey);
		return false;
	}
	return true;
}

bool Config::ReadConfig() {
	// if config version doesnt match cheat version, say error
	Version vConfig;
	Read<Version>("Info", "Version", vConfig);
	if (vVersion == vConfig) {
		Read<int>("Key Binds", "Terminate", uiExitKey);
		Read<int>("Key Binds", "Reload Config", uiReloadKey);
	} else {
		// set defaults
		uiExitKey = VK_F4;
		uiReloadKey = VK_F5;
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
	return true;
}

Config::~Config() {
	Write<int>("Info", "Quit Reason", uiQuitReason);
}
