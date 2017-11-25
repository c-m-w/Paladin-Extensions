#include "main.h"

Automation *aut = nullptr;

void Automation::AutoJump()
{
	while (1)
	{
		if (bExit) 
			return;

		if (GetAsyncKeyState(VK_SPACE) & 1) 
		{
			mem->Read(Addresses::ksForceJump);

			if (Addresses::ksForceJump == Keystroke::PRESS)
				eng->Jump(int(Keystroke::RELEASE));

			mem->Read(Addresses::lp_fFlags);
			
			dbg->LogDebugMsg(DBG, "Local Player");
			dbg->LogDebugMsg(DBG, "Loc: %p", Addresses::dwLocalPlayer.loc);
			dbg->LogDebugMsg(DBG, "Ptr: %p", Addresses::dwLocalPlayer.ptr);
			dbg->LogDebugMsg(DBG, "Val: %u", Addresses::dwLocalPlayer.val);

			dbg->LogDebugMsg(DBG, "Flags");
			dbg->LogDebugMsg(DBG, "Loc: %p", Addresses::lp_fFlags.loc);
			dbg->LogDebugMsg(DBG, "Ptr: %p", Addresses::lp_fFlags.ptr);
			dbg->LogDebugMsg(DBG, "Val: %u", Addresses::lp_fFlags.val);

			if (Addresses::lp_fFlags & FL_ONGROUND) 
				eng->Jump(int(Keystroke::SCROLL));
			else 
				Wait(1);
		}
		else 
		{
			Wait(1);
		}	
	}
}