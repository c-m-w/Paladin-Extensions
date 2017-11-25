#include "main.h"

namespace Addresses 
{
	// global Engine addresses
	// Engine pointer addresses
	Address<DWORD> dwClientState		= { 0x57D844 };
	Address<uint8_t> cs_soState			= { 0x108 };

	// global Client addresses
	Address<uint8_t> ksForceJump		= { 0x4F0ED94 };
	Address<uint8_t> ksForceAttack		= { 0x2EB9EA0 };
	Address<float> flSensitivity		= { 0xAA04EC, 0xAA04C0 };

	// Client pointer addresses
	Address<DWORD> dwLocalPlayer		= { 0xA9ADEC };
	Address<frame> lp_fFlags			= { 0x100 };
	Address<total> lp_totalHitsOnServer	= { 0xBA94 };
}