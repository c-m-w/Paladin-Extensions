#include "debug.h"

void LogDebugMsg(DebugMessage dmType, unsigned short iLayer, char * cMessage, ...) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole != INVALID_HANDLE_VALUE) {
		//Experimental output
		for (unsigned i = 0; i < iLayer + 1; i++) {
			printf("\t");
		}
		if (iLayer > 1) {
			printf("|-> ");
		}
		switch (dmType) {
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
		char cBuffer[2048] = {};
		va_list vaList;
		va_start(vaList, cMessage);
		vsnprintf(cBuffer, sizeof cBuffer, cMessage, vaList);
		va_end(vaList);
		printf(cBuffer);
	}
}

/* Look up errors here:
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx
 */
void LogLastError(unsigned int iLayer) {
	DWORD error = GetLastError();
	if (!error) {
		LogDebugMsg(LER, iLayer, "No error\n");
		return;
	}
	LPSTR errorString = nullptr;
	if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), LPWSTR(&errorString), 0, nullptr)) {
		LogDebugMsg(LER, iLayer, "[0x%08lu] - Unable to retrieve error description\n", error);
	} else {
		LogDebugMsg(LER, iLayer, "[0x%08lu] - %s\n", error, errorString);
	}
	LocalFree(errorString);
}
