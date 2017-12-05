#pragma once

template<typename datatype> struct Address {
	DWORD loc = NULL; // location
	DWORD ptr = NULL; // this ptr
	datatype val = datatype(NULL); // value
};

namespace Addresses {
	// global CEngine addresses
	// CEngine pointer addresses
	extern Address<DWORD> dwClientState;
	extern Address<ESignOnState> cs_soState;
	// global Client addresses
	extern Address<EKeystroke> ksForceJump;
	extern Address<EKeystroke> ksForceAttack;
	extern Address<float> flSensitivity;
	// Client pointer addresses
	extern Address<DWORD> dwLocalPlayer;
	extern Address<frame> lp_fFlags;
	extern Address<total> lp_totalHitsOnServer;
}

using namespace Addresses;

class CMemoryManager {
	DWORD dwProcessId = NULL;
	HANDLE hGame = nullptr;

public:
	DWORD dwClientBase = NULL;
	DWORD dwEngineBase = NULL;

	bool AttachToGame();

	void InitializeAddresses();

	template<class datatype> bool Read(Address<datatype> &adrRead) {
		if (adrRead.loc != 0) {
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
		if (adrWrite.loc != 0) {
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
