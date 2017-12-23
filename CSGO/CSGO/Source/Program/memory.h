#pragma once

template< typename xDatatype > struct address_t
{
	DWORD off = 0; // offset
	DWORD ptr = 0; // thisptr
	DWORD loc = 0; // location
	xDatatype val { }; // value
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
	extern address_t< std::vector< CPlayer > > plrEntities;

	extern address_t< DWORD > pdwLocalPlayer;
	extern address_t< CPlayer > plrLocalPlayer;
	
	extern address_t< DWORD > pdwGlowManager;
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

	template< typename xDatatype > bool Get( address_t< xDatatype > &adrRead )
	{
		if ( adrRead.loc )
		{
			if ( adrRead.ptr )
			{
				DWORD dwXor;
				bool bSuccess = ReadProcessMemory( hGame, LPVOID( adrRead.loc ), &dwXor, sizeof(DWORD), nullptr );
				dwXor ^= adrRead.ptr;
				adrRead.val = *reinterpret_cast< xDatatype* >( &dwXor );
				return bSuccess;
			}
			return ReadProcessMemory( hGame, LPVOID( adrRead.loc ), &adrRead.val, sizeof(xDatatype), nullptr );
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

	CMemoryManager( ) = default; // constructor
	CMemoryManager( CMemoryManager & ) = default; // copy constructor
	CMemoryManager( CMemoryManager && ) = default; // move constructor
	CMemoryManager &operator=( CMemoryManager const & ) = default; // copy assignment operator
	CMemoryManager &operator=( CMemoryManager && ) = default; // move assignment operator
	~CMemoryManager( ); // deconstructor
};

extern CMemoryManager mem;
