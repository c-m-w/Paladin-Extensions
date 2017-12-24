#pragma once

class MemoryManager 
{
private:
	DWORD dwProcessId = NULL;
	HANDLE hGame = nullptr;

public:
	DWORD dwClientBase = NULL;
	DWORD dwEngineBase = NULL;

	~MemoryManager();

	bool AttachToGame();
	void InitializeAddresses();

	template<class datatype> bool Read(Address<datatype> &adrRead) 
	{
		if (adrRead.loc != 0) 
		{
			if (adrRead.ptr) 
			{
				DWORD dwXor;
				bool bSuccess = ReadProcessMemory(hGame, LPVOID(adrRead.loc), &dwXor, sizeof(DWORD), nullptr);
				adrRead.val = *reinterpret_cast<datatype*>(dwXor ^ adrRead.ptr);
				return bSuccess;
			}
			return ReadProcessMemory(hGame, LPVOID(adrRead.loc), &adrRead.val, sizeof(datatype), nullptr);
		}
		return false;
	}

	template<class datatype> bool Write(Address<datatype> &adrWrite) 
	{
		if (adrWrite.loc != 0) 
		{
			if (adrWrite.ptr) 
			{
				DWORD dwXor = *reinterpret_cast<DWORD*>(&adrWrite.val) ^ adrWrite.ptr;
				return ReadProcessMemory(hGame, LPVOID(adrWrite.loc), &dwXor, sizeof(DWORD), nullptr);
			}
			return WriteProcessMemory(hGame, LPVOID(adrWrite.loc), &adrWrite.val, sizeof(datatype), nullptr);
		}
		return false;
	}
};

extern MemoryManager *mem;