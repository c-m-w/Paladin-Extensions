#pragma once

template<typename datatype> struct Address {
	DWORD off = 0; // offset
	DWORD ptr = 0; // thisptr
	DWORD loc = 0; // location
	datatype val; // value
};

namespace Addresses {
	// global CEngine addresses
	// CEngine pointer addresses
	extern Address<GlobalVars> dwGlobalVars;
	extern Address<DWORD> dwClientState;
	extern Address<ESignOnState> cs_soSignOnState;
	extern Address<angle> cs_aViewAngle;
	// global Client addresses
	extern Address<float> flSensitivity;
	extern Address<frame> fForceAttack;
	extern Address<frame> fForceJump;
	// Client pointer addresses
	extern Address<DWORD> dwEntityList;
	extern Address<ETeam> el_tTeamNum;
	extern Address<bool> el_bSpotted;

	extern Address<DWORD> dwLocalPlayer;

	extern Address<ETeam> lp_tTeamNum;
	extern Address<frame> lp_fFlags;
	extern Address<EMoveType> lp_mMoveType;
	extern Address<angle> lp_aAimPunch;
	extern Address<int> lp_iFOV;
	extern Address<total> lp_totalHitsOnServer;
	extern Address<float> lp_flFlashMaxAlpha;

	extern Address<handle> lp_hActiveWeapon;
	extern Address<float> aw_flNextPrimaryAttack;
}

using namespace Addresses;

class CMemoryManager {
	DWORD dwProcessID = 0;
	HANDLE hGame = nullptr;
	DWORD dwClientBase = 0;
	DWORD dwEngineBase = 0;

public:
	bool AttachToGame();

	DWORD FindPattern(BYTE * mask, char * szMask, const DWORD address, const DWORD length);

	void InitializeAddresses();

	template<class datatype> bool Get(Address<datatype> &adrRead) {
		if (adrRead.loc) {
			if (adrRead.ptr) {
				DWORD dwXor;
				bool bSuccess = ReadProcessMemory(hGame, LPVOID(adrRead.loc), &dwXor, sizeof(DWORD), nullptr);
				adrRead.val = *reinterpret_cast<datatype*>(dwXor ^ adrRead.ptr);
				return bSuccess;
			}
			return ReadProcessMemory(hGame, LPVOID(adrRead.loc), &adrRead.val, sizeof(datatype), nullptr);
		}
		return false;
	}

	template<class datatype> bool Set(Address<datatype> &adrWrite) {
		if (adrWrite.loc) {
			if (adrWrite.ptr) {
				DWORD dwXor = *reinterpret_cast<DWORD*>(&adrWrite.val) ^ adrWrite.ptr;
				return WriteProcessMemory(hGame, LPVOID(adrWrite.loc), &dwXor, sizeof(DWORD), nullptr);
			}
			return WriteProcessMemory(hGame, LPVOID(adrWrite.loc), &adrWrite.val, sizeof(datatype), nullptr);
		}
		return false;
	}

	~CMemoryManager();
};

extern CMemoryManager mem;
