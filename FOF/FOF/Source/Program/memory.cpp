#include "../dllmain.h"

namespace Addresses
{
	// global engine addresses
	address_t< CGlobalVars > gvGlobalVars;
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
	address_t< std::vector< CPlayer> > plrEntities;
	address_t< DWORD > pdwLocalPlayer;
	address_t< CPlayer > plrLocalPlayer;
	address_t< DWORD > pdwGlowManager;
}

CMemoryManager::~CMemoryManager( )
{
	if ( hGame || hGame != INVALID_HANDLE_VALUE )
	{
		CloseHandle( hGame );
	}
}

bool CMemoryManager::AttachToGame( )
{
	while ( !GetWindowThreadProcessId( FindWindowA( nullptr, "Counter-Strike: Global Offensive" ), &dwProcessID ) )
	{
		LogDebugMsg( DBG, "Searching for CSGO" );
		Wait( 1000 );
	}
	if ( all.GetElevationState( ) != all.GetElevationState( hGame ) && all.GetElevationState( ) != EElevation::ADMIN )
	{
		LogDebugMsg( ERR, "No permissions" );
		return false;
	}
	hGame = OpenProcess( PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, dwProcessID );
	if ( !hGame || hGame == INVALID_HANDLE_VALUE )
	{
		LogDebugMsg( ERR, "Invalid game handle" );
		return false;
	}
	LogDebugMsg( SCS, "Attached to game" );
	HANDLE hSnapshot;
	for ( unsigned short us= 0; us < 5; us++, Wait( 2000 ) )
	{
		do
		{
			SetLastError( 0 );
			hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessID );
			Wait( 1 );
		} while ( hSnapshot == INVALID_HANDLE_VALUE || GetLastError( ) == ERROR_BAD_LENGTH );
		if ( hSnapshot == INVALID_HANDLE_VALUE || !hSnapshot )
		{
			LogDebugMsg( ERR, "Invalid module snapshot" );
			return false;
		}
		LogDebugMsg( SCS, "Module snapshot created" );
		MODULEENTRY32 me = { };
		me.dwSize = sizeof(MODULEENTRY32);
		if ( Module32First( hSnapshot, &me ) )
		{
			do
			{
				if ( !_stricmp( me.szModule, "client.dll" ) )
				{
					dwClientBase = DWORD( me.modBaseAddr );
				}
				else if ( !_stricmp( me.szModule, "engine.dll" ) )
				{
					dwEngineBase = DWORD( me.modBaseAddr );
				}
			} while ( Module32Next( hSnapshot, &me ) );
			CloseHandle( hSnapshot );
		}
		if ( dwClientBase && dwEngineBase )
		{
			LogDebugMsg( SCS, "Modules found" );
			LogDebugMsg( SCS, "Client.dll: 0x%p", dwClientBase );
			LogDebugMsg( SCS, "Engine.dll: 0x%p", dwEngineBase );
			return true;
		}
		LogDebugMsg( DBG, "Modules not found, retrying" );
		LogDebugMsg( DBG, "Client.dll: 0x%p", dwClientBase );
		LogDebugMsg( DBG, "Engine.dll: 0x%p", dwEngineBase );
	}
	LogDebugMsg( ERR, "Unable to get modules" );
	return false;
}

DWORD CMemoryManager::FindPattern( BYTE *bMask, char *szMask, DWORD dwAddress, DWORD dwLength )
{
	DWORD dwDataLength = strlen( szMask );
	BYTE *bData = new BYTE[dwDataLength + 1];
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
	LogDebugMsg( DBG, "Initializing addresses" );

	// global Engine addresses
	gvGlobalVars = { 0x57B4F0 };
	// Engine pointer addresses
	pdwClientState = { 0x57B7EC };
	soSignOnState = { 0x108 };
	angViewAngle = { 0x4D10 };
	// global Client addresses
	flSensitivity = { 0xAA14DC, 0xAA14B0 };
	fForceAttack = { 0x2EBAF64 };
	fForceJump = { 0x4F0FE0C };
	// Client pointer addresses
	pdwEntityList = { 0x4A78BA4 };
	pdwGlowManager = { 0x4F959F0 };
	pdwLocalPlayer = { 0xA9BDDC };
	LogDebugMsg( SCS, "Initialized bases" );

	// engine
	gvGlobalVars.loc = dwEngineBase + gvGlobalVars.off;
	pdwClientState.loc = dwEngineBase + pdwClientState.off;
	// client
	fForceJump.loc = dwClientBase + fForceJump.off;
	fForceAttack.loc = dwClientBase + fForceAttack.off;
	flSensitivity.loc = dwClientBase + flSensitivity.off;
	flSensitivity.ptr += dwClientBase;
	pdwEntityList.loc = dwClientBase + pdwEntityList.off;
	pdwLocalPlayer.loc = dwClientBase + pdwLocalPlayer.off;
	LogDebugMsg( SCS, "Initialized locations" );

	LogDebugMsg( SCS, "Initialized addresses" );
}

CMemoryManager mem;
