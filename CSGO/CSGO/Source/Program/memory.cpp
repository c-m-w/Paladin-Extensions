#include "memory.h"
MemoryManager::MemoryManager() {
	
}

MemoryManager::~MemoryManager() {
	if (hGame != nullptr || hGame != INVALID_HANDLE_VALUE) {
		CloseHandle(hGame);
	}
}
