#pragma once

enum class EQuitReasons
{
	UNKNOWN = -1,
	LOAD_LIBRARY_ERROR,
	SUCCESS,
	BLACKLISTED_CALL,
	PANIC
};

enum class EPremium
{
	BANNED = -2,
	EXPIRED,
	NOT_PREMIUM,
	PREMIUM
};

enum class EElevation
{
	UNTESTED = -1,
	NOT_ADMIN,
	ADMIN
};

enum class EAnticheatStatus
{
	NOT_FOUND = -1,
	FAILED,
	KILLED
};
