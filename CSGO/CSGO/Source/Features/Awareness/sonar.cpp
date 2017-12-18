#include "../../dllmain.h"
float ExPos;
float EyPos;
float EzPos;

float myxPos;
float myyPos;
float myzPos;

float distance;

/* DISTANCE FORMULA

 ____________________
√(x2−x1)^2+(y2−y1)^2

*/

void CSonar::Sonar()
{
	for (int iEntity = 1; iEntity < eng.GetGlobalVars().maxClients; iEntity++)
	{
		//iEntity = 10;
		if (!eng.GetEntityDormancy(iEntity))
		{
			/*
			if (eng.GetTeam() != eng.GetEntityTeam(iEntity))
			{
				
				ExPos = eng.GetEntityOrigin(iEntity).x;
				EyPos = eng.GetEntityOrigin(iEntity).y;
				EzPos = eng.GetEntityOrigin(iEntity).z;

				myxPos = eng.GetEntityOrigin(1).x;
				myyPos = eng.GetEntityOrigin(1).y;
				myzPos = eng.GetEntityOrigin(1).z;

				distance = sqrt(pow((EzPos - myzPos), 2) + pow((EyPos - myyPos), 2));

				std::cout << "Current Entity: " << iEntity << "  Dist: " << distance << std::endl;
				Sleep(20);

			}
			/*/
		}
	}
}

CSonar son;
