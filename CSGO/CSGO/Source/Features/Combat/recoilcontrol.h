#pragma once

class CRecoilControl
{
	angle_t aOldAimPunch = { 0, 0, 0 };
public:
	void RecoilControl( );
};

extern CRecoilControl rcs;
