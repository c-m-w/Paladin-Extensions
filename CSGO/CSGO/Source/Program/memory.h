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
	std::atomic<bool> bExitState = false;
public:
	bool GetExitState() const {
		return bExitState;
	}

	void SetExitState(const bool bState) {
		bExitState = bState;
	}

	template<class datatype> bool Read(Address<datatype> adrRead) {
		return ReadProcessMemory(hGame, LPVOID(adrRead.off), &adrRead.val, sizeof(datatype), nullptr);
	}

	template<class datatype> bool Write(Address<datatype> adrWrite) {
		return WriteProcessMemory(hGame, LPVOID(adrWrite.off), &adrWrite.val, sizeof(datatype), nullptr);
	}
};
