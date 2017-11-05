#pragma once
#include <Windows.h>
#include <thread>
#include <TlHelp32.h>
#include <atomic>
#include <ctime>
#define PI 3.141593f

/* Conventions:
 * Start everything with a capital
 * * Variables must start with a lowercase including their datatype (bExitState, dwClientBase)
 * Every function should be a verb (get, clamp)
 * * Instead of Alive or IsAlive, do GetLifeState
 * Everything should be English
 * * Instead of OffsetX for a function, do GetHorizontalDistance
 * Always clean your code with ReSharper before committing
 * * Retest to make sure it doesn't break anything!
 */

DWORD dwProcessId;
HANDLE hGame;

template<typename value> struct Address {
	DWORD off; // offset
	value val; // value
	template<typename size> Address<size> operator+(Address<size> const & rhs) {
		Address<size> sum;
		sum.off = this->off + rhs.off;
		sum.val = this->val + rhs.val;
		return sum;
	}

	template<typename size> Address<size> operator+(const DWORD rhs) {
		Address<size> sum;
		sum.off = this->off + rhs;
		sum.val = this->val;
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

template<class size> bool Read(Address<size> adrRead) {
	return ReadProcessMemory(hGame, LPVOID(adrRead.off), &adrRead.val, sizeof(size), nullptr);
}

template<class size> bool Write(Address<size> adrWrite) {
	return WriteProcessMemory(hGame, LPVOID(adrWrite.off), &adrWrite.val, sizeof(size), nullptr);
}

inline void Wait(const unsigned int z) {
	std::this_thread::sleep_for(std::chrono::milliseconds(z));
}

inline int GetTimeMs() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

enum CsWeaponType {
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};
