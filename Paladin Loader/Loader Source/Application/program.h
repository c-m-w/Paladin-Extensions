#pragma once

class CProgram
{
	struct user_t
	{
		int iUserID { };
		std::string strSecretKey { };
		std::string strWindowsName { };
		int iHardwareID { };
	};
	user_t uCurrentUser { };
	void GetUserInfo( );
	void DeleteUserInfo( );
public:
	EPremium GetPremium( );

	EElevation GetElevationState( HANDLE );
	EAnticheatStatus KillAnticheat( LPCSTR, char * );

	const char *GetFileHash( char * );
	
	float GetWindowsSensitivity( );
};

extern CProgram pro;
