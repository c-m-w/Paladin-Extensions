#pragma once

#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Shell32.lib")

#include <Windows.h>
#include <Windowsx.h>
#include <commctrl.h>
#include <Ole2.h>
#include <shlobj.h>
#include <Shlwapi.h>
#include <Shellapi.h>
#include <tlhelp32.h>
#include <string>

#include "standard.h"