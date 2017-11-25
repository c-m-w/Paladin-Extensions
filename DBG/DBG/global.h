#pragma once

#define PI 3.141593f

extern HINSTANCE hInst;
extern std::atomic<bool> bExitState;
extern std::vector<std::thread> threads;

void Panic();
void Cleanup(bool exit = false);

void Wait(unsigned int z);
unsigned int GetTime();