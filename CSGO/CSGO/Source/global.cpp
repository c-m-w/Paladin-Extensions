#include "dllmain.h"

HINSTANCE hInst = nullptr;
std::atomic<bool> bExitState = false;
std::vector<std::thread> tThreads;

void Wait(unsigned int nSleepTime) {
	std::this_thread::sleep_for(std::chrono::milliseconds(nSleepTime));
}

moment GetTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

bool angle_t::operator==(angle_t rhs) {
	if (pitch == rhs.pitch && yaw == rhs.yaw && roll == rhs.roll) {
		return true;
	}
	return false;
}

bool angle_t::operator!=(angle_t rhs) {
	return !(*this == rhs);
}

angle_t angle_t::operator+(angle_t rhs) {
	pitch += rhs.pitch;
	yaw += rhs.yaw;
	roll += rhs.roll;
	return *this;
}

angle_t angle_t::operator-(angle_t rhs) {
	pitch -= rhs.pitch;
	yaw -= rhs.yaw;
	roll -= rhs.roll;
	return *this;
}

angle_t & angle_t::operator+=(angle_t rhs) {
	return *this + rhs;
}

angle_t & angle_t::operator-=(angle_t rhs) {
	return *this - rhs;
}

vector_t::vector_t(coordinate_t cOrigin, coordinate_t cEndPoint) {
	dx = cEndPoint.x - cOrigin.x;
	dy = cEndPoint.y - cOrigin.y;
	dz = cEndPoint.z - cOrigin.z;
}
