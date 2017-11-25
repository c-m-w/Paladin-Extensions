#include "main.h"

Automation *aut = nullptr;

void Automation::AutoJump()
{
	dbg->LogDebugMsg(DBG, "Thread Started");
	while (1)
	{
		if (bExit) 
		{
			dbg->LogDebugMsg(DBG, "We Out");
			return;
		}

		if (GetAsyncKeyState(VK_SPACE) & 1) 
		{
			dbg->LogDebugMsg(DBG, "Space Down");

			mem->Read(Addresses::ksForceJump);

			if (Addresses::ksForceJump == Keystroke::PRESS)
				eng->Jump(int(Keystroke::RELEASE));

			mem->Read(Addresses::lp_fFlags);

			dbg->LogDebugMsg(DBG, "Flags: %u | Result: %u", Addresses::lp_fFlags.val, Addresses::lp_fFlags.val & FL_ONGROUND);

			if (Addresses::lp_fFlags & FL_ONGROUND) 
			{
				dbg->LogDebugMsg(DBG, "Jump");
				eng->Jump(int(Keystroke::SCROLL));
			}
			else 
			{
				Wait(1);
			}
		}
		else 
		{
			Wait(1);
		}
			
	}
}