#pragma once
#include "../main.h"

template<typename datatype> struct Address {
	std::atomic<DWORD> loc = NULL; // location
	std::atomic<DWORD> ptr = NULL; // this ptr
	std::atomic<datatype> val = NULL; // value

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
			loc = rvalue;
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val = rvalue;
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> &operator+=(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc += rvalue;
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val._My_val += rvalue;
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> &operator-=(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc -= rvalue;
		} else if (typeid(datatype) == typeid(rdatatype)) {
			val._My_val -= rvalue;
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
	extern Address<int> cs_soState;

	extern Address<int> ksForceJump;
	extern Address<int> ksForceAttack;
	extern Address<float> fSensitivity;

	extern Address<DWORD> dwLocalPlayer;
	extern Address<int> lp_uiFlags;
	extern Address<int> lp_uiTotalHits;
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
			bool bSuccess = ReadProcessMemory(hGame, LPVOID(adrRead.loc._My_val), &dwXor, sizeof(DWORD), nullptr);
			adrRead.val = *reinterpret_cast<datatype*>(dwXor ^ adrRead.ptr);
			return bSuccess;
		}
		return ReadProcessMemory(hGame, LPVOID(adrRead.loc._My_val), &adrRead.val, sizeof(datatype), nullptr);
	}

	template<class datatype> bool Write(Address<datatype> &adrWrite) {
		if (adrWrite.ptr) {
			DWORD dwXor = *reinterpret_cast<DWORD*>(&adrWrite.val) ^ adrWrite.ptr;
			return ReadProcessMemory(hGame, LPVOID(adrWrite.loc._My_val), &dwXor, sizeof(DWORD), nullptr);
		}
		return WriteProcessMemory(hGame, LPVOID(adrWrite.loc._My_val), &adrWrite.val, sizeof(datatype), nullptr);
	}

	~MemoryManager();

};

extern MemoryManager mem;
