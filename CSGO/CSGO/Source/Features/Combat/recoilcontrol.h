#pragma once

class CRecoilControl
{
	int iOldShotsFired = 0;
	angle_t angOldAimPunch { 0, 0, 0 };
public:
	void RecoilControl( );
};

extern CRecoilControl rcs;
