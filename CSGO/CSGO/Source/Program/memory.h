#pragma once
#include "interface.h"

template<typename datatype> struct Address {
	DWORD loc = NULL; // location
	DWORD ptr = NULL; // this ptr
	datatype val = NULL; // value

	template<typename rdatatype> Address<datatype> operator+(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc += rvalue;
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val += rvalue;
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> operator-(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc -= rvalue;
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val -= rvalue;
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> &operator=(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc = DWORD(rvalue);
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val = rvalue;
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> &operator+=(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc += rvalue;
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val += datatype(rvalue);
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> &operator-=(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc -= rvalue;
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val -= rvalue;
		}
		return *this;
	}

	template<typename rdatatype> bool operator==(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			if (loc == rvalue) {
				return true;
			}
		} else if (typeid(datatype) == typeid(rdatatype)) {
			if (val == rvalue) {
				return true;
			}
		}
		return false;
	}

	template<typename rdatatype> bool operator!=(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			if (loc != rvalue) {
				return true;
			}
		} else if (typeid(datatype) == typeid(rdatatype)) {
			if (val != rvalue) {
				return true;
			}
		}
		return false;
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
		if (adrRead.ptr) {
			DWORD dwXor;
			bool bSuccess = ReadProcessMemory(hGame, LPVOID(adrRead.loc), &dwXor, sizeof(DWORD), nullptr);
			adrRead.val = *reinterpret_cast<datatype*>(dwXor ^ adrRead.ptr);
			return bSuccess;
		}
		return ReadProcessMemory(hGame, LPVOID(adrRead.loc), &adrRead.val, sizeof(datatype), nullptr);
	}

	template<class datatype> bool Write(Address<datatype> &adrWrite) {
		if (adrWrite.ptr) {
			DWORD dwXor = *reinterpret_cast<DWORD*>(&adrWrite.val) ^ adrWrite.ptr;
			return ReadProcessMemory(hGame, LPVOID(adrWrite.loc), &dwXor, sizeof(DWORD), nullptr);
		}
		return WriteProcessMemory(hGame, LPVOID(adrWrite.loc), &adrWrite.val, sizeof(datatype), nullptr);
	}

	~MemoryManager();

};

extern MemoryManager mem;
