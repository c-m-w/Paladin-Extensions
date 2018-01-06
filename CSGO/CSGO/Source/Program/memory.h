#pragma once

template< typename xDatatype > struct address_t
{
	DWORD dwOffset = 0; // offset
	DWORD dwPointer = 0; // thisptr
	DWORD dwLocation = 0; // location
	xDatatype xValue { }; // value
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
	extern std::atomic< address_t< CPlayer > > plrEntities[250];

	extern address_t< DWORD > pdwLocalPlayer;
	extern std::atomic< address_t< CPlayer > > plrLocalPlayer;

	extern address_t< DWORD > pdwGlowManager;
}

using namespace Addresses;

class CMemoryManager
{
public:
	DWORD dwProcessID = 0;
	HANDLE hGame = nullptr;
	DWORD dwClientBase = 0;
	DWORD dwEngineBase = 0;

	bool AttachToGame( );

	DWORD FindPattern( BYTE *, char *, DWORD, DWORD );

	void InitializeAddresses( );

	template< typename xDatatype > bool Get( address_t< xDatatype > &xRead )
	{
		if ( xRead.dwLocation )
		{
			if ( xRead.dwPointer )
			{
				DWORD dwXor;
				bool bSuccess = ReadProcessMemory( hGame, LPVOID( xRead.dwLocation ), &dwXor, sizeof(DWORD), nullptr );
				dwXor ^= xRead.dwPointer;
				xRead.xValue = *reinterpret_cast< xDatatype* >( &dwXor );
				return bSuccess;
			}
			return ReadProcessMemory( hGame, LPVOID( xRead.dwLocation ), &xRead.xValue, sizeof(xDatatype), nullptr );
		}
		return false;
	}

	template< typename xDatatype > bool Set( address_t< xDatatype > &xWrite )
	{
		if ( xWrite.dwLocation )
		{
			if ( xWrite.dwPointer )
			{
				DWORD dwXor = *reinterpret_cast< DWORD* >( &xWrite.xValue ) ^ xWrite.dwPointer;
				return WriteProcessMemory( hGame, LPVOID( xWrite.dwLocation ), &dwXor, sizeof(DWORD), nullptr );
			}
			return WriteProcessMemory( hGame, LPVOID( xWrite.dwLocation ), &xWrite.xValue, sizeof(xDatatype), nullptr );
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
