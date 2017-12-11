#include "../../dllmain.h"

void CRecoilControl::RecoilControl() {
	// TODO save old view punch
	eng.SetViewAngle(eng.NormalizeAngle(eng.GetViewAngle() - eng.GetAimPunch())); // TODO operator overloading
}

CRecoilControl rcs;
