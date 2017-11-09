#pragma once
#include "../global.h"

template<typename value> struct Address {
	DWORD off; // offset
	value val; // value
	template<typename datatype> Address<datatype> operator+(Address<datatype> const & rhs) {
		// self addition
		Address<datatype> sum;
		sum.off = off + rhs.off;
		sum.val = val + rhs.val;
		return sum;
	}

	template<typename datatype> Address<datatype> operator-(Address<datatype> const & rhs) {
		// self subtraction
		Address<datatype> sum;
		sum.off = off - rhs.off;
		sum.val = val - rhs.val;
		return sum;
	}

	template<typename datatype> Address<datatype> operator+(const DWORD rhs) {
		// address addition
		Address<datatype> sum;
		sum.off = off + rhs;
		sum.val = val;
		return sum;
	}

	template<typename datatype> Address<datatype> operator-(const DWORD rhs) {
		// address subtraction
		Address<datatype> sum;
		sum.off = off - rhs;
		sum.val = val;
		return sum;
	}

	template<typename datatype> Address<datatype> operator+(const datatype rhs) {
		// value addition
		Address<datatype> sum;
		sum.off = off;
		sum.val = val + rhs;
		return sum;
	}

	template<typename datatype> Address<datatype> operator-(const datatype rhs) {
		// value subtraction
		Address<datatype> sum;
		sum.off = off;
		sum.val = val - rhs;
		return sum;
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
	DWORD_PTR dwClientBase = NULL;
	DWORD_PTR dwEngineBase = NULL;

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
		unsigned int startTime = GetTimeMs();










		HANDLE hSnapshot;
		unsigned short walkCount = 0;
		while (12000 < GetTimeMs() - startTime) {
			walkCount++;
			LogDebugMsg(DBG, 1, "Walk " + walkCount);
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
						dwClientBase = DWORD_PTR(me.modBaseAddr);
					}
					else if (!_stricmp(me.szModule, "engine.dll")) {
						dwEngineBase = DWORD_PTR(me.modBaseAddr);
					}
				} while (Module32Next(hSnapshot, &me) || !dwClientBase && !dwEngineBase);
				CloseHandle(hSnapshot);
			}
			if (!dwClientBase || !dwEngineBase) {
				LogDebugMsg(WRN, 1, "Failed " + walkCount + " walk!");
				Wait(1000);
				continue;
			}
			LogDebugMsg(SCS, 1, "Found module locations!");
			return true;
		}
		LogDebugMsg(ERR, 1, "Quit trying to walk after " + walkCount + " walks! (Timeout)");
		return false;



	}







	template<class datatype> bool Read(Address<datatype> adrRead) {
		return ReadProcessMemory(hGame, LPVOID(adrRead.off), &adrRead.val, sizeof(datatype), nullptr);
	}

	template<class datatype> bool Write(Address<datatype> adrWrite) {
		return WriteProcessMemory(hGame, LPVOID(adrWrite.off), &adrWrite.val, sizeof(datatype), nullptr);
	}


	MemoryManager();
	~MemoryManager();
};
