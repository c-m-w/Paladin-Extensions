#include "main.h"

namespace Addresses 
{
	// global Engine addresses
	// Engine pointer addresses
	Address<DWORD> dwClientState		= { 0x5A783C };
	Address<uint8_t> cs_soState			= { 0x108 };

	// global Client addresses
	Address<uint8_t> ksForceJump		= { 0x4F2419C };
	Address<uint8_t> ksForceAttack		= { 0x2ECF46C };
	Address<float> flSensitivity		= { 0xAB547C, 0xAB5450 };

	// Client pointer addresses
	Address<DWORD> dwLocalPlayer		= { 0xAAFD7C };
	Address<frame> lp_fFlags			= { 0x100 };
	Address<total> lp_totalHitsOnServer	= { 0xBA94 };
}