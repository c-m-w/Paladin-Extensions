#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>

#include "global.h"
#include "debug.h"

#include "Program/general.h"
#include "Program/config.h"
#include "Program/interface.h"
#include "Program/memory.h"

#include "Features/engine.h"
#include "Features/Awareness/hitsound.h"
#include "Features/Awareness/nodrunk.h"
#include "Features/Combat/trigger.h"
#include "Features/Miscellaneous/automation.h"

void Feature( bool, unsigned, std::function< void( ) > );
void Feature( bool, unsigned, std::function< void( ) >, int );
void CleanUp( );
void Panic( );
void CreateThreads( );
bool GetPremium( );
void SetDebug( );
int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow );
BOOL WINAPI DllMain( HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved );

/* Conventions:
 * Start naming on everything with a capital
 * * Variables must start with a lowercase including their datatype (bExitState, dwClientBase)
 * * * EEnum
 * * * * NUMS ARE ALL CAPITALS
 * * * CClass
 * * * struct_t
 * * * typedef
 * * * b bool/byte
 * * * f flag
 * * * i int
 * * * n unsigned int (total, c are alternatives - pls do not use these)
 * * * l long
 * * * clr color
 * * * cor coordinate
 * * * ang angle
 * * * mnt moment
 * * * vec vector
 * * * fl float
 * * * db double
 * * * ch char
 * * * sz string of chars
 * * * str string
 * * * dw dword
 * * * fn function
 * * * p pointer
 * * * lp long pointer
 * * * x unknown (_ is an alternative - pls do not use this)
 * * Variables must also include their inheritance prefix with an underscore (lp_fFlags for frame Local Player Flags)
 * Every function should be a verb (get, set, clamp)
 * * Instead of Alive or IsAlive, do GetLifeState
 * Everything should be English
 * * Instead of OffsetX for a function, do GetHorizontalDistance
 * Always clean your code with ReSharper before committing
 * * Retest to make sure it doesn't break anything!
 */