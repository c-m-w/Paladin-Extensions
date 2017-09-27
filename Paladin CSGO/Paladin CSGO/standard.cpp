#include "stdafx.h"
#include "standard.h"
standard::standard() {
    const auto instanceSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 instanceEntry;
    Process32First(instanceSnap, &instanceEntry);
    do {
        if (!_stricmp(instanceEntry.szExeFile, "CSGO Cheat.exe")) {
            // ENTER cheat exe name
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
    srand(static_cast<unsigned int>(time(nullptr)));
    cci.dwSize = 25; // v console cursor length to invisible
    cci.bVisible = false; // v console cursor to invisible
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
    z(1);
    MoveWindow(GetConsoleWindow(), 300, 300, 339, 279, false); // window size -> 30x50
}
void standard::forCheck(const TCHAR * owner) {
    for (auto x = 1; x < 256; x++) {
        if (owner[x - 1] && owner[x] != currentUser[x]) {
            checkfor--;
        }
    }
}
bool standard::ownerCheck() {
    GetUserName(currentUser, &size);
    forCheck(owner4);
    if (checkfor == 3) {
        forCheck(owner3);
    }
    if (checkfor == 2) {
        forCheck(owner2);
    }
    if (checkfor == 1) {
        forCheck(owner1);
    }
    if (!checkfor) {
        return false;
    }
    return true;
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
standard::~standard() {}
