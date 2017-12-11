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
	extern Address<CGlobalVars> dwGlobalVars;
	extern Address<DWORD> dwClientState;
	extern Address<ESignOnState> cs_soState;
	// global Client addresses
	extern Address<EKeystroke> ksForceJump;
	extern Address<EKeystroke> ksForceAttack;
	extern Address<float> flSensitivity;
	// Client pointer addresses
	extern Address<DWORD> dwEntityList;
	extern Address<DWORD> dwLocalPlayer;

	extern Address<frame> lp_fFlags;
	extern Address<total> lp_totalHitsOnServer;
	extern Address<float> lp_flFlashMaxAlpha;
	extern Address<int> lp_iFOV;

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

	bool PatternCompare(); // todo
	DWORD FindPattern(); // todo

	void InitializeAddresses();

	template<class datatype> bool Read(Address<datatype> &adrRead) {
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

	template<class datatype> bool Write(Address<datatype> &adrWrite) {
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
