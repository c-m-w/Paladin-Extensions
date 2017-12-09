#include "../../main.h"

void CNoFlash::NoFlash() {
	eng.SetFlashMaxAlpha(0);
}

CNoFlash nof;
