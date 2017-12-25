#pragma once

struct version_t
{
	unsigned __int8 unUpper, unLower;

	bool operator==( version_t rhs )
	{
		return unUpper == rhs.unUpper && unLower == rhs.unLower;
	}
};

class CConfig
{
	char cfgPath[MAX_PATH] { };
	// read from config TODO
	template< typename xDatatype > void Read( char *szSetting, char *szSubSetting, xDatatype &xStatus )
	{ }

	// write to config TODO
	template< typename xDatatype > void Write( char *szSetting, char *szSubSetting, xDatatype xStatus )
	{ }

public:
	version_t verVersion { };
	EQuitReasons iQuitReason { };

#ifdef _DEBUG
	bool bCheckForAnticheat = false;
#else
	bool bCheckForAnticheat = true;
#endif

	// Keys TODO rest of features
	short sExitKey { };
	short sReloadKey { };
	short sAutoJumpKey { };

	// F{}eature Toggles
	bool bHitSound { };
	bool bAutoJumpState { };

	// F{}eature Settings
	std::string strHitSoundLocation;

	// open config, create if doesn't exist
	bool LoadConfig( );
	// read loaded config, replace impossible values
	bool ReadConfig( );

	CConfig( ); // constructor
	CConfig( CConfig & ) = default; // copy constructor
	CConfig( CConfig && ) = default; // move constructor
	CConfig &operator=( CConfig const & ) = default; // copy assignment operator
	CConfig &operator=( CConfig && ) = default; // move assignment operator
	~CConfig( ); // deconstructor
};

extern CConfig cfg;
