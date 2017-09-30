#include "stdafx.h"
#include "memory.h"
// ReSharper disable once CppPossiblyUninitializedMember
memory::memory() {}
void memory::z(const int z) {
    std::this_thread::sleep_for(std::chrono::milliseconds(z));
}
bool memory::gameAttach() {
    processEntry.dwSize = sizeof(PROCESSENTRY32);
failed:
    snapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapHandle == INVALID_HANDLE_VALUE) {
        return false;
    }
    Process32First(snapHandle, &processEntry);
    do {
        if (!_stricmp(processEntry.szExeFile, gameExe)) {
            gameHandle = OpenProcess(access, false, processEntry.th32ProcessID);
            goto got_handle;
        }
    } while (Process32Next(snapHandle, &processEntry));
    z(1);
    goto failed;
got_handle:
    return true;
}
DWORD_PTR memory::moduleWrapping(TCHAR * moduleName) {
    if (!FindWindowA(nullptr, gameName)) {
        do {
            z(12000);
        } while (!FindWindowA(nullptr, gameName));
    }
    do {
        snapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processEntry.th32ProcessID);
        z(1);
    } while (snapHandle == INVALID_HANDLE_VALUE && GetLastError() == ERROR_BAD_LENGTH);
    if (snapHandle == INVALID_HANDLE_VALUE) {
        goto failed;
    }
    moduleEntry.dwSize = sizeof(MODULEENTRY32);
    Module32First(snapHandle, &moduleEntry);
    do {
        if (!_stricmp(moduleEntry.szModule, moduleName)) {
            goto wrapped;
        }
    } while (Module32Next(snapHandle, &moduleEntry));
    CloseHandle(snapHandle);
    goto failed;
wrapped:
    CloseHandle(snapHandle);
    return DWORD_PTR(moduleEntry.modBaseAddr);
