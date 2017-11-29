#pragma once
#include "../includes.h"
#include "general.h"

template<typename datatype> struct Address {
	DWORD loc = NULL; // location
	DWORD ptr = NULL; // this ptr
	datatype val = NULL; // value

	template<typename rdatatype> Address<datatype> operator+(rdatatype rhs) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc += DWORD(rhs);
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val += datatype(rhs);
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> operator-(rdatatype rhs) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc -= DWORD(rhs);
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val -= datatype(rhs);
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> &operator=(rdatatype rhs) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc = DWORD(rhs);
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val = datatype(rhs);
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> &operator+=(rdatatype rhs) {
		return (*this + rhs); // TODO warning C4172
	}

	template<typename rdatatype> Address<datatype> &operator-=(rdatatype rhs) {
		return (*this - rhs); // TODO warning C4172
	}

	template<typename rdatatype> bool operator==(rdatatype rhs) {
		if (typeid(DWORD) == typeid(rdatatype) && typeid(DWORD) != typeid(datatype)) {
			if (loc == DWORD(rhs)) {
				return true;
			}
		} else if (typeid(datatype) == typeid(rdatatype)) {
			if (val == datatype(rhs)) {
				return true;
			}
		}
		return false;
	}

	template<typename rdatatype> bool operator!=(rdatatype rhs) {
		return !(*this == rhs);
	}

	template<typename rdatatype> datatype operator&(rdatatype rhs) {
		if (typeid(datatype) == typeid(rdatatype)) {
			return val & datatype(rhs);
		}
		return 0;
	}

	template<typename rdatatype> datatype operator|(rdatatype rhs) {
		if (typeid(datatype) == typeid(rdatatype)) {
			return val | datatype(rhs);
		}
		return 0;
	}
};

namespace Addresses {

	extern Address<DWORD> dwClientState;
	extern Address<uint8> cs_soState;

	extern Address<uint8> ksForceJump;
	extern Address<uint8> ksForceAttack;
	extern Address<float> flSensitivity;

	extern Address<DWORD> dwLocalPlayer;
	extern Address<frame> lp_fFlags;
	extern Address<total> lp_totalHitsOnServer;
}

using namespace Addresses;

class MemoryManager {
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

	~MemoryManager();
};

extern MemoryManager mem;
