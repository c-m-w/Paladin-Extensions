#pragma once

template<typename datatype> struct Address {
	DWORD loc = NULL; // location
	DWORD ptr = NULL; // this ptr
	datatype val = NULL; // value

	template<typename rdatatype> Address<datatype> operator+(const rdatatype &rhs)
	{
		if (typeid(DWORD) == typeid(rdatatype))
			loc += DWORD(rhs);
		else if (typeid(datatype) == typeid(rdatatype))
			val += datatype(rhs);
		return *this;
	}

	template<typename rdatatype> Address<datatype> operator-(const rdatatype &rhs)
	{
		if (typeid(DWORD) == typeid(rdatatype))
			loc -= DWORD(rhs);
		else if (typeid(datatype) == typeid(rdatatype))
			val -= datatype(rhs);
		return *this;
	}

	template<typename rdatatype> Address<datatype> &operator=(const rdatatype &rhs)
	{
		if (typeid(DWORD) == typeid(rdatatype))
			loc = DWORD(rhs);
		else if (typeid(datatype) == typeid(rdatatype))
			val = datatype(rhs);
		return *this;
	}

	template<typename rdatatype> Address<datatype> &operator+=(const rdatatype &rhs)
	{
		if (typeid(DWORD) == typeid(rdatatype))
			loc += DWORD(rhs);
		else if (typeid(datatype) == typeid(rdatatype))
			val += datatype(rhs);
		return *this;
	}

	template<typename rdatatype> Address<datatype> &operator-=(const rdatatype &rhs)
	{
		if (typeid(DWORD) == typeid(rdatatype))
			loc -= DWORD(rhs);
		else if (typeid(datatype) == typeid(rdatatype))
			val -= datatype(rhs);
		return *this;
	}

	template<typename rdatatype> bool operator==(const rdatatype &rhs)
	{
		if (typeid(DWORD) == typeid(rdatatype))
		{
			if (loc == DWORD(rhs))
			{
				return true;
			}
		}
		else if (typeid(datatype) == typeid(rdatatype))
		{
			if (val == datatype(rhs))
			{
				return true;
			}
		}
		return false;
	}

	template<typename rdatatype> bool operator!=(const rdatatype &rhs)
	{
		if (typeid(DWORD) == typeid(rdatatype))
		{
			if (loc != DWORD(rhs))
			{
				return true;
			}
		}
		else if (typeid(datatype) == typeid(rdatatype))
		{
			if (val != datatype(rhs))
			{
				return true;
			}
		}
		return false;
	}

	template<typename rdatatype> datatype operator&(const rdatatype &rhs)
	{
		if (typeid(datatype) == typeid(rdatatype))
			return val & datatype(rhs);
		return 0;
	}

	template<typename rdatatype> datatype operator|(const rdatatype &rhs)
	{
		if (typeid(datatype) == typeid(rdatatype))
			return val | datatype(rhs);
		return 0;
	}
};

namespace Addresses
{
	extern Address<DWORD> dwClientState;
	extern Address<uint8_t> cs_soState;

	extern Address<uint8_t> ksForceJump;
	extern Address<uint8_t> ksForceAttack;
	extern Address<float> flSensitivity;

	extern Address<DWORD> dwLocalPlayer;
	extern Address<frame> lp_fFlags;
	extern Address<total> lp_totalHitsOnServer;
}