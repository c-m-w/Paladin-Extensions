#include "stdafx.h"
#include "standard.h"
#pragma warning(disable : 4996)
standard::standard() {
    const auto instanceSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 instanceEntry;
    Process32First(instanceSnap, &instanceEntry);
    do {
        if (!_stricmp(instanceEntry.szExeFile, "Paladin CSGO.exe")) {
            multi += 1;
        }
    } while (Process32Next(instanceSnap, &instanceEntry));
    if (instanceSnap != INVALID_HANDLE_VALUE) {
        CloseHandle(instanceSnap);
    }
    SetConsoleTitle(windowName);
    system("Color 0B"); // console color + text color
    cfiEx.cbSize = sizeof cfiEx;
    cfiEx.dwFontSize.X = 6;
    cfiEx.dwFontSize.Y = 8;
    wcscpy_s(cfiEx.FaceName, L"Terminal");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cfiEx);
    EnableMenuItem(GetSystemMenu(GetConsoleWindow(), false), SC_CLOSE, MF_GRAYED);
    SetWindowLong(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~SC_CLOSE & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    srand(timeNow);
    cci.dwSize = 25; // v console cursor length to invisible
    cci.bVisible = false; // v console cursor to invisible
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
    z(1);
    MoveWindow(GetConsoleWindow(), 300, 300, 339, 279, false); // window size -> 30x50
}
bool standard::forCheck(const user owner) const {
    for (auto x = 0; x < 256; x++) {
        if (owner.username[x] && owner.username[x] != currentUser.username[x]) {
            return false;
        }
        if (!owner.username[x]) {
            break;
        }
    }
    return true;
}
void standard::getOwners() {
    owners[0].username = "bhopfu1";
    owners[0].hardware = 12 * 4095;
    owners[0].expire = oct1 + 35 * days;
    owners[1].username = "Cole White";
    owners[1].hardware = 4 * 15;
    owners[1].expire = oct1 + 365 * days;
    // TODO GET OTHER OWNERS FROM SERVER
}
int standard::ownerCheck() {
    if (oct1 > timeNow && oct1 - timeNow > days) {
        // TODO REPLACE OCT1 WITH TIME OF SERVER IN THIS LINE ONLY
        return 0;
    }
    char currentUserUsername[256];
    GetUserName(currentUserUsername, &size);
    currentUser.username = currentUserUsername;
    getOwners();
    int x;
    for (x = 0; x <= 51; x++) {
        if (owners[x].username && forCheck(owners[x])) {
            break;
        }
        if (x == 51) {
            return 0;
        }
    }
    GetSystemInfo(&currentUserHardware);
    currentUser.hardware = currentUserHardware.dwActiveProcessorMask * currentUserHardware.dwProcessorType;
    if (currentUser.hardware != owners[x].hardware) {
        return 0;
    }
    currentUser.expire = owners[x].expire;
    if (currentUser.expire < timeNow) {
        return -1;
    }
    return 1;
}
void standard::force() const {
    while (!multi) {
        if (GetAsyncKeyState(VK_F1)) {
            terminate();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
bool standard::adminCheck() {
    OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &selfHandle);
    if (GetTokenInformation(selfHandle, TokenElevation, &selfAdminTokenElevation, sizeof selfAdminTokenElevation, &selfSize)) {
        CloseHandle(selfHandle);
        return selfAdminTokenElevation.TokenIsElevated;
    }
    CloseHandle(selfHandle);
    return false;
}
int standard::killAc(const LPCSTR acName, const char acExe) {
    if (FindWindowA(nullptr, acName)) {
        if (adminCheck()) {
            system("taskkill /F /T /IM " + acExe);
            return 1;
        }
        return 0;
    }
    return -1;
}
standard::~standard() {
}
