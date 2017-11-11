#pragma once

template<typename value> struct Address 
{
	DWORD off; // offset
	std::atomic<DWORD> loc = off; // location
	std::atomic<value> val = NULL; // value

	// self addition
	template<typename datatype> Address<datatype> operator+(const Address<datatype> & rvalue) 
	{
		this->loc += rvalue.off;
		this->val += rvalue.val;
		return *this;
	}

	// self subtraction
	template<typename datatype> Address<datatype> operator-(const Address<datatype> & rvalue) 
	{
		this->loc -= rvalue.off;
		this->val -= rvalue.val;
		return *this;
	}

	// self assignment
	template<typename datatype> Address<datatype> & operator=(const Address<datatype> & rvalue) 
	{
		this->loc = rvalue.loc;
		this->val = rvalue.val;
		return *this;
	}

	// self addition assignment
	template<typename datatype> Address<datatype> & operator+=(const Address<datatype> & rvalue) 
	{
		this->loc += rvalue.off;
		this->val += rvalue.val;
		return *this;
	}

	// self subtraction assignment
	template<typename datatype> Address<datatype> & operator-=(const Address<datatype> & rvalue) 
	{
		this->loc -= rvalue.off;
		this->val -= rvalue.val;
		return *this;
	}

	// address addition
	template<typename datatype> Address<datatype> operator+(const DWORD & rvalue) 
	{
		this->loc += rvalue;
		return *this;
	}

	// address subtraction
	template<typename datatype> Address<datatype> operator-(const DWORD & rvalue) 
	{
		this->loc -= rvalue;
		return *this;
	}

	// address assignment
	template<typename datatype> Address<datatype> & operator=(const DWORD & rvalue) 
	{
		this->loc = rvalue;
		return *this;
	}

	// address addition assignment
	template<typename datatype> Address<datatype> & operator+=(const DWORD & rvalue) 
	{
		this->loc += rvalue;
		return *this;
	}

	// address subtraction assignment
	template<typename datatype> Address<datatype> & operator-=(const DWORD & rvalue) 
	{
		this->loc -= rvalue;
		return *this;
	}

	// value addition
	template<typename datatype> Address<datatype> operator+(const datatype & rvalue) 
	{
		this->val += rvalue;
		return *this;
	}

	// value subtraction
	template<typename datatype> Address<datatype> operator-(const datatype & rvalue) 
	{
		this->val -= rvalue;
		return *this;
	}

	// value assignment
	template<typename datatype> Address<datatype> & operator=(const datatype & rvalue) 
	{
		this->val = rvalue;
		return *this;
	}

	// value addition assignment
	template<typename datatype> Address<datatype> & operator+=(const datatype & rvalue) 
	{
		this->val += rvalue;
		return *this;
	}

	// value subtraction assignment
	template<typename datatype> Address<datatype> & operator-=(const datatype & rvalue) 
	{
		this->val -= rvalue;
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
