#include "stdafx.h"
#include "memory.h"
// ReSharper disable once CppPossiblyUninitializedMember
memory::memory() {
}
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
            z(15000);
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
    rpm<int>(offsetConnection, connection);
    z(1500);
    while (connection != 6 || GetForegroundWindow() != FindWindowA(nullptr, gameName)) {
        z(3500);
        rpm<int>(offsetConnection, connection);
    }
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
        screen = {temp.right - temp.left, temp.bottom - temp.top};
    } else {
        screen = {temp.right - temp.left - 6, temp.bottom - temp.top - 29};
    }
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
    offsetViewAngle += clientState;
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
                        z(bhopNextDelay);
                        for (auto x = 0; x < rand() % 7; x++) {
                            mouse_event(MOUSEEVENTF_WHEEL, 0, 0, WHEEL_DELTA * bhopDirection, 0);
                            z(7);
                        }
                    } else {
                        z(bhopNextDelay);
                        for (auto x = 0; x < rand() % 7; x++) {
                            mouse_event(MOUSEEVENTF_WHEEL, 0, 0, WHEEL_DELTA * bhopDirection, 0);
                            z(7);
                        }
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
                            if (tempTime[1] - tempTime[0] > trigTimeout) {
                                z(trigTimeout);
                                break;
                            }
                            if (!GetAsyncKeyState(keyTrig)) {
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
                            if (tempTime[1] - tempTime[0] > trigTimeout) {
                                z(trigTimeout);
                                break;
                            }
                            if (!GetAsyncKeyState(keyTrig)) {
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
                    if (tempTime[1] - tempTime[0] > slowTimeout) {
                        z(slowTimeout);
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
            viewPunchPrevious = {0, 0, 0};
            shotFiredPrevious = 0;
            while (GetAsyncKeyState(VK_LBUTTON)) {
                rpm<int>(offsetShotFired, shotFired);
                if (shotFired > rcsIgnoreShots && shotFired > shotFiredPrevious) {
                    rpm<vector>(offsetViewPunch, viewPunchCurrent);
                    // math
                    vector temp {viewPunchCurrent.x - viewPunchPrevious.x, viewPunchPrevious.y - viewPunchCurrent.y};
                    temp = {((rcsXMin + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (rcsXMax - rcsXMin))) * (temp.x * 2.f)), ((rcsYMin + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (rcsYMax - rcsYMin))) * (temp.y * 2.f)), 0};
                    if (wasInCross) {
                        temp = { temp.x * slowFactor, temp.y * slowFactor, 0};
                    }
                    temp = { temp.x / convertMouse, temp.y / convertMouse, 0};
                    // rounding
                    if (temp.x > 0) {
                        temp = { temp.x + 1, temp.y,0};
                    } else if (temp.x < 0) {
                        temp = { temp.x - 1, temp.y, 0};
                    }
                    if (temp.y > 0) {
                        temp = { temp.x, temp.y + 1, 0};
                    } else if (temp.y < 0) {
                        temp = { temp.x, temp.y - 1, 0};
                    }
                    mouseRcs = {-static_cast<int>(temp.y), -static_cast<int>(temp.x)};
                    // smoothing
                    const auto smoothing = rand() % (smoothFactorMax - smoothFactorMin) + smoothFactorMin;
                    if (isSmooth) {
                        for (auto smooth = 0; smooth < smoothing; smooth++) {
                            mouse_event(MOUSEEVENTF_MOVE, mouseRcs.x / smoothing, mouseRcs.y / smoothing, 0, 0);
                            z(smoothFactorMin);
                            if (!GetAsyncKeyState(VK_LBUTTON)) {
                                break;
                            }
                        }
                    } else {
                        mouse_event(MOUSEEVENTF_MOVE, mouseRcs.x, mouseRcs.y, 0, 0);
                    }
                    // readjustment
                    if (shotFired % 10 == 0 && isSmooth) {
                        mouse_event(MOUSEEVENTF_MOVE, smoothing, smoothing, 0, 0);
                    }
                    // storing
                    viewPunchPrevious = viewPunchCurrent;
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
                    rpm<DWORD>(offsetEntities + (inCross - 1) * 0x10, enemyPlayer);
                    rpm<vector>(enemyPlayer + 0x134, enemyPlayerLocation);
                    rpm<vector>(offsetPlayerLocation, localPlayerLocation);
                    rpm<vector>(localPlayer + offsetPlayerView, localPlayerDisplace);
                    rpm<vector>(enemyPlayer + offsetPlayerView, enemyPlayerDisplace);
                    rpm<vector>(offsetViewAngle, viewAngle);
                    rpm<vector>(offsetViewPunch, viewPunchCurrent);
                    const vector del = {localPlayerLocation.x - enemyPlayerLocation.x, localPlayerLocation.y - enemyPlayerLocation.y, localPlayerLocation.z + localPlayerDisplace.z - enemyPlayerLocation.z - enemyPlayerDisplace.z + aimDisplace};
                    vector temp = {0, 0, 0};
                    // math
                    if (!del.x && !del.y) {
                        if (del.z > 0) {
                            temp.y = -89;
                        } else {
                            temp.y = 89;
                        }
                    } else {
                        const auto hypot = sqrt(del.x * del.x + del.y * del.y);
                        temp.y = atan2(del.z, hypot) * (180.f / pi);
                        temp.x = atan2(del.y, del.x) * (180.f / pi) + 180;
                    }
                    // clamping
                    if (temp.y > 89) {
                        temp.y = 89;
                    } else if (temp.y < -89) {
                        temp.y = -89;
                    }
                    while (temp.x < -180) {
                        temp.x += 360;
                    }
                    while (temp.x > 180) {
                        temp.x -= 360;
                    }
                    // change in angle
                    temp.x = (viewAngle.y - temp.x - viewPunchCurrent.y) / convertMouse;
                    temp.y = (viewAngle.x - temp.y - viewPunchCurrent.x) / convertMouse;
                    if (wasInCross) {
                        temp.x *= 2;
                        temp.y *= 2;
                    }
                    // rounding
                    mouseAim = { static_cast<int>(aimOver * temp.x), -static_cast<int>(aimOver * temp.y) };
                    if (mouseAim.x > 0) {
                        mouseAim = { mouseAim.x + 1, mouseAim.y };
                    }
                    else if (mouseAim.x < 0) {
                        mouseAim = { mouseAim.x - 1, mouseAim.y };
                    }
                    if (mouseAim.y > 0) {
                        mouseAim = { mouseAim.x, mouseAim.y + 1 };
                    }
                    else if (mouseAim.y < 0) {
                        mouseAim = { mouseAim.x, mouseAim.y - 1 };
                    }
                    // smoothing
                    const auto smoothing = rand() % (smoothFactorMax - smoothFactorMin) + smoothFactorMin;
                    if (isSmooth) {
                        for (auto smooth = 0; smooth < smoothing; smooth++) {
                            mouse_event(MOUSEEVENTF_MOVE, mouseAim.x / smoothing, mouseAim.y / smoothing, 0, 0);
                            z(smoothFactorMin);
                            if (!GetAsyncKeyState(VK_LBUTTON)) {
                                break;
                            }
                        }
                    } else {
                        mouse_event(MOUSEEVENTF_MOVE, mouseAim.x, mouseAim.y, 0, 0);
                        z(5);
                    }
                }
                tempTime[1] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                if (aimTimeout && tempTime[1] - tempTime[0] > aimTimeout) {
                    z(aimTimeout);
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
