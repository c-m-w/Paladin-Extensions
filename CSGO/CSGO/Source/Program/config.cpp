#include "../dllmain.h"

bool CConfig::LoadConfig( )
{
	char chTemp[MAX_PATH];
	GetModuleFileName( nullptr, chTemp, MAX_PATH );
	memset( cfgPath, 0, MAX_PATH );
	strcpy_s( cfgPath, std::string( chTemp ).substr( 0, std::string( chTemp ).find_last_of( "/\\" ) + 1 ).c_str( ) );
	strcat_s( cfgPath, "config.txt" );
	struct stat buffer{};
	if ( stat( cfgPath, &buffer ) )
	{
		Write( "Key bds", "Terminate", sExitKey );
		Write( "Key bds", "Reload Config", sReloadKey );
		Write( "Key bds", "Auto Jump", sAutoJumpKey );
		Write( "Auto Jump", "Enabled", bAutoJumpState );
		Write( "Hit Sound", "Enabled", bHitSound );
		Write( "Hit Sound", "File Location", strHitSoundLocation );
		Write( "Info", "Version", verVersion );
		Write( "Info", "Quit Reason", iQuitReason );
#ifdef _DEBUG
		Write( "Info", "Log", strLog );
#endif
		return false;
	}
	return true;
}

bool CConfig::ReadConfig( )
{
	version_t verConfig{};
	Read( "Info", "Version", verConfig );
	if ( verVersion == verConfig )
	{
		Read( "Key bds", "Terminate", sExitKey );
		Read( "Key bds", "Reload Config", sReloadKey );
		Read( "Key bds", "Auto Jump", sAutoJumpKey );
		Read( "Auto Jump", "Enabled", bAutoJumpState );
		Read( "Hit Sound", "Enabled", bHitSound );
		Read( "Hit Sound", "File Location", strHitSoundLocation );
	}
	else
	{
		// set defaults
		sExitKey = VK_F4;
		sReloadKey = VK_F5;
		sAutoJumpKey = VK_XBUTTON1;
		bAutoJumpState = true;
		bHitSound = true;
		return false;
	}
	Limit( sExitKey, VK_F4, INT_MAX );
	Limit( sReloadKey, VK_F5, INT_MAX );
	Limit( sAutoJumpKey, VK_XBUTTON1, INT_MAX );
	return true;
}

CConfig::CConfig( )
{
	verVersion = { 1, 0 };
	iQuitReason = EQuitReasons::UNKNOWN;
	sExitKey = VK_F4;
	sReloadKey = VK_F5;
	sAutoJumpKey = VK_XBUTTON1;
	bAutoJumpState = true;
	bHitSound = true;
}

CConfig::~CConfig( )
{
	Write( "Info", "Quit Reason", iQuitReason );
#ifdef _DEBUG
	Write( "Info", "Log", strLog );
#endif
}

CConfig cfg;
