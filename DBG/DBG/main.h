#pragma once

#define _CRT_SECURE_NO_WARNINGS

//Comment out for no debug console
#define m_DEBUG

#include <Windows.h>
#include <atomic>
#include <thread>
#include <vector>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <io.h>

void Panic();

#include "debug.h"
#include "global.h"