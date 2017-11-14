#pragma once

#define PI 3.141593f

class Global {
public:
	HINSTANCE hInst = nullptr;
	std::atomic<bool> bExitState = false;
	std::vector<std::thread> threads;

	static void Wait(const unsigned int z);
	unsigned int GetTime() const;

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
};
