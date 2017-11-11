#pragma once

template<typename datatype> struct Address 
{
	std::atomic<DWORD> loc = NULL; // location
	std::atomic<datatype> val = NULL; // value

	template<typename rdatatype> Address<datatype> operator+(const rdatatype & rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc += rvalue;
		}
		if (typeid(datatype) == typeid(rdatatype)) {
			val += rvalue;
		}
		return *this;
	}
	template<typename rdatatype> Address<datatype> operator-(const rdatatype & rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc -= rvalue;
		}
		if (typeid(datatype) == typeid(rdatatype)) {
			val -= rvalue;
		}
		return *this;
	}
	template<typename rdatatype> Address<datatype> & operator=(const rdatatype & rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc = rvalue;
		}
		if (typeid(datatype) == typeid(rdatatype)) {
			val = rvalue;
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> & operator+=(const rdatatype & rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc += rvalue;
		}
		if (typeid(datatype) == typeid(rdatatype)) {
			val += rvalue;
		}
		return *this;
	}

	template<typename rdatatype> Address<datatype> & operator-=(const rdatatype & rvalue) {
		if (typeid(DWORD) == typeid(rdatatype)) {
			loc -= rvalue;
		}
		if (typeid(datatype) == typeid(rdatatype)) {
			val -= rvalue;
		}
		return *this;
	}
};

class MemoryManager 
{
public:
	MemoryManager();
	~MemoryManager();
	bool AttachToGame();
	void InitializeAddresses();

private:
	DWORD dwProcessId = NULL;
	HANDLE hGame = nullptr;

public:
	DWORD dwClientBase = NULL;
	DWORD dwEngineBase = NULL;

	template<class datatype> bool Read(Address<datatype> & adrRead) {
		return ReadProcessMemory(hGame, LPVOID(adrRead.loc._My_val), &adrRead.val, sizeof(datatype), nullptr);
	}

	template<class datatype> bool Write(Address<datatype> & adrWrite) {
		return WriteProcessMemory(hGame, LPVOID(adrWrite.loc._My_val), &adrWrite.val, sizeof(datatype), nullptr);
	}

	Address<DWORD> dwLocalPlayer = {0xAAFD7C};
	Address<int> lp_iFlags = {0x100};
	Address<int> iForceJump = {0x4F2419C};

};
