#include "main.h"

Automation *aut = nullptr;

void Automation::AutoJump()
{
	while (1)
	{
		if (bExit) 
			return;

		if (GetAsyncKeyState(VK_SPACE)) 
		{
			mem->Read(Addresses::ksForceJump);

			/*
			if (Addresses::ksForceJump == Keystroke::PRESS)
				eng->Jump(int(Keystroke::RELEASE));
			*/

			if (Addresses::ksForceJump.val == 5)
				eng->Jump(int(Keystroke::RELEASE));

			mem->Read(Addresses::lp_fFlags);

			if (Addresses::lp_fFlags.val & FL_ONGROUND)
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