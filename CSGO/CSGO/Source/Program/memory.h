#pragma once
#include "../main.h"

template<typename datatype> struct Address {
	std::atomic<DWORD> loc = NULL; // location
	std::atomic<DWORD> ptr = NULL; // this ptr
	std::atomic<datatype> val = NULL; // value

	template<typename rdatatype> Address<datatype> operator+(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc += rvalue;
		}
		if (typeid(datatype) == typeid(rdatatype)) {
			val += rvalue;
		}
		return *this;
	}
	template<typename rdatatype> Address<datatype> operator-(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc -= rvalue;
		}
		if (typeid(datatype) == typeid(rdatatype)) {
			val -= rvalue;
		}
		return *this;
	}
	template<typename rdatatype> Address<datatype> &operator=(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc = rvalue;
		}
		if (typeid(datatype) == typeid(rdatatype)) {
			val = rvalue;
		}
		return *this;
	}
	template<typename rdatatype> Address<datatype> &operator+=(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc += rvalue;
		}
		if (typeid(datatype) == typeid(rdatatype)) {
			val += rvalue;
		}
		return *this;
	}
	template<typename rdatatype> Address<datatype> &operator-=(const rdatatype &rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc -= rvalue;
		}
		if (typeid(datatype) == typeid(rdatatype)) {
			val -= rvalue;
		}
		return *this;
	}
};

namespace Addresses {
	// global addresses
	Address<Keystroke> ksForceJump = { 0x4F2419C };
	Address<Keystroke> ksForceAttack = { 0x2ECF46C };
	Address<float> fSensitivity = { 0xAB547C, 0xAB5450 };
	// pointer addresses
	Address<DWORD> dwLocalPlayer = { 0xAAFD7C };
	Address<int> lp_iFlags = { 0x100 };
	Address<int> lp_uiTotalHits = { 0xBA94 };
}

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
