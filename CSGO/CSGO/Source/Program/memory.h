#pragma once
#include "../dllmain.h"

template<typename value> struct Address {
	const DWORD off; // offset
	std::atomic<DWORD> loc = off; // location
	std::atomic<value> val = NULL; // value

	// operator overloading

	template<typename datatype> Address<datatype> operator+(const Address<datatype> & rvalue) {
		// self addition
		loc += rvalue.off;
		val += rvalue.val;
		return *this;
	}

	template<typename datatype> Address<datatype> operator-(const Address<datatype> & rvalue) {
		// self subtraction
		loc -= rvalue.off;
		val -= rvalue.val;
		return *this;
	}

	template<typename datatype> Address<datatype> & operator=(const Address<datatype> & rvalue) {
		// self assignment
		loc = rvalue.loc;
		val = rvalue.val;
		return *this;
	}

	template<typename datatype> Address<datatype> & operator+=(const Address<datatype> & rvalue) {
		// self addition assignment
		loc += rvalue.off;
		val += rvalue.val;
		return *this;
	}

	template<typename datatype> Address<datatype> & operator-=(const Address<datatype> & rvalue) {
		// self subtraction assignment
		loc -= rvalue.off;
		val -= rvalue.val;
		return *this;
	}

	template<typename datatype> Address<datatype> operator+(const DWORD & rvalue) {
		// address addition
		loc += rvalue;
		return *this;
	}

	template<typename datatype> Address<datatype> operator-(const DWORD & rvalue) {
		// address subtraction
		loc -= rvalue;
		return *this;
	}

	template<typename datatype> Address<datatype> & operator=(const DWORD & rvalue) {
		// address assignment
		loc = rvalue;
		return *this;
	}

	template<typename datatype> Address<datatype> & operator+=(const DWORD & rvalue) {
		// address addition assignment
		loc += rvalue;
		return *this;
	}

	template<typename datatype> Address<datatype> & operator-=(const DWORD & rvalue) {
		// address subtraction assignment
		loc -= rvalue;
		return *this;
	}

	template<typename datatype> Address<datatype> operator+(const datatype & rvalue) {
		// value addition
		val += rvalue;
		return *this;
	}

	template<typename datatype> Address<datatype> operator-(const datatype & rvalue) {
		// value subtraction
		val -= rvalue;
		return *this;
	}

	template<typename datatype> Address<datatype> & operator=(const datatype & rvalue) {
		// value assignment
		val = rvalue;
		return *this;
	}

	template<typename datatype> Address<datatype> & operator+=(const datatype & rvalue) {
		// value addition assignment
		val += rvalue;
		return *this;
	}

	template<typename datatype> Address<datatype> & operator-=(const datatype & rvalue) {
		// value subtraction assignment
		val -= rvalue;
		return *this;
	}

};

struct Angle {
	float pitch, yaw, roll; // y, x, z
};

struct Coordinate {
	float x, y, z;
};

struct Color {
	unsigned __int8 r, g, b, a;
};

enum WeaponType {
	KNIFE,
	PISTOL,
	SMG,
	RIFLE,
	SHOTGUN,
	SNIPER,
	LMG,
	BOMB,
	PLACEHOLDER,
	GRENADE,
	UNKNOWN
};

class MemoryManager {
	DWORD dwProcessId = NULL;
	HANDLE hGame = nullptr;
public:
	DWORD dwClientBase = NULL;
	DWORD dwEngineBase = NULL;

	bool AttachToGame() {
		LogDebugMsg(DBG, 1, "Searching for CSGO");
		while (!GetWindowThreadProcessId(FindWindowA(nullptr, "Counter-Strike: Global Offensive"), &dwProcessId)) {
			Wait(1000);
		}
		LogDebugMsg(DBG, 1, "Found CSGO");
		LogDebugMsg(DBG, 1, "Opening handle");
		hGame = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE, false, dwProcessId);
		if (!hGame) {
			LogDebugMsg(ERR, 1, "Failed to open a handle to CSGO!");
			return false;
		}
		LogDebugMsg(SCS, 1, "Handle created!");
		LogDebugMsg(DBG, 1, "Walking modules");
		unsigned int startTime = GetTime();
		HANDLE hSnapshot;
		unsigned short walkCount = 0;
		while (12000 < GetTime() - startTime) {
			walkCount++;
			char out[6] = { 'W','a','l','k',' ', walkCount};
			LogDebugMsg(DBG, 1, out);
			LogDebugMsg(DBG, 1, "Enumerating modules");
			do {
				SetLastError(0);
				hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
				Wait(1);
			} while (hSnapshot == INVALID_HANDLE_VALUE && GetLastError() == ERROR_BAD_LENGTH);
			if (hSnapshot == INVALID_HANDLE_VALUE) {
				LogDebugMsg(ERR, 1, "Failed to enumerate modules!");
				return false;
			}
			MODULEENTRY32 me;
			me.dwSize = sizeof(MODULEENTRY32);
			if (Module32First(hSnapshot, &me)) {
				do {
					if (!_stricmp(me.szModule, "client.dll")) {
						dwClientBase = DWORD(me.modBaseAddr);
					} else if (!_stricmp(me.szModule, "engine.dll")) {
						dwEngineBase = DWORD(me.modBaseAddr);
					}
				} while (Module32Next(hSnapshot, &me) || !dwClientBase && !dwEngineBase);
				CloseHandle(hSnapshot);
			}
			if (!dwClientBase || !dwEngineBase) {
				char fail[14] = { 'F','a','i','l','e','d',' ',walkCount, ' ','w','a','l','k','!'};
				LogDebugMsg(WRN, 1, fail);
				Wait(1000);
				continue;
			}
			LogDebugMsg(SCS, 1, "Found module locations!");
			return true;
		}
		char quit[49] = { 'Q','u','i','t',' ','t','r','y','i','n','g',' ' // TODO Mike: append these character bits
			,'t','o',' ','w','a','l','k',' ','a','f','t','e','r',' ', walkCount,
			'w','a','l','k','s','!',' ','(','T','i','m','e','o','u','t',')'};
		LogDebugMsg(ERR, 1, quit);
		return false;
	}

	template<class datatype> bool Read(Address<datatype> & adrRead) {
		return ReadProcessMemory(hGame, LPVOID(adrRead.loc), &adrRead.val, sizeof(datatype), nullptr);
	}

	template<class datatype> bool Write(Address<datatype> & adrWrite) {
		return WriteProcessMemory(hGame, LPVOID(adrWrite.loc), &adrWrite.val, sizeof(datatype), nullptr);
	}

	Address<DWORD> dwLocalPlayer = {0xAAFD7C};
	Address<int> lp_iFlags = {0x100};
	Address<int> iForceJump = {0x4F2419C};

	void InitializeAddresses() {
		iForceJump += dwClientBase;
		dwLocalPlayer += dwClientBase;
		Read(dwLocalPlayer);
		lp_iFlags += dwLocalPlayer;
	}

	MemoryManager();
	~MemoryManager();
};
