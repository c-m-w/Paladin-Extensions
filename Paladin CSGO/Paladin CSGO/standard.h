#pragma once
#define STANDARD_H
class standard: public memory {
    const TCHAR owner4[257] = ""; // ENTER
    const TCHAR owner3[257] = "";
    const TCHAR owner2[257] = "Lucas";
    const TCHAR owner1[257] = "bhopfu1";
    TCHAR currentUser[257];
    DWORD size = 257;
    const char * windowName = "bhopfu1's Multihack";
    CONSOLE_FONT_INFOEX cfiEx = {
        0
    };
    CONSOLE_CURSOR_INFO cci = {
        0
    };
    HANDLE selfHandle = nullptr;
    TOKEN_ELEVATION selfAdminTokenElevation;
    DWORD selfSize = sizeof(TOKEN_ELEVATION);
    int checkfor = 4; // ENTER
    void forCheck(const TCHAR * owner);
public:
    int multi = -1;
    // ctor -> theme + other
    standard();
    // HWID check
    bool ownerCheck();
    // force quit thread
    void force() const;
    // admin check
    bool adminCheck();
    // check if ac is running
    int killAc(LPCSTR acName, char acExe);
    // dctor
    ~standard();
};
