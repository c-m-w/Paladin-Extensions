#pragma once

struct version_t
{
	unsigned __int8 upper, lower;

	bool operator==( version_t rhs )
	{
		return upper == rhs.upper && lower == rhs.lower;
	}
};

class CConfig
{
	char cfgPath[255]{};
	// read from config TODO
	template< typename datatype > void Read( char *szSetting, char *szSubSetting, datatype &xStatus )
	{ }

	// write to config TODO
	template< typename datatype > void Write( char *szSetting, char *szSubSetting, datatype xStatus )
	{ }

public:
	version_t verVersion{};
	EQuitReasons iQuitReason{};

#ifdef _DEBUG
	bool bCheckForAnticheat = false;
#else
	bool bCheckForAnticheat = true;
#endif

	// Keys TODO rest of features
	short sExitKey{};
	short sReloadKey{ };
	short sAutoJumpKey{ };

	// F{}eature Toggles
	bool bHitSound{};
	bool bAutoJumpState{ };

	// F{}eature Settings
	std::string strHitSoundLocation;

	// open config, create if doesn't exist
	bool LoadConfig( );
	// read loaded config, replace impossible values
	bool ReadConfig( );

	CConfig( ); // constructor
	CConfig( CConfig& ) = default; // copy constructor
	CConfig( CConfig&& ) = default; // move constructor
	CConfig & operator=( CConfig const& ) = default; // copy assignment operator
	CConfig & operator=( CConfig&& ) = default; // move assignment operator
	~CConfig( ); // deconstructor
};

extern CConfig cfg;
