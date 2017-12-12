#pragma once

struct version_t
{
	uint8 upper, lower;

	bool operator==( const version_t &rhs )
	{
		if ( upper == rhs.upper && lower == rhs.lower )
		{
			return true;
		}
		return false;
	}
};

class CConfig
{
	char cfgPath[255];
	// read from config TODO
	template< typename datatype > void Read( char *szSetting, char *szSubSetting, datatype &xStatus )
	{ }

	// write to config TODO
	template< typename datatype > void Write( char *szSetting, char *szSubSetting, datatype xStatus )
	{ }

public:
	version_t verVersion;
	EQuitReasons iQuitReason;

#ifdef _DEBUG
	bool bCheckForAnticheat = false;
#else
	bool bCheckForAnticheat = true;
#endif

	// Keys TODO rest of features
	int iExitKey;
	int iReloadKey;
	int iAutoJumpKey;

	// Feature Toggles
	bool bHitSound;
	bool bAutoJumpState;

	// Feature Settings
	std::string strHitSoundLocation;

	CConfig( );
	// open config, create if doesn't exist
	bool LoadConfig( );
	// read loaded config, replace impossible values
	bool ReadConfig( );
	// set quit reason
	~CConfig( );
};

extern CConfig cfg;
