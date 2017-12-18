#pragma once

template< typename datatype > struct address_t
{
	DWORD off = 0; // offset
	DWORD ptr = 0; // thisptr
	DWORD loc = 0; // location
	datatype val; // value
};

namespace Addresses
{
	// global CEngine addresses
	// CEngine pointer addresses
	extern address_t< CGlobalVars > gvGlobalVars;
	extern address_t< DWORD > pdwClientState;
	extern address_t< ESignOnState > cs_soSignOnState;
	extern address_t< angle_t > cs_aViewAngle;
	// global Client addresses
	extern address_t< float > flSensitivity;
	extern address_t< flag > fForceAttack;
	extern address_t< flag > fForceJump;
	// Client pointer addresses
	extern address_t< DWORD > pdwEntityList;
	extern address_t< DWORD > el_dwGlowManager;
	extern address_t< bool > el_bDormant;
	extern address_t< ETeam > el_tTeamNum;
	extern address_t< bool > el_bSpottedState;

	extern address_t< DWORD > pdwLocalPlayer;

	extern address_t< ETeam > lp_tTeamNum;
	extern address_t< flag > lp_fFlags;
	extern address_t< EMoveType > lp_mMoveType;
	extern address_t< angle_t > lp_aAimPunch;
	extern address_t< int > lp_iFOV;
	extern address_t< int > lp_iShotsFired;
	extern address_t< total > lp_totalHitsOnServer;
	extern address_t< float > lp_flFlashMaxAlpha;

	extern address_t< handle > lp_hActiveWeapon;
	extern address_t< int > aw_iZoomLevel;
	extern address_t< float > aw_flNextPrimaryAttack;
	extern address_t< EWeapon > aw_wpnPlayerWeaponIndex;
}

using namespace Addresses;

class CMemoryManager
{
	DWORD dwProcessID = 0;
	HANDLE hGame = nullptr;
	DWORD dwClientBase = 0;
	DWORD dwEngineBase = 0;

public:
	bool AttachToGame( );

	DWORD FindPattern( BYTE *, char *, DWORD, DWORD );

	void InitializeAddresses( );

	template< typename datatype > bool Get( address_t< datatype > &adrRead )
	{
		if ( adrRead.loc )
		{
			if ( adrRead.ptr )
			{
				DWORD dwXor;
				bool bSuccess = ReadProcessMemory( hGame, LPVOID( adrRead.loc ), &dwXor, sizeof(DWORD), nullptr );
				dwXor ^= adrRead.ptr;
				adrRead.val = *reinterpret_cast< datatype* >( &dwXor );
				return bSuccess;
			}
			return ReadProcessMemory( hGame, LPVOID( adrRead.loc ), &adrRead.val, sizeof(datatype), nullptr );
		}
		return false;
	}

	template< typename datatype > bool Set( address_t< datatype > &adrWrite )
	{
		if ( adrWrite.loc )
		{
			if ( adrWrite.ptr )
			{
				DWORD dwXor = *reinterpret_cast< DWORD* >( &adrWrite.val ) ^ adrWrite.ptr;
				return WriteProcessMemory( hGame, LPVOID( adrWrite.loc ), &dwXor, sizeof(DWORD), nullptr );
			}
			return WriteProcessMemory( hGame, LPVOID( adrWrite.loc ), &adrWrite.val, sizeof(datatype), nullptr );
		}
		return false;
	}

	~CMemoryManager( );
};

extern CMemoryManager mem;
