#include "debug.h"

void LogDebugMsg(DBG_MSG type, unsigned int layer, char *msg, ...)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole != INVALID_HANDLE_VALUE)
    {

        //Experimental output
        for (unsigned i = 0; i < layer + 1; i++)
            printf("\t");
        if (layer > 1)
            printf("|-> ");

        switch (type)
        {
        case SCS:
            SetConsoleTextAttribute(hConsole, 10);
            printf("[SCS] ");
            break;
        case DBG:
            SetConsoleTextAttribute(hConsole, 15);
            printf("[DBG] ");
            break;
        case WRN:
            SetConsoleTextAttribute(hConsole, 14);
            printf("[WRN] ");
            break;
        case ERR:
            SetConsoleTextAttribute(hConsole, 12);
            printf("[ERR] ");
            break;
        case LER:
            SetConsoleTextAttribute(hConsole, 12);
            printf("[LER] ");
            break;
        default:
            SetConsoleTextAttribute(hConsole, 15);
            printf("[DBG] ");
        }

        SetConsoleTextAttribute(hConsole, 7);

        /*	!!! IMPORTANT !!!
        *
        *	Be cautious about sending long debug messages
        *	Current limit is 2048 chars (2047 if you count null terminator)
        *	If you want, you can expand this buffer, or you can recode this part to handle buffer overflows
        *
        */
        char buf[2048] = {};

        va_list list;

        va_start(list, msg);
        vsnprintf(buf, sizeof(buf), msg, list);
        va_end(list);

        printf(buf);
    }

    return;
}

/*
*	Look up errors here: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx
*/
void LogLastError(unsigned int layer)
{
    DWORD error = GetLastError();

    if (!error)
    {
        LogDebugMsg(LER, layer, "No error\n");
        return;
    }

    LPSTR errorString = nullptr;

    if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&errorString, 0, NULL))
        LogDebugMsg(LER, layer, "[0x%08lu] - Unable to retrieve error description\n", error);
    else
        LogDebugMsg(LER, layer, "[0x%08lu] - %s\n", error, errorString);

    LocalFree(errorString);

    return;
}