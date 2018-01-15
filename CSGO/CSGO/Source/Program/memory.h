#pragma once

template< typename xDatatype > struct address_t
{
	std::atomic< DWORD > dwOffset { }; // offset
	std::atomic< DWORD > dwPointer { }; // thisptr
	std::atomic< DWORD > dwLocation { }; // location
	std::atomic< xDatatype > xValue { }; // value
};

namespace Addresses
{
	// global engine addresses
	extern address_t< CGlobalVars > gvGlobalVars;
	extern address_t< bool > bSendPackets;
	// engine pointer addresses
	extern address_t< DWORD > pdwClientState;
	extern address_t< ESignOnState > soSignOnState;
	extern address_t< angle_t > angViewAngle;
	// global client addresses
	extern address_t< float > flSensitivity;
	extern address_t< FLAG > fForceAttack;
	extern address_t< FLAG > fForceJump;
	// client pointer addresses
	extern address_t< DWORD > pdwEntityList;
	extern address_t< CPlayer > plrEntities[64];

	extern address_t< DWORD > pdwLocalPlayer;
	extern address_t< CPlayer > plrLocalPlayer;

	extern address_t< int > iItemDefinitionIndex;
	extern address_t< int > iHighID;
	extern address_t< weapon_t > wepWeaponSkinBase;

	extern address_t< DWORD > pdwGlowManager;
}

using namespace Addresses;

class CMemoryManager
{
	DWORD dwProcessID { };
	HANDLE hGame { };
	DWORD dwClientBase { };
	DWORD dwEngineBase { };
public:
	bool AttachToGame( );

	DWORD FindPattern( BYTE *, char *, DWORD, DWORD );

	void InitializeAddresses( );

	template< typename xDatatype > bool Get( address_t< xDatatype > &xAddress )
	{
		if ( xAddress.dwLocation )
		{
			if ( xAddress.dwPointer )
			{
				DWORD dwXor { };
				bool bSuccess = ReadProcessMemory( hGame, LPVOID( xAddress.dwLocation._My_val ), &dwXor, sizeof( DWORD ), nullptr );
				dwXor ^= xAddress.dwPointer;
				xAddress.xValue = *reinterpret_cast< xDatatype* >( &dwXor );
				return bSuccess;
			}
			xDatatype xRead { };
			bool bSuccess = ReadProcessMemory( hGame, LPVOID( xAddress.dwLocation._My_val ), &xRead, sizeof( xDatatype ), nullptr );
			xAddress.xValue = xRead;
			return bSuccess;
		}
		return false;
	}

	template< typename xDatatype > bool Set( address_t< xDatatype > &xAddress )
	{
		if ( xAddress.dwLocation )
		{
			if ( xAddress.dwPointer )
			{
				DWORD dwXor = *reinterpret_cast< DWORD* >( &xAddress.xValue ) ^ xAddress.dwPointer;
				return WriteProcessMemory( hGame, LPVOID( xAddress.dwLocation._My_val ), &dwXor, sizeof( DWORD ), nullptr );
			}
			xDatatype xWrite = xAddress.xValue;
			return WriteProcessMemory( hGame, LPVOID( xAddress.dwLocation._My_val ), &xWrite, sizeof( xDatatype ), nullptr );
		}
		return false;
	}

	CMemoryManager( ) = default; // constructor
	CMemoryManager( CMemoryManager & ) = default; // copy constructor
	CMemoryManager( CMemoryManager && ) = default; // move constructor
	CMemoryManager &operator=( CMemoryManager const & ) = default; // copy assignment operator
	CMemoryManager &operator=( CMemoryManager && ) = default; // move assignment operator
	~CMemoryManager( ); // deconstructor
};

extern CMemoryManager mem;
