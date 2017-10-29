#include "main.h"

void wait(unsigned int t) 
{
	std::this_thread::sleep_for(std::chrono::milliseconds(t));
}

inline int msTime() 
{
	return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

void normalize(angle *angle)
{

	if (angle->pitch > 89.f)
		angle->pitch = 89.f;
	else if (angle->pitch < -89.f)
		angle->pitch = -89.f;

	while (angle->yaw > 180.f)
		angle->yaw -= 360.f;
	while (angle->yaw < -180.f)
		angle->yaw += 360.f;

	if (angle->roll > 50.f)
		angle->roll = 50.f;

	if (angle->roll < -50.f)
		angle->roll = 50.f;

	return;
}

void clamp(angle *angle)
{
	if (angle->pitch > 89.f)
		angle->pitch = 89.f;
	else if (angle->pitch < -89.f)
		angle->pitch = -89.f;

	if (angle->yaw > 180.f)
		angle->yaw = 180.f;
	else if (angle->yaw < -180.f)
		angle->yaw = -180.f;

	if (angle->roll > 50.f)
		angle->roll = 50.f;
	else if (angle->roll < -50.f)
		angle->roll = 50.f;
	
	return;
}

void round(angle *angle)
{

	//ToDo

	return;
}

void smoothe(angle *cur, angle *tar)
{

	if (hypot(tar->pitch - cur->pitch, tar->yaw - cur->yaw) > 22.f /*&& !Smoothing*/) {

		if (tar->pitch - cur->pitch > 0) {
			//TODO
		}else if (tar->pitch - cur->pitch < 0) {
			//TODO
		}

		if (tar->yaw - cur->yaw > 0) {
			//TODO
		}else if (tar->yaw - cur->yaw < 0) {
			//TODO
		}

	}

	return;
}

//Debug stuff
void Debug(DBG_MSG type, char *msg, ...)
{

#ifdef _DEBUG

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole != INVALID_HANDLE_VALUE)
	{

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
		default:
			SetConsoleTextAttribute(hConsole, 15);
			printf("[DBG] ");
		}

		SetConsoleTextAttribute(hConsole, 7);

		//Our debug messages shouldn't exceed this many chars
		char buf[2048] = {};

		va_list va_alist;

		va_start(va_alist, msg);
		vsnprintf(buf, sizeof(buf), msg, va_alist);
		va_end(va_alist);

		printf(buf);
	}

#endif

	return;
}

//Look up errors here: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx
void LogLastError()
{

#ifndef _DEBUG

	DWORD error = GetLastError();

	if (!error)
		return;

	LPSTR errorString = nullptr;

	if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&errorString, 0, NULL))
		Debug(ERR, "[0x%lu] - Unable to retrieve error description\n", error);
	else
		Debug(ERR, "[0x%lu] - %s\n", error, errorString);

	LocalFree(errorString);

#endif

	return;
}