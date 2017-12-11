#include "dllmain.h"

HINSTANCE hInst = nullptr;
std::atomic<bool> bExitState = false;
std::vector<std::thread> tThreads;

void Wait(unsigned int z) {
	std::this_thread::sleep_for(std::chrono::milliseconds(z));
}

Time GetTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

bool angle::operator==(angle rhs) {
	if (pitch == rhs.pitch && yaw == rhs.yaw && roll == rhs.roll) {
		return true;
	}
	return false;
}

bool angle::operator!=(angle rhs) {
	return !(*this == rhs);
}

vector::vector(coordinate cOrigin, coordinate cEndPoint) {
	dx = cEndPoint.x - cOrigin.x;
	dy = cEndPoint.y - cOrigin.y;
	dz = cEndPoint.z - cOrigin.z;
