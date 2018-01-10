#include "../dllmain.h"

namespace Addresses
{
	// global engine addresses
	address_t< CGlobalVars > gvGlobalVars;
	address_t< bool > bSendPackets;
	// engine pointer addresses
	address_t< DWORD > pdwClientState;
	address_t< ESignOnState > soSignOnState;
	address_t< angle_t > angViewAngle;
	// global client addresses
	address_t< float > flSensitivity;
	address_t< FLAG > fForceAttack;
	address_t< FLAG > fForceJump;
	// client pointer addresses
	address_t< DWORD > pdwEntityList;
	address_t< CPlayer > plrEntities[64];

	address_t< DWORD > pdwLocalPlayer;
	address_t< CPlayer > plrLocalPlayer;

	address_t< DWORD > pdwGlowManager;
}

CMemoryManager::~CMemoryManager( )
{
	if ( hGame != nullptr && hGame != INVALID_HANDLE_VALUE )
	{
		CloseHandle( hGame );
	}
}

bool CMemoryManager::AttachToGame( )
{
	while ( !GetWindowThreadProcessId( FindWindow( nullptr, "Counter-Strike: Global Offensive" ), &dwProcessID ) )
	{
		DEBUG( DBG, "Searching for CSGO" );
		Wait( 1000 );
	}
	if ( all.GetElevationState( ) != all.GetElevationState( hGame ) && all.GetElevationState( ) != EElevation::ADMIN )
	{
		DEBUG( ERR, "No permissions" );
		return false;
	}
	hGame = OpenProcess( PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, dwProcessID );
	if ( !hGame || hGame == INVALID_HANDLE_VALUE )
	{
		DEBUG( ERR, "Invalid game handle" );
		return false;
	}
	DEBUG( SCS, "Attached to game" );
	HANDLE hSnapshot;
	for ( unsigned short us = 0; us < 5; us++, Wait( 2000 ) )
	{
		do
		{
			SetLastError( 0 );
			hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessID );
			Wait( 1 );
		} while ( hSnapshot == INVALID_HANDLE_VALUE || GetLastError( ) == ERROR_BAD_LENGTH );
		if ( hSnapshot == INVALID_HANDLE_VALUE || !hSnapshot )
		{
			DEBUG( ERR, "Invalid module snapshot" );
			return false;
		}
		DEBUG( SCS, "Module snapshot created" );
		MODULEENTRY32 meModules { };
		meModules.dwSize = sizeof(MODULEENTRY32);
		if ( Module32First( hSnapshot, &meModules ) )
		{
			do
			{
				//DEBUG(SCS, "%s", meModules.szModule);
				if ( !_stricmp( meModules.szModule, "client.dll" ) )
				{
					dwClientBase = DWORD( meModules.modBaseAddr );
				}
				else if ( !_stricmp( meModules.szModule, "engine.dll" ) )
				{
					dwEngineBase = DWORD( meModules.modBaseAddr );
				}
			} while ( Module32Next( hSnapshot, &meModules ) );
			CloseHandle( hSnapshot );
		}
		if ( dwClientBase && dwEngineBase )
		{
			DEBUG( SCS, "Modules found" );
			DEBUG( SCS, "Client.dll: 0x%p", dwClientBase );
			DEBUG( SCS, "Engine.dll: 0x%p", dwEngineBase );
			return true;
		}
		DEBUG( DBG, "Modules not found, retrying" );
		DEBUG( DBG, "Client.dll: 0x%p", dwClientBase );
		DEBUG( DBG, "Engine.dll: 0x%p", dwEngineBase );
	}
	DEBUG( ERR, "Unable to get modules" );
	return false;
}

DWORD CMemoryManager::FindPattern( BYTE *bMask, char *szMask, DWORD dwAddress, DWORD dwLength )
{
	DWORD dwDataLength = strlen( szMask );
	auto *bData = new BYTE[dwDataLength + 1];
	SIZE_T sRead;
	for ( DWORD dwAdditive = 0; dwAdditive < dwLength; dwAdditive++ )
	{
		auto dwCurrentAddress = dwAddress + dwAdditive;
		bool bSuccess = ReadProcessMemory( hGame, LPVOID( dwCurrentAddress ), bData, dwDataLength, &sRead );
		if ( !bSuccess || !sRead )
		{
			continue;
		}
		while ( *szMask )
		{
			++szMask;
			++bData;
			++bMask;
			if ( *szMask == 'x' && *bData != *bMask )
			{
				break;
			}
			delete[] bData;
			return dwAddress + dwAdditive;
		}
	}
	delete[] bData;
	return 0;
}

void CMemoryManager::InitializeAddresses( )
{
	DEBUG( DBG, "Initializing addresses" );

	// todo signature scanning
	// global Engine addresses
	gvGlobalVars.dwOffset = 0x57B4F0;
	bSendPackets.dwOffset = 0xCCD9A;
	// Engine pointer addresses
	pdwClientState.dwOffset = 0x57B7EC;
	soSignOnState.dwOffset = 0x108;
	angViewAngle.dwOffset = 0x4D10;
	// global Client addresses
	flSensitivity.dwOffset = 0xAA17DC;
	flSensitivity.dwPointer = 0xAA17B0;
	fForceAttack.dwOffset = 0x2EBB25C;
	fForceJump.dwOffset = 0x4F10154;
	// Client pointer addresses
	pdwEntityList.dwOffset = 0x4A78EE4;
	pdwGlowManager.dwOffset = 0x4F95D48;
	pdwLocalPlayer.dwOffset = 0xA9C0DC;
	DEBUG( DBG, "Initialized bases" );

	// engine global
	gvGlobalVars.dwLocation = dwEngineBase + gvGlobalVars.dwOffset;
	bSendPackets.dwLocation = dwEngineBase + bSendPackets.dwOffset;
	// engine pointers
	pdwClientState.dwLocation = dwEngineBase + pdwClientState.dwOffset;
	// client global
	fForceJump.dwLocation = dwClientBase + fForceJump.dwOffset;
	fForceAttack.dwLocation = dwClientBase + fForceAttack.dwOffset;
	flSensitivity.dwLocation = dwClientBase + flSensitivity.dwOffset;
	flSensitivity.dwPointer += dwClientBase;
	// client pointers
	pdwEntityList.dwLocation = dwClientBase + pdwEntityList.dwOffset;
	pdwLocalPlayer.dwLocation = dwClientBase + pdwLocalPlayer.dwOffset;
	pdwGlowManager.dwLocation = dwClientBase + pdwGlowManager.dwOffset;
	DEBUG( DBG, "Initialized locations" );

	DEBUG( SCS, "Initialized addresses" );
}

CMemoryManager mem;
