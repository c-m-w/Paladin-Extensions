#pragma once

//ToDo: Possibly implement in the future
template<typename value> struct address 
{
	DWORD offset;
	DWORD loc;
	value val;
	bool op; //Whether or not operation was successful (safe to access data)
};


class Memory 
{
private:
	HANDLE hGame;
	
	DWORD clientDll;
	DWORD engineDll;

//A bit dangerous, might fix in the future (possibly by inheritance from engine class)
public:
	DWORD clientOffs;
	DWORD client;
	DWORD clientStateOffs;
	DWORD clientState;

public:
	Memory();
	bool Attach();
	bool Init();


/*
 *	Memory access
 *	Only error check/log on debug build for now
 *	ToDo: Print data type of t
 */
public:

#ifdef _DEBUG

	template<class t> t rpm(DWORD addr)
	{
		t tmp;
		if (!ReadProcessMemory(this->hGame, (LPVOID)addr, &tmp, sizeof(t), nullptr)) 
		{
			//DEBUG(ERR, "ReadProcessMemory failed to read at 0x%lu\n", addr);
			DEBUG(ERR, 1, "ReadProcessMemory failed at 0x%08lu\n", addr);
			LASTERR(1);
			return 0;
		}
		return tmp;
	}

	template<class t> void wpm(DWORD addr, t &val)
	{
		if (!WriteProcessMemory(this->hGame, (LPVOID)addr, val, sizeof(t), nullptr)) 
		{
			DEBUG(ERR, 1, "WriteProcessMemory failed at 0x%08lu\n", addr);
			LASTERR(1);
		}
	}

#else

	template<class t> t rpm(DWORD addr)
	{
		t tmp;
		ReadProcessMemory(this->hGame, (LPVOID)addr, &tmp, sizeof(t), nullptr);
		return tmp;
	}

	template<class t> void wpm(DWORD addr, t & val)
	{
		WriteProcessMemory(this->hGame, (LPVOID)addr, val, sizeof(t), nullptr);
	}

#endif
	
};