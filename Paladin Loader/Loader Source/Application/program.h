#pragma once

class CProgram
{
	struct user_t
	{
		int iUserID { };
		std::wstring wstrSecretKey { };
		std::wstring wstrWindowsName { };
		int iHardwareID { };
	};
	user_t uCurrentUser { };
	void GetUserInfo( );
	void DeleteUserInfo( );
public:
	EPremium GetPremium( );

	EElevation GetElevationState( HANDLE );
	EAnticheatStatus KillAnticheat( LPCWSTR, const wchar_t * );
	
	float GetWindowsSensitivity( );
};

extern CProgram pro;
