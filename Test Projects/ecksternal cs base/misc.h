#pragma once
void wait(unsigned int t);
inline int msTime();
/*
 *	Why use pointers?
 *	Angle	- 12 bytes
 *	Pointer	- 4 bytes
 */
void normalize(angle * angle);
void clamp(angle * angle);
void round(angle * angle);
void smoothe(angle * cur, angle * tar);
//Debug stuff
void Debug(DBG_MSG type, char * msg, ...);
void LogLastError();
