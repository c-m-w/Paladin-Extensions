#pragma once
#define STANDARD_H
class standard: public memory {
    const int oct1 = 150841200;
    const int days = 86400;
    struct user {
        TCHAR * username;
        int hardware;
        time_t expire;
    };
    user owners[51]; // 50 MAX OTHER USERS
    user currentUser;
    SYSTEM_INFO currentUserHardware;

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
    bool forCheck(user owner) const;
    void getOwners();
public:
    int multi = 0;
    // ctor -> theme + other
    standard();
    // HWID check
    int ownerCheck();
    // force quit thread
    void force() const;
    // admin check
    bool adminCheck();
    // check if ac is running
    int killAc(LPCSTR acName, char acExe);
    // dctor
    ~standard();
};
