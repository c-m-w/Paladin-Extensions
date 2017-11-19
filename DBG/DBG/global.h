#pragma once

#define PI 3.141593f

extern HINSTANCE hInst;
extern std::atomic<bool> bExitState;
extern std::vector<std::thread> threads;

void Wait(unsigned int z);
unsigned int GetTime();