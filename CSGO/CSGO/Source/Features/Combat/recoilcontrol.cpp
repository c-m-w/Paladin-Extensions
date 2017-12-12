#include "../../dllmain.h"

void CRecoilControl::RecoilControl() {
	angle_t aCurrentAimPunch = eng.GetAimPunch() - aOldAimPunch;
	eng.SetViewAngle(eng.NormalizeAngle(eng.GetViewAngle() + aCurrentAimPunch));
	aOldAimPunch += aCurrentAimPunch;
	eng.WaitTicks(1);
}

CRecoilControl rcs;
