#include "stdafx.h"
#include "standard.h"
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
    srand(static_cast<unsigned int>(time(nullptr)));
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
    }
    return true;
}
void standard::getOwners() {
    owners[0].username = "bhopfu1";
    owners[0].hardware = 12 * 856;
    owners[0].expire = sep1 + 1 * days;
    owners[1].username = "Lucas";
    owners[1].hardware = 8 * 0;
    owners[1].expire = sep1 + 365 * days;
    // TODO GET OTHER OWNERS
}
int standard::ownerCheck() {
    if (sep1 > time(nullptr) && time(nullptr) - sep1 > days) { // TODO REPLACE SEP1 WITH TIME OF SERVER. JUST CHECK IF IT'S WITHIN 24 HOURS
        return 0;
    }
    GetUserName(currentUser.username, &size);
    getOwners();
    int temp;
    for (auto x = 0; x <= 51; x++) {
        if (owners[x].username && forCheck(owners[x])) {
            temp = x;
        } else {
            return 0;
        }
    }
    GetSystemInfo(&currentUserHardware);
    currentUser.hardware = currentUserHardware.dwNumberOfProcessors * currentUserHardware.dwProcessorType;
    if (currentUser.hardware != owners[temp].hardware) {
        return 0;
    }
    if (currentUser.expire < time(nullptr)) {
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
standard::~standard() {}
