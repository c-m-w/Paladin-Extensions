#include "../main.h"

void LogDebugMsg(DebugMessage type, char * msg, ...) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole != INVALID_HANDLE_VALUE) {
		switch (type) {
			case SCS:
				SetConsoleTextAttribute(hConsole, 10);
				printf("\n[SCS] ");
				break;
			case DBG:
				SetConsoleTextAttribute(hConsole, 15);
				printf("\n[DBG] ");
				break;
			case WRN:
				SetConsoleTextAttribute(hConsole, 14);
				printf("\n[WRN] ");
				break;
			case ERR:
				SetConsoleTextAttribute(hConsole, 12);
				printf("\n[ERR] ");
				break;
			case LER:
				SetConsoleTextAttribute(hConsole, 12);
				printf("\n[LER] ");
				break;
			default:
				SetConsoleTextAttribute(hConsole, 15);
				printf("\n[DBG] ");
		}
		SetConsoleTextAttribute(hConsole, 7);
		//Ideally we want to dynamically allocate this, might do later (for now, stick to a max of 2047 data characters)
		char cBuffer[2048] = {'\0'};
		va_list vaList;
		va_start(vaList, msg);
		vsnprintf(cBuffer, sizeof cBuffer, msg, vaList);
		va_end(vaList);
		printf(cBuffer);
	}
}

// Look up errors here: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx
void LogLastError() {
	DWORD error = GetLastError();
	if (!error) {
		LogDebugMsg(LER, "No error");
		return;
	}
	LPSTR errorString = nullptr;
	if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), LPSTR(&errorString), 0, nullptr)) {
		LogDebugMsg(LER, "[0x%08lu] - Unable to retrieve error description", error);
	}
	else {
		LogDebugMsg(LER, "[0x%08lu] - %s", error, errorString);
	}
	LocalFree(errorString);
}
