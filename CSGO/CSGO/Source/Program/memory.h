#pragma once
#include "../main.h"

template<typename datatype> struct Address {
	std::atomic<DWORD> loc = NULL; // location
	std::atomic<DWORD> ptr = NULL; // this ptr
	std::atomic<datatype> val = NULL; // value

	template<typename rdatatype> Address<datatype> operator+(const rdatatype &rvalue);
	template<typename rdatatype> Address<datatype> operator-(const rdatatype &rvalue);
	template<typename rdatatype> Address<datatype> &operator=(const rdatatype &rvalue);
	template<typename rdatatype> Address<datatype> &operator+=(const rdatatype &rvalue);
	template<typename rdatatype> Address<datatype> &operator-=(const rdatatype &rvalue);
};

class MemoryManager {
	DWORD dwProcessId = NULL;
	HANDLE hGame = nullptr;

public:
	DWORD dwClientBase = NULL;
	DWORD dwEngineBase = NULL;

	bool AttachToGame();

	Address<int> ksForceJump = {0x4F2419C};
	Address<int> ksForceAttack = {0x2ECF46C};
	Address<float> fSensitivity = {0xAB547C, 0xAB5450};

	Address<DWORD> dwLocalPlayer = {0xAAFD7C};
	Address<int> lp_iFlags = {0x100};

	void InitializeAddresses();

	template<class datatype> bool Read(Address<datatype> &adrRead);
	template<class datatype> bool Write(Address<datatype> &adrWrite);
	~MemoryManager();

};
