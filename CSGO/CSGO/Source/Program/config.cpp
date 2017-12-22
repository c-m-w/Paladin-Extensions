#include "../dllmain.h"

CConfig::CConfig( )
{
	verVersion = { 1, 0 };
	iQuitReason = EQuitReasons::UNKNOWN;
	iExitKey = VK_F4;
	iReloadKey = VK_F5;
	iAutoJumpKey = VK_XBUTTON1;
	bAutoJumpState = true;
	bHitSound = true;
	strHitSoundLocation = "\0";
}

bool CConfig::LoadConfig( )
{
	char chTemp[MAX_PATH];
	GetModuleFileName( nullptr, chTemp, MAX_PATH );
	memset( cfgPath, 0, MAX_PATH );
	strcpy_s( cfgPath, std::string( chTemp ).substr( 0, std::string( chTemp ).find_last_of( "/\\" ) + 1 ).c_str( ) );
	strcat_s( cfgPath, "config.txt" );
	struct stat buffer;
	if ( stat( cfgPath, &buffer ) )
	{
		Write( "Key bds", "Terminate", iExitKey );
		Write( "Key bds", "Reload Config", iReloadKey );
		Write( "Key bds", "Auto Jump", iAutoJumpKey );
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
	version_t verConfig;
	Read( "Info", "Version", verConfig );
	if ( verVersion == verConfig )
	{
		Read( "Key bds", "Terminate", iExitKey );
		Read( "Key bds", "Reload Config", iReloadKey );
		Read( "Key bds", "Auto Jump", iAutoJumpKey );
		Read( "Auto Jump", "Enabled", bAutoJumpState );
		Read( "Hit Sound", "Enabled", bHitSound );
		Read( "Hit Sound", "File Location", strHitSoundLocation );
	}
	else
	{
		// set defaults
		iExitKey = VK_F4;
		iReloadKey = VK_F5;
		iAutoJumpKey = VK_XBUTTON1;
		bAutoJumpState = true;
		bHitSound = true;
		strHitSoundLocation = "\0";
		return false;
	}
	Limit( iExitKey, VK_F4, MAXINT );
	Limit( iReloadKey, VK_F5, MAXINT );
	Limit( iAutoJumpKey, VK_XBUTTON1, MAXINT );
	return true;
}

CConfig::~CConfig( )
{
	Write( "Info", "Quit Reason", iQuitReason );
#ifdef _DEBUG
	Write( "Info", "Log", strLog );
#endif
}

CConfig cfg;
