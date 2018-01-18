#pragma once

#define PREMIUM_USERS unsigned __int8( 55 )
#define DECEMBER_FIRST moment( 1512086400000 )
#define DAY moment( 86400000 )

class CProgram
{
	struct user_t
	{
		LPSTR lpstrUsername { };
		int iHardwareID { };
		moment tExpiration { };
		bool bValid { };
		bool bBanned { };
	};

	user_t uPremiumUsers[ PREMIUM_USERS ] { };
	void GetPremiumUsers( );
	bool CompareName( user_t, user_t );
public:
	EPremium CheckPremiumStatus( );

	EElevation GetElevationState( HANDLE );
	EAnticheatStatus KillAnticheat( LPCSTR, char );

	float GetWindowsSensitivity( );
};

extern CProgram pro;
