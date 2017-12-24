#pragma once

/*	ToDo
 *	-Operator overloading for Pointer.val
 *	-Fix equality and setting
 *	-Fix ur operator overload paste
 *	-Config shit
 */

#define _CRT_SECURE_NO_WARNINGS

//Comment out for no debug console
#define m_DEBUG

#include <Windows.h>
#include <TlHelp32.h>
#include <atomic>
#include <thread>
#include <vector>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <io.h>

//Items from main related to exiting
extern HINSTANCE hInst;

extern std::atomic<bool> bEjecting;
extern std::atomic<bool> bExit;
extern std::vector<std::thread> threads;

void Panic();
void Cleanup(bool exit = false);

#include "debug.h"

#include "types.h"
#include "global.h"
#include "addresses.h"

#include "memory.h"
#include "engine.h"

#include "autojump.h"