failed:
    return false;
}
void memory::setAccess(const DWORD inAccess) {
    access = inAccess;
}
template<class size> void memory::rpm(const DWORD read, size & write) {
    ReadProcessMemory(gameHandle, LPVOID(read), &write, sizeof(size), nullptr);
}
template<class size> void memory::wpm(const DWORD read, size & write) {
    WriteProcessMemory(gameHandle, LPVOID(read), &write, sizeof(size), nullptr);
}
void memory::initialize(const DWORD_PTR clientModule, const DWORD_PTR engineModule) {
    pointerClientState += engineModule;
    rpm<DWORD>(pointerClientState, clientState);
    offsetConnection += clientState;
    WINDOWINFO info;
    GetWindowInfo(FindWindowA(nullptr, gameName), &info);
    if (info.dwExStyle & WS_EX_TOPMOST) {
        while (GetForegroundWindow() != FindWindowA(nullptr, gameName)) {
            z(1);
        }
    }
    RECT temp;
    GetWindowRect(FindWindowA(nullptr, gameName), &temp);
    if (temp.right == GetSystemMetrics(SM_CXSCREEN) && temp.bottom == GetSystemMetrics(SM_CYSCREEN)) {
        screen._My_val.x = temp.right - temp.left;
        screen._My_val.y = temp.bottom - temp.top;
    } else {
        screen._My_val.x = temp.right - temp.left - 6;
        screen._My_val.y = temp.bottom - temp.top - 29;
    }
    do {
        rpm<int>(offsetConnection, connection);
        z(1);
    } while (connection != 6);
    pointerLocalPlayer += clientModule;
    rpm<DWORD>(pointerLocalPlayer, localPlayer);
    offsetHits += localPlayer;
    offsetFlag += localPlayer;
    offsetCrosshair += localPlayer;
    SystemParametersInfo(SPI_GETMOUSESPEED, 0, &winSens, false);
    offsetSensitivity += clientModule;
    offsetSensitivityPtr += clientModule;
    rpm<int>(offsetSensitivity, sensitivity);
    sensitivity ^= offsetSensitivityPtr;
    sens = *reinterpret_cast<float*>(&sensitivity);
    convertMouse = .022f * sens * (static_cast<float>(winSens) / 10.f);
    offsetViewPunch += localPlayer;
    offsetShotFired += localPlayer;
    offsetPlayerLocation += localPlayer;
    offsetEntities += clientModule;
}
BOOL memory::patternCompare(BYTE * data, BYTE * mask, char * szMask) {
    for (; *szMask; ++szMask, ++data, ++mask)
        if (*szMask == 'x' && *data != *mask) {
            return false;
        }
    return *szMask;
}
DWORD memory::findPattern(BYTE * mask, char * szMask, const DWORD address, const DWORD length) const {
    const DWORD dataLength = strlen(szMask);
    const auto data = new BYTE[dataLength + 1];
    SIZE_T read;
    for (DWORD i = 0; i < length; i++) {
        const auto curAddress = address + i;
        const bool success = ReadProcessMemory(gameHandle, LPCVOID(curAddress), data, dataLength, &read);
        if (!success || read == 0) {
            continue;
        }
        if (patternCompare(data, mask, szMask)) {
            delete[] data;
            return address + i;
        }
    }
    delete[] data;
    return 0;
}
bool memory::closeThreads(const bool x) {
    timeToExit = x;
    if (timeToExit == x) {
        return true;
    }
    return false;
}
bool memory::exit(const bool isContinue) const {
    do {
        if (timeToExit || !isContinue) {
            return true;
        }
        z(1);
    } while (GetForegroundWindow() != FindWindowA(nullptr, gameName));
    return false;
}
void memory::bhop() {
    while (true) {
        rpm<int>(offsetConnection, connection);
        while (connection == 6) {
            rpm<int>(offsetConnection, connection);
            while (GetAsyncKeyState(keyBhop)) {
                rpm<int>(offsetFlag, flag);
                if (flag == 257 || flag == 261 || flag == 263) {
                    if (bhopHitchance >= static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 100.f)) {
                        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, WHEEL_DELTA * bhopDirection, 0);
                        z(bhopNextDelay._My_val);
                    } else {
                        z(bhopNextDelay._My_val * 7);
                        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, WHEEL_DELTA * bhopDirection, 0);
                    }
                }
            }
            if (exit(isBhop)) {
                return;
            }
        }
        if (exit(isBhop)) {
            return;
        }
    }
}
void memory::trigger() {
    while (true) {
        rpm<int>(offsetConnection, connection);
        while (connection == 6) {
            int tempTime[2];
            tempTime[0] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            while (GetAsyncKeyState(keyTrig)) {
                rpm<int>(offsetCrosshair, inCross);
                if (inCross) {
                    if (isTrigSlow && !isSlow) {
                        SystemParametersInfo(SPI_SETMOUSESPEED, 0, LPVOID(winSens / slowFactor), SPIF_SENDCHANGE);
                        if (isTrigDelay) {
                            z(rand() % (trigDelayMax - trigDelayMin) + trigDelayMin);
                        }
                        do {
                            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                            z(rand() % (trigDelayNextMax - trigDelayNextMin) + trigDelayNextMin);
                            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                            z(rand() % (trigDelayNextMax - trigDelayNextMin) + trigDelayNextMin);
                            rpm<int>(offsetCrosshair, inCross);
                            tempTime[1] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                            if (tempTime[1] - tempTime[0] > 10000) {
                                // ENTER 10000 timeout variable
                                z(3000);
                                break;
                            }
                        } while (inCross);
                        wasInCross = true;
                    } else {
                        if (isTrigDelay) {
                            z(trigDelayMin);
                        }
                        do {
                            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                            z(7);
                            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                            z(7);
                            rpm<int>(offsetCrosshair, inCross);
                            tempTime[1] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                            if (tempTime[1] - tempTime[0] > 10000) {
                                // ENTER 10000 timeout variable
                                z(3000);
                                break;
                            }
                        } while (inCross);
                        wasInCross = true;
                    }
                }
            }
            if (wasInCross) {
                SystemParametersInfo(SPI_SETMOUSESPEED, 0, LPVOID(winSens), SPIF_SENDCHANGE);
                wasInCross = false;
            }
            if (exit(isTrig)) {
                return;
            }
        }
        if (exit(isTrig)) {
            return;
        }
    }
}
void memory::slowaim() {
    while (true) {
        rpm<int>(offsetConnection, connection);
        while (connection == 6) {
            int tempTime[2];
            tempTime [0] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            rpm<int>(offsetCrosshair, inCross);
            if (inCross) {
                SystemParametersInfo(SPI_SETMOUSESPEED, 0, LPVOID(winSens / slowFactor), SPIF_SENDCHANGE);
                wasInCross = true;
                while (inCross) {
                    rpm<int>(offsetCrosshair, inCross);
                    tempTime[1] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    if (tempTime[1] - tempTime[0] > 10000) {
                        // ENTER 10000 timeout variable
                        z(3000);
                        break;
                    }
                }
            }
            if (wasInCross & !inCross) {
                SystemParametersInfo(SPI_SETMOUSESPEED, 0, LPVOID(winSens), SPIF_SENDCHANGE);
                wasInCross = false;
            }
            if (exit(isSlow)) {
                return;
            }
        }
        if (exit(isSlow)) {
            return;
        }
    }
}
void memory::rcs() {
    while (true) {
        rpm<int>(offsetConnection, connection);
        while (connection == 6) {
            rcsTo.store({
                0, 0, 0
            });
            viewPunchPrevious.store({
                0, 0, 0
            });
            shotFiredPrevious = 0;
            while (GetAsyncKeyState(VK_LBUTTON)) {
                rpm<int>(offsetShotFired, shotFired);
                if (shotFired > rcsIgnoreShots && shotFired > shotFiredPrevious) {
                    rpm<vector>(offsetViewPunch, viewPunchCurrent);
                    // math
                    const vector temp {
                        viewPunchCurrent.x - viewPunchPrevious._My_val.x, viewPunchPrevious._My_val.y - viewPunchCurrent.y, 0
                    };
                    rcsTo.store({
                        ((rcsXMin + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (rcsXMax - rcsXMin))) * (temp.x * 2.f) / convertMouse),
                        ((rcsYMin + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (rcsYMax - rcsYMin))) * (temp.y * 2.f) / convertMouse),
                        0
                    });
                    if (wasInCross) {
                        rcsTo.store({
                            rcsTo._My_val.x * slowFactor,
                            rcsTo._My_val.y * slowFactor
                        });
                    }
                    // rounding
                    if (rcsTo._My_val.x > 0) {
                        rcsTo._My_val.x += 1;
                    } else if (rcsTo._My_val.x < 0) {
                        rcsTo._My_val.x -= 1;
                    }
                    if (rcsTo._My_val.y > 0) {
                        rcsTo._My_val.y += 1;
                    } else if (rcsTo._My_val.y < 0) {
                        rcsTo._My_val.y -= 1;
                    }
                    mouseRcs._My_val.x = -static_cast<int>(rcsTo._My_val.y);
                    mouseRcs._My_val.y = -static_cast<int>(rcsTo._My_val.x);
                    // smoothing
                    const auto smoothing = rand() % (smoothFactorMax - smoothFactorMin) + smoothFactorMin;
                    if (isSmooth) {
                        for (auto smooth = 0; smooth < smoothing; smooth++) {
                            mouse_event(MOUSEEVENTF_MOVE, mouseRcs._My_val.x / smoothing, mouseRcs._My_val.y / smoothing, 0, 0);
                            z(7);
                        }
                    } else {
                        mouse_event(MOUSEEVENTF_MOVE, mouseRcs._My_val.x, mouseRcs._My_val.y, 0, 0);
                    }
                    // readjustment
                    if (shotFired % 10 == 0 && isSmooth) {
                        mouse_event(MOUSEEVENTF_MOVE, smoothing, smoothing, 0, 0);
                    }
                    // storing
                    viewPunchPrevious.store(viewPunchCurrent);
                    shotFiredPrevious = shotFired;
                }
            }
            if (exit(isRcs)) {
                return;
            }
        }
        if (exit(isRcs)) {
            return;
        }
    }
}
void memory::aim() {
    while (true) {
        rpm<int>(offsetConnection, connection);
        while (connection == 6) {
            int tempTime[2];
            tempTime[0] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            while (GetAsyncKeyState(keyAim)) {
                rpm<int>(offsetCrosshair, inCross);
                if (0 < inCross && inCross < 64) {
                    rpm<DWORD>(offsetEntities + (inCross + 1) * 0x10, entityEnemy);
                    rpm<vector>(entityEnemy + 0x134, enemyBone);
                    rpm<vector>(offsetPlayerLocation, localPlayerLocation);
                    localPlayerView.store({
                        localPlayerLocation.x, localPlayerLocation.y, localPlayerLocation.z
                    });
                    const vector temp {
                        localPlayerView._My_val.x - enemyBone.x, localPlayerView._My_val.y - enemyBone.y, localPlayerView._My_val.z - enemyBone.z + aimDisplace
                    };
                    //
                    //
                    // TODO
                    //
                    //
                    const auto hypotu = sqrt(temp.x * temp.x + temp.y * temp.y);
                    std::cout << "ANG X: " << atan2(temp.z, hypotu) * (180.0f / pi) << "\n";
                    std::cout << "ANG Y: " << atan2(temp.y, temp.x) * (180.0f / pi) << "\n";
                    aimTo.store({
                        atan2(temp.z, hypotu) * (180.0f / pi) / convertMouse,
                        atan2(temp.y, temp.x) * (180.0f / pi) / convertMouse
                    });
                    //
                    //
                    // TODO
                    //
                    //
                    if (wasInCross) {
                        aimTo.store({
                            aimTo._My_val.x * slowFactor,
                            aimTo._My_val.y * slowFactor
                        });
                    }
                    if (aimTo._My_val.x > 0) {
                        aimTo.store({
                            aimTo._My_val.x + 1
                        });
                    }
                    if (aimTo._My_val.y > 0) {
                        aimTo.store({
                            aimTo._My_val.y + 1
                        });
                    }
                    mouseAim.store({
                        static_cast<int>(aimOver * aimTo._My_val.y - rcsTo._My_val.y),
                        static_cast<int>(aimOver * aimTo._My_val.x - rcsTo._My_val.x)
                    });
                    const auto smoothing = rand() % (smoothFactorMax - smoothFactorMin) + smoothFactorMin;
                    if (isSmooth) {
                        for (auto smooth = 0; smooth < smoothing; smooth++) {
                            mouse_event(MOUSEEVENTF_MOVE, mouseAim._My_val.x / smoothing, mouseAim._My_val.y / smoothing, 0, 0);
                            z(7);
                        }
                    } else {
                        mouse_event(MOUSEEVENTF_MOVE, mouseAim._My_val.x, mouseAim._My_val.y, 0, 0);
                        z(1);
                    }
                }
                tempTime[1] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                if (tempTime[1] - tempTime[0] > 10000) {
                    // ENTER 10000 timeout variable
                    z(3000);
                    break;
                }
            }
            if (exit(isAim)) {
                return;
            }
        }
        if (exit(isAim)) {
            return;
        }
    }
}
void memory::hits() {
    while (true) {
        rpm<int>(offsetConnection, connection);
        if (connection == 6) {
            rpm<int>(offsetHits, shotsLanded);
        }
        while (connection == 6) {
            const auto shotsLandedLast = shotsLanded;
            rpm<int>(offsetHits, shotsLanded);
            if (shotsLanded > shotsLandedLast) {
                for (auto hits = 0; hits < shotsLanded - shotsLandedLast; hits++) {
                    Beep(hitsPitch, hitsTime);
                    z(hitsTime + 1);
                }
            }
            if (exit(isHits)) {
                return;
            }
        }
        if (exit(isHits)) {
            return;
        }
    }
}
memory::~memory() {
    CloseHandle(gameHandle);
}
