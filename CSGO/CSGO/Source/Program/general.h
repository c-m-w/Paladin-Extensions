#pragma once

class CGeneral
{
	struct user_t
	{
		LPSTR lpstrUsername = nullptr;
		int iHardwareID = 0;
		moment tExpiration = 0;
		bool bValid = false;
		bool bBanned = false;
	};

	user_t uPremiumUsers[PREMIUM_USERS];
	void GetPremiumUsers( );
	bool CompareName( user_t, user_t );
public:
	EPremium CheckPremiumStatus( );
private:
	EElevation eElevationState = EElevation::UNTESTED;
public:
	EElevation GetElevationState( );
	EElevation GetElevationState( HANDLE );
	EAnticheatStatus KillAnticheat( LPCSTR, char );
	float GetWindowsSensitivity( );
};

extern CGeneral all;
