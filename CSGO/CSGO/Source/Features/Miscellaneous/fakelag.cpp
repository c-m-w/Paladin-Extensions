#include "../../dllmain.h"

void CFakeLag::FakeLag( )
{
	if ( eng.GetGlobalVars( ).uiTickCount % 16 < 15 ) // change 15 to amount of packets to choke, limited to 15
	{
		eng.SetSendPackets( false );
	}
	else
	{
		eng.SetSendPackets( true );
	}
}

CFakeLag lag;
